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

    File: LTE_fdd_dl_fs_flowgraph.h

    Description: Contains all the definitions for the LTE FDD DL File Scanner
                 gnuradio flowgraph.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

#ifndef __LTE_FDD_DL_FS_FLOWGRAPH_H__
#define __LTE_FDD_DL_FS_FLOWGRAPH_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_fdd_dl_scan_block.h"

#include <gnuradio/top_block.h>
#include <gnuradio/blocks/file_source.h>

#include <mutex>
#include <thread>

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_dl_fs_flowgraph
{
public:
    LTE_fdd_dl_fs_flowgraph();
    ~LTE_fdd_dl_fs_flowgraph();

    bool is_started();
    int start(std::string file_name, liblte_fdd_dl_scan_block_sptr &scan_block, size_t in_size);
    int stop();

private:
    static void thread_runner(LTE_fdd_dl_fs_flowgraph *fg);

    gr::top_block_sptr             top_block;
    gr::blocks::file_source::sptr  samp_source;
    std::mutex                     start_mutex;
    std::thread                   *fs_thread;
    bool                           started;
};

#endif // __LTE_FDD_DL_FS_FLOWGRAPH_H__
