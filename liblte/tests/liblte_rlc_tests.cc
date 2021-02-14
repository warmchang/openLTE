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

    File: liblte_rlc_tests.cc

    Description: Contains all the tests for the LTE RLC library.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_rlc.h"

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

int umd_pdu_test(void)
{
    LIBLTE_RLC_UMD_PDU_STRUCT umd;
    umd.hdr.fi = LIBLTE_RLC_FI_FIELD_FULL_SDU;
    umd.hdr.sn_size = LIBLTE_RLC_UMD_SN_SIZE_5_BITS;
    umd.hdr.sn = 1;
    umd.N_data = 1;
    umd.data[0].N_bytes = 8;
    umd.data[0].msg[0] = 0x01;
    umd.data[0].msg[1] = 0x23;
    umd.data[0].msg[2] = 0x45;
    umd.data[0].msg[3] = 0x67;
    umd.data[0].msg[4] = 0x89;
    umd.data[0].msg[5] = 0xAB;
    umd.data[0].msg[6] = 0xCD;
    umd.data[0].msg[7] = 0xEF;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_rlc_pack_umd_pdu(&umd, &pdu))
        return -1;
    if(pdu.N_bytes != 9)
        return -1;
    if(pdu.msg[0] != 0x01 || pdu.msg[1] != 0x01 || pdu.msg[2] != 0x23 || pdu.msg[3] != 0x45 ||
       pdu.msg[4] != 0x67 || pdu.msg[5] != 0x89 || pdu.msg[6] != 0xAB || pdu.msg[7] != 0xCD ||
       pdu.msg[8] != 0xEF)
        return -1;
    if(LIBLTE_SUCCESS != liblte_rlc_unpack_umd_pdu(&pdu, &umd))
        return -1;
    if(umd.hdr.fi != LIBLTE_RLC_FI_FIELD_FULL_SDU ||
       umd.hdr.sn_size != LIBLTE_RLC_UMD_SN_SIZE_5_BITS || umd.hdr.sn != 1 ||
       umd.N_data != 1 || umd.data[0].N_bytes != 8 || umd.data[0].msg[0] != 0x01 ||
       umd.data[0].msg[1] != 0x23 || umd.data[0].msg[2] != 0x45 || umd.data[0].msg[3] != 0x67 ||
       umd.data[0].msg[4] != 0x89 || umd.data[0].msg[5] != 0xAB || umd.data[0].msg[6] != 0xCD ||
       umd.data[0].msg[7] != 0xEF)
        return -1;
    umd.N_data = 2;
    umd.data[1].N_bytes = 8;
    umd.data[1].msg[0] = 0xFE;
    umd.data[1].msg[1] = 0xDC;
    umd.data[1].msg[2] = 0xBA;
    umd.data[1].msg[3] = 0x98;
    umd.data[1].msg[4] = 0x76;
    umd.data[1].msg[5] = 0x54;
    umd.data[1].msg[6] = 0x32;
    umd.data[1].msg[7] = 0x10;
    if(LIBLTE_SUCCESS != liblte_rlc_pack_umd_pdu(&umd, &pdu))
        return -1;
    if(pdu.N_bytes != 19)
        return -1;
    if(pdu.msg[0] != 0x21 || pdu.msg[1] != 0x00 || pdu.msg[2] != 0x80 || pdu.msg[3] != 0x01 ||
       pdu.msg[4] != 0x23 || pdu.msg[5] != 0x45 || pdu.msg[6] != 0x67 || pdu.msg[7] != 0x89 ||
       pdu.msg[8] != 0xAB || pdu.msg[9] != 0xCD || pdu.msg[10] != 0xEF ||
       pdu.msg[11] != 0xFE || pdu.msg[12] != 0xDC || pdu.msg[13] != 0xBA ||
       pdu.msg[14] != 0x98 || pdu.msg[15] != 0x76 || pdu.msg[16] != 0x54 ||
       pdu.msg[17] != 0x32 || pdu.msg[18] != 0x10)
        return -1;
    if(LIBLTE_SUCCESS != liblte_rlc_unpack_umd_pdu(&pdu, &umd))
        return -1;
    if(umd.hdr.fi != LIBLTE_RLC_FI_FIELD_FULL_SDU ||
       umd.hdr.sn_size != LIBLTE_RLC_UMD_SN_SIZE_5_BITS || umd.hdr.sn != 1 ||
       umd.N_data != 2 || umd.data[0].N_bytes != 8 || umd.data[0].msg[0] != 0x01 ||
       umd.data[0].msg[1] != 0x23 || umd.data[0].msg[2] != 0x45 || umd.data[0].msg[3] != 0x67 ||
       umd.data[0].msg[4] != 0x89 || umd.data[0].msg[5] != 0xAB || umd.data[0].msg[6] != 0xCD ||
       umd.data[0].msg[7] != 0xEF || umd.data[1].N_bytes != 8 || umd.data[1].msg[0] != 0xFE ||
       umd.data[1].msg[1] != 0xDC || umd.data[1].msg[2] != 0xBA || umd.data[1].msg[3] != 0x98 ||
       umd.data[1].msg[4] != 0x76 || umd.data[1].msg[5] != 0x54 || umd.data[1].msg[6] != 0x32 ||
       umd.data[1].msg[7] != 0x10)
        return -1;
    return 0;
}

int amd_pdu_test(void)
{
    LIBLTE_RLC_AMD_PDUS_STRUCT amd;
    amd.N_pdu = 1;
    amd.pdu[0].hdr.dc = LIBLTE_RLC_DC_FIELD_DATA_PDU;
    amd.pdu[0].hdr.rf = LIBLTE_RLC_RF_FIELD_AMD_PDU;
    amd.pdu[0].hdr.p = LIBLTE_RLC_P_FIELD_STATUS_REPORT_REQUESTED;
    amd.pdu[0].hdr.fi = LIBLTE_RLC_FI_FIELD_FULL_SDU;
    amd.pdu[0].hdr.lsf = LIBLTE_RLC_LSF_FIELD_NOT_LAST_SEGMENT;
    amd.pdu[0].hdr.sn = 4;
    amd.pdu[0].hdr.so = 1;
    amd.pdu[0].data.N_bytes = 8;
    amd.pdu[0].data.msg[0] = 0x01;
    amd.pdu[0].data.msg[1] = 0x23;
    amd.pdu[0].data.msg[2] = 0x45;
    amd.pdu[0].data.msg[3] = 0x67;
    amd.pdu[0].data.msg[4] = 0x89;
    amd.pdu[0].data.msg[5] = 0xAB;
    amd.pdu[0].data.msg[6] = 0xCD;
    amd.pdu[0].data.msg[7] = 0xEF;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_rlc_pack_amd_pdu(&amd, &pdu))
        return -1;
    if(pdu.N_bytes != 10)
        return -1;
    if(pdu.msg[0] != 0xA0 || pdu.msg[1] != 0x04 || pdu.msg[2] != 0x01 || pdu.msg[3] != 0x23 ||
       pdu.msg[4] != 0x45 || pdu.msg[5] != 0x67 || pdu.msg[6] != 0x89 || pdu.msg[7] != 0xAB ||
       pdu.msg[8] != 0xCD || pdu.msg[9] != 0xEF)
        return -1;
    if(LIBLTE_SUCCESS != liblte_rlc_unpack_amd_pdu(&pdu, &amd))
        return -1;
    if(amd.N_pdu != 1 || amd.pdu[0].hdr.dc != LIBLTE_RLC_DC_FIELD_DATA_PDU ||
       amd.pdu[0].hdr.rf != LIBLTE_RLC_RF_FIELD_AMD_PDU ||
       amd.pdu[0].hdr.p != LIBLTE_RLC_P_FIELD_STATUS_REPORT_REQUESTED ||
       amd.pdu[0].hdr.fi != LIBLTE_RLC_FI_FIELD_FULL_SDU ||
       amd.pdu[0].hdr.lsf != LIBLTE_RLC_LSF_FIELD_NOT_LAST_SEGMENT ||
       amd.pdu[0].hdr.sn != 4 || amd.pdu[0].hdr.so != 1 ||
       amd.pdu[0].data.N_bytes != 8 || amd.pdu[0].data.msg[0] != 0x01 ||
       amd.pdu[0].data.msg[1] != 0x23 || amd.pdu[0].data.msg[2] != 0x45 ||
       amd.pdu[0].data.msg[3] != 0x67 || amd.pdu[0].data.msg[4] != 0x89 ||
       amd.pdu[0].data.msg[5] != 0xAB || amd.pdu[0].data.msg[6] != 0xCD ||
       amd.pdu[0].data.msg[7] != 0xEF)
        return -1;
    amd.N_pdu = 2;
    amd.pdu[1].data.N_bytes = 8;
    amd.pdu[1].data.msg[0] = 0xFE;
    amd.pdu[1].data.msg[1] = 0xDC;
    amd.pdu[1].data.msg[2] = 0xBA;
    amd.pdu[1].data.msg[3] = 0x98;
    amd.pdu[1].data.msg[4] = 0x76;
    amd.pdu[1].data.msg[5] = 0x54;
    amd.pdu[1].data.msg[6] = 0x32;
    amd.pdu[1].data.msg[7] = 0x10;
    if(LIBLTE_SUCCESS != liblte_rlc_pack_amd_pdu(&amd, &pdu))
        return -1;
    if(pdu.N_bytes != 20)
        return -1;
    if(pdu.msg[0] != 0xA4 || pdu.msg[1] != 0x04 || pdu.msg[2] != 0x00 || pdu.msg[3] != 0x80 ||
       pdu.msg[4] != 0x01 || pdu.msg[5] != 0x23 || pdu.msg[6] != 0x45 || pdu.msg[7] != 0x67 ||
       pdu.msg[8] != 0x89 || pdu.msg[9] != 0xAB || pdu.msg[10] != 0xCD || pdu.msg[11] != 0xEF ||
       pdu.msg[12] != 0xFE || pdu.msg[13] != 0xDC || pdu.msg[14] != 0xBA ||
       pdu.msg[15] != 0x98 || pdu.msg[16] != 0x76 || pdu.msg[17] != 0x54 ||
       pdu.msg[18] != 0x32 || pdu.msg[19] != 0x10)
        return -1;
    if(LIBLTE_SUCCESS != liblte_rlc_unpack_amd_pdu(&pdu, &amd))
        return -1;
    if(amd.N_pdu != 2 || amd.pdu[0].hdr.dc != LIBLTE_RLC_DC_FIELD_DATA_PDU ||
       amd.pdu[0].hdr.rf != LIBLTE_RLC_RF_FIELD_AMD_PDU ||
       amd.pdu[0].hdr.p != LIBLTE_RLC_P_FIELD_STATUS_REPORT_REQUESTED ||
       amd.pdu[0].hdr.fi != LIBLTE_RLC_FI_FIELD_FULL_SDU ||
       amd.pdu[0].hdr.lsf != LIBLTE_RLC_LSF_FIELD_NOT_LAST_SEGMENT ||
       amd.pdu[0].hdr.sn != 4 || amd.pdu[0].hdr.so != 1 ||
       amd.pdu[0].data.N_bytes != 8 || amd.pdu[0].data.msg[0] != 0x01 ||
       amd.pdu[0].data.msg[1] != 0x23 || amd.pdu[0].data.msg[2] != 0x45 ||
       amd.pdu[0].data.msg[3] != 0x67 || amd.pdu[0].data.msg[4] != 0x89 ||
       amd.pdu[0].data.msg[5] != 0xAB || amd.pdu[0].data.msg[6] != 0xCD ||
       amd.pdu[0].data.msg[7] != 0xEF ||
       amd.pdu[1].hdr.dc != LIBLTE_RLC_DC_FIELD_DATA_PDU ||
       amd.pdu[1].hdr.rf != LIBLTE_RLC_RF_FIELD_AMD_PDU ||
       amd.pdu[1].hdr.p != LIBLTE_RLC_P_FIELD_STATUS_REPORT_REQUESTED ||
       amd.pdu[1].hdr.fi != LIBLTE_RLC_FI_FIELD_FULL_SDU ||
       amd.pdu[1].hdr.lsf != LIBLTE_RLC_LSF_FIELD_NOT_LAST_SEGMENT ||
       amd.pdu[1].hdr.sn != 4 || amd.pdu[1].hdr.so != 1 ||
       amd.pdu[1].data.N_bytes != 8 || amd.pdu[1].data.msg[0] != 0xFE ||
       amd.pdu[1].data.msg[1] != 0xDC || amd.pdu[1].data.msg[2] != 0xBA ||
       amd.pdu[1].data.msg[3] != 0x98 || amd.pdu[1].data.msg[4] != 0x76 ||
       amd.pdu[1].data.msg[5] != 0x54 || amd.pdu[1].data.msg[6] != 0x32 ||
       amd.pdu[1].data.msg[7] != 0x10)
        return -1;
    return 0;
}

int status_pdu_test(void)
{
    LIBLTE_RLC_STATUS_PDU_STRUCT status;
    status.N_nack = 1;
    status.ack_sn = 15;
    status.nack_sn[0] = 4;
    LIBLTE_BYTE_MSG_STRUCT pdu;
    if(LIBLTE_SUCCESS != liblte_rlc_pack_status_pdu(&status, &pdu))
        return -1;
    if(pdu.N_bytes != 4)
        return -1;
    if(pdu.msg[0] != 0x00 || pdu.msg[1] != 0x3E || pdu.msg[2] != 0x02 || pdu.msg[3] != 0x00)
        return -1;
    if(LIBLTE_SUCCESS != liblte_rlc_unpack_status_pdu(&pdu, &status))
        return -1;
    if(status.N_nack != 1 || status.ack_sn != 15 || status.nack_sn[0] != 4)
        return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    printf("umd_pdu_test: ");
    if(0 != umd_pdu_test())
        exit(-1);
    printf("pass\n");
    printf("amd_pdu_test: ");
    if(0 != amd_pdu_test())
        exit(-1);
    printf("pass\n");
    printf("status_pdu_test: ");
    if(0 != status_pdu_test())
        exit(-1);
    printf("pass\n");
    exit(0);
}
