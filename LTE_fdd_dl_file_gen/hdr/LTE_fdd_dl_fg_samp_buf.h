/*******************************************************************************

    Copyright 2012-2014, 2021 Ben Wojtowicz

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

    File: LTE_fdd_dl_fg_samp_buf.h

    Description: Contains all the definitions for the LTE FDD DL File Generator
                 sample buffer block.

    Revision History
    ----------    -------------    --------------------------------------------
    06/15/2012    Ben Wojtowicz    Created file.
    08/19/2012    Ben Wojtowicz    Using the latest liblte library.
    11/10/2012    Ben Wojtowicz    Added SIB2 support and changed the parameter
                                   input method to be "interactive"
    12/26/2012    Ben Wojtowicz    Added SIB3, SIB4, and SIB8 support and fixed
                                   a file size bug
    01/07/2013    Ben Wojtowicz    Moved from automake to cmake
    03/03/2013    Ben Wojtowicz    Added support for a test load.
    07/21/2013    Ben Wojtowicz    Using the latest LTE library.
    08/26/2013    Ben Wojtowicz    Updates to support GnuRadio 3.7.
    09/16/2013    Ben Wojtowicz    Added support for changing the sample rate.
    09/28/2013    Ben Wojtowicz    Added support for setting the sample rate
                                   and output data type.
    06/15/2014    Ben Wojtowicz    Using the latest LTE library.
    02/14/2021    Ben Wojtowicz    Massive reformat and using the new RRC
                                   library.

*******************************************************************************/

#ifndef __LTE_FDD_DL_FG_SAMP_BUF_H__
#define __LTE_FDD_DL_FG_SAMP_BUF_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fg_samp_buf_api.h"
#include "liblte_phy.h"
#include <gnuradio/sync_block.h>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define LTE_FDD_DL_FG_SAMP_BUF_SIZE (LIBLTE_PHY_N_SAMPS_PER_FRAME_30_72MHZ)

/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/

class LTE_fdd_dl_fg_samp_buf;

/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/

typedef boost::shared_ptr<LTE_fdd_dl_fg_samp_buf> LTE_fdd_dl_fg_samp_buf_sptr;

typedef enum{
    LTE_FDD_DL_FG_OUT_SIZE_INT8 = 0,
    LTE_FDD_DL_FG_OUT_SIZE_GR_COMPLEX,
}LTE_FDD_DL_FG_OUT_SIZE_ENUM;

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

LTE_FDD_DL_FG_SAMP_BUF_API LTE_fdd_dl_fg_samp_buf_sptr LTE_fdd_dl_fg_make_samp_buf(size_t out_size_val);
class LTE_FDD_DL_FG_SAMP_BUF_API LTE_fdd_dl_fg_samp_buf : public gr::sync_block
{
public:
    ~LTE_fdd_dl_fg_samp_buf();

    int32 work(int32                      noutput_items,
               gr_vector_const_void_star &input_items,
               gr_vector_void_star       &output_items);

    void set_parameters(MasterInformationBlock *mib_, SystemInformationBlockType1 *sib1_,
                        SystemInformationBlockType2 *sib2_, SystemInformationBlockType3 *sib3_,
                        SystemInformationBlockType4 *sib4_, SystemInformationBlockType8 *sib8_,
                        uint32 *N_frames_, uint32 *N_ant_, uint32 *N_id_cell_,
                        uint32 *percent_load_, uint32 *sib3_present_, uint32 *sib4_present_,
                        uint32 *sib8_present_);

private:
    friend LTE_FDD_DL_FG_SAMP_BUF_API LTE_fdd_dl_fg_samp_buf_sptr LTE_fdd_dl_fg_make_samp_buf(size_t out_size_val);

    LTE_fdd_dl_fg_samp_buf(size_t out_size_val);

    // Input parameters
    LTE_FDD_DL_FG_OUT_SIZE_ENUM out_size;

    // Sample buffer
    complex *samp_buf;
    uint32  samp_buf_idx;
    bool    samples_ready;
    bool    last_samp_was_i;

    // Parameters set externally
    MasterInformationBlock      *mib;
    SystemInformationBlockType1 *sib1;
    SystemInformationBlockType2 *sib2;
    SystemInformationBlockType3 *sib3;
    SystemInformationBlockType4 *sib4;
    SystemInformationBlockType8 *sib8;
    uint32                      *N_frames;
    uint32                      *N_ant;
    uint32                      *N_id_cell;
    uint32                      *percent_load;
    uint32                      *sib3_present;
    uint32                      *sib4_present;
    uint32                      *sib8_present;

    LIBLTE_BIT_MSG_STRUCT                    rrc_msg;
    BCCH_BCH_Message                         bcch_bch;
    BCCH_DL_SCH_Message                      bcch_dlsch;
    LIBLTE_PHY_STRUCT                       *phy_struct;
    LIBLTE_PHY_PCFICH_STRUCT                 pcfich;
    LIBLTE_PHY_PHICH_STRUCT                  phich;
    LIBLTE_PHY_PDCCH_STRUCT                  pdcch;
    LIBLTE_PHY_SUBFRAME_STRUCT               subframe;
    LIBLTE_PHY_FS_ENUM                       fs;
    float                                    phich_res;
    uint32                                   sfn;
    uint32                                   N_id_1;
    uint32                                   N_id_2;
    uint32                                   N_rb_dl;
    uint32                                   si_periodicity_T;
    uint32                                   si_win_len;
    uint32                                   sib_tx_mode;
};

#endif /* __LTE_FDD_DL_FG_SAMP_BUF_H__ */
