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

    File: LTE_fdd_dl_fs_flowgraph.cc

    Description: Contains all the implementations for the LTE FDD DL File
                 Scanner gnuradio flowgraph.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fs_flowgraph.h"

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

LTE_fdd_dl_fs_flowgraph::LTE_fdd_dl_fs_flowgraph() :
    fs_thread{NULL}, started{false}
{
}

LTE_fdd_dl_fs_flowgraph::~LTE_fdd_dl_fs_flowgraph()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        stop();
}

bool LTE_fdd_dl_fs_flowgraph::is_started()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    return started;
}

int LTE_fdd_dl_fs_flowgraph::start(std::string file_name,
                                   liblte_fdd_dl_scan_block_sptr &scan_block,
                                   size_t in_size)
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(started)
        return -1;

    if(NULL == top_block.get())
        top_block = gr::make_top_block("top");

    if(NULL == samp_source.get())
        samp_source = gr::blocks::file_source::make(in_size, file_name.c_str());

    if(NULL == top_block.get() || NULL == samp_source.get() || NULL == scan_block.get())
        return -1;

    top_block->connect(samp_source, 0, scan_block, 0);
    fs_thread = new std::thread(thread_runner, this);
    started = true;
    return 0;
}

int LTE_fdd_dl_fs_flowgraph::stop()
{
    std::lock_guard<std::mutex> lock(start_mutex);

    if(!started)
        return -1;

    started = false;
    fs_thread->join();
    delete fs_thread;
    top_block.reset();
    return 0;
}

void LTE_fdd_dl_fs_flowgraph::thread_runner(LTE_fdd_dl_fs_flowgraph *fg)
{
    fg->top_block->run();

    fg->top_block->stop();
    fg->top_block->disconnect_all();
    fg->samp_source.reset();
}
