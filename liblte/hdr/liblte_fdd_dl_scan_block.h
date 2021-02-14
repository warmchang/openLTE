/*******************************************************************************

    Copyright 2013-2014, 2021 Ben Wojtowicz

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

    File: LTE_fdd_dl_scan_block.h

    Description: Contains all the definitions for the LTE FDD DL Scanner
                 block.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2013    Ben Wojtowicz    Created file
    07/21/2013    Ben Wojtowicz    Added support for multiple sample rates
    08/26/2013    Ben Wojtowicz    Updates to support GnuRadio 3.7.
    06/15/2014    Ben Wojtowicz    Using the latest LTE library.
    02/14/2021    Ben Wojtowicz    Migrated from
                                   LTE_fdd_dl_scan_state_machine.cc.

*******************************************************************************/

#ifndef __LIBLTE_FDD_DL_SCAN_BLOCK_H__
#define __LIBLTE_FDD_DL_SCAN_BLOCK_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_fdd_dl_scan_block_api.h"
#include "liblte_phy.h"
#include <gnuradio/sync_block.h>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define LIBLTE_FDD_DL_SCAN_BLOCK_N_DECODED_CHANS_MAX 10

/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/

class liblte_fdd_dl_scan_block;

/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/

typedef boost::shared_ptr<liblte_fdd_dl_scan_block> liblte_fdd_dl_scan_block_sptr;

typedef enum{
    LIBLTE_FDD_DL_SCAN_BLOCK_STATE_FREQ_CHANGE_WAIT = 0,
    LIBLTE_FDD_DL_SCAN_BLOCK_STATE_COARSE_TIMING_SEARCH,
    LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PSS_AND_FINE_TIMING_SEARCH,
    LIBLTE_FDD_DL_SCAN_BLOCK_STATE_SSS_SEARCH,
    LIBLTE_FDD_DL_SCAN_BLOCK_STATE_BCH_DECODE,
    LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PDSCH_DECODE_SIB1,
    LIBLTE_FDD_DL_SCAN_BLOCK_STATE_PDSCH_DECODE_SI_GENERIC,
}LIBLTE_FDD_DL_SCAN_BLOCK_STATE_ENUM;

/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class liblte_fdd_dl_scan_block_is_started_callback
{
public:
    template<class C, bool (C::*Func)()>
        static bool wrapper(void *o) {return (static_cast<C*>(o)->*Func)();}
    typedef bool (*FuncType)(void*);
    liblte_fdd_dl_scan_block_is_started_callback(FuncType f, void *o) : func{f}, obj{o} {};
    bool operator()() { return (*func)(obj); };
private:
    FuncType  func;
    void     *obj;
};

class liblte_fdd_dl_scan_block_switch_freq_callback
{
public:
    template<class C, int32 (C::*Func)()>
        static int32 wrapper(void *o) {return (static_cast<C*>(o)->*Func)();}
    typedef int32 (*FuncType)(void*);
    liblte_fdd_dl_scan_block_switch_freq_callback(FuncType f, void *o) : func{f}, obj{o} {};
    int32 operator()() { return (*func)(obj); };
private:
    FuncType  func;
    void     *obj;
};

class liblte_fdd_dl_scan_block_send_pcap_callback
{
public:
    template<class C, void (C::*Func)(const uint32, const uint32, LIBLTE_BIT_MSG_STRUCT&)>
        static void wrapper(void *o, const uint32 rnti, const uint32 current_tti, LIBLTE_BIT_MSG_STRUCT &msg) {return (static_cast<C*>(o)->*Func)(rnti, current_tti, msg);}
    typedef void (*FuncType)(void*, const uint32, const uint32, LIBLTE_BIT_MSG_STRUCT&);
    liblte_fdd_dl_scan_block_send_pcap_callback(FuncType f, void *o) : func{f}, obj{o} {};
    void operator()(const uint32 rnti, const uint32 current_tti, LIBLTE_BIT_MSG_STRUCT &msg) { return (*func)(obj, rnti, current_tti, msg); };
private:
    FuncType  func;
    void     *obj;
};

class liblte_fdd_dl_scan_block_send_channel_found_begin_callback
{
public:
    template<class C, void (C::*Func)(const float, const uint32, const MasterInformationBlock&, const uint32, const uint8)>
        static void wrapper(void *o, const float freq_offset, const uint32 N_id_cell, const MasterInformationBlock &mib, const uint32 sfn, const uint8 N_ant) {return (static_cast<C*>(o)->*Func)(freq_offset, N_id_cell, mib, sfn, N_ant);}
    typedef void (*FuncType)(void*, const float, const uint32, const MasterInformationBlock&, const uint32, const uint8);
    liblte_fdd_dl_scan_block_send_channel_found_begin_callback(FuncType f, void *o) : func{f}, obj{o} {};
    void operator()(const float freq_offset, const uint32 N_id_cell, const MasterInformationBlock &mib, const uint32 sfn, const uint8 N_ant) { return (*func)(obj, freq_offset, N_id_cell, mib, sfn, N_ant); };
private:
    FuncType  func;
    void     *obj;
};

class liblte_fdd_dl_scan_block_send_sib1_callback
{
public:
    template<class C, void (C::*Func)(const float, const uint32, const SystemInformationBlockType1&, const uint32)>
        static void wrapper(void *o, const float freq_offset, const uint32 N_id_cell, const SystemInformationBlockType1 &sib1, const uint32 sfn) {return (static_cast<C*>(o)->*Func)(freq_offset, N_id_cell, sib1, sfn);}
    typedef void (*FuncType)(void*, const float, const uint32, const SystemInformationBlockType1&, const uint32 sfn);
    liblte_fdd_dl_scan_block_send_sib1_callback(FuncType f, void *o) : func{f}, obj{o} {};
    void operator()(const float freq_offset, const uint32 N_id_cell, const SystemInformationBlockType1 &sib1, const uint32 sfn) { return (*func)(obj, freq_offset, N_id_cell, sib1, sfn); };
private:
    FuncType  func;
    void     *obj;
};

class liblte_fdd_dl_scan_block_send_sib_callback
{
public:
    template<class C, void (C::*Func)(const float, const uint32, const SystemInformation_r8_IEs&, const uint32)>
        static void wrapper(void *o, const float freq_offset, const uint32 N_id_cell, const SystemInformation_r8_IEs &sib, const uint32 sfn) {return (static_cast<C*>(o)->*Func)(freq_offset, N_id_cell, sib, sfn);}
    typedef void (*FuncType)(void*, const float, const uint32, const SystemInformation_r8_IEs&, const uint32 sfn);
    liblte_fdd_dl_scan_block_send_sib_callback(FuncType f, void *o) : func{f}, obj{o} {};
    void operator()(const float freq_offset, const uint32 N_id_cell, const SystemInformation_r8_IEs &sib, const uint32 sfn) { return (*func)(obj, freq_offset, N_id_cell, sib, sfn); };
private:
    FuncType  func;
    void     *obj;
};

class liblte_fdd_dl_scan_block_send_channel_found_end_callback
{
public:
    template<class C, void (C::*Func)(const float, const uint32)>
        static void wrapper(void *o, const float freq_offset, const uint32 N_id_cell) {return (static_cast<C*>(o)->*Func)(freq_offset, N_id_cell);}
    typedef void (*FuncType)(void*, const float, const uint32);
    liblte_fdd_dl_scan_block_send_channel_found_end_callback(FuncType f, void *o) : func{f}, obj{o} {};
    void operator()(const float freq_offset, const uint32 N_id_cell) { return (*func)(obj, freq_offset, N_id_cell); };
private:
    FuncType  func;
    void     *obj;
};

class liblte_fdd_dl_scan_block_send_channel_not_found_callback
{
public:
    template<class C, void (C::*Func)()>
        static void wrapper(void *o) {return (static_cast<C*>(o)->*Func)();}
    typedef void (*FuncType)(void*);
    liblte_fdd_dl_scan_block_send_channel_not_found_callback(FuncType f, void *o) : func{f}, obj{o} {};
    void operator()() { return (*func)(obj); };
private:
    FuncType  func;
    void     *obj;
};

LIBLTE_FDD_DL_SCAN_BLOCK_API liblte_fdd_dl_scan_block_sptr liblte_fdd_dl_scan_block_make(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                                                                                         liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                                                                                         liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                                                                                         liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                                                                                         liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                                                                                         liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                                                                                         liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                                                                                         size_t                                                      _in_size,
                                                                                         uint32                                                      N_samp_buf_frames,
                                                                                         LIBLTE_PHY_FS_ENUM                                          samp_rate);
LIBLTE_FDD_DL_SCAN_BLOCK_API liblte_fdd_dl_scan_block_sptr liblte_fdd_dl_scan_block_make(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                                                                                         liblte_fdd_dl_scan_block_switch_freq_callback              &_switch_freq_cb,
                                                                                         liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                                                                                         liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                                                                                         liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                                                                                         liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                                                                                         liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                                                                                         liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                                                                                         size_t                                                      _in_size,
                                                                                         uint32                                                      N_samp_buf_frames,
                                                                                         LIBLTE_PHY_FS_ENUM                                          samp_rate);
class LIBLTE_FDD_DL_SCAN_BLOCK_API liblte_fdd_dl_scan_block : public gr::sync_block
{
public:
    ~liblte_fdd_dl_scan_block();

    int32 work(int32                      ninput_items,
               gr_vector_const_void_star &input_items,
               gr_vector_void_star       &output_items);

private:
    friend LIBLTE_FDD_DL_SCAN_BLOCK_API liblte_fdd_dl_scan_block_sptr liblte_fdd_dl_scan_block_make(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                                                                                                    size_t                                                      _in_size,
                                                                                                    uint32                                                      N_samp_buf_frames,
                                                                                                    LIBLTE_PHY_FS_ENUM                                          samp_rate);

    friend LIBLTE_FDD_DL_SCAN_BLOCK_API liblte_fdd_dl_scan_block_sptr liblte_fdd_dl_scan_block_make(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                                                                                                    liblte_fdd_dl_scan_block_switch_freq_callback              &_switch_freq_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                                                                                                    liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                                                                                                    size_t                                                      _in_size,
                                                                                                    uint32                                                      N_samp_buf_frames,
                                                                                                    LIBLTE_PHY_FS_ENUM                                          samp_rate);
    liblte_fdd_dl_scan_block(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                             liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                             liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                             liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                             liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                             liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                             liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                             size_t                                                      _in_size,
                             uint32                                                      N_samp_buf_frames,
                             LIBLTE_PHY_FS_ENUM                                          samp_rate);
    liblte_fdd_dl_scan_block(liblte_fdd_dl_scan_block_is_started_callback               &_is_started_cb,
                             liblte_fdd_dl_scan_block_switch_freq_callback              &_switch_freq_cb,
                             liblte_fdd_dl_scan_block_send_pcap_callback                &_send_pcap_cb,
                             liblte_fdd_dl_scan_block_send_channel_found_begin_callback &_send_channel_found_begin_cb,
                             liblte_fdd_dl_scan_block_send_sib1_callback                &_send_sib1_cb,
                             liblte_fdd_dl_scan_block_send_sib_callback                 &_send_sib_cb,
                             liblte_fdd_dl_scan_block_send_channel_found_end_callback   &_send_channel_found_end_cb,
                             liblte_fdd_dl_scan_block_send_channel_not_found_callback   &_send_channel_not_found_cb,
                             size_t                                                      _in_size,
                             uint32                                                      N_samp_buf_frames,
                             LIBLTE_PHY_FS_ENUM                                          samp_rate);
    void initialize(uint32 N_samp_buf_frames, LIBLTE_PHY_FS_ENUM samp_rate);
    void change_freq_init(void);
    void do_freq_change_wait();
    void do_coarse_timing_search(bool &switch_freq, int32 &done_flag);
    void do_pss_and_fine_timing_search(float &pss_thresh, bool &switch_freq, int32 &done_flag);
    void do_sss_search(float pss_thresh, bool &switch_freq, int32 &done_flag);
    void do_bch_decode(bool &switch_freq, int32 &done_flag);
    void do_pdsch_decode_sib1(bool &switch_freq, int32 &done_flag);
    void do_pdsch_decode_si_generic(bool &switch_freq, int32 &done_flag);
    void copy_input_to_samp_buf(gr_vector_const_void_star &input_items, int32 ninput_items);
    void freq_shift(uint32 start_idx, uint32 num_samps, float freq_offset);
    void channel_found(bool &switch_freq, int32 &done_flag);
    void channel_not_found(bool &switch_freq, int32 &done_flag);
    void send_sib1();
    void send_sib(bool &switch_freq, int32 &done_flag);
    void check_if_all_sibs_received(bool &switch_freq, int32 &done_flag);

    liblte_fdd_dl_scan_block_is_started_callback                                   is_started_cb;
    liblte_fdd_dl_scan_block_switch_freq_callback                                 *switch_freq_cb;
    liblte_fdd_dl_scan_block_send_pcap_callback                                    send_pcap_cb;
    liblte_fdd_dl_scan_block_send_channel_found_begin_callback                     send_channel_found_begin_cb;
    liblte_fdd_dl_scan_block_send_sib1_callback                                    send_sib1_cb;
    liblte_fdd_dl_scan_block_send_sib_callback                                     send_sib_cb;
    liblte_fdd_dl_scan_block_send_channel_found_end_callback                       send_channel_found_end_cb;
    liblte_fdd_dl_scan_block_send_channel_not_found_callback                       send_channel_not_found_cb;
    BCCH_BCH_Message                                                               bcch_bch;
    BCCH_DL_SCH_Message                                                            bcch_dlsch;
    PCCH_Message                                                                   pcch;
    std::vector<uint32>                                                            decoded_chans;
    std::vector<SIB_Type>                                                          expected_sibs;
    std::vector<SystemInformation_r8_IEs::sib_TypeAndInfo_::sib_TypeAndInfo_Enum>  received_sibs;
    LIBLTE_PHY_STRUCT                                                             *phy_struct;
    LIBLTE_PHY_COARSE_TIMING_STRUCT                                                timing_struct;
    LIBLTE_BIT_MSG_STRUCT                                                          rrc_msg;
    LIBLTE_FDD_DL_SCAN_BLOCK_STATE_ENUM                                            state;
    PHICH_Config::phich_Duration_Enum                                              phich_dur;
    size_t                                                                         in_size;
    complex                                                                       *samp_buf;
    float                                                                          phich_res;
    float                                                                          freq_offset;
    uint32                                                                         samp_buf_size;
    uint32                                                                         N_samps_needed;
    uint32                                                                         samp_buf_w_idx;
    uint32                                                                         samp_buf_r_idx;
    uint32                                                                         N_freq_change_iterations;
    uint32                                                                         frame_start_idx;
    uint32                                                                         sfn;
    uint32                                                                         N_sfr;
    uint32                                                                         N_id_cell;
    uint32                                                                         N_id_2;
    uint32                                                                         corr_peak_idx;
    uint32                                                                         N_attempts;
    uint32                                                                         N_bch_attempts;
    uint32                                                                         N_pdsch_attempts;
    uint8                                                                          N_ant;
    bool                                                                           last_samp_was_i;
    bool                                                                           sib1_sent;
    bool                                                                           send_cnf;
};

#endif /* __LIBLTE_FDD_DL_SCAN_BLOCK_H__ */
