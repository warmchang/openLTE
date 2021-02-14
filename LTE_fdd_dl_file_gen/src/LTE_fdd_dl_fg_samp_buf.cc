/*******************************************************************************

    Copyright 2012-2014, 2017, 2021 Ben Wojtowicz

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

    File: LTE_fdd_dl_fg_samp_buf.cc

    Description: Contains all the implementations for the LTE FDD DL File
                 Generator sample buffer block.

    Revision History
    ----------    -------------    --------------------------------------------
    06/16/2012    Ben Wojtowicz    Created file.
    08/19/2012    Ben Wojtowicz    Using the latest liblte library.
    11/10/2012    Ben Wojtowicz    Added SIB2 support and changed the parameter
                                   input method to be "interactive"
    12/01/2012    Ben Wojtowicz    Using the latest liblte library and added
                                   4 antenna support
    12/26/2012    Ben Wojtowicz    Added SIB3, SIB4, and SIB8 support, fixed a
                                   file size bug, and pulled in a 64 bit bug fix
                                   from Thomas Bertani.
    01/07/2013    Ben Wojtowicz    Moved from automake to cmake
    03/03/2013    Ben Wojtowicz    Added support for a test load and using the
                                   latest libraries.
    07/21/2013    Ben Wojtowicz    Using the latest LTE library.
    08/26/2013    Ben Wojtowicz    Updates to support GnuRadio 3.7 and the
                                   latest LTE library.
    09/16/2013    Ben Wojtowicz    Added support for changing the sample rate.
    09/28/2013    Ben Wojtowicz    Added support for setting the sample rate
                                   and output data type.
    01/18/2014    Ben Wojtowicz    Fixed a bug with transmitting SIB2 for 1.4MHz
                                   bandwidth.
    03/26/2014    Ben Wojtowicz    Using the latest LTE library.
    04/12/2014    Ben Wojtowicz    Using the latest LTE library.
    05/04/2014    Ben Wojtowicz    Added PHICH support.
    11/01/2014    Ben Wojtowicz    Using the latest LTE library.
    07/29/2017    Ben Wojtowicz    Using the latest LTE library.
    02/14/2021    Ben Wojtowicz    Massive reformat and using the new RRC
                                   library.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_dl_fg_samp_buf.h"
#include "liblte_mac.h"
#include <gnuradio/io_signature.h>
#include <errno.h>

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              GLOBAL VARIABLES
*******************************************************************************/

// minimum and maximum number of input and output streams
static const int32 MIN_IN  = 0;
static const int32 MAX_IN  = 0;
static const int32 MIN_OUT = 1;
static const int32 MAX_OUT = 1;

/*******************************************************************************
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

LTE_fdd_dl_fg_samp_buf_sptr LTE_fdd_dl_fg_make_samp_buf(size_t out_size_val)
{
    return LTE_fdd_dl_fg_samp_buf_sptr(new LTE_fdd_dl_fg_samp_buf(out_size_val));
}

LTE_fdd_dl_fg_samp_buf::LTE_fdd_dl_fg_samp_buf(size_t out_size_val)
    : gr::sync_block ("samp_buf",
                      gr::io_signature::make(MIN_IN,  MAX_IN,  sizeof(int8)),
                      gr::io_signature::make(MIN_OUT, MAX_OUT, out_size_val)),
      mib{NULL}, sib1{NULL}, sib2{NULL}, sib3{NULL}, sib4{NULL}, sib8{NULL},
    N_frames{NULL}, N_ant{NULL}, N_id_cell{NULL}, percent_load{NULL}, sib3_present{NULL},
    sib4_present{NULL}, sib8_present{NULL}
{
    // Parse the inputs
    if(out_size_val == sizeof(gr_complex))
    {
        out_size = LTE_FDD_DL_FG_OUT_SIZE_GR_COMPLEX;
    }else if(out_size_val == sizeof(int8)){
        out_size = LTE_FDD_DL_FG_OUT_SIZE_INT8;
    }else{
        out_size = LTE_FDD_DL_FG_OUT_SIZE_INT8;
    }

    // Initialize the LTE parameters
    sfn = 0;
    // PCFICH
    pcfich.cfi = 2;
    // PHICH
    for(uint32 i=0; i<25; i++)
        for(uint32 j=0; j<8; j++)
            phich.present[i][j] = false;

    // Allocate the sample buffer
    samp_buf        = (complex *)malloc(4*LTE_FDD_DL_FG_SAMP_BUF_SIZE*sizeof(complex));
    samp_buf_idx    = 0;
    samples_ready   = false;
    last_samp_was_i = false;
}
LTE_fdd_dl_fg_samp_buf::~LTE_fdd_dl_fg_samp_buf()
{
    // Cleanup the LTE library
    liblte_phy_cleanup(phy_struct);

    // Free the sample buffer
    free(samp_buf);
}

int32 LTE_fdd_dl_fg_samp_buf::work(int32                      noutput_items,
                                   gr_vector_const_void_star &input_items,
                                   gr_vector_void_star       &output_items)
{
    gr_complex *gr_complex_out = (gr_complex *)output_items[0];
    uint32      loop_cnt;
    int8       *int8_out = (int8 *)output_items[0];
    bool        done = false;


    if(false == samples_ready)
    {
        // Generate frame
        if(sfn < *N_frames)
        {
            for(uint32 N_sfr=0; N_sfr<10; N_sfr++)
            {
                // Initialize the output to all zeros
                for(uint32 p=0; p<*N_ant; p++)
                    for(uint32 j=0; j<16; j++)
                        for(uint32 k=0; k<LIBLTE_PHY_N_RB_DL_20MHZ*LIBLTE_PHY_N_SC_RB_DL_NORMAL_CP; k++)
                            subframe.tx_symb[p][j][k] = complex(0, 0);
                subframe.num = N_sfr;

                // PSS and SSS
                if(subframe.num == 0 || subframe.num == 5)
                {
                    liblte_phy_map_pss(phy_struct,
                                       &subframe,
                                       N_id_2,
                                       *N_ant);
                    liblte_phy_map_sss(phy_struct,
                                       &subframe,
                                       N_id_1,
                                       N_id_2,
                                       *N_ant);
                }

                // CRS
                liblte_phy_map_crs(phy_struct,
                                   &subframe,
                                   *N_id_cell,
                                   *N_ant);

                // PBCH
                if(subframe.num == 0)
                {
                    mib->systemFrameNumber_SetValue(sfn/4);
                    bcch_bch.message_Set()->MasterInformationBlock_value_Set(*mib);
                    std::vector<uint8_t> bits;
                    bcch_bch.Pack(bits);
                    rrc_msg.N_bits = bits.size();
                    for(uint32 i=0; i<bits.size(); i++)
                        rrc_msg.msg[i] = bits[i];
                    liblte_phy_bch_channel_encode(phy_struct,
                                                  rrc_msg.msg,
                                                  rrc_msg.N_bits,
                                                  *N_id_cell,
                                                  *N_ant,
                                                  &subframe,
                                                  sfn);
                }

                // PDCCH & PDSCH
                pdcch.N_dl_alloc = 0;
                if(subframe.num == 5 && (sfn % 2) == 0)
                {
                    // SIB1
                    bcch_dlsch.message_Set()->SetChoice(BCCH_DL_SCH_MessageType::k_c1);
                    bcch_dlsch.message_Set()->c1_SetChoice(BCCH_DL_SCH_MessageType::k_c1_systemInformationBlockType1);
                    bcch_dlsch.message_Set()->c1_systemInformationBlockType1_Set(*sib1);
                    std::vector<uint8_t> bits;
                    bcch_dlsch.Pack(bits);
                    pdcch.dl_alloc[pdcch.N_dl_alloc].msg[0].N_bits = bits.size();
                    for(uint32 i=0; i<bits.size(); i++)
                        pdcch.dl_alloc[pdcch.N_dl_alloc].msg[0].msg[i] = bits[i];
                    liblte_phy_get_tbs_mcs_and_n_prb_for_dl(pdcch.dl_alloc[pdcch.N_dl_alloc].msg[0].N_bits,
                                                            subframe.num,
                                                            N_rb_dl,
                                                            LIBLTE_MAC_SI_RNTI,
                                                            &pdcch.dl_alloc[pdcch.N_dl_alloc].tbs,
                                                            &pdcch.dl_alloc[pdcch.N_dl_alloc].mcs,
                                                            &pdcch.dl_alloc[pdcch.N_dl_alloc].N_prb);
                    pdcch.dl_alloc[pdcch.N_dl_alloc].pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
                    pdcch.dl_alloc[pdcch.N_dl_alloc].mod_type       = LIBLTE_PHY_MODULATION_TYPE_QPSK;
                    pdcch.dl_alloc[pdcch.N_dl_alloc].rv_idx         = (uint32)ceilf(1.5 * ((sfn / 2) % 4)) % 4; //36.321 section 5.3.1
                    pdcch.dl_alloc[pdcch.N_dl_alloc].N_codewords    = 1;
                    pdcch.dl_alloc[pdcch.N_dl_alloc].rnti           = LIBLTE_MAC_SI_RNTI;
                    pdcch.dl_alloc[pdcch.N_dl_alloc].tx_mode        = sib_tx_mode;
                    pdcch.N_dl_alloc++;
                }
                if(subframe.num             >=  (0 * si_win_len)%10 &&
                   subframe.num             <   (1 * si_win_len)%10 &&
                   (sfn % si_periodicity_T) == ((0 * si_win_len)/10))
                {
                    // SIs in 1st scheduling info list entry
                    std::vector<SystemInformation_r8_IEs::sib_TypeAndInfo_> sibs;
                    SystemInformation_r8_IEs::sib_TypeAndInfo_ sib;
                    bcch_dlsch.message_Set()->SetChoice(BCCH_DL_SCH_MessageType::k_c1);
                    bcch_dlsch.message_Set()->c1_SetChoice(BCCH_DL_SCH_MessageType::k_c1_systemInformation);
                    bcch_dlsch.message_Set()->c1_systemInformation_Set()->criticalExtensions_SetChoice(SystemInformation::k_criticalExtensions_systemInformation_r8);
                    sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib2);
                    sib.sib_TypeAndInfo_sib2_Set(*sib2);
                    sibs.push_back(sib);
                    if(sib1->schedulingInfoList_Set()->Value()[0].sib_MappingInfo_Set()->Value().size() != 0)
                    {
                        switch(sib1->schedulingInfoList_Set()->Value()[0].sib_MappingInfo_Set()->Value()[0].Value())
                        {
                        case SIB_Type::k_sibType3:
                            sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib3);
                            sib.sib_TypeAndInfo_sib3_Set(*sib3);
                            sibs.push_back(sib);
                            break;
                        case SIB_Type::k_sibType4:
                            sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib4);
                            sib.sib_TypeAndInfo_sib4_Set(*sib4);
                            sibs.push_back(sib);
                            break;
                        case SIB_Type::k_sibType8:
                            sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib8);
                            sib.sib_TypeAndInfo_sib8_Set(*sib8);
                            sibs.push_back(sib);
                            break;
                        default:
                            break;
                        }
                    }
                    bcch_dlsch.message_Set()->c1_systemInformation_Set()->criticalExtensions_systemInformation_r8_Set()->sib_TypeAndInfo_SetValue(sibs);
                    std::vector<uint8_t> bits;
                    bcch_dlsch.Pack(bits);
                    pdcch.dl_alloc[pdcch.N_dl_alloc].msg[0].N_bits = bits.size();
                    for(uint32 i=0; i<bits.size(); i++)
                        pdcch.dl_alloc[pdcch.N_dl_alloc].msg[0].msg[i] = bits[i];

                    // FIXME: This was a hack to allow SIB2 decoding with 1.4MHz BW due to overlap with MIB
                    if(LIBLTE_SUCCESS == liblte_phy_get_tbs_mcs_and_n_prb_for_dl(pdcch.dl_alloc[pdcch.N_dl_alloc].msg[0].N_bits,
                                                                                 subframe.num,
                                                                                 N_rb_dl,
                                                                                 LIBLTE_MAC_SI_RNTI,
                                                                                 &pdcch.dl_alloc[pdcch.N_dl_alloc].tbs,
                                                                                 &pdcch.dl_alloc[pdcch.N_dl_alloc].mcs,
                                                                                 &pdcch.dl_alloc[pdcch.N_dl_alloc].N_prb))
                    {
                        pdcch.dl_alloc[pdcch.N_dl_alloc].pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
                        pdcch.dl_alloc[pdcch.N_dl_alloc].mod_type       = LIBLTE_PHY_MODULATION_TYPE_QPSK;
                        pdcch.dl_alloc[pdcch.N_dl_alloc].rv_idx         = 0; //36.321 section 5.3.1
                        pdcch.dl_alloc[pdcch.N_dl_alloc].N_codewords    = 1;
                        pdcch.dl_alloc[pdcch.N_dl_alloc].rnti           = LIBLTE_MAC_SI_RNTI;
                        pdcch.dl_alloc[pdcch.N_dl_alloc].tx_mode        = sib_tx_mode;
                        pdcch.N_dl_alloc++;
                    }
                }
                for(uint32 j=1; j<sib1->schedulingInfoList_Set()->Value().size(); j++)
                {
                    if(subframe.num             ==  (j * si_win_len)%10 &&
                       (sfn % si_periodicity_T) == ((j * si_win_len)/10))
                    {
                        // SIs in the jth scheduling info list entry
                        std::vector<SystemInformation_r8_IEs::sib_TypeAndInfo_> sibs;
                        SystemInformation_r8_IEs::sib_TypeAndInfo_ sib;
                        bcch_dlsch.message_Set()->SetChoice(BCCH_DL_SCH_MessageType::k_c1);
                        bcch_dlsch.message_Set()->c1_SetChoice(BCCH_DL_SCH_MessageType::k_c1_systemInformation);
                        bcch_dlsch.message_Set()->c1_systemInformation_Set()->criticalExtensions_SetChoice(SystemInformation::k_criticalExtensions_systemInformation_r8);
                        for(uint32 i=0; i<sib1->schedulingInfoList_Set()->Value()[j].sib_MappingInfo_Set()->Value().size(); i++)
                        {
                            switch(sib1->schedulingInfoList_Set()->Value()[j].sib_MappingInfo_Set()->Value()[i].Value())
                            {
                            case SIB_Type::k_sibType3:
                                sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib3);
                                sib.sib_TypeAndInfo_sib3_Set(*sib3);
                                sibs.push_back(sib);
                                break;
                            case SIB_Type::k_sibType4:
                                sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib4);
                                sib.sib_TypeAndInfo_sib4_Set(*sib4);
                                sibs.push_back(sib);
                                break;
                            case SIB_Type::k_sibType8:
                                sib.sib_TypeAndInfo_SetChoice(SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib8);
                                sib.sib_TypeAndInfo_sib8_Set(*sib8);
                                sibs.push_back(sib);
                                break;
                            default:
                                break;
                            }
                        }
                        bcch_dlsch.message_Set()->c1_systemInformation_Set()->criticalExtensions_systemInformation_r8_Set()->sib_TypeAndInfo_SetValue(sibs);
                        if(0 != sibs.size())
                        {
                            std::vector<uint8_t> bits;
                            bcch_dlsch.Pack(bits);
                            pdcch.dl_alloc[pdcch.N_dl_alloc].msg[0].N_bits = bits.size();
                            for(uint32 i=0; i<bits.size(); i++)
                                pdcch.dl_alloc[pdcch.N_dl_alloc].msg[0].msg[i] = bits[i];
                            liblte_phy_get_tbs_mcs_and_n_prb_for_dl(pdcch.dl_alloc[pdcch.N_dl_alloc].msg[0].N_bits,
                                                                    subframe.num,
                                                                    N_rb_dl,
                                                                    LIBLTE_MAC_SI_RNTI,
                                                                    &pdcch.dl_alloc[pdcch.N_dl_alloc].tbs,
                                                                    &pdcch.dl_alloc[pdcch.N_dl_alloc].mcs,
                                                                    &pdcch.dl_alloc[pdcch.N_dl_alloc].N_prb);
                            pdcch.dl_alloc[pdcch.N_dl_alloc].pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
                            pdcch.dl_alloc[pdcch.N_dl_alloc].mod_type       = LIBLTE_PHY_MODULATION_TYPE_QPSK;
                            pdcch.dl_alloc[pdcch.N_dl_alloc].rv_idx         = 0; //36.321 section 5.3.1
                            pdcch.dl_alloc[pdcch.N_dl_alloc].N_codewords    = 1;
                            pdcch.dl_alloc[pdcch.N_dl_alloc].rnti           = LIBLTE_MAC_SI_RNTI;
                            pdcch.dl_alloc[pdcch.N_dl_alloc].tx_mode        = sib_tx_mode;
                            pdcch.N_dl_alloc++;
                        }
                    }
                }
                // Add test load
                if(0 == pdcch.N_dl_alloc)
                {
                    pdcch.dl_alloc[0].msg[0].N_bits = 0;
                    pdcch.dl_alloc[0].N_prb         = 0;
                    uint32 max_N_prb;
                    liblte_phy_get_tbs_mcs_and_n_prb_for_dl(1480,
                                                            subframe.num,
                                                            N_rb_dl,
                                                            LIBLTE_MAC_P_RNTI,
                                                            &pdcch.dl_alloc[0].tbs,
                                                            &pdcch.dl_alloc[0].mcs,
                                                            &max_N_prb);
                    while(pdcch.dl_alloc[0].N_prb < (uint32)((float)(max_N_prb*(*percent_load))/100.0))
                    {
                        pdcch.dl_alloc[0].msg[0].N_bits += 8;
                        liblte_phy_get_tbs_mcs_and_n_prb_for_dl(pdcch.dl_alloc[0].msg[0].N_bits,
                                                                subframe.num,
                                                                N_rb_dl,
                                                                LIBLTE_MAC_P_RNTI,
                                                                &pdcch.dl_alloc[0].tbs,
                                                                &pdcch.dl_alloc[0].mcs,
                                                                &pdcch.dl_alloc[0].N_prb);
                    }
                    for(uint32 i=0; i<pdcch.dl_alloc[0].msg[0].N_bits; i++)
                        pdcch.dl_alloc[0].msg[0].msg[i] = i%2;
                    if(0 != pdcch.dl_alloc[0].N_prb)
                    {
                        pdcch.dl_alloc[0].pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
                        pdcch.dl_alloc[0].mod_type       = LIBLTE_PHY_MODULATION_TYPE_QPSK;
                        pdcch.dl_alloc[0].N_codewords    = 1;
                        pdcch.dl_alloc[0].rnti           = LIBLTE_MAC_P_RNTI;
                        pdcch.dl_alloc[0].tx_mode        = sib_tx_mode;
                        pdcch.N_dl_alloc++;
                    }
                }

                // Schedule all allocations
                // FIXME: Scheduler
                uint32 last_prb = 0;
                for(uint32 i=0; i<pdcch.N_dl_alloc; i++)
                {
                    for(uint32 j=0; j<pdcch.dl_alloc[i].N_prb; j++)
                    {
                        pdcch.dl_alloc[i].prb[0][j] = last_prb;
                        pdcch.dl_alloc[i].prb[1][j] = last_prb++;
                    }
                }
                if(0 != pdcch.N_dl_alloc)
                {
                    liblte_phy_pdcch_channel_encode(phy_struct,
                                                    &pcfich,
                                                    &phich,
                                                    &pdcch,
                                                    *N_id_cell,
                                                    *N_ant,
                                                    phich_res,
                                                    mib->phich_Config_Set()->phich_Duration_Value(),
                                                    &subframe);
                    liblte_phy_pdsch_channel_encode(phy_struct,
                                                    &pdcch,
                                                    *N_id_cell,
                                                    *N_ant,
                                                    &subframe);
                }

                // Construct the output
                for(uint32 p=0; p<*N_ant; p++)
                {
                    liblte_phy_create_dl_subframe(phy_struct,
                                                  &subframe,
                                                  p,
                                                  &samp_buf[(p*phy_struct->N_samps_per_frame) + (subframe.num*phy_struct->N_samps_per_subfr)]);
                }
            }
        }else{
            done = true;
        }
        sfn++;
        samples_ready = true;
    }

    int32 act_noutput_items;
    if(false == done &&
       true  == samples_ready)
    {
        act_noutput_items = 0;
        uint32 out_idx    = 0;
        if(noutput_items > 0)
        {
            if(LTE_FDD_DL_FG_OUT_SIZE_INT8 == out_size)
            {
                // Write out the first half sample if needed
                if(true == last_samp_was_i)
                {
                    float q_samp = 0;
                    for(uint32 p=0; p<*N_ant; p++)
                        q_samp += samp_buf[(p*phy_struct->N_samps_per_frame) + samp_buf_idx].imag();
                    int8_out[out_idx++] = (int8)(q_samp);
                    samp_buf_idx++;
                    act_noutput_items++;
                }

                // Determine how many full samples to write
                if((int32)(phy_struct->N_samps_per_frame - samp_buf_idx) < ((noutput_items - act_noutput_items) / 2))
                {
                    loop_cnt = (phy_struct->N_samps_per_frame - samp_buf_idx)*2;
                }else{
                    loop_cnt = noutput_items - act_noutput_items;
                }

                // Write out the full samples
                for(uint32 i=0; i<loop_cnt/2; i++)
                {
                    complex samp = complex(0, 0);
                    for(uint32 p=0; p<*N_ant; p++)
                        samp += samp_buf[(p*phy_struct->N_samps_per_frame) + samp_buf_idx];

                    int8_out[out_idx++] = (int8)(samp.real());
                    int8_out[out_idx++] = (int8)(samp.imag());
                    samp_buf_idx++;
                    act_noutput_items += 2;
                }

                // Write out the last half sample if needed
                if((noutput_items - act_noutput_items) == 1)
                {
                    float i_samp = 0;
                    for(uint32 p=0; p<*N_ant; p++)
                        i_samp += samp_buf[(p*phy_struct->N_samps_per_frame) + samp_buf_idx].real();
                    int8_out[out_idx++] = (int8)(i_samp);
                    act_noutput_items++;
                    last_samp_was_i = true;
                }else{
                    last_samp_was_i = false;
                }
            }else{ // LTE_FDD_DL_FG_OUT_SIZE_GR_COMPLEX == out_size
                // Determine how many samples to write
                if((int32)(phy_struct->N_samps_per_frame - samp_buf_idx) < noutput_items)
                {
                    loop_cnt = phy_struct->N_samps_per_frame - samp_buf_idx;
                }else{
                    loop_cnt = noutput_items;
                }

                // Write out samples
                for(uint32 i=0; i<loop_cnt; i++)
                {
                    complex samp = complex(0, 0);
                    for(uint32 p=0; p<*N_ant; p++)
                        samp += samp_buf[(p*phy_struct->N_samps_per_frame) + samp_buf_idx];
                    gr_complex_out[out_idx++] = samp;
                    samp_buf_idx++;
                    act_noutput_items++;
                }
            }
        }

        // Check to see if we need more samples
        if(samp_buf_idx >= phy_struct->N_samps_per_frame)
        {
            samples_ready = false;
            samp_buf_idx  = 0;
        }
    }else if(true == done){
        // No more samples to write to file, so mark as done
        act_noutput_items = -1;
    }else{
        // Should never get here
        act_noutput_items = 0;
        samples_ready     = false;
    }

    // Tell runtime system how many input items we consumed
    consume_each(0);

    // Tell runtime system how many output items we produced
    return act_noutput_items;
}

void LTE_fdd_dl_fg_samp_buf::set_parameters(MasterInformationBlock *mib_,
                                            SystemInformationBlockType1 *sib1_,
                                            SystemInformationBlockType2 *sib2_,
                                            SystemInformationBlockType3 *sib3_,
                                            SystemInformationBlockType4 *sib4_,
                                            SystemInformationBlockType8 *sib8_,
                                            uint32 *N_frames_,
                                            uint32 *N_ant_,
                                            uint32 *N_id_cell_,
                                            uint32 *percent_load_,
                                            uint32 *sib3_present_,
                                            uint32 *sib4_present_,
                                            uint32 *sib8_present_)
{
    mib = mib_;
    sib1 = sib1_;
    sib2 = sib2_;
    sib3 = sib3_;
    sib4 = sib4_;
    sib8 = sib8_;
    N_frames = N_frames_;
    N_ant = N_ant_;
    N_id_cell = N_id_cell_;
    percent_load = percent_load_;
    sib3_present = sib3_present_;
    sib4_present = sib4_present_;
    sib8_present = sib8_present_;

    // Derived parameters
    N_id_2 = (*N_id_cell % 3);
    N_id_1 = (*N_id_cell - N_id_2)/3;
    switch(mib->dl_Bandwidth_Value())
    {
    case MasterInformationBlock::k_dl_Bandwidth_n6:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_1_4MHZ;
        fs      = LIBLTE_PHY_FS_1_92MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n15:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_3MHZ;
        fs      = LIBLTE_PHY_FS_3_84MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n25:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_5MHZ;
        fs      = LIBLTE_PHY_FS_7_68MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n50:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_10MHZ;
        fs      = LIBLTE_PHY_FS_15_36MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n75:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_15MHZ;
        fs      = LIBLTE_PHY_FS_15_36MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n100:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_20MHZ;
        fs      = LIBLTE_PHY_FS_30_72MHZ;
        break;
    }
    sib_tx_mode = 1;
    if(*N_ant != 1)
        sib_tx_mode = 2;
    switch(mib->phich_Config_Set()->phich_Resource_Value())
    {
    case PHICH_Config::k_phich_Resource_oneSixth:
        phich_res = 1/6;
        break;
    case PHICH_Config::k_phich_Resource_half:
        phich_res = 0.5;
        break;
    case PHICH_Config::k_phich_Resource_one:
        phich_res = 1;
        break;
    case PHICH_Config::k_phich_Resource_two:
        phich_res = 2;
        break;
    }
    si_periodicity_T = 8;
    switch(sib1->si_WindowLength_Value())
    {
    case SystemInformationBlockType1::k_si_WindowLength_ms1:
        si_win_len = 1;
        break;
    case SystemInformationBlockType1::k_si_WindowLength_ms2:
        si_win_len = 2;
        break;
    case SystemInformationBlockType1::k_si_WindowLength_ms5:
        si_win_len = 5;
        break;
    case SystemInformationBlockType1::k_si_WindowLength_ms10:
        si_win_len = 10;
        break;
    case SystemInformationBlockType1::k_si_WindowLength_ms15:
        si_win_len = 15;
        break;
    case SystemInformationBlockType1::k_si_WindowLength_ms20:
        si_win_len = 20;
        break;
    case SystemInformationBlockType1::k_si_WindowLength_ms40:
        si_win_len = 40;
        break;
    }
    // Determine which SIBs need to be mapped
    uint32 sib_array[3];
    uint32 num_sibs = 0;
    if(1 == *sib3_present)
        sib_array[num_sibs++] = 3;
    if(1 == *sib4_present)
        sib_array[num_sibs++] = 4;
    if(1 == *sib8_present)
        sib_array[num_sibs++] = 8;

    std::vector<SchedulingInfo> sched_info_list;
    for(uint32 i=0; i<num_sibs; i++)
    {
        // Mapping 1 SIB per scheduling opportunity for simplicity
        SIB_Type sib_type;
        if(sib_array[i] == 3)
        {
            sib_type.SetValue(SIB_Type::k_sibType3);
        }else if(sib_array[i] == 4){
            sib_type.SetValue(SIB_Type::k_sibType4);
        }else{ // sib_array[i] == 8
            sib_type.SetValue(SIB_Type::k_sibType8);
        }
        SchedulingInfo sched_info;
        sched_info.si_Periodicity_SetValue(SchedulingInfo::k_si_Periodicity_rf8);
        sched_info.sib_MappingInfo_Set()->SetValue({sib_type});
        sched_info_list.push_back(sched_info);
    }
    if(sched_info_list.size() == 0)
    {
        SchedulingInfo sched_info;
        sched_info.si_Periodicity_SetValue(SchedulingInfo::k_si_Periodicity_rf8);
        sched_info.sib_MappingInfo_Set()->SetValue({});
        sched_info_list.push_back(sched_info);
        sib1->schedulingInfoList_Set()->SetValue(sched_info_list);
    }else{
        sib1->schedulingInfoList_Set()->SetValue(sched_info_list);
    }

    liblte_phy_init(&phy_struct,
                    fs,
                    *N_id_cell,
                    *N_ant,
                    N_rb_dl,
                    LIBLTE_PHY_N_SC_RB_DL_NORMAL_CP,
                    phich_res);
}
