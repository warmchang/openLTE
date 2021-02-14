/*******************************************************************************

    Copyright 2013, 2015, 2021 Ben Wojtowicz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************

    File: LTE_file_recorder_flowgraph.cc

    Description: Contains all the implementations for the LTE file recorder
                 gnuradio flowgraph.

    Revision History
    ----------    -------------    --------------------------------------------
    08/26/2013    Ben Wojtowicz    Created file
    11/13/2013    Ben Wojtowicz    Added support for USRP B2X0.
    11/30/2013    Ben Wojtowicz    Added support for bladeRF.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_file_recorder_flowgraph.h"
#include "liblte_interface.h"
#include "uhd/usrp/multi_usrp.hpp"

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              GLOBAL VARIABLES
*******************************************************************************/


/*******************************************************************************
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

LTE_file_recorder_flowgraph::LTE_file_recorder_flowgraph() :
    fr_thread{NULL}, started{false}
{
}

LTE_file_recorder_flowgraph::~LTE_file_recorder_flowgraph()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        stop();
}

bool LTE_file_recorder_flowgraph::is_started()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    return started;
}

int LTE_file_recorder_flowgraph::start(uint16 earfcn, std::string file_name)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        return -1;

    if(NULL == top_block.get())
        top_block = gr::make_top_block("top");
    LTE_FILE_RECORDER_HW_TYPE_ENUM hardware_type;
    if(NULL == samp_src.get())
        setup_sample_source(hardware_type);
    if(NULL == file_sink.get())
        file_sink = gr::blocks::file_sink::make(sizeof(gr_complex), file_name.c_str());
    if(NULL == top_block.get() || NULL == samp_src.get() || NULL == file_sink.get() ||
       0 == samp_src->get_num_channels())
        return -1;

    switch(hardware_type)
    {
    case LTE_FILE_RECORDER_HW_TYPE_USRP:
        samp_src->set_sample_rate(15360000);
        samp_src->set_gain_mode(false);
        samp_src->set_gain(35);
        samp_src->set_bandwidth(10000000);
        break;
    case LTE_FILE_RECORDER_HW_TYPE_HACKRF:
        samp_src->set_sample_rate(15360000);
        samp_src->set_gain_mode(false);
        samp_src->set_gain(14);
        samp_src->set_dc_offset_mode(osmosdr::source::DCOffsetAutomatic);
        break;
    case LTE_FILE_RECORDER_HW_TYPE_BLADERF:
        samp_src->set_sample_rate(15360000);
        samp_src->set_gain_mode(false);
        samp_src->set_gain(6, "LNA");
        samp_src->set_gain(33, "VGA1");
        samp_src->set_gain(3, "VGA2");
        samp_src->set_bandwidth(10000000);
        break;
    case LTE_FILE_RECORDER_HW_TYPE_UNKNOWN:
    default:
        printf("Unknown hardware, treating like RTL-SDR\n");
    case LTE_FILE_RECORDER_HW_TYPE_RTL_SDR:
        samp_src->set_sample_rate(1920000);
        samp_src->set_gain_mode(true);
        break;
    }
    uint32 freq = liblte_interface_dl_earfcn_to_frequency(earfcn);
    if(freq == 0)
        freq = liblte_interface_ul_earfcn_to_frequency(earfcn);
    samp_src->set_center_freq(freq);
    top_block->connect(samp_src, 0, file_sink, 0);
    fr_thread = new std::thread(thread_runner, this);
    started   = true;

    return 0;
}

int LTE_file_recorder_flowgraph::stop()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(!started)
        return -1;

    started = false;
    fr_thread->join();
    delete fr_thread;
    top_block.reset();
    return 0;
}

void LTE_file_recorder_flowgraph::setup_sample_source(LTE_FILE_RECORDER_HW_TYPE_ENUM &hw_type)
{
    // Try USRP
    osmosdr::source::sptr tmp_src = osmosdr::source::make("uhd");
    uhd::device_addr_t    hint;
    double                mcr = 0.0;
    BOOST_FOREACH(const uhd::device_addr_t &dev, uhd::device::find(hint))
    {
        uhd::usrp::multi_usrp::make(dev)->set_master_clock_rate(30720000);
        mcr = uhd::usrp::multi_usrp::make(dev)->get_master_clock_rate();
    }
    if(0 != tmp_src->get_sample_rates().size() && 1 >= fabs(mcr - 30720000))
    {
        hw_type  = LTE_FILE_RECORDER_HW_TYPE_USRP;
        samp_src = tmp_src;
        return;
    }

    // Try HACKRF
    tmp_src = osmosdr::source::make("hackrf");
    if(0 != tmp_src->get_sample_rates().size())
    {
        hw_type  = LTE_FILE_RECORDER_HW_TYPE_HACKRF;
        samp_src = tmp_src;
        return;
    }

    // Try BLADERF
    tmp_src = osmosdr::source::make("bladerf");
    if(0 != tmp_src->get_sample_rates().size())
    {
        hw_type  = LTE_FILE_RECORDER_HW_TYPE_BLADERF;
        samp_src = tmp_src;
        return;
    }

    // Try RTL SDR
    tmp_src = osmosdr::source::make("rtl=0");
    if(0 != tmp_src->get_sample_rates().size())
    {
        hw_type  = LTE_FILE_RECORDER_HW_TYPE_RTL_SDR;
        samp_src = tmp_src;
        return;
    }

    hw_type  = LTE_FILE_RECORDER_HW_TYPE_UNKNOWN;
    samp_src = osmosdr::source::make();
}

void LTE_file_recorder_flowgraph::thread_runner(LTE_file_recorder_flowgraph *fg)
{
    fg->top_block->run();

    fg->top_block->stop();
    fg->top_block->disconnect_all();
    fg->samp_src.reset();
    fg->file_sink.reset();
}
