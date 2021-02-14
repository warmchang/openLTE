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

    File: liblte_pdcp_tests.cc

    Description: Contains all the tests for the LTE PDCP library.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_pdcp.h"
#include "liblte_security.h"

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

int cpdu_format_1_test(void)
{
    LIBLTE_PDCP_CONTROL_PDU_STRUCT contents;
    contents.count = 0x15;
    contents.data.N_bits = 16;
    for(uint32 i=0; i<16; i++)
        contents.data.msg[i] = i%2;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_control_pdu(&contents, &pdu))
        return -1;
    if(7 != pdu.N_bytes)
        return -1;
    if(0x15 != pdu.msg[0] || 0x55 != pdu.msg[1] || 0x55 != pdu.msg[2] || 0x00 != pdu.msg[3] ||
       0x00 != pdu.msg[4] || 0x00 != pdu.msg[5] || 0x00 != pdu.msg[6])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_control_pdu(&pdu, &contents))
        return -1;
    if(contents.count != 0x15 || contents.data.N_bits != 16)
        return -1;
    for(uint32 i=0; i<16; i++)
        if(contents.data.msg[i] != i%2)
            return -1;
    return 0;
}

int cpdu_format_2_test(void)
{
    LIBLTE_PDCP_CONTROL_PDU_STRUCT contents;
    contents.count = 0x15;
    LIBLTE_BIT_MSG_STRUCT data;
    data.N_bits = 16;
    for(uint32 i=0; i<16; i++)
        data.msg[i] = i%2;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_control_pdu(&contents, &data, &pdu))
        return -1;
    if(7 != pdu.N_bytes)
        return -1;
    if(0x15 != pdu.msg[0] || 0x55 != pdu.msg[1] || 0x55 != pdu.msg[2] || 0x00 != pdu.msg[3] ||
       0x00 != pdu.msg[4] || 0x00 != pdu.msg[5] || 0x00 != pdu.msg[6])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_control_pdu(&pdu, &contents))
        return -1;
    if(contents.count != 0x15 || contents.data.N_bits != 16)
        return -1;
    for(uint32 i=0; i<16; i++)
        if(contents.data.msg[i] != i%2)
            return -1;
    return 0;
}

int cpdu_format_3_test(void)
{
    LIBLTE_PDCP_CONTROL_PDU_STRUCT contents;
    contents.count = 0x15;
    contents.data.N_bits = 16;
    for(uint32 i=0; i<16; i++)
        contents.data.msg[i] = i%2;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    uint8 key[32];
    for(uint32 i=0; i<32; i++)
        key[i] = i;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_control_pdu(&contents, key,
                                                      LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                      2, &pdu))
        return -1;
    if(7 != pdu.N_bytes)
        return -1;
    if(0x15 != pdu.msg[0] || 0x55 != pdu.msg[1] || 0x55 != pdu.msg[2] || 0x64 != pdu.msg[3] ||
       0xD0 != pdu.msg[4] || 0x90 != pdu.msg[5] || 0x6F != pdu.msg[6])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_control_pdu(&pdu, &contents))
        return -1;
    if(contents.count != 0x15 || contents.data.N_bits != 16)
        return -1;
    for(uint32 i=0; i<16; i++)
        if(contents.data.msg[i] != i%2)
            return -1;
    return 0;
}

int cpdu_format_4_test(void)
{
    LIBLTE_PDCP_CONTROL_PDU_STRUCT contents;
    contents.count = 0x15;
    LIBLTE_BIT_MSG_STRUCT data;
    data.N_bits = 16;
    for(uint32 i=0; i<16; i++)
        data.msg[i] = i%2;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    uint8 key[32];
    for(uint32 i=0; i<32; i++)
        key[i] = i;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_control_pdu(&contents, &data, key,
                                                      LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                      2, &pdu))
        return -1;
    if(7 != pdu.N_bytes)
        return -1;
    if(0x15 != pdu.msg[0] || 0x55 != pdu.msg[1] || 0x55 != pdu.msg[2] || 0x64 != pdu.msg[3] ||
       0xD0 != pdu.msg[4] || 0x90 != pdu.msg[5] || 0x6F != pdu.msg[6])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_control_pdu(&pdu, &contents))
        return -1;
    if(contents.count != 0x15 || contents.data.N_bits != 16)
        return -1;
    for(uint32 i=0; i<16; i++)
        if(contents.data.msg[i] != i%2)
            return -1;
    return 0;
}

int control_pdu_test(void)
{
    if(0 != cpdu_format_1_test())
        return -1;
    if(0 != cpdu_format_2_test())
        return -1;
    if(0 != cpdu_format_3_test())
        return -1;
    if(0 != cpdu_format_4_test())
        return -1;
    return 0;
}

int dpls_format_1_test(void)
{
    LIBLTE_PDCP_DATA_PDU_WITH_LONG_SN_STRUCT contents;
    contents.count = 0xABC;
    contents.data.N_bytes = 2;
    contents.data.msg[0] = 0xA5;
    contents.data.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_data_pdu_with_long_sn(&contents, &pdu))
        return -1;
    if(4 != pdu.N_bytes)
        return -1;
    if(0x8A != pdu.msg[0] || 0xBC != pdu.msg[1] || 0xA5 != pdu.msg[2] || 0x5A != pdu.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_data_pdu_with_long_sn(&pdu, &contents))
        return -1;
    if(contents.count != 0xABC || contents.data.N_bytes != 2 ||
       contents.data.msg[0] != 0xA5 || contents.data.msg[1] !=0x5A)
        return -1;
    return 0;
}

int dpls_format_2_test(void)
{
    LIBLTE_PDCP_DATA_PDU_WITH_LONG_SN_STRUCT contents;
    contents.count = 0xABC;
    LIBLTE_BYTE_MSG_STRUCT data;
    data.N_bytes = 2;
    data.msg[0] = 0xA5;
    data.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_data_pdu_with_long_sn(&contents, &data, &pdu))
        return -1;
    if(4 != pdu.N_bytes)
        return -1;
    if(0x8A != pdu.msg[0] || 0xBC != pdu.msg[1] || 0xA5 != pdu.msg[2] || 0x5A != pdu.msg[3])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_data_pdu_with_long_sn(&pdu, &contents))
        return -1;
    if(contents.count != 0xABC || contents.data.N_bytes != 2 ||
       contents.data.msg[0] != 0xA5 || contents.data.msg[1] !=0x5A)
        return -1;
    return 0;
}

int data_pdu_with_long_sn_test(void)
{
    if(0 != dpls_format_1_test())
        return -1;
    if(0 != dpls_format_2_test())
        return -1;
    return 0;
}

int dpss_format_1_test(void)
{
    LIBLTE_PDCP_DATA_PDU_WITH_SHORT_SN_STRUCT contents;
    contents.count = 0x5A;
    contents.data.N_bytes = 2;
    contents.data.msg[0] = 0xA5;
    contents.data.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_data_pdu_with_short_sn(&contents, &pdu))
        return -1;
    if(3 != pdu.N_bytes)
        return -1;
    if(0xDA != pdu.msg[0] || 0xA5 != pdu.msg[1] || 0x5A != pdu.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_data_pdu_with_short_sn(&pdu, &contents))
        return -1;
    if(contents.count != 0x5A || contents.data.N_bytes != 2 ||
       contents.data.msg[0] != 0xA5 || contents.data.msg[1] !=0x5A)
        return -1;
    return 0;
}

int dpss_format_2_test(void)
{
    LIBLTE_PDCP_DATA_PDU_WITH_SHORT_SN_STRUCT contents;
    contents.count = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT data;
    data.N_bytes = 2;
    data.msg[0] = 0xA5;
    data.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_data_pdu_with_short_sn(&contents, &data, &pdu))
        return -1;
    if(3 != pdu.N_bytes)
        return -1;
    if(0xDA != pdu.msg[0] || 0xA5 != pdu.msg[1] || 0x5A != pdu.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_data_pdu_with_short_sn(&pdu, &contents))
        return -1;
    if(contents.count != 0x5A || contents.data.N_bytes != 2 ||
       contents.data.msg[0] != 0xA5 || contents.data.msg[1] !=0x5A)
        return -1;
    return 0;
}

int data_pdu_with_short_sn_test(void)
{
    if(0 != dpss_format_1_test())
        return -1;
    if(0 != dpss_format_2_test())
        return -1;
    return 0;
}

int cpirf_format_1_test(void)
{
    LIBLTE_PDCP_CONTROL_PDU_FOR_INTERSPERSED_ROHC_FEEDBACK_STRUCT contents;
    contents.pdu_type = LIBLTE_PDCP_PDU_TYPE_INTERSPERSED_ROHC_FEEDBACK_PACKET;
    contents.rohc_feedback_packet.N_bytes = 2;
    contents.rohc_feedback_packet.msg[0] = 0xA5;
    contents.rohc_feedback_packet.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_control_pdu_for_interspersed_rohc_feedback(&contents,
                                                                                     &pdu))
        return -1;
    if(3 != pdu.N_bytes)
        return -1;
    if(0x10 != pdu.msg[0] || 0xA5 != pdu.msg[1] || 0x5A != pdu.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_control_pdu_for_interspersed_rohc_feedback(&pdu,
                                                                                       &contents))
        return -1;
    if(contents.pdu_type != LIBLTE_PDCP_PDU_TYPE_INTERSPERSED_ROHC_FEEDBACK_PACKET ||
       contents.rohc_feedback_packet.N_bytes != 2 ||
       contents.rohc_feedback_packet.msg[0] != 0xA5 ||
       contents.rohc_feedback_packet.msg[1] !=0x5A)
        return -1;
    return 0;
}

int cpirf_format_2_test(void)
{
    LIBLTE_PDCP_CONTROL_PDU_FOR_INTERSPERSED_ROHC_FEEDBACK_STRUCT contents;
    contents.pdu_type = LIBLTE_PDCP_PDU_TYPE_INTERSPERSED_ROHC_FEEDBACK_PACKET;
    LIBLTE_BYTE_MSG_STRUCT rohc_feedback_packet;
    rohc_feedback_packet.N_bytes = 2;
    rohc_feedback_packet.msg[0] = 0xA5;
    rohc_feedback_packet.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_control_pdu_for_interspersed_rohc_feedback(&contents,
                                                                                     &rohc_feedback_packet,
                                                                                     &pdu))
        return -1;
    if(3 != pdu.N_bytes)
        return -1;
    if(0x10 != pdu.msg[0] || 0xA5 != pdu.msg[1] || 0x5A != pdu.msg[2])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_control_pdu_for_interspersed_rohc_feedback(&pdu,
                                                                                       &contents))
        return -1;
    if(contents.pdu_type != LIBLTE_PDCP_PDU_TYPE_INTERSPERSED_ROHC_FEEDBACK_PACKET ||
       contents.rohc_feedback_packet.N_bytes != 2 ||
       contents.rohc_feedback_packet.msg[0] != 0xA5 ||
       contents.rohc_feedback_packet.msg[1] !=0x5A)
        return -1;
    return 0;
}

int control_pdu_for_interspersed_rohc_feedback_test(void)
{
    if(0 != cpirf_format_1_test())
        return -1;
    if(0 != cpirf_format_2_test())
        return -1;
    return 0;
}

int rupdp_format_1_test(void)
{
    LIBLTE_PDCP_RN_USER_PLANE_DATA_PDU_STRUCT contents;
    contents.count = 0xABC;
    contents.data.N_bytes = 2;
    contents.data.msg[0] = 0xA5;
    contents.data.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_rn_user_plane_data_pdu(&contents, &pdu))
        return -1;
    if(8 != pdu.N_bytes)
        return -1;
    if(0x8A != pdu.msg[0] || 0xBC != pdu.msg[1] || 0xA5 != pdu.msg[2] || 0x5A != pdu.msg[3] ||
       0x00 != pdu.msg[4] || 0x00 != pdu.msg[5] || 0x00 != pdu.msg[6] || 0x00 != pdu.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_rn_user_plane_data_pdu(&pdu, &contents))
        return -1;
    if(contents.count != 0xABC || contents.data.N_bytes != 2 ||
       contents.data.msg[0] != 0xA5 || contents.data.msg[1] != 0x5A)
        return -1;
    return 0;
}

int rupdp_format_2_test(void)
{
    LIBLTE_PDCP_RN_USER_PLANE_DATA_PDU_STRUCT contents;
    contents.count = 0xABC;
    LIBLTE_BYTE_MSG_STRUCT data;
    data.N_bytes = 2;
    data.msg[0] = 0xA5;
    data.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_rn_user_plane_data_pdu(&contents, &data, &pdu))
        return -1;
    if(8 != pdu.N_bytes)
        return -1;
    if(0x8A != pdu.msg[0] || 0xBC != pdu.msg[1] || 0xA5 != pdu.msg[2] || 0x5A != pdu.msg[3] ||
       0x00 != pdu.msg[4] || 0x00 != pdu.msg[5] || 0x00 != pdu.msg[6] || 0x00 != pdu.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_rn_user_plane_data_pdu(&pdu, &contents))
        return -1;
    if(contents.count != 0xABC || contents.data.N_bytes != 2 ||
       contents.data.msg[0] != 0xA5 || contents.data.msg[1] != 0x5A)
        return -1;
    return 0;
}

int rupdp_format_3_test(void)
{
    LIBLTE_PDCP_RN_USER_PLANE_DATA_PDU_STRUCT contents;
    contents.count = 0xABC;
    contents.data.N_bytes = 2;
    contents.data.msg[0] = 0xA5;
    contents.data.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    uint8 key[32];
    for(uint32 i=0; i<32; i++)
        key[i] = i;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_rn_user_plane_data_pdu(&contents, key,
                                                                 LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                 2, &pdu))
        return -1;
    if(8 != pdu.N_bytes)
        return -1;
    if(0x8A != pdu.msg[0] || 0xBC != pdu.msg[1] || 0xA5 != pdu.msg[2] || 0x5A != pdu.msg[3] ||
       0x37 != pdu.msg[4] || 0xB2 != pdu.msg[5] || 0x21 != pdu.msg[6] || 0xE2 != pdu.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_rn_user_plane_data_pdu(&pdu, &contents))
        return -1;
    if(contents.count != 0xABC || contents.data.N_bytes != 2 ||
       contents.data.msg[0] != 0xA5 || contents.data.msg[1] != 0x5A)
        return -1;
    return 0;
}

int rupdp_format_4_test(void)
{
    LIBLTE_PDCP_RN_USER_PLANE_DATA_PDU_STRUCT contents;
    contents.count = 0xABC;
    LIBLTE_BYTE_MSG_STRUCT data;
    data.N_bytes = 2;
    data.msg[0] = 0xA5;
    data.msg[1] = 0x5A;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    uint8 key[32];
    for(uint32 i=0; i<32; i++)
        key[i] = i;
    if(LIBLTE_SUCCESS != liblte_pdcp_pack_rn_user_plane_data_pdu(&contents, &data, key,
                                                                 LIBLTE_SECURITY_DIRECTION_DOWNLINK,
                                                                 2, &pdu))
        return -1;
    if(8 != pdu.N_bytes)
        return -1;
    if(0x8A != pdu.msg[0] || 0xBC != pdu.msg[1] || 0xA5 != pdu.msg[2] || 0x5A != pdu.msg[3] ||
       0x37 != pdu.msg[4] || 0xB2 != pdu.msg[5] || 0x21 != pdu.msg[6] || 0xE2 != pdu.msg[7])
        return -1;
    if(LIBLTE_SUCCESS != liblte_pdcp_unpack_rn_user_plane_data_pdu(&pdu, &contents))
        return -1;
    if(contents.count != 0xABC || contents.data.N_bytes != 2 ||
       contents.data.msg[0] != 0xA5 || contents.data.msg[1] != 0x5A)
        return -1;
    return 0;
}

int rn_user_plane_data_pdu_test(void)
{
    if(0 != rupdp_format_1_test())
        return -1;
    if(0 != rupdp_format_2_test())
        return -1;
    if(0 != rupdp_format_3_test())
        return -1;
    if(0 != rupdp_format_4_test())
        return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    printf("control_pdu_test: ");
    if(0 != control_pdu_test())
        exit(-1);
    printf("pass\n");
    printf("data_pdu_with_long_sn_test: ");
    if(0 != data_pdu_with_long_sn_test())
        exit(-1);
    printf("pass\n");
    printf("data_pdu_with_short_sn_test: ");
    if(0 != data_pdu_with_short_sn_test())
        exit(-1);
    printf("pass\n");
    printf("control_pdu_for_interspersed_rohc_feedback_test: ");
    if(0 != control_pdu_for_interspersed_rohc_feedback_test())
        exit(-1);
    printf("pass\n");
    printf("rn_user_plane_data_pdu_test: ");
    if(0 != rn_user_plane_data_pdu_test())
        exit(-1);
    printf("pass\n");
    exit(0);
}
