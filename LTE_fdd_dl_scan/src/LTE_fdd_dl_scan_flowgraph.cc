/*******************************************************************************

    Copyright 2013-2015, 2021 Ben Wojtowicz

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

    File: LTE_fdd_dl_scan_flowgraph.cc

    Description: Contains all the implementations for the LTE FDD DL Scanner
                 gnuradio flowgraph.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2013    Ben Wojtowicz    Created file
    07/21/2013    Ben Wojtowicz    Added support for HackRF Jawbreaker
    08/26/2013    Ben Wojtowicz    Updates to support GnuRadio 3.7 and added a
                                   new hardware discovery mechanism.
    11/13/2013    Ben Wojtowicz    Added support for USRP B2X0.
    11/30/2013    Ben Wojtowicz    Added support for bladeRF.
    04/12/2014    Ben Wojtowicz    Pulled in a patch from Jevgenij for
                                   supporting non-B2X0 USRPs.
    07/22/2014    Ben Wojtowicz    Pulled in a patch from Jeff Long to optimally
                                   set the master clock rate for USRP B2X0.
    12/16/2014    Ben Wojtowicz    Pulled in a patch from Ruben Merz to add
                                   USRP X300 support.
    03/11/2015    Ben Wojtowicz    Added UmTRX support.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_scan_flowgraph.h"
#include "LTE_fdd_dl_scan_interface.h"
#include "uhd/usrp/multi_usrp.hpp"
#include "osmosdr/device.h"

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

LTE_fdd_dl_scan_flowgraph::LTE_fdd_dl_scan_flowgraph() :
    scan_thread{NULL}, started{false}
{
}

LTE_fdd_dl_scan_flowgraph::~LTE_fdd_dl_scan_flowgraph()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        stop();
}

bool LTE_fdd_dl_scan_flowgraph::is_started()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    return started;
}

int LTE_fdd_dl_scan_flowgraph::start(uint16 dl_earfcn, void* iface)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        return -1;

    if(NULL == top_block.get())
        top_block = gr::make_top_block("top");
    LTE_FDD_DL_SCAN_HW_TYPE_ENUM hardware_type;
    if(NULL == samp_src.get())
        setup_sample_source(hardware_type);
    liblte_fdd_dl_scan_block_is_started_callback is_cb(
        &liblte_fdd_dl_scan_block_is_started_callback::wrapper<LTE_fdd_dl_scan_flowgraph, &LTE_fdd_dl_scan_flowgraph::is_started>,
        this);
    liblte_fdd_dl_scan_block_switch_freq_callback sf_cb(
        &liblte_fdd_dl_scan_block_switch_freq_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::switch_to_next_freq>,
        iface);
    liblte_fdd_dl_scan_block_send_pcap_callback sp_cb(
        &liblte_fdd_dl_scan_block_send_pcap_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::send_pcap_msg>,
        iface);
    liblte_fdd_dl_scan_block_send_channel_found_begin_callback scfb_cb(
        &liblte_fdd_dl_scan_block_send_channel_found_begin_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::send_channel_found_begin_msg>,
        iface);
    liblte_fdd_dl_scan_block_send_sib1_callback ss1_cb(
        &liblte_fdd_dl_scan_block_send_sib1_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::send_sib1_msg>,
        iface);
    liblte_fdd_dl_scan_block_send_sib_callback ss_cb(
        &liblte_fdd_dl_scan_block_send_sib_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::send_sib_msg>,
        iface);
    liblte_fdd_dl_scan_block_send_channel_found_end_callback scfe_cb(
        &liblte_fdd_dl_scan_block_send_channel_found_end_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::send_channel_found_end_msg>,
        iface);
    liblte_fdd_dl_scan_block_send_channel_not_found_callback scnf_cb(
        &liblte_fdd_dl_scan_block_send_channel_not_found_callback::wrapper<LTE_fdd_dl_scan_interface, &LTE_fdd_dl_scan_interface::send_channel_not_found_msg>,
        iface);
    if(NULL == scan_block.get())
    {
        switch(hardware_type)
        {
        case LTE_FDD_DL_SCAN_HW_TYPE_USRP_B:
        case LTE_FDD_DL_SCAN_HW_TYPE_USRP_N:
        case LTE_FDD_DL_SCAN_HW_TYPE_USRP_X:
        case LTE_FDD_DL_SCAN_HW_TYPE_HACKRF:
        case LTE_FDD_DL_SCAN_HW_TYPE_BLADERF:
            scan_block = liblte_fdd_dl_scan_block_make(is_cb, sf_cb, sp_cb, scfb_cb, ss1_cb,
                                                       ss_cb, scfe_cb, scnf_cb,
                                                       sizeof(gr_complex), 100,
                                                       LIBLTE_PHY_FS_15_36MHZ);
            break;
        case LTE_FDD_DL_SCAN_HW_TYPE_UMTRX:
            scan_block = liblte_fdd_dl_scan_block_make(is_cb, sf_cb, sp_cb, scfb_cb, ss1_cb,
                                                       ss_cb, scfe_cb, scnf_cb,
                                                       sizeof(gr_complex), 100,
                                                       LIBLTE_PHY_FS_7_68MHZ);
            break;
        case LTE_FDD_DL_SCAN_HW_TYPE_UNKNOWN:
        default:
            printf("Unknown hardware, treating like RTL-SDR\n");
        case LTE_FDD_DL_SCAN_HW_TYPE_RTL_SDR:
            scan_block = liblte_fdd_dl_scan_block_make(is_cb, sf_cb, sp_cb, scfb_cb, ss1_cb,
                                                       ss_cb, scfe_cb, scnf_cb,
                                                       sizeof(gr_complex), 100,
                                                       LIBLTE_PHY_FS_1_92MHZ);
            break;
        }
    }

    if(NULL == top_block.get() || NULL == samp_src.get() || NULL == scan_block.get() ||
       0 == samp_src->get_num_channels())
        return -1;

    switch(hardware_type)
    {
    case LTE_FDD_DL_SCAN_HW_TYPE_USRP_B:
        samp_src->set_sample_rate(15360000);
        samp_src->set_gain_mode(false);
        samp_src->set_gain(35);
        samp_src->set_bandwidth(10000000);
        break;
    case LTE_FDD_DL_SCAN_HW_TYPE_USRP_N:
        samp_src->set_sample_rate(25000000);
        samp_src->set_gain_mode(false);
        samp_src->set_gain(35);
        samp_src->set_bandwidth(10000000);
        break;
    case LTE_FDD_DL_SCAN_HW_TYPE_UMTRX:
        samp_src->set_sample_rate(13000000);
        samp_src->set_gain_mode(false);
        samp_src->set_gain(35);
        samp_src->set_bandwidth(5000000);
        break;
    case LTE_FDD_DL_SCAN_HW_TYPE_USRP_X:
        samp_src->set_sample_rate(15360000);
        samp_src->set_gain_mode(false);
        samp_src->set_gain(25);
        samp_src->set_bandwidth(10000000);
        break;
    case LTE_FDD_DL_SCAN_HW_TYPE_HACKRF:
        samp_src->set_sample_rate(15360000);
        samp_src->set_gain_mode(false);
        samp_src->set_gain(14);
        samp_src->set_dc_offset_mode(osmosdr::source::DCOffsetAutomatic);
        break;
    case LTE_FDD_DL_SCAN_HW_TYPE_BLADERF:
        samp_src->set_sample_rate(15360000);
        samp_src->set_gain_mode(false);
        samp_src->set_gain(6, "LNA");
        samp_src->set_gain(33, "VGA1");
        samp_src->set_gain(3, "VGA2");
        samp_src->set_bandwidth(10000000);
        break;
    case LTE_FDD_DL_SCAN_HW_TYPE_UNKNOWN:
    default:
        printf("Unknown hardware, treating like RTL-SDR\n");
    case LTE_FDD_DL_SCAN_HW_TYPE_RTL_SDR:
        samp_src->set_sample_rate(1920000);
        samp_src->set_gain_mode(true);
        break;
    }
    samp_src->set_center_freq(liblte_interface_dl_earfcn_to_frequency(dl_earfcn));

    if(LTE_FDD_DL_SCAN_HW_TYPE_USRP_N == hardware_type)
    {
        resample_taps    = gr::filter::firdes::low_pass(384, 1, 0.00065, 0.0013, gr::filter::firdes::WIN_KAISER, 5);
        resampler_filter = gr::filter::rational_resampler_base_ccf::make(384, 625, resample_taps);
        top_block->connect(samp_src, 0, resampler_filter, 0);
        top_block->connect(resampler_filter, 0, scan_block, 0);
    }else if(LTE_FDD_DL_SCAN_HW_TYPE_UMTRX == hardware_type){
        resample_taps    = gr::filter::firdes::low_pass(192, 1, 0.00065, 0.0013, gr::filter::firdes::WIN_KAISER, 5);
        resampler_filter = gr::filter::rational_resampler_base_ccf::make(192, 325, resample_taps);
        top_block->connect(samp_src, 0, resampler_filter, 0);
        top_block->connect(resampler_filter, 0, scan_block, 0);
    }else{
        top_block->connect(samp_src, 0, scan_block, 0);
    }

    scan_thread = new std::thread(thread_runner, this);
    started     = true;

    return 0;
}

int LTE_fdd_dl_scan_flowgraph::stop()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(!started)
        return -1;

    started = false;
    scan_thread->join();
    delete scan_thread;
    top_block.reset();
    return 0;
}

void LTE_fdd_dl_scan_flowgraph::update_center_freq(uint16 dl_earfcn)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started &&
       NULL != samp_src.get())
        samp_src->set_center_freq(liblte_interface_dl_earfcn_to_frequency(dl_earfcn));
}

void LTE_fdd_dl_scan_flowgraph::setup_sample_source(LTE_FDD_DL_SCAN_HW_TYPE_ENUM &hw_type)
{
    // Try with UHD
    {
        uhd::device_addr_t  hint;
        uhd::device_addrs_t dev_addrs = uhd::device::find(hint);
        for(auto dev : dev_addrs)
        {
            osmosdr::source::sptr tmp_src = osmosdr::source::make("uhd");
            if(0 == tmp_src->get_sample_rates().size())
                continue;

            // Try USRP B
            uhd::usrp::multi_usrp::make(dev)->set_master_clock_rate(15360000);
            double mcr = uhd::usrp::multi_usrp::make(dev)->get_master_clock_rate();
            if(1 >= fabs(mcr - 15360000))
            {
                hw_type  = LTE_FDD_DL_SCAN_HW_TYPE_USRP_B;
                samp_src = tmp_src;
                return;
            }

            // Try USRP_N
            uhd::usrp::multi_usrp::make(dev)->set_master_clock_rate(100000000);
            mcr = uhd::usrp::multi_usrp::make(dev)->get_master_clock_rate();
            if(1 >= fabs(mcr - 100000000))
            {
                hw_type  = LTE_FDD_DL_SCAN_HW_TYPE_USRP_N;
                samp_src = tmp_src;
                return;
            }

            // Try UMTRX
            if(dev["type"] == "umtrx")
            {
                hw_type  = LTE_FDD_DL_SCAN_HW_TYPE_UMTRX;
                samp_src = tmp_src;
                return;
            }

            // Try USRP_X
            tmp_src.reset();
            tmp_src = osmosdr::source::make("uhd,master_clock_rate=184320000");
            if(dev["type"] == "x300")
            {
                hw_type  = LTE_FDD_DL_SCAN_HW_TYPE_USRP_X;
                samp_src = tmp_src;
                return;
            }
        }
    }

    // Try with osmosdr
    {
        // Try HACKRF
        osmosdr::source::sptr tmp_src = osmosdr::source::make("hackrf");
        if(0 != tmp_src->get_sample_rates().size())
        {
            hw_type  = LTE_FDD_DL_SCAN_HW_TYPE_HACKRF;
            samp_src = tmp_src;
            return;
        }

        // Try BLADERF
        tmp_src = osmosdr::source::make("bladerf");
        if(0 != tmp_src->get_sample_rates().size())
        {
            hw_type  = LTE_FDD_DL_SCAN_HW_TYPE_BLADERF;
            samp_src = tmp_src;
            return;
        }

        // Try RTL SDR
        tmp_src = osmosdr::source::make("rtl=0");
        if(0 != tmp_src->get_sample_rates().size())
        {
            hw_type  = LTE_FDD_DL_SCAN_HW_TYPE_RTL_SDR;
            samp_src = tmp_src;
            return;
        }
    }

    hw_type  = LTE_FDD_DL_SCAN_HW_TYPE_UNKNOWN;
    samp_src = osmosdr::source::make();
}

void LTE_fdd_dl_scan_flowgraph::thread_runner(LTE_fdd_dl_scan_flowgraph *fg)
{
    fg->top_block->run();

    fg->top_block->stop();
    fg->top_block->disconnect_all();
    fg->samp_src.reset();
    fg->scan_block.reset();
}
