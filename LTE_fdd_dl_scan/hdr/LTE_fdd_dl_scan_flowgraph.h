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

    File: LTE_fdd_dl_scan_flowgraph.h

    Description: Contains all the definitions for the LTE FDD DL Scanner
                 gnuradio flowgraph.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2013    Ben Wojtowicz    Created file
    07/21/2013    Ben Wojtowicz    Added support for HackRF Jawbreaker
    08/26/2013    Ben Wojtowicz    Updates to support GnuRadio 3.7.
    11/13/2013    Ben Wojtowicz    Added support for USRP B2X0.
    11/30/2013    Ben Wojtowicz    Added support for bladeRF.
    04/12/2014    Ben Wojtowicz    Pulled in a patch from Jevgenij for
                                   supporting non-B2X0 USRPs.
    12/16/2014    Ben Wojtowicz    Pulled in a patch from Ruben Merz to add
                                   USRP X300 support.
    03/11/2015    Ben Wojtowicz    Added UmTRX support.
    12/06/2015    Ben Wojtowicz    Changed boost::mutex to pthread_mutex_t.
    02/14/2021    Ben Wojtowicz    Massive reformat.

*******************************************************************************/

#ifndef __LTE_FDD_DL_SCAN_FLOWGRAPH_H__
#define __LTE_FDD_DL_SCAN_FLOWGRAPH_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_fdd_dl_scan_block.h"
#include <gnuradio/top_block.h>
#include <gnuradio/filter/rational_resampler_base.h>
#include <gnuradio/filter/firdes.h>
#include <osmosdr/source.h>
#include <mutex>
#include <thread>

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/

typedef enum{
    LTE_FDD_DL_SCAN_HW_TYPE_RTL_SDR = 0,
    LTE_FDD_DL_SCAN_HW_TYPE_HACKRF,
    LTE_FDD_DL_SCAN_HW_TYPE_USRP_B,
    LTE_FDD_DL_SCAN_HW_TYPE_USRP_N,
    LTE_FDD_DL_SCAN_HW_TYPE_UMTRX,
    LTE_FDD_DL_SCAN_HW_TYPE_USRP_X,
    LTE_FDD_DL_SCAN_HW_TYPE_BLADERF,
    LTE_FDD_DL_SCAN_HW_TYPE_UNKNOWN,
}LTE_FDD_DL_SCAN_HW_TYPE_ENUM;

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_dl_scan_flowgraph
{
public:
    LTE_fdd_dl_scan_flowgraph();
    ~LTE_fdd_dl_scan_flowgraph();

    bool is_started();
    int start(uint16 dl_earfcn, void *iface);
    int stop();
    void update_center_freq(uint16 dl_earfcn);

private:
    void setup_sample_source(LTE_FDD_DL_SCAN_HW_TYPE_ENUM &hw_type);
    static void thread_runner(LTE_fdd_dl_scan_flowgraph *fg);

    std::vector<float>                             resample_taps;
    gr::top_block_sptr                             top_block;
    gr::filter::rational_resampler_base_ccf::sptr  resampler_filter;
    osmosdr::source::sptr                          samp_src;
    liblte_fdd_dl_scan_block_sptr                  scan_block;
    std::thread                                   *scan_thread;
    std::mutex                                     start_mutex;
    bool                                           started;
};

#endif /* __LTE_FDD_DL_SCAN_FLOWGRAPH_H__ */
