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

    File: LTE_fdd_dl_fg_flowgraph.h

    Description: Contains all the definitions for the LTE FDD DL File Generator
                 gnuradio flowgraph.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

#ifndef __LTE_FDD_DL_FG_FLOWGRAPH_H__
#define __LTE_FDD_DL_FG_FLOWGRAPH_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fg_samp_buf.h"

#include <gnuradio/top_block.h>
#include <gnuradio/blocks/file_sink.h>

#include <mutex>
#include <thread>

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_dl_fg_flowgraph
{
public:
    LTE_fdd_dl_fg_flowgraph();
    ~LTE_fdd_dl_fg_flowgraph();

    bool is_started();
    bool start(std::string file_name, LTE_fdd_dl_fg_samp_buf_sptr &samp_buf, size_t out_size);
    bool stop();

private:
    static void thread_runner(LTE_fdd_dl_fg_flowgraph *fg);

    gr::top_block_sptr           top_block;
    gr::blocks::file_sink::sptr  samp_sink;
    std::mutex                   start_mutex;
    std::thread                 *fg_thread;
    bool                         started;
};

#endif // __LTE_FDD_DL_FG_FLOWGRAPH_H__
