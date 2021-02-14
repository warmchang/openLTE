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

    File: LTE_fdd_dl_scan_block.cc

    Description: Contains all the implementations for the LTE FDD DL Scanner
                 block.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2013    Ben Wojtowicz    Created file
    07/21/2013    Ben Wojtowicz    Added support for multiple sample rates and
                                   for decoding SIBs.
    08/26/2013    Ben Wojtowicz    Updates to support GnuRadio 3.7 and the
                                   latest LTE library.
    03/26/2014    Ben Wojtowicz    Using the latest LTE library.
    06/15/2014    Ben Wojtowicz    Added PCAP support.
    03/11/2015    Ben Wojtowicz    Added 7.68MHz support.
    02/14/2021    Ben Wojtowicz    Migrated from
                                   LTE_fdd_dl_scan_state_machine.cc.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_fdd_dl_scan_block.h"
#include "liblte_mac.h"
#include <gnuradio/io_signature.h>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

// Generic defines
#define FREQ_CHANGE_WAIT_NUM_FRAMES              10
#define FREQ_CHANGE_WAIT_NUM_ITERATIONS          10
#define COARSE_TIMING_N_SLOTS                    160
#define COARSE_TIMING_SEARCH_NUM_SUBFRAMES       ((COARSE_TIMING_N_SLOTS/2)+2)
#define PSS_AND_FINE_TIMING_SEARCH_NUM_SUBFRAMES COARSE_TIMING_SEARCH_NUM_SUBFRAMES
#define SSS_SEARCH_NUM_SUBFRAMES                 COARSE_TIMING_SEARCH_NUM_SUBFRAMES
#define BCH_DECODE_NUM_FRAMES                    2
#define PDSCH_DECODE_SIB1_NUM_FRAMES             2
#define PDSCH_DECODE_SI_GENERIC_NUM_FRAMES       1
#define N_TURBO_ITERATIONS                       1
#define MAX_ATTEMPTS                             5
#define MAX_PDSCH_ATTEMPTS                       (20*10)
#define N_TURBO_ITERATIONS                       1

/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              GLOBAL VARIABLES
*******************************************************************************/

// minimum and maximum number of input and output streams
static const int32 MIN_IN  = 1;
static const int32 MAX_IN  = 1;
static const int32 MIN_OUT = 0;
static const int32 MAX_OUT = 0;

/*******************************************************************************
                              CLASS IMPLEMENTATIONS
*******************************************************************************/

liblte_fdd_dl_scan_block_sptr liblte_fdd_dl_scan_block_make(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                                                            liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                                                            liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                                                            liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                                                            liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                                                            liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                                                            liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                                                            size_t                                                      _in_size,
                                                            uint32                                                      N_samp_buf_frames,
                                                            LIBLTE_PHY_FS_ENUM                                          samp_rate)
{
    return liblte_fdd_dl_scan_block_sptr(new liblte_fdd_dl_scan_block(_is_started_cb,
                                                                      _send_pcap_cb,
                                                                      _send_channel_found_begin_cb,
                                                                      _send_sib1_cb,
                                                                      _send_sib_cb,
                                                                      _send_channel_found_end_cb,
                                                                      _send_channel_not_found_cb,
                                                                      _in_size,
                                                                      N_samp_buf_frames,
                                                                      samp_rate));
}

liblte_fdd_dl_scan_block_sptr liblte_fdd_dl_scan_block_make(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                                                            liblte_fdd_dl_scan_block_switch_freq_callback              &_switch_freq_cb,
                                                            liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                                                            liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                                                            liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                                                            liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                                                            liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                                                            liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                                                            size_t                                                      _in_size,
                                                            uint32                                                      N_samp_buf_frames,
                                                            LIBLTE_PHY_FS_ENUM                                          samp_rate)
{
    return liblte_fdd_dl_scan_block_sptr(new liblte_fdd_dl_scan_block(_is_started_cb,
                                                                      _switch_freq_cb,
                                                                      _send_pcap_cb,
                                                                      _send_channel_found_begin_cb,
                                                                      _send_sib1_cb,
                                                                      _send_sib_cb,
                                                                      _send_channel_found_end_cb,
                                                                      _send_channel_not_found_cb,
                                                                      _in_size,
                                                                      N_samp_buf_frames,
                                                                      samp_rate));
}

liblte_fdd_dl_scan_block::liblte_fdd_dl_scan_block(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                                                   liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                                                   liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                                                   liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                                                   liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                                                   liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                                                   liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                                                   size_t                                                      _in_size,
                                                   uint32                                                      N_samp_buf_frames,
                                                   LIBLTE_PHY_FS_ENUM                                          samp_rate)
    : gr::sync_block("liblte_fdd_dl_scan_block",
                     gr::io_signature::make(MAX_IN, MAX_IN, _in_size),
                     gr::io_signature::make(MAX_OUT, MAX_OUT, _in_size)),
      is_started_cb{_is_started_cb}, switch_freq_cb{NULL}, send_pcap_cb{_send_pcap_cb},
      send_channel_found_begin_cb{_send_channel_found_begin_cb}, send_sib1_cb{_send_sib1_cb},
      send_sib_cb{_send_sib_cb}, send_channel_found_end_cb{_send_channel_found_end_cb},
      send_channel_not_found_cb{_send_channel_not_found_cb}, in_size{_in_size}
{
    initialize(N_samp_buf_frames, samp_rate);
}

liblte_fdd_dl_scan_block::liblte_fdd_dl_scan_block(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                                                   liblte_fdd_dl_scan_block_switch_freq_callback              &_switch_freq_cb,
                                                   liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                                                   liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                                                   liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                                                   liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                                                   liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                                                   liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                                                   size_t                                                      _in_size,
                                                   uint32                                                      N_samp_buf_frames,
                                                   LIBLTE_PHY_FS_ENUM                                          samp_rate)
    : gr::sync_block("liblte_fdd_dl_scan_block",
                     gr::io_signature::make(MAX_IN, MAX_IN, _in_size),
                     gr::io_signature::make(MAX_OUT, MAX_OUT, _in_size)),
      is_started_cb{_is_started_cb}, send_pcap_cb{_send_pcap_cb},
      send_channel_found_begin_cb{_send_channel_found_begin_cb},
      send_sib1_cb{_send_sib1_cb}, send_sib_cb{_send_sib_cb},
      send_channel_found_end_cb{_send_channel_found_end_cb},
      send_channel_not_found_cb{_send_channel_not_found_cb}, in_size{_in_size}
{
    switch_freq_cb = new liblte_fdd_dl_scan_block_switch_freq_callback(_switch_freq_cb);
    initialize(N_samp_buf_frames, samp_rate);
}

void liblte_fdd_dl_scan_block::initialize(uint32             N_samp_buf_frames,
                                          LIBLTE_PHY_FS_ENUM samp_rate)
{
    uint32 N_rb_dl = LIBLTE_PHY_N_RB_DL_20MHZ;
    switch(samp_rate)
    {
    case LIBLTE_PHY_FS_1_92MHZ:
        N_rb_dl       = LIBLTE_PHY_N_RB_DL_1_4MHZ;
        samp_buf_size = N_samp_buf_frames * LIBLTE_PHY_N_SAMPS_PER_FRAME_1_92MHZ;
        break;
    case LIBLTE_PHY_FS_3_84MHZ:
        N_rb_dl       = LIBLTE_PHY_N_RB_DL_3MHZ;
        samp_buf_size = N_samp_buf_frames * LIBLTE_PHY_N_SAMPS_PER_FRAME_3_84MHZ;
        break;
    case LIBLTE_PHY_FS_7_68MHZ:
        N_rb_dl       = LIBLTE_PHY_N_RB_DL_5MHZ;
        samp_buf_size = N_samp_buf_frames * LIBLTE_PHY_N_SAMPS_PER_FRAME_7_68MHZ;
        break;
    case LIBLTE_PHY_FS_15_36MHZ:
        N_rb_dl       = LIBLTE_PHY_N_RB_DL_10MHZ;
        samp_buf_size = N_samp_buf_frames * LIBLTE_PHY_N_SAMPS_PER_FRAME_15_36MHZ;
        break;
    case LIBLTE_PHY_FS_30_72MHZ:
    default:
        N_rb_dl       = LIBLTE_PHY_N_RB_DL_20MHZ;
        samp_buf_size = N_samp_buf_frames * LIBLTE_PHY_N_SAMPS_PER_FRAME_30_72MHZ;
        break;
    }
    liblte_phy_init(&phy_struct,
                    samp_rate,
                    LIBLTE_PHY_INIT_N_ID_CELL_UNKNOWN,
                    4,
                    N_rb_dl,
                    LIBLTE_PHY_N_SC_RB_DL_NORMAL_CP,
                    1);

    // Initialize the sample buffer
    samp_buf = (complex *)malloc(samp_buf_size * sizeof(complex));
    samp_buf_w_idx  = 0;
    samp_buf_r_idx  = 0;
    last_samp_was_i = false;

    // Variables
    change_freq_init();
    send_cnf = true;
    corr_peak_idx = 0;
    for(uint32 i=0; i<LIBLTE_PHY_N_MAX_ROUGH_CORR_SEARCH_PEAKS; i++)
        timing_struct.freq_offset[i] = 0;
}

liblte_fdd_dl_scan_block::~liblte_fdd_dl_scan_block()
{
    // Cleanup the LTE library
    liblte_phy_cleanup(phy_struct);

    // Free the sample buffer
    free(samp_buf);
}

int32 liblte_fdd_dl_scan_block::work(int32                      ninput_items,
                                     gr_vector_const_void_star &input_items,
                                     gr_vector_void_star       &output_items)
{
    bool switch_freq     = false;
    bool process_samples = false;
    bool copy_input      = false;
    if(sizeof(int8) == in_size)
    {
        if(samp_buf_w_idx < (uint32)(samp_buf_size - ((ninput_items+1)/2)))
        {
            copy_input_to_samp_buf(input_items, ninput_items);

            // Check if buffer is full enough
            if(samp_buf_w_idx >= (uint32)(samp_buf_size - ((ninput_items+1)/2)))
            {
                process_samples = true;
                copy_input      = false;
            }
        }else{
            // Buffer is too full process samples, then copy
            process_samples = true;
            copy_input      = true;
        }
    }else{ // gr_complex
        if(samp_buf_w_idx < (uint32)(samp_buf_size - (ninput_items+1)))
        {
            copy_input_to_samp_buf(input_items, ninput_items);

            // Check if buffer is full enough
            if(samp_buf_w_idx >= (uint32)(samp_buf_size - (ninput_items+1)))
            {
                process_samples = true;
                copy_input      = false;
            }
        }else{
            // Buffer is too full process samples, then copy
            process_samples = true;
            copy_input      = true;
        }
    }

    int32 done_flag = 0;
    if(process_samples)
    {
        freq_shift(0, samp_buf_size, timing_struct.freq_offset[corr_peak_idx]);

        switch(state)
        {
        case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_FREQ_CHANGE_WAIT:
            N_samps_needed = phy_struct->N_samps_per_frame * FREQ_CHANGE_WAIT_NUM_FRAMES;
            break;
        case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH:
            N_samps_needed = phy_struct->N_samps_per_subfr * COARSE_TIMING_SEARCH_NUM_SUBFRAMES;
            break;
        case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PSS_AND_FINE_TIMING_SEARCH:
            N_samps_needed = phy_struct->N_samps_per_subfr * PSS_AND_FINE_TIMING_SEARCH_NUM_SUBFRAMES;
            break;
        case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_SSS_SEARCH:
            N_samps_needed = phy_struct->N_samps_per_subfr * SSS_SEARCH_NUM_SUBFRAMES;
            break;
        case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_BCH_DECODE:
            N_samps_needed = phy_struct->N_samps_per_frame * BCH_DECODE_NUM_FRAMES;
            break;
        case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PDSCH_DECODE_SIB1:
            N_samps_needed = phy_struct->N_samps_per_frame * PDSCH_DECODE_SIB1_NUM_FRAMES;
            break;
        case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PDSCH_DECODE_SI_GENERIC:
            N_samps_needed = phy_struct->N_samps_per_frame * PDSCH_DECODE_SI_GENERIC_NUM_FRAMES;
            break;
        }

        float pss_thresh;
        while(samp_buf_r_idx < (samp_buf_w_idx - N_samps_needed) &&
              samp_buf_w_idx != 0)
        {
            // reinit?

            switch(state)
            {
            case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_FREQ_CHANGE_WAIT:
                do_freq_change_wait();
                break;
            case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH:
                do_coarse_timing_search(switch_freq, done_flag);
                break;
            case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PSS_AND_FINE_TIMING_SEARCH:
                printf("PSS\n");
                do_pss_and_fine_timing_search(pss_thresh, switch_freq, done_flag);
                break;
            case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_SSS_SEARCH:
                printf("SSS\n");
                do_sss_search(pss_thresh, switch_freq, done_flag);
                break;
            case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_BCH_DECODE:
                printf("BCH %u\n", N_id_cell);
                do_bch_decode(switch_freq, done_flag);
                break;
            case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PDSCH_DECODE_SIB1:
                printf("SIB1\n");
                do_pdsch_decode_sib1(switch_freq, done_flag);
                break;
            case LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PDSCH_DECODE_SI_GENERIC:
                do_pdsch_decode_si_generic(switch_freq, done_flag);
                break;
            }

            if(switch_freq)
            {
                samp_buf_w_idx = 0;
                samp_buf_r_idx = 0;
                change_freq_init();
                corr_peak_idx = 0;
                for(uint32 i=0; i<LIBLTE_PHY_N_MAX_ROUGH_CORR_SEARCH_PEAKS; i++)
                    timing_struct.freq_offset[i] = 0;
                break;
            }

            if(-1 == done_flag)
                break;
        }

        // Copy remaining samples to beginning of buffer
        if(samp_buf_r_idx > 100)
        {
            samp_buf_r_idx       -= 100;
            uint32 samps_to_copy = 0;
            if(samp_buf_w_idx > samp_buf_r_idx)
                samps_to_copy  = samp_buf_w_idx - samp_buf_r_idx;
            samp_buf_w_idx = 0;
            freq_shift(samp_buf_r_idx,
                       samps_to_copy,
                       -timing_struct.freq_offset[corr_peak_idx]);
            for(uint32 i=0; i<samps_to_copy; i++)
                samp_buf[samp_buf_w_idx++] = samp_buf[samp_buf_r_idx++];
            samp_buf_r_idx = 100;
        }

        if(true == copy_input)
            copy_input_to_samp_buf(input_items, ninput_items);
    }

    if(!is_started_cb())
        done_flag = -1;

    // Tell runtime system how many input items we consumed
    consume_each(ninput_items);

    // Tell runtime system how many output items we produced.
    return done_flag;
}

void liblte_fdd_dl_scan_block::change_freq_init(void)
{
    state = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH;
    if(switch_freq_cb != NULL)
    {
        state                    = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_FREQ_CHANGE_WAIT;
        N_freq_change_iterations = 0;
    }
    decoded_chans.clear();
    expected_sibs.clear();
    received_sibs.clear();
    phich_res        = 0;
    sfn              = 0;
    N_sfr            = 0;
    N_ant            = 0;
    N_id_cell        = 0;
    N_id_2           = 0;
    N_attempts       = 0;
    N_bch_attempts   = 0;
    N_pdsch_attempts = 0;
    sib1_sent        = false;
}

void liblte_fdd_dl_scan_block::do_freq_change_wait()
{
    if(N_freq_change_iterations++ < FREQ_CHANGE_WAIT_NUM_ITERATIONS)
    {
        samp_buf_r_idx += N_samps_needed;
        return;
    }

    // Move to coarse timing search
    state          = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH;
    N_samps_needed = phy_struct->N_samps_per_subfr * COARSE_TIMING_SEARCH_NUM_SUBFRAMES;
}

void liblte_fdd_dl_scan_block::do_coarse_timing_search(bool &switch_freq,
                                                       int32 &done_flag)
{
    if(LIBLTE_SUCCESS == liblte_phy_dl_find_coarse_timing_and_freq_offset(phy_struct,
                                                                          samp_buf,
                                                                          COARSE_TIMING_N_SLOTS,
                                                                          &timing_struct))
    {
        if(corr_peak_idx >= timing_struct.n_corr_peaks)
            return channel_not_found(switch_freq, done_flag);

        // Search for PSS and fine timing
        state          = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PSS_AND_FINE_TIMING_SEARCH;
        N_samps_needed = phy_struct->N_samps_per_subfr * PSS_AND_FINE_TIMING_SEARCH_NUM_SUBFRAMES;

        // Correct frequency error
        return freq_shift(0, samp_buf_size, timing_struct.freq_offset[corr_peak_idx]);
    }

    // Stay in coarse timing search
    samp_buf_r_idx += N_samps_needed;
    if(N_attempts++ > MAX_ATTEMPTS)
        channel_not_found(switch_freq, done_flag);
}

void liblte_fdd_dl_scan_block::do_pss_and_fine_timing_search(float &pss_thresh,
                                                             bool  &switch_freq,
                                                             int32 &done_flag)
{
    float  freq_offset_local;
    uint32 pss_symb;
    if(LIBLTE_SUCCESS == liblte_phy_find_pss_and_fine_timing(phy_struct,
                                                             samp_buf,
                                                             timing_struct.symb_starts[corr_peak_idx],
                                                             &N_id_2,
                                                             &pss_symb,
                                                             &pss_thresh,
                                                             &freq_offset_local))
    {
        if(fabs(freq_offset_local) > 100)
        {
            freq_shift(0, samp_buf_size, freq_offset_local);
            timing_struct.freq_offset[corr_peak_idx] += freq_offset_local;
        }

        // Search for SSS
        state          = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_SSS_SEARCH;
        N_samps_needed = phy_struct->N_samps_per_subfr * SSS_SEARCH_NUM_SUBFRAMES;
        return;
    }

    // Go back to coarse timing search
    state           = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH;
    N_samps_needed  = phy_struct->N_samps_per_subfr * COARSE_TIMING_SEARCH_NUM_SUBFRAMES;
    samp_buf_r_idx += N_samps_needed;
    if(N_attempts++ > MAX_ATTEMPTS)
        channel_not_found(switch_freq, done_flag);
}

void liblte_fdd_dl_scan_block::do_sss_search(float pss_thresh, bool &switch_freq,
                                             int32 &done_flag)
{
    uint32 N_id_1;
    uint32 frame_start_idx;
    if(LIBLTE_SUCCESS == liblte_phy_find_sss(phy_struct,
                                             samp_buf,
                                             N_id_2,
                                             timing_struct.symb_starts[corr_peak_idx],
                                             pss_thresh,
                                             &N_id_1,
                                             &frame_start_idx))
    {
        N_id_cell = 3*N_id_1 + N_id_2;

        for(auto pci : decoded_chans)
        {
            if(N_id_cell == pci)
            {
                // Go back to coarse timing search
                state = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH;
                corr_peak_idx++;
                return change_freq_init();
            }
        }

        // Decode BCH
        state = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_BCH_DECODE;
        while(frame_start_idx < samp_buf_r_idx)
            frame_start_idx += phy_struct->N_samps_per_frame;
        samp_buf_r_idx = frame_start_idx;
        N_samps_needed = phy_struct->N_samps_per_frame * BCH_DECODE_NUM_FRAMES;
        return;
    }

    // Go back to coarse timing search
    state           = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH;
    N_samps_needed  = phy_struct->N_samps_per_subfr * COARSE_TIMING_SEARCH_NUM_SUBFRAMES;
    samp_buf_r_idx += N_samps_needed;
    if(N_attempts++ > MAX_ATTEMPTS)
        channel_not_found(switch_freq, done_flag);
}

void liblte_fdd_dl_scan_block::do_bch_decode(bool &switch_freq, int32 &done_flag)
{
    LIBLTE_PHY_SUBFRAME_STRUCT subframe;
    uint32                     N_rb_dl = LIBLTE_PHY_N_RB_DL_20MHZ;
    uint8                      sfn_offset;
//    for(uint32 i=0; i<15360; i++)
//        printf("(%f,%f) ", samp_buf[samp_buf_r_idx+i].real(), samp_buf[samp_buf_r_idx+i].imag());
//    printf("\n");
    if(!(LIBLTE_SUCCESS == liblte_phy_get_dl_subframe_and_ce(phy_struct,
                                                             samp_buf,
                                                             samp_buf_r_idx,
                                                             0,
                                                             N_id_cell,
                                                             4,
                                                             &subframe) &&
         LIBLTE_SUCCESS == liblte_phy_bch_channel_decode(phy_struct,
                                                         &subframe,
                                                         N_id_cell,
                                                         &N_ant,
                                                         rrc_msg.msg,
                                                         &rrc_msg.N_bits,
                                                         &sfn_offset)))
    {
        // Try next MIB
        state           = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_BCH_DECODE;
        samp_buf_r_idx += phy_struct->N_samps_per_frame;
        N_samps_needed  = phy_struct->N_samps_per_frame * BCH_DECODE_NUM_FRAMES;
        if(N_bch_attempts++ > MAX_ATTEMPTS)
        {
            // Go back to coarse timing
            state           = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH;
            N_samps_needed  = phy_struct->N_samps_per_subfr * COARSE_TIMING_SEARCH_NUM_SUBFRAMES;
            samp_buf_r_idx += N_samps_needed;
            if(N_attempts++ > MAX_ATTEMPTS)
                channel_not_found(switch_freq, done_flag);
        }
        return;
    }

    std::vector<uint8_t> bits;
    for(uint32 i=0; i<rrc_msg.N_bits; i++)
        bits.push_back(rrc_msg.msg[i]);
    bcch_bch.Unpack(bits);
    phich_dur = bcch_bch.message_Get().MasterInformationBlock_value_Get().phich_Config_Get().phich_Duration_Value();
    switch(bcch_bch.message_Get().MasterInformationBlock_value_Get().dl_Bandwidth_Value())
    {
    case MasterInformationBlock::k_dl_Bandwidth_n6:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_1_4MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n15:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_3MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n25:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_5MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n50:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_10MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n75:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_15MHZ;
        break;
    case MasterInformationBlock::k_dl_Bandwidth_n100:
        N_rb_dl = LIBLTE_PHY_N_RB_DL_20MHZ;
        break;
    default:
        break;
    }
    liblte_phy_update_n_rb_dl(phy_struct, N_rb_dl);
    sfn = (bcch_bch.message_Get().MasterInformationBlock_value_Get().systemFrameNumber_Value() << 2) + sfn_offset;
    switch(bcch_bch.message_Get().MasterInformationBlock_value_Get().phich_Config_Get().phich_Resource_Value())
    {
    case PHICH_Config::k_phich_Resource_oneSixth:
        phich_res = 1/6;
        break;
    case PHICH_Config::k_phich_Resource_half:
        phich_res = 1/2;
        break;
    case PHICH_Config::k_phich_Resource_one:
        phich_res = 1;
        break;
    case PHICH_Config::k_phich_Resource_two:
        phich_res = 2;
        break;
    }

    // Send a PCAP message
    send_pcap_cb(0xFFFFFFFF, sfn*10 + subframe.num, rrc_msg);

    // Send channel found start and mib decoded messages
    freq_offset = timing_struct.freq_offset[corr_peak_idx];
    send_channel_found_begin_cb(freq_offset, N_id_cell,
                                bcch_bch.message_Get().MasterInformationBlock_value_Get(),
                                sfn, N_ant);

    // Add this channel to the list of decoded channels
    decoded_chans.push_back(N_id_cell);
    if(LIBLTE_FDD_DL_SCAN_BLOCK_N_DECODED_CHANS_MAX == decoded_chans.size())
        channel_not_found(switch_freq, done_flag);

    // Decode PDSCH for SIB1
    state = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PDSCH_DECODE_SIB1;
    if((sfn % 2) != 0)
    {
        samp_buf_r_idx += phy_struct->N_samps_per_frame;
        sfn++;
    }
    N_samps_needed = phy_struct->N_samps_per_frame * PDSCH_DECODE_SIB1_NUM_FRAMES;
}

void liblte_fdd_dl_scan_block::do_pdsch_decode_sib1(bool &switch_freq, int32 &done_flag)
{
    LIBLTE_PHY_SUBFRAME_STRUCT subframe;
    LIBLTE_PHY_PCFICH_STRUCT   pcfich;
    LIBLTE_PHY_PHICH_STRUCT    phich;
    LIBLTE_PHY_PDCCH_STRUCT    pdcch;
    if(!(LIBLTE_SUCCESS == liblte_phy_get_dl_subframe_and_ce(phy_struct,
                                                             samp_buf,
                                                             samp_buf_r_idx,
                                                             5,
                                                             N_id_cell,
                                                             N_ant,
                                                             &subframe) &&
         LIBLTE_SUCCESS == liblte_phy_pdcch_channel_decode(phy_struct,
                                                           &subframe,
                                                           N_id_cell,
                                                           N_ant,
                                                           phich_res,
                                                           phich_dur,
                                                           &pcfich,
                                                           &phich,
                                                           &pdcch) &&
         LIBLTE_SUCCESS == liblte_phy_pdsch_channel_decode(phy_struct,
                                                           &subframe,
                                                           &pdcch.dl_alloc[0],
                                                           pdcch.N_symbs,
                                                           N_id_cell,
                                                           N_ant,
                                                           N_TURBO_ITERATIONS,
                                                           rrc_msg.msg,
                                                           &rrc_msg.N_bits)))
    {
        // Try to decode SIB1 again
        N_samps_needed  = phy_struct->N_samps_per_frame * PDSCH_DECODE_SIB1_NUM_FRAMES;
        samp_buf_r_idx += N_samps_needed;
        sfn            += PDSCH_DECODE_SIB1_NUM_FRAMES;

        // Determine if PDSCH search is done
        if(N_pdsch_attempts++ >= MAX_PDSCH_ATTEMPTS)
            channel_found(switch_freq, done_flag);
    }

    // Send a PCAP message
    send_pcap_cb(pdcch.dl_alloc[0].rnti, sfn*10 + subframe.num, rrc_msg);

    std::vector<uint8_t> bits;
    for(uint32 i=0; i<rrc_msg.N_bits; i++)
        bits.push_back(rrc_msg.msg[i]);
    bcch_dlsch.Unpack(bits);
    if(bcch_dlsch.message_Get().Choice() == BCCH_DL_SCH_MessageType::k_c1 &&
       bcch_dlsch.message_Get().c1_Choice() == BCCH_DL_SCH_MessageType::k_c1_systemInformationBlockType1)
        send_sib1();

    // Decode all PDSCHs
    state          = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PDSCH_DECODE_SI_GENERIC;
    N_sfr          = 0;
    N_samps_needed = phy_struct->N_samps_per_frame * PDSCH_DECODE_SI_GENERIC_NUM_FRAMES;

    // Determine if PDSCH search is done
    if(N_pdsch_attempts++ >= MAX_PDSCH_ATTEMPTS)
        channel_found(switch_freq, done_flag);
}

void liblte_fdd_dl_scan_block::do_pdsch_decode_si_generic(bool  &switch_freq,
                                                          int32 &done_flag)
{
    LIBLTE_PHY_SUBFRAME_STRUCT subframe;
    LIBLTE_PHY_PCFICH_STRUCT   pcfich;
    LIBLTE_PHY_PHICH_STRUCT    phich;
    LIBLTE_PHY_PDCCH_STRUCT    pdcch;
    if(LIBLTE_SUCCESS == liblte_phy_get_dl_subframe_and_ce(phy_struct,
                                                           samp_buf,
                                                           samp_buf_r_idx,
                                                           N_sfr,
                                                           N_id_cell,
                                                           N_ant,
                                                           &subframe) &&
       LIBLTE_SUCCESS == liblte_phy_pdcch_channel_decode(phy_struct,
                                                         &subframe,
                                                         N_id_cell,
                                                         N_ant,
                                                         phich_res,
                                                         phich_dur,
                                                         &pcfich,
                                                         &phich,
                                                         &pdcch) &&
       LIBLTE_SUCCESS == liblte_phy_pdsch_channel_decode(phy_struct,
                                                         &subframe,
                                                         &pdcch.dl_alloc[0],
                                                         pdcch.N_symbs,
                                                         N_id_cell,
                                                         N_ant,
                                                         N_TURBO_ITERATIONS,
                                                         rrc_msg.msg,
                                                         &rrc_msg.N_bits))
    {
        // Send a PCAP message
        send_pcap_cb(pdcch.dl_alloc[0].rnti, sfn*10 + subframe.num, rrc_msg);
        
        std::vector<uint8_t> bits;
        for(uint32 i=0; i<rrc_msg.N_bits; i++)
            bits.push_back(rrc_msg.msg[i]);
        if(LIBLTE_MAC_SI_RNTI == pdcch.dl_alloc[0].rnti)
        {
            bcch_dlsch.Unpack(bits);
            if(bcch_dlsch.message_Get().Choice() == BCCH_DL_SCH_MessageType::k_c1 &&
               bcch_dlsch.message_Get().c1_Choice() == BCCH_DL_SCH_MessageType::k_c1_systemInformationBlockType1)
            {
                send_sib1();
            }else if(bcch_dlsch.message_Get().Choice() == BCCH_DL_SCH_MessageType::k_c1 &&
                     bcch_dlsch.message_Get().c1_Choice() == BCCH_DL_SCH_MessageType::k_c1_systemInformation &&
                     bcch_dlsch.message_Get().c1_systemInformation_Get().criticalExtensions_Choice() == SystemInformation::k_criticalExtensions_systemInformation_r8){
                send_sib(switch_freq, done_flag);
            }else{
                printf("Invalid BCCH_DL_SCH_Message received\n");
            }
        }else if(LIBLTE_MAC_P_RNTI == pdcch.dl_alloc[0].rnti){
            uint32 i;
            for(i=0; i<16; i++)
                if(bits[i] != i%2)
                    break;
            if(i == 16)
                printf("TEST FILL RECEIVED\n");
        }
    }

    // Determine if PDSCH search is done
    if(N_pdsch_attempts++ >= MAX_PDSCH_ATTEMPTS)
        return channel_found(switch_freq, done_flag);

    state          = LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PDSCH_DECODE_SI_GENERIC;
    N_samps_needed = phy_struct->N_samps_per_frame * PDSCH_DECODE_SI_GENERIC_NUM_FRAMES;
    N_sfr++;
    if(N_sfr >= 10)
    {
        N_sfr = 0;
        sfn++;
        samp_buf_r_idx += N_samps_needed;
    }
}

void liblte_fdd_dl_scan_block::copy_input_to_samp_buf(gr_vector_const_void_star &input_items,
                                                      int32                      ninput_items)
{
    if(sizeof(gr_complex) == in_size)
    {
        const gr_complex *gr_complex_in = (gr_complex *)input_items[0];
        for(int32 i=0; i<ninput_items; i++)
            samp_buf[samp_buf_w_idx++] = gr_complex_in[i];
        return;
    }

    // in_size = int8
    uint32      offset  = 0;
    const int8 *int8_in = (int8 *)input_items[0];
    if(true == last_samp_was_i)
    {
        samp_buf[samp_buf_w_idx] = complex(samp_buf[samp_buf_w_idx].real(), int8_in[0]);
        samp_buf_w_idx++;
        offset = 1;
    }
    for(uint32 i=0; i<(ninput_items-offset)/2; i++)
        samp_buf[samp_buf_w_idx++] = complex(int8_in[i*2+offset], int8_in[i*2+offset+1]);
    if(((ninput_items-offset) % 2) != 0)
    {
        samp_buf[samp_buf_w_idx] = complex(int8_in[ninput_items-1], 0);
        last_samp_was_i          = true;
    }else{
        last_samp_was_i = false;
    }
}

void liblte_fdd_dl_scan_block::freq_shift(uint32 start_idx, uint32 num_samps,
                                          float freq_offset)
{
    if(state == LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH)
        return;
    for(uint32 i=start_idx; i<(start_idx+num_samps); i++)
        samp_buf[i] = samp_buf[i] *
            std::conj(std::polar<float>(1, (i+1)*freq_offset*2*M_PI/phy_struct->fs));
}

void liblte_fdd_dl_scan_block::channel_found(bool  &switch_freq,
                                             int32 &done_flag)
{
    // Send the channel information
    send_channel_found_end_cb(freq_offset, N_id_cell);

    // Initialize for the next channel
    change_freq_init();

    // Determine if a frequency change is needed
    corr_peak_idx++;
    if(corr_peak_idx >= timing_struct.n_corr_peaks)
    {
        // Change frequency
        corr_peak_idx = 0;
        if(0 == (*switch_freq_cb)())
        {
            switch_freq = true;
            send_cnf    = true;
        }else{
            done_flag = -1;
        }
    }else{
        send_cnf = false;
    }
}

void liblte_fdd_dl_scan_block::channel_not_found(bool  &switch_freq,
                                                 int32 &done_flag)
{
    if(send_cnf)
        send_channel_not_found_cb();

    // Initialize for the next channel
    change_freq_init();

    // Change frequency
    if(switch_freq_cb != NULL)
    {
        corr_peak_idx = 0;
        if(0 == (*switch_freq_cb)())
        {
            switch_freq = true;
            send_cnf    = true;
        }else{
            done_flag = -1;
        }
    }
}

void liblte_fdd_dl_scan_block::send_sib1()
{
    if(sib1_sent)
        return;

    for(auto sched_info : bcch_dlsch.message_Get().c1_systemInformationBlockType1_Get().schedulingInfoList_Get().Value())
        for(auto sib_type : sched_info.sib_MappingInfo_Get().Value())
            expected_sibs.push_back(sib_type);

    send_sib1_cb(freq_offset, N_id_cell,
                 bcch_dlsch.message_Get().c1_systemInformationBlockType1_Get(),
                 sfn);
    sib1_sent = true;
}

void liblte_fdd_dl_scan_block::send_sib(bool &switch_freq, int32 &done_flag)
{
    if(received_sibs.size() == 0)
    {
        send_sib_cb(freq_offset, N_id_cell,
                    bcch_dlsch.message_Get().c1_systemInformation_Get().criticalExtensions_systemInformation_r8_Get(),
                    sfn);
        for(auto sib : bcch_dlsch.message_Get().c1_systemInformation_Get().criticalExtensions_systemInformation_r8_Get().sib_TypeAndInfo_Value())
            received_sibs.push_back(sib.sib_TypeAndInfo_Choice());
        return check_if_all_sibs_received(switch_freq, done_flag);
    }
    for(auto sib_type : received_sibs)
    {
        if(bcch_dlsch.message_Get().c1_systemInformation_Get().criticalExtensions_systemInformation_r8_Get().sib_TypeAndInfo_Value()[0].sib_TypeAndInfo_Choice() != sib_type)
        {
            send_sib_cb(freq_offset, N_id_cell,
                        bcch_dlsch.message_Get().c1_systemInformation_Get().criticalExtensions_systemInformation_r8_Get(),
                        sfn);
        }
    }
    for(auto sib : bcch_dlsch.message_Get().c1_systemInformation_Get().criticalExtensions_systemInformation_r8_Get().sib_TypeAndInfo_Value())
        received_sibs.push_back(sib.sib_TypeAndInfo_Choice());
    check_if_all_sibs_received(switch_freq, done_flag);
}

void liblte_fdd_dl_scan_block::check_if_all_sibs_received(bool &switch_freq, int32 &done_flag)
{
    bool sib2_received = false;
    for(auto sib_type : received_sibs)
        if(sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib2)
            sib2_received = true;
    if(!sib2_received)
        return;

    for(auto expected_sib_type : expected_sibs)
    {
        bool sib_received = false;

        for(auto received_sib_type : received_sibs)
        {
            if(expected_sib_type.Value() == SIB_Type::k_sibType3 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib3)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType4 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib4)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType5 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib5)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType6 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib6)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType7 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib7)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType8 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib8)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType9 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib9)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType10 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib10)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType11 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib11)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType12_v920 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib12_v920)
            {
                sib_received = true;
                break;
            }
            if(expected_sib_type.Value() == SIB_Type::k_sibType13_v920 &&
               received_sib_type == SystemInformation_r8_IEs::sib_TypeAndInfo_::k_sib_TypeAndInfo_sib13_v920)
            {
                sib_received = true;
                break;
            }
        }

        if(!sib_received)
            return;
    }

    channel_found(switch_freq, done_flag);
}
