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

    File: liblte_mac_tests.cc

    Description: Contains all the tests for the LTE MAC library.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_mac.h"

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
                              FUNCTIONS
*******************************************************************************/

int truncated_bsr_test(void)
{
    LIBLTE_MAC_TRUNCATED_BSR_CE_STRUCT t_bsr;
    t_bsr.max_buffer_size = 4676;
    t_bsr.min_buffer_size = 3996;
    t_bsr.lcg_id          = 1;
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_truncated_bsr_ce(&t_bsr, &ce_ptr))
        return -1;
    if(8 != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    if(1 != liblte_bits_2_value(&ce_ptr, 2) || 40 != liblte_bits_2_value(&ce_ptr, 6))
        return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_truncated_bsr_ce(&ce_ptr, &t_bsr))
        return -1;
    if(t_bsr.lcg_id != 1 || t_bsr.max_buffer_size != 4677 || t_bsr.min_buffer_size != 3995)
        return -1;
    return 0;
}

int short_bsr_test(void)
{
    LIBLTE_MAC_SHORT_BSR_CE_STRUCT s_bsr;
    s_bsr.max_buffer_size = 4676;
    s_bsr.min_buffer_size = 3996;
    s_bsr.lcg_id          = 1;
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_short_bsr_ce(&s_bsr, &ce_ptr))
        return -1;
    if(8 != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    if(1 != liblte_bits_2_value(&ce_ptr, 2) || 40 != liblte_bits_2_value(&ce_ptr, 6))
        return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_short_bsr_ce(&ce_ptr, &s_bsr))
        return -1;
    if(s_bsr.lcg_id != 1 || s_bsr.max_buffer_size != 4677 || s_bsr.min_buffer_size != 3995)
        return -1;
    return 0;
}

int long_bsr_test(void)
{
    LIBLTE_MAC_LONG_BSR_CE_STRUCT l_bsr;
    l_bsr.max_buffer_size_0 = 4676;
    l_bsr.min_buffer_size_0 = 3996;
    l_bsr.max_buffer_size_1 = 1325;
    l_bsr.min_buffer_size_1 = 1133;
    l_bsr.max_buffer_size_2 = 58250;
    l_bsr.min_buffer_size_2 = 49760;
    l_bsr.max_buffer_size_3 = 16;
    l_bsr.min_buffer_size_3 = 15;
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_long_bsr_ce(&l_bsr, &ce_ptr))
        return -1;
    if(24 != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    if(40 != liblte_bits_2_value(&ce_ptr, 6) || 32 != liblte_bits_2_value(&ce_ptr, 6) ||
       56 != liblte_bits_2_value(&ce_ptr, 6) || 4 != liblte_bits_2_value(&ce_ptr, 6))
        return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_long_bsr_ce(&ce_ptr, &l_bsr))
        return -1;
    if(l_bsr.max_buffer_size_0 != 4677 || l_bsr.min_buffer_size_0 != 3995 ||
       l_bsr.max_buffer_size_1 != 1326 || l_bsr.min_buffer_size_1 != 1132 ||
       l_bsr.max_buffer_size_2 != 58255 || l_bsr.min_buffer_size_2 != 49759 ||
       l_bsr.max_buffer_size_3 != 17 || l_bsr.min_buffer_size_3 != 14)
        return -1;
    return 0;
}

int c_rnti_test(void)
{
    LIBLTE_MAC_C_RNTI_CE_STRUCT c_rnti;
    c_rnti.c_rnti = 0xA55A;
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_c_rnti_ce(&c_rnti, &ce_ptr))
        return -1;
    if(16 != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    if(0xA55A != liblte_bits_2_value(&ce_ptr, 16))
        return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_c_rnti_ce(&ce_ptr, &c_rnti))
        return -1;
    if(c_rnti.c_rnti != 0xA55A)
        return -1;
    return 0;
}

int ue_contention_resolution_id_test(void)
{
    LIBLTE_MAC_UE_CONTENTION_RESOLUTION_ID_CE_STRUCT ue_cr;
    ue_cr.id = 0xA55A12345678;
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_ue_contention_resolution_id_ce(&ue_cr, &ce_ptr))
        return -1;
    if(48 != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    if(0xA55A != liblte_bits_2_value(&ce_ptr, 16) ||
       0x12345678 != liblte_bits_2_value(&ce_ptr, 32))
        return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_ue_contention_resolution_id_ce(&ce_ptr, &ue_cr))
        return -1;
    if(ue_cr.id != 0xA55A12345678)
        return -1;
    return 0;
}

int ta_command_test(void)
{
    LIBLTE_MAC_TA_COMMAND_CE_STRUCT ta_command;
    ta_command.ta = 0x26;
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_ta_command_ce(&ta_command, &ce_ptr))
        return -1;
    if(8 != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    if(0x26 != liblte_bits_2_value(&ce_ptr, 8))
        return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_ta_command_ce(&ce_ptr, &ta_command))
        return -1;
    if(ta_command.ta != 0x26)
        return -1;
    return 0;
}

int power_headroom_test(void)
{
    LIBLTE_MAC_POWER_HEADROOM_CE_STRUCT power_headroom;
    power_headroom.ph = 0x26;
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_power_headroom_ce(&power_headroom, &ce_ptr))
        return -1;
    if(8 != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    if(0x26 != liblte_bits_2_value(&ce_ptr, 8))
        return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_power_headroom_ce(&ce_ptr, &power_headroom))
        return -1;
    if(power_headroom.ph != 0x26)
        return -1;
    return 0;
}

int ext_power_headroom_test(void)
{
    LIBLTE_MAC_EXT_POWER_HEADROOM_CE_STRUCT ext_power_headroom;
    ext_power_headroom.pcell_type_2_present = false;
    ext_power_headroom.scell_present[0] = true;
    ext_power_headroom.scell_present[1] = true;
    ext_power_headroom.scell_present[2] = false;
    ext_power_headroom.scell_present[3] = false;
    ext_power_headroom.scell_present[4] = true;
    ext_power_headroom.scell_present[5] = false;
    ext_power_headroom.scell_present[6] = true;
    ext_power_headroom.pcell_type_1.ph = 6;
    ext_power_headroom.pcell_type_1.p_cmax = 5;
    ext_power_headroom.pcell_type_1.p = true;
    ext_power_headroom.pcell_type_1.v = false;
    for(uint32 i=0; i<7; i++)
    {
        ext_power_headroom.scell[i].ph = i;
        ext_power_headroom.scell[i].p = false;
        ext_power_headroom.scell[i].v = true;
    }
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_ext_power_headroom_ce(&ext_power_headroom, &ce_ptr))
        return -1;
    if(56 != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    if(0xA6 != liblte_bits_2_value(&ce_ptr, 8) || 0x86 != liblte_bits_2_value(&ce_ptr, 8) ||
       0x05 != liblte_bits_2_value(&ce_ptr, 8) || 0x40 != liblte_bits_2_value(&ce_ptr, 8) ||
       0x41 != liblte_bits_2_value(&ce_ptr, 8) || 0x44 != liblte_bits_2_value(&ce_ptr, 8) ||
       0x46 != liblte_bits_2_value(&ce_ptr, 8))
        return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_ext_power_headroom_ce(&ce_ptr,
                                                                 false,
                                                                 &ext_power_headroom))
        return -1;
    if(ext_power_headroom.pcell_type_2_present != false ||
       ext_power_headroom.scell_present[0] != true ||
       ext_power_headroom.scell_present[1] != true ||
       ext_power_headroom.scell_present[2] != false ||
       ext_power_headroom.scell_present[3] != false ||
       ext_power_headroom.scell_present[4] != true ||
       ext_power_headroom.scell_present[5] != false ||
       ext_power_headroom.scell_present[6] != true ||
       ext_power_headroom.pcell_type_1.ph != 6 ||
       ext_power_headroom.pcell_type_1.p_cmax != 5 ||
       ext_power_headroom.pcell_type_1.p != true ||
       ext_power_headroom.pcell_type_1.v != false ||
       ext_power_headroom.scell[0].ph != 0 || ext_power_headroom.scell[0].p != false ||
       ext_power_headroom.scell[0].v != true || ext_power_headroom.scell[1].ph != 1 ||
       ext_power_headroom.scell[1].p != false || ext_power_headroom.scell[1].v != true ||
       ext_power_headroom.scell[4].ph != 4 || ext_power_headroom.scell[4].p != false ||
       ext_power_headroom.scell[4].v != true || ext_power_headroom.scell[6].ph != 6 ||
       ext_power_headroom.scell[6].p != false || ext_power_headroom.scell[6].v != true)
        return -1;
    return 0;
}

int mch_scheduling_information_test(void)
{
    LIBLTE_MAC_MCH_SCHEDULING_INFORMATION_CE_STRUCT mch_sched_info;
    mch_sched_info.N_items = 5;
    for(uint32 i=0; i<mch_sched_info.N_items; i++)
    {
        mch_sched_info.stop_mch[i] = i+5;
        mch_sched_info.lcid[i] = i;
    }
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_mch_scheduling_information_ce(&mch_sched_info,
                                                                       &ce_ptr))
        return -1;
    if((5*16) != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    for(uint32 i=0; i<mch_sched_info.N_items; i++)
        if(i != liblte_bits_2_value(&ce_ptr, 5) || (i+5) != liblte_bits_2_value(&ce_ptr, 11))
            return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_mch_scheduling_information_ce(&ce_ptr,
                                                                         &mch_sched_info))
        return -1;
    for(uint32 i=0; i<5; i++)
        if(mch_sched_info.stop_mch[i] != i+5 || mch_sched_info.lcid[i] != i)
            return -1;
    return 0;
}

int activation_deactivation_test(void)
{
    LIBLTE_MAC_ACTIVATION_DEACTIVATION_CE_STRUCT act_deact;
    act_deact.c7 = true;
    act_deact.c6 = false;
    act_deact.c5 = true;
    act_deact.c4 = false;
    act_deact.c3 = true;
    act_deact.c2 = false;
    act_deact.c1 = true;
    LIBLTE_BIT_MSG_STRUCT msg;
    uint8 *ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_activation_deactivation_ce(&act_deact, &ce_ptr))
        return -1;
    if(8 != (ce_ptr - msg.msg))
        return -1;
    ce_ptr = msg.msg;
    if(1 != liblte_bits_2_value(&ce_ptr, 1) || 0 != liblte_bits_2_value(&ce_ptr, 1) ||
       1 != liblte_bits_2_value(&ce_ptr, 1) || 0 != liblte_bits_2_value(&ce_ptr, 1) ||
       1 != liblte_bits_2_value(&ce_ptr, 1) || 0 != liblte_bits_2_value(&ce_ptr, 1) ||
       1 != liblte_bits_2_value(&ce_ptr, 1) || 0 != liblte_bits_2_value(&ce_ptr, 1))
        return -1;
    ce_ptr = msg.msg;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_activation_deactivation_ce(&ce_ptr, &act_deact))
        return -1;
    if(act_deact.c7 != true || act_deact.c6 != false || act_deact.c5 != true ||
       act_deact.c4 != false || act_deact.c3 != true || act_deact.c2 != false ||
       act_deact.c1 != true)
            return -1;
    return 0;
}

int mac_pdu_dlsch_test(void)
{
    LIBLTE_MAC_PDU_STRUCT pdu;
    pdu.N_subheaders = 6;
    pdu.chan_type = LIBLTE_MAC_CHAN_TYPE_DLSCH;
    pdu.subheader[0].lcid = LIBLTE_MAC_DLSCH_CCCH_LCID;
    pdu.subheader[0].payload.sdu.N_bytes = 1;
    pdu.subheader[0].payload.sdu.msg[0] = 0xA5;
    pdu.subheader[1].lcid = LIBLTE_MAC_DLSCH_DCCH_LCID_BEGIN+1;
    pdu.subheader[1].payload.sdu.N_bytes = 1;
    pdu.subheader[1].payload.sdu.msg[0] = 0x5A;
    pdu.subheader[2].lcid = LIBLTE_MAC_DLSCH_ACTIVATION_DEACTIVATION_LCID;
    pdu.subheader[2].payload.act_deact.c1 = true;
    pdu.subheader[2].payload.act_deact.c2 = false;
    pdu.subheader[2].payload.act_deact.c3 = true;
    pdu.subheader[2].payload.act_deact.c4 = true;
    pdu.subheader[2].payload.act_deact.c5 = false;
    pdu.subheader[2].payload.act_deact.c6 = false;
    pdu.subheader[2].payload.act_deact.c7 = true;
    pdu.subheader[3].lcid = LIBLTE_MAC_DLSCH_UE_CONTENTION_RESOLUTION_ID_LCID;
    pdu.subheader[3].payload.ue_con_res_id.id = 0x123456789ABC;
    pdu.subheader[4].lcid = LIBLTE_MAC_DLSCH_TA_COMMAND_LCID;
    pdu.subheader[4].payload.ta_command.ta = 0x26;
    pdu.subheader[5].lcid = LIBLTE_MAC_DLSCH_PADDING_LCID;
    LIBLTE_BIT_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_mac_pdu(&pdu, &msg))
        return -1;
    if((18 * 8) != msg.N_bits)
        return -1;
    uint8 *pdu_ptr = msg.msg;
    if(0x2001 != liblte_bits_2_value(&pdu_ptr, 16) ||
       0x2201 != liblte_bits_2_value(&pdu_ptr, 16) ||
       0x3B3C != liblte_bits_2_value(&pdu_ptr, 16) ||
       0x3D1F != liblte_bits_2_value(&pdu_ptr, 16) ||
       0xA55A != liblte_bits_2_value(&pdu_ptr, 16) ||
       0x9A1234 != liblte_bits_2_value(&pdu_ptr, 24) ||
       0x56789ABC != liblte_bits_2_value(&pdu_ptr, 32) ||
       0x26 != liblte_bits_2_value(&pdu_ptr, 8))
        return -1;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_mac_pdu(&msg, false, &pdu))
        return -1;
    if(pdu.N_subheaders != 6 || pdu.chan_type != LIBLTE_MAC_CHAN_TYPE_DLSCH ||
       pdu.subheader[0].lcid != LIBLTE_MAC_DLSCH_CCCH_LCID ||
       pdu.subheader[0].payload.sdu.N_bytes != 1 ||
       pdu.subheader[0].payload.sdu.msg[0] != 0xA5 ||
       pdu.subheader[1].lcid != LIBLTE_MAC_DLSCH_DCCH_LCID_BEGIN+1 ||
       pdu.subheader[1].payload.sdu.N_bytes != 1 ||
       pdu.subheader[1].payload.sdu.msg[0] != 0x5A ||
       pdu.subheader[2].lcid != LIBLTE_MAC_DLSCH_ACTIVATION_DEACTIVATION_LCID ||
       pdu.subheader[2].payload.act_deact.c1 != true ||
       pdu.subheader[2].payload.act_deact.c2 != false ||
       pdu.subheader[2].payload.act_deact.c3 != true ||
       pdu.subheader[2].payload.act_deact.c4 != true ||
       pdu.subheader[2].payload.act_deact.c5 != false ||
       pdu.subheader[2].payload.act_deact.c6 != false ||
       pdu.subheader[2].payload.act_deact.c7 != true ||
       pdu.subheader[3].lcid != LIBLTE_MAC_DLSCH_UE_CONTENTION_RESOLUTION_ID_LCID ||
       pdu.subheader[3].payload.ue_con_res_id.id != 0x123456789ABC ||
       pdu.subheader[4].lcid != LIBLTE_MAC_DLSCH_TA_COMMAND_LCID ||
       pdu.subheader[4].payload.ta_command.ta != 0x26 ||
       pdu.subheader[5].lcid != LIBLTE_MAC_DLSCH_PADDING_LCID)
        return -1;
    return 0;
}

int mac_pdu_ulsch_test(void)
{
    LIBLTE_MAC_PDU_STRUCT pdu;
    pdu.N_subheaders = 9;
    pdu.chan_type = LIBLTE_MAC_CHAN_TYPE_ULSCH;
    pdu.subheader[0].lcid = LIBLTE_MAC_ULSCH_CCCH_LCID;
    pdu.subheader[0].payload.sdu.N_bytes = 1;
    pdu.subheader[0].payload.sdu.msg[0] = 0xA5;
    pdu.subheader[1].lcid = LIBLTE_MAC_ULSCH_DCCH_LCID_BEGIN+1;
    pdu.subheader[1].payload.sdu.N_bytes = 1;
    pdu.subheader[1].payload.sdu.msg[0] = 0x5A;
    pdu.subheader[2].lcid = LIBLTE_MAC_ULSCH_EXT_POWER_HEADROOM_REPORT_LCID;
    pdu.subheader[2].payload.ext_power_headroom.pcell_type_2_present = false;
    pdu.subheader[2].payload.ext_power_headroom.scell_present[0] = true;
    pdu.subheader[2].payload.ext_power_headroom.scell_present[1] = true;
    pdu.subheader[2].payload.ext_power_headroom.scell_present[2] = false;
    pdu.subheader[2].payload.ext_power_headroom.scell_present[3] = false;
    pdu.subheader[2].payload.ext_power_headroom.scell_present[4] = true;
    pdu.subheader[2].payload.ext_power_headroom.scell_present[5] = false;
    pdu.subheader[2].payload.ext_power_headroom.scell_present[6] = true;
    pdu.subheader[2].payload.ext_power_headroom.pcell_type_1.ph = 6;
    pdu.subheader[2].payload.ext_power_headroom.pcell_type_1.p_cmax = 5;
    pdu.subheader[2].payload.ext_power_headroom.pcell_type_1.p = true;
    pdu.subheader[2].payload.ext_power_headroom.pcell_type_1.v = false;
    for(uint32 i=0; i<7; i++)
    {
        pdu.subheader[2].payload.ext_power_headroom.scell[i].ph = i;
        pdu.subheader[2].payload.ext_power_headroom.scell[i].p = false;
        pdu.subheader[2].payload.ext_power_headroom.scell[i].v = true;
    }
    pdu.subheader[3].lcid = LIBLTE_MAC_ULSCH_POWER_HEADROOM_REPORT_LCID;
    pdu.subheader[3].payload.power_headroom.ph = 0x3F;
    pdu.subheader[4].lcid = LIBLTE_MAC_ULSCH_C_RNTI_LCID;
    pdu.subheader[4].payload.c_rnti.c_rnti = 0x1234;
    pdu.subheader[5].lcid = LIBLTE_MAC_ULSCH_TRUNCATED_BSR_LCID;
    pdu.subheader[5].payload.truncated_bsr.lcg_id = 1;
    pdu.subheader[5].payload.truncated_bsr.max_buffer_size = 4676;
    pdu.subheader[5].payload.truncated_bsr.min_buffer_size = 3996;
    pdu.subheader[6].lcid = LIBLTE_MAC_ULSCH_SHORT_BSR_LCID;
    pdu.subheader[6].payload.short_bsr.lcg_id = 2;
    pdu.subheader[6].payload.short_bsr.max_buffer_size = 1325;
    pdu.subheader[6].payload.short_bsr.min_buffer_size = 1133;
    pdu.subheader[7].lcid = LIBLTE_MAC_ULSCH_LONG_BSR_LCID;
    pdu.subheader[7].payload.long_bsr.max_buffer_size_0 = 4676;
    pdu.subheader[7].payload.long_bsr.min_buffer_size_0 = 3996;
    pdu.subheader[7].payload.long_bsr.max_buffer_size_1 = 1325;
    pdu.subheader[7].payload.long_bsr.min_buffer_size_1 = 1133;
    pdu.subheader[7].payload.long_bsr.max_buffer_size_2 = 58250;
    pdu.subheader[7].payload.long_bsr.min_buffer_size_2 = 49760;
    pdu.subheader[7].payload.long_bsr.max_buffer_size_3 = 16;
    pdu.subheader[7].payload.long_bsr.min_buffer_size_3 = 15;
    pdu.subheader[8].lcid = LIBLTE_MAC_ULSCH_PADDING_LCID;
    LIBLTE_BIT_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_mac_pdu(&pdu, &msg))
        return -1;
    if((29 * 8) != msg.N_bits)
        return -1;
    uint8 *pdu_ptr = msg.msg;
    if(0x20012201 != liblte_bits_2_value(&pdu_ptr, 32) ||
       0x39073A3B != liblte_bits_2_value(&pdu_ptr, 32) ||
       0x3C3D3E1F != liblte_bits_2_value(&pdu_ptr, 32) ||
       0xA55AA686 != liblte_bits_2_value(&pdu_ptr, 32) ||
       0x05404144 != liblte_bits_2_value(&pdu_ptr, 32) ||
       0x463F1234 != liblte_bits_2_value(&pdu_ptr, 32) ||
       0x68A0A20E != liblte_bits_2_value(&pdu_ptr, 32) ||
       0x04 != liblte_bits_2_value(&pdu_ptr, 8))
        return -1;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_mac_pdu(&msg, false, &pdu))
        return -1;
    if(pdu.N_subheaders != 9 || pdu.chan_type != LIBLTE_MAC_CHAN_TYPE_ULSCH ||
       pdu.subheader[0].lcid != LIBLTE_MAC_ULSCH_CCCH_LCID ||
       pdu.subheader[0].payload.sdu.N_bytes != 1 ||
       pdu.subheader[0].payload.sdu.msg[0] != 0xA5 ||
       pdu.subheader[1].lcid != LIBLTE_MAC_ULSCH_DCCH_LCID_BEGIN+1 ||
       pdu.subheader[1].payload.sdu.N_bytes != 1 ||
       pdu.subheader[1].payload.sdu.msg[0] != 0x5A ||
       pdu.subheader[2].lcid != LIBLTE_MAC_ULSCH_EXT_POWER_HEADROOM_REPORT_LCID ||
       pdu.subheader[2].payload.ext_power_headroom.scell_present[0] != true ||
       pdu.subheader[2].payload.ext_power_headroom.scell_present[1] != true ||
       pdu.subheader[2].payload.ext_power_headroom.scell_present[2] != false ||
       pdu.subheader[2].payload.ext_power_headroom.scell_present[3] != false ||
       pdu.subheader[2].payload.ext_power_headroom.scell_present[4] != true ||
       pdu.subheader[2].payload.ext_power_headroom.scell_present[5] != false ||
       pdu.subheader[2].payload.ext_power_headroom.scell_present[6] != true ||
       pdu.subheader[2].payload.ext_power_headroom.pcell_type_1.ph != 6 ||
       pdu.subheader[2].payload.ext_power_headroom.pcell_type_1.p_cmax != 5 ||
       pdu.subheader[2].payload.ext_power_headroom.pcell_type_1.p != true ||
       pdu.subheader[2].payload.ext_power_headroom.pcell_type_1.v != false ||
       pdu.subheader[2].payload.ext_power_headroom.scell[0].ph != 0 ||
       pdu.subheader[2].payload.ext_power_headroom.scell[0].p != false ||
       pdu.subheader[2].payload.ext_power_headroom.scell[0].v != true ||
       pdu.subheader[2].payload.ext_power_headroom.scell[1].ph != 1 ||
       pdu.subheader[2].payload.ext_power_headroom.scell[1].p != false ||
       pdu.subheader[2].payload.ext_power_headroom.scell[1].v != true ||
       pdu.subheader[2].payload.ext_power_headroom.scell[4].ph != 4 ||
       pdu.subheader[2].payload.ext_power_headroom.scell[4].p != false ||
       pdu.subheader[2].payload.ext_power_headroom.scell[4].v != true ||
       pdu.subheader[2].payload.ext_power_headroom.scell[6].ph != 6 ||
       pdu.subheader[2].payload.ext_power_headroom.scell[6].p != false ||
       pdu.subheader[2].payload.ext_power_headroom.scell[6].v != true ||
       pdu.subheader[3].lcid != LIBLTE_MAC_ULSCH_POWER_HEADROOM_REPORT_LCID ||
       pdu.subheader[3].payload.power_headroom.ph != 0x3F ||
       pdu.subheader[4].lcid != LIBLTE_MAC_ULSCH_C_RNTI_LCID ||
       pdu.subheader[4].payload.c_rnti.c_rnti != 0x1234 ||
       pdu.subheader[5].lcid != LIBLTE_MAC_ULSCH_TRUNCATED_BSR_LCID ||
       pdu.subheader[5].payload.truncated_bsr.lcg_id != 1 ||
       pdu.subheader[5].payload.truncated_bsr.max_buffer_size != 4677 ||
       pdu.subheader[5].payload.truncated_bsr.min_buffer_size != 3995 ||
       pdu.subheader[6].lcid != LIBLTE_MAC_ULSCH_SHORT_BSR_LCID ||
       pdu.subheader[6].payload.short_bsr.lcg_id != 2 ||
       pdu.subheader[6].payload.short_bsr.max_buffer_size != 1326 ||
       pdu.subheader[6].payload.short_bsr.min_buffer_size != 1132 ||
       pdu.subheader[7].lcid != LIBLTE_MAC_ULSCH_LONG_BSR_LCID ||
       pdu.subheader[7].payload.long_bsr.max_buffer_size_0 != 4677 ||
       pdu.subheader[7].payload.long_bsr.min_buffer_size_0 != 3995 ||
       pdu.subheader[7].payload.long_bsr.max_buffer_size_1 != 1326 ||
       pdu.subheader[7].payload.long_bsr.min_buffer_size_1 != 1132 ||
       pdu.subheader[7].payload.long_bsr.max_buffer_size_2 != 58255 ||
       pdu.subheader[7].payload.long_bsr.min_buffer_size_2 != 49759 ||
       pdu.subheader[7].payload.long_bsr.max_buffer_size_3 != 17 ||
       pdu.subheader[7].payload.long_bsr.min_buffer_size_3 != 14 ||
       pdu.subheader[8].lcid != LIBLTE_MAC_ULSCH_PADDING_LCID)
        return -1;
    return 0;
}

int mac_pdu_test(void)
{
    if(0 != mac_pdu_dlsch_test())
        return -1;
    if(0 != mac_pdu_ulsch_test())
        return -1;
    return 0;
}

int random_access_response_bi_test(void)
{
    LIBLTE_MAC_RAR_STRUCT rar;
    rar.hdr_type = LIBLTE_MAC_RAR_HEADER_TYPE_BI;
    rar.BI = 5;
    LIBLTE_BIT_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_random_access_response_pdu(&rar, &msg))
        return -1;
    if(8 != msg.N_bits)
        return -1;
    uint8 *pdu_ptr = msg.msg;
    if(0x05 != liblte_bits_2_value(&pdu_ptr, 8))
        return -1;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_random_access_response_pdu(&msg, &rar))
        return -1;
    if(rar.hdr_type != LIBLTE_MAC_RAR_HEADER_TYPE_BI || rar.BI != 5)
        return -1;
    return 0;
}

int random_access_response_rapid_test(void)
{
    LIBLTE_MAC_RAR_STRUCT rar;
    rar.hdr_type = LIBLTE_MAC_RAR_HEADER_TYPE_RAPID;
    rar.RAPID = 0x2A;
    rar.timing_adv_cmd = 0x3A5;
    rar.hopping_flag = LIBLTE_MAC_RAR_HOPPING_DISABLED;
    rar.rba = 0x15A;
    rar.mcs = 0x06;
    rar.tpc_command = LIBLTE_MAC_RAR_TPC_COMMAND_2dB;
    rar.ul_delay = LIBLTE_MAC_RAR_UL_DELAY_DISABLED;
    rar.csi_req = LIBLTE_MAC_RAR_CSI_REQ_ENABLED;
    rar.temp_c_rnti = 0x1234;
    LIBLTE_BIT_MSG_STRUCT msg;
    if(LIBLTE_SUCCESS != liblte_mac_pack_random_access_response_pdu(&rar, &msg))
        return -1;
    if(56 != msg.N_bits)
        return -1;
    uint8 *pdu_ptr = msg.msg;
    if(0x6A != liblte_bits_2_value(&pdu_ptr, 8) || 0x3A != liblte_bits_2_value(&pdu_ptr, 8) ||
       0x52 != liblte_bits_2_value(&pdu_ptr, 8) || 0xB4 != liblte_bits_2_value(&pdu_ptr, 8) ||
       0xD1 != liblte_bits_2_value(&pdu_ptr, 8) || 0x1234 != liblte_bits_2_value(&pdu_ptr, 16))
        return -1;
    if(LIBLTE_SUCCESS != liblte_mac_unpack_random_access_response_pdu(&msg, &rar))
        return -1;
    if(rar.hdr_type != LIBLTE_MAC_RAR_HEADER_TYPE_RAPID || rar.RAPID != 0x2A ||
       rar.timing_adv_cmd != 0x3A5 || rar.hopping_flag != LIBLTE_MAC_RAR_HOPPING_DISABLED ||
       rar.rba != 0x15A || rar.mcs != 0x06 ||
       rar.tpc_command != LIBLTE_MAC_RAR_TPC_COMMAND_2dB ||
       rar.ul_delay != LIBLTE_MAC_RAR_UL_DELAY_DISABLED ||
       rar.csi_req != LIBLTE_MAC_RAR_CSI_REQ_ENABLED ||
       rar.temp_c_rnti != 0x1234)
        return -1;
    return 0;
}

int random_access_response_test(void)
{
    if(0 != random_access_response_bi_test())
        return -1;
    if(0 != random_access_response_rapid_test())
        return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    printf("truncated_bsr_test: ");
    if(0 != truncated_bsr_test())
        exit(-1);
    printf("pass\n");
    printf("short_bsr_test: ");
    if(0 != short_bsr_test())
        exit(-1);
    printf("pass\n");
    printf("long_bsr_test: ");
    if(0 != long_bsr_test())
        exit(-1);
    printf("pass\n");
    printf("c_rnti_test: ");
    if(0 != c_rnti_test())
        exit(-1);
    printf("pass\n");
    printf("ue_contention_resolution_id_test: ");
    if(0 != ue_contention_resolution_id_test())
        exit(-1);
    printf("pass\n");
    printf("ta_command_test: ");
    if(0 != ta_command_test())
        exit(-1);
    printf("pass\n");
    printf("power_headroom_test: ");
    if(0 != power_headroom_test())
        exit(-1);
    printf("pass\n");
    printf("ext_power_headroom_test: ");
    if(0 != ext_power_headroom_test())
        exit(-1);
    printf("pass\n");
    printf("mch_scheduling_information_test: ");
    if(0 != mch_scheduling_information_test())
        exit(-1);
    printf("pass\n");
    printf("activation_deactivation_test: ");
    if(0 != activation_deactivation_test())
        exit(-1);
    printf("pass\n");
    printf("mac_pdu_test: ");
    if(0 != mac_pdu_test())
        exit(-1);
    printf("pass\n");
    printf("random_access_response_test: ");
    if(0 != random_access_response_test())
        exit(-1);
    printf("pass\n");
    exit(0);
}
