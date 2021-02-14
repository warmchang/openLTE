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

    File: liblte_security_tests.cc

    Description: Contains all the tests for the LTE security library.

    Revision History
    ----------    -------------    --------------------------------------------
    02/14/2021    Ben Wojtowicz    Created file.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

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

int generate_k_asme_test(void)
{
    uint8 ck[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8 ik[16] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    uint8 ak[6] = {0, 1, 2, 3, 4, 5};
    uint8 sqn[6] = {5, 4, 3, 2, 1, 0};
    uint8 k_asme[32];
    std::vector<MCC_MNC_Digit> mcc_digits(3);
    mcc_digits[0].SetValue(0);
    mcc_digits[1].SetValue(0);
    mcc_digits[2].SetValue(1);
    PLMN_IdentityInfo plmn_id;
    plmn_id.plmn_Identity_Set()->mcc_Set()->SetValue(mcc_digits);
    std::vector<MCC_MNC_Digit> mnc_digits(2);
    mnc_digits[0].SetValue(0);
    mnc_digits[1].SetValue(1);
    plmn_id.plmn_Identity_Set()->mnc_Set()->SetValue(mnc_digits);
    if(LIBLTE_SUCCESS != liblte_security_generate_k_asme(ck, ik, ak, sqn,
                                                         plmn_id.plmn_Identity_Get().mcc_Get(),
                                                         plmn_id.plmn_Identity_Get().mnc_Get(),
                                                         k_asme))
        return -1;
    if(k_asme[0] != 0xE9 || k_asme[1] != 0x42 || k_asme[2] != 0x85 || k_asme[3] != 0x3C ||
       k_asme[4] != 0x9F || k_asme[5] != 0x15 || k_asme[6] != 0x0C || k_asme[7] != 0x69 ||
       k_asme[8] != 0x79 || k_asme[9] != 0x84 || k_asme[10] != 0x3F || k_asme[11] != 0x4F ||
       k_asme[12] != 0x0B || k_asme[13] != 0x1D || k_asme[14] != 0xC2 || k_asme[15] != 0x6F ||
       k_asme[16] != 0x77 || k_asme[17] != 0xA0 || k_asme[18] != 0xED || k_asme[19] != 0x68 ||
       k_asme[20] != 0xF3 || k_asme[21] != 0xE2 || k_asme[22] != 0x29 || k_asme[23] != 0x6D ||
       k_asme[24] != 0x42 || k_asme[25] != 0x31 || k_asme[26] != 0xCC || k_asme[27] != 0x7E ||
       k_asme[28] != 0xD3 || k_asme[29] != 0x63 || k_asme[30] != 0x05 || k_asme[31] != 0x07)
        return -1;
    return 0;
}

int generate_k_enb_test(void)
{
    uint8 k_asme[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    uint8 k_enb[32];
    if(LIBLTE_SUCCESS != liblte_security_generate_k_enb(k_asme, 0x12345678, k_enb))
        return -1;
    if(k_enb[0] != 0x04 || k_enb[1] != 0x06 || k_enb[2] != 0x8B || k_enb[3] != 0x4C ||
       k_enb[4] != 0x06 || k_enb[5] != 0x79 || k_enb[6] != 0x97 || k_enb[7] != 0x99 ||
       k_enb[8] != 0x55 || k_enb[9] != 0xFE || k_enb[10] != 0x1E || k_enb[11] != 0x2D ||
       k_enb[12] != 0x44 || k_enb[13] != 0x59 || k_enb[14] != 0x28 || k_enb[15] != 0x3A ||
       k_enb[16] != 0x5B || k_enb[17] != 0x8E || k_enb[18] != 0x9C || k_enb[19] != 0x41 ||
       k_enb[20] != 0x7C || k_enb[21] != 0x16 || k_enb[22] != 0x00 || k_enb[23] != 0x71 ||
       k_enb[24] != 0x75 || k_enb[25] != 0xA9 || k_enb[26] != 0x61 || k_enb[27] != 0x97 ||
       k_enb[28] != 0xEF || k_enb[29] != 0x31 || k_enb[30] != 0xEA || k_enb[31] != 0xE7)
        return -1;
    return 0;
}

int generate_k_nas_test(void)
{
    uint8 k_asme[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    uint8 k_nas_enc[32];
    uint8 k_nas_int[32];
    if(LIBLTE_SUCCESS != liblte_security_generate_k_nas(k_asme,
                                                        LIBLTE_SECURITY_CIPHERING_ALGORITHM_ID_128_EEA1,
                                                        LIBLTE_SECURITY_INTEGRITY_ALGORITHM_ID_128_EIA2,
                                                        k_nas_enc, k_nas_int))
        return -1;
    if(k_nas_enc[0] != 0x23 || k_nas_enc[1] != 0x60 || k_nas_enc[2] != 0xEC ||
       k_nas_enc[3] != 0x32 || k_nas_enc[4] != 0x92 || k_nas_enc[5] != 0xCB ||
       k_nas_enc[6] != 0x87 || k_nas_enc[7] != 0x7F || k_nas_enc[8] != 0xC5 ||
       k_nas_enc[9] != 0x36 || k_nas_enc[10] != 0x54 || k_nas_enc[11] != 0xA2 ||
       k_nas_enc[12] != 0x78 || k_nas_enc[13] != 0x90 || k_nas_enc[14] != 0xFB ||
       k_nas_enc[15] != 0xE9 || k_nas_enc[16] != 0x5F || k_nas_enc[17] != 0x44 ||
       k_nas_enc[18] != 0xAB || k_nas_enc[19] != 0x2E || k_nas_enc[20] != 0xF2 ||
       k_nas_enc[21] != 0xA4 || k_nas_enc[22] != 0xC4 || k_nas_enc[23] != 0x7D ||
       k_nas_enc[24] != 0x2D || k_nas_enc[25] != 0x69 || k_nas_enc[26] != 0x79 ||
       k_nas_enc[27] != 0xFA || k_nas_enc[28] != 0xF5 || k_nas_enc[29] != 0x18 ||
       k_nas_enc[30] != 0xE8 || k_nas_enc[31] != 0x73)
        return -1;
    if(k_nas_int[0] != 0xA6 || k_nas_int[1] != 0x6B || k_nas_int[2] != 0x74 ||
       k_nas_int[3] != 0x92 || k_nas_int[4] != 0xBD || k_nas_int[5] != 0xD6 ||
       k_nas_int[6] != 0x3F || k_nas_int[7] != 0x0E || k_nas_int[8] != 0x88 ||
       k_nas_int[9] != 0x96 || k_nas_int[10] != 0xA9 || k_nas_int[11] != 0x54 ||
       k_nas_int[12] != 0x29 || k_nas_int[13] != 0x30 || k_nas_int[14] != 0x25 ||
       k_nas_int[15] != 0x25 || k_nas_int[16] != 0xB5 || k_nas_int[17] != 0xA0 ||
       k_nas_int[18] != 0xE5 || k_nas_int[19] != 0xF9 || k_nas_int[20] != 0xEE ||
       k_nas_int[21] != 0x4F || k_nas_int[22] != 0x88 || k_nas_int[23] != 0x7E ||
       k_nas_int[24] != 0x39 || k_nas_int[25] != 0x1E || k_nas_int[26] != 0x3A ||
       k_nas_int[27] != 0x64 || k_nas_int[28] != 0x0E || k_nas_int[29] != 0x3A ||
       k_nas_int[30] != 0x68 || k_nas_int[31] != 0x8A)
        return -1;
    return 0;
}

int generate_k_rrc_test(void)
{
    uint8 k_asme[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    uint8 k_rrc_enc[32];
    uint8 k_rrc_int[32];
    if(LIBLTE_SUCCESS != liblte_security_generate_k_rrc(k_asme,
                                                        LIBLTE_SECURITY_CIPHERING_ALGORITHM_ID_128_EEA1,
                                                        LIBLTE_SECURITY_INTEGRITY_ALGORITHM_ID_128_EIA2,
                                                        k_rrc_enc, k_rrc_int))
        return -1;
    if(k_rrc_enc[0] != 0x26 || k_rrc_enc[1] != 0xD9 || k_rrc_enc[2] != 0xEC ||
       k_rrc_enc[3] != 0xDD || k_rrc_enc[4] != 0xFA || k_rrc_enc[5] != 0xF9 ||
       k_rrc_enc[6] != 0xB2 || k_rrc_enc[7] != 0xAF || k_rrc_enc[8] != 0x23 ||
       k_rrc_enc[9] != 0x1E || k_rrc_enc[10] != 0x43 || k_rrc_enc[11] != 0xE6 ||
       k_rrc_enc[12] != 0x2B || k_rrc_enc[13] != 0xC9 || k_rrc_enc[14] != 0x80 ||
       k_rrc_enc[15] != 0xFD || k_rrc_enc[16] != 0xFD || k_rrc_enc[17] != 0x7D ||
       k_rrc_enc[18] != 0x9A || k_rrc_enc[19] != 0xB3 || k_rrc_enc[20] != 0x0D ||
       k_rrc_enc[21] != 0xB1 || k_rrc_enc[22] != 0xAA || k_rrc_enc[23] != 0x91 ||
       k_rrc_enc[24] != 0x47 || k_rrc_enc[25] != 0xCB || k_rrc_enc[26] != 0x7F ||
       k_rrc_enc[27] != 0x94 || k_rrc_enc[28] != 0x5E || k_rrc_enc[29] != 0xD5 ||
       k_rrc_enc[30] != 0x54 || k_rrc_enc[31] != 0xCA)
        return -1;
    if(k_rrc_int[0] != 0xA2 || k_rrc_int[1] != 0x23 || k_rrc_int[2] != 0xB1 ||
       k_rrc_int[3] != 0x81 || k_rrc_int[4] != 0x16 || k_rrc_int[5] != 0x1B ||
       k_rrc_int[6] != 0x9D || k_rrc_int[7] != 0x48 || k_rrc_int[8] != 0xD2 ||
       k_rrc_int[9] != 0x4A || k_rrc_int[10] != 0xC4 || k_rrc_int[11] != 0x4A ||
       k_rrc_int[12] != 0xC5 || k_rrc_int[13] != 0xA6 || k_rrc_int[14] != 0xFA ||
       k_rrc_int[15] != 0xAB || k_rrc_int[16] != 0x36 || k_rrc_int[17] != 0xD0 ||
       k_rrc_int[18] != 0x56 || k_rrc_int[19] != 0x71 || k_rrc_int[20] != 0x13 ||
       k_rrc_int[21] != 0x74 || k_rrc_int[22] != 0x00 || k_rrc_int[23] != 0x5D ||
       k_rrc_int[24] != 0xC6 || k_rrc_int[25] != 0xD5 || k_rrc_int[26] != 0x65 ||
       k_rrc_int[27] != 0x6B || k_rrc_int[28] != 0x68 || k_rrc_int[29] != 0x09 ||
       k_rrc_int[30] != 0x35 || k_rrc_int[31] != 0x40)
        return -1;
    return 0;
}

int generate_k_up_test(void)
{
    uint8 k_asme[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    uint8 k_up_enc[32];
    uint8 k_up_int[32];
    if(LIBLTE_SUCCESS != liblte_security_generate_k_up(k_asme,
                                                       LIBLTE_SECURITY_CIPHERING_ALGORITHM_ID_128_EEA1,
                                                       LIBLTE_SECURITY_INTEGRITY_ALGORITHM_ID_128_EIA2,
                                                       k_up_enc, k_up_int))
        return -1;
    if(k_up_enc[0] != 0xD9 || k_up_enc[1] != 0x65 || k_up_enc[2] != 0xAA ||
       k_up_enc[3] != 0x6F || k_up_enc[4] != 0x64 || k_up_enc[5] != 0x38 ||
       k_up_enc[6] != 0x61 || k_up_enc[7] != 0x06 || k_up_enc[8] != 0x61 ||
       k_up_enc[9] != 0xBB || k_up_enc[10] != 0x8D || k_up_enc[11] != 0x9A ||
       k_up_enc[12] != 0x2B || k_up_enc[13] != 0x97 || k_up_enc[14] != 0x09 ||
       k_up_enc[15] != 0x66 || k_up_enc[16] != 0xCB || k_up_enc[17] != 0x20 ||
       k_up_enc[18] != 0x86 || k_up_enc[19] != 0x86 || k_up_enc[20] != 0x1A ||
       k_up_enc[21] != 0x44 || k_up_enc[22] != 0x15 || k_up_enc[23] != 0xB4 ||
       k_up_enc[24] != 0x3F || k_up_enc[25] != 0x92 || k_up_enc[26] != 0x37 ||
       k_up_enc[27] != 0x46 || k_up_enc[28] != 0x60 || k_up_enc[29] != 0x95 ||
       k_up_enc[30] != 0x01 || k_up_enc[31] != 0x94)
        return -1;
    if(k_up_int[0] != 0x8F || k_up_int[1] != 0x2B || k_up_int[2] != 0x00 ||
       k_up_int[3] != 0x89 || k_up_int[4] != 0xAB || k_up_int[5] != 0xBB ||
       k_up_int[6] != 0x02 || k_up_int[7] != 0xCA || k_up_int[8] != 0x63 ||
       k_up_int[9] != 0xA5 || k_up_int[10] != 0x9B || k_up_int[11] != 0xC2 ||
       k_up_int[12] != 0xE6 || k_up_int[13] != 0xF3 || k_up_int[14] != 0x0E ||
       k_up_int[15] != 0x29 || k_up_int[16] != 0x8C || k_up_int[17] != 0x2E ||
       k_up_int[18] != 0xCA || k_up_int[19] != 0x77 || k_up_int[20] != 0x7C ||
       k_up_int[21] != 0x60 || k_up_int[22] != 0xC9 || k_up_int[23] != 0x69 ||
       k_up_int[24] != 0x56 || k_up_int[25] != 0x90 || k_up_int[26] != 0x9D ||
       k_up_int[27] != 0xF2 || k_up_int[28] != 0x26 || k_up_int[29] != 0x64 ||
       k_up_int[30] != 0xD3 || k_up_int[31] != 0xB8)
        return -1;
    return 0;
}

int byte_128_eia2_test(void)
{
    uint8 key[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    LIBLTE_BIT_MSG_STRUCT msg;
    msg.N_bits = 100;
    for(uint32 i=0; i<msg.N_bits; i++)
        msg.msg[i] = i%2;
    uint8 mac[4];
    if(LIBLTE_SUCCESS != liblte_security_128_eia2(key, 0x12345678, 0x15, 0, &msg, mac))
        return -1;
    if(mac[0] != 0xE0 || mac[1] != 0x63 || mac[2] != 0x3A || mac[3] != 0x44)
        return -1;
    return 0;
}

int bit_128_eia2_test(void)
{
    uint8 key[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                     16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    uint8 msg[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8 mac[4];
    if(LIBLTE_SUCCESS != liblte_security_128_eia2(key, 0x12345678, 0x15, 0, msg, 16, mac))
        return -1;
    if(mac[0] != 0x13 || mac[1] != 0x4D || mac[2] != 0x4E || mac[3] != 0xCC)
        return -1;
    return 0;
}

int milenage_f1_test(void)
{
    uint8 key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8 rand[16] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    uint8 sqn[6] = {0, 1, 2, 3, 4, 5};
    uint8 amf[2] = {1, 0};
    uint8 mac_a[8];
    if(LIBLTE_SUCCESS != liblte_security_milenage_f1(key, rand, sqn, amf, mac_a))
        return -1;
    if(mac_a[0] != 0x84 || mac_a[1] != 0x19 || mac_a[2] != 0xCC || mac_a[3] != 0xB3 ||
       mac_a[4] != 0x56 || mac_a[5] != 0x5C || mac_a[6] != 0x3C || mac_a[7] != 0x8D)
        return -1;
    return 0;
}

int milenage_f1_star_test(void)
{
    uint8 key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8 rand[16] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    uint8 sqn[6] = {0, 1, 2, 3, 4, 5};
    uint8 amf[2] = {1, 0};
    uint8 mac_s[8];
    if(LIBLTE_SUCCESS != liblte_security_milenage_f1_star(key, rand, sqn, amf, mac_s))
        return -1;
    if(mac_s[0] != 0xCD || mac_s[1] != 0x46 || mac_s[2] != 0x57 || mac_s[3] != 0x92 ||
       mac_s[4] != 0x02 || mac_s[5] != 0xFB || mac_s[6] != 0x93 || mac_s[7] != 0x50)
        return -1;
    return 0;
}

int milenage_f2345_test(void)
{
    uint8 key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8 rand[16] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    uint8 res[8];
    uint8 ck[16];
    uint8 ik[16];
    uint8 ak[6];
    if(LIBLTE_SUCCESS != liblte_security_milenage_f2345(key, rand, res, ck, ik, ak))
        return -1;
    if(res[0] != 0x2A || res[1] != 0xC2 || res[2] != 0xFB || res[3] != 0x73 ||
       res[4] != 0xDA || res[5] != 0x7D || res[6] != 0x62 || res[7] != 0xEA)
        return -1;
    if(ck[0] != 0xF6 || ck[1] != 0xEE || ck[2] != 0x6C || ck[3] != 0x4B ||
       ck[4] != 0xA2 || ck[5] != 0xEA || ck[6] != 0x5D || ck[7] != 0x86 ||
       ck[8] != 0xB3 || ck[9] != 0x5F || ck[10] != 0x13 || ck[11] != 0x61 ||
       ck[12] != 0xCA || ck[13] != 0x4D || ck[14] != 0x4A || ck[15] != 0xE7)
        return -1;
    if(ik[0] != 0x7B || ik[1] != 0xA9 || ik[2] != 0xAA || ik[3] != 0xA6 ||
       ik[4] != 0x02 || ik[5] != 0x08 || ik[6] != 0xC6 || ik[7] != 0x41 ||
       ik[8] != 0x5B || ik[9] != 0x9C || ik[10] != 0xB5 || ik[11] != 0x8C ||
       ik[12] != 0x6C || ik[13] != 0xE2 || ik[14] != 0x13 || ik[15] != 0x91)
        return -1;
    if(ak[0] != 0x25 || ak[1] != 0x2E || ak[2] != 0xE0 || ak[3] != 0x26 ||
       ak[4] != 0xA6 || ak[5] != 0x20)
        return -1;
    return 0;
}

int milenage_f5_star_test(void)
{
    uint8 key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8 rand[16] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    uint8 ak[6];
    if(LIBLTE_SUCCESS != liblte_security_milenage_f5_star(key, rand, ak))
        return -1;
    if(ak[0] != 0xBD || ak[1] != 0x23 || ak[2] != 0x09 || ak[3] != 0xC1 ||
       ak[4] != 0x9E || ak[5] != 0xC4)
        return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    printf("generate_k_asme_test: ");
    if(0 != generate_k_asme_test())
        exit(-1);
    printf("pass\n");
    printf("generate_k_enb_test: ");
    if(0 != generate_k_enb_test())
        exit(-1);
    printf("pass\n");
    printf("generate_k_nas_test: ");
    if(0 != generate_k_nas_test())
        exit(-1);
    printf("pass\n");
    printf("generate_k_rrc_test: ");
    if(0 != generate_k_rrc_test())
        exit(-1);
    printf("pass\n");
    printf("generate_k_up_test: ");
    if(0 != generate_k_up_test())
        exit(-1);
    printf("pass\n");
    printf("byte_128_eia2_test: ");
    if(0 != byte_128_eia2_test())
        exit(-1);
    printf("pass\n");
    printf("bit_128_eia2_test: ");
    if(0 != bit_128_eia2_test())
        exit(-1);
    printf("pass\n");
    printf("milenage_f1_test: ");
    if(0 != milenage_f1_test())
        exit(-1);
    printf("pass\n");
    printf("milenage_f1_star_test: ");
    if(0 != milenage_f1_star_test())
        exit(-1);
    printf("pass\n");
    printf("milenage_f2345_test: ");
    if(0 != milenage_f2345_test())
        exit(-1);
    printf("pass\n");
    printf("milenage_f5_star_test: ");
    if(0 != milenage_f5_star_test())
        exit(-1);
    printf("pass\n");
    exit(0);
}
