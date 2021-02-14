/*******************************************************************************

    Copyright 2021 Ben Wojtowicz

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

    File: LTE_fdd_dl_fg_flowgraph.cc

    Description: Contains all the implementations for the LTE FDD DL File
                 Generator gnuradio flowgraph.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fg_flowgraph.h"

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

LTE_fdd_dl_fg_flowgraph::LTE_fdd_dl_fg_flowgraph() :
    started{false}
{
}

LTE_fdd_dl_fg_flowgraph::~LTE_fdd_dl_fg_flowgraph()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        stop();
}

bool LTE_fdd_dl_fg_flowgraph::is_started()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    return started;
}

bool LTE_fdd_dl_fg_flowgraph::start(std::string file_name,
                                    LTE_fdd_dl_fg_samp_buf_sptr &samp_buf,
                                    size_t out_size)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        return true;

    if(NULL == top_block.get())
        top_block = gr::make_top_block("top");

    if(NULL == samp_sink.get())
        samp_sink = gr::blocks::file_sink::make(out_size, file_name.c_str());

    if(NULL == top_block.get() || NULL == samp_sink.get() || NULL == samp_buf.get())
        return true;

    top_block->connect(samp_buf, 0, samp_sink, 0);
    fg_thread = new std::thread(thread_runner, this);
    started = true;
    return false;
}

bool LTE_fdd_dl_fg_flowgraph::stop()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(!started)
        return true;

    started = false;
    fg_thread->join();
    delete fg_thread;
    top_block.reset();
    return false;
}

void LTE_fdd_dl_fg_flowgraph::thread_runner(LTE_fdd_dl_fg_flowgraph *fg)
{
    fg->top_block->run();

    fg->top_block->stop();
    fg->top_block->disconnect_all();
    fg->samp_sink.reset();
}
