/*******************************************************************************

    Copyright 2012-2017, 2021 Ben Wojtowicz
    Copyright 2014 Andrew Murphy (DCI 1C Unpack)

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

    File: liblte_phy.cc

    Description: Contains all the implementations for the LTE Physical Layer
                 library.

    Revision History
    ----------    -------------    --------------------------------------------
    02/26/2012    Ben Wojtowicz    Created file.
    04/25/2012    Ben Wojtowicz    Added Turbo encode/decode and PDSCH decode
    05/06/2012    Ben Wojtowicz    Fixed bugs in find_pss_and_fine_timing and
                                   find_sss (thanks Joel!!)
    05/13/2012    Ben Wojtowicz    Fixed a bug with frame_start_idx going
                                   negative in find_sss (thanks again Joel!!)
    06/02/2012    Ben Wojtowicz    Added more DL transmit functionality,
                                   rearranged to match the specs, and fixed
                                   several bugs: 1) frame_start_idx going
                                   negative, 2) PDCCH sizes were too small, 3)
                                   PDCCH reg calculation was wrong, 4) rate
                                   match/unmatch bit packing.
    06/09/2012    Ben Wojtowicz    Fixed several bugs in turbo_decode,
                                   rate_unmatch_turbo, pdsch_channel_encode,
                                   and pdcch_channel_encode.
    06/11/2012    Ben Wojtowicz    Added padding of dlsch inputs to TBS sizes.
                                   Added BER tolerance for CFI decoding.  Fixed
                                   various other bugs.  Enabled fftw input,
                                   output, and plan in phy_struct.
    08/19/2012    Ben Wojtowicz    Fixed a bug in the PDCCH decoder.
    10/06/2012    Ben Wojtowicz    Added random access and paging PDCCH
                                   decoding, soft turbo decoding, and PDSCH
                                   decoding per allocation.
    11/10/2012    Ben Wojtowicz    Added TBS, MCS, and N_prb calculations for
                                   SI PDSCH messages, added more sample defines,
                                   and re-factored the coarse timing and freq
                                   search to find more than 1 eNB.
    12/01/2012    Ben Wojtowicz    Added the ability to preconfigure CRS, fixed
                                   decoding of 4 antennas, optimized prs
                                   generation.
    12/26/2012    Ben Wojtowicz    Started supporting N_sc_rb for normal and
                                   extended CP, fixed several FIXMEs, and fixed
                                   an indexing error in PHICH mapping.
    03/03/2013    Ben Wojtowicz    Added support for multiple sampling rates,
                                   pre-permutation of PDCCH encoding, integer
                                   frequency offset detection, a phase wrapping
                                   routine, configurable N_slots for the
                                   find_coarse_timing_and_freq_offset routine,
                                   and fixed a phase wrapping bug in
                                   get_subframe_and_ce.
    03/17/2013    Ben Wojtowicz    Moved to single float version of fftw.
    07/03/2013    Ben Wojtowicz    Fixed two indexing bugs.
    07/21/2013    Ben Wojtowicz    Added routines for determining TBS, MCS,
                                   N_prb, and N_cce.
    08/26/2013    Ben Wojtowicz    Added PRACH generation and detection support
                                   and changed ambiguous routines/variables to
                                   be non-ambiguous.
    09/16/2013    Ben Wojtowicz    Implemented routines for determining TBS,
                                   MCS, N_prb, and N_cce.  Fixed a bug in the
                                   RIV calculation of dci_1a_unpack.
    11/13/2013    Ben Wojtowicz    Started adding PUSCH functionality.
    01/18/2014    Ben Wojtowicz    Optimization of PDSCH mapping/de-mapping and
                                   several bug fixes: PRACH detector, PDCCH
                                   PRACH processing, RIVs larger than 1/2
                                   N_rb_dl, normalization of single antenna case
                                   in pre_decoder_and_matched_filter, coding
                                   rate in get_tbs_mcs_and_n_prb_for_dl, N_REs
                                   in get_num_bits_in_prb.
    03/05/2014    Andrew Murphy    Added DCI 1C unpack.
    03/26/2014    Ben Wojtowicz    Added PUSCH functionality.
    04/12/2014    Ben Wojtowicz    Pulled in a patch from Astrasel to initialize
                                   the frequency offset estimate array in
                                   dl_find_coarse_timing_and_freq_offset and
                                   added support for PRB allocation differences
                                   in each slot.
    05/04/2014    Ben Wojtowicz    Added PHICH support, C-RNTI support for
                                   DCIs, and seperated PHICH and PCFICH from
                                   PDCCH encode/decode.
    06/15/2014    Ben Wojtowicz    Added DCI 0 packing and proper support for
                                   transmission of more than one CCE in PDCCH.
    07/22/2014    Ben Wojtowicz    Pulled in a patch from Mike Peters to fix
                                   an uninitialized N_bits value.
    08/03/2014    Ben Wojtowicz    Using the common value_2_bits and
                                   bits_2_value functions.
    11/29/2014    Ben Wojtowicz    Using the common liblte_value_2_bits and
                                   liblte_bits_2_value functions.
    12/24/2014    Ben Wojtowicz    Added C-RNTI support to
                                   get_tbs_mcs_and_N_prb_for_dl.
    02/15/2015    Ben Wojtowicz    Properly handling modulation schemes and
                                   added 16QAM and 64QAM demapping.
    03/11/2015    Ben Wojtowicz    Fixed I_tbs to mcs conversion for PUSCH.
    07/25/2015    Ben Wojtowicz    Added an error return for dci_1a_unpack
                                   (thanks to Joel Carlson for the suggestion),
                                   properly initializing vd_w_metric (thanks
                                   ziminghe for finding this), an changed the
                                   upper limit of PUSCH allocations to 10 PRBs
                                   for performance reasons.
    12/06/2015    Ben Wojtowicz    Added a return to liblte_phy_get_n_cce,
                                   thanks to Damian Jarek for reporting this.
    02/13/2016    Ben Wojtowicz    Moved turbo coder rate match/unmatch and
                                   code block segmentation/desegmentation to
                                   globally available routines to support unit
                                   tests and incorporated changes from Ziming
                                   He for better PBCH detection.
    03/12/2016    Ben Wojtowicz    Added PUCCH channel decode support.
    03/26/2016    Ben Wojtowicz    Fixed the calculation of n_prime_p in
                                   generate_dmrs_pucch.
    07/03/2016    Ben Wojtowicz    Added an error return to dci_1c_unpack, using
                                   new PDCCH size defines, and clearing
                                   punctured turbo decode bits before decoding.
    12/18/2016    Ben Wojtowicz    Fixed turbo encode tail bits (thanks to
                                   Laurent Louf and Jeremy Quirke).
    07/29/2017    Ben Wojtowicz    Added two codeword support, refactored PUCCH
                                   channel decoding for PUCCH types, 1, 1A, and
                                   1B, and added a function to map SR
                                   configuration index.
    02/14/2021    Ben Wojtowicz    Massive reformat, using the new RRC library,
                                   using complex, improved turbo decoder, added
                                   PUCCH format 1/1a/1b encoder, added UL
                                   subframe creator, added TBS/MCS helper, and
                                   added TTI math helpers.

*******************************************************************************/

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "liblte_phy.h"
#include "liblte_mac.h"
#include <math.h>

/*******************************************************************************
                              DEFINES
*******************************************************************************/

#define N_SYMB_DL_NORMAL_CP 7

/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              GLOBAL VARIABLES
*******************************************************************************/

// Orthogonal sequences for PUCCH from 3GPP TS 36.211 v10.1.0 table 5.4.1-2
int32 W_5_4_1_2[3][4] = {{ 1,  1,  1,  1},
                         { 1, -1,  1, -1},
                         { 1, -1, -1,  1}};

// UL reference signal phi value for M_sc_rs = N_sc_rb_ul from 3GPP TS 36.211 v10.1.0 table 5.5.1.2-1
int32 UL_RS_5_5_1_2_1[30][12] = {{-1, 1, 3,-3, 3, 3, 1, 1, 3, 1,-3, 3},
                                 { 1, 1, 3, 3, 3,-1, 1,-3,-3, 1,-3, 3},
                                 { 1, 1,-3,-3,-3,-1,-3,-3, 1,-3, 1,-1},
                                 {-1, 1, 1, 1, 1,-1,-3,-3, 1,-3, 3,-1},
                                 {-1, 3, 1,-1, 1,-1,-3,-1, 1,-1, 1, 3},
                                 { 1,-3, 3,-1,-1, 1, 1,-1,-1, 3,-3, 1},
                                 {-1, 3,-3,-3,-3, 3, 1,-1, 3, 3,-3, 1},
                                 {-3,-1,-1,-1, 1,-3, 3,-1, 1,-3, 3, 1},
                                 { 1,-3, 3, 1,-1,-1,-1, 1, 1, 3,-1, 1},
                                 { 1,-3,-1, 3, 3,-1,-3, 1, 1, 1, 1, 1},
                                 {-1, 3,-1, 1, 1,-3,-3,-1,-3,-3, 3,-1},
                                 { 3, 1,-1,-1, 3, 3,-3, 1, 3, 1, 3, 3},
                                 { 1,-3, 1, 1,-3, 1, 1, 1,-3,-3,-3, 1},
                                 { 3, 3,-3, 3,-3, 1, 1, 3,-1,-3, 3, 3},
                                 {-3, 1,-1,-3,-1, 3, 1, 3, 3, 3,-1, 1},
                                 { 3,-1, 1,-3,-1,-1, 1, 1, 3, 1,-1,-3},
                                 { 1, 3, 1,-1, 1, 3, 3, 3,-1,-1, 3,-1},
                                 {-3, 1, 1, 3,-3, 3,-3,-3, 3, 1, 3,-1},
                                 {-3, 3, 1, 1,-3, 1,-3,-3,-1,-1, 1,-3},
                                 {-1, 3, 1, 3, 1,-1,-1, 3,-3,-1,-3,-1},
                                 {-1,-3, 1, 1, 1, 1, 3, 1,-1, 1,-3,-1},
                                 {-1, 3,-1, 1,-3,-3,-3,-3,-3, 1,-1,-3},
                                 { 1, 1,-3,-3,-3,-3,-1, 3,-3, 1,-3, 3},
                                 { 1, 1,-1,-3,-1,-3, 1,-1, 1, 3,-1, 1},
                                 { 1, 1, 3, 1, 3, 3,-1, 1,-1,-3,-3, 1},
                                 { 1,-3, 3, 3, 1, 3, 3, 1,-3,-1,-1, 3},
                                 { 1, 3,-3,-3, 3,-3, 1,-1,-1, 3,-1,-3},
                                 {-3,-1,-3,-1,-3, 3, 1,-1, 1, 3,-3,-3},
                                 {-1, 3,-3, 3,-1, 3, 3,-3, 3, 3,-1,-1},
                                 { 3,-3,-3,-1,-1,-3,-1, 3,-3, 3, 1,-1}};

// UL reference signal phi value for M_sc_rs = 2*N_sc_rb_ul from 3GPP TS 36.211 v10.1.0 table 5.5.1.2-2
int32 UL_RS_5_5_1_2_2[30][24] = {{-1, 3, 1,-3, 3,-1, 1, 3,-3, 3, 1, 3,-3, 3, 1, 1,-1, 1, 3,-3, 3,-3,-1,-3},
                                 {-3, 3,-3,-3,-3, 1,-3,-3, 3,-1, 1, 1, 1, 3, 1,-1, 3,-3,-3, 1, 3, 1, 1,-3},
                                 { 3,-1, 3, 3, 1, 1,-3, 3, 3, 3, 3, 1,-1, 3,-1, 1, 1,-1,-3,-1,-1, 1, 3, 3},
                                 {-1,-3, 1, 1, 3,-3, 1, 1,-3,-1,-1, 1, 3, 1, 3, 1,-1, 3, 1, 1,-3,-1,-3,-1},
                                 {-1,-1,-1,-3,-3,-1, 1, 1, 3, 3,-1, 3,-1, 1,-1,-3, 1,-1,-3,-3, 1,-3,-1,-1},
                                 {-3, 1, 1, 3,-1, 1, 3, 1,-3, 1,-3, 1, 1,-1,-1, 3,-1,-3, 3,-3,-3,-3, 1, 1},
                                 { 1, 1,-1,-1, 3,-3,-3, 3,-3, 1,-1,-1, 1,-1, 1, 1,-1,-3,-1, 1,-1, 3,-1,-3},
                                 {-3, 3, 3,-1,-1,-3,-1, 3, 1, 3, 1, 3, 1, 1,-1, 3, 1,-1, 1, 3,-3,-1,-1, 1},
                                 {-3, 1, 3,-3, 1,-1,-3, 3,-3, 3,-1,-1,-1,-1, 1,-3,-3,-3, 1,-3,-3,-3, 1,-3},
                                 { 1, 1,-3, 3, 3,-1,-3,-1, 3,-3, 3, 3, 3,-1, 1, 1,-3, 1,-1, 1, 1,-3, 1, 1},
                                 {-1, 1,-3,-3, 3,-1, 3,-1,-1,-3,-3,-3,-1,-3,-3, 1,-1, 1, 3, 3,-1, 1,-1, 3},
                                 { 1, 3, 3,-3,-3, 1, 3, 1,-1,-3,-3,-3, 3, 3,-3, 3, 3,-1,-3, 3,-1, 1,-3, 1},
                                 { 1, 3, 3, 1, 1, 1,-1,-1, 1,-3, 3,-1, 1, 1,-3, 3, 3,-1,-3, 3,-3,-1,-3,-1},
                                 { 3,-1,-1,-1,-1,-3,-1, 3, 3, 1,-1, 1, 3, 3, 3,-1, 1, 1,-3, 1, 3,-1,-3, 3},
                                 {-3,-3, 3, 1, 3, 1,-3, 3, 1, 3, 1, 1, 3, 3,-1,-1,-3, 1,-3,-1, 3, 1, 1, 3},
                                 {-1,-1, 1,-3, 1, 3,-3, 1,-1,-3,-1, 3, 1, 3, 1,-1,-3,-3,-1,-1,-3,-3,-3,-1},
                                 {-1,-3, 3,-1,-1,-1,-1, 1, 1,-3, 3, 1, 3, 3, 1,-1, 1,-3, 1,-3, 1, 1,-3,-1},
                                 { 1, 3,-1, 3, 3,-1,-3, 1,-1,-3, 3, 3, 3,-1, 1, 1, 3,-1,-3,-1, 3,-1,-1,-1},
                                 { 1, 1, 1, 1, 1,-1, 3,-1,-3, 1, 1, 3,-3, 1,-3,-1, 1, 1,-3,-3, 3, 1, 1,-3},
                                 { 1, 3, 3, 1,-1,-3, 3,-1, 3, 3, 3,-3, 1,-1, 1,-1,-3,-1, 1, 3,-1, 3,-3,-3},
                                 {-1,-3, 3,-3,-3,-3,-1,-1,-3,-1,-3, 3, 1, 3,-3,-1, 3,-1, 1,-1, 3,-3, 1,-1},
                                 {-3,-3, 1, 1,-1, 1,-1, 1,-1, 3, 1,-3,-1, 1,-1, 1,-1,-1, 3, 3,-3,-1, 1,-3},
                                 {-3,-1,-3, 3, 1,-1,-3,-1,-3,-3, 3,-3, 3,-3,-1, 1, 3, 1,-3, 1, 3, 3,-1,-3},
                                 {-1,-1,-1,-1, 3, 3, 3, 1, 3, 3,-3, 1, 3,-1, 3,-1, 3, 3,-3, 3, 1,-1, 3, 3},
                                 { 1,-1, 3, 3,-1,-3, 3,-3,-1,-1, 3,-1, 3,-1,-1, 1, 1, 1, 1,-1,-1,-3,-1, 3},
                                 { 1,-1, 1,-1, 3,-1, 3, 1, 1,-1,-1,-3, 1, 1,-3, 1, 3,-3, 1, 1,-3,-3,-1,-1},
                                 {-3,-1, 1, 3, 1, 1,-3,-1,-1,-3, 3,-3, 3, 1,-3, 3,-3, 1,-1, 1,-3, 1, 1, 1},
                                 {-1,-3, 3, 3, 1, 1, 3,-1,-3,-1,-1,-1, 3, 1,-3,-3,-1, 3,-3,-1,-3,-1,-3,-1},
                                 {-1,-3,-1,-1, 1,-3,-1,-1, 1,-1,-3, 1, 1,-3, 1,-3,-3, 3, 1, 1,-1, 3,-1,-1},
                                 { 1, 1,-1,-1,-3,-1, 3,-1, 3,-1, 1, 3, 1,-1, 3, 1, 3,-3,-3, 1,-1,-1, 1, 3}};

// UL reference signal prime numbers less than 2048 from 3GPP TS 36.211 v10.1.0 section 5.5.1.1
#define UL_RS_PRIMES_LESS_THAN_2048_LEN 309
uint32 UL_RS_PRIMES_LESS_THAN_2048[UL_RS_PRIMES_LESS_THAN_2048_LEN] = {   2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
                                                                         31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
                                                                         73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
                                                                        127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
                                                                        179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
                                                                        233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
                                                                        283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
                                                                        353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
                                                                        419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
                                                                        467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
                                                                        547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
                                                                        607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
                                                                        661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
                                                                        739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
                                                                        811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
                                                                        877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
                                                                        947, 953, 967, 971, 977, 983, 991, 997,1009,1013,
                                                                       1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,
                                                                       1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,
                                                                       1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,
                                                                       1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,
                                                                       1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,
                                                                       1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,
                                                                       1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,
                                                                       1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,
                                                                       1597,1601,1607,1609,1613,1619,1621,1627,1637,1657,
                                                                       1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,
                                                                       1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,
                                                                       1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,
                                                                       1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,
                                                                       1993,1997,1999,2003,2011,2017,2027,2029,2039};

// N_2_DMRS_LAMBDA table from 3GPP TS 36.211 v10.1.0 table 5.5.2.1.1-1
uint32 N_2_DMRS_LAMBDA_5_5_2_1_1_1[8][4] = {{ 0, 6, 3, 9},
                                            { 6, 0, 9, 3},
                                            { 3, 9, 6, 0},
                                            { 4,10, 7, 1},
                                            { 2, 8, 5,11},
                                            { 8, 2,11, 5},
                                            {10, 4, 1, 7},
                                            { 9, 3, 0, 6}};

// W table from 3GPP TS 36.211 v10.1.0 table 5.5.2.1.1-1
int32 W_1_5_5_2_1_1_1[8][4] = {{ 1, 1,-1,-1},
                               {-1,-1, 1, 1},
                               {-1,-1, 1, 1},
                               { 1, 1, 1, 1},
                               { 1, 1, 1, 1},
                               {-1,-1,-1,-1},
                               {-1,-1,-1,-1},
                               { 1, 1,-1,-1}};

// N_1_DMRS table from 3GPP TS 36.211 v10.1.0 table 5.5.2.1.1-2
uint32 N_1_DMRS_5_5_2_1_1_2[8] = {0,2,3,4,6,8,9,10};

// W table from 3GPP TS 36.211 v10.1.0 table 5.5.2.2.1-2
float W_5_5_2_2_1_2_phase[3][3] = {{0, 0, 0},
                                   {0, 2*M_PI/3, 4*M_PI/3},
                                   {0, 4*M_PI/3, 2*M_PI/3}};

// PRACH N_cs unrestricted set values from 3GPP TS 36.211 v10.1.0 table 5.7.2-2
uint32 PRACH_5_7_2_2_URS[16] = {0,13,15,18,22,26,32,38,46,59,76,93,119,167,279,419};

// PRACH N_cs restricted set values from 3GPP TS 36.211 v10.1.0 table 5.7.2-2
uint32 PRACH_5_7_2_2_RS[15] = {15,18,22,26,32,38,46,55,68,82,100,128,158,202,237};

// PRACH N_cs values from 3GPP TS 36.211 v10.1.0 table 5.7.2-3
uint32 PRACH_5_7_2_3[7] = {2,4,6,8,10,12,15};

// PRACH root Zadoff-Chu sequence values from 3GPP TS 36.211 v10.1.0 table 5.7.2-4
uint32 PRACH_5_7_2_4[838] = {129, 710, 140, 699, 120, 719, 210, 629, 168, 671,  84, 755,
                             105, 734,  93, 746,  70, 769,  60, 779,   2, 837,   1, 838,
                              56, 783, 112, 727, 148, 691,  80, 759,  42, 797,  40, 799,
                              35, 804,  73, 766, 146, 693,  31, 808,  28, 811,  30, 809,
                              27, 812,  29, 810,  24, 815,  48, 791,  68, 771,  74, 765,
                             178, 661, 136, 703,  86, 753,  78, 761,  43, 796,  39, 800,
                              20, 819,  21, 818,  95, 744, 202, 637, 190, 649, 181, 658,
                             137, 702, 125, 714, 151, 688, 217, 622, 128, 711, 142, 697,
                             122, 717, 203, 636, 118, 721, 110, 729,  89, 750, 103, 736,
                              61, 778,  55, 784,  15, 824,  14, 825,  12, 827,  23, 816,
                              34, 805,  37, 802,  46, 793, 207, 632, 179, 660, 145, 694,
                             130, 709, 223, 616, 228, 611, 227, 612, 132, 707, 133, 706,
                             143, 696, 135, 704, 161, 678, 201, 638, 173, 666, 106, 733,
                              83, 756,  91, 748,  66, 773,  53, 786,  10, 829,   9, 830,
                               7, 832,   8, 831,  16, 823,  47, 792,  64, 775,  57, 782,
                             104, 735, 101, 738, 108, 731, 208, 631, 184, 655, 197, 642,
                             191, 648, 121, 718, 141, 698, 149, 690, 216, 623, 218, 621,
                             152, 687, 144, 695, 134, 705, 138, 701, 199, 640, 162, 677,
                             176, 663, 119, 720, 158, 681, 164, 675, 174, 665, 171, 668,
                             170, 669,  87, 752, 169, 670,  88, 751, 107, 732,  81, 758,
                              82, 757, 100, 739,  98, 741,  71, 768,  59, 780,  65, 774,
                              50, 789,  49, 790,  26, 813,  17, 822,  13, 826,   6, 833,
                               5, 834,  33, 806,  51, 788,  75, 764,  99, 740,  96, 743,
                              97, 742, 166, 673, 172, 667, 175, 664, 187, 652, 163, 676,
                             185, 654, 200, 639, 114, 725, 189, 650, 115, 724, 194, 645,
                             195, 644, 192, 647, 182, 657, 157, 682, 156, 683, 211, 628,
                             154, 685, 123, 716, 139, 700, 212, 627, 153, 686, 213, 626,
                             215, 624, 150, 689, 225, 614, 224, 615, 221, 618, 220, 619,
                             127, 712, 147, 692, 124, 715, 193, 646, 205, 634, 206, 633,
                             116, 723, 160, 679, 186, 653, 167, 672,  79, 760,  85, 754,
                              77, 762,  92, 747,  58, 781,  62, 777,  69, 770,  54, 785,
                              36, 803,  32, 807,  25, 814,  18, 821,  11, 828,   4, 835,
                               3, 836,  19, 820,  22, 817,  41, 798,  38, 801,  44, 795,
                              52, 787,  45, 794,  63, 776,  67, 772,  72, 767,  76, 763,
                              94, 745, 102, 737,  90, 749, 109, 730, 165, 674, 111, 728,
                             209, 630, 204, 635, 117, 722, 188, 651, 159, 680, 198, 641,
                             113, 726, 183, 656, 180, 659, 177, 662, 196, 643, 155, 684,
                             214, 625, 126, 713, 131, 708, 219, 620, 222, 617, 226, 613,
                             230, 609, 232, 607, 262, 577, 252, 587, 418, 421, 416, 423,
                             413, 426, 411, 428, 376, 463, 395, 444, 283, 556, 285, 554,
                             379, 460, 390, 449, 363, 476, 384, 455, 388, 451, 386, 453,
                             361, 478, 387, 452, 360, 479, 310, 529, 354, 485, 328, 511,
                             315, 524, 337, 502, 349, 490, 335, 504, 324, 515, 323, 516,
                             320, 519, 334, 505, 359, 480, 295, 544, 385, 454, 292, 547,
                             291, 548, 381, 458, 399, 440, 380, 459, 397, 442, 369, 470,
                             377, 462, 410, 429, 407, 432, 281, 558, 414, 425, 247, 592,
                             277, 562, 271, 568, 272, 567, 264, 575, 259, 580, 237, 602,
                             239, 600, 244, 595, 243, 596, 275, 564, 278, 561, 250, 589,
                             246, 593, 417, 422, 248, 591, 394, 445, 393, 446, 370, 469,
                             365, 474, 300, 539, 299, 540, 364, 475, 362, 477, 298, 541,
                             312, 527, 313, 526, 314, 525, 353, 486, 352, 487, 343, 496,
                             327, 512, 350, 489, 326, 513, 319, 520, 332, 507, 333, 506,
                             348, 491, 347, 492, 322, 517, 330, 509, 338, 501, 341, 498,
                             340, 499, 342, 497, 301, 538, 366, 473, 401, 438, 371, 468,
                             408, 431, 375, 464, 249, 590, 269, 570, 238, 601, 234, 605,
                             257, 582, 273, 566, 255, 584, 254, 585, 245, 594, 251, 588,
                             412, 427, 372, 467, 282, 557, 403, 436, 396, 443, 392, 447,
                             391, 448, 382, 457, 389, 450, 294, 545, 297, 542, 311, 528,
                             344, 495, 345, 494, 318, 521, 331, 508, 325, 514, 321, 518,
                             346, 493, 339, 500, 351, 488, 306, 533, 289, 550, 400, 439,
                             378, 461, 374, 465, 415, 424, 270, 569, 241, 598, 231, 608,
                             260, 579, 268, 571, 276, 563, 409, 430, 398, 441, 290, 549,
                             304, 535, 308, 531, 358, 481, 316, 523, 293, 546, 288, 551,
                             284, 555, 368, 471, 253, 586, 256, 583, 263, 576, 242, 597,
                             274, 565, 402, 437, 383, 456, 357, 482, 329, 510, 317, 522,
                             307, 532, 286, 553, 287, 552, 266, 573, 261, 578, 236, 603,
                             303, 536, 356, 483, 355, 484, 405, 434, 404, 435, 406, 433,
                             235, 604, 267, 572, 302, 537, 309, 530, 265, 574, 233, 606,
                             367, 472, 296, 543, 336, 503, 305, 534, 373, 466, 280, 559,
                             279, 560, 419, 420, 240, 599, 258, 581, 229, 610};

// PRACH root Zadoff-Chu sequence values from 3GPP TS 36.211 v10.1.0 table 5.7.2-5
uint32 PRACH_5_7_2_5[138] = {   1, 138,   2, 137,   3, 136,   4, 135,   5, 134,   6, 133,
                                7, 132,   8, 131,   9, 130,  10, 129,  11, 128,  12, 127,
                               13, 126,  14, 125,  15, 124,  16, 123,  17, 122,  18, 121,
                               19, 120,  20, 119,  21, 118,  22, 117,  23, 116,  24, 115,
                               25, 114,  26, 113,  27, 112,  28, 111,  29, 110,  30, 109,
                               31, 108,  32, 107,  33, 106,  34, 105,  35, 104,  36, 103,
                               37, 102,  38, 101,  39, 100,  40,  99,  41,  98,  42,  97,
                               43,  96,  44,  95,  45,  94,  46,  93,  47,  92,  48,  91,
                               49,  90,  50,  89,  51,  88,  52,  87,  53,  86,  54,  85,
                               55,  84,  56,  83,  57,  82,  58,  81,  59,  80,  60,  79,
                               61,  78,  62,  77,  63,  76,  64,  75,  65,  74,  66,  73,
                               67,  72,  68,  71,  69,  70};

// PHICH orthogonal sequences table from 3GPP TS 36.211 v10.1.0 table 6.9.1-2
complex PHICH_w_normal_cp_6_9_1_2[8][4] = {{complex( 1, 0),complex( 1, 0),complex( 1, 0),complex( 1, 0)},
                                           {complex( 1, 0),complex(-1, 0),complex( 1, 0),complex(-1, 0)},
                                           {complex( 1, 0),complex( 1, 0),complex(-1, 0),complex(-1, 0)},
                                           {complex( 1, 0),complex(-1, 0),complex(-1, 0),complex( 1, 0)},
                                           {complex( 0, 1),complex( 0, 1),complex( 0, 1),complex( 0, 1)},
                                           {complex( 0, 1),complex( 0,-1),complex( 0, 1),complex( 0,-1)},
                                           {complex( 0, 1),complex( 0, 1),complex( 0,-1),complex( 0,-1)},
                                           {complex( 0, 1),complex( 0,-1),complex( 0,-1),complex( 0, 1)}};
complex PHICH_w_extended_cp_6_9_1_2[4][2] = {{complex( 1, 0),complex( 1, 0)},
                                             {complex( 1, 0),complex(-1, 0)},
                                             {complex( 0, 1),complex( 0, 1)},
                                             {complex( 0, 1),complex( 0,-1)}};

// BPSK symbols from 3GPP TS 36.211 v10.1.0 table 7.1.1-1
complex mod_map_bpsk[2] = {complex( 1/sqrt(2), 1/sqrt(2)),complex(-1/sqrt(2), 1/sqrt(2))};

// QPSK symbols from 3GPP TS 36.211 v10.1.0 table 7.1.2-1
complex mod_map_qpsk[4] = {complex( 1/sqrt(2), 1/sqrt(2)),complex( 1/sqrt(2),-1/sqrt(2)),
                           complex(-1/sqrt(2), 1/sqrt(2)),complex(-1/sqrt(2),-1/sqrt(2))};

// 16QAM symbols from 3GPP TS 36.211 v10.1.0 table 7.1.3-1
complex mod_map_16qam[16] = {complex( 1/sqrt(10), 1/sqrt(10)),complex( 1/sqrt(10), 3/sqrt(10)),
                             complex( 3/sqrt(10), 1/sqrt(10)),complex( 3/sqrt(10), 3/sqrt(10)),
                             complex( 1/sqrt(10),-1/sqrt(10)),complex( 1/sqrt(10),-3/sqrt(10)),
                             complex( 3/sqrt(10),-1/sqrt(10)),complex( 3/sqrt(10),-3/sqrt(10)),
                             complex(-1/sqrt(10), 1/sqrt(10)),complex(-1/sqrt(10), 3/sqrt(10)),
                             complex(-3/sqrt(10), 1/sqrt(10)),complex(-3/sqrt(10), 3/sqrt(10)),
                             complex(-1/sqrt(10),-1/sqrt(10)),complex(-1/sqrt(10),-3/sqrt(10)),
                             complex(-3/sqrt(10),-1/sqrt(10)),complex(-3/sqrt(10),-3/sqrt(10))};

// 64QAM symbols from 3GPP TS 36.211 v10.1.0 table 7.1.4-1
complex mod_map_64qam[64] = {complex( 3/sqrt(42), 3/sqrt(42)),complex( 3/sqrt(42), 1/sqrt(42)),
                             complex( 1/sqrt(42), 3/sqrt(42)),complex( 1/sqrt(42), 1/sqrt(42)),
                             complex( 3/sqrt(42), 5/sqrt(42)),complex( 3/sqrt(42), 7/sqrt(42)),
                             complex( 1/sqrt(42), 5/sqrt(42)),complex( 1/sqrt(42), 7/sqrt(42)),
                             complex( 5/sqrt(42), 3/sqrt(42)),complex( 5/sqrt(42), 1/sqrt(42)),
                             complex( 7/sqrt(42), 3/sqrt(42)),complex( 7/sqrt(42), 1/sqrt(42)),
                             complex( 5/sqrt(42), 5/sqrt(42)),complex( 5/sqrt(42), 7/sqrt(42)),
                             complex( 7/sqrt(42), 5/sqrt(42)),complex( 7/sqrt(42), 7/sqrt(42)),
                             complex( 3/sqrt(42),-3/sqrt(42)),complex( 3/sqrt(42),-1/sqrt(42)),
                             complex( 1/sqrt(42),-3/sqrt(42)),complex( 1/sqrt(42),-1/sqrt(42)),
                             complex( 3/sqrt(42),-5/sqrt(42)),complex( 3/sqrt(42),-7/sqrt(42)),
                             complex( 1/sqrt(42),-5/sqrt(42)),complex( 1/sqrt(42),-7/sqrt(42)),
                             complex( 5/sqrt(42),-3/sqrt(42)),complex( 5/sqrt(42),-1/sqrt(42)),
                             complex( 7/sqrt(42),-3/sqrt(42)),complex( 7/sqrt(42),-1/sqrt(42)),
                             complex( 5/sqrt(42),-5/sqrt(42)),complex( 5/sqrt(42),-7/sqrt(42)),
                             complex( 7/sqrt(42),-5/sqrt(42)),complex( 7/sqrt(42),-7/sqrt(42)),
                             complex(-3/sqrt(42), 3/sqrt(42)),complex(-3/sqrt(42), 1/sqrt(42)),
                             complex(-1/sqrt(42), 3/sqrt(42)),complex(-1/sqrt(42), 1/sqrt(42)),
                             complex(-3/sqrt(42), 5/sqrt(42)),complex(-3/sqrt(42), 7/sqrt(42)),
                             complex(-1/sqrt(42), 5/sqrt(42)),complex(-1/sqrt(42), 7/sqrt(42)),
                             complex(-5/sqrt(42), 3/sqrt(42)),complex(-5/sqrt(42), 1/sqrt(42)),
                             complex(-7/sqrt(42), 3/sqrt(42)),complex(-7/sqrt(42), 1/sqrt(42)),
                             complex(-5/sqrt(42), 5/sqrt(42)),complex(-5/sqrt(42), 7/sqrt(42)),
                             complex(-7/sqrt(42), 5/sqrt(42)),complex(-7/sqrt(42), 7/sqrt(42)),
                             complex(-3/sqrt(42),-3/sqrt(42)),complex(-3/sqrt(42),-1/sqrt(42)),
                             complex(-1/sqrt(42),-3/sqrt(42)),complex(-1/sqrt(42),-1/sqrt(42)),
                             complex(-3/sqrt(42),-5/sqrt(42)),complex(-3/sqrt(42),-7/sqrt(42)),
                             complex(-1/sqrt(42),-5/sqrt(42)),complex(-1/sqrt(42),-7/sqrt(42)),
                             complex(-5/sqrt(42),-3/sqrt(42)),complex(-5/sqrt(42),-1/sqrt(42)),
                             complex(-7/sqrt(42),-3/sqrt(42)),complex(-7/sqrt(42),-1/sqrt(42)),
                             complex(-5/sqrt(42),-5/sqrt(42)),complex(-5/sqrt(42),-7/sqrt(42)),
                             complex(-7/sqrt(42),-5/sqrt(42)),complex(-7/sqrt(42),-7/sqrt(42))};

// Control Format Indicator
uint8 CFI_BITS_1[32] = {0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1};
uint8 CFI_BITS_2[32] = {1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0};
uint8 CFI_BITS_3[32] = {1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1};
uint8 CFI_BITS_4[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// Rate Matching
uint8 IC_PERM_CC[32] = { 1,17, 9,25, 5,21,13,29, 3,19,11,27, 7,23,15,31,
                         0,16, 8,24, 4,20,12,28, 2,18,10,26, 6,22,14,30};
uint8 IC_PERM_TC[32] = { 0,16, 8,24, 4,20,12,28, 2,18,10,26, 6,22,14,30,
                         1,17, 9,25, 5,21,13,29, 3,19,11,27, 7,23,15,31};

// Turbo Internal Interleaver from 3GPP TS 36.212 v10.1.0 table 5.1.3-3
#define TURBO_INT_K_TABLE_SIZE 188
uint32 TURBO_INT_K_TABLE[188] = {  40,  48,  56,  64,  72,  80,  88,  96, 104, 112,
                                  120, 128, 136, 144, 152, 160, 168, 176, 184, 192,
                                  200, 208, 216, 224, 232, 240, 248, 256, 264, 272,
                                  280, 288, 296, 304, 312, 320, 328, 336, 344, 352,
                                  360, 368, 376, 384, 392, 400, 408, 416, 424, 432,
                                  440, 448, 456, 464, 472, 480, 488, 496, 504, 512,
                                  528, 544, 560, 576, 592, 608, 624, 640, 656, 672,
                                  688, 704, 720, 736, 752, 768, 784, 800, 816, 832,
                                  848, 864, 880, 896, 912, 928, 944, 960, 976, 992,
                                 1008,1024,1056,1088,1120,1152,1184,1216,1248,1280,
                                 1312,1344,1376,1408,1440,1472,1504,1536,1568,1600,
                                 1632,1664,1696,1728,1760,1792,1824,1856,1888,1920,
                                 1952,1984,2016,2048,2112,2176,2240,2304,2368,2432,
                                 2496,2560,2624,2688,2752,2816,2880,2944,3008,3072,
                                 3136,3200,3264,3328,3392,3456,3520,3584,3648,3712,
                                 3776,3840,3904,3968,4032,4096,4160,4224,4288,4352,
                                 4416,4480,4544,4608,4672,4736,4800,4864,4928,4992,
                                 5056,5120,5184,5248,5312,5376,5440,5504,5568,5632,
                                 5696,5760,5824,5888,5952,6016,6080,6144};
uint32 TURBO_INT_F1_TABLE[188] = {  3,  7, 19,  7,  7, 11,  5, 11,  7, 41,103, 15,  9,
                                   17,  9, 21,101, 21, 57, 23, 13, 27, 11, 27, 85, 29,
                                   33, 15, 17, 33,103, 19, 19, 37, 19, 21, 21,115,193,
                                   21,133, 81, 45, 23,243,151,155, 25, 51, 47, 91, 29,
                                   29,247, 29, 89, 91,157, 55, 31, 17, 35,227, 65, 19,
                                   37, 41, 39,185, 43, 21,155, 79,139, 23,217, 25, 17,
                                  127, 25,239, 17,137,215, 29, 15,147, 29, 59, 65, 55,
                                   31, 17,171, 67, 35, 19, 39, 19,199, 21,211, 21, 43,
                                  149, 45, 49, 71, 13, 17, 25,183, 55,127, 27, 29, 29,
                                   57, 45, 31, 59,185,113, 31, 17,171,209,253,367,265,
                                  181, 39, 27,127,143, 43, 29, 45,157, 47, 13,111,443,
                                   51, 51,451,257, 57,313,271,179,331,363,375,127, 31,
                                   33, 43, 33,477, 35,233,357,337, 37, 71, 71, 37, 39,
                                  127, 39, 39, 31,113, 41,251, 43, 21, 43, 45, 45,161,
                                   89,323, 47, 23, 47,263};
uint32 TURBO_INT_F2_TABLE[188] = { 10, 12, 42, 16, 18, 20, 22, 24, 26, 84, 90, 32, 34,
                                  108, 38,120, 84, 44, 46, 48, 50, 52, 36, 56, 58, 60,
                                   62, 32,198, 68,210, 36, 74, 76, 78,120, 82, 84, 86,
                                   44, 90, 46, 94, 48, 98, 40,102, 52,106, 72,110,168,
                                  114, 58,118,180,122, 62, 84, 64, 66, 68,420, 96, 74,
                                   76,234, 80, 82,252, 86, 44,120, 92, 94, 48, 98, 80,
                                  102, 52,106, 48,110,112,114, 58,118, 60,122,124, 84,
                                   64, 66,204,140, 72, 74, 76, 78,240, 82,252, 86, 88,
                                   60, 92,846, 48, 28, 80,102,104,954, 96,110,112,114,
                                  116,354,120,610,124,420, 64, 66,136,420,216,444,456,
                                  468, 80,164,504,172, 88,300, 92,188, 96, 28,240,204,
                                  104,212,192,220,336,228,232,236,120,244,248,168, 64,
                                  130,264,134,408,138,280,142,480,146,444,120,152,462,
                                  234,158, 80, 96,902,166,336,170, 86,174,176,178,120,
                                  182,184,186, 94,190,480};

// Transport Block Size from 3GPP TS 36.213 v10.3.0 table 7.1.7.2.1-1
uint32 TBS_71721[27][110] = {{   16,   32,   56,   88,  120,  152,  176,  208,  224,  256,  288,
                                328,  344,  376,  392,  424,  456,  488,  504,  536,  568,  600,
                                616,  648,  680,  712,  744,  776,  776,  808,  840,  872,  904,
                                936,  968, 1000, 1032, 1032, 1064, 1096, 1128, 1160, 1192, 1224,
                               1256, 1256, 1288, 1320, 1352, 1384, 1416, 1416, 1480, 1480, 1544,
                               1544, 1608, 1608, 1608, 1672, 1672, 1736, 1736, 1800, 1800, 1800,
                               1864, 1864, 1928, 1928, 1992, 1992, 2024, 2088, 2088, 2088, 2152,
                               2152, 2216, 2216, 2280, 2280, 2280, 2344, 2344, 2408, 2408, 2472,
                               2472, 2536, 2536, 2536, 2600, 2600, 2664, 2664, 2728, 2728, 2728,
                               2792, 2792, 2856, 2856, 2856, 2984, 2984, 2984, 2984, 2984, 3112},
                             {   24,   56,   88,  144,  176,  208,  224,  256,  328,  344,  376,
                                424,  456,  488,  520,  568,  600,  632,  680,  712,  744,  776,
                                808,  872,  904,  936,  968, 1000, 1032, 1064, 1128, 1160, 1192,
                               1224, 1256, 1288, 1352, 1384, 1416, 1416, 1480, 1544, 1544, 1608,
                               1608, 1672, 1736, 1736, 1800, 1800, 1864, 1864, 1928, 1992, 1992,
                               2024, 2088, 2088, 2152, 2152, 2216, 2280, 2280, 2344, 2344, 2408,
                               2472, 2472, 2536, 2536, 2600, 2600, 2664, 2728, 2728, 2792, 2792,
                               2856, 2856, 2856, 2984, 2984, 2984, 3112, 3112, 3112, 3240, 3240,
                               3240, 3240, 3368, 3368, 3368, 3496, 3496, 3496, 3496, 3624, 3624,
                               3624, 3752, 3752, 3752, 3752, 3880, 3880, 3880, 4008, 4008, 4008},
                             {   32,   72,  144,  176,  208,  256,  296,  328,  376,  424,  472,
                                520,  568,  616,  648,  696,  744,  776,  840,  872,  936,  968,
                               1000, 1064, 1096, 1160, 1192, 1256, 1288, 1320, 1384, 1416, 1480,
                               1544, 1544, 1608, 1672, 1672, 1736, 1800, 1800, 1864, 1928, 1992,
                               2024, 2088, 2088, 2152, 2216, 2216, 2280, 2344, 2344, 2408, 2472,
                               2536, 2536, 2600, 2664, 2664, 2728, 2792, 2856, 2856, 2856, 2984,
                               2984, 3112, 3112, 3112, 3240, 3240, 3240, 3368, 3368, 3368, 3496,
                               3496, 3496, 3624, 3624, 3624, 3752, 3752, 3880, 3880, 3880, 4008,
                               4008, 4008, 4136, 4136, 4136, 4264, 4264, 4264, 4392, 4392, 4392,
                               4584, 4584, 4584, 4584, 4584, 4776, 4776, 4776, 4776, 4968, 4968},
                             {   40,  104,  176,  208,  256,  328,  392,  440,  504,  568,  616,
                                680,  744,  808,  872,  904,  968, 1032, 1096, 1160, 1224, 1256,
                               1320, 1384, 1416, 1480, 1544, 1608, 1672, 1736, 1800, 1864, 1928,
                               1992, 2024, 2088, 2152, 2216, 2280, 2344, 2408, 2472, 2536, 2536,
                               2600, 2664, 2728, 2792, 2856, 2856, 2984, 2984, 3112, 3112, 3240,
                               3240, 3368, 3368, 3496, 3496, 3624, 3624, 3624, 3752, 3752, 3880,
                               3880, 4008, 4008, 4136, 4136, 4264, 4264, 4392, 4392, 4392, 4584,
                               4584, 4584, 4776, 4776, 4776, 4776, 4968, 4968, 4968, 5160, 5160,
                               5160, 5352, 5352, 5352, 5352, 5544, 5544, 5544, 5736, 5736, 5736,
                               5736, 5992, 5992, 5992, 5992, 6200, 6200, 6200, 6200, 6456, 6456},
                             {   56,  120,  208,  256,  328,  408,  488,  552,  632,  696,  776,
                                840,  904, 1000, 1064, 1128, 1192, 1288, 1352, 1416, 1480, 1544,
                               1608, 1736, 1800, 1864, 1928, 1992, 2088, 2152, 2216, 2280, 2344,
                               2408, 2472, 2600, 2664, 2728, 2792, 2856, 2984, 2984, 3112, 3112,
                               3240, 3240, 3368, 3496, 3496, 3624, 3624, 3752, 3752, 3880, 4008,
                               4008, 4136, 4136, 4264, 4264, 4392, 4392, 4584, 4584, 4584, 4776,
                               4776, 4968, 4968, 4968, 5160, 5160, 5160, 5352, 5352, 5544, 5544,
                               5544, 5736, 5736, 5736, 5992, 5992, 5992, 5992, 6200, 6200, 6200,
                               6456, 6456, 6456, 6456, 6712, 6712, 6712, 6968, 6968, 6968, 6968,
                               7224, 7224, 7224, 7480, 7480, 7480, 7480, 7736, 7736, 7736, 7992},
                             {   72,  144,  224,  328,  424,  504,  600,  680,  776,  872,  968,
                               1032, 1128, 1224, 1320, 1384, 1480, 1544, 1672, 1736, 1864, 1928,
                               2024, 2088, 2216, 2280, 2344, 2472, 2536, 2664, 2728, 2792, 2856,
                               2984, 3112, 3112, 3240, 3368, 3496, 3496, 3624, 3752, 3752, 3880,
                               4008, 4008, 4136, 4264, 4392, 4392, 4584, 4584, 4776, 4776, 4776,
                               4968, 4968, 5160, 5160, 5352, 5352, 5544, 5544, 5736, 5736, 5736,
                               5992, 5992, 5992, 6200, 6200, 6200, 6456, 6456, 6712, 6712, 6712,
                               6968, 6968, 6968, 7224, 7224, 7224, 7480, 7480, 7480, 7736, 7736,
                               7736, 7992, 7992, 7992, 8248, 8248, 8248, 8504, 8504, 8760, 8760,
                               8760, 8760, 9144, 9144, 9144, 9144, 9528, 9528, 9528, 9528, 9528},
                             {  328,  176,  256,  392,  504,  600,  712,  808,  936, 1032, 1128,
                               1224, 1352, 1480, 1544, 1672, 1736, 1864, 1992, 2088, 2216, 2280,
                               2408, 2472, 2600, 2728, 2792, 2984, 2984, 3112, 3240, 3368, 3496,
                               3496, 3624, 3752, 3880, 4008, 4136, 4136, 4264, 4392, 4584, 4584,
                               4776, 4776, 4968, 4968, 5160, 5160, 5352, 5352, 5544, 5736, 5736,
                               5992, 5992, 5992, 6200, 6200, 6456, 6456, 6456, 6712, 6712, 6968,
                               6968, 6968, 7224, 7224, 7480, 7480, 7736, 7736, 7736, 7992, 7992,
                               8248, 8248, 8248, 8504, 8504, 8760, 8760, 8760, 9144, 9144, 9144,
                               9144, 9528, 9528, 9528, 9528, 9912, 9912, 9912,10296,10296,10296,
                              10296,10680,10680,10680,10680,11064,11064,11064,11448,11448,11448},
                             {  104,  224,  328,  472,  584,  712,  840,  968, 1096, 1224, 1320,
                               1480, 1608, 1672, 1800, 1928, 2088, 2216, 2344, 2472, 2536, 2664,
                               2792, 2984, 3112, 3240, 3368, 3368, 3496, 3624, 3752, 3880, 4008,
                               4136, 4264, 4392, 4584, 4584, 4776, 4968, 4968, 5160, 5352, 5352,
                               5544, 5736, 5736, 5992, 5992, 6200, 6200, 6456, 6456, 6712, 6712,
                               6712, 6968, 6968, 7224, 7224, 7480, 7480, 7736, 7736, 7992, 7992,
                               8248, 8248, 8504, 8504, 8760, 8760, 8760, 9144, 9144, 9144, 9528,
                               9528, 9528, 9912, 9912, 9912,10296,10296,10296,10680,10680,10680,
                              11064,11064,11064,11448,11448,11448,11448,11832,11832,11832,12216,
                              12216,12216,12576,12576,12576,12960,12960,12960,12960,13536,13536},
                             {  120,  256,  392,  536,  680,  808,  968, 1096, 1256, 1384, 1544,
                               1672, 1800, 1928, 2088, 2216, 2344, 2536, 2664, 2792, 2984, 3112,
                               3240, 3368, 3496, 3624, 3752, 3880, 4008, 4264, 4392, 4584, 4584,
                               4776, 4968, 4968, 5160, 5352, 5544, 5544, 5736, 5992, 5992, 6200,
                               6200, 6456, 6456, 6712, 6968, 6968, 7224, 7224, 7480, 7480, 7736,
                               7736, 7992, 7992, 8248, 8504, 8504, 8760, 8760, 9144, 9144, 9144,
                               9528, 9528, 9528, 9912, 9912, 9912,10296,10296,10680,10680,10680,
                              11064,11064,11064,11448,11448,11448,11832,11832,12216,12216,12216,
                              12576,12576,12576,12960,12960,12960,13536,13536,13536,13536,14112,
                              14112,14112,14112,14688,14688,14688,14688,15264,15264,15264,15264},
                             {  136,  296,  456,  616,  776,  936, 1096, 1256, 1416, 1544, 1736,
                               1864, 2024, 2216, 2344, 2536, 2664, 2856, 2984, 3112, 3368, 3496,
                               3624, 3752, 4008, 4136, 4264, 4392, 4584, 4776, 4968, 5160, 5160,
                               5352, 5544, 5736, 5736, 5992, 6200, 6200, 6456, 6712, 6712, 6968,
                               6968, 7224, 7480, 7480, 7736, 7992, 7992, 8248, 8248, 8504, 8760,
                               8760, 9144, 9144, 9144, 9528, 9528, 9912, 9912,10296,10296,10296,
                              10680,10680,11064,11064,11064,11448,11448,11832,11832,11832,12216,
                              12216,12576,12576,12960,12960,12960,13536,13536,13536,13536,14112,
                              14112,14112,14112,14688,14688,14688,15264,15264,15264,15264,15840,
                              15840,15840,16416,16416,16416,16416,16992,16992,16992,16992,17568},
                             {  144,  328,  504,  680,  872, 1032, 1224, 1384, 1544, 1736, 1928,
                               2088, 2280, 2472, 2664, 2792, 2984, 3112, 3368, 3496, 3752, 3880,
                               4008, 4264, 4392, 4584, 4776, 4968, 5160, 5352, 5544, 5736, 5736,
                               5992, 6200, 6200, 6456, 6712, 6712, 6968, 7224, 7480, 7480, 7736,
                               7992, 7992, 8248, 8504, 8504, 8760, 9144, 9144, 9144, 9528, 9528,
                               9912, 9912,10296,10296,10680,10680,11064,11064,11448,11448,11448,
                              11832,11832,12216,12216,12576,12576,12960,12960,12960,13536,13536,
                              13536,14112,14112,14112,14688,14688,14688,14688,15264,15264,15264,
                              15840,15840,15840,16416,16416,16416,16992,16992,16992,16992,17568,
                              17568,17568,18336,18336,18336,18336,18336,19080,19080,19080,19080},
                             {  176,  376,  584,  776, 1000, 1192, 1384, 1608, 1800, 2024, 2216,
                               2408, 2600, 2792, 2984, 3240, 3496, 3624, 3880, 4008, 4264, 4392,
                               4584, 4776, 4968, 5352, 5544, 5736, 5992, 5992, 6200, 6456, 6712,
                               6968, 6968, 7224, 7480, 7736, 7736, 7992, 8248, 8504, 8760, 8760,
                               9144, 9144, 9528, 9528, 9912, 9912,10296,10680,10680,11064,11064,
                              11448,11448,11832,11832,12216,12216,12576,12576,12960,12960,13536,
                              13536,13536,14112,14112,14112,14688,14688,14688,15264,15264,15840,
                              15840,15840,16416,16416,16416,16992,16992,16992,17568,17568,17568,
                              18336,18336,18336,18336,19080,19080,19080,19080,19848,19848,19848,
                              19848,20616,20616,20616,21384,21384,21384,21384,22152,22152,22152},
                             {  208,  440,  680,  904, 1128, 1352, 1608, 1800, 2024, 2280, 2472,
                               2728, 2984, 3240, 3368, 3624, 3880, 4136, 4392, 4584, 4776, 4968,
                               5352, 5544, 5736, 5992, 6200, 6456, 6712, 6712, 6968, 7224, 7480,
                               7736, 7992, 8248, 8504, 8760, 8760, 9144, 9528, 9528, 9912, 9912,
                              10296,10680,10680,11064,11064,11448,11832,11832,12216,12216,12576,
                              12576,12960,12960,13536,13536,14112,14112,14112,14688,14688,15264,
                              15264,15264,15840,15840,16416,16416,16416,16992,16992,17568,17568,
                              17568,18336,18336,18336,19080,19080,19080,19080,19848,19848,19848,
                              20616,20616,20616,21384,21384,21384,21384,22152,22152,22152,22920,
                              22920,22920,23688,23688,23688,23688,24496,24496,24496,24496,25456},
                             {  224,  488,  744, 1000, 1256, 1544, 1800, 2024, 2280, 2536, 2856,
                               3112, 3368, 3624, 3880, 4136, 4392, 4584, 4968, 5160, 5352, 5736,
                               5992, 6200, 6456, 6712, 6968, 7224, 7480, 7736, 7992, 8248, 8504,
                               8760, 9144, 9144, 9528, 9912, 9912,10296,10680,10680,11064,11448,
                              11448,11832,12216,12216,12576,12960,12960,13536,13536,14112,14112,
                              14688,14688,14688,15264,15264,15840,15840,16416,16416,16992,16992,
                              16992,17568,17568,18336,18336,18336,19080,19080,19080,19848,19848,
                              19848,20616,20616,20616,21384,21384,21384,22152,22152,22152,22920,
                              22920,22920,23688,23688,23688,24496,24496,24496,25456,25456,25456,
                              25456,26416,26416,26416,26416,27376,27376,27376,27376,28336,28336},
                             {  256,  552,  840, 1128, 1416, 1736, 1992, 2280, 2600, 2856, 3112,
                               3496, 3752, 4008, 4264, 4584, 4968, 5160, 5544, 5736, 5992, 6200,
                               6456, 6968, 7224, 7480, 7736, 7992, 8248, 8504, 8760, 9144, 9528,
                               9912, 9912,10296,10680,11064,11064,11448,11832,12216,12216,12576,
                              12960,12960,13536,13536,14112,14112,14688,14688,15264,15264,15840,
                              15840,16416,16416,16992,16992,17568,17568,18336,18336,18336,19080,
                              19080,19848,19848,19848,20616,20616,20616,21384,21384,22152,22152,
                              22152,22920,22920,22920,23688,23688,24496,24496,24496,25456,25456,
                              25456,25456,26416,26416,26416,27376,27376,27376,28336,28336,28336,
                              28336,29296,29296,29296,29296,30576,30576,30576,30576,31704,31704},
                             {  280,  600,  904, 1224, 1544, 1800, 2152, 2472, 2728, 3112, 3368,
                               3624, 4008, 4264, 4584, 4968, 5160, 5544, 5736, 6200, 6456, 6712,
                               6968, 7224, 7736, 7992, 8248, 8504, 8760, 9144, 9528, 9912,10296,
                              10296,10680,11064,11448,11832,11832,12216,12576,12960,12960,13536,
                              13536,14112,14688,14688,15264,15264,15840,15840,16416,16416,16992,
                              16992,17568,17568,18336,18336,18336,19080,19080,19848,19848,20616,
                              20616,20616,21384,21384,22152,22152,22152,22920,22920,23688,23688,
                              23688,24496,24496,24496,25456,25456,25456,26416,26416,26416,27376,
                              27376,27376,28336,28336,28336,29296,29296,29296,29296,30576,30576,
                              30576,30576,31704,31704,31704,31704,32856,32856,32856,34008,34008},
                             {  328,  632,  968, 1288, 1608, 1928, 2280, 2600, 2984, 3240, 3624,
                               3880, 4264, 4584, 4968, 5160, 5544, 5992, 6200, 6456, 6712, 7224,
                               7480, 7736, 7992, 8504, 8760, 9144, 9528, 9912, 9912,10296,10680,
                              11064,11448,11832,12216,12216,12576,12960,13536,13536,14112,14112,
                              14688,14688,15264,15840,15840,16416,16416,16992,16992,17568,17568,
                              18336,18336,19080,19080,19848,19848,19848,20616,20616,21384,21384,
                              22152,22152,22152,22920,22920,23688,23688,24496,24496,24496,25456,
                              25456,25456,26416,26416,26416,27376,27376,27376,28336,28336,28336,
                              29296,29296,29296,30576,30576,30576,30576,31704,31704,31704,31704,
                              32856,32856,32856,34008,34008,34008,34008,35160,35160,35160,35160},
                             {  336,  696, 1064, 1416, 1800, 2152, 2536, 2856, 3240, 3624, 4008,
                               4392, 4776, 5160, 5352, 5736, 6200, 6456, 6712, 7224, 7480, 7992,
                               8248, 8760, 9144, 9528, 9912,10296,10296,10680,11064,11448,11832,
                              12216,12576,12960,13536,13536,14112,14688,14688,15264,15264,15840,
                              16416,16416,16992,17568,17568,18336,18336,19080,19080,19848,19848,
                              20616,20616,20616,21384,21384,22152,22152,22920,22920,23688,23688,
                              24496,24496,24496,25456,25456,26416,26416,26416,27376,27376,27376,
                              28336,28336,29296,29296,29296,30576,30576,30576,30576,31704,31704,
                              31704,32856,32856,32856,34008,34008,34008,35160,35160,35160,35160,
                              36696,36696,36696,36696,37888,37888,37888,39232,39232,39232,39232},
                             {  376,  776, 1160, 1544, 1992, 2344, 2792, 3112, 3624, 4008, 4392,
                               4776, 5160, 5544, 5992, 6200, 6712, 7224, 7480, 7992, 8248, 8760,
                               9144, 9528, 9912,10296,10680,11064,11448,11832,12216,12576,12960,
                              13536,14112,14112,14688,15264,15264,15840,16416,16416,16992,17568,
                              17568,18336,18336,19080,19080,19848,19848,20616,21384,21384,22152,
                              22152,22920,22920,23688,23688,24496,24496,24496,25456,25456,26416,
                              26416,27376,27376,27376,28336,28336,29296,29296,29296,30576,30576,
                              30576,31704,31704,31704,32856,32856,32856,34008,34008,34008,35160,
                              35160,35160,36696,36696,36696,37888,37888,37888,37888,39232,39232,
                              39232,40576,40576,40576,40576,42368,42368,42368,42368,43816,43816},
                             {  408,  840, 1288, 1736, 2152, 2600, 2984, 3496, 3880, 4264, 4776,
                               5160, 5544, 5992, 6456, 6968, 7224, 7736, 8248, 8504, 9144, 9528,
                               9912,10296,10680,11064,11448,12216,12576,12960,13536,13536,14112,
                              14688,15264,15264,15840,16416,16992,16992,17568,18336,18336,19080,
                              19080,19848,20616,20616,21384,21384,22152,22152,22920,22920,23688,
                              24496,24496,25456,25456,25456,26416,26416,27376,27376,28336,28336,
                              29296,29296,29296,30576,30576,30576,31704,31704,32856,32856,32856,
                              34008,34008,34008,35160,35160,35160,36696,36696,36696,37888,37888,
                              37888,39232,39232,39232,40576,40576,40576,40576,42368,42368,42368,
                              43816,43816,43816,43816,45352,45352,45352,46888,46888,46888,46888},
                             {  440,  904, 1384, 1864, 2344, 2792, 3240, 3752, 4136, 4584, 5160,
                               5544, 5992, 6456, 6968, 7480, 7992, 8248, 8760, 9144, 9912,10296,
                              10680,11064,11448,12216,12576,12960,13536,14112,14688,14688,15264,
                              15840,16416,16992,16992,17568,18336,18336,19080,19848,19848,20616,
                              20616,21384,22152,22152,22920,22920,23688,24496,24496,25456,25456,
                              26416,26416,27376,27376,28336,28336,29296,29296,29296,30576,30576,
                              31704,31704,31704,32856,32856,34008,34008,34008,35160,35160,35160,
                              36696,36696,36696,37888,37888,39232,39232,39232,40576,40576,40576,
                              42368,42368,42368,42368,43816,43816,43816,45352,45352,45352,46888,
                              46888,46888,46888,48936,48936,48936,48936,48936,51024,51024,51024},
                             {  488, 1000, 1480, 1992, 2472, 2984, 3496, 4008, 4584, 4968, 5544,
                               5992, 6456, 6968, 7480, 7992, 8504, 9144, 9528, 9912,10680,11064,
                              11448,12216,12576,12960,13536,14112,14688,15264,15840,15840,16416,
                              16992,17568,18336,18336,19080,19848,19848,20616,21384,21384,22152,
                              22920,22920,23688,24496,24496,25456,25456,26416,26416,27376,27376,
                              28336,28336,29296,29296,30576,30576,31704,31704,31704,32856,32856,
                              34008,34008,35160,35160,35160,36696,36696,36696,37888,37888,39232,
                              39232,39232,40576,40576,40576,42368,42368,42368,43816,43816,43816,
                              45352,45352,45352,46888,46888,46888,46888,48936,48936,48936,48936,
                              51024,51024,51024,51024,52752,52752,52752,52752,55056,55056,55056},
                             {  520, 1064, 1608, 2152, 2664, 3240, 3752, 4264, 4776, 5352, 5992,
                               6456, 6968, 7480, 7992, 8504, 9144, 9528,10296,10680,11448,11832,
                              12576,12960,13536,14112,14688,15264,15840,16416,16992,16992,17568,
                              18336,19080,19080,19848,20616,21384,21384,22152,22920,22920,23688,
                              24496,24496,25456,25456,26416,27376,27376,28336,28336,29296,29296,
                              30576,30576,31704,31704,32856,32856,34008,34008,34008,35160,35160,
                              36696,36696,36696,37888,37888,39232,39232,40576,40576,40576,42368,
                              42368,42368,43816,43816,43816,45352,45352,45352,46888,46888,46888,
                              48936,48936,48936,48936,51024,51024,51024,51024,52752,52752,52752,
                              55056,55056,55056,55056,57336,57336,57336,57336,59256,59256,59256},
                             {  552, 1128, 1736, 2280, 2856, 3496, 4008, 4584, 5160, 5736, 6200,
                               6968, 7480, 7992, 8504, 9144, 9912,10296,11064,11448,12216,12576,
                              12960,13536,14112,14688,15264,15840,16416,16992,17568,18336,19080,
                              19848,19848,20616,21384,22152,22152,22920,23688,24496,24496,25456,
                              25456,26416,27376,27376,28336,28336,29296,29296,30576,30576,31704,
                              31704,32856,32856,34008,34008,35160,35160,36696,36696,37888,37888,
                              37888,39232,39232,40576,40576,40576,42368,42368,43816,43816,43816,
                              45352,45352,45352,46888,46888,46888,48936,48936,48936,51024,51024,
                              51024,51024,52752,52752,52752,55056,55056,55056,55056,57336,57336,
                              57336,57336,59256,59256,59256,59256,61664,61664,61664,61664,63776},
                             {  584, 1192, 1800, 2408, 2984, 3624, 4264, 4968, 5544, 5992, 6712,
                               7224, 7992, 8504, 9144, 9912,10296,11064,11448,12216,12960,13536,
                              14112,14688,15264,15840,16416,16992,17568,18336,19080,19848,19848,
                              20616,21384,22152,22920,22920,23688,24496,25456,25456,26416,26416,
                              27376,28336,28336,29296,29296,30576,31704,31704,32856,32856,34008,
                              34008,35160,35160,36696,36696,36696,37888,37888,39232,39232,40576,
                              40576,42368,42368,42368,43816,43816,45352,45352,45352,46888,46888,
                              46888,48936,48936,48936,51024,51024,51024,52752,52752,52752,52752,
                              55056,55056,55056,57336,57336,57336,57336,59256,59256,59256,61664,
                              61664,61664,61664,63776,63776,63776,63776,66592,66592,66592,66592},
                             {  616, 1256, 1864, 2536, 3112, 3752, 4392, 5160, 5736, 6200, 6968,
                               7480, 8248, 8760, 9528,10296,10680,11448,12216,12576,13536,14112,
                              14688,15264,15840,16416,16992,17568,18336,19080,19848,20616,20616,
                              21384,22152,22920,23688,24496,24496,25456,26416,26416,27376,28336,
                              28336,29296,29296,30576,31704,31704,32856,32856,34008,34008,35160,
                              35160,36696,36696,37888,37888,39232,39232,40576,40576,40576,42368,
                              42368,43816,43816,43816,45352,45352,46888,46888,46888,48936,48936,
                              48936,51024,51024,51024,52752,52752,52752,55056,55056,55056,55056,
                              57336,57336,57336,59256,59256,59256,61664,61664,61664,61664,63776,
                              63776,63776,63776,66592,66592,66592,66592,68808,68808,68808,71112},
                             {  712, 1480, 2216, 2984, 3752, 4392, 5160, 5992, 6712, 7480, 8248,
                               8760, 9528,10296,11064,11832,12576,13536,14112,14688,15264,16416,
                              16992,17568,18336,19080,19848,20616,21384,22152,22920,23688,24496,
                              25456,25456,26416,27376,28336,29296,29296,30576,30576,31704,32856,
                              32856,34008,35160,35160,36696,36696,37888,37888,39232,40576,40576,
                              40576,42368,42368,43816,43816,45352,45352,46888,46888,48936,48936,
                              48936,51024,51024,52752,52752,52752,55056,55056,55056,55056,57336,
                              57336,57336,59256,59256,59256,61664,61664,61664,63776,63776,63776,
                              66592,66592,66592,68808,68808,68808,71112,71112,71112,73712,73712,
                              75376,75376,75376,75376,75376,75376,75376,75376,75376,75376,75376}};

// Transport Block Size from 3GPP TS 36.213 v10.3.0 table 7.1.7.2.3-1
uint32 TBS_71723[32] = {  40,  56,  72, 120, 136, 144, 176, 208, 224, 256, 280, 296, 328, 336, 392, 488,
                         552, 600, 632, 696, 776, 840, 904,1000,1064,1128,1224,1288,1384,1480,1608,1736};

/*******************************************************************************
                              LOCAL FUNCTION PROTOTYPES
*******************************************************************************/

/*********************************************************************
    Name: layer_mapper_ul / layer_demapper_ul

    Description: Maps complex-valued modulation symbols onto one or
                 several uplink layers / De-maps one or several uplink
                 layers into complex-valued modulation symbols

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.3.2A

    Notes: Currently only supports single antenna
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void layer_mapper_ul(complex *d,
                     uint32   M_symb,
                     uint8    N_ant,
                     uint32   N_codewords,
                     complex *x,
                     uint32  *M_layer_symb)
{
    if(N_codewords == 1)
    {
        if(N_ant == 1)
        {
            // 3GPP TS 36.211 v10.1.0 section 5.3.2A.1 and 5.3.2A.2
            *M_layer_symb = M_symb;
            for(uint32 i=0; i<M_symb; i++)
                x[i] = d[i];
        }
    }

    // FIXME: Handle N_ant != 1 and N_codewords != 1
}
void layer_demapper_ul(complex *x,
                       uint32   M_layer_symb,
                       uint8    N_ant,
                       uint32   N_codewords,
                       complex *d,
                       uint32  *M_symb)
{
    if(N_codewords == 1)
    {
        if(N_ant == 1)
        {
            // 3GPP TS 36.211 v10.1.0 section 5.3.2A.1 and 5.3.2A.2
            *M_symb = M_layer_symb;
            for(uint32 i=0; i<M_layer_symb; i++)
                d[i] = x[i];
        }
    }

    // FIXME: Handle N_ant != 1 and N_codewords != 1
}

/*********************************************************************
    Name: transform_precoding / transform_pre_decoding

    Description: DFT spreads the complex-valued symbols onto the
                 entire uplink bandwidth / DFT despreads the entire
                 uplink bandwidth into complex-valued symbols

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.3.3
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void transform_precoding(LIBLTE_PHY_STRUCT *phy_struct,
                         complex           *x,
                         uint32             M_layer_symb,
                         uint32             N_prb,
                         uint8              N_ant,
                         uint32             N_codewords,
                         complex           *y)
{
    // Calculate M_pusch_sc and 1/sqrt(M_pusch_sc)
    uint32 M_pusch_sc               = N_prb * phy_struct->N_sc_rb_ul;
    float  one_over_sqrt_M_pusch_sc = 1/sqrt(M_pusch_sc);

    for(uint32 i=0; i<12; i++)
    {
        for(uint32 j=0; j<M_pusch_sc; j++)
        {
            phy_struct->transform_precoding_in[j][0] = x[i*M_pusch_sc + j].real();
            phy_struct->transform_precoding_in[j][1] = x[i*M_pusch_sc + j].imag();
        }
        fftwf_execute(phy_struct->transform_precoding_plan[N_prb]);
        for(uint32 j=0; j<M_pusch_sc; j++)
            y[i*M_pusch_sc + j] = one_over_sqrt_M_pusch_sc * complex(phy_struct->transform_precoding_out[j][0],
                                                                     phy_struct->transform_precoding_out[j][1]);
    }
}
void transform_pre_decoding(LIBLTE_PHY_STRUCT *phy_struct,
                            complex           *y,
                            uint32             M_layer_symb,
                            uint32             N_prb,
                            uint8              N_ant,
                            uint32             N_codewords,
                            complex           *x)
{
    // Calculate M_pusch_sc and sqrt(M_pusch_sc)
    uint32 M_pusch_sc      = N_prb * phy_struct->N_sc_rb_ul;
    float  sqrt_M_pusch_sc = sqrt(M_pusch_sc);

    for(uint32 i=0; i<12; i++)
    {
        for(uint32 j=0; j<M_pusch_sc; j++)
        {
            phy_struct->transform_precoding_in[j][0] = y[i*M_pusch_sc + j].real();
            phy_struct->transform_precoding_in[j][1] = y[i*M_pusch_sc + j].imag();
        }
        fftwf_execute(phy_struct->transform_pre_decoding_plan[N_prb]);
        for(uint32 j=0; j<M_pusch_sc; j++)
            x[i*M_pusch_sc + j] = sqrt_M_pusch_sc * complex(phy_struct->transform_precoding_out[j][0],
                                                            phy_struct->transform_precoding_out[j][1]);
    }
}

/*********************************************************************
    Name: pre_coder_ul / de_pre_coder_ul

    Description: Generates a block of vectors to be mapped onto
                 resources on each uplink antenna port / Recovers a
                 block of vectors from resources on each uplink
                 antenna port

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.3.3A

    Notes: Currently only supports single antenna
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void pre_coder_ul(complex *y,
                  uint32   M_layer_symb,
                  uint8    N_ant,
                  uint8    N_layers,
                  complex *z,
                  uint32  *M_ap_symb)
{
    if(N_ant    == 1 &&
       N_layers == 1)
    {
        // 3GPP TS 36.211 v10.1.0 section 5.3.3A.1
        *M_ap_symb = M_layer_symb;
        for(uint32 i=0; i<M_layer_symb; i++)
            z[i] = y[i];
    }else{
        // FIXME
    }
}
void de_pre_coder_ul(complex *z,
                     complex *h,
                     uint32   M_ap_symb,
                     uint8    N_ant,
                     uint8    N_layers,
                     complex *y,
                     uint32  *M_layer_symb)
{
    if(N_ant    == 1 &&
       N_layers == 1)
    {
        // 3GPP TS 36.211 v10.1.0 section 5.3.3A.1
        *M_layer_symb = M_ap_symb;
        for(uint32 i=0; i<M_ap_symb; i++)
            y[i] = z[i] / h[i];
    }else{
        // FIXME
    }
}

/*********************************************************************
    Name: generate_prs_c

    Description: Generates the psuedo random sequence c

    Document Reference: 3GPP TS 36.211 v10.1.0 section 7.2
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void generate_prs_c(uint32  c_init,
                    uint32  len,
                    uint32 *c)
{
    // Initialize the 2nd m-sequence
    uint32 x2 = c_init;

    // Advance the 2nd m-sequence
    for(uint32 i=0; i<(1600-31); i++)
    {
        uint8 new_bit2 = ((x2 >> 3) ^ (x2 >> 2) ^ (x2 >> 1) ^ x2) & 0x1;

        x2 = (x2 >> 1) | (new_bit2 << 30);
    }

    // Initialize the 1st m-sequence
    uint32 x1 = 0x54D21B24; // This is the result of advancing the initial value of 0x00000001

    // Generate c
    for(uint32 i=0; i<len; i++)
    {
        uint8 new_bit1 = ((x1 >> 3) ^ x1) & 0x1;
        uint8 new_bit2 = ((x2 >> 3) ^ (x2 >> 2) ^ (x2 >> 1) ^ x2) & 0x1;

        x1 = (x1 >> 1) | (new_bit1 << 30);
        x2 = (x2 >> 1) | (new_bit2 << 30);

        c[i] = new_bit1 ^ new_bit2;
    }
}

/*********************************************************************
    Name: generate_ul_rs

    Description: Generates uplink reference signals

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.5.1
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void generate_ul_rs(LIBLTE_PHY_STRUCT         *phy_struct,
                    uint32                     N_slot,
                    uint32                     N_id_cell,
                    LIBLTE_PHY_CHAN_TYPE_ENUM  chan_type,
                    uint32                     delta_ss,
                    uint32                     N_prb,
                    float                      alpha,
                    bool                       group_hopping_enabled,
                    bool                       sequence_hopping_enabled,
                    complex                   *ul_rs)
{
    // Calculate M_sc_rs
    uint32 M_sc_rs = N_prb * LIBLTE_PHY_N_SC_RB_UL;

    // Determine N_zc_rs
    uint32 N_zc_rs = 0;
    for(uint32 i=UL_RS_PRIMES_LESS_THAN_2048_LEN-1; i>0; i--)
        if(UL_RS_PRIMES_LESS_THAN_2048[i] < M_sc_rs)
        {
            N_zc_rs = UL_RS_PRIMES_LESS_THAN_2048[i];
            break;
        }

    // Determine f_ss
    uint32 f_ss = N_id_cell % 30;
    if(LIBLTE_PHY_CHAN_TYPE_ULSCH == chan_type)
        f_ss = ((N_id_cell % 30) + delta_ss) % 30;

    // Determine u
    uint32 u = f_ss % 30;
    if(group_hopping_enabled)
    {
        generate_prs_c(N_id_cell/30, 160, phy_struct->ulrs_c);
        uint32 f_gh = 0;
        for(uint32 i=0; i<8; i++)
            f_gh += phy_struct->ulrs_c[8*N_slot + i] << i;
        f_gh %= 30;
        u     = (f_gh + f_ss) % 30;
    }

    // Determine v
    uint32 v = 0;
    if(M_sc_rs >= 6*LIBLTE_PHY_N_SC_RB_UL && !group_hopping_enabled &&
       sequence_hopping_enabled)
    {
        generate_prs_c(((N_id_cell/30) << 5) + f_ss, 20, phy_struct->ulrs_c);
        v = phy_struct->ulrs_c[N_slot];
    }

    // Determine r_bar_u_v
    if(M_sc_rs >= 3*LIBLTE_PHY_N_SC_RB_UL)
    {
        float q_bar = (float)N_zc_rs*(float)(u+1)/(float)31;
        int32 q;
        if((((uint32)(2*q_bar)) % 2) == 0)
        {
            q = (uint32)(q_bar + 0.5) + v;
        }else{
            q = (uint32)(q_bar + 0.5) - v;
        }
        for(uint32 i=0; i<N_zc_rs; i++)
            phy_struct->ulrs_x_q[i] = complex_polar(1, -M_PI*q*i*(i+1)/N_zc_rs);
        for(uint32 i=0; i<M_sc_rs; i++)
            phy_struct->ulrs_r_bar_u_v[i] = phy_struct->ulrs_x_q[i % N_zc_rs];
    }else if(M_sc_rs == LIBLTE_PHY_N_SC_RB_UL){
        for(uint32 i=0; i<M_sc_rs; i++)
            phy_struct->ulrs_r_bar_u_v[i] = complex_polar(1, UL_RS_5_5_1_2_1[u][i]*M_PI/4);
    }else{ // M_sc_rs == 2*LIBLTE_PHY_N_SC_RB_UL
        for(uint32 i=0; i<M_sc_rs; i++)
            phy_struct->ulrs_r_bar_u_v[i] = complex_polar(1, UL_RS_5_5_1_2_2[u][i]*M_PI/4);
    }

    // Calculate r_u_v (ul_rs_re and ul_rs_im)
    for(uint32 i=0; i<M_sc_rs; i++)
        ul_rs[i] = complex_polar(1, alpha*i) * phy_struct->ulrs_r_bar_u_v[i];
}

/*********************************************************************
    Name: generate_dmrs_pusch

    Description: Generates demodulation reference signals for the
                 uplink shared channel

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.5.2
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void generate_dmrs_pusch(LIBLTE_PHY_STRUCT *phy_struct,
                         uint32             N_subfr,
                         uint32             N_id_cell,
                         uint32             delta_ss,
                         uint32             cyclic_shift,
                         uint32             cyclic_shift_dci,
                         uint32             N_prb,
                         uint32             layer,
                         bool               group_hopping_enabled,
                         bool               sequence_hopping_enabled,
                         complex           *dmrs_0,
                         complex           *dmrs_1)
{
    // Calculate N_slot
    uint32 N_slot = N_subfr*2;

    // Set lambda
    uint32 lambda = layer;

    // Calculate f_ss_pusch
    uint32 f_ss_pusch = ((N_id_cell % 30) + delta_ss) % 30;

    // Generate c
    uint32 N_ul_symb = 7; // FIXME: Only handling normal CP
    generate_prs_c(((N_id_cell/30) << 5) + f_ss_pusch, 8*N_ul_symb*20, phy_struct->pusch_dmrs_c);

    // Calculate n_pn_ns
    uint32 n_pn_ns_1 = 0;
    uint32 n_pn_ns_2 = 0;
    for(uint32 i=0; i<8; i++)
    {
        n_pn_ns_1 += phy_struct->pusch_dmrs_c[8*N_ul_symb*N_slot + i] << i;
        n_pn_ns_2 += phy_struct->pusch_dmrs_c[8*N_ul_symb*(N_slot+1) + i] << i;
    }

    // Determine n_1_dmrs
    uint32 n_1_dmrs = N_1_DMRS_5_5_2_1_1_2[cyclic_shift];

    // Determine n_2_dmrs_lambda
    uint32 n_2_dmrs_lambda = N_2_DMRS_LAMBDA_5_5_2_1_1_1[cyclic_shift_dci][lambda];

    // Calculate n_cs_lambda
    uint32 n_cs_lambda_1 = (n_1_dmrs + n_2_dmrs_lambda + n_pn_ns_1) % 12;
    uint32 n_cs_lambda_2 = (n_1_dmrs + n_2_dmrs_lambda + n_pn_ns_2) % 12;

    // Calculate alpha_lambda
    float alpha_lambda_1 = 2*M_PI*n_cs_lambda_1/12;
    float alpha_lambda_2 = 2*M_PI*n_cs_lambda_2/12;

    // Generate the base reference signal
    uint32  M_sc_rb = N_prb * LIBLTE_PHY_N_SC_RB_UL;
    complex r_u_v_alpha_lambda[2][M_sc_rb];
    generate_ul_rs(phy_struct,
                   N_slot,
                   N_id_cell,
                   LIBLTE_PHY_CHAN_TYPE_ULSCH,
                   delta_ss,
                   N_prb,
                   alpha_lambda_1,
                   group_hopping_enabled,
                   sequence_hopping_enabled,
                   r_u_v_alpha_lambda[0]);
    generate_ul_rs(phy_struct,
                   N_slot+1,
                   N_id_cell,
                   LIBLTE_PHY_CHAN_TYPE_ULSCH,
                   delta_ss,
                   N_prb,
                   alpha_lambda_2,
                   group_hopping_enabled,
                   sequence_hopping_enabled,
                   r_u_v_alpha_lambda[1]);

    // Determine w vector
    // FIXME: Handle fixed values
    int32 w_vector[2] = {1, W_1_5_5_2_1_1_1[cyclic_shift_dci][lambda]};

    // Generate the PUSCH demodulation reference signal sequence
    for(uint32 i=0; i<M_sc_rb; i++)
    {
        dmrs_0[i] = complex(w_vector[0], 0) * r_u_v_alpha_lambda[0][i];
        dmrs_1[i] = complex(w_vector[1], 0) * r_u_v_alpha_lambda[1][i];
    }

    // FIXME: Add precoding to arrive at r_tilda
}

/*********************************************************************
    Name: generate_dmrs_pucch

    Description: Generates demodulation reference signals for the
                 uplink control channel

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.5.2
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void generate_dmrs_pucch(LIBLTE_PHY_STRUCT *phy_struct,
                         uint32             N_subfr,
                         uint32             N_id_cell,
                         uint32             delta_ss,
                         bool               group_hopping_enabled,
                         bool               sequence_hopping_enabled,
                         uint8              N_cs_1,
                         uint8              N_1_p_pucch,
                         uint8              delta_pucch_shift,
                         uint8              N_ant,
                         complex           *dmrs_0,
                         complex           *dmrs_1)
{
    // Calculate N_slot
    uint32 N_slot = N_subfr*2;

    // Calculate N_prime
    uint32 N_prime = LIBLTE_PHY_N_SC_RB_UL;
    if(N_1_p_pucch < (3*N_cs_1/delta_pucch_shift))
        N_prime = N_cs_1;

    // Calculate n_prime_p
    // FIXME: Only supporting normal cyclic prefix
    uint32 h_p;
    if(N_1_p_pucch < (3*N_cs_1/delta_pucch_shift))
    {
        phy_struct->pucch_n_prime_p[N_subfr][N_1_p_pucch][0] = N_1_p_pucch;
        h_p                                                  = (phy_struct->pucch_n_prime_p[N_subfr][N_1_p_pucch][0] + 2) % (3*N_prime/delta_pucch_shift);
        phy_struct->pucch_n_prime_p[N_subfr][N_1_p_pucch][1] = (h_p/3) + (h_p%3)*N_prime/delta_pucch_shift;
    }else{
        phy_struct->pucch_n_prime_p[N_subfr][N_1_p_pucch][0] = (N_1_p_pucch - 3*N_cs_1/delta_pucch_shift) % (3*LIBLTE_PHY_N_SC_RB_UL/delta_pucch_shift);
        phy_struct->pucch_n_prime_p[N_subfr][N_1_p_pucch][1] = ((3*(phy_struct->pucch_n_prime_p[N_subfr][N_1_p_pucch][0]+1)) % ((3*LIBLTE_PHY_N_SC_RB_UL/delta_pucch_shift)+1)) - 1;
    }

    // Calculate N_oc_p
    for(uint32 i=0; i<2; i++)
        phy_struct->pucch_n_oc_p[N_subfr][N_1_p_pucch][i] = phy_struct->pucch_n_prime_p[N_subfr][N_1_p_pucch][i]*delta_pucch_shift/N_prime;

    // Generate c
    uint32 N_ul_symb = 7; // FIXME: Only handling normal CP
    generate_prs_c(N_id_cell, 8*N_ul_symb*20, phy_struct->pucch_dmrs_c);

    // Calculate N_cs_cell
    uint32 n_cs_cell[2][N_ul_symb];
    for(uint32 i=0; i<2; i++)
    {
        for(uint32 j=0; j<N_ul_symb; j++)
        {
            n_cs_cell[i][j] = 0;
            for(uint32 idx=0; idx<8; idx++)
                n_cs_cell[i][j] += phy_struct->pucch_dmrs_c[8*N_ul_symb*(N_slot+i) + 8*j + idx] << idx;
        }
    }

    // Calculate N_cs_p
    // FIXME: Only supporting normal cyclic prefix
    uint32 n_cs_p[2][N_ul_symb];
    for(uint32 i=0; i<2; i++)
        for(uint32 j=0; j<N_ul_symb; j++)
            n_cs_p[i][j] = (n_cs_cell[i][j] +
                            ((phy_struct->pucch_n_prime_p[N_subfr][N_1_p_pucch][i]*delta_pucch_shift +
                              (phy_struct->pucch_n_oc_p[N_subfr][N_1_p_pucch][i] % delta_pucch_shift)) % N_prime)) % LIBLTE_PHY_N_SC_RB_UL;

    // Calculate alpha_p
    float alpha_p[2][N_ul_symb];
    for(uint32 i=0; i<2; i++)
        for(uint32 j=0; j<N_ul_symb; j++)
            alpha_p[i][j] = 2*M_PI*n_cs_p[i][j]/LIBLTE_PHY_N_SC_RB_UL;

    // Generate the base reference signal
    for(uint32 i=0; i<2; i++)
        for(uint32 j=0; j<N_ul_symb; j++)
            generate_ul_rs(phy_struct,
                           N_slot + i,
                           N_id_cell,
                           LIBLTE_PHY_CHAN_TYPE_ULCCH,
                           delta_ss,
                           1,
                           alpha_p[i][j],
                           group_hopping_enabled,
                           sequence_hopping_enabled,
                           phy_struct->pucch_r_u_v_alpha_p[N_subfr][N_1_p_pucch][i][j]);

    // Generate the PUCCH demodulation reference signal sequence
    complex one_over_sqrt_n_ant = complex(1/sqrt(N_ant), 0);
    for(uint32 i=0; i<2; i++)
    {
        complex *dmrs = dmrs_1;
        if(0 == i)
            dmrs = dmrs_0;
        for(uint32 j=0; j<LIBLTE_PHY_M_PUCCH_RS; j++)
        {
            complex w = complex_polar(1, W_5_5_2_2_1_2_phase[phy_struct->pucch_n_oc_p[N_subfr][N_1_p_pucch][i]][j]);
            for(uint32 k=0; k<LIBLTE_PHY_N_SC_RB_UL; k++)
            {
                complex alpha = phy_struct->pucch_r_u_v_alpha_p[N_subfr][N_1_p_pucch][i][j+2][k];
                // z(m) = 1
                dmrs[j*LIBLTE_PHY_N_SC_RB_UL + k] = w * alpha * one_over_sqrt_n_ant;
            }
        }
    }
}

/*********************************************************************
    Name: prach_preamble_seq_gen

    Description: Generates all 64 PRACH preamble sequences

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.7.2
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void prach_preamble_seq_gen(LIBLTE_PHY_STRUCT *phy_struct,
                            uint32             root_seq_idx,
                            uint32             pre_format,
                            uint32             zczc,
                            bool               hs_flag)
{
    phy_struct->prach_root_seq_idx    = root_seq_idx;
    phy_struct->prach_preamble_format = pre_format;
    phy_struct->prach_zczc            = zczc;
    phy_struct->prach_hs_flag         = hs_flag;

    phy_struct->prach_N_x_u = 0;
    uint32 N_gen_pre        = 0;
    while(N_gen_pre < 64)
    {
        // Determine u and N_zc
        uint32 u               = PRACH_5_7_2_4[root_seq_idx+phy_struct->prach_N_x_u];
        phy_struct->prach_N_zc = 839;
        if(4 == pre_format)
        {
            u                      = PRACH_5_7_2_5[root_seq_idx+phy_struct->prach_N_x_u];
            phy_struct->prach_N_zc = 139;
        }

        // Generate x_u
        for(uint32 i=0; i<phy_struct->prach_N_zc; i++)
            phy_struct->prach_x_u[phy_struct->prach_N_x_u][i] = complex_polar(1, -M_PI*u*i*(i+1)/phy_struct->prach_N_zc);

        // Determine N_cs
        uint32 N_cs;
        if(4 == pre_format)
        {
            N_cs = PRACH_5_7_2_3[zczc];
        }else{
            if(hs_flag)
            {
                N_cs = PRACH_5_7_2_2_RS[zczc];
            }else{
                N_cs = PRACH_5_7_2_2_URS[zczc];
            }
        }

        // Determine v_max
        uint32 v_max;
        uint32 N_RA_shift = 0;
        uint32 d_start    = 0;
        if(hs_flag)
        {
            // Determine d_u
            uint32 p;
            uint32 d_u;
            for(p=1; p<=phy_struct->prach_N_zc; p++)
                if(((p*u) % phy_struct->prach_N_zc) == 1)
                    break;
            if(p >= 0 && p < phy_struct->prach_N_zc/2)
            {
                d_u = p;
            }else{
                d_u = phy_struct->prach_N_zc - p;
            }

            // Determine N_RA_shift, d_start, N_RA_group, and N_neg_RA_shift
            uint32 N_RA_group;
            uint32 N_neg_RA_shift;
            if(d_u >= N_cs && d_u < phy_struct->prach_N_zc/3)
            {
                N_RA_shift     = d_u/N_cs;
                d_start        = 2*d_u + N_RA_shift*N_cs;
                N_RA_group     = phy_struct->prach_N_zc/d_start;
                N_neg_RA_shift = (phy_struct->prach_N_zc - 2*d_u - N_RA_group*d_start)/N_cs;
                if(N_neg_RA_shift < 0)
                    N_neg_RA_shift = 0;
            }else{
                N_RA_shift     = (phy_struct->prach_N_zc - 2*d_u)/N_cs;
                d_start        = phy_struct->prach_N_zc - 2*d_u + N_RA_shift*N_cs;
                N_RA_group     = d_u/d_start;
                N_neg_RA_shift = (d_u - N_RA_group*d_start)/N_cs;
                if(N_neg_RA_shift < 0)
                    N_neg_RA_shift = 0;
                if(N_neg_RA_shift > N_RA_shift)
                    N_neg_RA_shift = N_RA_shift;
            }

            // Restricted set
            v_max = N_RA_shift*N_RA_group + N_neg_RA_shift - 1;
        }else{
            // Unrestricted set
            v_max = (phy_struct->prach_N_zc/N_cs)-1;
            if(0 == N_cs)
                v_max = 0;
        }

        // Generate x_u_v
        for(uint32 v=0; v<=v_max; v++)
        {
            uint32 C_v;
            if(hs_flag)
            {
                // Restricted set
                C_v = d_start*floor(v/N_RA_shift) + (v % N_RA_shift)*N_cs;
            }else{
                // Unrestricted set
                C_v = v*N_cs;
            }

            for(uint32 i=0; i<phy_struct->prach_N_zc; i++)
                phy_struct->prach_x_u_v[N_gen_pre][i] = phy_struct->prach_x_u[phy_struct->prach_N_x_u][(i+C_v) % phy_struct->prach_N_zc];

            // Determine if enough preambles are generated
            N_gen_pre++;
            if(N_gen_pre >= 64)
                break;
        }

        // Move to the next root sequence
        phy_struct->prach_N_x_u++;
    }
}

/*********************************************************************
    Name: layer_mapper_dl / layer_demapper_dl

    Description: Maps complex-valued modulation symbols onto one or
                 several downlink layers / De-maps one or several
                 downlink layers into complex-valued modulation
                 symbols

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.3.3

    Notes: Currently only supports single antenna or TX diversity
*********************************************************************/
// Defines
#define RX_NULL_SYMB 10000
#define TX_NULL_SYMB 100
// Enums
// Structs
// Functions
void layer_mapper_dl(complex                        *d,
                     uint32                          M_symb,
                     uint8                           N_ant,
                     uint32                          N_codewords,
                     LIBLTE_PHY_PRE_CODER_TYPE_ENUM  type,
                     complex                        *x,
                     uint32                         *M_layer_symb)
{
    if(N_ant       == 1 &&
       N_codewords == 1)
    {
        // 3GPP TS 36.211 v10.1.0 section 6.3.3.1
        *M_layer_symb = M_symb;
        for(uint32 i=0; i<M_symb; i++)
            x[i] = d[i];
    }else{
        if(LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY == type)
        {
            // 3GPP TS 36.211 v10.1.0 section 6.3.3.3
            if(N_ant == 2)
            {
                *M_layer_symb = M_symb/2;
                for(uint32 i=0; i<*M_layer_symb; i++)
                {
                    x[i]               = d[2*i];
                    x[*M_layer_symb+i] = d[2*i+1];
                }
            }else{ // N_ant == 4
                if((M_symb % 4) == 0)
                {
                    *M_layer_symb = M_symb/4;
                }else{
                    *M_layer_symb = (M_symb+2)/4;
                }
                for(uint32 i=0; i<*M_layer_symb; i++)
                {
                    x[i]                   = d[4*i];
                    x[*M_layer_symb+i]     = d[4*i+1];
                    x[2*(*M_layer_symb)+i] = d[4*i+2];
                    x[3*(*M_layer_symb)+i] = d[4*i+3];
                }
            }
        }else{
            if(N_ant == 2)
            {
                if(N_codewords == 1)
                {
                    *M_layer_symb = M_symb/2;
                    for(uint32 i=0; i<*M_layer_symb; i++)
                    {
                        x[i]               = d[2*i];
                        x[*M_layer_symb+i] = d[2*i+1];
                    }
                }else{ // N_codewords == 2
                    *M_layer_symb = M_symb;
                    for(uint32 i=0; i<*M_layer_symb; i++)
                    {
                        x[i]               = d[i];
                        x[*M_layer_symb+i] = d[M_symb+i];
                    }
                }
            }else if(N_ant == 3){
                if(N_codewords == 1)
                {
                    *M_layer_symb = M_symb/3;
                    for(uint32 i=0; i<*M_layer_symb; i++)
                    {
                        x[i]                   = d[3*i];
                        x[*M_layer_symb+i]     = d[3*i+1];
                        x[2*(*M_layer_symb)+i] = d[3*i+2];
                    }
                }else{ // N_codewords == 2
                    // FIXME
                }
            }else if(N_ant == 4){
                if(N_codewords == 1)
                {
                    *M_layer_symb = M_symb/4;
                    for(uint32 i=0; i<*M_layer_symb; i++)
                    {
                        x[i]                   = d[4*i];
                        x[*M_layer_symb+i]     = d[4*i+1];
                        x[2*(*M_layer_symb)+i] = d[4*i+2];
                        x[3*(*M_layer_symb)+i] = d[4*i+3];
                    }
                }else{ // N_codewords == 2
                    *M_layer_symb = M_symb/2;
                    for(uint32 i=0; i<*M_layer_symb; i++)
                    {
                        x[i]                   = d[2*i];
                        x[*M_layer_symb+i]     = d[2*i+1];
                        x[2*(*M_layer_symb)+i] = d[M_symb+2*i];
                        x[3*(*M_layer_symb)+i] = d[M_symb+2*i+1];
                    }
                }
            }else if(N_ant == 5){
                // FIXME
            }else if(N_ant == 6){
                *M_layer_symb = M_symb/3;
                for(uint32 i=0; i<*M_layer_symb; i++)
                {
                    x[i]                   = d[3*i];
                    x[*M_layer_symb+i]     = d[3*i+1];
                    x[2*(*M_layer_symb)+i] = d[3*i+2];
                    x[3*(*M_layer_symb)+i] = d[M_symb+3*i];
                    x[4*(*M_layer_symb)+i] = d[M_symb+3*i+1];
                    x[5*(*M_layer_symb)+i] = d[M_symb+3*i+2];
                }
            }else if(N_ant == 7){
                // FIXME
            }else{ // N_ant == 8
                *M_layer_symb = M_symb/4;
                for(uint32 i=0; i<*M_layer_symb; i++)
                {
                    x[i]                   = d[4*i];
                    x[*M_layer_symb+i]     = d[4*i+1];
                    x[2*(*M_layer_symb)+i] = d[4*i+2];
                    x[3*(*M_layer_symb)+i] = d[4*i+3];
                    x[4*(*M_layer_symb)+i] = d[M_symb+4*i];
                    x[5*(*M_layer_symb)+i] = d[M_symb+4*i+1];
                    x[6*(*M_layer_symb)+i] = d[M_symb+4*i+2];
                    x[7*(*M_layer_symb)+i] = d[M_symb+4*i+3];
                }
            }
        }
    }
}
void layer_demapper_dl(complex                        *x,
                       uint32                          M_layer_symb,
                       uint8                           N_ant,
                       uint32                          N_codewords,
                       LIBLTE_PHY_PRE_CODER_TYPE_ENUM  type,
                       complex                        *d,
                       uint32                         *M_symb)
{
    // FIXME: Only supports TX diversity
    // Index all arrays
    complex *x_ptr[N_ant];
    for(uint32 p=0; p<N_ant; p++)
        x_ptr[p] = &x[p*M_layer_symb];

    // 3GPP TS 36.211 v10.1.0 sections 6.3.3.1 and 6.3.3.3
    *M_symb = M_layer_symb*N_ant;
    if(N_ant                    == 4                                   &&
       x_ptr[2][M_layer_symb-1] == complex(RX_NULL_SYMB, RX_NULL_SYMB) &&
       x_ptr[3][M_layer_symb-1] == complex(RX_NULL_SYMB, RX_NULL_SYMB))
        *M_symb = *M_symb - 2;

    for(uint32 p=0; p<N_ant; p++)
        for(uint32 i=0; i<M_layer_symb; i++)
            d[i*N_ant+p] = x_ptr[p][i];
}

/*********************************************************************
    Name: pre_coder_dl / de_pre_coder_dl

    Description: Generates a block of vectors to be mapped onto
                 resources on each downlink antenna port / Alamouti
                 decodes a block of vectors from resources on each
                 downlink antenna port

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.3.4

    NOTES: Currently only supports signle antenna or TX diversity
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void pre_coder_dl(complex                        *x,
                  uint32                          M_layer_symb,
                  uint8                           N_ant,
                  LIBLTE_PHY_PRE_CODER_TYPE_ENUM  type,
                  complex                        *y,
                  uint32                          y_len,
                  uint32                         *M_ap_symb)
{
    // Index all arrays
    complex *x_ptr[N_ant];
    complex *y_ptr[N_ant];
    for(uint32 p=0; p<N_ant; p++)
    {
        x_ptr[p] = &x[p*M_layer_symb];
        y_ptr[p] = &y[p*y_len];
    }

    float one_over_sqrt_2 = 1/sqrt(2);
    if(N_ant == 1)
    {
        // 3GPP TS 36.211 v10.1.0 section 6.3.4.1
        *M_ap_symb = M_layer_symb;
        for(uint32 i=0; i<*M_ap_symb; i++)
            y_ptr[0][i] = x_ptr[0][i];
    }else if(N_ant == 2){
        if(LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY == type)
        {
            // 3GPP TS 36.211 v10.1.0 section 6.3.4.3
            *M_ap_symb = 2*M_layer_symb;
            for(uint32 i=0; i<M_layer_symb; i++)
            {
                y_ptr[0][2*i+0] = +one_over_sqrt_2 * x_ptr[0][i];
                y_ptr[1][2*i+0] = -one_over_sqrt_2 * std::conj(x_ptr[1][i]);
                y_ptr[0][2*i+1] = +one_over_sqrt_2 * x_ptr[1][i];
                y_ptr[1][2*i+1] = +one_over_sqrt_2 * std::conj(x_ptr[0][i]);
            }
        }else{
            // FIXME: Currently only supporting TX Diversity
        }
    }else{
        if(LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY == type)
        {
            // 3GPP TS 36.211 v10.1.0 section 6.3.4.3
            if(x_ptr[2][M_layer_symb-1] == complex(TX_NULL_SYMB, TX_NULL_SYMB) &&
               x_ptr[3][M_layer_symb-1] == complex(TX_NULL_SYMB, TX_NULL_SYMB))
            {
                *M_ap_symb = 4*M_layer_symb - 2;
            }else{
                *M_ap_symb = 4*M_layer_symb;
            }
            for(uint32 i=0; i<M_layer_symb; i++)
            {
                y_ptr[0][4*i+0] = +one_over_sqrt_2 * x_ptr[0][i];
                y_ptr[1][4*i+0] = complex(0, 0);
                y_ptr[2][4*i+0] = -one_over_sqrt_2 * std::conj(x_ptr[1][i]);
                y_ptr[3][4*i+0] = complex(0, 0);
                y_ptr[0][4*i+1] = +one_over_sqrt_2 * x_ptr[1][i];
                y_ptr[1][4*i+1] = complex(0, 0);
                y_ptr[2][4*i+1] = +one_over_sqrt_2 * std::conj(x_ptr[0][i]);
                y_ptr[3][4*i+1] = complex(0, 0);
                y_ptr[0][4*i+2] = complex(0, 0);
                y_ptr[1][4*i+2] = +one_over_sqrt_2 * x_ptr[2][i];
                y_ptr[2][4*i+2] = complex(0, 0);
                y_ptr[3][4*i+2] = -one_over_sqrt_2 * std::conj(x_ptr[3][i]);
                y_ptr[0][4*i+3] = complex(0, 0);
                y_ptr[1][4*i+3] = +one_over_sqrt_2 * x_ptr[3][i];
                y_ptr[2][4*i+3] = complex(0, 0);
                y_ptr[3][4*i+3] = +one_over_sqrt_2 * std::conj(x_ptr[2][i]);
            }
        }else{
            // FIXME: Currently only supporting TX Diversity
        }
    }
}
void de_pre_coder_dl(complex                        *y,
                     complex                        *h,
                     uint32                          h_len,
                     uint32                          M_ap_symb,
                     uint8                           N_ant,
                     LIBLTE_PHY_PRE_CODER_TYPE_ENUM  type,
                     complex                        *x,
                     uint32                         *M_layer_symb)
{
    // Index all arrays
    complex *h_ptr[N_ant];
    complex *x_ptr[N_ant];
    for(uint32 p=0; p<N_ant; p++)
    {
        h_ptr[p] = &h[p*h_len];
        x_ptr[p] = &x[p*(M_ap_symb/N_ant)];
    }

    if(N_ant == 1)
    {
        // 3GPP TS 36.211 v10.1.0 section 6.3.4.1
        *M_layer_symb = M_ap_symb;
        for(uint32 i=0; i<*M_layer_symb; i++)
            x_ptr[0][i] = y[i] / h_ptr[0][i];
    }else if(N_ant == 2){
        // 3GPP TS 36.211 v10.1.0 section 6.3.4.3
        *M_layer_symb = M_ap_symb/2;
        for(uint32 i=0; i<*M_layer_symb; i++)
        {
            x_ptr[0][i] = ((std::conj(h_ptr[0][i*2+0]) * y[i*2+0] +
                            h_ptr[1][i*2+1] * std::conj(y[i*2+1])) /
                           std::abs(complex(std::norm(h_ptr[0][i*2+0]),
                                            std::norm(h_ptr[1][i*2+1]))));
            x_ptr[1][i] = -(std::conj(std::conj(h_ptr[0][i*2+1]) * y[i*2+0] -
                                      h_ptr[1][i*2+0] * std::conj(y[i*2+1])) /
                            std::abs(complex(std::norm(h_ptr[1][i*2+0]),
                                             std::norm(h_ptr[0][i*2+1]))));
        }
    }else{ // N_ant == 4
        // 3GPP TS 36.211 v10.1.0 section 6.3.4.3
        *M_layer_symb = M_ap_symb/4;
        uint32 i;
        for(i=0; i<*M_layer_symb; i++)
        {
            x_ptr[0][i] = ((std::conj(h_ptr[0][i*4+0]) * y[i*4+0] +
                            h_ptr[2][i*4+1] * std::conj(y[i*4+1])) /
                           std::abs(complex(std::norm(h_ptr[0][i*4+0]),
                                            std::norm(h_ptr[2][i*4+1]))));
            x_ptr[1][i] = -(std::conj(std::conj(h_ptr[0][i*4+1]) * y[i*4+0] -
                                      h_ptr[2][i*4+0] * std::conj(y[i*4+1])) /
                            std::abs(complex(std::norm(h_ptr[0][i*4+1]),
                                             std::norm(h_ptr[2][i*4+0]))));
            x_ptr[2][i] = ((std::conj(h_ptr[1][i*4+2]) * y[i*4+2] +
                            h_ptr[3][i*4+3] * std::conj(y[i*4+3])) /
                           std::abs(complex(std::norm(h_ptr[1][i*4+2]),
                                            std::norm(h_ptr[3][i*4+3]))));
            x_ptr[3][i] = -(std::conj(std::conj(h_ptr[1][i*4+3]) * y[i*4+2] -
                                      h_ptr[3][i*4+2] * std::conj(y[i*4+3])) /
                            std::abs(complex(std::norm(h_ptr[1][i*4+3]),
                                             std::norm(h_ptr[3][i*4+2]))));
        }
        if((M_ap_symb % 4) != 0)
        {
            *M_layer_symb    = (M_ap_symb+2)/4;
            float h_norm_0_2 = std::norm(complex(std::norm(h_ptr[0][i*4+0]),
                                                 std::norm(h_ptr[2][i*4+0])));
            x_ptr[0][i]      = complex((h_ptr[0][i*4+0].real() * y[i*4+0].real() +
                                        h_ptr[0][i*4+0].imag() * y[i*4+0].imag() +
                                        h_ptr[2][i*4+0].real() * y[i*4+1].real() +
                                        h_ptr[2][i*4+0].imag() * y[i*4+1].imag()) / h_norm_0_2,
                                       (h_ptr[0][i*4+0].real() * y[i*4+0].imag() -
                                        h_ptr[0][i*4+0].imag() * y[i*4+0].real() -
                                        h_ptr[2][i*4+0].real() * y[i*4+1].imag() +
                                        h_ptr[2][i*4+0].imag() * y[i*4+1].real()) / h_norm_0_2);
            x_ptr[1][i]      = complex((-h_ptr[2][i*4+0].real() * y[i*4+0].real() -
                                        h_ptr[2][i*4+0].imag() * y[i*4+0].imag() +
                                        h_ptr[0][i*4+0].real() * y[i*4+1].real() +
                                        h_ptr[0][i*4+0].imag() * y[i*4+1].imag()) / h_norm_0_2,
                                       (-h_ptr[2][i*4+0].real() * y[i*4+0].imag() +
                                        h_ptr[2][i*4+0].imag() * y[i*4+0].real() -
                                        h_ptr[0][i*4+0].real() * y[i*4+1].real() +
                                        h_ptr[0][i*4+0].imag() * y[i*4+1].imag()) / h_norm_0_2);
            x_ptr[2][i]      = complex(RX_NULL_SYMB, RX_NULL_SYMB);
            x_ptr[3][i]      = complex(RX_NULL_SYMB, RX_NULL_SYMB);
        }
    }
}

/*********************************************************************
    Name: cfi_channel_encode / cfi_channel_decode

    Description: Channel encodes the Control Format Indicator
                 channel / Channel decodes the Control Format
                 Indicator channel

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.3.4
*********************************************************************/
// Defines
#define CFI_N_ACCEPTABLE_BERS 4
// Enums
// Structs
// Functions
void cfi_channel_encode(LIBLTE_PHY_STRUCT *phy_struct,
                        uint32             cfi,
                        uint8             *out_bits,
                        uint32            *N_out_bits)
{
    *N_out_bits = 32;
    uint8 *cfi_bits;
    if(1 == cfi)
    {
        cfi_bits = CFI_BITS_1;
    }else if(2 == cfi){
        cfi_bits = CFI_BITS_2;
    }else if(3 == cfi){
        cfi_bits = CFI_BITS_3;
    }else{
        cfi_bits = CFI_BITS_4;
    }
    for(uint32 i=0; i<*N_out_bits; i++)
        out_bits[i] = cfi_bits[i];
}
LIBLTE_ERROR_ENUM cfi_channel_decode(LIBLTE_PHY_STRUCT *phy_struct,
                                     float             *in_bits,
                                     uint32             N_in_bits,
                                     uint32            *cfi)
{
    // Calculate the number of bit errors for each CFI
    uint32 ber[4] = {0, 0, 0, 0};
    for(uint32 i=0; i<N_in_bits; i++)
    {
        // Convert from soft NRZ to hard bit
        uint8 in_bit = 1;
        if(in_bits[i] >= 0)
            in_bit = 0;

        if(CFI_BITS_1[i] != in_bit)
            ber[0]++;
        if(CFI_BITS_2[i] != in_bit)
            ber[1]++;
        if(CFI_BITS_3[i] != in_bit)
            ber[2]++;
        if(CFI_BITS_4[i] != in_bit)
            ber[3]++;
    }

    // Find the CFI with the least number of bit errors
    uint32 min_ber = 32;
    uint32 cfi_num;
    for(uint32 i=0; i<4; i++)
    {
        if(ber[i] < min_ber)
        {
            min_ber = ber[i];
            cfi_num = i+1;
        }
    }

    // Make sure the number of bit errors is acceptably low
    if(min_ber < CFI_N_ACCEPTABLE_BERS)
    {
        *cfi = cfi_num;
        return LIBLTE_SUCCESS;
    }

    return LIBLTE_ERROR_INVALID_CRC;
}

/*********************************************************************
    Name: get_soft_decision

    Description: Determines the magnitude of the soft decision

    Document Reference: N/A
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
inline float get_soft_decision(complex rx,
                               complex exp,
                               float   max_dist)
{
    float dist = std::abs(rx - exp);

    if(dist >= (max_dist - (max_dist/120)))
        dist = max_dist - (max_dist/120);

    return (max_dist - dist) / max_dist;
}

/*********************************************************************
    Name: modulation_mapper / modulation_demapper

    Description: Maps binary digits to complex-valued modulation
                 symbols / Maps complex-valued modulation symbols to
                 soft digits

    Document Reference: 3GPP TS 36.211 v10.1.0 section 7.1
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void modulation_mapper(uint8                           *bits,
                       uint32                           N_bits,
                       LIBLTE_PHY_MODULATION_TYPE_ENUM  type,
                       complex                         *d,
                       uint32                          *M_symb)
{
    switch(type)
    {
    case LIBLTE_PHY_MODULATION_TYPE_BPSK:
        // 3GPP TS 36.211 v10.1.0 section 7.1.1
        for(uint32 i=0; i<N_bits; i++)
            d[i] = mod_map_bpsk[bits[i]];
        *M_symb = N_bits;
        break;
    case LIBLTE_PHY_MODULATION_TYPE_QPSK:
        // 3GPP TS 36.211 v10.1.0 section 7.1.2

        for(uint32 i=0; i<(N_bits/2); i++)
            d[i] = mod_map_qpsk[(bits[i*2] << 1) | bits[i*2+1]];
        *M_symb = (N_bits/2);
        if((N_bits % 2) != 0)
        {
            *M_symb = (N_bits/2) + 1;
            // Add a trailing zero
            d[N_bits/2] = mod_map_qpsk[bits[N_bits-1]];
        }
        break;
    case LIBLTE_PHY_MODULATION_TYPE_16QAM:
        // 3GPP TS 36.211 v10.1.0 section 7.1.3
        for(uint32 i=0; i<(N_bits/4); i++)
            d[i] = mod_map_16qam[(bits[i*4+0] << 3) | (bits[i*4+1] << 2) |
                                 (bits[i*4+2] << 1) | bits[i*4+3]];
        *M_symb = (N_bits/4);
        if((N_bits % 4) != 0)
        {
            *M_symb = (N_bits/4) + 1;
            uint32 input;
            if((N_bits % 4) == 1)
            {
                input = bits[N_bits-1] << 3;
            }else if((N_bits % 4) == 2){
                input = ((bits[N_bits-2] << 3) | (bits[N_bits-1] << 2));
            }else if((N_bits % 4) == 3){
                input = ((bits[N_bits-3] << 3) | (bits[N_bits-2] << 2) | (bits[N_bits-1] << 1));
            }
            d[N_bits/4] = mod_map_16qam[input];
        }
        break;
    case LIBLTE_PHY_MODULATION_TYPE_64QAM:
        // 3GPP TS 36.211 v10.1.0 section 7.1.4
        for(uint32 i=0; i<(N_bits/6); i++)
            d[i] = mod_map_64qam[(bits[i*6+0] << 5) | (bits[i*6+1] << 4) | (bits[i*6+2] << 3) |
                                 (bits[i*6+3] << 2) | (bits[i*6+4] << 1) | bits[i*6+5]];
        *M_symb = (N_bits/6);
        if((N_bits % 6) != 0)
        {
            *M_symb = (N_bits/6) + 1;
            uint32 input;
            if((N_bits % 6) == 1)
            {
                input = bits[N_bits-1] << 5;
            }else if((N_bits % 6) == 2){
                input = ((bits[N_bits-2] << 5) | (bits[N_bits-1] << 4));
            }else if((N_bits % 6) == 3){
                input = ((bits[N_bits-3] << 5) | (bits[N_bits-2] << 4) | (bits[N_bits-1] << 3));
            }else if((N_bits % 6) == 4){
                input = ((bits[N_bits-4] << 5) | (bits[N_bits-3] << 4) |
                         (bits[N_bits-2] << 3) | (bits[N_bits-1] << 2));
            }else if((N_bits % 6) == 5){
                input = ((bits[N_bits-5] << 5) | (bits[N_bits-4] << 4) | (bits[N_bits-3] << 3) |
                         (bits[N_bits-2] << 2) | (bits[N_bits-1] << 1));
            }
            d[N_bits/6] = mod_map_64qam[input];
        }
        break;
    default:
        break;
    }
}
void modulation_demapper(complex                         *d,
                         uint32                           M_symb,
                         LIBLTE_PHY_MODULATION_TYPE_ENUM  type,
                         int8                            *bits,
                         uint32                          *N_bits)
{
    if(LIBLTE_PHY_MODULATION_TYPE_BPSK == type)
    {
        // 3GPP TS 36.211 v10.1.0 section 7.1.1
        float one_over_root_2 = 1/sqrt(2);
        *N_bits               = M_symb;
        for(uint32 i=0; i<M_symb; i++)
        {
            float ang = std::arg(d[i]);
            float sd;
            if((ang > -M_PI/4) && (ang < 3*M_PI/4))
            {
                sd = get_soft_decision(d[i], mod_map_bpsk[0], one_over_root_2);
            }else{
                sd = -get_soft_decision(d[i], mod_map_bpsk[1], one_over_root_2);
            }
            bits[i] = (int8)(127*sd);
        }
    }else if(LIBLTE_PHY_MODULATION_TYPE_QPSK == type){
        // 3GPP TS 36.211 v10.1.0 section 7.1.2
        float one_over_root_2 = 1/sqrt(2);
        *N_bits               = M_symb*2;
        for(uint32 i=0; i<M_symb; i++)
        {
            float sd;
            if(d[i].real() > 0)
            {
                sd = get_soft_decision(d[i].real(), one_over_root_2, one_over_root_2);
            }else{
                sd = -get_soft_decision(d[i].real(), -one_over_root_2, one_over_root_2);
            }
            bits[i*2] = (int8)(127*sd);
            if(d[i].imag() > 0)
            {
                sd = get_soft_decision(d[i].imag(), one_over_root_2, one_over_root_2);
            }else{
                sd = -get_soft_decision(d[i].imag(), -one_over_root_2, one_over_root_2);
            }
            bits[i*2+1] = (int8)(127*sd);
        }
    }else if(LIBLTE_PHY_MODULATION_TYPE_16QAM == type){
        // 3GPP TS 36.211 v10.1.0 section 7.1.3
        float one_over_root_10   = 1/sqrt(10);
        float two_over_root_10   = 2 * one_over_root_10;
        float three_over_root_10 = 3 * one_over_root_10;
        *N_bits                  = M_symb*4;
        for(uint32 i=0; i<M_symb; i++)
        {
            float sd1;
            float sd2;
            if(d[i].real() > 0)
            {
                sd1 = get_soft_decision(d[i].real(), one_over_root_10, one_over_root_10);
                sd2 = get_soft_decision(d[i].real(), three_over_root_10, one_over_root_10);
            }else{
                sd1 = -get_soft_decision(d[i].real(), -one_over_root_10, one_over_root_10);
                sd2 = -get_soft_decision(d[i].real(), -three_over_root_10, one_over_root_10);
            }
            if(fabs(sd1) > fabs(sd2))
            {
                bits[i*4] = (int8)(127*sd1);
            }else{
                bits[i*4] = (int8)(127*sd2);
            }
            if(d[i].imag() > 0)
            {
                sd1 = get_soft_decision(d[i].imag(), one_over_root_10, one_over_root_10);
                sd2 = get_soft_decision(d[i].imag(), three_over_root_10, one_over_root_10);
            }else{
                sd1 = -get_soft_decision(d[i].imag(), -one_over_root_10, one_over_root_10);
                sd2 = -get_soft_decision(d[i].imag(), -three_over_root_10, one_over_root_10);
            }
            if(fabs(sd1) > fabs(sd2))
            {
                bits[i*4+1] = (int8)(127*sd1);
            }else{
                bits[i*4+1] = (int8)(127*sd2);
            }
            float tmp = fabs(d[i].real()) - two_over_root_10;
            if(tmp < 0)
            {
                sd1 = get_soft_decision(tmp, -one_over_root_10, one_over_root_10);
            }else{
                sd1 = -get_soft_decision(tmp, one_over_root_10, one_over_root_10);
            }
            bits[i*4+2] = (int8)(127*sd1);
            tmp = fabs(d[i].imag()) - two_over_root_10;
            if(tmp < 0)
            {
                sd1 = get_soft_decision(tmp, -one_over_root_10, one_over_root_10);
            }else{
                sd1 = -get_soft_decision(tmp, one_over_root_10, one_over_root_10);
            }
            bits[i*4+3] = (int8)(127*sd1);
        }
    }else{ // LIBLTE_PHY_MODULATION_TYPE_64QAM == type
        // 3GPP TS 36.211 v10.1.0 section 7.1.4
        float one_over_root_42   = 1/sqrt(42);
        float two_over_root_42   = 2 * one_over_root_42;
        float three_over_root_42 = 3 * one_over_root_42;
        float four_over_root_42  = 4 * one_over_root_42;
        float five_over_root_42  = 5 * one_over_root_42;
        float six_over_root_42   = 6 * one_over_root_42;
        float seven_over_root_42 = 7 * one_over_root_42;
        *N_bits                  = M_symb*6;
        for(uint32 i=0; i<M_symb; i++)
        {
            float sd1;
            float sd2;
            if(d[i].real() > 0)
            {
                sd1 = get_soft_decision(d[i].real(), one_over_root_42, one_over_root_42);
                sd2 = get_soft_decision(d[i].real(), three_over_root_42, one_over_root_42);
                if(sd2 > sd1)
                    sd1 = sd2;
                sd2 = get_soft_decision(d[i].real(), five_over_root_42, one_over_root_42);
                if(sd2 > sd1)
                    sd1 = sd2;
                sd2 = get_soft_decision(d[i].real(), seven_over_root_42, one_over_root_42);
                if(sd2 > sd1)
                    sd1 = sd2;
            }else{
                sd1 = -get_soft_decision(d[i].real(), -one_over_root_42, one_over_root_42);
                sd2 = -get_soft_decision(d[i].real(), -three_over_root_42, one_over_root_42);
                if(sd2 < sd1)
                    sd1 = sd2;
                sd2 = -get_soft_decision(d[i].real(), -five_over_root_42, one_over_root_42);
                if(sd2 < sd1)
                    sd1 = sd2;
                sd2 = -get_soft_decision(d[i].real(), -seven_over_root_42, one_over_root_42);
                if(sd2 < sd1)
                    sd1 = sd2;
            }
            bits[i*6] = (int8)(127*sd1);
            if(d[i].imag() > 0)
            {
                sd1 = get_soft_decision(d[i].imag(), one_over_root_42, one_over_root_42);
                sd2 = get_soft_decision(d[i].imag(), three_over_root_42, one_over_root_42);
                if(sd2 > sd1)
                    sd1 = sd2;
                sd2 = get_soft_decision(d[i].imag(), five_over_root_42, one_over_root_42);
                if(sd2 > sd1)
                    sd1 = sd2;
                sd2 = get_soft_decision(d[i].imag(), seven_over_root_42, one_over_root_42);
                if(sd2 > sd1)
                    sd1 = sd2;
            }else{
                sd1 = -get_soft_decision(d[i].imag(), -one_over_root_42, one_over_root_42);
                sd2 = -get_soft_decision(d[i].imag(), -three_over_root_42, one_over_root_42);
                if(sd2 < sd1)
                    sd1 = sd2;
                sd2 = -get_soft_decision(d[i].imag(), -five_over_root_42, one_over_root_42);
                if(sd2 < sd1)
                    sd1 = sd2;
                sd2 = -get_soft_decision(d[i].imag(), -seven_over_root_42, one_over_root_42);
                if(sd2 < sd1)
                    sd1 = sd2;
            }
            bits[i*6+1] = (int8)(127*sd1);
            float tmp = fabs(d[i].real()) - four_over_root_42;
            if(tmp < 0)
            {
                sd1 = get_soft_decision(tmp, -one_over_root_42, one_over_root_42);
                sd2 = get_soft_decision(tmp, -three_over_root_42, one_over_root_42);
            }else{
                sd1 = -get_soft_decision(tmp, one_over_root_42, one_over_root_42);
                sd2 = -get_soft_decision(tmp, three_over_root_42, one_over_root_42);
            }
            if(fabs(sd1) > fabs(sd2))
            {
                bits[i*6+2] = (int8)(127*sd1);
            }else{
                bits[i*6+2] = (int8)(127*sd2);
            }
            tmp = fabs(d[i].imag()) - four_over_root_42;
            if(tmp < 0)
            {
                sd1 = get_soft_decision(tmp, -one_over_root_42, one_over_root_42);
                sd2 = get_soft_decision(tmp, -three_over_root_42, one_over_root_42);
            }else{
                sd1 = -get_soft_decision(tmp, one_over_root_42, one_over_root_42);
                sd2 = -get_soft_decision(tmp, three_over_root_42, one_over_root_42);
            }
            if(fabs(sd1) > fabs(sd2))
            {
                bits[i*6+3] = (int8)(127*sd1);
            }else{
                bits[i*6+3] = (int8)(127*sd2);
            }
            if(fabs(d[i].real()) < four_over_root_42)
            {
                tmp = fabs(d[i].real()) - two_over_root_42;
                if(tmp > 0)
                {
                    sd1 = get_soft_decision(tmp, one_over_root_42, one_over_root_42);
                }else{
                    sd1 = -get_soft_decision(tmp, -one_over_root_42, one_over_root_42);
                }
            }else{
                tmp = fabs(d[i].real()) - six_over_root_42;
                if(tmp < 0)
                {
                    sd1 = get_soft_decision(tmp, -one_over_root_42, one_over_root_42);
                }else{
                    sd1 = -get_soft_decision(tmp, one_over_root_42, one_over_root_42);
                }
            }
            bits[i*6+4] = (int8)(127*sd1);
            if(fabs(d[i].imag()) < four_over_root_42)
            {
                tmp = fabs(d[i].imag()) - two_over_root_42;
                if(tmp > 0)
                {
                    sd1 = get_soft_decision(tmp, one_over_root_42, one_over_root_42);
                }else{
                    sd1 = -get_soft_decision(tmp, -one_over_root_42, one_over_root_42);
                }
            }else{
                tmp = fabs(d[i].imag()) - six_over_root_42;
                if(tmp < 0)
                {
                    sd1 = get_soft_decision(tmp, -one_over_root_42, one_over_root_42);
                }else{
                    sd1 = -get_soft_decision(tmp, one_over_root_42, one_over_root_42);
                }
            }
            bits[i*6+5] = (int8)(127*sd1);
        }
    }
}

/*********************************************************************
    Name: pcfich_channel_map / pcfich_channel_demap

    Description: Channel maps / demaps the PCFICH

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.7
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void pcfich_channel_map(LIBLTE_PHY_STRUCT          *phy_struct,
                        LIBLTE_PHY_PCFICH_STRUCT   *pcfich,
                        uint32                      N_id_cell,
                        uint8                       N_ant,
                        LIBLTE_PHY_SUBFRAME_STRUCT *subframe)
{
    // Encode, 3GPP TS 36.211 v10.1.0 section 6.7
    uint32 N_bits;
    cfi_channel_encode(phy_struct,
                       pcfich->cfi,
                       phy_struct->pdcch_encode_bits,
                       &N_bits);
    uint32 c_init = (((subframe->num + 1)*(2*N_id_cell + 1)) << 9) + N_id_cell;
    generate_prs_c(c_init, N_bits, phy_struct->pdcch_c);
    for(uint32 i=0; i<N_bits; i++)
        phy_struct->pdcch_scramb_bits[i] = phy_struct->pdcch_encode_bits[i] ^ phy_struct->pdcch_c[i];
    uint32 M_symb;
    modulation_mapper(phy_struct->pdcch_scramb_bits,
                      N_bits,
                      LIBLTE_PHY_MODULATION_TYPE_QPSK,
                      phy_struct->pdcch_d,
                      &M_symb);
    uint32 M_layer_symb;
    layer_mapper_dl(phy_struct->pdcch_d,
                    M_symb,
                    N_ant,
                    1,
                    LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                    phy_struct->pdcch_x,
                    &M_layer_symb);
    uint32 M_ap_symb;
    pre_coder_dl(phy_struct->pdcch_x,
                 M_layer_symb,
                 N_ant,
                 LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                 phy_struct->pdcch_y[0],
                 576,
                 &M_ap_symb);
    // Map the symbols to resource elements, 3GPP TS 36.211 v10.1.0 section 6.7.4
    pcfich->N_reg = 4;
    uint32 k_hat  = (phy_struct->N_sc_rb_dl/2)*(N_id_cell % (2*phy_struct->N_rb_dl));
    for(uint32 i=0; i<pcfich->N_reg; i++)
    {
        pcfich->k[i] = (k_hat + (i*phy_struct->N_rb_dl/2)*phy_struct->N_sc_rb_dl/2) % (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl);
        pcfich->n[i] = (pcfich->k[i]/6) - 0.5;
        for(uint32 p=0; p<N_ant; p++)
        {
            uint32 idx = 0;
            for(uint32 j=0; j<6; j++)
            {
                if((N_id_cell % 3) != (j % 3))
                {
                    subframe->tx_symb[p][0][pcfich->k[i]+j] = phy_struct->pdcch_y[p][idx+(i*4)];
                    idx++;
                }
            }
        }
    }
}
void pcfich_channel_demap(LIBLTE_PHY_STRUCT          *phy_struct,
                          LIBLTE_PHY_SUBFRAME_STRUCT *subframe,
                          uint32                      N_id_cell,
                          uint8                       N_ant,
                          LIBLTE_PHY_PCFICH_STRUCT   *pcfich,
                          uint32                     *N_bits)
{
    // Calculate resources, 3GPP TS 36.211 v10.1.0 section 6.7.4
    pcfich->N_reg = 4;
    uint32 k_hat  = (phy_struct->N_sc_rb_dl/2)*(N_id_cell % (2*phy_struct->N_rb_dl));
    for(uint32 i=0; i<pcfich->N_reg; i++)
    {
        pcfich->k[i] = (k_hat + (i*phy_struct->N_rb_dl/2)*phy_struct->N_sc_rb_dl/2) % (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl);
        pcfich->n[i] = (pcfich->k[i]/6) - 0.5;

        // Extract resource elements and channel estimate
        uint32 idx = 0;
        for(uint32 j=0; j<6; j++)
        {
            if((N_id_cell % 3) != (j % 3))
            {
                phy_struct->pdcch_y_est[idx+(i*4)] = subframe->rx_symb[0][pcfich->k[i]+j];
                for(uint32 p=0; p<N_ant; p++)
                    phy_struct->pdcch_c_est[p][idx+(i*4)] = subframe->rx_ce[p][0][pcfich->k[i]+j];
                idx++;
            }
        }
    }
    // Decode, 3GPP TS 36.211 v10.1.0 section 6.7
    uint32 c_init = (((subframe->num + 1)*(2*N_id_cell + 1)) << 9) + N_id_cell;
    generate_prs_c(c_init, 32, phy_struct->pdcch_c);
    uint32 M_layer_symb;
    de_pre_coder_dl(phy_struct->pdcch_y_est,
                    phy_struct->pdcch_c_est[0],
                    576,
                    16,
                    N_ant,
                    LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                    phy_struct->pdcch_x,
                    &M_layer_symb);
    uint32 M_symb;
    layer_demapper_dl(phy_struct->pdcch_x,
                      M_layer_symb,
                      N_ant,
                      1,
                      LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                      phy_struct->pdcch_d,
                      &M_symb);
    modulation_demapper(phy_struct->pdcch_d,
                        M_symb,
                        LIBLTE_PHY_MODULATION_TYPE_QPSK,
                        phy_struct->pdcch_soft_bits,
                        N_bits);
    for(uint32 i=0; i<*N_bits; i++)
        phy_struct->pdcch_descramb_bits[i] = (float)phy_struct->pdcch_soft_bits[i]*(1-2*(float)phy_struct->pdcch_c[i]);
}

/*********************************************************************
    Name: pdcch_permute_pre_calc

    Description: Pre calculates the PDCCH REG permutation.

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.8.5
*********************************************************************/
// Defines
#define RX_NULL_BIT 10000
// Enums
// Structs
// Functions
void pdcch_permute_pre_calc(LIBLTE_PHY_STRUCT *phy_struct,
                            uint32             N_ant,
                            float              phich_res)
{
    uint32 N_reg_phich = phy_struct->N_group_phich*3;
    for(uint32 N_symbs=1; N_symbs<=3; N_symbs++)
    {
        uint32 N_reg_rb     = 3;
        uint32 N_reg_pcfich = 4;
        uint32 N_reg_pdcch  = N_symbs*(phy_struct->N_rb_dl*N_reg_rb) - phy_struct->N_rb_dl - N_reg_pcfich - N_reg_phich;
        for(uint32 i=0; i<N_reg_pdcch; i++)
            phy_struct->pdcch_reg_vec[i] = i;
        // Sub block interleaving
        // Step 1
        uint32 C_cc_sb = 32;
        // Step 2
        uint32 R_cc_sb = 0;
        while(N_reg_pdcch > (C_cc_sb*R_cc_sb))
            R_cc_sb++;
        // Step 3
        uint32 N_dummy = 0;
        if(N_reg_pdcch < (C_cc_sb*R_cc_sb))
            N_dummy = C_cc_sb*R_cc_sb - N_reg_pdcch;
        for(uint32 i=0; i<N_dummy; i++)
            phy_struct->ruc_tmp[i] = RX_NULL_BIT;
        uint32 idx = 0;
        for(uint32 i=N_dummy; i<C_cc_sb*R_cc_sb; i++)
            phy_struct->ruc_tmp[i] = phy_struct->pdcch_reg_vec[idx++];
        idx = 0;
        for(uint32 i=0; i<R_cc_sb; i++)
            for(uint32 j=0; j<C_cc_sb; j++)
                phy_struct->ruc_sb_mat[i][j] = phy_struct->ruc_tmp[idx++];
        // Step 4
        for(uint32 i=0; i<R_cc_sb; i++)
            for(uint32 j=0; j<C_cc_sb; j++)
                phy_struct->ruc_sb_perm_mat[i][j] = phy_struct->ruc_sb_mat[i][IC_PERM_CC[j]];
        // Step 5
        idx = 0;
        for(uint32 j=0; j<C_cc_sb; j++)
            for(uint32 i=0; i<R_cc_sb; i++)
                phy_struct->ruc_w[idx++] = phy_struct->ruc_sb_perm_mat[i][j];
        uint32 K_pi = R_cc_sb*C_cc_sb;
        uint32 k    = 0;
        uint32 j    = 0;
        while(k < N_reg_pdcch)
        {
            if(phy_struct->ruc_w[j%K_pi] != RX_NULL_BIT)
                phy_struct->pdcch_reg_perm_vec[k++] = phy_struct->ruc_w[j%K_pi];
            j++;
        }
        for(uint32 p=0; p<N_ant; p++)
            for(uint32 i=0; i<N_reg_pdcch; i++)
                phy_struct->pdcch_permute_map[N_reg_pdcch][i] = phy_struct->pdcch_reg_perm_vec[i];
    }
}

/*********************************************************************
    Name: phich_channel_map / phich_channel_demap

    Description: Channel maps / demaps the PHICH

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.9
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void phich_channel_map(LIBLTE_PHY_STRUCT                 *phy_struct,
                       LIBLTE_PHY_PHICH_STRUCT           *phich,
                       LIBLTE_PHY_PCFICH_STRUCT          *pcfich,
                       uint32                             N_id_cell,
                       uint8                              N_ant,
                       float                              phich_res,
                       PHICH_Config::phich_Duration_Enum  phich_dur,
                       LIBLTE_PHY_SUBFRAME_STRUCT        *subframe)
{
    // Determine the number of REGs
    phich->N_reg = phy_struct->N_group_phich*3;

    uint32 c_init = (((subframe->num + 1)*(2*N_id_cell + 1)) << 9) + N_id_cell;
    generate_prs_c(c_init, 12, phy_struct->pdcch_c);
    uint32 idx         = 0;
    uint8  ack_seq[3]  = {1, 1, 1};
    uint8  nack_seq[3] = {0, 0, 0};
    for(uint32 m_prime=0; m_prime<phy_struct->N_group_phich; m_prime++)
    {
        for(uint32 i=0; i<12; i++)
            phy_struct->pdcch_d[i] = complex(0, 0);
        for(uint32 seq=0; seq<8; seq++) // FIXME: Only handling normal CP
        {
            if(phich->present[m_prime][seq])
            {
                uint8 *bit_seq = nack_seq;
                if(phich->b[m_prime][seq])
                    bit_seq = ack_seq;
                uint32 M_symb;
                modulation_mapper(bit_seq,
                                  3,
                                  LIBLTE_PHY_MODULATION_TYPE_BPSK,
                                  phich->z,
                                  &M_symb);
                for(uint32 i=0; i<(3 * phy_struct->N_sf_phich); i++)
                {
                    uint32 w_idx = i % phy_struct->N_sf_phich;
                    uint32 z_idx = i / phy_struct->N_sf_phich;
                    if(phy_struct->pdcch_c[i] == 1)
                    {
                        phy_struct->pdcch_d[i] +=
                            PHICH_w_normal_cp_6_9_1_2[seq][w_idx] * -phich->z[z_idx];
                    }else{
                        phy_struct->pdcch_d[i] +=
                            PHICH_w_normal_cp_6_9_1_2[seq][w_idx] * phich->z[z_idx];
                    }
                }
            }
        }
        uint32 M_layer_symb;
        layer_mapper_dl(phy_struct->pdcch_d,
                        3 * phy_struct->N_sf_phich,
                        N_ant,
                        1,
                        LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                        phy_struct->pdcch_x,
                        &M_layer_symb);
        // FIXME: Pre coder for 4 antennas is not correct
        uint32 M_ap_symb;
        pre_coder_dl(phy_struct->pdcch_x,
                     M_layer_symb,
                     N_ant,
                     LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                     phy_struct->pdcch_y[0],
                     576,
                     &M_ap_symb);

        // Map the group
        if(PHICH_Config::k_phich_Duration_normal == phich_dur)
        {
            // Step 7 : l_prime = 0
            // Step 1, 2, and 3
            uint32 n_l_prime = phy_struct->N_rb_dl*2 - pcfich->N_reg;
            // Step 8
            uint32 n_hat[3];
            for(uint32 i=0; i<3; i++)
                n_hat[i] = (N_id_cell + m_prime + i*n_l_prime/3) % n_l_prime;
            // Avoid PCFICH
            for(uint32 i=0; i<pcfich->N_reg; i++)
                for(uint32 j=0; j<3; j++)
                    if(n_hat[j] > pcfich->n[i])
                        n_hat[j]++;
            // Step 5
            uint32 y_idx = 0;
            for(uint32 i=0; i<3; i++)
            {
                phich->k[idx+i] = n_hat[i]*6;
                for(uint32 p=0; p<N_ant; p++)
                    for(uint32 j=0; j<6; j++)
                        if((N_id_cell % 3) != (j % 3))
                            subframe->tx_symb[p][0][phich->k[idx+i]+j] = phy_struct->pdcch_y[p][y_idx++];
            }
        }else{
            // FIXME: Not handling extended PHICH duration
        }
        idx += 3;
    }
}
void phich_channel_demap(LIBLTE_PHY_STRUCT                 *phy_struct,
                         LIBLTE_PHY_PCFICH_STRUCT          *pcfich,
                         LIBLTE_PHY_SUBFRAME_STRUCT        *subframe,
                         uint32                             N_id_cell,
                         uint8                              N_ant,
                         float                              phich_res,
                         PHICH_Config::phich_Duration_Enum  phich_dur,
                         LIBLTE_PHY_PHICH_STRUCT           *phich)
{
    // Calculate resources, 3GPP TS 36.211 v10.1.0 section 6.9
    phy_struct->N_group_phich = 2*(uint32)ceilf((float)phich_res*((float)phy_struct->N_rb_dl/(float)8));
    if(LIBLTE_PHY_N_SC_RB_DL_NORMAL_CP == phy_struct->N_sc_rb_dl)
        phy_struct->N_group_phich = (uint32)ceilf((float)phich_res*((float)phy_struct->N_rb_dl/(float)8));
    phich->N_reg = phy_struct->N_group_phich*3;
    // Step 4
    uint32 m_prime = 0;
    uint32 idx     = 0;
    // Step 10
    while(m_prime < phy_struct->N_group_phich)
    {
        if(PHICH_Config::k_phich_Duration_normal == phich_dur)
        {
            // Step 7 : l_prime = 0
            // Step 1, 2, and 3
            uint32 n_l_prime = phy_struct->N_rb_dl*2 - pcfich->N_reg;
            // Step 8
            uint32 n_hat[3];
            for(uint32 i=0; i<3; i++)
                n_hat[i] = (N_id_cell + m_prime + i*n_l_prime/3) % n_l_prime;
            // Avoid PCFICH
            for(uint32 i=0; i<pcfich->N_reg; i++)
                for(uint32 j=0; j<3; j++)
                    if(n_hat[j] > pcfich->n[i])
                        n_hat[j]++;
            // Step 5
            for(uint32 i=0; i<3; i++)
            {
                phich->k[idx+i] = n_hat[i]*6;
                // FIXME: Not currently implementing step 6
            }
            idx += 3;
        }else{
            // FIXME: Not handling extended PHICH duration
            printf("ERROR: Not handling extended PHICH duration\n");
        }
        // Step 9
        m_prime++;
    }
}

/*********************************************************************
    Name: generate_crs

    Description: Generates LTE cell specific reference signals

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.10.1.1
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void generate_crs(uint32   N_s,
                  uint32   L,
                  uint32   N_id_cell,
                  uint32   N_sc_rb_dl,
                  complex *crs)
{
    uint32 N_cp = 0;
    if(LIBLTE_PHY_N_SC_RB_DL_NORMAL_CP == N_sc_rb_dl)
        N_cp = 1;

    // Calculate c_init
    uint32 c_init = 1024 * (7 * (N_s+1) + L + 1) * (2 * N_id_cell + 1) + 2*N_id_cell + N_cp;

    // Generate the psuedo random sequence c
    uint32 len = 2*LIBLTE_PHY_N_RB_DL_MAX;
    uint32 c[2*len];
    generate_prs_c(c_init, 2*len, c);

    // Construct the reference signals
    float one_over_sqrt_2 = 1/sqrt(2);
    for(uint32 i=0; i<len; i++)
        crs[i] = one_over_sqrt_2 * complex(1 - 2*(float)c[2*i],
                                           1 - 2*(float)c[2*i+1]);
}

/*********************************************************************
    Name: generate_pss

    Description: Generates an LTE primary synchronization signal

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.11.1.1
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void generate_pss(uint32   N_id_2,
                  complex *pss)
{
    float root_idx;
    if(N_id_2 == 0)
    {
        root_idx = 25;
    }else if(N_id_2 == 1){
        root_idx = 29;
    }else{
        root_idx = 34;
    }

    for(uint32 i=0; i<31; i++)
        pss[i] = complex_polar(1, -M_PI*root_idx*i*(i+1)/63);
    for(uint32 i=31; i<62; i++)
        pss[i] = complex_polar(1, -M_PI*root_idx*(i+1)*(i+2)/63);
}

/*********************************************************************
    Name: generate_sss

    Description: Generates LTE secondary synchronization signals

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.11.2.1
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void generate_sss(LIBLTE_PHY_STRUCT *phy_struct,
                  uint32             N_id_1,
                  uint32             N_id_2,
                  complex           *sss_0,
                  complex           *sss_5)
{
    // Generate m0 and m1
    uint32 q_prime = N_id_1/30;
    uint32 q       = (N_id_1 + (q_prime*(q_prime+1)/2))/30;
    uint32 m_prime = N_id_1 + (q*(q+1)/2);
    uint32 m0      = m_prime % 31;
    uint32 m1      = (m0 + (m_prime/31) + 1) % 31;

    // Generate s_tilda
    memset(phy_struct->sss_x_s_tilda, 0, sizeof(uint8)*31);
    phy_struct->sss_x_s_tilda[4] = 1;
    for(uint32 i=0; i<26; i++)
        phy_struct->sss_x_s_tilda[i+5] = (phy_struct->sss_x_s_tilda[i+2] +
                                          phy_struct->sss_x_s_tilda[i]) % 2;
    for(uint32 i=0; i<31; i++)
        phy_struct->sss_s_tilda[i] = 1 - 2*phy_struct->sss_x_s_tilda[i];

    // Generate c_tilda
    memset(phy_struct->sss_x_c_tilda, 0, sizeof(uint8)*31);
    phy_struct->sss_x_c_tilda[4] = 1;
    for(uint32 i=0; i<26; i++)
        phy_struct->sss_x_c_tilda[i+5] = (phy_struct->sss_x_c_tilda[i+3] +
                                          phy_struct->sss_x_c_tilda[i]) % 2;
    for(uint32 i=0; i<31; i++)
        phy_struct->sss_c_tilda[i] = 1 - 2*phy_struct->sss_x_c_tilda[i];

    // Generate z_tilda
    memset(phy_struct->sss_x_z_tilda, 0, sizeof(uint8)*31);
    phy_struct->sss_x_z_tilda[4] = 1;
    for(uint32 i=0; i<26; i++)
        phy_struct->sss_x_z_tilda[i+5] = (phy_struct->sss_x_z_tilda[i+4] +
                                          phy_struct->sss_x_z_tilda[i+2] +
                                          phy_struct->sss_x_z_tilda[i+1] +
                                          phy_struct->sss_x_z_tilda[i]) % 2;
    for(uint32 i=0; i<31; i++)
        phy_struct->sss_z_tilda[i] = 1 - 2*phy_struct->sss_x_z_tilda[i];

    // Generate s0_m0 and s1_m1
    for(uint32 i=0; i<31; i++)
    {
        phy_struct->sss_s0_m0[i] = phy_struct->sss_s_tilda[(i + m0) % 31];
        phy_struct->sss_s1_m1[i] = phy_struct->sss_s_tilda[(i + m1) % 31];
    }

    // Generate c0 and c1
    for(uint32 i=0; i<31; i++)
    {
        phy_struct->sss_c0[i] = phy_struct->sss_c_tilda[(i + N_id_2) % 31];
        phy_struct->sss_c1[i] = phy_struct->sss_c_tilda[(i + N_id_2 + 3) % 31];
    }

    // Generate z1_m0 and z1_m1
    for(uint32 i=0; i<31; i++)
    {
        phy_struct->sss_z1_m0[i] = phy_struct->sss_z_tilda[(i + (m0 % 8)) % 31];
        phy_struct->sss_z1_m1[i] = phy_struct->sss_z_tilda[(i + (m1 % 8)) % 31];
    }

    // Generate SSS
    for(uint32 i=0; i<31; i++)
    {
        sss_0[2*i]   = complex(phy_struct->sss_s0_m0[i]*phy_struct->sss_c0[i], 0);
        sss_0[2*i+1] = complex(phy_struct->sss_s1_m1[i]*phy_struct->sss_c1[i]*phy_struct->sss_z1_m0[i], 0);

        sss_5[2*i]   = complex(phy_struct->sss_s1_m1[i]*phy_struct->sss_c0[i], 0);
        sss_5[2*i+1] = complex(phy_struct->sss_s0_m0[i]*phy_struct->sss_c1[i]*phy_struct->sss_z1_m1[i], 0);
    }
}

/*********************************************************************
    Name: symbols_to_samples_dl / samples_to_symbols_dl

    Description: Converts subcarrier symbols to I/Q samples for the
                 downlink / Converts I/Q samples to subcarrier symbols
                 for the downlink

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.12
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void symbols_to_samples_dl(LIBLTE_PHY_STRUCT *phy_struct,
                           complex           *symb,
                           uint32             symbol_offset,
                           complex           *samps,
                           uint32            *N_samps)
{
    // Calculate index and CP length
    uint32 CP_len = phy_struct->N_samps_cp_l_else;
    if((symbol_offset % 7) == 0)
        CP_len = phy_struct->N_samps_cp_l_0;

    for(uint32 i=0; i<phy_struct->N_samps_per_symb; i++)
    {
        phy_struct->s2s_in[i][0] = 0;
        phy_struct->s2s_in[i][1] = 0;
    }
    for(uint32 i=0; i<(phy_struct->FFT_size/2)-phy_struct->FFT_pad_size; i++)
    {
        // Positive spectrum
        phy_struct->s2s_in[i+1][0] = symb[i+((phy_struct->FFT_size/2)-phy_struct->FFT_pad_size)].real();
        phy_struct->s2s_in[i+1][1] = symb[i+((phy_struct->FFT_size/2)-phy_struct->FFT_pad_size)].imag();

        // Negative spectrum
        phy_struct->s2s_in[phy_struct->N_samps_per_symb-i-1][0] = symb[((phy_struct->FFT_size/2)-phy_struct->FFT_pad_size)-i-1].real();
        phy_struct->s2s_in[phy_struct->N_samps_per_symb-i-1][1] = symb[((phy_struct->FFT_size/2)-phy_struct->FFT_pad_size)-i-1].imag();
    }
    fftwf_execute(phy_struct->symbs_to_samps_dl_plan);
    for(uint32 i=0; i<phy_struct->N_samps_per_symb; i++)
        samps[CP_len+i] = complex(phy_struct->s2s_out[i][0], phy_struct->s2s_out[i][1]);
    for(uint32 i=0; i<CP_len; i++)
        samps[i] = samps[phy_struct->N_samps_per_symb+i];
    *N_samps = phy_struct->N_samps_per_symb + CP_len;
}
void samples_to_symbols_dl(LIBLTE_PHY_STRUCT *phy_struct,
                           complex           *samps,
                           uint32             slot_start_idx,
                           uint32             symbol_offset,
                           uint8              scale,
                           complex           *symb)
{
    // Calculate index and CP length
    uint32 CP_len = phy_struct->N_samps_cp_l_else;
    if((symbol_offset % 7) == 0)
        CP_len = phy_struct->N_samps_cp_l_0;
    uint32 index = slot_start_idx + (phy_struct->N_samps_per_symb+phy_struct->N_samps_cp_l_else)*symbol_offset;
    if(symbol_offset > 0)
        index += phy_struct->N_samps_cp_l_0 - phy_struct->N_samps_cp_l_else;

    for(uint32 i=0; i<phy_struct->N_samps_per_symb; i++)
    {
        phy_struct->s2s_in[i][0] = samps[index+CP_len-1+i].real();
        phy_struct->s2s_in[i][1] = samps[index+CP_len-1+i].imag();
    }
    fftwf_execute(phy_struct->samps_to_symbs_dl_plan);
    for(uint32 i=0; i<(phy_struct->FFT_size/2)-phy_struct->FFT_pad_size; i++)
    {
        // Positive spectrum
        symb[i+((phy_struct->FFT_size/2)-phy_struct->FFT_pad_size)] =
            complex(phy_struct->s2s_out[i+1][0], phy_struct->s2s_out[i+1][1]);

        // Negative spectrum
        symb[((phy_struct->FFT_size/2)-phy_struct->FFT_pad_size)-i-1] =
            complex(phy_struct->s2s_out[phy_struct->N_samps_per_symb-i-1][0], phy_struct->s2s_out[phy_struct->N_samps_per_symb-i-1][1]);
    }

    if(scale == 1)
        for(uint32 i=0; i<2*((phy_struct->FFT_size/2)-phy_struct->FFT_pad_size); i++)
            symb[i] = complex_polar(1, std::arg(symb[i]));
}

/*********************************************************************
    Name: symbols_to_samples_ul / samples_to_symbols_ul

    Description: Converts subcarrier symbols to I/Q samples for the
                 uplink / Converts I/Q samples to subcarrier symbols
                 for the uplink

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.6
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void symbols_to_samples_ul(LIBLTE_PHY_STRUCT *phy_struct,
                           complex           *symb,
                           uint32             symbol_offset,
                           complex           *samps,
                           uint32            *N_samps)
{
    // Calculate index and CP length
    uint32 CP_len = phy_struct->N_samps_cp_l_else;
    if((symbol_offset % 7) == 0)
        CP_len = phy_struct->N_samps_cp_l_0;

    for(uint32 i=0; i<phy_struct->N_samps_per_symb; i++)
    {
        phy_struct->s2s_in[i][0] = 0;
        phy_struct->s2s_in[i][1] = 0;
    }
    for(uint32 i=0; i<phy_struct->FFT_size-(phy_struct->FFT_pad_size/2); i++)
    {
        uint32 idx                 = ((i*phy_struct->FFT_pad_size+phy_struct->FFT_size/2)*2+1)%(phy_struct->FFT_size*2);
        phy_struct->s2s_in[idx][0] = symb[i].real();
        phy_struct->s2s_in[idx][1] = symb[i].imag();
    }
    fftwf_execute(phy_struct->symbs_to_samps_ul_plan);
    for(uint32 i=0; i<phy_struct->N_samps_per_symb; i++)
        samps[CP_len+i] = complex(phy_struct->s2s_out[i][0], phy_struct->s2s_out[i][1]);
    for(uint32 i=0; i<CP_len; i++)
        samps[i] = samps[phy_struct->N_samps_per_symb+i];
    *N_samps = phy_struct->N_samps_per_symb + CP_len;
}
void samples_to_symbols_ul(LIBLTE_PHY_STRUCT *phy_struct,
                           complex           *samps,
                           uint32             slot_start_idx,
                           uint32             symbol_offset,
                           complex           *symb)
{
    // Calculate index and CP length
    uint32 CP_len = phy_struct->N_samps_cp_l_else;
    if((symbol_offset % 7) == 0)
        CP_len = phy_struct->N_samps_cp_l_0;
    uint32 index = slot_start_idx + (phy_struct->N_samps_per_symb+phy_struct->N_samps_cp_l_else)*symbol_offset;
    if(symbol_offset > 0)
        index += phy_struct->N_samps_cp_l_0 - phy_struct->N_samps_cp_l_else;

    for(uint32 i=0; i<phy_struct->N_samps_per_symb; i++)
    {
        phy_struct->s2s_in[i][0] = samps[index+CP_len-1+i].real();
        phy_struct->s2s_in[i][1] = samps[index+CP_len-1+i].imag();
    }
    fftwf_execute(phy_struct->samps_to_symbs_ul_plan);
    for(uint32 i=0; i<phy_struct->FFT_size-(phy_struct->FFT_pad_size*2); i++)
    {
        uint32 idx = ((i+phy_struct->FFT_pad_size+phy_struct->FFT_size/2)*2+1)%(phy_struct->FFT_size*2);
        symb[i]    = complex(phy_struct->s2s_out[idx][0], phy_struct->s2s_out[idx][1]);
    }
}

/*********************************************************************
    Name: calc_crc / check_crc

    Description: Calculates one of the LTE CRCs / Returns the number
                 of bit errors in a CRC

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.1
*********************************************************************/
// Defines
#define CRC24A 0x01864CFB
#define CRC24B 0x01800063
#define CRC16  0x00011021
#define CRC8   0x0000019B
// Enums
// Structs
// Functions
void calc_crc(uint8  *a_bits,
              uint32  N_a_bits,
              uint32  crc,
              uint8  *p_bits,
              uint32  N_p_bits)
{
    // Initialize tmp_array
    uint8 tmp_array[N_a_bits + N_p_bits];
    memset(tmp_array, 0, N_a_bits + N_p_bits);
    memcpy(tmp_array, a_bits, N_a_bits);

    uint32 crc_rem   = 0;
    uint32 crc_check = (1 << N_p_bits);
    for(uint32 i=0; i<N_a_bits + N_p_bits; i++)
    {
        crc_rem <<= 1;
        crc_rem  |= tmp_array[i];

        if(crc_rem & crc_check)
            crc_rem ^= crc;
    }

    for(uint32 i=0; i<N_p_bits; i++)
        p_bits[i] = (crc_rem >> (N_p_bits-1-i)) & 1;
}
uint32 check_crc(uint8  *ref,
                 uint8  *crc,
                 uint32  N_bits)
{
    uint32 ber = 0;
    for(uint32 i=0; i<N_bits; i++)
        ber += ref[i] ^ crc[i];
    return ber;
}

/*********************************************************************
    Name: conv_encode

    Description: Convolutionally encodes a bit array using the
                 provided parameters

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.3.1
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void conv_encode(LIBLTE_PHY_STRUCT *phy_struct,
                 uint8             *c_bits,
                 uint32             N_c_bits,
                 uint32             constraint_len,
                 uint32             rate,
                 uint32            *g,
                 bool               tail_bit,
                 uint8             *d_bits,
                 uint32            *N_d_bits)
{
    // Initialize the shift register
    uint8 s_reg[constraint_len];
    if(tail_bit)
    {
        for(uint32 i=0; i<constraint_len; i++)
            s_reg[i] = c_bits[N_c_bits-i-1];
    }else{
        for(uint32 i=0; i<constraint_len; i++)
            s_reg[i] = 0;
    }

    // Convert g from octal to binary array
    uint8 g_array[3][constraint_len];
    for(uint32 i=0; i<rate; i++)
        for(uint32 j=0; j<constraint_len; j++)
            g_array[i][j] = (g[i] >> (constraint_len-j-1)) & 1;

    // Convolutionally encode input
    for(uint32 i=0; i<N_c_bits; i++)
    {
        // Add next bit to shift register
        for(int32 j=constraint_len-1; j>0; j--)
            s_reg[j] = s_reg[j-1];
        s_reg[0] = c_bits[i];

        // Determine the output bits
        for(uint32 j=0; j<rate; j++)
        {
            d_bits[i*rate + j] = 0;

            for(uint32 k=0; k<constraint_len; k++)
                d_bits[i*rate + j] += s_reg[k]*g_array[j][k];
            d_bits[i*rate + j] %= 2;
        }
    }

    *N_d_bits = N_c_bits*rate;
}

/*********************************************************************
    Name: viterbi_decode

    Description: Viterbi decodes a convolutionally coded input bit
                 array using the provided parameters

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.3.1
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void viterbi_decode(LIBLTE_PHY_STRUCT *phy_struct,
                    float             *d_bits,
                    uint32             N_d_bits,
                    uint32             constraint_len,
                    uint32             rate,
                    uint32            *g,
                    uint8             *c_bits,
                    uint32            *N_c_bits)
{
    // Convert g to binary
    uint8 g_array[3][constraint_len];
    for(uint32 i=0; i<rate; i++)
        for(uint32 j=0; j<constraint_len; j++)
            g_array[i][j] = (g[i] >> (constraint_len-j-1)) & 1;

    // Precalculate state transition outputs
    uint32 N_states = 1<<(constraint_len-1);
    for(uint32 i=0; i<N_states; i++)
    {
        // Determine the input path
        uint8 in_path = 1;
        if(i < (N_states/2))
            in_path = 0;

        // Determine the outputs based on the previous state and input path
        uint8 s_reg[constraint_len];
        for(uint32 j=0; j<2; j++)
        {
            uint8 prev_state = ((i << 1) + j) % N_states;
            for(uint32 k=0; k<constraint_len; k++)
                s_reg[k] = (prev_state >> (constraint_len-k-1)) & 1;
            s_reg[0] = in_path;
            for(uint32 k=0; k<rate; k++)
            {
                phy_struct->vd_st_output[i][j][k] = 0;
                for(uint32 o=0; o<constraint_len; o++)
                    phy_struct->vd_st_output[i][j][k] += s_reg[o]*g_array[k][o];
                phy_struct->vd_st_output[i][j][k] %= 2;
            }
        }
    }

    // Calculate branch and path metrics
    for(uint32 i=0; i<N_states; i++)
        for(uint32 j=0; j<(N_d_bits/rate)+10; j++)
            phy_struct->vd_path_metric[i][j] = 0;
    for(uint32 i=0; i<(N_d_bits/rate); i++)
    {
        for(uint32 j=0; j<N_states; j++)
        {
            phy_struct->vd_br_metric[j][0] = 0;
            phy_struct->vd_br_metric[j][1] = 0;
            phy_struct->vd_p_metric[j][0]  = 0;
            phy_struct->vd_p_metric[j][1]  = 0;
            phy_struct->vd_w_metric[j][0]  = 0;
            phy_struct->vd_w_metric[j][1]  = 0;

            // Calculate the accumulated branch metrics for each state
            for(uint32 k=0; k<2; k++)
            {
                uint8 prev_state              = ((j<<1)+k) % N_states;
                phy_struct->vd_p_metric[j][k] = phy_struct->vd_path_metric[prev_state][i];
                for(uint32 o=0; o<rate; o++)
                {
                    uint8 in_bit = 1;
                    if(d_bits[i*rate + o] >= 0)
                        in_bit = 0;
                    phy_struct->vd_br_metric[j][k] += (phy_struct->vd_st_output[j][k][o]+in_bit)%2;
                    phy_struct->vd_w_metric[j][k]  += fabs(d_bits[i*rate + o]);
                }
            }

            // Keep the smallest branch metric as the path metric, weight the branch metric
            float tmp1 = phy_struct->vd_br_metric[j][0] + phy_struct->vd_p_metric[j][0];
            float tmp2 = phy_struct->vd_br_metric[j][1] + phy_struct->vd_p_metric[j][1];
            if(tmp1 > tmp2)
            {
                phy_struct->vd_path_metric[j][i+1] = phy_struct->vd_p_metric[j][1] + phy_struct->vd_w_metric[j][1]*phy_struct->vd_br_metric[j][1];
            }else{
                phy_struct->vd_path_metric[j][i+1] = phy_struct->vd_p_metric[j][0] + phy_struct->vd_w_metric[j][0]*phy_struct->vd_br_metric[j][0];
            }
        }
    }

    // Find the minimum metric for the last iteration
    float  init_min              = 1000000;
    uint32 idx                   = 0;
    phy_struct->vd_tb_state[idx] = 1000000;
    for(uint32 i=0; i<N_states; i++)
    {
        if(phy_struct->vd_path_metric[i][(N_d_bits/rate)] < init_min)
        {
            init_min                     = phy_struct->vd_path_metric[i][(N_d_bits/rate)];
            phy_struct->vd_tb_state[idx] = i;
        }
    }
    idx++;

    // Traceback to find the minimum path metrics at each iteration
    for(int32 i=(N_d_bits/rate)-1; i>=0; i--)
    {
        uint8 prev_state_0 = ((((uint8)phy_struct->vd_tb_state[idx-1])<<1) + 0) % N_states;
        uint8 prev_state_1 = ((((uint8)phy_struct->vd_tb_state[idx-1])<<1) + 1) % N_states;

        // Keep the smallest state
        if(phy_struct->vd_path_metric[prev_state_0][i] > phy_struct->vd_path_metric[prev_state_1][i])
        {
            phy_struct->vd_tb_state[idx++] = prev_state_1;
        }else{
            phy_struct->vd_tb_state[idx++] = prev_state_0;
        }
    }
    uint32 tb_state_len = idx;

    // Read through the traceback to determine the input bits
    idx = 0;
    for(int32 i=tb_state_len-2; i>=0; i--)
    {
        // If transition has resulted in a lower valued state,
        // the output is 0 and vice-versa
        if(phy_struct->vd_tb_state[i] < phy_struct->vd_tb_state[i+1])
        {
            c_bits[idx++] = 0;
        }else if(phy_struct->vd_tb_state[i] > phy_struct->vd_tb_state[i+1]){
            c_bits[idx++] = 1;
        }else{
            // Check to see if the transition has resulted in the same state
            // In this case, if state is 0 then output is 0
            if(phy_struct->vd_tb_state[i] == 0)
            {
                c_bits[idx++] = 0;
            }else{
                c_bits[idx++] = 1;
            }
        }
    }
    *N_c_bits = idx;
}

/*********************************************************************
    Name: viterbi_rsc_decode_siso

    Description: Soft input soft output viterbi decodes a
                 recursive, systematic, convolutionally coded input
                 bit array using the provided parameters

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.3.1
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void viterbi_rsc_decode_siso(LIBLTE_PHY_STRUCT *phy_struct,
                             int8              *d_bits,
                             uint32             N_d_bits,
                             uint32             constraint_len,
                             uint32             rate,
                             uint32            *g,
                             int8              *c_bits,
                             uint32            *N_c_bits)
{
    // Convert g to binary
    uint8 g_array[3][constraint_len];
    for(uint32 i=0; i<rate; i++)
        for(uint32 j=0; j<constraint_len; j++)
            g_array[i][j] = (g[i] >> (constraint_len-j-1)) & 1;

    // Precalculate state transition outputs
    uint32 N_states = 1<<(constraint_len-1);
    for(uint32 i=0; i<N_states; i++)
    {
        // Determine the input path
        uint8 in_path = 1;
        if(i < (N_states/2))
            in_path = 0;

        // Determine the outputs based on the previous state and input path
        uint8 s_reg[constraint_len];
        for(uint32 j=0; j<2; j++)
        {
            uint8 prev_state = ((i*2) + (j + (i%2) + (i/4))%2) % N_states;
            for(uint32 k=0; k<constraint_len; k++)
                s_reg[k] = (prev_state >> (constraint_len-k-1)) & 1;
            s_reg[0] = in_path;
            for(uint32 k=0; k<rate; k++)
            {
                phy_struct->vd_st_output[i][j][k] = 0;
                for(uint32 o=0; o<constraint_len; o++)
                    phy_struct->vd_st_output[i][j][k] += s_reg[o]*g_array[k][o];
                phy_struct->vd_st_output[i][j][k] %= 2;
            }
        }
    }

    // Calculate branch and path metrics
    for(uint32 i=0; i<N_states; i++)
    {
        for(uint32 j=0; j<(N_d_bits/rate)+10; j++)
        {
            phy_struct->vd_path_metric[i][j] = 0;
            phy_struct->vd_w_metric[i][j]    = 0;
        }
    }
    phy_struct->vd_path_metric[0][0] = -1;
    for(uint32 i=0; i<(N_d_bits/rate); i++)
    {
        for(uint32 j=0; j<N_states; j++)
        {
            // Calculate the accumulated branch metrics for each state
            for(uint32 k=0; k<2; k++)
            {
                phy_struct->vd_br_metric[j][k] = 0;
                phy_struct->vd_p_metric[j][k]  = 0;
                phy_struct->vd_br_weight[j][k] = 0;

                uint8 prev_state              = ((j*2) + (k + (j%2) + (j/4))%2) % N_states;
                phy_struct->vd_p_metric[j][k] = phy_struct->vd_path_metric[prev_state][i];

                for(uint32 o=0; o<rate; o++)
                {
                    uint8 in_bit = 1;
                    if(d_bits[i*rate + o] >= 0)
                        in_bit = 0;
                    if(phy_struct->vd_st_output[j][k][o] == in_bit)
                    {
                        phy_struct->vd_br_metric[j][k] += -1;
                    }else{
                        phy_struct->vd_br_metric[j][k] += 1;
                    }
                    phy_struct->vd_br_weight[j][k] += fabs(d_bits[i*rate + o]);
                }
            }

            // Keep the smallest branch metric as the path metric, weight the branch metric
            uint8 idx = 0;
            if((phy_struct->vd_br_metric[j][0] + phy_struct->vd_p_metric[j][0]) >
               (phy_struct->vd_br_metric[j][1] + phy_struct->vd_p_metric[j][1]))
                idx = 1;
            phy_struct->vd_path_metric[j][i+1] = phy_struct->vd_p_metric[j][idx] + phy_struct->vd_br_weight[j][idx]*phy_struct->vd_br_metric[j][idx];
            phy_struct->vd_w_metric[j][i+1]    = phy_struct->vd_br_weight[j][idx];
        }
    }

    // Find the minimum metric for the last iteration
    float init_min             = 1000000;
    phy_struct->vd_tb_state[0] = 1000000;
    float max_weight           = 0;
    for(uint32 i=0; i<N_states; i++)
    {
        if(phy_struct->vd_path_metric[i][(N_d_bits/rate)] < init_min)
        {
            init_min                    = phy_struct->vd_path_metric[i][(N_d_bits/rate)];
            phy_struct->vd_tb_state[0]  = i;
            phy_struct->vd_tb_weight[0] = phy_struct->vd_w_metric[i][(N_d_bits/rate)];
            max_weight                  = phy_struct->vd_tb_weight[0];
        }
    }
    uint32 idx = 1;

    // Traceback to find the minimum path metrics at each iteration
    for(int32 i=(N_d_bits/rate)-1; i>=0; i--)
    {
        uint8 state        = (uint8)phy_struct->vd_tb_state[idx-1];
        uint8 prev_state_0 = ((state*2) + (0 + (state%2) + (state/4))%2) % N_states;
        uint8 prev_state_1 = ((state*2) + (1 + (state%2) + (state/4))%2) % N_states;

        // Keep the smallest state
        if(phy_struct->vd_path_metric[prev_state_0][i] >
           phy_struct->vd_path_metric[prev_state_1][i])
        {
            phy_struct->vd_tb_state[idx]  = prev_state_1;
            phy_struct->vd_tb_weight[idx] = phy_struct->vd_w_metric[prev_state_1][i];
        }else{
            phy_struct->vd_tb_state[idx]  = prev_state_0;
            phy_struct->vd_tb_weight[idx] = phy_struct->vd_w_metric[prev_state_0][i];
        }
        if(phy_struct->vd_tb_weight[idx] > max_weight)
            max_weight = phy_struct->vd_tb_weight[idx];
        idx++;
    }
    uint32 tb_state_len = idx;

    // Read through the traceback to determine the input bits
    idx = 0;
    for(int32 i=tb_state_len-2; i>=0; i--)
    {
        uint8 state        = (uint8)phy_struct->vd_tb_state[i];
        uint8 prev_state_0 = ((state*2) + (0 + (state%2) + (state/4))%2) % N_states;

        // If the previous state corresponds to the "0" transition, the output
        // is a "0".  Otherwise it is a "1".
        int8 sign = -1;
        if(phy_struct->vd_tb_state[i+1] == prev_state_0)
            sign = +1;
        c_bits[idx++] = sign * 127 * (phy_struct->vd_tb_weight[i]/max_weight);
    }
    *N_c_bits = idx;
}

/*********************************************************************
    Name: turbo_constituent_encoder

    Description: Constituent encoder for the LTE Parallel Concatenated
                 Convolutional Code

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.3.2
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void turbo_constituent_encoder(uint8  *in_bits,
                               uint32  N_in_bits,
                               uint8  *out_bits,
                               uint8  *fb_bits)
{
    uint32 constraint_len = 4;
    uint8  s_reg[4]       = {0, 0, 0, 0};
    uint8  g_array[4]     = {1, 1, 0, 1};
    uint8  fb_array[4]    = {0, 0, 1, 1};

    // Convolutionally encode input
    for(uint32 i=0; i<N_in_bits; i++)
    {
        // Sequence the shift register
        for(int32 j=constraint_len-1; j>0; j--)
            s_reg[j] = s_reg[j-1];

        // Calculate the feedback bit
        fb_bits[i] = 0;
        for(uint32 j=0; j<constraint_len; j++)
            fb_bits[i] += s_reg[j]*fb_array[j];
        fb_bits[i] %= 2;

        // Add the next bit to the shift register
        s_reg[0] = (fb_bits[i] + in_bits[i]) % 2;

        // Calculate the output bit
        out_bits[i] = 0;
        for(uint32 j=0; j<constraint_len; j++)
            out_bits[i] += s_reg[j]*g_array[j];
        out_bits[i] %= 2;
    }

    // Trellis termination
    for(uint32 i=N_in_bits; i<N_in_bits+4; i++)
    {
        // Sequence the shift register
        for(int32 j=constraint_len-1; j>0; j--)
            s_reg[j] = s_reg[j-1];

        // Calculate the feedback bit
        fb_bits[i] = 0;
        for(uint32 j=0; j<constraint_len; j++)
            fb_bits[i] += s_reg[j]*fb_array[j];
        fb_bits[i] %= 2;

        // Add the next bit to the shift register
        s_reg[0] = (fb_bits[i] + fb_bits[i]) % 2;

        // Calculate the output bit
        out_bits[i] = 0;
        for(uint32 j=0; j<constraint_len; j++)
            out_bits[i] += s_reg[j]*g_array[j];
        out_bits[i] %= 2;
    }
}

/*********************************************************************
    Name: turbo_internal_interleaver / turbo_internal_deinterleaver

    Description: Internal interleaver / deinterleaver for the LTE
                 Parallel Concatenated Convolutional Code

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.3.2
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void turbo_internal_interleaver_get_f1_and_f2(uint32  N_in_bits,
                                              uint32 &f1,
                                              uint32 &f2)
{
    f1 = 0;
    f2 = 0;
    for(uint32 i=0; i<TURBO_INT_K_TABLE_SIZE; i++)
    {
        if(N_in_bits == TURBO_INT_K_TABLE[i])
        {
            f1 = TURBO_INT_F1_TABLE[i];
            f2 = TURBO_INT_F2_TABLE[i];
            break;
        }
    }
}
inline uint32 turbo_internal_interleaver_get_index(uint32 f1,
                                                   uint32 f2,
                                                   uint32 i,
                                                   uint32 N_in_bits)
{
    return (f1*i + f2*i*i) % N_in_bits;
}
void turbo_internal_interleaver(uint8  *in_bits,
                                uint32  N_in_bits,
                                uint8  *out_bits)
{
    // Determine f1 and f2
    uint32 f1;
    uint32 f2;
    turbo_internal_interleaver_get_f1_and_f2(N_in_bits, f1, f2);

    for(uint32 i=0; i<N_in_bits; i++)
        out_bits[i] = in_bits[turbo_internal_interleaver_get_index(f1, f2, i, N_in_bits)];
}
void turbo_internal_interleaver(int8   *in_bits,
                                uint32  N_in_bits,
                                int8   *out_bits)
{
    // Determine f1 and f2
    uint32 f1;
    uint32 f2;
    turbo_internal_interleaver_get_f1_and_f2(N_in_bits, f1, f2);

    for(uint32 i=0; i<N_in_bits; i++)
        out_bits[i] = in_bits[turbo_internal_interleaver_get_index(f1, f2, i, N_in_bits)];
}
void turbo_internal_deinterleaver(int8   *in_bits,
                                  uint32  N_in_bits,
                                  int8   *out_bits)
{
    // Determine f1 and f2
    uint32 f1;
    uint32 f2;
    turbo_internal_interleaver_get_f1_and_f2(N_in_bits, f1, f2);

    for(uint32 i=0; i<N_in_bits; i++)
        out_bits[turbo_internal_interleaver_get_index(f1, f2, i, N_in_bits)] = in_bits[i];
}

/*********************************************************************
    Name: turbo_encode / turbo_decode

    Description: Turbo encodes a bit array using the LTE Parallel
                 Concatenated Convolutional Code / Turbo decodes data
                 according to the LTE Parallel Concatenated
                 Convolutional Code.  This decoder uses a soft output
                 viterbi algorithm in an iterative fashion.

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.3.2

    Notes: Currently not handling filler bits
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void turbo_encode(LIBLTE_PHY_STRUCT *phy_struct,
                  uint8             *c_bits,
                  uint32             N_c_bits,
                  uint32             N_fill_bits,
                  uint8             *d_bits,
                  uint32            *N_d_bits)
{
    // Construct z
    turbo_constituent_encoder(c_bits,
                              N_c_bits,
                              phy_struct->te_z,
                              phy_struct->te_fb1);

    // Construct c_prime
    turbo_internal_interleaver(c_bits,
                               N_c_bits,
                               phy_struct->te_c_prime);

    // Construct z_prime
    turbo_constituent_encoder(phy_struct->te_c_prime,
                              N_c_bits,
                              phy_struct->te_z_prime,
                              phy_struct->te_x_prime);

    // Construct d_bits
    uint32 N_branch_bits = N_c_bits + 4;
    for(uint32 i=0; i<N_c_bits; i++)
    {
        d_bits[i]                 = c_bits[i];
        d_bits[N_branch_bits+i]   = phy_struct->te_z[i];
        d_bits[2*N_branch_bits+i] = phy_struct->te_z_prime[i];
    }
    d_bits[N_c_bits]                   = phy_struct->te_fb1[N_c_bits];
    d_bits[N_c_bits+1]                 = phy_struct->te_z[N_c_bits+1];
    d_bits[N_c_bits+2]                 = phy_struct->te_x_prime[N_c_bits];
    d_bits[N_c_bits+3]                 = phy_struct->te_z_prime[N_c_bits+1];
    d_bits[N_branch_bits+N_c_bits]     = phy_struct->te_z[N_c_bits];
    d_bits[N_branch_bits+N_c_bits+1]   = phy_struct->te_fb1[N_c_bits+2];
    d_bits[N_branch_bits+N_c_bits+2]   = phy_struct->te_z_prime[N_c_bits];
    d_bits[N_branch_bits+N_c_bits+3]   = phy_struct->te_x_prime[N_c_bits+2];
    d_bits[2*N_branch_bits+N_c_bits]   = phy_struct->te_fb1[N_c_bits+1];
    d_bits[2*N_branch_bits+N_c_bits+1] = phy_struct->te_z[N_c_bits+2];
    d_bits[2*N_branch_bits+N_c_bits+2] = phy_struct->te_x_prime[N_c_bits+1];
    d_bits[2*N_branch_bits+N_c_bits+3] = phy_struct->te_z_prime[N_c_bits+2];

    *N_d_bits = N_branch_bits*3;
}
void turbo_decode(LIBLTE_PHY_STRUCT *phy_struct,
                  float             *d_bits,
                  uint32             N_d_bits,
                  uint32             N_fill_bits,
                  uint32             N_iterations,
                  uint8             *c_bits,
                  uint32            *N_c_bits)
{
    // Step 0: Clear punctured bits
    uint32 n_cnt = 0;
    for(uint32 i=0; i<N_d_bits; i++)
        if(RX_NULL_BIT == d_bits[i])
        {
            n_cnt++;
            d_bits[i] = 0;
        }

    // Step 1: Calculate in_act_1 using d0 and d1
    float  max_value     = 0;
    uint32 N_branch_bits = N_d_bits/3;
    for(uint32 i=0; i<N_branch_bits; i++)
    {
        if(fabs(d_bits[i*3+0]) > max_value)
            max_value = fabs(d_bits[i*3+0]);
        if(fabs(d_bits[i*3+1]) > max_value)
            max_value = fabs(d_bits[i*3+1]);
        if(fabs(d_bits[i*3+2]) > max_value)
            max_value = fabs(d_bits[i*3+2]);
    }
    for(uint32 i=0; i<N_branch_bits-4; i++)
    {
        phy_struct->td_vitdec_apriori_in[i] = (int8)(d_bits[i]*127/max_value);
        phy_struct->td_vitdec_in_1[i*2+0]   = (int8)(d_bits[N_branch_bits+i]*127/max_value);
        phy_struct->td_vitdec_in_2[i*2+0]   = (int8)(d_bits[2*N_branch_bits+i]*127/max_value);
    }
    phy_struct->td_vitdec_in_1[(N_branch_bits-4)*2+0] = (int8)(d_bits[2*N_branch_bits-4]*127/max_value);
    phy_struct->td_vitdec_in_1[(N_branch_bits-4)*2+1] = (int8)(d_bits[N_branch_bits-4]*127/max_value);
    phy_struct->td_vitdec_in_1[(N_branch_bits-3)*2+0] = (int8)(d_bits[N_branch_bits-3]*127/max_value);
    phy_struct->td_vitdec_in_1[(N_branch_bits-3)*2+1] = (int8)(d_bits[3*N_branch_bits-4]*127/max_value);
    phy_struct->td_vitdec_in_1[(N_branch_bits-2)*2+0] = (int8)(d_bits[3*N_branch_bits-3]*127/max_value);
    phy_struct->td_vitdec_in_1[(N_branch_bits-2)*2+1] = (int8)(d_bits[2*N_branch_bits-3]*127/max_value);
    phy_struct->td_vitdec_in_2[(N_branch_bits-4)*2+0] = (int8)(d_bits[2*N_branch_bits-2]*127/max_value);
    phy_struct->td_vitdec_in_2[(N_branch_bits-4)*2+1] = (int8)(d_bits[N_branch_bits-2]*127/max_value);
    phy_struct->td_vitdec_in_2[(N_branch_bits-3)*2+0] = (int8)(d_bits[N_branch_bits-1]*127/max_value);
    phy_struct->td_vitdec_in_2[(N_branch_bits-3)*2+1] = (int8)(d_bits[3*N_branch_bits-2]*127/max_value);
    phy_struct->td_vitdec_in_2[(N_branch_bits-2)*2+0] = (int8)(d_bits[3*N_branch_bits-1]*127/max_value);
    phy_struct->td_vitdec_in_2[(N_branch_bits-2)*2+1] = (int8)(d_bits[2*N_branch_bits-1]*127/max_value);

    uint32 N_bits;
    uint32 g[2] = {015, 013}; // THESE ARE IN OCTAL
    for(uint32 i=0; i<N_iterations; i++)
    {
        for(uint32 j=0; j<N_branch_bits-4; j++)
            phy_struct->td_vitdec_in_1[j*2+1] = phy_struct->td_vitdec_apriori_in[j];

        viterbi_rsc_decode_siso(phy_struct,
                                phy_struct->td_vitdec_in_1,
                                (N_branch_bits-1)*2,
                                4,
                                2,
                                g,
                                phy_struct->td_vitdec_out,
                                &N_bits);
        turbo_internal_interleaver(phy_struct->td_vitdec_out,
                                   N_branch_bits-4,
                                   phy_struct->td_vitdec_apriori_in);

        for(uint32 j=0; j<N_branch_bits-4; j++)
            phy_struct->td_vitdec_in_2[2*j+1] = phy_struct->td_vitdec_apriori_in[j];

        viterbi_rsc_decode_siso(phy_struct,
                                phy_struct->td_vitdec_in_2,
                                (N_branch_bits-1)*2,
                                4,
                                2,
                                g,
                                phy_struct->td_vitdec_out,
                                &N_bits);
        turbo_internal_deinterleaver(phy_struct->td_vitdec_out,
                                     N_branch_bits-4,
                                     phy_struct->td_vitdec_apriori_in);
    }

    for(uint32 i=0; i<N_branch_bits-4; i++)
    {
        c_bits[i] = 1;
        if(phy_struct->td_vitdec_apriori_in[i] >= 0)
            c_bits[i] = 0;
    }
}

/*********************************************************************
    Name: rate_match_conv / rate_unmatch_conv

    Description: Rate matches / unmatches convolutionally encoded data

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.4.2
*********************************************************************/
// Defines
#define TX_NULL_BIT 100
// Enums
// Structs
// Functions
void rate_match_conv(LIBLTE_PHY_STRUCT *phy_struct,
                     uint8             *d_bits,
                     uint32             N_d_bits,
                     uint32             N_e_bits,
                     uint8             *e_bits)
{
    // Step 1: Assign C_cc_sb to 32
    uint32 C_cc_sb = 32;

    // Sub-block interleaving
    // Step 2: Determine the number of rows
    uint32 R_cc_sb = 0;
    while((N_d_bits/3) > (C_cc_sb*R_cc_sb))
        R_cc_sb++;

    // Steps 3, 4, and 5
    uint32 w_idx = 0;
    for(uint32 x=0; x<3; x++)
    {
        // Step 3: Pack data into matrix and pad with dummy
        uint32 N_dummy = 0;
        if((N_d_bits/3) < (C_cc_sb*R_cc_sb))
            N_dummy = C_cc_sb*R_cc_sb - (N_d_bits/3);
        for(uint32 i=0; i<N_dummy; i++)
            phy_struct->rmc_tmp[i] = TX_NULL_BIT;
        uint32 d_idx = 0;
        for(uint32 i=N_dummy; i<C_cc_sb*R_cc_sb; i++)
        {
            phy_struct->rmc_tmp[i] = d_bits[d_idx*3+x];
            d_idx++;
        }
        uint32 idx = 0;
        for(uint32 i=0; i<R_cc_sb; i++)
            for(uint32 j=0; j<C_cc_sb; j++)
                phy_struct->rmc_sb_mat[i][j] = phy_struct->rmc_tmp[idx++];

        // Step 4: Inter-column permutation
        for(uint32 i=0; i<R_cc_sb; i++)
            for(uint32 j=0; j<C_cc_sb; j++)
                phy_struct->rmc_sb_perm_mat[i][j] = phy_struct->rmc_sb_mat[i][IC_PERM_CC[j]];

        // Step 5: Read out the bits
        for(uint32 j=0; j<C_cc_sb; j++)
            for(uint32 i=0; i<R_cc_sb; i++)
                phy_struct->rmc_w[w_idx++] = phy_struct->rmc_sb_perm_mat[i][j];
    }
    uint32 K_pi = R_cc_sb*C_cc_sb;

    // Bit collection, selection, and transmission
    // Create circular buffer
    uint32 K_w = 3*K_pi;
    uint32 k   = 0;
    uint32 j   = 0;
    while(k < N_e_bits)
    {
        if(phy_struct->rmc_w[j%K_w] != TX_NULL_BIT)
            e_bits[k++] = phy_struct->rmc_w[j%K_w];
        j++;
    }
}
void rate_unmatch_conv(LIBLTE_PHY_STRUCT *phy_struct,
                       float             *e_bits,
                       uint32             N_e_bits,
                       uint32             N_c_bits,
                       float             *d_bits,
                       uint32            *N_d_bits)
{
    // Step 1: Assign C_cc_sb to 32
    uint32 C_cc_sb = 32;

    // In order to undo bit collection, selection, and transmission
    // a dummy block must be sub-block interleaved to determine
    // where NULL bits are to be inserted
    // Sub-block interleaving
    // Step 2: Determine the number of rows
    uint32 R_cc_sb = 0;
    while(N_c_bits > (C_cc_sb*R_cc_sb))
        R_cc_sb++;

    // Steps 3, 4, and 5
    uint32 w_idx = 0;
    uint32 idx;
    for(uint32 x=0; x<3; x++)
    {
        // Step 3: Pack data into matrix and pad with dummy
        uint32 N_dummy = 0;
        if(N_c_bits < (C_cc_sb*R_cc_sb))
            N_dummy = C_cc_sb*R_cc_sb - N_c_bits;
        for(uint32 i=0; i<N_dummy; i++)
            phy_struct->ruc_tmp[i] = RX_NULL_BIT;
        for(uint32 i=N_dummy; i<C_cc_sb*R_cc_sb; i++)
            phy_struct->ruc_tmp[i] = 0;
        idx = 0;
        for(uint32 i=0; i<R_cc_sb; i++)
            for(uint32 j=0; j<C_cc_sb; j++)
                phy_struct->ruc_sb_mat[i][j] = phy_struct->ruc_tmp[idx++];

        // Step 4: Inter-column permutation
        for(uint32 i=0; i<R_cc_sb; i++)
            for(uint32 j=0; j<C_cc_sb; j++)
                phy_struct->ruc_sb_perm_mat[i][j] = phy_struct->ruc_sb_mat[i][IC_PERM_CC[j]];

        // Step 5: Read out the bits
        for(uint32 j=0; j<C_cc_sb; j++)
        {
            for(uint32 i=0; i<R_cc_sb; i++)
            {
                phy_struct->ruc_w_dum[w_idx] = phy_struct->ruc_sb_perm_mat[i][j];
                phy_struct->ruc_w[w_idx]     = RX_NULL_BIT;
                w_idx++;
            }
        }
    }

    // Undo bit collection, selection, and transmission by
    // recreating the circular buffer
    uint32 K_pi = R_cc_sb*C_cc_sb;
    uint32 K_w  = 3*K_pi;
    uint32 k    = 0;
    uint32 j    = 0;
    while(k < N_e_bits)
    {
        if(phy_struct->ruc_w_dum[j%K_w] != RX_NULL_BIT)
        {
            // Soft combine the inputs
            if(phy_struct->ruc_w[j%K_w] == RX_NULL_BIT)
            {
                phy_struct->ruc_w[j%K_w] = e_bits[k];
            }else if(e_bits[k] != RX_NULL_BIT){
                phy_struct->ruc_w[j%K_w] += e_bits[k];
            }
            k++;
        }
        j++;
    }

    // Recreate the sub-block interleaver output
    for(uint32 i=0; i<K_pi; i++)
    {
        phy_struct->ruc_v[0][i] = phy_struct->ruc_w[i];
        phy_struct->ruc_v[1][i] = phy_struct->ruc_w[i+K_pi];
        phy_struct->ruc_v[2][i] = phy_struct->ruc_w[i+2*K_pi];
    }

    // Sub-block deinterleaving
    // Steps 5, 4, and 3
    uint32 d_idx;
    for(uint32 x=0; x<3; x++)
    {
        // Step 5: Load the permuted matrix
        idx = 0;
        for(j=0; j<C_cc_sb; j++)
            for(uint32 i=0; i<R_cc_sb; i++)
                phy_struct->ruc_sb_perm_mat[i][j] = phy_struct->ruc_v[x][idx++];

        // Step 4: Undo permutation
        for(uint32 i=0; i<R_cc_sb; i++)
            for(j=0; j<C_cc_sb; j++)
                phy_struct->ruc_sb_mat[i][IC_PERM_CC[j]] = phy_struct->ruc_sb_perm_mat[i][j];

        // Step 3: Unpack the data and remove dummy
        uint32 N_dummy = 0;
        if(N_c_bits < (C_cc_sb*R_cc_sb))
            N_dummy = C_cc_sb*R_cc_sb - N_c_bits;
        idx = 0;
        for(uint32 i=0; i<R_cc_sb; i++)
            for(j=0; j<C_cc_sb; j++)
                phy_struct->ruc_tmp[idx++] = phy_struct->ruc_sb_mat[i][j];
        d_idx = 0;
        for(uint32 i=N_dummy; i<C_cc_sb*R_cc_sb; i++)
        {
            d_bits[d_idx*3+x] = phy_struct->ruc_tmp[i];
            d_idx++;
        }
    }
    *N_d_bits = d_idx*3;
}

/*********************************************************************
    Name: code_block_concatenation / code_block_deconcatenation

    Description: Performs code block concatenation / deconcatenation
                 for turbo coded channels

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.5
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void code_block_concatenation(LIBLTE_PHY_E_BITS_STRUCT *e,
                              uint32                    N_codeblocks,
                              uint8                    *f_bits,
                              uint32                   *N_f_bits)
{
    // Concatenate code blocks
    uint32 r = 0;
    uint32 k = 0;
    while(r < N_codeblocks)
    {
        uint32 j = 0;
        while(j < e->N_bits[r])
            f_bits[k++] = e->tx_bits[r][j++];
        r++;
    }
    *N_f_bits = k;
}
void get_code_block_segmentation_parameters(uint32  N_b_bits,
                                            uint32 *L,
                                            uint32 *C,
                                            uint32 *B_prime,
                                            uint32 *K_plus,
                                            uint32 *C_plus,
                                            uint32 *K_minus,
                                            uint32 *C_minus,
                                            uint32 *F)
{
    uint32 Z = 6144;

    *K_plus  = 0;
    *K_minus = 0;
    if(N_b_bits <= Z)
    {
        *L       = 0;
        *C       = 1;
        *B_prime = N_b_bits;
        for(uint32 i=0; i<TURBO_INT_K_TABLE_SIZE; i++)
        {
            if(*C*TURBO_INT_K_TABLE[i] >= *B_prime)
            {
                *K_plus = TURBO_INT_K_TABLE[i];
                break;
            }
        }
        *K_minus = 0;
        *C_plus  = 1;
        *C_minus = 0;
        *F       = (*C_plus)*(*K_plus) + (*C_minus)*(*K_minus) - (*B_prime);
        return;
    }

    uint32 B = N_b_bits;
    *L       = 24;
    *C       = (uint32)ceilf((float)B/(float)(Z-(*L)));
    *B_prime = B + (*C)*(*L);
    for(uint32 i=0; i<TURBO_INT_K_TABLE_SIZE; i++)
    {
        if(*C*TURBO_INT_K_TABLE[i] >= *B_prime)
        {
            *K_plus = TURBO_INT_K_TABLE[i];
            break;
        }
    }
    for(int32 i=TURBO_INT_K_TABLE_SIZE-1; i>=0; i--)
    {
        if(TURBO_INT_K_TABLE[i] < *K_plus)
        {
            *K_minus = TURBO_INT_K_TABLE[i];
            break;
        }
    }
    uint32 K_delta = K_plus - K_minus;
    *C_minus       = ((*C)*(*K_plus) - (*B_prime))/K_delta;
    *C_plus        = (*C) - (*C_minus);
    *F             = (*C_plus)*(*K_plus) + (*C_minus)*(*K_minus) - (*B_prime);
}
void code_block_deconcatenation(float                    *f_bits,
                                uint32                    N_f_bits,
                                uint32                    tbs,
                                uint32                    G,
                                uint32                    N_l,
                                uint32                    Q_m,
                                LIBLTE_PHY_E_BITS_STRUCT *e,
                                uint32                   *N_codeblocks)
{
    // Determine L, C, B', K+, C+, K-, and C-, 3GPP TS 36.212 v10.1.0 section 5.1.2
    uint32 L;
    uint32 B_prime;
    uint32 K_plus;
    uint32 C_plus;
    uint32 K_minus;
    uint32 C_minus;
    uint32 F;
    get_code_block_segmentation_parameters(tbs+24, &L, N_codeblocks, &B_prime, &K_plus,
                                           &C_plus, &K_minus, &C_minus, &F);

    // Deconcatenate code blocks
    uint32 k = 0;
    uint32 r = 0;
    while(r < *N_codeblocks)
    {
        uint32 G_prime = G/(N_l*Q_m);
        uint32 lambda  = G_prime % *N_codeblocks;
        if(r <= (*N_codeblocks - lambda - 1))
        {
            e->N_bits[r] = N_l*Q_m*(G_prime/(*N_codeblocks));
        }else{
            e->N_bits[r] = N_l*Q_m*(uint32)ceilf((float)G_prime/(float)(*N_codeblocks));
        }

        uint32 j = 0;
        while(j < e->N_bits[r])
            e->rx_bits[r][j++] = f_bits[k++];
        r++;
    }
}

/*********************************************************************
    Name: ulsch_data_control_multiplexing /
          ulsch_data_control_demultiplexing

    Description: Multiplexes / Demultiplexes the control and data bits
                 for Uplink Shared Channel

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.2.2.7
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void ulsch_data_control_multiplexing(uint8  *f_bits,
                                     uint32  N_f_bits,
                                     uint8  *cqi_bits,
                                     uint32  N_cqi_bits,
                                     uint32  N_l,
                                     uint32  Q_m,
                                     uint8  *g_bits,
                                     uint32 *N_g_bits)
{
    uint32 j = 0;
    uint32 k = 0;
    while(j < N_cqi_bits)
    {
        for(uint32 n=0; n<N_l*Q_m; n++)
            g_bits[k*N_l*Q_m + n] = cqi_bits[j+n];
        j += N_l*Q_m;
        k++;
    }
    uint32 i = 0;
    while(i < N_f_bits)
    {
        for(uint32 n=0; n<N_l*Q_m; n++)
            g_bits[k*N_l*Q_m + n] = f_bits[i+n];
        i += N_l*Q_m;
        k++;
    }
    *N_g_bits = k;
}
void ulsch_data_control_demultiplexing(float  *g_bits,
                                       uint32  N_g_bits,
                                       uint32  N_cqi_bits,
                                       uint32  N_l,
                                       uint32  Q_m,
                                       float  *f_bits,
                                       uint32 *N_f_bits,
                                       float  *cqi_bits)
{
    uint32 j = 0;
    uint32 k = 0;
    while(j < N_cqi_bits)
    {
        for(uint32 n=0; n<N_l*Q_m; n++)
            cqi_bits[j + n] = g_bits[k*Q_m*N_l + n];
        j += N_l*Q_m;
        k++;
    }
    *N_f_bits = N_g_bits - N_cqi_bits;
    uint32 i  = 0;
    while(i < *N_f_bits)
    {
        for(uint32 n=0; n<N_l*Q_m; n++)
            f_bits[i + n] = g_bits[k*Q_m*N_l + n];
        i += N_l*Q_m;
        k++;
    }
}

/*********************************************************************
    Name: ulsch_channel_interleaver / ulsch_channel_deinterleaver

    Description: Interleaves / Deinterleaves Uplink Shared Channel
                 data with RI and ACK control information

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.2.2.8
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void ulsch_channel_interleaver(LIBLTE_PHY_STRUCT *phy_struct,
                               uint8             *g_bits,
                               uint32             N_g_bits,
                               uint8             *ri_bits,
                               uint32             N_ri_bits,
                               uint8             *ack_bits,
                               uint32             N_ack_bits,
                               uint32             N_l,
                               uint32             Q_m,
                               uint8             *h_bits,
                               uint32            *N_h_bits)
{
    uint32 N_pusch_symbs = 12; // FIXME: Only handling normal CP

    // Step 1: Define C_mux
    uint32 C_mux = N_pusch_symbs;

    // Step 2: Define R_mux and R_prime_mux
    uint32 H_prime       = N_g_bits;
    uint32 H_prime_total = H_prime + N_ri_bits;
    uint32 R_mux         = (H_prime_total*Q_m*N_l)/C_mux;
    uint32 R_prime_mux   = R_mux/(Q_m*N_l);

    // Initialize the matricies
    for(uint32 i=0; i<C_mux*R_prime_mux; i++)
        phy_struct->ulsch_y_idx[i] = TX_NULL_SYMB;
    for(uint32 i=0; i<C_mux*R_mux; i++)
        phy_struct->ulsch_y_mat[i] = 0;

    // Step 3: Interleave the RI control bits
    uint32 i                = 0;
    uint32 j                = 0;
    uint32 r                = R_prime_mux-1;
    uint32 ri_column_set[4] = {1, 4, 7, 10};
    while(i < N_ri_bits)
    {
        uint32 C_ri                             = ri_column_set[j];
        phy_struct->ulsch_y_idx[r*C_mux + C_ri] = 1;
        for(uint32 k=0; k<Q_m*N_l; k++)
            phy_struct->ulsch_y_mat[(C_mux*r*Q_m*N_l) + C_ri*Q_m*N_l + k] = ri_bits[i+k];
        i++;
        r = R_prime_mux - 1 - i/4;
        j = (j + 3) % 4;
    }

    // Step 4: Interleave the data bits
    i        = 0;
    uint32 k = 0;
    while(k < H_prime)
    {
        if(phy_struct->ulsch_y_idx[i] == TX_NULL_SYMB)
        {
            phy_struct->ulsch_y_idx[i] = 1;
            for(j=0; j<Q_m*N_l; j++)
                phy_struct->ulsch_y_mat[i*Q_m*N_l + j] = g_bits[k*Q_m*N_l + j];
            k++;
        }
        i++;
    }

    // Step 5: Interleave the ACK control bits
    i                        = 0;
    j                        = 0;
    r                        = R_prime_mux-1;
    uint32 ack_column_set[4] = {2, 3, 8, 9};
    while(i < N_ack_bits)
    {
        uint32 C_ack                             = ack_column_set[j];
        phy_struct->ulsch_y_idx[r*C_mux + C_ack] = 2;
        for(k=0; k<Q_m*N_l; k++)
            phy_struct->ulsch_y_mat[(C_mux*r*Q_m*N_l) + C_ack*Q_m*N_l + k] = ack_bits[i+k];
        i++;
        r = R_prime_mux - 1 - i/4;
        j = (j + 3) % 4;
    }

    // Step 6: Read out the bits
    uint32 idx = 0;
    for(i=0; i<C_mux; i++)
        for(j=0; j<R_prime_mux; j++)
            for(k=0; k<Q_m*N_l; k++)
                h_bits[idx++] = phy_struct->ulsch_y_mat[j*C_mux*Q_m*N_l + i*Q_m*N_l + k];
    *N_h_bits = idx;
}
void ulsch_channel_deinterleaver(LIBLTE_PHY_STRUCT *phy_struct,
                                 float             *h_bits,
                                 uint32             N_h_bits,
                                 uint32             N_ri_bits,
                                 uint32             N_ack_bits,
                                 uint32             N_l,
                                 uint32             Q_m,
                                 float             *g_bits,
                                 uint32            *N_g_bits,
                                 float             *ri_bits,
                                 float             *ack_bits)
{
    uint32 N_pusch_symbs = 12; // FIXME: Only handling normal CP

    // Step 1: Define C_mux
    uint32 C_mux = N_pusch_symbs;

    // Step 2: Define R_mux and R_prime_mux
    uint32 H_prime       = N_h_bits/(Q_m*N_l);
    uint32 H_prime_total = H_prime + N_ri_bits;
    uint32 R_mux         = (H_prime_total*Q_m*N_l)/C_mux;
    uint32 R_prime_mux   = R_mux/(Q_m*N_l);

    // Initialize the matricies
    for(uint32 i=0; i<C_mux*R_prime_mux; i++)
        phy_struct->ulsch_y_idx[i] = RX_NULL_SYMB;
    for(uint32 i=0; i<C_mux*R_mux; i++)
        phy_struct->ulsch_y_mat[i] = 0;

    // Step 6: Construct matrix
    uint32 idx = 0;
    for(uint32 i=0; i<C_mux; i++)
        for(uint32 j=0; j<R_prime_mux; j++)
            for(uint32 k=0; k<Q_m*N_l; k++)
                phy_struct->ulsch_y_mat[j*C_mux*Q_m*N_l + i*Q_m*N_l + k] = h_bits[idx++];

    // Step 5: Deinterleave the ACK control bits
    uint32 i                 = 0;
    uint32 j                 = 0;
    uint32 r                 = R_prime_mux-1;
    uint32 ack_column_set[4] = {2, 3, 8, 9};
    while(i < N_ack_bits)
    {
        uint32 C_ack                             = ack_column_set[j];
        phy_struct->ulsch_y_idx[r*C_mux + C_ack] = 2;
        for(uint32 k=0; k<Q_m*N_l; k++)
            ack_bits[i+k] = phy_struct->ulsch_y_mat[C_mux*r*Q_m*N_l + C_ack*Q_m*N_l + k];
        i++;
        r = R_prime_mux - 1 - i/4;
        j = (j + 3) % 4;
    }

    // Step 3: Deinterleave the RI control bits
    i                       = 0;
    j                       = 0;
    r                       = R_prime_mux-1;
    uint32 ri_column_set[4] = {1, 4, 7, 10};
    while(i < N_ri_bits)
    {
        uint32 C_ri                             = ri_column_set[j];
        phy_struct->ulsch_y_idx[r*C_mux + C_ri] = 1;
        for(uint32 k=0; k<Q_m*N_l; k++)
            ri_bits[i*Q_m*N_l + k] = phy_struct->ulsch_y_mat[C_mux*r*Q_m*N_l + C_ri*Q_m*N_l + k];
        i++;
        r = R_prime_mux - 1 - i/4;
        j = (j + 3) % 4;
    }

    // Step 4: Interleave the data bits
    i        = 0;
    uint32 k = 0;
    while(k < H_prime)
    {
        if(phy_struct->ulsch_y_idx[i] == RX_NULL_SYMB)
        {
            phy_struct->ulsch_y_idx[i] = 1;
            for(j=0; j<Q_m*N_l; j++)
                g_bits[k*Q_m*N_l + j] = phy_struct->ulsch_y_mat[i*Q_m*N_l + j];
            k++;
        }else if(phy_struct->ulsch_y_idx[i] == 2){
            for(j=0; j<Q_m*N_l; j++)
                g_bits[k*Q_m*N_l + j] = RX_NULL_SYMB;
            k++;
        }
        i++;
    }
    *N_g_bits = k*Q_m*N_l;
}

/*********************************************************************
    Name: ulsch_channel_encode / ulsch_channel_decode

    Description: Channel encodes / decodes the Uplink Shared Channel

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.2.2

    Notes: Not handling control bits
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void ulsch_channel_encode(LIBLTE_PHY_STRUCT *phy_struct,
                          uint8             *in_bits,
                          uint32             N_in_bits,
                          uint32             tbs,
                          uint32             tx_mode,
                          uint32             G,
                          uint32             N_l,
                          uint32             Q_m,
                          uint32             rv_idx,
                          uint8             *out_bits,
                          uint32            *N_out_bits)
{
    // Define a_bits
    uint8 *a_bits = in_bits;

    // Pad input up to tbs size, calculate p_bits, and construct b_bits
    uint8 p_bits[24];
    for(uint32 i=0; i<N_in_bits; i++)
        phy_struct->ulsch_b_bits[i] = a_bits[i];
    for(uint32 i=N_in_bits; i<tbs; i++)
        phy_struct->ulsch_b_bits[i] = 0;
    calc_crc(phy_struct->ulsch_b_bits, tbs, CRC24A, p_bits, 24);
    for(uint32 i=0; i<24; i++)
        phy_struct->ulsch_b_bits[tbs+i] = p_bits[i];

    // Construct c_bits
    uint32 N_codeblocks;
    uint32 N_fill_bits;
    liblte_phy_code_block_segmentation(phy_struct->ulsch_b_bits,
                                       tbs+24,
                                       &N_codeblocks,
                                       &N_fill_bits,
                                       &phy_struct->ulsch_c);

    for(uint32 cb=0; cb<N_codeblocks; cb++)
    {
        // Construct d_bits
        uint32 N_d_bits;
        turbo_encode(phy_struct,
                     phy_struct->ulsch_c.bits[cb],
                     phy_struct->ulsch_c.N_bits[cb],
                     N_fill_bits,
                     phy_struct->ulsch_tx_d_bits,
                     &N_d_bits);

        // Determine e_bits and N_e_bits
        uint32 G_prime = G/(N_l*Q_m);
        uint32 lambda  = G_prime % N_codeblocks;
        if(cb <= (N_codeblocks - lambda - 1))
        {
            phy_struct->ulsch_e.N_bits[cb] = N_l*Q_m*(G_prime/N_codeblocks);
        }else{
            phy_struct->ulsch_e.N_bits[cb] = N_l*Q_m*(uint32)ceilf((float)G_prime/(float)N_codeblocks);
        }
        liblte_phy_rate_match_turbo(phy_struct,
                                    phy_struct->ulsch_tx_d_bits,
                                    N_d_bits,
                                    N_codeblocks,
                                    tx_mode,
                                    1,
                                    1,
                                    LIBLTE_PHY_CHAN_TYPE_ULSCH,
                                    rv_idx,
                                    phy_struct->ulsch_e.N_bits[cb],
                                    phy_struct->ulsch_e.tx_bits[cb]);
    }

    // Determine f_bits
    uint32 N_f_bits;
    code_block_concatenation(&phy_struct->ulsch_e,
                             N_codeblocks,
                             phy_struct->ulsch_tx_f_bits,
                             &N_f_bits);

    // Determine g_bits
    uint32 N_g_bits;
    uint32 N_cqi_bits = 0;
    ulsch_data_control_multiplexing(phy_struct->ulsch_tx_f_bits,
                                    N_f_bits,
                                    NULL,
                                    N_cqi_bits,
                                    N_l,
                                    Q_m,
                                    phy_struct->ulsch_tx_g_bits,
                                    &N_g_bits);

    // Determine output
    uint32 N_ri_bits  = 0;
    uint32 N_ack_bits = 0;
    ulsch_channel_interleaver(phy_struct,
                              phy_struct->ulsch_tx_g_bits,
                              N_g_bits,
                              NULL,
                              N_ri_bits,
                              NULL,
                              N_ack_bits,
                              N_l,
                              Q_m,
                              out_bits,
                              N_out_bits);
}
LIBLTE_ERROR_ENUM ulsch_channel_decode(LIBLTE_PHY_STRUCT *phy_struct,
                                       float             *in_bits,
                                       uint32             N_in_bits,
                                       uint32             tbs,
                                       uint32             tx_mode,
                                       uint32             G,
                                       uint32             N_l,
                                       uint32             Q_m,
                                       uint32             rv_idx,
                                       uint32             N_turbo_iterations,
                                       uint8             *out_bits,
                                       uint32            *N_out_bits)
{
    // In order to decode an ULSCH message, the NULL bit pattern must be
    // determined by encoding a sequence of zeros
    uint32 N_b_bits = tbs+24;
    memset(phy_struct->ulsch_b_bits, 0, sizeof(uint8)*N_b_bits);
    uint32 N_codeblocks;
    uint32 N_fill_bits;
    liblte_phy_code_block_segmentation(phy_struct->ulsch_b_bits,
                                       N_b_bits,
                                       &N_codeblocks,
                                       &N_fill_bits,
                                       &phy_struct->ulsch_c);

    // Determine g_bits
    uint32 N_g_bits;
    uint32 N_ri_bits  = 0;
    uint32 N_ack_bits = 0;
    ulsch_channel_deinterleaver(phy_struct,
                                in_bits,
                                N_in_bits,
                                N_ri_bits,
                                N_ack_bits,
                                N_l,
                                Q_m,
                                phy_struct->ulsch_rx_g_bits,
                                &N_g_bits,
                                NULL,
                                NULL);

    // Determine f_bits
    uint32 N_f_bits;
    uint32 N_cqi_bits = 0;
    ulsch_data_control_demultiplexing(phy_struct->ulsch_rx_g_bits,
                                      N_g_bits,
                                      N_cqi_bits,
                                      N_l,
                                      Q_m,
                                      phy_struct->ulsch_rx_f_bits,
                                      &N_f_bits,
                                      NULL);

    // Determine e_bits
    code_block_deconcatenation(phy_struct->ulsch_rx_f_bits,
                               N_f_bits,
                               tbs,
                               G,
                               N_l,
                               Q_m,
                               &phy_struct->ulsch_e,
                               &N_codeblocks);

    for(uint32 cb=0; cb<N_codeblocks; cb++)
    {
        // Construct dummy_d_bits
        uint32 N_d_bits;
        turbo_encode(phy_struct,
                     phy_struct->ulsch_c.bits[cb],
                     phy_struct->ulsch_c.N_bits[cb],
                     N_fill_bits,
                     phy_struct->ulsch_tx_d_bits,
                     &N_d_bits);

        // Determine d_bits
        liblte_phy_rate_unmatch_turbo(phy_struct,
                                      phy_struct->ulsch_e.rx_bits[cb],
                                      phy_struct->ulsch_e.N_bits[cb],
                                      phy_struct->ulsch_tx_d_bits,
                                      N_d_bits/3,
                                      N_codeblocks,
                                      tx_mode,
                                      1,
                                      1,
                                      LIBLTE_PHY_CHAN_TYPE_ULSCH,
                                      rv_idx,
                                      phy_struct->ulsch_rx_d_bits,
                                      &N_d_bits);

        // Determine c_bits
        turbo_decode(phy_struct,
                     phy_struct->ulsch_rx_d_bits,
                     N_d_bits,
                     N_fill_bits,
                     N_turbo_iterations,
                     phy_struct->ulsch_c.bits[cb],
                     &phy_struct->ulsch_c.N_bits[cb]);
    }

    // Determine b_bits
    liblte_phy_code_block_desegmentation(&phy_struct->ulsch_c,
                                         tbs,
                                         phy_struct->ulsch_b_bits,
                                         N_b_bits);

    // Recover a_bits and p_bits
    uint8 *a_bits = &phy_struct->ulsch_b_bits[0];
    uint8 *p_bits = &phy_struct->ulsch_b_bits[tbs];

    // Calculate p_bits
    uint8 calc_p_bits[24];
    calc_crc(a_bits, tbs, CRC24A, calc_p_bits, 24);

    // Check CRC
    if(0 == check_crc(p_bits, calc_p_bits, 24))
    {
        for(uint32 i=0; i<tbs; i++)
            out_bits[i] = a_bits[i];
        *N_out_bits = tbs;
        return LIBLTE_SUCCESS;
    }

    return LIBLTE_ERROR_INVALID_CRC;
}

/*********************************************************************
    Name: bch_channel_encode / bch_channel_decode

    Description: Channel encodes / decodes the broadcast channel

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.3.1
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void bch_channel_encode(LIBLTE_PHY_STRUCT *phy_struct,
                        uint8             *in_bits,
                        uint32             N_in_bits,
                        uint8              N_ant,
                        uint8             *out_bits,
                        uint32            *N_out_bits)
{
    uint8 *ant_mask       = NULL;
    uint8  ant_mask_1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint8  ant_mask_2[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    uint8  ant_mask_4[16] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
    if(N_ant == 1)
    {
        ant_mask = ant_mask_1;
    }else if(N_ant == 2){
        ant_mask = ant_mask_2;
    }else{
        ant_mask = ant_mask_4;
    }

    // Define a_bits
    uint8 *a_bits = in_bits;

    // Calculate p_bits
    uint8 p_bits[16];
    calc_crc(a_bits, 24, CRC16, p_bits, 16);

    // Mask p_bits
    for(uint32 i=0; i<16; i++)
        p_bits[i] = p_bits[i] ^ ant_mask[i];

    // Construct c_bits
    for(uint32 i=0; i<24; i++)
        phy_struct->bch_c_bits[i] = a_bits[i];
    for(uint32 i=0; i<16; i++)
        phy_struct->bch_c_bits[24+i] = p_bits[i];

    // Determine d_bits
    uint32 N_d_bits;
    uint32 g[3] = {0133, 0171, 0165}; // Numbers are in octal
    conv_encode(phy_struct,
                phy_struct->bch_c_bits,
                40,
                7,
                3,
                g,
                true,
                phy_struct->bch_tx_d_bits,
                &N_d_bits);

    // Determine e_bits
    rate_match_conv(phy_struct, phy_struct->bch_tx_d_bits, N_d_bits, 1920, out_bits);
    *N_out_bits = 1920;
}
LIBLTE_ERROR_ENUM bch_channel_decode(LIBLTE_PHY_STRUCT *phy_struct,
                                     float             *in_bits,
                                     uint32             N_in_bits,
                                     uint8              N_ant,
                                     uint8             *out_bits,
                                     uint32            *N_out_bits)
{
    // Choose the correct antenna mask
    uint8 *ant_mask       = NULL;
    uint8  ant_mask_1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint8  ant_mask_2[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    uint8  ant_mask_4[16] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
    if(1 == N_ant)
    {
        ant_mask = ant_mask_1;
    }else if(2 == N_ant){
        ant_mask = ant_mask_2;
    }else{ // 4 == N_ant
        ant_mask = ant_mask_4;
    }

    // Rate unmatch to get the d_bits
    uint32 N_d_bits;
    rate_unmatch_conv(phy_struct,
                      in_bits,
                      N_in_bits,
                      40,
                      phy_struct->bch_rx_d_bits,
                      &N_d_bits);

    // Viterbi decode the d_bits to get the c_bits
    uint32 N_c_bits;
    uint32 g[3] = {0133, 0171, 0165}; // Numbers are in octal
    viterbi_decode(phy_struct,
                   phy_struct->bch_rx_d_bits,
                   N_d_bits,
                   7,
                   3,
                   g,
                   phy_struct->bch_c_bits,
                   &N_c_bits);

    // Recover a_bits and p_bits
    uint8 *a_bits = &phy_struct->bch_c_bits[0];
    uint8 *p_bits = &phy_struct->bch_c_bits[24];

    // Calculate p_bits
    uint8 calc_p_bits[16];
    calc_crc(a_bits, 24, CRC16, calc_p_bits, 16);

    // Calculate the number of bit errors
    uint32 ber = 0;
    for(uint32 i=0; i<16; i++)
        ber += p_bits[i] ^ (calc_p_bits[i] ^ ant_mask[i]);
    if(ber == 0)
    {
        for(uint32 i=0; i<24; i++)
            out_bits[i] = a_bits[i];
        *N_out_bits = 24;
        return LIBLTE_SUCCESS;
    }

    return LIBLTE_ERROR_INVALID_CRC;
}

/*********************************************************************
    Name: dlsch_channel_encode / dlsch_channel_decode

    Description: Channel encodes / decodes the Downlink Shared Channel

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.3.2
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void dlsch_channel_encode(LIBLTE_PHY_STRUCT *phy_struct,
                          uint8             *in_bits,
                          uint32             N_in_bits,
                          uint32             tbs,
                          uint32             tx_mode,
                          uint32             rv_idx,
                          uint32             G,
                          uint32             N_l,
                          uint32             Q_m,
                          uint32             M_dl_harq,
                          uint32             N_soft,
                          uint8             *out_bits,
                          uint32            *N_out_bits)
{
    // Define a_bits
    uint8 *a_bits = in_bits;

    // Pad input up to tbs size, calculate p_bits, and construct b_bits
    for(uint32 i=0; i<N_in_bits; i++)
        phy_struct->dlsch_b_bits[i] = a_bits[i];
    for(uint32 i=N_in_bits; i<tbs; i++)
        phy_struct->dlsch_b_bits[i] = 0;
    uint8 p_bits[24];
    calc_crc(phy_struct->dlsch_b_bits, tbs, CRC24A, p_bits, 24);
    for(uint32 i=0; i<24; i++)
        phy_struct->dlsch_b_bits[tbs+i] = p_bits[i];

    // Construct c_bits
    uint32 N_codeblocks;
    uint32 N_fill_bits;
    liblte_phy_code_block_segmentation(phy_struct->dlsch_b_bits,
                                       tbs+24,
                                       &N_codeblocks,
                                       &N_fill_bits,
                                       &phy_struct->dlsch_c);

    for(uint32 cb=0; cb<N_codeblocks; cb++)
    {
        // Construct d_bits
        uint32 N_d_bits;
        turbo_encode(phy_struct,
                     phy_struct->dlsch_c.bits[cb],
                     phy_struct->dlsch_c.N_bits[cb],
                     N_fill_bits,
                     phy_struct->dlsch_tx_d_bits,
                     &N_d_bits);

        // Determine e_bits and N_e_bits
        uint32 G_prime = G/(N_l*Q_m);
        uint32 lambda  = G_prime % N_codeblocks;
        if(cb <= (N_codeblocks - lambda - 1))
        {
            phy_struct->dlsch_e.N_bits[cb] = N_l*Q_m*(G_prime/N_codeblocks);
        }else{
            phy_struct->dlsch_e.N_bits[cb] = N_l*Q_m*(uint32)ceilf((float)G_prime/(float)N_codeblocks);
        }
        liblte_phy_rate_match_turbo(phy_struct,
                                    phy_struct->dlsch_tx_d_bits,
                                    N_d_bits,
                                    N_codeblocks,
                                    tx_mode,
                                    N_soft,
                                    M_dl_harq,
                                    LIBLTE_PHY_CHAN_TYPE_DLSCH,
                                    rv_idx,
                                    phy_struct->dlsch_e.N_bits[cb],
                                    phy_struct->dlsch_e.tx_bits[cb]);
    }

    code_block_concatenation(&phy_struct->dlsch_e, N_codeblocks, out_bits, N_out_bits);
}
LIBLTE_ERROR_ENUM dlsch_channel_decode(LIBLTE_PHY_STRUCT *phy_struct,
                                       float             *in_bits,
                                       uint32             N_in_bits,
                                       uint32             tbs,
                                       uint32             tx_mode,
                                       uint32             rv_idx,
                                       uint32             G,
                                       uint32             N_l,
                                       uint32             Q_m,
                                       uint32             M_dl_harq,
                                       uint32             N_soft,
                                       uint32             N_turbo_iterations,
                                       uint8             *out_bits,
                                       uint32            *N_out_bits)
{
    // In order to decode a DLSCH message, the NULL bit pattern must be
    // determined by encoding a sequence of zeros
    uint32 N_b_bits = tbs+24;
    memset(phy_struct->dlsch_b_bits, 0, sizeof(uint8)*N_b_bits);
    uint32 N_codeblocks;
    uint32 N_fill_bits;
    liblte_phy_code_block_segmentation(phy_struct->dlsch_b_bits,
                                       N_b_bits,
                                       &N_codeblocks,
                                       &N_fill_bits,
                                       &phy_struct->dlsch_c);

    // Determine e_bits
    code_block_deconcatenation(in_bits,
                               N_in_bits,
                               tbs,
                               G,
                               N_l,
                               Q_m,
                               &phy_struct->dlsch_e,
                               &N_codeblocks);

    for(uint32 cb=0; cb<N_codeblocks; cb++)
    {
        // Construct dummy_d_bits
        uint32 N_d_bits;
        turbo_encode(phy_struct,
                     phy_struct->dlsch_c.bits[cb],
                     phy_struct->dlsch_c.N_bits[cb],
                     N_fill_bits,
                     phy_struct->dlsch_tx_d_bits,
                     &N_d_bits);

        // Determine d_bits
        liblte_phy_rate_unmatch_turbo(phy_struct,
                                      phy_struct->dlsch_e.rx_bits[cb],
                                      phy_struct->dlsch_e.N_bits[cb],
                                      phy_struct->dlsch_tx_d_bits,
                                      N_d_bits/3,
                                      N_codeblocks,
                                      tx_mode,
                                      N_soft,
                                      M_dl_harq,
                                      LIBLTE_PHY_CHAN_TYPE_DLSCH,
                                      rv_idx,
                                      phy_struct->dlsch_rx_d_bits,
                                      &N_d_bits);

        // Determine c_bits
        turbo_decode(phy_struct,
                     phy_struct->dlsch_rx_d_bits,
                     N_d_bits,
                     N_fill_bits,
                     N_turbo_iterations,
                     phy_struct->dlsch_c.bits[cb],
                     &phy_struct->dlsch_c.N_bits[cb]);
    }

    // Determine b_bits
    liblte_phy_code_block_desegmentation(&phy_struct->dlsch_c,
                                         tbs,
                                         phy_struct->dlsch_b_bits,
                                         N_b_bits);

    // Recover a_bits and p_bits
    uint8 *a_bits = &phy_struct->dlsch_b_bits[0];
    uint8 *p_bits = &phy_struct->dlsch_b_bits[tbs];

    // Calculate p_bits
    uint8 calc_p_bits[24];
    calc_crc(a_bits, tbs, CRC24A, calc_p_bits, 24);

    // Check CRC
    if(0 == check_crc(p_bits, calc_p_bits, 24))
    {
        for(uint32 i=0; i<tbs; i++)
            out_bits[i] = a_bits[i];
        *N_out_bits = tbs;
        return LIBLTE_SUCCESS;
    }

    return LIBLTE_ERROR_INVALID_CRC;
}

/*********************************************************************
    Name: dci_channel_encode / dci_channel_decode

    Description: Channel encodes / decodes the Downlink Control
                 Information channel

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.3.3
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void dci_channel_encode(LIBLTE_PHY_STRUCT *phy_struct,
                        uint8             *in_bits,
                        uint32             N_in_bits,
                        uint16             rnti,
                        uint8              ue_ant,
                        uint32             N_out_bits,
                        uint8             *out_bits)
{
    // Convert RNTI to bit array
    uint8 x_rnti_bits[16];
    for(uint32 i=0; i<16; i++)
        x_rnti_bits[i] = (rnti >> (15-i)) & 1;

    // Construct UE antenna mask
    uint8 x_as_bits[16];
    memset(x_as_bits, 0, sizeof(uint8)*16);
    if(ue_ant == 1)
        x_as_bits[15] = 1;

    // Calculate p_bits
    uint8 p_bits[16];
    calc_crc(in_bits, N_in_bits, CRC16, p_bits, 16);

    // Mask p_bits
    for(uint32 i=0; i<16; i++)
        p_bits[i] ^= x_rnti_bits[i] ^ x_as_bits[i];

    // Construct c_bits
    for(uint32 i=0; i<N_in_bits; i++)
        phy_struct->dci_c_bits[i] = in_bits[i];
    for(uint32 i=0; i<16; i++)
        phy_struct->dci_c_bits[N_in_bits+i] = p_bits[i];

    // Determine d_bits
    uint32 N_d_bits;
    uint32 g[3] = {0133, 0171, 0165}; // Numbers are in octal
    conv_encode(phy_struct,
                phy_struct->dci_c_bits,
                N_in_bits+16,
                7,
                3,
                g,
                true,
                phy_struct->dci_tx_d_bits,
                &N_d_bits);

    // Determine e_bits
    rate_match_conv(phy_struct, phy_struct->dci_tx_d_bits, N_d_bits, N_out_bits, out_bits);
}
LIBLTE_ERROR_ENUM dci_channel_decode(LIBLTE_PHY_STRUCT *phy_struct,
                                     float             *in_bits,
                                     uint32             N_in_bits,
                                     uint16             rnti_start,
                                     uint16             rnti_range,
                                     uint8              ue_ant,
                                     uint8             *out_bits,
                                     uint32             N_out_bits,
                                     uint16            *rnti_found)
{
    // Construct UE antenna mask
    uint8 x_as_bits[16];
    memset(x_as_bits, 0, sizeof(uint8)*16);
    if(ue_ant == 1)
        x_as_bits[15] = 1;

    // Rate unmatch to get the d_bits
    uint32 N_d_bits;
    rate_unmatch_conv(phy_struct,
                      in_bits,
                      N_in_bits,
                      N_out_bits+16,
                      phy_struct->dci_rx_d_bits,
                      &N_d_bits);

    // Viterbi decode the d_bits to get the c_bits
    uint32 N_c_bits;
    uint32 g[3] = {0133, 0171, 0165}; // Numbers are in octal
    viterbi_decode(phy_struct,
                   phy_struct->dci_rx_d_bits,
                   N_d_bits,
                   7,
                   3,
                   g,
                   phy_struct->dci_c_bits,
                   &N_c_bits);

    // Recover a_bits and p_bits
    uint8 *a_bits = &phy_struct->dci_c_bits[0];
    uint8 *p_bits = &phy_struct->dci_c_bits[N_out_bits];

    // Calculate p_bits
    uint8 calc_p_bits[16];
    calc_crc(a_bits, N_out_bits, CRC16, calc_p_bits, 16);

    uint8 x_rnti_bits[16];
    for(uint32 j=0; j<rnti_range; j++)
    {
        // Convert RNTI to bit array
        uint16 rnti;
        for(uint32 i=0; i<16; i++)
        {
            rnti           = rnti_start + j;
            x_rnti_bits[i] = (rnti >> (15-i)) & 1;
        }

        // Check CRC
        uint32 ber = 0;
        for(uint32 i=0; i<16; i++)
            ber += p_bits[i] ^ (calc_p_bits[i] ^ x_rnti_bits[i] ^ x_as_bits[i]);
        if(ber == 0)
        {
            for(uint32 i=0; i<N_out_bits; i++)
                out_bits[i] = a_bits[i];
            *rnti_found = rnti;
            return LIBLTE_SUCCESS;
        }
    }

    return LIBLTE_ERROR_INVALID_CRC;
}

/*********************************************************************
    Name: dci_0_pack / dci_0_unpack

    Description: Packs / Unpacks all of the fields into / from the
                 Downlink Control Information format 0

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.3.3.1.1
                        3GPP TS 36.213 v10.3.0 section 8.1.1
                        3GPP TS 36.213 v10.3.0 section 8.6

    Notes: Currently only handles non-hopping single-cluster
           assignments
*********************************************************************/
// Defines
#define DCI_0_1A_FLAG_0          0
#define DCI_0_1A_FLAG_1A         1
#define DCI_VRB_TYPE_LOCALIZED   0
#define DCI_VRB_TYPE_DISTRIBUTED 1
// Enums
// Structs
// Functions
void dci_0_pack(LIBLTE_PHY_ALLOCATION_STRUCT    *alloc,
                LIBLTE_PHY_DCI_CA_PRESENCE_ENUM  ca_presence,
                uint32                           N_rb_ul,
                uint8                            N_ant,
                uint8                           *out_bits,
                uint32                          *N_out_bits)
{
    uint8 *dci = out_bits;

    // Carrier indicator
    if(LIBLTE_PHY_DCI_CA_PRESENT == ca_presence)
    {
        printf("WARNING: Not handling carrier indicator\n");
        liblte_value_2_bits(0, &dci, 3);
    }

    // Format 0/1A flag is set to format 0
    liblte_value_2_bits(DCI_0_1A_FLAG_0, &dci, 1);

    // Frequency hopping flag
    liblte_value_2_bits(0, &dci, 1);

    // RBA
    // FIXME: Only supporting non-hopping single-cluster
    uint32 RIV_length = (uint32)ceilf(logf(N_rb_ul*(N_rb_ul+1)/2)/logf(2));
    uint32 RIV        = N_rb_ul*(alloc->N_prb-1) + alloc->prb[0][0];
    if((alloc->N_prb-1) > (N_rb_ul/2))
        RIV = N_rb_ul*(N_rb_ul - alloc->N_prb + 1) + (N_rb_ul - 1 - alloc->prb[0][0]);
    liblte_value_2_bits(RIV, &dci, RIV_length);

    // Modulation and coding scheme and redundancy version
    liblte_value_2_bits(alloc->mcs, &dci, 5);

    // New data indicator
    liblte_value_2_bits(alloc->ndi, &dci, 1);

    // TPC command
    liblte_value_2_bits(alloc->tpc, &dci, 2);

    // Cyclic shift
    liblte_value_2_bits(0, &dci, 3);

    // CSI request
    liblte_value_2_bits(0, &dci, 1);

    // Pad bit
    liblte_value_2_bits(0, &dci, 1);

    // Pad if needed
    uint32 size = dci - out_bits;
    if(size == 12 || size == 14 || size == 16 || size == 20 || size == 24 ||
       size == 26 || size == 32 || size == 40 || size == 44 || size == 56)
    {
        size++;
        liblte_value_2_bits(0, &dci, 1);
    }
    *N_out_bits = size;
}
// FIXME

/*********************************************************************
    Name: dci_1a_pack / dci_1a_unpack

    Description: Packs / Unpacks all of the fields into / from the
                 Downlink Control Information format 1A

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.3.3.1.3
                        3GPP TS 36.213 v10.3.0 section 7.1.6.3
                        3GPP TS 36.213 v10.3.0 section 7.1.7

    Notes: Currently only handles SI-RNTI, P-RNTI, or RA-RNTI and
           localized virtual resource blocks
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void dci_1a_pack(LIBLTE_PHY_ALLOCATION_STRUCT    *alloc,
                 LIBLTE_PHY_DCI_CA_PRESENCE_ENUM  ca_presence,
                 uint32                           N_rb_dl,
                 uint8                            N_ant,
                 uint8                           *out_bits,
                 uint32                          *N_out_bits)
{
    uint8 *dci = out_bits;

    // Carrier indicator
    if(LIBLTE_PHY_DCI_CA_PRESENT == ca_presence)
    {
        printf("WARNING: Not handling carrier indicator\n");
        liblte_value_2_bits(0, &dci, 3);
    }

    // Format 0/1A flag is set to format 1A
    liblte_value_2_bits(DCI_0_1A_FLAG_1A, &dci, 1);

    if(LIBLTE_MAC_SI_RNTI        == alloc->rnti ||
       LIBLTE_MAC_P_RNTI         == alloc->rnti ||
       (LIBLTE_MAC_RA_RNTI_START <= alloc->rnti &&
        LIBLTE_MAC_RA_RNTI_END   >= alloc->rnti))
    {
        // FIXME: Only supporting localized VRBs
        liblte_value_2_bits(DCI_VRB_TYPE_LOCALIZED, &dci, 1);
        uint32 RIV_length = (uint32)ceilf(logf(N_rb_dl*(N_rb_dl+1)/2)/logf(2));
        uint32 RIV        = N_rb_dl*(alloc->N_prb-1) + alloc->prb[0][0];
        if((alloc->N_prb-1) > (N_rb_dl/2))
            RIV = N_rb_dl*(N_rb_dl-alloc->N_prb+1) + (N_rb_dl - 1 - alloc->prb[0][0]);
        liblte_value_2_bits(RIV, &dci, RIV_length);

        // Modulation and coding scheme
        liblte_value_2_bits(alloc->mcs, &dci, 5);

        // HARQ process number, FIXME: FDD only
        liblte_value_2_bits(0, &dci, 3);

        // New data indicator
        liblte_value_2_bits(0, &dci, 1);

        // Redundancy version
        liblte_value_2_bits(alloc->rv_idx, &dci, 2);

        // TPC
        uint32 N_prb_1a = 3;
        liblte_value_2_bits(1, &dci, 2);

        // Calculate the TBS
        alloc->tbs = TBS_71721[alloc->mcs][N_prb_1a-1];
    }else{
        // FIXME: Only supporting localized VRBs
        liblte_value_2_bits(DCI_VRB_TYPE_LOCALIZED, &dci, 1);
        uint32 RIV_length = (uint32)ceilf(logf(N_rb_dl*(N_rb_dl+1)/2)/logf(2));
        uint32 RIV        = N_rb_dl*(alloc->N_prb-1) + alloc->prb[0][0];
        if((alloc->N_prb-1) > (N_rb_dl/2))
            RIV = N_rb_dl*(N_rb_dl - alloc->N_prb + 1) + (N_rb_dl - 1 - alloc->prb[0][0]);
        liblte_value_2_bits(RIV, &dci, RIV_length);

        // Modulation and coding scheme
        liblte_value_2_bits(alloc->mcs, &dci, 5);

        // HARQ process number, FIXME: FDD only
        liblte_value_2_bits(alloc->harq_process, &dci, 3);

        // New data indicator
        liblte_value_2_bits(alloc->ndi, &dci, 1);

        // Redundancy version
        liblte_value_2_bits(alloc->rv_idx, &dci, 2);

        // TPC
        liblte_value_2_bits(alloc->tpc, &dci, 2);

        // Calculate the TBS
        alloc->tbs = TBS_71721[alloc->mcs][alloc->N_prb-1];
    }

    // Pad if needed
    uint32 size = dci - out_bits;
    if(size == 12 || size == 14 || size == 16 || size == 20 || size == 24 ||
       size == 26 || size == 32 || size == 40 || size == 44 || size == 56)
    {
        size++;
        liblte_value_2_bits(0, &dci, 1);
    }
    *N_out_bits = size;
}
LIBLTE_ERROR_ENUM dci_1a_unpack(uint8                           *in_bits,
                                uint32                           N_in_bits,
                                LIBLTE_PHY_DCI_CA_PRESENCE_ENUM  ca_presence,
                                uint16                           rnti,
                                uint32                           N_rb_dl,
                                uint8                            N_ant,
                                LIBLTE_PHY_ALLOCATION_STRUCT    *alloc)
{
    uint8 *dci = in_bits;

    // Carrier indicator
    if(LIBLTE_PHY_DCI_CA_PRESENT == ca_presence)
    {
        liblte_bits_2_value(&dci, 3);
        printf("WARNING: Not handling carrier indicator\n");
    }

    // Check DCI 0/1A flag 3GPP TS 36.212 v10.1.0 section 5.3.3.1.3
    uint32 dci_0_1a_flag = liblte_bits_2_value(&dci, 1);
    if(DCI_0_1A_FLAG_0 == dci_0_1a_flag)
    {
        printf("ERROR: DCI 1A flagged as DCI 0\n");
        return LIBLTE_ERROR_INVALID_CONTENTS;
    }

    if(LIBLTE_MAC_SI_RNTI        == rnti ||
       LIBLTE_MAC_P_RNTI         == rnti ||
       (LIBLTE_MAC_RA_RNTI_START <= rnti &&
        LIBLTE_MAC_RA_RNTI_END   >= rnti))
    {
        // Determine if RIV uses local or distributed VRBs
        uint32 loc_or_dist = liblte_bits_2_value(&dci, 1);

        // Find the RIV that was sent 3GPP TS 36.213 v10.3.0 section 7.1.6.3
        uint32 RIV_length = (uint32)ceilf(logf(N_rb_dl*(N_rb_dl+1)/2)/logf(2));
        uint32 RIV        = liblte_bits_2_value(&dci, RIV_length);
        uint32 quotient   = (RIV/N_rb_dl) + 1;
        uint32 remainder  = RIV % N_rb_dl;
        uint32 RB_start   = 0;
        if(remainder > (N_rb_dl - quotient))
        {
            alloc->N_prb = N_rb_dl - (quotient - 2);
            RB_start     = N_rb_dl - 1 - remainder;
        }else{
            alloc->N_prb = quotient;
            RB_start     = remainder;
        }

        // Extract the rest of the fields
        alloc->mcs          = liblte_bits_2_value(&dci, 5);
        alloc->harq_process = liblte_bits_2_value(&dci, 3);
        liblte_bits_2_value(&dci, 1); // New Data Indicator
        alloc->rv_idx = liblte_bits_2_value(&dci, 2);
        uint32 tpc    = liblte_bits_2_value(&dci, 2);

        // Parse the data
        uint32 N_prb_1a = 3;
        if((tpc % 2) == 0)
            N_prb_1a = 2;
        if(DCI_VRB_TYPE_DISTRIBUTED == loc_or_dist)
        {
            // FIXME: Figure out gapping
            // FIXME: Convert to localized blocks
        }else{
            // Convert allocation into array of prbs
            for(uint32 i=0; i<alloc->N_prb; i++)
            {
                alloc->prb[0][i] = RB_start + i;
                alloc->prb[1][i] = RB_start + i;
            }
        }

        // Fill in the allocation structure 3GPP TS 36.213 v10.3.0 section 7.1.7
        alloc->mod_type       = LIBLTE_PHY_MODULATION_TYPE_QPSK;
        alloc->pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
        if(N_ant == 1)
        {
            alloc->tx_mode = 1;
        }else{
            alloc->tx_mode = 2;
        }
        alloc->N_codewords = 1;
        if(27 < alloc->mcs)
            return LIBLTE_ERROR_INVALID_CONTENTS;
        alloc->tbs  = TBS_71721[alloc->mcs][N_prb_1a-1];
        alloc->rnti = rnti;
    }else{
        // FIXME_TEST
        liblte_bits_2_value(&dci, 1);

        uint32 RIV_length = (uint32)ceilf(logf(N_rb_dl*(N_rb_dl+1)/2)/logf(2));
        uint32 RIV        = liblte_bits_2_value(&dci, RIV_length);
        alloc->N_prb      = RIV/N_rb_dl + 1;
        uint32 RB_start   = RIV % N_rb_dl;

        alloc->mcs          = liblte_bits_2_value(&dci, 5);
        alloc->harq_process = liblte_bits_2_value(&dci, 3);
        alloc->ndi          = liblte_bits_2_value(&dci, 1);
        alloc->rv_idx       = liblte_bits_2_value(&dci, 2);
        liblte_bits_2_value(&dci, 2);
        for(uint32 i=0; i<alloc->N_prb; i++)
        {
            alloc->prb[0][i] = RB_start + i;
            alloc->prb[1][i] = RB_start + i;
        }
        alloc->mod_type       = LIBLTE_PHY_MODULATION_TYPE_QPSK;
        alloc->pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
        alloc->tx_mode        = 1;
        alloc->N_codewords    = 1;
        alloc->tbs            = TBS_71721[alloc->mcs][alloc->N_prb-1];
        alloc->rnti           = rnti;
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: dci_1c_pack / dci_1c_unpack

    Description: Packs / Unpacks all of the fields into / from the
                 Downlink Control Information format 1C

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.3.3.1.4
                        3GPP TS 36.213 v10.3.0 section 7.1.6.3
                        3GPP TS 36.213 v10.3.0 section 7.1.7

    Notes: Currently only handling SI-RNTI, P-RNTI, and RA-RNTI
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
// FIXME
LIBLTE_ERROR_ENUM dci_1c_unpack(uint8                        *in_bits,
                                uint32                        N_in_bits,
                                uint16                        rnti,
                                uint32                        N_rb_dl,
                                uint8                         N_ant,
                                LIBLTE_PHY_ALLOCATION_STRUCT *alloc)
{
    uint8 *dci = in_bits;

    uint32 gap_ind = 0;
    if(N_rb_dl >= 50)
        gap_ind = liblte_bits_2_value(&dci, 1);

    uint32 N_gap;
    if(N_rb_dl <= 10)
    {
        N_gap = (uint32)ceilf(N_rb_dl/2.0);
    }else if(N_rb_dl == 11){
        N_gap = 4;
    }else if(N_rb_dl <= 19){
        N_gap = 8;
    }else if(N_rb_dl <= 26){
        N_gap = 12;
    }else if(N_rb_dl <= 44){
        N_gap = 18;
    }else if(N_rb_dl <= 49){
        N_gap = 27;
    }else if(N_rb_dl <= 63){
        N_gap = (gap_ind == 0) ? 27 : 9;
    }else if(N_rb_dl <= 70){
        N_gap = (gap_ind == 0) ? 32 : 16;
    }else{
        N_gap = (gap_ind == 0) ? 48 : 16;
    }

    uint32 N_vrb_gap1_dl = 2 * (N_rb_dl-N_gap);
    if(N_gap < (N_rb_dl-N_gap))
        N_vrb_gap1_dl = 2 * N_gap;

    uint32 N_vrb_gap2_dl = (N_rb_dl/(2*N_gap)) * 2 * N_gap;

    uint32 N_vrb_dl = N_vrb_gap2_dl;
    if(gap_ind == 0)
        N_vrb_dl = N_vrb_gap1_dl;

    uint32 N_rb_step = 4;
    if(N_rb_dl <= 49)
        N_rb_step = 2;

    uint32 Ntilde_vrb_dl = (gap_ind == 0) ? N_vrb_dl : 2*N_gap;

    if(LIBLTE_MAC_SI_RNTI        == rnti ||
       LIBLTE_MAC_P_RNTI         == rnti ||
       (LIBLTE_MAC_RA_RNTI_START <= rnti &&
        LIBLTE_MAC_RA_RNTI_END   >= rnti))
    {
        uint32 RIV_length = ceilf(logf((N_vrb_gap1_dl/N_rb_step) * ((N_vrb_gap1_dl/N_rb_step)+1) / 2.0)/logf(2));
        uint32 RIV        = liblte_bits_2_value(&dci, RIV_length);
        uint32 RB_start   = 0;
        for(uint32 i=N_rb_step; i<=(N_vrb_dl/N_rb_step)*N_rb_step; i+=N_rb_step) // L_crb running variable N_rb_step to floor(N_vrb_dl/N_rb_step)*N_rb_step
        {
            for(uint32 j=0; j<=((N_vrb_dl/N_rb_step)-1)*N_rb_step; j+=N_rb_step) // RB_start running variable 0 to (floor(N_vrb_dl/N_rb_step)-1)*N_rb_step
            {
                uint32 idash        = i/N_rb_step;
                uint32 jdash        = j/N_rb_step;
                uint32 Ndash_vrb_dl = N_vrb_dl/N_rb_step;

                if((idash-1) <= (Ndash_vrb_dl/2))
                {
                    if(RIV == (Ndash_vrb_dl*(idash-1)+jdash)) // RB_start to RB_start+alloc->N_prb gives n_vrb(i).  These are then mapped to PRBs as below
                    {
                        alloc->N_prb = i;
                        RB_start     = j;
                    }
                }else{
                    if(RIV == (Ndash_vrb_dl*(Ndash_vrb_dl-idash+1)+(Ndash_vrb_dl-1-jdash)))
                    {
                        alloc->N_prb = i;
                        RB_start     = j;
                    }
                }
            }
        }
        // Extract the rest of the fields
        alloc->mcs = liblte_bits_2_value(&dci, 5);

        // Convert allocation into array of PRBs
        // Calculate Resource Block Group size (P)
        uint32 P;
        if(N_rb_dl <= 10)
        {
            P = 1;
        }else if(N_rb_dl <= 26){
            P = 2;
        }else if(N_rb_dl <= 63){
            P = 3;
        }else{
            P = 4;
        }

        uint32 N_row  = ceilf(Ntilde_vrb_dl/(4.0*P)) * P;
        uint32 N_null = 4*N_row - Ntilde_vrb_dl;
        uint32 n_vrb  = RB_start;

        // 3GPP TS 36.211 v10.6.0 section 6.2.3.2
        for(uint32 i=0; i<alloc->N_prb; i++)
        {
            uint32 ntilde_vrb         = n_vrb % Ntilde_vrb_dl;
            uint32 ntildedash_prb     = 2*N_row*(ntilde_vrb % 2) + (ntilde_vrb/2) + Ntilde_vrb_dl*(n_vrb/Ntilde_vrb_dl);
            uint32 ntildedashdash_prb = N_row*(ntilde_vrb % 4) + (ntilde_vrb/4) + Ntilde_vrb_dl*(n_vrb/Ntilde_vrb_dl);
            // even slot
            uint32 ntilde_prb_even;
            if((N_null != 0) && (ntilde_vrb >= (Ntilde_vrb_dl-N_null)) && (ntilde_vrb%2 == 1))
            {
                ntilde_prb_even = ntildedash_prb - N_row;
            }else if((N_null != 0) && (ntilde_vrb >= (Ntilde_vrb_dl-N_null)) && (ntilde_vrb%2 == 0)){
                ntilde_prb_even = ntildedash_prb - N_row + N_null/2;
            }else if((N_null != 0) && (ntilde_vrb < (Ntilde_vrb_dl-N_null)) && (ntilde_vrb%4 >= 2)){
                ntilde_prb_even = ntildedashdash_prb - N_null/2;
            }else{
                ntilde_prb_even = ntildedashdash_prb;
            }
            // odd slot
            uint32 ntilde_prb_odd = (ntilde_prb_even + Ntilde_vrb_dl/2)%Ntilde_vrb_dl + Ntilde_vrb_dl * (n_vrb/Ntilde_vrb_dl);

            // even slot
            uint32 n_prb_even = ntilde_prb_even + N_gap - Ntilde_vrb_dl/2;
            if(ntilde_prb_even < Ntilde_vrb_dl/2)
                n_prb_even = ntilde_prb_even;

            // odd slot
            uint32 n_prb_odd = ntilde_prb_odd + N_gap - Ntilde_vrb_dl/2;
            if(ntilde_prb_odd < Ntilde_vrb_dl/2)
                n_prb_odd = ntilde_prb_odd;

            alloc->prb[0][i] = n_prb_even;
            alloc->prb[1][i] = n_prb_odd;
            n_vrb++;
        }

        // Fill in the allocation structure 3GPP TS 36.213 v10.3.0 section 7.1.7
        alloc->mod_type       = LIBLTE_PHY_MODULATION_TYPE_QPSK;
        alloc->pre_coder_type = LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY;
        if(N_ant == 1)
        {
            alloc->tx_mode = 1;
        }else{
            alloc->tx_mode = 2;
        }
        alloc->N_codewords = 1;
        if(32 > alloc->mcs)
        {
            alloc->tbs = TBS_71723[alloc->mcs];
        }else{
            return LIBLTE_ERROR_INVALID_CONTENTS;
        }
        alloc->rnti = rnti;
    }else{
        printf("ERROR: Not handling DCI 1Cs for C-RNTI\n");
        return LIBLTE_ERROR_INVALID_CONTENTS;
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: get_ulsch_ce

    Description: Resolves channel estimates for the uplink shared
                 channel

    Document Reference: N/A
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void get_ulsch_ce(LIBLTE_PHY_STRUCT *phy_struct,
                  complex           *c_est_0,
                  complex           *c_est_1,
                  uint32             N_prb,
                  uint32             N_subfr,
                  complex           *c_est)
{
    complex *dmrs_0 = phy_struct->pusch_dmrs_0[N_subfr][N_prb];
    complex *dmrs_1 = phy_struct->pusch_dmrs_1[N_subfr][N_prb];

    float  ce_mag[12];
    float  ce_ang[12];
    uint32 M_pusch_sc = N_prb * phy_struct->N_sc_rb_ul;
    for(uint32 i=0; i<M_pusch_sc; i++)
    {
        complex tmp = c_est_0[i] / dmrs_0[i];
        float mag_0 = std::abs(tmp);
        float ang_0 = std::arg(tmp);
        tmp         = c_est_1[i] / dmrs_1[i];
        float mag_1 = std::abs(tmp);
        float ang_1 = std::arg(tmp);

        float frac_mag = (mag_1 - mag_0)/7;
        float frac_ang = (ang_1 - ang_0);
        if(frac_ang >= M_PI) // Wrap angle
        {
            frac_ang -= 2*M_PI;
        }else if(frac_ang <= -M_PI){
            frac_ang += 2*M_PI;
        }
        frac_ang /= 7;

        for(uint32 L=0; L<3; L++)
        {
            ce_mag[L]   = mag_0 - (3-L)*frac_mag;
            ce_ang[L]   = ang_0 - (3-L)*frac_ang;
            ce_mag[3+L] = mag_0 + (1+L)*frac_mag;
            ce_ang[3+L] = ang_0 + (1+L)*frac_ang;
            ce_mag[6+L] = mag_1 - (3-L)*frac_mag;
            ce_ang[6+L] = ang_1 - (3-L)*frac_ang;
            ce_mag[9+L] = mag_1 + (1+L)*frac_mag;
            ce_ang[9+L] = ang_1 + (1+L)*frac_ang;
        }
        for(uint32 L=0; L<12; L++)
            c_est[L*M_pusch_sc + i] = complex_polar(ce_mag[L], ce_ang[L]);
    }
}

/*********************************************************************
    Name: get_ulcch_ce

    Description: Resolves channel estimates for the uplink control
                 channel

    Document Reference: N/A
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
void get_ulcch_ce(LIBLTE_PHY_STRUCT *phy_struct,
                  complex           *c_est_0,
                  complex           *c_est_1,
                  uint32             N_subfr,
                  uint32             N_1_p_pucch,
                  complex           *c_est)
{
    complex *dmrs_0 = phy_struct->pucch_dmrs_0[N_subfr][N_1_p_pucch];
    complex *dmrs_1 = phy_struct->pucch_dmrs_1[N_subfr][N_1_p_pucch];

    float ave_mag_0[LIBLTE_PHY_N_SC_RB_UL];
    float ave_mag_1[LIBLTE_PHY_N_SC_RB_UL];
    for(uint32 i=0; i<LIBLTE_PHY_N_SC_RB_UL; i++)
    {
        ave_mag_0[i] = 0;
        ave_mag_1[i] = 0;
    }

    float tmp_ang_0[LIBLTE_PHY_M_PUCCH_RS][LIBLTE_PHY_N_SC_RB_UL];
    float tmp_ang_1[LIBLTE_PHY_M_PUCCH_RS][LIBLTE_PHY_N_SC_RB_UL];
    for(uint32 i=0; i<LIBLTE_PHY_M_PUCCH_RS; i++)
    {
        for(uint32 j=0; j<LIBLTE_PHY_N_SC_RB_UL; j++)
        {
            uint32 idx       = i*LIBLTE_PHY_N_SC_RB_UL + j;
            complex tmp      = c_est_0[idx] / dmrs_0[idx];
            ave_mag_0[j]    += std::abs(tmp) / LIBLTE_PHY_M_PUCCH_RS;
            tmp_ang_0[i][j]  = std::arg(tmp);
            tmp              = c_est_1[idx] / dmrs_1[idx];
            ave_mag_1[j]    += std::abs(tmp) / LIBLTE_PHY_M_PUCCH_RS;
            tmp_ang_1[i][j]  = std::arg(tmp);
        }
    }

    float ave_ang_0[LIBLTE_PHY_N_SC_RB_UL];
    float ave_ang_1[LIBLTE_PHY_N_SC_RB_UL];
    for(uint32 j=0; j<LIBLTE_PHY_N_SC_RB_UL; j++)
    {
        ave_ang_0[j] = tmp_ang_0[0][j];
        ave_ang_1[j] = tmp_ang_1[0][j];
    }

    for(uint32 i=0; i<4; i++)
    {
        for(uint32 j=0; j<LIBLTE_PHY_N_SC_RB_UL; j++)
        {
            c_est[i*LIBLTE_PHY_N_SC_RB_UL + j]     = complex_polar(ave_mag_0[j], ave_ang_0[j]);
            c_est[(4+i)*LIBLTE_PHY_N_SC_RB_UL + j] = complex_polar(ave_mag_1[j], ave_ang_1[j]);
        }
    }
}

/*********************************************************************
    Name: get_num_bits_in_prb

    Description: Determines the number of bits available in a
                 particular PRB with a particular modulation type

    Document Reference: N/A
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
uint32 get_num_bits_in_prb(uint32                          N_subframe,
                           uint32                          N_ctrl_symbs,
                           uint32                          prb,
                           uint32                          N_rb_dl,
                           uint8                           N_ant,
                           LIBLTE_PHY_MODULATION_TYPE_ENUM mod_type)
{
    // Determine first and last PBCH, PSS, and SSS PRBs
    uint32 first_prb;
    uint32 last_prb;
    bool   partial_prb;
    if(N_rb_dl == 6)
    {
        partial_prb = false;
        first_prb   = 0;
        last_prb    = 5;
    }else if(N_rb_dl == 15){
        partial_prb = true;
        first_prb   = 4;
        last_prb    = 10;
    }else if(N_rb_dl == 25){
        partial_prb = true;
        first_prb   = 9;
        last_prb    = 15;
    }else if(N_rb_dl == 50){
        partial_prb = false;
        first_prb   = 22;
        last_prb    = 27;
    }else if(N_rb_dl == 75){
        partial_prb = true;
        first_prb   = 34;
        last_prb    = 40;
    }else{ // N_rb_dl == 100
        partial_prb = false;
        first_prb   = 47;
        last_prb    = 52;
    }

    uint32 N_REs;
    if(N_ant == 1)
    {
        // Start with raw number of resource elements
        N_REs = (14-4)*12 + 4*10;

        // Remove control symbols
        N_REs -= ((N_ctrl_symbs-1)*12 + 10);

        // Remove PBCH, PSS, and SSS
        if(prb >= first_prb && prb <= last_prb)
        {
            if(true == partial_prb && (prb == first_prb || prb == last_prb))
            {
                if(N_subframe == 0)
                {
                    N_REs -= 5*6 + 5;
                }else if(N_subframe == 5){
                    N_REs -= 2*6;
                }
            }else{
                if(N_subframe == 0)
                {
                    N_REs -= 5*12 + 10;
                }else if(N_subframe == 5){
                    N_REs -= 2*12;
                }
            }
        }
    }else if(N_ant == 2){
        // Start with raw number of resource elements
        N_REs = (14-4)*12 + 4*8;

        // Remove control symbols
        N_REs -= ((N_ctrl_symbs-1)*12 + 8);

        // Remove PBCH, PSS, and SSS
        if(prb >= first_prb && prb <= last_prb)
        {
            if(true == partial_prb && (prb == first_prb || prb == last_prb))
            {
                if(N_subframe == 0)
                {
                    N_REs -= 5*6 + 4;
                }else if(N_subframe == 5){
                    N_REs -= 2*6;
                }
            }else{
                if(N_subframe == 0)
                {
                    N_REs -= 5*12 + 8;
                }else if(N_subframe == 5){
                    N_REs -= 2*12;
                }
            }
        }
    }else{ // N_ant == 4
        // Start with raw number of resource elements
        N_REs = (14-6)*12 + 6*8;

        // Remove control symbols
        if(1 == N_ctrl_symbs)
        {
            N_REs -= 8;
        }else{
            N_REs -= ((N_ctrl_symbs-2)*12 + 2*8);
        }

        // Remove PBCH, PSS, and SSS
        if(prb >= first_prb && prb <= last_prb)
        {
            if(true == partial_prb && (prb == first_prb || prb == last_prb))
            {
                if(N_subframe == 0)
                {
                    N_REs -= 4*6 + 2*4;
                }else if(N_subframe == 5){
                    N_REs -= 2*6;
                }
            }else{
                if(N_subframe == 0)
                {
                    N_REs -= 4*12 + 2*8;
                }else if(N_subframe == 5){
                    N_REs -= 2*12;
                }
            }
        }
    }

    switch(mod_type)
    {
    case LIBLTE_PHY_MODULATION_TYPE_BPSK:
        return N_REs;
    case LIBLTE_PHY_MODULATION_TYPE_QPSK:
        return N_REs*2;
    case LIBLTE_PHY_MODULATION_TYPE_16QAM:
        return N_REs*4;
    case LIBLTE_PHY_MODULATION_TYPE_64QAM:
        return N_REs*6;
    default:
        return 0;
    }
}

/*********************************************************************
    Name: wrap_phase

    Description: Checks the phase difference between two angles and
                 wraps one to make the difference less than 2*pi.

    Document Reference: N/A
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
inline void wrap_phase(float *phase_1,
                       float  phase_2)
{
    while((*phase_1 - phase_2) >= M_PI)
        *phase_1 = *phase_1 - 2*M_PI;
    while((*phase_1 - phase_2) <= -M_PI)
        *phase_1 = *phase_1 + 2*M_PI;
}

/*********************************************************************
    Name: get_mcs_from_I_tbs / get_I_tbs_from_mcs

    Description: Calculates MCS based on Itbs and vice versa

    Document Reference: N/A
*********************************************************************/
// Defines
// Enums
// Structs
// Functions
uint8 get_mcs_from_I_tbs(uint32 I_tbs)
{
    if(9 >= I_tbs)
        return I_tbs;
    if(15 >= I_tbs)
        return I_tbs + 1;
    return I_tbs + 2;
}
uint32 get_I_tbs_from_mcs(uint8 mcs)
{
    if(9 >= mcs)
        return mcs;
    if(16 >= mcs)
        return mcs - 1;
    return mcs - 2;
}

/*******************************************************************************
                              LIBRARY FUNCTIONS
*******************************************************************************/

/*********************************************************************
    Name: liblte_phy_init

    Description: Initializes the LTE Physical Layer library.

    Document Reference: N/A
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_init(LIBLTE_PHY_STRUCT                **phy_struct,
                                  uint32                             samp_rate,
                                  uint16                             N_id_cell,
                                  uint8                              N_ant,
                                  uint32                             N_rb_dl,
                                  uint32                             N_sc_rb_dl,
                                  PHICH_Config::phich_Resource_Enum  phich_res)
{
    LIBLTE_PHY_FS_ENUM fs = LIBLTE_PHY_FS_30_72MHZ;
    if(30720000 == samp_rate)
    {
        fs = LIBLTE_PHY_FS_30_72MHZ;
    }else if(15360000 == samp_rate){
        fs = LIBLTE_PHY_FS_15_36MHZ;
    }else if(7680000 == samp_rate){
        fs = LIBLTE_PHY_FS_7_68MHZ;
    }else if(3840000 == samp_rate){
        fs = LIBLTE_PHY_FS_3_84MHZ;
    }else if(1920000 == samp_rate){
        fs = LIBLTE_PHY_FS_1_92MHZ;
    }else{
        return LIBLTE_ERROR_INVALID_INPUTS;
    }
    float res = 0.0;
    switch(phich_res)
    {
    case PHICH_Config::k_phich_Resource_oneSixth:
        res = 1/6;
        break;
    case PHICH_Config::k_phich_Resource_half:
        res = 0.5;
        break;
    case PHICH_Config::k_phich_Resource_one:
        res = 1.0;
        break;
    case PHICH_Config::k_phich_Resource_two:
        res = 2.0;
        break;
    }
    return liblte_phy_init(phy_struct, fs, N_id_cell, N_ant, N_rb_dl, N_sc_rb_dl, res);
}
LIBLTE_ERROR_ENUM liblte_phy_init(LIBLTE_PHY_STRUCT  **phy_struct,
                                  LIBLTE_PHY_FS_ENUM   fs,
                                  uint16               N_id_cell,
                                  uint8                N_ant,
                                  uint32               N_rb_dl,
                                  uint32               N_sc_rb_dl,
                                  float                phich_res)
{
    if(phy_struct == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    *phy_struct = (LIBLTE_PHY_STRUCT *)malloc(sizeof(LIBLTE_PHY_STRUCT));

    // Generic
    switch(fs)
    {
    case LIBLTE_PHY_FS_30_72MHZ:
        (*phy_struct)->fs                = 30720000;
        (*phy_struct)->N_samps_per_symb  = LIBLTE_PHY_N_SAMPS_PER_SYMB_30_72MHZ;
        (*phy_struct)->N_samps_cp_l_0    = LIBLTE_PHY_N_SAMPS_CP_L_0_30_72MHZ;
        (*phy_struct)->N_samps_cp_l_else = LIBLTE_PHY_N_SAMPS_CP_L_ELSE_30_72MHZ;
        (*phy_struct)->N_samps_per_slot  = LIBLTE_PHY_N_SAMPS_PER_SLOT_30_72MHZ;
        (*phy_struct)->N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_30_72MHZ;
        (*phy_struct)->N_samps_per_frame = LIBLTE_PHY_N_SAMPS_PER_FRAME_30_72MHZ;
        break;
    case LIBLTE_PHY_FS_15_36MHZ:
        (*phy_struct)->fs                = 15360000;
        (*phy_struct)->N_samps_per_symb  = LIBLTE_PHY_N_SAMPS_PER_SYMB_15_36MHZ;
        (*phy_struct)->N_samps_cp_l_0    = LIBLTE_PHY_N_SAMPS_CP_L_0_15_36MHZ;
        (*phy_struct)->N_samps_cp_l_else = LIBLTE_PHY_N_SAMPS_CP_L_ELSE_15_36MHZ;
        (*phy_struct)->N_samps_per_slot  = LIBLTE_PHY_N_SAMPS_PER_SLOT_15_36MHZ;
        (*phy_struct)->N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_15_36MHZ;
        (*phy_struct)->N_samps_per_frame = LIBLTE_PHY_N_SAMPS_PER_FRAME_15_36MHZ;
        break;
    case LIBLTE_PHY_FS_7_68MHZ:
        (*phy_struct)->fs                = 7680000;
        (*phy_struct)->N_samps_per_symb  = LIBLTE_PHY_N_SAMPS_PER_SYMB_7_68MHZ;
        (*phy_struct)->N_samps_cp_l_0    = LIBLTE_PHY_N_SAMPS_CP_L_0_7_68MHZ;
        (*phy_struct)->N_samps_cp_l_else = LIBLTE_PHY_N_SAMPS_CP_L_ELSE_7_68MHZ;
        (*phy_struct)->N_samps_per_slot  = LIBLTE_PHY_N_SAMPS_PER_SLOT_7_68MHZ;
        (*phy_struct)->N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_7_68MHZ;
        (*phy_struct)->N_samps_per_frame = LIBLTE_PHY_N_SAMPS_PER_FRAME_7_68MHZ;
        break;
    case LIBLTE_PHY_FS_3_84MHZ:
        (*phy_struct)->fs                = 3840000;
        (*phy_struct)->N_samps_per_symb  = LIBLTE_PHY_N_SAMPS_PER_SYMB_3_84MHZ;
        (*phy_struct)->N_samps_cp_l_0    = LIBLTE_PHY_N_SAMPS_CP_L_0_3_84MHZ;
        (*phy_struct)->N_samps_cp_l_else = LIBLTE_PHY_N_SAMPS_CP_L_ELSE_3_84MHZ;
        (*phy_struct)->N_samps_per_slot  = LIBLTE_PHY_N_SAMPS_PER_SLOT_3_84MHZ;
        (*phy_struct)->N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_3_84MHZ;
        (*phy_struct)->N_samps_per_frame = LIBLTE_PHY_N_SAMPS_PER_FRAME_3_84MHZ;
        break;
    case LIBLTE_PHY_FS_1_92MHZ:
        (*phy_struct)->fs                = 1920000;
        (*phy_struct)->N_samps_per_symb  = LIBLTE_PHY_N_SAMPS_PER_SYMB_1_92MHZ;
        (*phy_struct)->N_samps_cp_l_0    = LIBLTE_PHY_N_SAMPS_CP_L_0_1_92MHZ;
        (*phy_struct)->N_samps_cp_l_else = LIBLTE_PHY_N_SAMPS_CP_L_ELSE_1_92MHZ;
        (*phy_struct)->N_samps_per_slot  = LIBLTE_PHY_N_SAMPS_PER_SLOT_1_92MHZ;
        (*phy_struct)->N_samps_per_subfr = LIBLTE_PHY_N_SAMPS_PER_SUBFR_1_92MHZ;
        (*phy_struct)->N_samps_per_frame = LIBLTE_PHY_N_SAMPS_PER_FRAME_1_92MHZ;
        break;
    default:
        break;
    }
    (*phy_struct)->N_sc_rb_dl = N_sc_rb_dl;
    (*phy_struct)->N_sc_rb_ul = LIBLTE_PHY_N_SC_RB_UL;
    liblte_phy_update_n_rb_dl((*phy_struct), N_rb_dl);
    (*phy_struct)->N_ant   = N_ant;
    (*phy_struct)->ul_init = false;

    // PHICH
    if(LIBLTE_PHY_N_SC_RB_DL_NORMAL_CP == (*phy_struct)->N_sc_rb_dl)
    {
        (*phy_struct)->N_group_phich = (uint32)ceilf((float)phich_res*((float)(*phy_struct)->N_rb_dl/8.0));
        (*phy_struct)->N_sf_phich    = 4;
    }else{
        (*phy_struct)->N_group_phich = 2*(uint32)ceilf((float)phich_res*((float)(*phy_struct)->N_rb_dl/8.0));
        (*phy_struct)->N_sf_phich    = 2;
    }

    // PDCCH Permutation
    pdcch_permute_pre_calc(*phy_struct,
                           N_ant,
                           phich_res);

    // CRS Storage
    if(LIBLTE_PHY_INIT_N_ID_CELL_UNKNOWN != N_id_cell)
    {
        (*phy_struct)->N_id_cell_crs = N_id_cell;
        for(uint32 i=0; i<20; i++)
        {
            generate_crs(i, 0, N_id_cell, N_sc_rb_dl, (*phy_struct)->crs_storage[i][0]);
            generate_crs(i, 1, N_id_cell, N_sc_rb_dl, (*phy_struct)->crs_storage[i][1]);
            generate_crs(i, 4, N_id_cell, N_sc_rb_dl, (*phy_struct)->crs_storage[i][2]);
        }
    }

    // Samples to symbols
    (*phy_struct)->s2s_in                 = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*(*phy_struct)->N_samps_per_symb*2*20);
    (*phy_struct)->s2s_out                = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*(*phy_struct)->N_samps_per_symb*2*20);
    (*phy_struct)->symbs_to_samps_dl_plan = fftwf_plan_dft_1d((*phy_struct)->N_samps_per_symb,
                                                              (*phy_struct)->s2s_in,
                                                              (*phy_struct)->s2s_out,
                                                              FFTW_BACKWARD,
                                                              FFTW_MEASURE);
    (*phy_struct)->samps_to_symbs_dl_plan = fftwf_plan_dft_1d((*phy_struct)->N_samps_per_symb,
                                                              (*phy_struct)->s2s_in,
                                                              (*phy_struct)->s2s_out,
                                                              FFTW_FORWARD,
                                                              FFTW_MEASURE);
    (*phy_struct)->symbs_to_samps_ul_plan = fftwf_plan_dft_1d((*phy_struct)->N_samps_per_symb*2,
                                                              (*phy_struct)->s2s_in,
                                                              (*phy_struct)->s2s_out,
                                                              FFTW_BACKWARD,
                                                              FFTW_MEASURE);
    (*phy_struct)->samps_to_symbs_ul_plan = fftwf_plan_dft_1d((*phy_struct)->N_samps_per_symb*2,
                                                              (*phy_struct)->s2s_in,
                                                              (*phy_struct)->s2s_out,
                                                              FFTW_FORWARD,
                                                              FFTW_MEASURE);

    return LIBLTE_SUCCESS;
}
LIBLTE_ERROR_ENUM liblte_phy_ul_init(LIBLTE_PHY_STRUCT                  *phy_struct,
                                     uint16                              N_id_cell,
                                     const RadioResourceConfigCommonSIB &rr_cnfg)
{
    return liblte_phy_ul_init(phy_struct,
                              N_id_cell,
                              rr_cnfg.prach_Config_Get().rootSequenceIndex_Value(),
                              rr_cnfg.prach_Config_Get().prach_ConfigInfo_Get().prach_ConfigIndex_Value() >> 4,
                              rr_cnfg.prach_Config_Get().prach_ConfigInfo_Get().zeroCorrelationZoneConfig_Value(),
                              rr_cnfg.prach_Config_Get().prach_ConfigInfo_Get().highSpeedFlag_Value(),
                              rr_cnfg.pusch_ConfigCommon_Get().ul_ReferenceSignalsPUSCH_Get().groupAssignmentPUSCH_Value(),
                              rr_cnfg.pusch_ConfigCommon_Get().ul_ReferenceSignalsPUSCH_Get().groupHoppingEnabled_Value(),
                              rr_cnfg.pusch_ConfigCommon_Get().ul_ReferenceSignalsPUSCH_Get().sequenceHoppingEnabled_Value(),
                              rr_cnfg.pusch_ConfigCommon_Get().ul_ReferenceSignalsPUSCH_Get().cyclicShift_Value(),
                              0,
                              rr_cnfg.pucch_ConfigCommon_Get().nCS_AN_Value(),
                              rr_cnfg.pucch_ConfigCommon_Get().deltaPUCCH_Shift_Value());
}
LIBLTE_ERROR_ENUM liblte_phy_ul_init(LIBLTE_PHY_STRUCT *phy_struct,
                                     uint16             N_id_cell,
                                     uint32             prach_root_seq_idx,
                                     uint32             prach_preamble_format,
                                     uint32             prach_zczc,
                                     bool               prach_hs_flag,
                                     uint8              group_assignment_pusch,
                                     bool               group_hopping_enabled,
                                     bool               sequence_hopping_enabled,
                                     uint8              cyclic_shift,
                                     uint8              cyclic_shift_dci,
                                     uint8              N_cs_an,
                                     uint8              delta_pucch_shift)
{
    if(phy_struct == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // PUSCH
    phy_struct->transform_precoding_in  = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*LIBLTE_PHY_N_RB_UL_MAX*LIBLTE_PHY_N_SC_RB_UL);
    phy_struct->transform_precoding_out = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*LIBLTE_PHY_N_RB_UL_MAX*LIBLTE_PHY_N_SC_RB_UL);
    for(uint32 i=0; i<phy_struct->N_rb_ul; i++)
    {
        if((i % 2) == 0 || (i % 3) == 0 || (i % 5) == 0)
        {
            phy_struct->transform_precoding_plan[i]    = fftwf_plan_dft_1d(i*LIBLTE_PHY_N_SC_RB_UL,
                                                                           phy_struct->transform_precoding_in,
                                                                           phy_struct->transform_precoding_out,
                                                                           FFTW_FORWARD,
                                                                           FFTW_MEASURE);
            phy_struct->transform_pre_decoding_plan[i] = fftwf_plan_dft_1d(i*LIBLTE_PHY_N_SC_RB_UL,
                                                                           phy_struct->transform_precoding_in,
                                                                           phy_struct->transform_precoding_out,
                                                                           FFTW_BACKWARD,
                                                                           FFTW_MEASURE);
        }
    }

    // PUSCH DMRS
    for(uint32 i=0; i<LIBLTE_PHY_N_SUBFR_PER_FRAME; i++)
        for(uint32 j=0; j<LIBLTE_PHY_N_RB_UL_MAX; j++)
            generate_dmrs_pusch(phy_struct,
                                i,
                                N_id_cell,
                                group_assignment_pusch,
                                cyclic_shift,
                                cyclic_shift_dci,
                                j,
                                0,
                                group_hopping_enabled,
                                sequence_hopping_enabled,
                                phy_struct->pusch_dmrs_0[i][j],
                                phy_struct->pusch_dmrs_1[i][j]);

    // PUCCH DMRS
    for(uint32 i=0; i<LIBLTE_PHY_N_SUBFR_PER_FRAME; i++)
        for(uint32 j=0; j<LIBLTE_PHY_N_RB_UL_MAX/2; j++)
            generate_dmrs_pucch(phy_struct,
                                i,
                                N_id_cell,
                                group_assignment_pusch,
                                group_hopping_enabled,
                                sequence_hopping_enabled,
                                N_cs_an,
                                j,
                                delta_pucch_shift+1,
                                phy_struct->N_ant,
                                phy_struct->pucch_dmrs_0[i][j],
                                phy_struct->pucch_dmrs_1[i][j]);

    // PRACH
    prach_preamble_seq_gen(phy_struct,
                           prach_root_seq_idx,
                           prach_preamble_format,
                           prach_zczc,
                           prach_hs_flag);

    switch(prach_preamble_format)
    {
    case 0:
        phy_struct->prach_T_fft      = 24576/(30720000/phy_struct->fs);
        phy_struct->prach_T_seq      = 24576/(30720000/phy_struct->fs);
        phy_struct->prach_T_cp       = 3168/(30720000/phy_struct->fs);
        phy_struct->prach_delta_f_RA = 1250;
        phy_struct->prach_phi        = 7;
        break;
    case 1:
        phy_struct->prach_T_fft      = 24576/(30720000/phy_struct->fs);
        phy_struct->prach_T_seq      = 24576/(30720000/phy_struct->fs);
        phy_struct->prach_T_cp       = 21024/(30720000/phy_struct->fs);
        phy_struct->prach_delta_f_RA = 1250;
        phy_struct->prach_phi        = 7;
        break;
    case 2:
        phy_struct->prach_T_fft      = 24576/(30720000/phy_struct->fs);
        phy_struct->prach_T_seq      = 2*24576/(30720000/phy_struct->fs);
        phy_struct->prach_T_cp       = 6240/(30720000/phy_struct->fs);
        phy_struct->prach_delta_f_RA = 1250;
        phy_struct->prach_phi        = 7;
        break;
    case 3:
        phy_struct->prach_T_fft      = 24576/(30720000/phy_struct->fs);
        phy_struct->prach_T_seq      = 2*24576/(30720000/phy_struct->fs);
        phy_struct->prach_T_cp       = 21024/(30720000/phy_struct->fs);
        phy_struct->prach_delta_f_RA = 1250;
        phy_struct->prach_phi        = 7;
        break;
    case 4:
    default:
        phy_struct->prach_T_fft      = 4096/(30720000/phy_struct->fs);
        phy_struct->prach_T_seq      = 4096/(30720000/phy_struct->fs);
        phy_struct->prach_T_cp       = 448/(30720000/phy_struct->fs);
        phy_struct->prach_delta_f_RA = 7500;
        phy_struct->prach_phi        = 2;
        break;
    }
    phy_struct->prach_dft_in    = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*phy_struct->prach_N_zc);
    phy_struct->prach_dft_out   = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*phy_struct->prach_N_zc);
    phy_struct->prach_fft_in    = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*phy_struct->prach_T_fft);
    phy_struct->prach_fft_out   = (fftwf_complex *)fftwf_malloc(sizeof(fftwf_complex)*phy_struct->prach_T_fft);
    phy_struct->prach_dft_plan  = fftwf_plan_dft_1d(phy_struct->prach_N_zc,
                                                    phy_struct->prach_dft_in,
                                                    phy_struct->prach_dft_out,
                                                    FFTW_FORWARD,
                                                    FFTW_MEASURE);
    phy_struct->prach_ifft_plan = fftwf_plan_dft_1d(phy_struct->prach_T_fft,
                                                    phy_struct->prach_fft_in,
                                                    phy_struct->prach_fft_out,
                                                    FFTW_BACKWARD,
                                                    FFTW_MEASURE);
    phy_struct->prach_fft_plan  = fftwf_plan_dft_1d(phy_struct->prach_T_fft,
                                                    phy_struct->prach_fft_in,
                                                    phy_struct->prach_fft_out,
                                                    FFTW_FORWARD,
                                                    FFTW_MEASURE);
    phy_struct->prach_idft_plan = fftwf_plan_dft_1d(phy_struct->prach_N_zc,
                                                    phy_struct->prach_dft_in,
                                                    phy_struct->prach_dft_out,
                                                    FFTW_BACKWARD,
                                                    FFTW_MEASURE);
    for(uint32 i=0; i<phy_struct->prach_N_x_u; i++)
    {
        for(uint32 j=0; j<phy_struct->prach_N_zc; j++)
        {
            phy_struct->prach_dft_in[j][0] = phy_struct->prach_x_u[i][j].real();
            phy_struct->prach_dft_in[j][1] = phy_struct->prach_x_u[i][j].imag();
        }
        fftwf_execute(phy_struct->prach_dft_plan);
        for(uint32 j=0; j<phy_struct->prach_N_zc; j++)
            phy_struct->prach_x_u_fft[i][j] = complex(phy_struct->prach_dft_out[j][0],
                                                      phy_struct->prach_dft_out[j][1]);
    }

    // Generic
    phy_struct->ul_init = true;

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_cleanup

    Description: Cleans up the LTE Physical Layer library.

    Document Reference: N/A
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_cleanup(LIBLTE_PHY_STRUCT *phy_struct)
{
    if(phy_struct == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Samples to symbols
    fftwf_destroy_plan(phy_struct->samps_to_symbs_dl_plan);
    fftwf_destroy_plan(phy_struct->symbs_to_samps_dl_plan);
    fftwf_destroy_plan(phy_struct->samps_to_symbs_ul_plan);
    fftwf_destroy_plan(phy_struct->symbs_to_samps_ul_plan);
    fftwf_free(phy_struct->s2s_in);
    fftwf_free(phy_struct->s2s_out);

    free(phy_struct);
    return LIBLTE_SUCCESS;
}
LIBLTE_ERROR_ENUM liblte_phy_ul_cleanup(LIBLTE_PHY_STRUCT *phy_struct)
{
    if(phy_struct == NULL || !phy_struct->ul_init)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // PRACH
    fftwf_destroy_plan(phy_struct->prach_idft_plan);
    fftwf_destroy_plan(phy_struct->prach_fft_plan);
    fftwf_destroy_plan(phy_struct->prach_ifft_plan);
    fftwf_destroy_plan(phy_struct->prach_dft_plan);
    fftwf_free(phy_struct->prach_dft_in);
    fftwf_free(phy_struct->prach_dft_out);
    fftwf_free(phy_struct->prach_fft_in);
    fftwf_free(phy_struct->prach_fft_out);

    // PUSCH
    for(uint32 i=0; i<phy_struct->N_rb_ul; i++)
    {
        if((i % 2) == 0 || (i % 3) == 0 || (i % 5) == 0)
        {
            fftwf_destroy_plan(phy_struct->transform_precoding_plan[i]);
            fftwf_destroy_plan(phy_struct->transform_pre_decoding_plan[i]);
        }
    }
    fftwf_free(phy_struct->transform_precoding_in);
    fftwf_free(phy_struct->transform_precoding_out);

    // Generic
    phy_struct->ul_init = false;

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_update_n_rb_dl

    Description: Updates N_rb_dl and all associated variables.

    Document Reference: N/A
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_update_n_rb_dl(LIBLTE_PHY_STRUCT *phy_struct,
                                            uint32             N_rb_dl)
{
    if(phy_struct == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    LIBLTE_ERROR_ENUM err              = LIBLTE_ERROR_INVALID_INPUTS;
    uint32            used_subcarriers = N_rb_dl*phy_struct->N_sc_rb_dl;
    switch(phy_struct->N_samps_per_symb)
    {
    case LIBLTE_PHY_N_SAMPS_PER_SYMB_30_72MHZ:
        phy_struct->FFT_size = LIBLTE_PHY_FFT_SIZE_30_72MHZ;
        err                  = LIBLTE_SUCCESS;
        break;
    case LIBLTE_PHY_N_SAMPS_PER_SYMB_15_36MHZ:
        if(LIBLTE_PHY_N_RB_DL_10MHZ  == N_rb_dl ||
           LIBLTE_PHY_N_RB_DL_5MHZ   == N_rb_dl ||
           LIBLTE_PHY_N_RB_DL_3MHZ   == N_rb_dl ||
           LIBLTE_PHY_N_RB_DL_1_4MHZ == N_rb_dl)
        {
            phy_struct->FFT_size = LIBLTE_PHY_FFT_SIZE_15_36MHZ;
            err                  = LIBLTE_SUCCESS;
        }
        break;
    case LIBLTE_PHY_N_SAMPS_PER_SYMB_7_68MHZ:
        if(LIBLTE_PHY_N_RB_DL_5MHZ   == N_rb_dl ||
           LIBLTE_PHY_N_RB_DL_3MHZ   == N_rb_dl ||
           LIBLTE_PHY_N_RB_DL_1_4MHZ == N_rb_dl)
        {
            phy_struct->FFT_size = LIBLTE_PHY_FFT_SIZE_7_68MHZ;
            err                  = LIBLTE_SUCCESS;
        }
        break;
    case LIBLTE_PHY_N_SAMPS_PER_SYMB_3_84MHZ:
        if(LIBLTE_PHY_N_RB_DL_3MHZ   == N_rb_dl ||
           LIBLTE_PHY_N_RB_DL_1_4MHZ == N_rb_dl)
        {
            phy_struct->FFT_size = LIBLTE_PHY_FFT_SIZE_3_84MHZ;
            err                  = LIBLTE_SUCCESS;
        }
        break;
    case LIBLTE_PHY_N_SAMPS_PER_SYMB_1_92MHZ:
        if(LIBLTE_PHY_N_RB_DL_1_4MHZ == N_rb_dl)
        {
            phy_struct->FFT_size = LIBLTE_PHY_FFT_SIZE_1_92MHZ;
            err                  = LIBLTE_SUCCESS;
        }
        break;
    }

    if(LIBLTE_SUCCESS == err)
    {
        phy_struct->N_rb_dl      = N_rb_dl;
        phy_struct->N_rb_ul      = N_rb_dl;
        phy_struct->FFT_pad_size = (phy_struct->FFT_size - used_subcarriers)/2;
    }

    return err;
}

/*********************************************************************
    Name: liblte_phy_pusch_channel_encode

    Description: Encodes and modulates the Physical Uplink Shared
                 Channel

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.3

    Notes: Only handling normal CP and N_ant=1
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_pusch_channel_encode(LIBLTE_PHY_STRUCT            *phy_struct,
                                                  LIBLTE_PHY_ALLOCATION_STRUCT *alloc,
                                                  uint32                        N_id_cell,
                                                  uint8                         N_ant,
                                                  LIBLTE_PHY_SUBFRAME_STRUCT   *subframe)
{
    if(phy_struct == NULL || alloc == NULL || subframe == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Determine Q_m
    uint32 Q_m = liblte_phy_modulation_type_to_q_m[alloc->mod_type];

    // Encode the PUSCH
    uint32 N_ul_symb = 7; // FIXME: Only handling normal CP
    uint32 N_bits;
    ulsch_channel_encode(phy_struct,
                         alloc->msg[0].msg,
                         alloc->msg[0].N_bits,
                         alloc->tbs,
                         alloc->tx_mode,
                         alloc->N_prb*phy_struct->N_sc_rb_ul*(N_ul_symb-1)*2*Q_m,
                         alloc->N_layers,
                         Q_m,
                         alloc->rv_idx,
                         phy_struct->pusch_encode_bits,
                         &N_bits);
    // FIXME: Only handling 1 codeword
    uint32 c_init = (alloc->rnti << 14) | (0 << 13) | (subframe->num << 9) | N_id_cell;
    generate_prs_c(c_init, N_bits, phy_struct->pusch_c);
    for(uint32 i=0; i<N_bits; i++)
        phy_struct->pusch_scramb_bits[i] = phy_struct->pusch_encode_bits[i] ^ phy_struct->pusch_c[i];
    uint32 M_symb;
    modulation_mapper(phy_struct->pusch_scramb_bits,
                      N_bits,
                      alloc->mod_type,
                      phy_struct->pusch_d,
                      &M_symb);
    uint32 M_layer_symb = 0;
    layer_mapper_ul(phy_struct->pusch_d,
                    M_symb,
                    N_ant,
                    alloc->N_codewords,
                    phy_struct->pusch_x,
                    &M_layer_symb);
    transform_precoding(phy_struct,
                        phy_struct->pusch_x,
                        M_layer_symb,
                        alloc->N_prb,
                        N_ant,
                        alloc->N_codewords,
                        phy_struct->pusch_y);
    uint32 M_ap_symb;
    pre_coder_ul(phy_struct->pusch_y,
                 M_layer_symb,
                 N_ant,
                 alloc->N_layers,
                 phy_struct->pusch_z[0],
                 &M_ap_symb);

    // Map to physical resources
    uint32 M_pusch_sc = alloc->N_prb*phy_struct->N_sc_rb_ul;
    for(uint32 p=0; p<N_ant; p++)
    {
        uint32 idx = 0;
        for(uint32 L=0; L<14; L++)
        {
            if(3 == L)
            {
                // DMRS 0
                for(uint32 j=0; j<M_pusch_sc; j++)
                    subframe->tx_symb[p][L][j] = phy_struct->pusch_dmrs_0[subframe->num][alloc->N_prb][j];
            }else if(10 == L){
                // DMRS 1
                for(uint32 j=0; j<M_pusch_sc; j++)
                    subframe->tx_symb[p][L][j] = phy_struct->pusch_dmrs_1[subframe->num][alloc->N_prb][j];
            }else{
                // PUSCH
                for(uint32 j=0; j<M_pusch_sc; j++)
                    subframe->tx_symb[p][L][j] = phy_struct->pusch_z[p][idx++];
            }
        }
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_pusch_channel_decode

    Description: Demodulates and decodes the Physical Uplink Shared
                 Channel

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.3

    Notes: Only handles normal CP
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_pusch_channel_decode(LIBLTE_PHY_STRUCT            *phy_struct,
                                                  LIBLTE_PHY_SUBFRAME_STRUCT   *subframe,
                                                  LIBLTE_PHY_ALLOCATION_STRUCT *alloc,
                                                  uint32                        N_id_cell,
                                                  uint8                         N_ant,
                                                  uint32                        N_turbo_iterations,
                                                  uint8                        *out_bits,
                                                  uint32                       *N_out_bits)
{
    if(phy_struct == NULL || subframe == NULL || alloc == NULL || out_bits == NULL ||
       N_out_bits == NULL || !phy_struct->ul_init)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // FIXME: Timing

    // Extract resource elements and construct channel estimate
    uint32 z_idx   = 0;
    uint32 c_idx_0 = 0;
    uint32 c_idx_1 = 0;
    for(uint32 L=0; L<14; L++)
    {
        for(uint32 prb_idx=0; prb_idx<alloc->N_prb; prb_idx++)
        {
            uint32 i = alloc->prb[L/7][prb_idx];
            for(uint32 j=0; j<phy_struct->N_sc_rb_ul; j++)
            {
                if(3 == L)
                {
                    phy_struct->pusch_c_est_0[c_idx_0++] = subframe->rx_symb[L][i*phy_struct->N_sc_rb_ul+j];
                }else if(10 == L){
                    phy_struct->pusch_c_est_1[c_idx_1++] = subframe->rx_symb[L][i*phy_struct->N_sc_rb_ul+j];
                }else{
                    phy_struct->pusch_z_est[z_idx++] = subframe->rx_symb[L][i*phy_struct->N_sc_rb_ul+j];
                }
            }
        }
    }
    get_ulsch_ce(phy_struct,
                 phy_struct->pusch_c_est_0,
                 phy_struct->pusch_c_est_1,
                 alloc->N_prb,
                 subframe->num,
                 phy_struct->pusch_c_est);
    uint32 M_layer_symb = 0;
    de_pre_coder_ul(phy_struct->pusch_z_est,
                    phy_struct->pusch_c_est,
                    z_idx,
                    N_ant,
                    alloc->N_layers,
                    phy_struct->pusch_y,
                    &M_layer_symb);
    transform_pre_decoding(phy_struct,
                           phy_struct->pusch_y,
                           M_layer_symb,
                           alloc->N_prb,
                           N_ant,
                           alloc->N_codewords,
                           phy_struct->pusch_x);
    uint32 M_symb = 0;
    layer_demapper_ul(phy_struct->pusch_x,
                      M_layer_symb,
                      N_ant,
                      alloc->N_codewords,
                      phy_struct->pusch_d,
                      &M_symb);
    uint32 N_bits;
    modulation_demapper(phy_struct->pusch_d,
                        M_symb,
                        alloc->mod_type,
                        phy_struct->pusch_soft_bits,
                        &N_bits);
    // FIXME: Only handling 1 codewords
    uint32 c_init = (alloc->rnti << 14) | (0 << 13) | (subframe->num << 9) | N_id_cell;
    generate_prs_c(c_init, N_bits, phy_struct->pusch_c);
    for(uint32 i=0; i<N_bits; i++)
        phy_struct->pusch_descramb_bits[i] = (float)phy_struct->pusch_soft_bits[i]*(1-2*(float)phy_struct->pusch_c[i]);
    uint32 N_ul_symb = 7; // FIXME: Only handling normal CP
    uint32 Q_m       = liblte_phy_modulation_type_to_q_m[alloc->mod_type];
    return ulsch_channel_decode(phy_struct,
                                phy_struct->pusch_descramb_bits,
                                N_bits,
                                alloc->tbs,
                                alloc->tx_mode,
                                alloc->N_prb*phy_struct->N_sc_rb_ul*(N_ul_symb-1)*2*Q_m,
                                alloc->N_layers,
                                Q_m,
                                alloc->rv_idx,
                                N_turbo_iterations,
                                out_bits,
                                N_out_bits);
}

/*********************************************************************
    Name: liblte_phy_pucch_format_1_1a_1b_channel_encode

    Description: Encodes and modulates the Physical Uplink Control
                 Channel for formats 1, 1a, and 1b

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.4.1
                        3GPP TS 36.212 v10.1.0 section 5.2.3

    Notes: Only handling normal CP and N_ant=1
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_pucch_format_1_1a_1b_channel_encode(LIBLTE_PHY_STRUCT            *phy_struct,
                                                                 uint8                        *in_bits,
                                                                 uint32                        N_in_bits,
                                                                 uint8                         N_ant,
                                                                 uint32                        N_1_p_pucch,
                                                                 LIBLTE_PHY_PUCCH_FORMAT_ENUM  format,
                                                                 LIBLTE_PHY_SUBFRAME_STRUCT   *subframe)
{
    if(phy_struct == NULL || in_bits == NULL || subframe == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    complex d;
    float   root_p = sqrt(N_ant);
    if(format == LIBLTE_PHY_PUCCH_FORMAT_1 || format == LIBLTE_PHY_PUCCH_FORMAT_1A)
    {
        d = complex(root_p, 0);
        if(in_bits[0] == 1)
            d = -d;
    }else{
        if(in_bits[0] == 0 && in_bits[1] == 0)
        {
            d = complex(root_p, 0);
        }else if(in_bits[0] == 0 && in_bits[1] == 1){
            d = complex(0, -root_p);
        }else if(in_bits[0] == 1 && in_bits[1] == 0){
            d = complex(0, root_p);
        }else{
            d = complex(-root_p, 0);
        }
    }

    // Calculate s_ns
    complex s_ns[2];
    for(uint32 m_prime=0; m_prime<2; m_prime++)
    {
        s_ns[m_prime] = complex(1, 0);
        if((phy_struct->pucch_n_prime_p[subframe->num][N_1_p_pucch][m_prime] % 2) != 0)
            s_ns[m_prime] = complex_polar(1, M_PI/2);
    }

    // Calculate pucch_z
    for(uint32 m_prime=0; m_prime<2; m_prime++)
    {
        uint32 N_pucch_sf = 4;
        for(uint32 i=0; i<N_pucch_sf; i++)
        {
            uint32 symb_num = i;
            if(1 < symb_num)
                symb_num += 3;
            complex s_w = s_ns[m_prime]*complex(W_5_4_1_2[phy_struct->pucch_n_oc_p[subframe->num][N_1_p_pucch][m_prime]][i], 0);
            for(uint32 j=0; j<LIBLTE_PHY_N_SC_RB_UL; j++)
                phy_struct->pucch_z[0][m_prime*N_pucch_sf*LIBLTE_PHY_N_SC_RB_UL + i*LIBLTE_PHY_N_SC_RB_UL + j] =
                    s_w * phy_struct->pucch_r_u_v_alpha_p[subframe->num][N_1_p_pucch][m_prime][symb_num][j] * d * root_p;
        }
    }

    // Map to physical resources
    for(uint32 p=0; p<N_ant; p++)
    {
        uint32 z_idx = 0;
        for(uint32 L=0; L<14; L++)
        {
            uint32 i = N_1_p_pucch;;
            if(7 <= L)
                i = phy_struct->N_rb_ul - N_1_p_pucch - 1;
            for(uint32 j=0; j<phy_struct->N_sc_rb_ul; j++)
            {
                uint32 idx = i*phy_struct->N_sc_rb_ul + j;
                if(2 == L || 3 == L || 4 == L)
                {
                    subframe->tx_symb[p][L][idx] = phy_struct->pucch_dmrs_0[subframe->num][N_1_p_pucch][idx];
                }else if(9 == L || 10 == L || 11 == L){
                    subframe->tx_symb[p][L][idx] = phy_struct->pucch_dmrs_1[subframe->num][N_1_p_pucch][idx];
                }else{
                    subframe->tx_symb[p][L][idx] = phy_struct->pucch_z[p][z_idx++];
                }
            }
        }
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_pucch_format_1_1a_1b_channel_decode

    Description: Demodulates and decodes the Physical Uplink Control
                 Channel for formats 1, 1a, and 1b

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.4.1
                        3GPP TS 36.212 v10.1.0 section 5.2.3

    Notes: Only handling normal CP and N_ant=1
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_pucch_format_1_1a_1b_channel_decode(LIBLTE_PHY_STRUCT            *phy_struct,
                                                                 LIBLTE_PHY_SUBFRAME_STRUCT   *subframe,
                                                                 LIBLTE_PHY_PUCCH_FORMAT_ENUM  format,
                                                                 uint8                         N_ant,
                                                                 uint32                        N_1_p_pucch,
                                                                 uint8                        *out_bits,
                                                                 uint32                       *N_out_bits)
{
    if(phy_struct == NULL || subframe == NULL || out_bits == NULL || N_out_bits == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    if(format != LIBLTE_PHY_PUCCH_FORMAT_1 && format != LIBLTE_PHY_PUCCH_FORMAT_1A &&
       format != LIBLTE_PHY_PUCCH_FORMAT_1B)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Extract resource elements and construct channel estimate
    uint32 z_idx   = 0;
    uint32 c_idx_0 = 0;
    uint32 c_idx_1 = 0;
    for(uint32 L=0; L<14; L++)
    {
        uint32 i = N_1_p_pucch;
        if(7 <= L)
            i = phy_struct->N_rb_ul - N_1_p_pucch - 1;
        for(uint32 j=0; j<phy_struct->N_sc_rb_ul; j++)
        {
            if(2 == L || 3 == L || 4 == L)
            {
                phy_struct->pucch_c_est_0[c_idx_0++] = subframe->rx_symb[L][i*phy_struct->N_sc_rb_ul+j];
            }else if(9 == L || 10 == L || 11 == L){
                phy_struct->pucch_c_est_1[c_idx_1++] = subframe->rx_symb[L][i*phy_struct->N_sc_rb_ul+j];
            }else{
                phy_struct->pucch_z_est[z_idx++] = subframe->rx_symb[L][i*phy_struct->N_sc_rb_ul+j];
            }
        }
    }

    // Recover z using the channel estimate
    get_ulcch_ce(phy_struct,
                 phy_struct->pucch_c_est_0,
                 phy_struct->pucch_c_est_1,
                 subframe->num,
                 N_1_p_pucch,
                 phy_struct->pucch_c_est);
    uint32 M_layer_symb;
    de_pre_coder_ul(phy_struct->pucch_z_est,
                    phy_struct->pucch_c_est,
                    z_idx,
                    N_ant,
                    1,
                    phy_struct->pucch_z[0],
                    &M_layer_symb);

    // Calculate s_ns
    complex s_ns[2];
    for(uint32 m_prime=0; m_prime<2; m_prime++)
    {
        s_ns[m_prime] = complex(1, 0);
        if((phy_struct->pucch_n_prime_p[subframe->num][N_1_p_pucch][m_prime] % 2) != 0)
            s_ns[m_prime] = complex_polar(1, M_PI/2);
    }

    // Recover the bit that was sent
    complex d = complex(0, 0);
    uint32  idx;
    for(uint32 m_prime=0; m_prime<2; m_prime++)
    {
        uint32 N_pucch_sf = 4;
        for(uint32 i=0; i<N_pucch_sf; i++)
        {
            uint32 symb_num = i;
            if(1 < symb_num)
                symb_num += 3;
            complex s_w = s_ns[m_prime] * complex(W_5_4_1_2[phy_struct->pucch_n_oc_p[subframe->num][N_1_p_pucch][m_prime]][i], 0);
            for(uint32 j=0; j<LIBLTE_PHY_N_SC_RB_UL; j++)
            {
                complex s_w_r  = s_w * phy_struct->pucch_r_u_v_alpha_p[subframe->num][N_1_p_pucch][m_prime][symb_num][j];
                idx            = m_prime*N_pucch_sf*LIBLTE_PHY_N_SC_RB_UL + i*LIBLTE_PHY_N_SC_RB_UL + j;
                d             += phy_struct->pucch_z[0][idx] * std::conj(s_w_r) * complex(1/std::norm(s_w_r));
            }
        }
    }
    d *= complex(sqrt(N_ant)/idx, 0);

    // Quantify the bits that were sent
    if(format == LIBLTE_PHY_PUCCH_FORMAT_1 || format == LIBLTE_PHY_PUCCH_FORMAT_1A)
    {
        float sd;
        if(d.real() < 0)
        {
            sd          = get_soft_decision(d, complex(-1, 0), 1);
            out_bits[0] = 1;
        }else{
            sd          = get_soft_decision(d, complex(1, 0), 1);
            out_bits[0] = 0;
        }
        *N_out_bits = 1;
        if(sd > 0.5)
            return LIBLTE_SUCCESS;
    }else{
        float sd;
        float ang = std::arg(d);
        if((ang >= M_PI/4) && (ang < 3*M_PI/4))
        {
            sd          = get_soft_decision(d, complex(0, 1), 1);
            out_bits[0] = 1;
            out_bits[1] = 0;
        }else if((ang >= -M_PI/4) && (ang < M_PI/4)){
            sd          = get_soft_decision(d, complex(1, 0), 1);
            out_bits[0] = 0;
            out_bits[1] = 0;
        }else if((ang >= -3*M_PI/4) && (ang < -M_PI/4)){
            sd          = get_soft_decision(d, complex(0, -1), 1);
            out_bits[0] = 0;
            out_bits[1] = 1;
        }else{
            sd          = get_soft_decision(d, complex(-1, 0), 1);
            out_bits[0] = 1;
            out_bits[1] = 1;
        }
        *N_out_bits = 2;
        if(sd > 0.5)
            return LIBLTE_SUCCESS;
    }

    return LIBLTE_ERROR_INVALID_INPUTS;
}

/*********************************************************************
    Name: liblte_phy_pucch_format_2_2a_2b_channel_encode

    Description: Encodes and modulates the Physical Uplink Control
                 Channel for formats 2, 2a, and 2b

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.4.2
                        3GPP TS 36.212 v10.1.0 section 5.2.3

    Notes: Only handling normal CP and N_ant=1
*********************************************************************/
// FIXME

/*********************************************************************
    Name: liblte_phy_pucch_format_2_2a_2b_channel_decode

    Description: Demodulates and decodes the Physical Uplink Control
                 Channel for formats 2, 2a, and 2b

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.4.2
                        3GPP TS 36.212 v10.1.0 section 5.2.3

    Notes: Only handling normal CP and N_ant=1
*********************************************************************/
// FIXME

/*********************************************************************
    Name: liblte_phy_pucch_map_sr_config_idx

    Description: Maps SR configuration index to SR periodicity and
                 SR subframe offset

    Document Reference: 3GPP TS 36.213 v10.3.0 table 10.1.5-1
*********************************************************************/
void liblte_phy_pucch_map_sr_config_idx(uint32  i_sr,
                                        uint32 *sr_periodicity,
                                        uint32 *N_offset_sr)
{
    if(i_sr < 5)
    {
        *sr_periodicity = 5;
        *N_offset_sr    = i_sr;
    }else if(i_sr < 15){
        *sr_periodicity = 10;
        *N_offset_sr    = i_sr - 5;
    }else if(i_sr < 35){
        *sr_periodicity = 20;
        *N_offset_sr    = i_sr - 15;
    }else if(i_sr < 75){
        *sr_periodicity = 40;
        *N_offset_sr    = i_sr - 35;
    }else if(i_sr < 155){
        *sr_periodicity = 80;
        *N_offset_sr    = i_sr - 75;
    }else if(i_sr < 157){
        *sr_periodicity = 2;
        *N_offset_sr    = i_sr - 155;
    }else{
        *sr_periodicity = 1;
        *N_offset_sr    = i_sr - 157;
    }
}

/*********************************************************************
    Name: liblte_phy_generate_prach

    Description: Generates the baseband signal for a PRACH

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.7.3
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_generate_prach(LIBLTE_PHY_STRUCT *phy_struct,
                                            uint32             preamble_idx,
                                            uint32             freq_offset,
                                            complex           *samps)
{
    if(phy_struct == NULL || samps == NULL || !phy_struct->ul_init)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Calculate PRACH parameters
    uint32 N_ra_prb = freq_offset;
    uint32 k_0      = N_ra_prb*phy_struct->N_sc_rb_ul - phy_struct->N_rb_ul*phy_struct->N_sc_rb_ul/2 + (phy_struct->FFT_size/2);
    uint32 K        = 15000/phy_struct->prach_delta_f_RA;

    for(uint32 i=0; i<phy_struct->prach_N_zc; i++)
    {
        phy_struct->prach_dft_in[i][0] = phy_struct->prach_x_u_v[preamble_idx][i].real();
        phy_struct->prach_dft_in[i][1] = phy_struct->prach_x_u_v[preamble_idx][i].imag();
    }
    fftwf_execute(phy_struct->prach_dft_plan);
    for(uint32 i=0; i<phy_struct->prach_T_fft; i++)
    {
        phy_struct->prach_fft_in[i][0] = 0;
        phy_struct->prach_fft_in[i][1] = 0;
    }
    uint32 start = phy_struct->prach_phi + (K*k_0) + (K/2);
    for(uint32 i=0; i<phy_struct->prach_N_zc; i++)
    {
        uint32 idx                       = (i+start+phy_struct->prach_T_fft/2)%phy_struct->prach_T_fft;
        phy_struct->prach_fft_in[idx][0] = phy_struct->prach_dft_out[(i+phy_struct->prach_N_zc/2)%phy_struct->prach_N_zc][0];
        phy_struct->prach_fft_in[idx][1] = phy_struct->prach_dft_out[(i+phy_struct->prach_N_zc/2)%phy_struct->prach_N_zc][1];
    }
    fftwf_execute(phy_struct->prach_ifft_plan);
    if(phy_struct->prach_T_fft == phy_struct->prach_T_seq)
    {
        for(uint32 i=0; i<phy_struct->prach_T_fft; i++)
            samps[phy_struct->prach_T_cp+i] = complex(phy_struct->prach_fft_out[i][0],
                                                      phy_struct->prach_fft_out[i][1]);
    }else{
        for(uint32 i=0; i<phy_struct->prach_T_fft; i++)
        {
            samps[phy_struct->prach_T_cp+i]                         = complex(phy_struct->prach_fft_out[i][0],
                                                                              phy_struct->prach_fft_out[i][1]);
            samps[phy_struct->prach_T_cp+phy_struct->prach_T_fft+i] = complex(phy_struct->prach_fft_out[i][0],
                                                                              phy_struct->prach_fft_out[i][1]);
        }
    }
    for(uint32 i=0; i<phy_struct->prach_T_cp; i++)
        samps[i] = samps[phy_struct->prach_T_seq+i];

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_detect_prach

    Description: Detects PRACHs from baseband I/Q

    Document Reference: 3GPP TS 36.211 v10.1.0 section 5.7.2 and 5.7.3

    Notes: Currently only supports detection of one preamble
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_detect_prach(LIBLTE_PHY_STRUCT *phy_struct,
                                          complex           *samps,
                                          uint32             freq_offset,
                                          uint32            *N_det_pre,
                                          uint32            *det_pre,
                                          uint32            *det_ta)
{
    if(phy_struct == NULL || samps == NULL || N_det_pre == NULL || det_pre == NULL ||
       det_ta == NULL || !phy_struct->ul_init)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Determine u
    uint32 u = PRACH_5_7_2_4[phy_struct->prach_root_seq_idx];
    if(4 == phy_struct->prach_preamble_format)
        u = PRACH_5_7_2_5[phy_struct->prach_root_seq_idx];

    // Determine N_cs
    uint32 N_cs;
    if(4 == phy_struct->prach_preamble_format)
    {
        N_cs = PRACH_5_7_2_3[phy_struct->prach_zczc];
    }else if(phy_struct->prach_hs_flag){
        N_cs = PRACH_5_7_2_2_RS[phy_struct->prach_zczc];
    }else{
        N_cs = PRACH_5_7_2_2_URS[phy_struct->prach_zczc];
    }

    // Determine v_max
    uint32 v_max;
    if(phy_struct->prach_hs_flag)
    {
        // Determine d_u
        uint32 p;
        for(p=1; p<=phy_struct->prach_N_zc; p++)
            if(((p*u) % phy_struct->prach_N_zc) == 1)
                break;
        uint32 d_u = phy_struct->prach_N_zc - p;
        if(p >= 0 && p < phy_struct->prach_N_zc/2)
            d_u = p;

        // Determine N_RA_shift, d_start, N_RA_group, and N_neg_RA_shift
        uint32 N_RA_shift;
        uint32 d_start;
        uint32 N_RA_group;
        int32  N_neg_RA_shift;
        if(d_u >= N_cs && d_u < phy_struct->prach_N_zc/3)
        {
            N_RA_shift     = d_u/N_cs;
            d_start        = 2*d_u + N_RA_shift*N_cs;
            N_RA_group     = phy_struct->prach_N_zc/d_start;
            N_neg_RA_shift = (phy_struct->prach_N_zc - 2*d_u - N_RA_group*d_start)/N_cs;
            if(N_neg_RA_shift < 0)
                N_neg_RA_shift = 0;
        }else{
            N_RA_shift     = (phy_struct->prach_N_zc - 2*d_u)/N_cs;
            d_start        = phy_struct->prach_N_zc - 2*d_u + N_RA_shift*N_cs;
            N_RA_group     = d_u/d_start;
            N_neg_RA_shift = (d_u - N_RA_group*d_start)/N_cs;
            if(N_neg_RA_shift < 0)
                N_neg_RA_shift = 0;
            if(N_neg_RA_shift > (int32)N_RA_shift)
                N_neg_RA_shift = N_RA_shift;
        }

        // Restricted set
        v_max = N_RA_shift*N_RA_group + N_neg_RA_shift - 1;
    }else{
        // Unrestricted set
        if(0 == N_cs)
        {
            v_max = 0;
        }else{
            v_max = (phy_struct->prach_N_zc/N_cs)-1;
        }
    }

    // Calculate PRACH parameters
    uint32 N_ra_prb = freq_offset;
    uint32 k_0      = N_ra_prb*phy_struct->N_sc_rb_ul - phy_struct->N_rb_ul*phy_struct->N_sc_rb_ul/2 + (phy_struct->FFT_size/2);
    uint32 K        = 15000/phy_struct->prach_delta_f_RA;
    for(uint32 i=0; i<phy_struct->prach_T_fft; i++)
    {
        phy_struct->prach_fft_in[i][0] = samps[phy_struct->prach_T_cp+i].real();
        phy_struct->prach_fft_in[i][1] = samps[phy_struct->prach_T_cp+i].imag();
    }
    fftwf_execute(phy_struct->prach_fft_plan);
    uint32 start = phy_struct->prach_phi + (K*k_0) + (K/2);
    for(uint32 i=0; i<phy_struct->prach_N_zc; i++)
    {
        uint32 idx                 = (i+start+phy_struct->prach_T_fft/2)%phy_struct->prach_T_fft;
        phy_struct->prach_x_hat[i] = complex(phy_struct->prach_fft_out[idx][0],
                                             phy_struct->prach_fft_out[idx][1]);
    }

    // Correlate with all available roots
    float  ave_val    = 0;
    float  max_val    = 0;
    uint32 max_root   = 0;
    uint32 max_offset = 0;
    for(uint32 i=0; i<phy_struct->prach_N_x_u; i++)
    {
        for(uint32 j=0; j<phy_struct->prach_N_zc; j++)
        {
            complex tmp = phy_struct->prach_x_u_fft[i][j] * std::conj(phy_struct->prach_x_hat[j]);
            phy_struct->prach_dft_in[j][0] = tmp.real();
            phy_struct->prach_dft_in[j][1] = tmp.imag();
        }
        fftwf_execute(phy_struct->prach_idft_plan);
        for(uint32 j=0; j<phy_struct->prach_N_zc; j++)
        {
            float abs_corr = std::norm(complex(phy_struct->prach_dft_out[j][0],
                                               phy_struct->prach_dft_out[j][1]));
            ave_val += abs_corr;
            if(abs_corr > max_val)
            {
                max_val    = abs_corr;
                max_root   = i;
                max_offset = j;
            }
        }
        ave_val /= phy_struct->prach_N_zc;
    }

    if(max_val >= 50*ave_val &&
       max_val != 0)
    {
        *N_det_pre = 1;
        if(0 == N_cs)
        {
            *det_pre = max_root*(v_max+1);
            *det_ta  = ((max_offset%phy_struct->prach_N_zc)*29.155/16)-1;
        }else{
            *det_pre = max_root*(v_max+1) + ((max_offset+N_cs)%phy_struct->prach_N_zc)/N_cs;
            *det_ta  = (((N_cs - ((max_offset+N_cs)%phy_struct->prach_N_zc))%N_cs)*29.155/16)-1;
        }
    }else{
        *N_det_pre = 0;
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_pdsch_channel_encode

    Description: Encodes and modulates the Physical Downlink Shared
                 Channel

    Document Reference: 3GPP TS 36.211 v10.1.0 sections 6.3 and 6.4
*********************************************************************/
bool is_this_RE_for_PDSCH(uint8 N_ant,
                          uint32 L,
                          uint32 N_id_cell,
                          uint32 sc,
                          uint32 N_rb_dl,
                          uint32 N_sc_rb_dl,
                          uint32 subfr_num,
                          uint32 prb)
{
    if(N_ant == 1 && (L % 7) == 0 && (N_id_cell % 6) == (sc % 6))
        // Skip CRS
        return false;
    if(N_ant == 1 && (L % 7) == 4 && ((N_id_cell+3) % 6) == (sc % 6))
        // Skip CRS
        return false;
    if((N_ant == 2 || N_ant == 4) && ((L % 7) == 0 || (L % 7) == 4) && (N_id_cell % 3) == (sc % 3))
        // Skip CRS
        return false;
    if(N_ant == 4 && (L % 7) == 1 && (N_id_cell % 3) == (sc % 3))
        // Skip CRS
        return false;
    uint32 first_sc;
    uint32 last_sc;
    if(N_rb_dl == 6)
    {
        first_sc = 0;
        last_sc  = (6*N_sc_rb_dl)-1;
    }else if(N_rb_dl == 15){
        first_sc = (4*N_sc_rb_dl)+6;
        last_sc  = (11*N_sc_rb_dl)-7;
    }else if(N_rb_dl == 25){
        first_sc = (9*N_sc_rb_dl)+6;
        last_sc  = (16*N_sc_rb_dl)-7;
    }else if(N_rb_dl == 50){
        first_sc = 22*N_sc_rb_dl;
        last_sc  = (28*N_sc_rb_dl)-1;
    }else if(N_rb_dl == 75){
        first_sc = (34*N_sc_rb_dl)+6;
        last_sc  = (41*N_sc_rb_dl)-7;
    }else{ // N_rb_dl == 100
        first_sc = 47*N_sc_rb_dl;
        last_sc  = (53*N_sc_rb_dl)-1;
    }
    if(subfr_num == 0 && (prb*N_sc_rb_dl + sc) >= first_sc && (prb*N_sc_rb_dl + sc) <= last_sc && L >= 7 && L <= 10)
        // Skip PBCH
        return false;
    if((subfr_num == 0 || subfr_num == 5) && (prb*N_sc_rb_dl + sc) >= first_sc && (prb*N_sc_rb_dl + sc) <= last_sc && L == 6)
        // Skip PSS
        return false;
    if((subfr_num == 0 || subfr_num == 5) && (prb*N_sc_rb_dl + sc) >= first_sc && (prb*N_sc_rb_dl + sc) <= last_sc && L == 5)
        // Skip SSS
        return false;
    return true;
}
LIBLTE_ERROR_ENUM liblte_phy_pdsch_channel_encode(LIBLTE_PHY_STRUCT          *phy_struct,
                                                  LIBLTE_PHY_PDCCH_STRUCT    *pdcch,
                                                  uint32                      N_id_cell,
                                                  uint8                       N_ant,
                                                  LIBLTE_PHY_SUBFRAME_STRUCT *subframe)
{
    if(phy_struct == NULL || pdcch == NULL || subframe == NULL || N_id_cell > 503)
        return LIBLTE_ERROR_INVALID_INPUTS;

    for(uint32 alloc_idx=0; alloc_idx<pdcch->N_dl_alloc; alloc_idx++)
    {
        if(pdcch->dl_alloc[alloc_idx].chan_type != LIBLTE_PHY_CHAN_TYPE_DLSCH)
            continue;

        // Determine the number of bits available for transmission
        uint32 N_bits_tot = 0;
        for(uint32 i=0; i<pdcch->dl_alloc[alloc_idx].N_prb; i++)
            N_bits_tot += get_num_bits_in_prb(subframe->num,
                                              pdcch->N_symbs,
                                              pdcch->dl_alloc[alloc_idx].prb[0][i],
                                              phy_struct->N_rb_dl,
                                              N_ant,
                                              pdcch->dl_alloc[alloc_idx].mod_type);
        // Determine Q_m
        uint32 Q_m = liblte_phy_modulation_type_to_q_m[pdcch->dl_alloc[alloc_idx].mod_type];
        uint32 N_bits;
        uint32 scramb_bits_idx = 0;
        for(uint32 i=0; i<pdcch->dl_alloc[alloc_idx].N_codewords; i++)
        {
            // Encode the PDSCH
            dlsch_channel_encode(phy_struct,
                                 pdcch->dl_alloc[alloc_idx].msg[i].msg,
                                 pdcch->dl_alloc[alloc_idx].msg[i].N_bits,
                                 pdcch->dl_alloc[alloc_idx].tbs,
                                 pdcch->dl_alloc[alloc_idx].tx_mode,
                                 pdcch->dl_alloc[alloc_idx].rv_idx,
                                 N_bits_tot,
                                 2,
                                 Q_m,
                                 8,
                                 250368,
                                 phy_struct->pdsch_encode_bits,
                                 &N_bits);
            uint32 c_init = (pdcch->dl_alloc[alloc_idx].rnti << 14) | (i << 13) | (subframe->num << 9) | N_id_cell;
            generate_prs_c(c_init, N_bits, phy_struct->pdsch_c);
            for(uint32 j=0; j<N_bits; j++)
                phy_struct->pdsch_scramb_bits[scramb_bits_idx++] = phy_struct->pdsch_encode_bits[j] ^ phy_struct->pdsch_c[j];
        }
        uint32 M_symb;
        modulation_mapper(phy_struct->pdsch_scramb_bits,
                          N_bits,
                          pdcch->dl_alloc[alloc_idx].mod_type,
                          phy_struct->pdsch_d,
                          &M_symb);
        uint32 M_layer_symb = 0;
        layer_mapper_dl(phy_struct->pdsch_d,
                        M_symb,
                        N_ant,
                        pdcch->dl_alloc[alloc_idx].N_codewords,
                        pdcch->dl_alloc[alloc_idx].pre_coder_type,
                        phy_struct->pdsch_x,
                        &M_layer_symb);
        uint32 M_ap_symb;
        pre_coder_dl(phy_struct->pdsch_x,
                     M_layer_symb,
                     N_ant,
                     pdcch->dl_alloc[alloc_idx].pre_coder_type,
                     phy_struct->pdsch_y[0],
                     5000,
                     &M_ap_symb);

        // Map the symbols to resource elements 3GPP TS 36.211 v10.1.0 section 6.3.5
        for(uint32 p=0; p<N_ant; p++)
        {
            uint32 idx = 0;
            for(uint32 L=pdcch->N_symbs; L<14; L++)
            {
                for(uint32 prb_idx=0; prb_idx<pdcch->dl_alloc[alloc_idx].N_prb; prb_idx++)
                {
                    uint32 i = pdcch->dl_alloc[alloc_idx].prb[L/7][prb_idx];
                    for(uint32 j=0; j<phy_struct->N_sc_rb_dl; j++)
                    {
                        if(is_this_RE_for_PDSCH(N_ant, L, N_id_cell, j, phy_struct->N_rb_dl,
                                                phy_struct->N_sc_rb_dl, subframe->num, i))
                            subframe->tx_symb[p][L][i*phy_struct->N_sc_rb_dl+j] = phy_struct->pdsch_y[p][idx++];
                    }
                }
            }
        }
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_pdsch_channel_decode

    Description: Demodulates and decodes the Physical Downlink Shared
                 Channel

    Document Reference: 3GPP TS 36.211 v10.1.0 sections 6.3 and 6.4
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_pdsch_channel_decode(LIBLTE_PHY_STRUCT            *phy_struct,
                                                  LIBLTE_PHY_SUBFRAME_STRUCT   *subframe,
                                                  LIBLTE_PHY_ALLOCATION_STRUCT *alloc,
                                                  uint32                        N_pdcch_symbs,
                                                  uint32                        N_id_cell,
                                                  uint8                         N_ant,
                                                  uint32                        N_turbo_iterations,
                                                  uint8                        *out_bits,
                                                  uint32                       *N_out_bits)
{
    if(phy_struct == NULL || subframe == NULL || alloc == NULL || N_id_cell > 503 ||
       out_bits == NULL || N_out_bits == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Extract resource elements and channel estimate 3GPP TS 36.211 v10.1.0 section 6.3.5
    uint32 idx = 0;
    for(uint32 L=N_pdcch_symbs; L<14; L++)
    {
        for(uint32 prb_idx=0; prb_idx<alloc->N_prb; prb_idx++)
        {
            uint32 i = alloc->prb[L/7][prb_idx];
            for(uint32 j=0; j<phy_struct->N_sc_rb_dl; j++)
            {
                if(!is_this_RE_for_PDSCH(N_ant, L, N_id_cell, j, phy_struct->N_rb_dl,
                                         phy_struct->N_sc_rb_dl, subframe->num, i))
                    continue;
                phy_struct->pdsch_y_est[idx] = subframe->rx_symb[L][i*phy_struct->N_sc_rb_dl+j];
                for(uint32 p=0; p<N_ant; p++)
                    phy_struct->pdsch_c_est[p][idx] = subframe->rx_ce[p][L][i*phy_struct->N_sc_rb_dl+j];
                idx++;
            }
        }
    }
    uint32 M_layer_symb;
    de_pre_coder_dl(phy_struct->pdsch_y_est,
                    phy_struct->pdsch_c_est[0],
                    5000,
                    idx,
                    N_ant,
                    alloc->pre_coder_type,
                    phy_struct->pdsch_x,
                    &M_layer_symb);
    uint32 M_symb;
    layer_demapper_dl(phy_struct->pdsch_x,
                      M_layer_symb,
                      N_ant,
                      alloc->N_codewords,
                      alloc->pre_coder_type,
                      phy_struct->pdsch_d,
                      &M_symb);
    uint32 N_bits;
    modulation_demapper(phy_struct->pdsch_d,
                        M_symb,
                        alloc->mod_type,
                        phy_struct->pdsch_soft_bits,
                        &N_bits);
    // FIXME: Only handling 1 codeword
    uint32 c_init = (alloc->rnti << 14) | (0 << 13) | (subframe->num << 9) | N_id_cell;
    generate_prs_c(c_init, N_bits, phy_struct->pdsch_c);
    for(uint32 i=0; i<N_bits; i++)
        phy_struct->pdsch_descramb_bits[i] = (float)phy_struct->pdsch_soft_bits[i]*(1-2*(float)phy_struct->pdsch_c[i]);
    uint32 Q_m        = liblte_phy_modulation_type_to_q_m[alloc->mod_type];
    uint32 N_bits_tot = 0;
    for(uint32 i=0; i<alloc->N_prb; i++)
        N_bits_tot += get_num_bits_in_prb(subframe->num,
                                          N_pdcch_symbs,
                                          alloc->prb[0][i],
                                          phy_struct->N_rb_dl,
                                          N_ant,
                                          alloc->mod_type);
    return dlsch_channel_decode(phy_struct,
                                phy_struct->pdsch_descramb_bits,
                                N_bits,
                                alloc->tbs,
                                alloc->tx_mode,
                                alloc->rv_idx,
                                N_bits_tot,
                                2,
                                Q_m,
                                8,
                                250368, // FIXME: Using N_soft from a cat 1 UE (3GPP TS 36.306)
                                N_turbo_iterations,
                                out_bits,
                                N_out_bits);
}

/*********************************************************************
    Name: liblte_phy_bch_channel_encode

    Description: Encodes and modulates the Physical Broadcast
                 Channel

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.6
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_bch_channel_encode(LIBLTE_PHY_STRUCT          *phy_struct,
                                                uint8                      *in_bits,
                                                uint32                      N_in_bits,
                                                uint32                      N_id_cell,
                                                uint8                       N_ant,
                                                LIBLTE_PHY_SUBFRAME_STRUCT *subframe,
                                                uint32                      sfn)
{
    if(phy_struct == NULL || in_bits == NULL || N_id_cell > 503 || subframe == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Encode the bits to symbols
    if(0 == phy_struct->bch_N_bits)
    {
        bch_channel_encode(phy_struct,
                           in_bits,
                           N_in_bits,
                           N_ant,
                           phy_struct->bch_encode_bits,
                           &phy_struct->bch_N_bits);
        generate_prs_c(N_id_cell, phy_struct->bch_N_bits, phy_struct->bch_c);
    }
    for(uint32 i=0; i<480; i++)
    {
        uint32 offset                  = (sfn % 4)*480;
        phy_struct->bch_scramb_bits[i] = phy_struct->bch_encode_bits[offset+i] ^ phy_struct->bch_c[offset + i];
    }
    if(3 == (sfn % 4))
        phy_struct->bch_N_bits = 0;
    uint32 M_symb;
    modulation_mapper(phy_struct->bch_scramb_bits,
                      480,
                      LIBLTE_PHY_MODULATION_TYPE_QPSK,
                      phy_struct->bch_d,
                      &M_symb);
    uint32 M_layer_symb;
    layer_mapper_dl(phy_struct->bch_d,
                    M_symb,
                    N_ant,
                    1,
                    LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                    phy_struct->bch_x,
                    &M_layer_symb);
    uint32 M_ap_symb;
    pre_coder_dl(phy_struct->bch_x,
                 M_layer_symb,
                 N_ant,
                 LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                 phy_struct->bch_y[0],
                 240,
                 &M_ap_symb);

    // Map the symbols to resource elements
    for(uint32 p=0; p<N_ant; p++)
    {
        uint32 idx = 0;
        for(uint32 i=0; i<72; i++)
        {
            uint32 k = (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl)/2 - 36 + i;
            if((N_id_cell % 3) != (k % 3))
            {
                subframe->tx_symb[p][7][k] = phy_struct->bch_y[p][idx];
                subframe->tx_symb[p][8][k] = phy_struct->bch_y[p][idx+48];
                idx++;
            }
            subframe->tx_symb[p][9][k]  = phy_struct->bch_y[p][i+96];
            subframe->tx_symb[p][10][k] = phy_struct->bch_y[p][i+168];
        }
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_bch_channel_decode

    Description: Demodulates and decodes the Physical Broadcast
                 Channel

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.6
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_bch_channel_decode(LIBLTE_PHY_STRUCT          *phy_struct,
                                                LIBLTE_PHY_SUBFRAME_STRUCT *subframe,
                                                uint32                      N_id_cell,
                                                uint8                      *N_ant,
                                                uint8                      *out_bits,
                                                uint32                     *N_out_bits,
                                                uint8                      *offset)
{
    if(phy_struct == NULL || subframe == NULL || N_id_cell > 503 || N_ant == NULL ||
       out_bits == NULL || N_out_bits == NULL || offset == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Unmap PBCH and channel estimates from resource elements
    uint32 idx = 0;
    for(uint32 i=0; i<72; i++)
    {
        uint32 in_idx = phy_struct->N_sc_rb_dl*phy_struct->N_rb_dl/2 - 36 + i;
        if((N_id_cell % 3) != (in_idx % 3))
        {
            phy_struct->bch_y_est[idx]    = subframe->rx_symb[7][in_idx];
            phy_struct->bch_y_est[idx+48] = subframe->rx_symb[8][in_idx];
            for(uint32 p=0; p<4; p++)
            {
                phy_struct->bch_c_est[p][idx]    = subframe->rx_ce[p][7][in_idx];
                phy_struct->bch_c_est[p][idx+48] = subframe->rx_ce[p][8][in_idx];
            }
            idx++;
        }
        phy_struct->bch_y_est[i+96]  = subframe->rx_symb[9][in_idx];
        phy_struct->bch_y_est[i+168] = subframe->rx_symb[10][in_idx];
        for(uint32 p=0; p<4; p++)
        {
            phy_struct->bch_c_est[p][i+96]  = subframe->rx_ce[p][9][in_idx];
            phy_struct->bch_c_est[p][i+168] = subframe->rx_ce[p][10][in_idx];
        }
    }

    // Generate the scrambling sequence
    generate_prs_c(N_id_cell, 1920, phy_struct->bch_c);

    // Try decoding with 1, 2, and 4 antenna configs,
    // and for each antenna config, try decoding with 0 to 3 offset
    *N_ant = 0;
    for(uint32 p=1; p<5; p++)
    {
        if(p == 3)
            continue;

        uint32 M_layer_symb;
        de_pre_coder_dl(phy_struct->bch_y_est,
                        phy_struct->bch_c_est[0],
                        240,
                        240,
                        p,
                        LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                        phy_struct->bch_x,
                        &M_layer_symb);
        uint32 M_symb;
        layer_demapper_dl(phy_struct->bch_x,
                          M_layer_symb,
                          p,
                          1,
                          LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                          phy_struct->bch_d,
                          &M_symb);
        uint32 N_bits;
        modulation_demapper(phy_struct->bch_d,
                            M_symb,
                            LIBLTE_PHY_MODULATION_TYPE_QPSK,
                            phy_struct->bch_soft_bits,
                            &N_bits);

        // Try decoding at each offset
        for(uint32 i=0; i<4; i++)
        {
            for(uint32 j=0; j<1920; j++)
                phy_struct->bch_descramb_bits[j] = RX_NULL_BIT;
            for(uint32 j=0; j<480; j++)
                phy_struct->bch_descramb_bits[(i*480)+j] = (float)phy_struct->bch_soft_bits[j]*(1-2*(float)phy_struct->bch_c[(i*480)+j]);
            if(LIBLTE_SUCCESS == bch_channel_decode(phy_struct,
                                                    phy_struct->bch_descramb_bits,
                                                    1920,
                                                    p,
                                                    out_bits,
                                                    N_out_bits))
            {
                *offset = i;
                *N_ant  = p;
                return LIBLTE_SUCCESS;
            }
        }
    }

    return LIBLTE_ERROR_DECODE_FAIL;
}

/*********************************************************************
    Name: liblte_phy_pdcch_channel_encode

    Description: Encodes and modulates all of the Physical Downlink
                 Control Channels (PCFICH, PHICH, and PDCCH)

    Document Reference: 3GPP TS 36.211 v10.1.0 sections 6.7, 6.8, and
                        6.9
                        3GPP TS 36.212 v10.1.0 section 5.1.4.2.1
                        3GPP TS 36.213 v10.3.0 section 7.1 and 9.1.1
*********************************************************************/
void dci_encode_and_map(LIBLTE_PHY_STRUCT            *phy_struct,
                        uint8                         N_ant,
                        LIBLTE_PHY_CHAN_TYPE_ENUM     chan_type,
                        LIBLTE_PHY_ALLOCATION_STRUCT *alloc)
{
    // Encode the DCI
    uint32 dci_size;
    if(LIBLTE_PHY_CHAN_TYPE_DLSCH == chan_type)
    {
        dci_1a_pack(alloc,
                    LIBLTE_PHY_DCI_CA_NOT_PRESENT,
                    phy_struct->N_rb_dl,
                    N_ant,
                    phy_struct->pdcch_dci,
                    &dci_size);
    }else{ // LIBLTE_PHY_CHAN_TYPE_ULSCH == chan_type
        dci_0_pack(alloc,
                   LIBLTE_PHY_DCI_CA_NOT_PRESENT,
                   phy_struct->N_rb_ul,
                   N_ant,
                   phy_struct->pdcch_dci,
                   &dci_size);
    }
    uint32 N_bits = 288; // Using aggregation level 4 (4*9*4*2 = 288)
    dci_channel_encode(phy_struct,
                       phy_struct->pdcch_dci,
                       dci_size,
                       alloc->rnti,
                       0,
                       N_bits,
                       phy_struct->pdcch_encode_bits);

// FIXME: User Specific search space does not work
//    // Add the DCIs to the search space
//    if(LIBLTE_MAC_SI_RNTI        == alloc->rnti ||
//       LIBLTE_MAC_P_RNTI         == alloc->rnti ||
//       (LIBLTE_MAC_RA_RNTI_START <= alloc->rnti &&
//        LIBLTE_MAC_RA_RNTI_END   >= alloc->rnti))
//    {
        // Add to the common search space, using aggregation level of 4
        for(uint32 css_idx=0; css_idx<4; css_idx++)
        {
            if(!phy_struct->pdcch_cce_used[4*css_idx+0] &&
               !phy_struct->pdcch_cce_used[4*css_idx+1] &&
               !phy_struct->pdcch_cce_used[4*css_idx+2] &&
               !phy_struct->pdcch_cce_used[4*css_idx+3])
            {
                for(uint32 i=0; i<N_bits; i++)
                    phy_struct->pdcch_scramb_bits[i] = phy_struct->pdcch_encode_bits[i] ^ phy_struct->pdcch_c[4*css_idx*LIBLTE_PHY_PDCCH_N_REG_CCE*4*2 + i];
                uint32 M_symb;
                modulation_mapper(phy_struct->pdcch_scramb_bits,
                                  N_bits,
                                  LIBLTE_PHY_MODULATION_TYPE_QPSK,
                                  phy_struct->pdcch_d,
                                  &M_symb);
                uint32 M_layer_symb;
                layer_mapper_dl(phy_struct->pdcch_d,
                                M_symb,
                                N_ant,
                                1,
                                LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                                phy_struct->pdcch_x,
                                &M_layer_symb);
                uint32 M_ap_symb;
                pre_coder_dl(phy_struct->pdcch_x,
                             M_layer_symb,
                             N_ant,
                             LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                             phy_struct->pdcch_y[0],
                             576,
                             &M_ap_symb);
                for(uint32 p=0; p<N_ant; p++)
                {
                    uint32 idx = 0;
                    for(uint32 i=0; i<4; i++)
                    {
                        for(uint32 j=0; j<(4*LIBLTE_PHY_PDCCH_N_REG_CCE); j++)
                            phy_struct->pdcch_cce[p][4*css_idx+i][j] = phy_struct->pdcch_y[p][idx++];
                        phy_struct->pdcch_cce_used[4*css_idx+i] = true;
                    }
                }
                break;
            }
        }
// FIXME: User Specific search space does not work
//    }else{
//        // Add to the user search space, using aggregation level of 4
//        uint32 Y_k = pdcch->alloc[a_idx].rnti;
//        for(uint32 i=0; i<=subframe->num; i++)
//            Y_k = (39827 * Y_k) % 65537;
//        for(uint32 uss_idx=0; uss_idx<2; uss_idx++)
//        {
//            uint32 actual_idx = 4*((Y_k+uss_idx) % (N_cce_pdcch/4));
//            if(!phy_struct->pdcch_cce_used[actual_idx+0] &&
//               !phy_struct->pdcch_cce_used[actual_idx+1] &&
//               !phy_struct->pdcch_cce_used[actual_idx+2] &&
//               !phy_struct->pdcch_cce_used[actual_idx+3])
//            {
//                for(uint32 i=0; i<N_bits; i++)
//                    phy_struct->pdcch_scramb_bits[i] = phy_struct->pdcch_encode_bits[i] ^ phy_struct->pdcch_c[4*actual_idx*LIBLTE_PHY_PDCCH_N_REG_CCE*4*2 + i];
//                uint32 M_symb;
//                modulation_mapper(phy_struct->pdcch_scramb_bits,
//                                  N_bits,
//                                  LIBLTE_PHY_MODULATION_TYPE_QPSK,
//                                  phy_struct->pdcch_d_re,
//                                  phy_struct->pdcch_d_im,
//                                  &M_symb);
//                uint32 M_layer_symb;
//                layer_mapper_dl(phy_struct->pdcch_d_re,
//                                phy_struct->pdcch_d_im,
//                                M_symb,
//                                N_ant,
//                                1,
//                                LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
//                                phy_struct->pdcch_x_re,
//                                phy_struct->pdcch_x_im,
//                                &M_layer_symb);
//                uint32 M_ap_symb;
//                pre_coder_dl(phy_struct->pdcch_x_re,
//                             phy_struct->pdcch_x_im,
//                             M_layer_symb,
//                             N_ant,
//                             LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
//                             phy_struct->pdcch_y_re[0],
//                             phy_struct->pdcch_y_im[0],
//                             576,
//                             &M_ap_symb);
//                for(uint32 p=0; p<N_ant; p++)
//                {
//                    uint32 idx = 0;
//                    for(uint32 i=0; i<4; i++)
//                    {
//                        for(uint32 j=0; j<(4*LIBLTE_PHY_PDCCH_N_REG_CCE); j++)
//                        {
//                            phy_struct->pdcch_cce_re[p][actual_idx+i][j] = phy_struct->pdcch_y_re[p][idx];
//                            phy_struct->pdcch_cce_im[p][actual_idx+i][j] = phy_struct->pdcch_y_im[p][idx];
//                            idx++;
//                        }
//                        phy_struct->pdcch_cce_used[actual_idx+i] = true;
//                    }
//                }
//                break;
//            }
//        }
//    }
}
LIBLTE_ERROR_ENUM liblte_phy_pdcch_channel_encode(LIBLTE_PHY_STRUCT                 *phy_struct,
                                                  LIBLTE_PHY_PCFICH_STRUCT          *pcfich,
                                                  LIBLTE_PHY_PHICH_STRUCT           *phich,
                                                  LIBLTE_PHY_PDCCH_STRUCT           *pdcch,
                                                  uint32                             N_id_cell,
                                                  uint8                              N_ant,
                                                  float                              phich_res,
                                                  PHICH_Config::phich_Duration_Enum  phich_dur,
                                                  LIBLTE_PHY_SUBFRAME_STRUCT        *subframe)
{
    if(phy_struct == NULL || pcfich == NULL || phich == NULL || pdcch == NULL ||
       N_id_cell > 503 || subframe == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // PCFICH
    pcfich_channel_map(phy_struct, pcfich, N_id_cell, N_ant, subframe);

    // PHICH
    phich_channel_map(phy_struct, phich, pcfich, N_id_cell, N_ant, phich_res, phich_dur, subframe);

    // PDCCH
    if(pdcch->N_dl_alloc == 0 && pdcch->N_ul_alloc == 0)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Calculate number of symbols, 3GPP TS 36.211 v10.1.0 section 6.7
    pdcch->N_symbs = pcfich->cfi;
    if(phy_struct->N_rb_dl <= 10)
        pdcch->N_symbs++;
    // Calculate resources, 3GPP TS 36.211 v10.1.0 section 6.8.1
    uint32 N_reg_rb    = 3;
    uint32 N_reg_pdcch = pdcch->N_symbs*(phy_struct->N_rb_dl*N_reg_rb) - phy_struct->N_rb_dl - pcfich->N_reg - phich->N_reg;
    if(N_ant == 4)
        N_reg_pdcch -= phy_struct->N_rb_dl; // Remove CRS
    uint32 N_cce_pdcch = N_reg_pdcch/LIBLTE_PHY_PDCCH_N_REG_CCE;

    // Initialize the search space
    for(uint32 p=0; p<N_ant; p++)
    {
        for(uint32 i=0; i<N_cce_pdcch; i++)
        {
            for(uint32 j=0; j<4*LIBLTE_PHY_PDCCH_N_REG_CCE; j++)
                phy_struct->pdcch_cce[p][i][j] = complex(0, 0);
            phy_struct->pdcch_cce_used[i] = false;
        }
    }

    // Generate the scrambling sequence
    uint32 c_init = (subframe->num << 9) + N_id_cell;
    generate_prs_c(c_init, LIBLTE_PHY_PDCCH_N_BITS_MAX * 2, phy_struct->pdcch_c);

    // Add the DCIs
    for(uint32 alloc_idx=0; alloc_idx<pdcch->N_dl_alloc; alloc_idx++)
        dci_encode_and_map(phy_struct,
                           N_ant,
                           pdcch->dl_alloc[alloc_idx].chan_type,
                           &pdcch->dl_alloc[alloc_idx]);
    for(uint32 alloc_idx=0; alloc_idx<pdcch->N_ul_alloc; alloc_idx++)
        dci_encode_and_map(phy_struct,
                           N_ant,
                           pdcch->ul_alloc[alloc_idx].chan_type,
                           &pdcch->ul_alloc[alloc_idx]);

    // Construct REGs
    for(uint32 p=0; p<N_ant; p++)
        for(uint32 i=0; i<N_cce_pdcch; i++)
            for(uint32 j=0; j<LIBLTE_PHY_PDCCH_N_REG_CCE; j++)
                for(uint32 k=0; k<4; k++)
                    phy_struct->pdcch_reg[p][i*LIBLTE_PHY_PDCCH_N_REG_CCE+j][k] = phy_struct->pdcch_cce[p][i][j*4+k];
    // Permute the REGs, 3GPP TS 36.212 v10.1.0 section 5.1.4.2.1
    for(uint32 p=0; p<N_ant; p++)
        for(uint32 i=0; i<N_reg_pdcch; i++)
            for(uint32 j=0; j<4; j++)
                phy_struct->pdcch_perm[p][i][j] = phy_struct->pdcch_reg[p][phy_struct->pdcch_permute_map[N_reg_pdcch][i]][j];
    // Cyclic shift the REGs
    for(uint32 p=0; p<N_ant; p++)
        for(uint32 i=0; i<N_reg_pdcch; i++)
        {
            uint32 shift_idx = (i+N_id_cell) % N_reg_pdcch;
            for(uint32 j=0; j<4; j++)
                phy_struct->pdcch_shift[p][i][j] = phy_struct->pdcch_perm[p][shift_idx][j];
        }
    // Map the REGs to resource elements, 3GPP TS 36.211 v10.1.0 section 6.8.5
    // Step 1 and 2
    uint32 m_prime = 0;
    uint32 k_prime = 0;
    // Step 10
    while(k_prime < (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl))
    {
        // Step 3
        uint32 l_prime = 0;
        // Step 8
        bool valid_reg;
        while(l_prime < pdcch->N_symbs)
        {
            if(l_prime == 0)
            {
                // Step 4
                // Avoid PCFICH and PHICH
                valid_reg = true;
                for(uint32 i=0; i<pcfich->N_reg; i++)
                    if(k_prime == pcfich->k[i])
                        valid_reg = false;
                for(uint32 i=0; i<phich->N_reg; i++)
                    if(k_prime == phich->k[i])
                        valid_reg = false;
                if((k_prime % 6) == 0 && valid_reg == true)
                {
                    if(m_prime < N_reg_pdcch)
                    {
                        // Step 5
                        uint32 idx = 0;
                        for(uint32 i=0; i<6; i++)
                        {
                            // Avoid CRS
                            if((N_id_cell % 3) != (i % 3))
                            {
                                for(uint32 p=0; p<N_ant; p++)
                                    subframe->tx_symb[p][l_prime][k_prime+i] = phy_struct->pdcch_shift[p][m_prime][idx];
                                idx++;
                            }
                        }
                        // Step 6
                        m_prime++;
                    }
                }
            }else if(l_prime == 1 && N_ant == 4){
                // Step 4
                if((k_prime % 6) == 0)
                {
                    if(m_prime < N_reg_pdcch)
                    {
                        // Step 5
                        uint32 idx = 0;
                        for(uint32 i=0; i<6; i++)
                        {
                            // Avoid CRS
                            if((N_id_cell % 3) != (i % 3))
                            {
                                for(uint32 p=0; p<N_ant; p++)
                                    subframe->tx_symb[p][l_prime][k_prime+i] = phy_struct->pdcch_shift[p][m_prime][idx];
                                idx++;
                            }
                        }
                        // Step 6
                        m_prime++;
                    }
                }
            }else{
                // Step 4
                if((k_prime % 4) == 0)
                {
                    if(m_prime < N_reg_pdcch)
                    {
                        // Step 5
                        for(uint32 i=0; i<4; i++)
                            for(uint32 p=0; p<N_ant; p++)
                                subframe->tx_symb[p][l_prime][k_prime+i] = phy_struct->pdcch_shift[p][m_prime][i];
                        // Step 6
                        m_prime++;
                    }
                }
            }
            // Step 7
            l_prime++;
        }
        // Step 9
        k_prime++;
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_pdcch_channel_decode

    Description: Demodulates and decodes all of the Physical Downlink
                 Control Channels (PCFICH, PHICH, and PDCCH)

    Document Reference: 3GPP TS 36.211 v10.1.0 sections 6.7, 6.8, and
                        6.9
                        3GPP TS 36.212 v10.1.0 section 5.1.4.2.1
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_pdcch_channel_decode(LIBLTE_PHY_STRUCT                 *phy_struct,
                                                  LIBLTE_PHY_SUBFRAME_STRUCT        *subframe,
                                                  uint32                             N_id_cell,
                                                  uint8                              N_ant,
                                                  float                              phich_res,
                                                  PHICH_Config::phich_Duration_Enum  phich_dur,
                                                  LIBLTE_PHY_PCFICH_STRUCT          *pcfich,
                                                  LIBLTE_PHY_PHICH_STRUCT           *phich,
                                                  LIBLTE_PHY_PDCCH_STRUCT           *pdcch)
{
    if(phy_struct == NULL || subframe == NULL || pcfich == NULL || phich == NULL ||
       pdcch == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // PCFICH
    uint32 N_bits;
    pcfich_channel_demap(phy_struct, subframe, N_id_cell, N_ant, pcfich, &N_bits);
    if(LIBLTE_SUCCESS != cfi_channel_decode(phy_struct,
                                            phy_struct->pdcch_descramb_bits,
                                            N_bits,
                                            &pcfich->cfi))
        return LIBLTE_ERROR_INVALID_CRC;

    // PHICH
    phich_channel_demap(phy_struct, pcfich, subframe, N_id_cell, N_ant, phich_res, phich_dur, phich);

    // PDCCH
    // Calculate number of symbols, 3GPP TS 36.211 v10.1.0 section 6.7
    pdcch->N_symbs = pcfich->cfi;
    if(phy_struct->N_rb_dl <= 10)
        pdcch->N_symbs++;
    // Calculate resources, 3GPP TS 36.211 v10.1.0 section 6.8.1
    uint32 N_reg_rb    = 3;
    uint32 N_reg_pdcch = pdcch->N_symbs*(phy_struct->N_rb_dl*N_reg_rb) - phy_struct->N_rb_dl - pcfich->N_reg - phich->N_reg;
    if(N_ant == 4)
        N_reg_pdcch -= phy_struct->N_rb_dl; // Remove CRS
    uint32 N_cce_pdcch = N_reg_pdcch/9;
    // Extract resource elements and channel estimate, 3GPP TS 36.211 v10.1.0 section 6.8.5
    // Step 1 and 2
    uint32 m_prime = 0;
    uint32 k_prime = 0;
    // Step 10
    uint32 idx;
    while(k_prime < (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl))
    {
        // Step 3
        uint32 l_prime = 0;
        // Step 8
        while(l_prime < pdcch->N_symbs)
        {
            if(l_prime == 0)
            {
                // Step 4
                // Avoid PCFICH and PHICH
                bool valid_reg = true;
                for(uint32 i=0; i<pcfich->N_reg; i++)
                    if(k_prime == pcfich->k[i])
                        valid_reg = false;
                for(uint32 i=0; i<phich->N_reg; i++)
                    if(k_prime == phich->k[i])
                        valid_reg = false;
                if((k_prime % 6) == 0 && valid_reg == true)
                {
                    if(m_prime < N_reg_pdcch)
                    {
                        // Step 5
                        idx = 0;
                        for(uint32 i=0; i<6; i++)
                        {
                            // Avoid CRS
                            if((N_id_cell % 3) != (i % 3))
                            {
                                phy_struct->pdcch_reg_y_est[m_prime][idx] = subframe->rx_symb[l_prime][k_prime+i];
                                for(uint32 p=0; p<N_ant; p++)
                                    phy_struct->pdcch_reg_c_est[p][m_prime][idx] = subframe->rx_ce[p][l_prime][k_prime+i];
                                idx++;
                            }
                        }
                        // Step 6
                        m_prime++;
                    }
                }
            }else if(l_prime == 1 && N_ant == 4){
                // Step 4
                if((k_prime % 6) == 0)
                {
                    if(m_prime < N_reg_pdcch)
                    {
                        // Step 5
                        idx = 0;
                        for(uint32 i=0; i<6; i++)
                        {
                            // Avoid CRS
                            if((N_id_cell % 3) != (i % 3))
                            {
                                phy_struct->pdcch_reg_y_est[m_prime][idx] = subframe->rx_symb[l_prime][k_prime+i];
                                for(uint32 p=0; p<N_ant; p++)
                                    phy_struct->pdcch_reg_c_est[p][m_prime][idx] = subframe->rx_ce[p][l_prime][k_prime+i];
                                idx++;
                            }
                        }
                        // Step 6
                        m_prime++;
                    }
                }
            }else{
                // Step 4
                if((k_prime % 4) == 0)
                {
                    if(m_prime < N_reg_pdcch)
                    {
                        // Step 5
                        for(uint32 i=0; i<4; i++)
                        {
                            phy_struct->pdcch_reg_y_est[m_prime][i] = subframe->rx_symb[l_prime][k_prime+i];
                            for(uint32 p=0; p<N_ant; p++)
                                phy_struct->pdcch_reg_c_est[p][m_prime][i] = subframe->rx_ce[p][l_prime][k_prime+i];
                        }
                        // Step 6
                        m_prime++;
                    }
                }
            }
            // Step 7
            l_prime++;
        }
        // Step 9
        k_prime++;
    }
    // Undo cyclic shift of the REGs
    for(uint32 i=0; i<N_reg_pdcch; i++)
    {
        uint32 shift_idx = (i+N_id_cell) % N_reg_pdcch;
        for(uint32 j=0; j<4; j++)
        {
            phy_struct->pdcch_shift_y_est[shift_idx][j] = phy_struct->pdcch_reg_y_est[i][j];
            for(uint32 p=0; p<N_ant; p++)
                phy_struct->pdcch_shift_c_est[p][shift_idx][j] = phy_struct->pdcch_reg_c_est[p][i][j];
        }
    }
    // Undo permutation of the REGs, 3GPP TS 36.212 v10.1.0 section 5.1.4.2.1
    for(uint32 i=0; i<N_reg_pdcch; i++)
        phy_struct->pdcch_reg_vec[i] = i;
    // In order to recreate circular buffer, a dummy block must be
    // sub block interleaved to determine where NULL bits are to be
    // inserted
    // Step 1
    uint32 C_cc_sb = 32;
    // Step 2
    uint32 R_cc_sb = 0;
    while(N_reg_pdcch > (C_cc_sb*R_cc_sb))
        R_cc_sb++;
    // Step 3
    uint32 N_dummy = 0;
    if(N_reg_pdcch < (C_cc_sb*R_cc_sb))
        N_dummy = C_cc_sb*R_cc_sb - N_reg_pdcch;
    for(uint32 i=0; i<N_dummy; i++)
        phy_struct->ruc_tmp[i] = RX_NULL_BIT;
    for(uint32 i=N_dummy; i<C_cc_sb*R_cc_sb; i++)
        phy_struct->ruc_tmp[i] = 0;
    idx = 0;
    for(uint32 i=0; i<R_cc_sb; i++)
        for(uint32 j=0; j<C_cc_sb; j++)
            phy_struct->ruc_sb_mat[i][j] = phy_struct->ruc_tmp[idx++];
    // Step 4
    for(uint32 i=0; i<R_cc_sb; i++)
        for(uint32 j=0; j<C_cc_sb; j++)
            phy_struct->ruc_sb_perm_mat[i][j] = phy_struct->ruc_sb_mat[i][IC_PERM_CC[j]];
    // Step 5
    idx = 0;
    for(uint32 j=0; j<C_cc_sb; j++)
        for(uint32 i=0; i<R_cc_sb; i++)
            phy_struct->ruc_v[0][idx++] = phy_struct->ruc_sb_perm_mat[i][j];
    // Recreate circular buffer
    uint32 K_pi = R_cc_sb*C_cc_sb;
    {
        uint32 k = 0;
        uint32 j = 0;
        while(k < N_reg_pdcch)
        {
            if(phy_struct->ruc_v[0][j%K_pi] != RX_NULL_BIT)
                phy_struct->ruc_v[0][j%K_pi] = phy_struct->pdcch_reg_vec[k++];
            j++;
        }
    }
    // Sub block deinterleaving
    // Step 5
    idx = 0;
    for(uint32 j=0; j<C_cc_sb; j++)
        for(uint32 i=0; i<R_cc_sb; i++)
            phy_struct->ruc_sb_perm_mat[i][j] = phy_struct->ruc_v[0][idx++];
    // Step 4
    for(uint32 i=0; i<R_cc_sb; i++)
        for(uint32 j=0; j<C_cc_sb; j++)
            phy_struct->ruc_sb_mat[i][IC_PERM_CC[j]] = phy_struct->ruc_sb_perm_mat[i][j];
    // Step 3
    idx = 0;
    for(uint32 i=0; i<R_cc_sb; i++)
        for(uint32 j=0; j<C_cc_sb; j++)
            phy_struct->ruc_tmp[idx++] = phy_struct->ruc_sb_mat[i][j];
    for(uint32 i=0; i<N_reg_pdcch; i++)
        for(uint32 j=0; j<4; j++)
        {
            phy_struct->pdcch_perm_y_est[i][j] = phy_struct->pdcch_shift_y_est[(uint32)phy_struct->ruc_tmp[N_dummy+i]][j];
            for(uint32 p=0; p<N_ant; p++)
                phy_struct->pdcch_perm_c_est[p][i][j] = phy_struct->pdcch_shift_c_est[p][(uint32)phy_struct->ruc_tmp[N_dummy+i]][j];
        }
    // Construct CCEs
    for(uint32 i=0; i<N_cce_pdcch; i++)
        for(uint32 j=0; j<LIBLTE_PHY_PDCCH_N_REG_CCE; j++)
            for(uint32 k=0; k<4; k++)
            {
                phy_struct->pdcch_cce_y_est[i][j*4+k] = phy_struct->pdcch_perm_y_est[i*LIBLTE_PHY_PDCCH_N_REG_CCE+j][k];
                for(uint32 p=0; p<N_ant; p++)
                    phy_struct->pdcch_cce_c_est[p][i][j*4+k] = phy_struct->pdcch_perm_c_est[p][i*LIBLTE_PHY_PDCCH_N_REG_CCE+j][k];
            }

    // Generate the scrambling sequence
    uint32 c_init = (subframe->num << 9) + N_id_cell;
    generate_prs_c(c_init, LIBLTE_PHY_PDCCH_N_BITS_MAX * 2, phy_struct->pdcch_c);

    // Determine the size of DCI 1A and 1C FIXME: Clean this up
    uint32 dci_1a_size;
    uint32 dci_1c_size;
    if(phy_struct->N_rb_dl == 6)
    {
        dci_1a_size = 21;
        dci_1c_size = 9;
    }else if(phy_struct->N_rb_dl == 15){
        dci_1a_size = 22;
        dci_1c_size = 11;
    }else if(phy_struct->N_rb_dl == 25){
        dci_1a_size = 25;
        dci_1c_size = 13;
    }else if(phy_struct->N_rb_dl == 50){
        dci_1a_size = 27;
        dci_1c_size = 13;
    }else if(phy_struct->N_rb_dl == 75){
        dci_1a_size = 27;
        dci_1c_size = 14;
    }else{ // phy_struct->N_rb_dl == 100
        dci_1a_size = 28;
        dci_1c_size = 15;
    }

    // Try decoding DCI 1A and 1C for SI in the common search space
    uint32 M_layer_symb;
    uint32 M_symb;
    uint16 rnti       = 0;
    pdcch->N_dl_alloc = 0;
    pdcch->N_ul_alloc = 0;
    for(uint32 i=0; i<4; i++)
    {
        idx = 0;
        for(uint32 j=0; j<4; j++)
            for(uint32 k=0; k<36; k++)
            {
                phy_struct->pdcch_y_est[idx] = phy_struct->pdcch_cce_y_est[i*4+j][k];
                for(uint32 p=0; p<N_ant; p++)
                    phy_struct->pdcch_c_est[p][idx] = phy_struct->pdcch_cce_c_est[p][i*4+j][k];
                idx++;
            }

        de_pre_coder_dl(phy_struct->pdcch_y_est,
                        phy_struct->pdcch_c_est[0],
                        576,
                        idx,
                        N_ant,
                        LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                        phy_struct->pdcch_x,
                        &M_layer_symb);
        layer_demapper_dl(phy_struct->pdcch_x,
                          M_layer_symb,
                          N_ant,
                          1,
                          LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                          phy_struct->pdcch_d,
                          &M_symb);
        modulation_demapper(phy_struct->pdcch_d,
                            M_symb,
                            LIBLTE_PHY_MODULATION_TYPE_QPSK,
                            phy_struct->pdcch_soft_bits,
                            &N_bits);
        for(uint32 j=0; j<N_bits; j++)
            phy_struct->pdcch_descramb_bits[j] = (float)phy_struct->pdcch_soft_bits[j]*(1-2*(float)phy_struct->pdcch_c[i*288+j]);
        if(pdcch->N_dl_alloc  <  LIBLTE_PHY_PDCCH_MAX_ALLOC &&
           (LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_SI_RNTI,
                                                   1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1a_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_P_RNTI,
                                                   1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1a_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_RA_RNTI_START,
                                                   LIBLTE_MAC_RA_RNTI_END - LIBLTE_MAC_RA_RNTI_START + 1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1a_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   61,
                                                   10,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1a_size,
                                                   &rnti)))
        {
            if(LIBLTE_SUCCESS == dci_1a_unpack(phy_struct->pdcch_dci,
                                               dci_1a_size,
                                               LIBLTE_PHY_DCI_CA_NOT_PRESENT,
                                               rnti,
                                               phy_struct->N_rb_dl,
                                               N_ant,
                                               &pdcch->dl_alloc[pdcch->N_dl_alloc]))
                pdcch->N_dl_alloc++;
        }
        if(pdcch->N_dl_alloc  <  LIBLTE_PHY_PDCCH_MAX_ALLOC &&
           (LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_SI_RNTI,
                                                   1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1c_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_P_RNTI,
                                                   1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1c_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_RA_RNTI_START,
                                                   LIBLTE_MAC_RA_RNTI_END - LIBLTE_MAC_RA_RNTI_START + 1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1c_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   61,
                                                   1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1c_size,
                                                   &rnti)))
        {
            if(LIBLTE_SUCCESS == dci_1c_unpack(phy_struct->pdcch_dci,
                                               dci_1c_size,
                                               rnti,
                                               phy_struct->N_rb_dl,
                                               N_ant,
                                               &pdcch->dl_alloc[pdcch->N_dl_alloc]))
                pdcch->N_dl_alloc++;
        }
    }
    for(uint32 i=0; i<2; i++)
    {
        idx = 0;
        for(uint32 j=0; j<8; j++)
            for(uint32 k=0; k<36; k++)
            {
                phy_struct->pdcch_y_est[idx] = phy_struct->pdcch_cce_y_est[i*8+j][k];
                for(uint32 p=0; p<N_ant; p++)
                    phy_struct->pdcch_c_est[p][idx] = phy_struct->pdcch_cce_c_est[p][i*8+j][k];
                idx++;
            }

        de_pre_coder_dl(phy_struct->pdcch_y_est,
                        phy_struct->pdcch_c_est[0],
                        576,
                        idx,
                        N_ant,
                        LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                        phy_struct->pdcch_x,
                        &M_layer_symb);
        layer_demapper_dl(phy_struct->pdcch_x,
                          M_layer_symb,
                          N_ant,
                          1,
                          LIBLTE_PHY_PRE_CODER_TYPE_TX_DIVERSITY,
                          phy_struct->pdcch_d,
                          &M_symb);
        modulation_demapper(phy_struct->pdcch_d,
                            M_symb,
                            LIBLTE_PHY_MODULATION_TYPE_QPSK,
                            phy_struct->pdcch_soft_bits,
                            &N_bits);
        for(uint32 j=0; j<N_bits; j++)
            phy_struct->pdcch_descramb_bits[j] = (float)phy_struct->pdcch_soft_bits[j]*(1-2*(float)phy_struct->pdcch_c[i*576+j]);
        if(pdcch->N_dl_alloc  <  LIBLTE_PHY_PDCCH_MAX_ALLOC &&
           (LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_SI_RNTI,
                                                   1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1a_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_P_RNTI,
                                                   1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1a_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_RA_RNTI_START,
                                                   LIBLTE_MAC_RA_RNTI_END - LIBLTE_MAC_RA_RNTI_START + 1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1a_size,
                                                   &rnti)))
        {
            if(LIBLTE_SUCCESS == dci_1a_unpack(phy_struct->pdcch_dci,
                                               dci_1a_size,
                                               LIBLTE_PHY_DCI_CA_NOT_PRESENT,
                                               rnti,
                                               phy_struct->N_rb_dl,
                                               N_ant,
                                               &pdcch->dl_alloc[pdcch->N_dl_alloc]))
                pdcch->N_dl_alloc++;
        }
        if(pdcch->N_dl_alloc  <  LIBLTE_PHY_PDCCH_MAX_ALLOC &&
           (LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_SI_RNTI,
                                                   1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1c_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_P_RNTI,
                                                   1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1c_size,
                                                   &rnti) ||
            LIBLTE_SUCCESS   == dci_channel_decode(phy_struct,
                                                   phy_struct->pdcch_descramb_bits,
                                                   N_bits,
                                                   LIBLTE_MAC_RA_RNTI_START,
                                                   LIBLTE_MAC_RA_RNTI_END - LIBLTE_MAC_RA_RNTI_START + 1,
                                                   0,
                                                   phy_struct->pdcch_dci,
                                                   dci_1c_size,
                                                   &rnti)))
        {
            if(LIBLTE_SUCCESS == dci_1c_unpack(phy_struct->pdcch_dci,
                                               dci_1c_size,
                                               rnti,
                                               phy_struct->N_rb_dl,
                                               N_ant,
                                               &pdcch->dl_alloc[pdcch->N_dl_alloc]))
                pdcch->N_dl_alloc++;
        }
    }

    if(pdcch->N_dl_alloc > 0)
        return LIBLTE_SUCCESS;
    return LIBLTE_ERROR_DECODE_FAIL;
}

/*********************************************************************
    Name: liblte_phy_map_crs

    Description: Maps the Cell Specific Reference Signals to the
                 subframe

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.10.1
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_map_crs(LIBLTE_PHY_STRUCT          *phy_struct,
                                     LIBLTE_PHY_SUBFRAME_STRUCT *subframe,
                                     uint32                      N_id_cell,
                                     uint8                       N_ant)
{
    if(phy_struct == NULL || subframe == NULL || N_id_cell > 503)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Generate cell specific reference signals
    complex *crs[14];
    if(phy_struct->N_id_cell_crs == N_id_cell)
    {
        crs[0]  = &phy_struct->crs_storage[subframe->num*2  ][0][0];
        crs[1]  = &phy_struct->crs_storage[subframe->num*2  ][1][0];
        crs[4]  = &phy_struct->crs_storage[subframe->num*2  ][2][0];
        crs[7]  = &phy_struct->crs_storage[subframe->num*2+1][0][0];
        crs[8]  = &phy_struct->crs_storage[subframe->num*2+1][1][0];
        crs[11] = &phy_struct->crs_storage[subframe->num*2+1][2][0];
    }else{
        generate_crs(subframe->num*2,   0, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->crs[0]);
        generate_crs(subframe->num*2,   1, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->crs[1]);
        generate_crs(subframe->num*2,   4, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->crs[4]);
        generate_crs(subframe->num*2+1, 0, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->crs[7]);
        generate_crs(subframe->num*2+1, 1, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->crs[8]);
        generate_crs(subframe->num*2+1, 4, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->crs[11]);
        crs[0]  = &phy_struct->crs[0 ][0];
        crs[1]  = &phy_struct->crs[1 ][0];
        crs[4]  = &phy_struct->crs[4 ][0];
        crs[7]  = &phy_struct->crs[7 ][0];
        crs[8]  = &phy_struct->crs[8 ][0];
        crs[11] = &phy_struct->crs[11][0];
    }

    for(uint32 p=0; p<N_ant; p++)
    {
        uint32 *v;
        uint32 *sym;
        uint32  v_p0_2[4]   = {0, 3, 0, 3};
        uint32  v_p1[4]     = {3, 0, 3, 0};
        uint32  v_p3[2]     = {3, 6};
        uint32  sym_p0_1[4] = {0, 4, 7, 11};
        uint32  sym_p2_3[2] = {1, 8};
        uint32  N_sym;
        if(p == 0)
        {
            v     = v_p0_2;
            sym   = sym_p0_1;
            N_sym = 4;
        }else if(p == 1){
            v     = v_p1;
            sym   = sym_p0_1;
            N_sym = 4;
        }else if(p == 2){
            v     = v_p0_2;
            sym   = sym_p2_3;
            N_sym = 2;
        }else{ // p == 3
            v     = v_p3;
            sym   = sym_p2_3;
            N_sym = 2;
        }
        uint32 v_shift = N_id_cell % 6;
        for(uint32 i=0; i<N_sym; i++)
            for(uint32 j=0; j<2*phy_struct->N_rb_dl; j++)
                subframe->tx_symb[p][sym[i]][6*j + (v[i] + v_shift)%6] =
                    crs[sym[i]][j + LIBLTE_PHY_N_RB_DL_MAX - phy_struct->N_rb_dl];
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_map_pss

    Description: Maps the Primary Synchronization Signal to the
                 subframe.

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.11.1
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_map_pss(LIBLTE_PHY_STRUCT          *phy_struct,
                                     LIBLTE_PHY_SUBFRAME_STRUCT *subframe,
                                     uint32                      N_id_2,
                                     uint8                       N_ant)
{
    if(phy_struct == NULL || subframe == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    complex pss[63];
    generate_pss(N_id_2, pss);

    for(uint32 p=0; p<N_ant; p++)
        for(uint32 i=0; i<62; i++)
            subframe->tx_symb[p][6][i - 31 + (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl)/2] =
                pss[i];

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_find_pss_and_fine_timing

    Description: Searches for the Primary Synchronization Signal and
                 determines fine timing.

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.11.1
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_find_pss_and_fine_timing(LIBLTE_PHY_STRUCT *phy_struct,
                                                      complex           *samps,
                                                      uint32            *symb_starts,
                                                      uint32            *N_id_2,
                                                      uint32            *pss_symb,
                                                      float             *pss_thresh,
                                                      float             *freq_offset)
{
    if(phy_struct == NULL || samps == NULL || symb_starts == NULL || N_id_2 == NULL ||
       pss_symb == NULL || pss_thresh == NULL || freq_offset == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Generate PSS
    for(uint32 i=0; i<3; i++)
    {
        for(uint32 j=0; j<phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl; j++)
            phy_struct->pss_mod[i][j] = complex(0, 0);
        complex pss[63];
        generate_pss(i, pss);
        for(uint32 j=0; j<62; j++)
        {
            uint32 k                       = j - 31 + (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl)/2;
            phy_struct->pss_mod_n1[i][k-1] = pss[j];
            phy_struct->pss_mod[i][k]      = pss[j];
            phy_struct->pss_mod_p1[i][k+1] = pss[j];
        }
    }

    // Demod symbols and correlate with PSS
    float corr_max = 0;
    int32 idx      = 0;
    for(uint32 i=0; i<12; i++)
    {
        for(uint32 j=0; j<N_SYMB_DL_NORMAL_CP; j++)
        {
            samples_to_symbols_dl(phy_struct,
                                  samps,
                                  symb_starts[j]+(phy_struct->N_samps_per_slot*i),
                                  0,
                                  0,
                                  phy_struct->rx_symb);

            for(uint32 k=0; k<3; k++)
            {
                complex corr_n1 = complex(0, 0);
                complex corr    = complex(0, 0);
                complex corr_p1 = complex(0, 0);
                for(uint32 z=0; z<phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl; z++)
                {
                    corr_n1 += phy_struct->pss_mod_n1[k][z] * std::conj(phy_struct->rx_symb[z]);
                    corr    += phy_struct->pss_mod[k][z] * std::conj(phy_struct->rx_symb[z]);
                    corr_p1 += phy_struct->pss_mod_p1[k][z] * std::conj(phy_struct->rx_symb[z]);
                }
                float abs_corr_n1 = std::abs(corr_n1);
                float abs_corr    = std::abs(corr);
                float abs_corr_p1 = std::abs(corr_p1);
                if(abs_corr_n1 > corr_max)
                {
                    idx       = -1;
                    corr_max  = abs_corr_n1;
                    *pss_symb = (i*N_SYMB_DL_NORMAL_CP)+j;
                    *N_id_2   = k;
                }
                if(abs_corr > corr_max)
                {
                    idx       = 0;
                    corr_max  = abs_corr;
                    *pss_symb = (i*N_SYMB_DL_NORMAL_CP)+j;
                    *N_id_2   = k;
                }
                if(abs_corr_p1 > corr_max)
                {
                    idx       = 1;
                    corr_max  = abs_corr_p1;
                    *pss_symb = (i*N_SYMB_DL_NORMAL_CP)+j;
                    *N_id_2   = k;
                }
            }
        }
    }
    complex *pss_mod;
    if(-1 == idx)
    {
        pss_mod      = &phy_struct->pss_mod_n1[*N_id_2][0];
        *freq_offset = -(phy_struct->fs / phy_struct->FFT_size);
    }else if(0 == idx){
        pss_mod      = &phy_struct->pss_mod[*N_id_2][0];
        *freq_offset = 0;
    }else{
        pss_mod      = &phy_struct->pss_mod_p1[*N_id_2][0];
        *freq_offset = phy_struct->fs / phy_struct->FFT_size;
    }

    // Find optimal timing
    uint32 N_s    = (*pss_symb)/7;
    uint32 N_symb = (*pss_symb)%7;
    int8   timing = 0;
    corr_max      = 0;
    for(int32 i=-40; i<40; i++)
    {
        int32 idx = symb_starts[N_symb] + (phy_struct->N_samps_per_slot*N_s);
        if(i < 0)
        {
            if(idx >= -i)
                idx += i;
        }else{
            idx += i;
        }

        samples_to_symbols_dl(phy_struct,
                              samps,
                              idx,
                              0,
                              0,
                              phy_struct->rx_symb);

        complex corr = complex(0, 0);
        for(uint32 j=0; j<phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl; j++)
            corr += pss_mod[j] * std::conj(phy_struct->rx_symb[j]);
        float abs_corr = std::abs(corr);
        if(abs_corr > corr_max)
        {
            corr_max = abs_corr;
            timing   = i;
        }
    }
    *pss_thresh = corr_max;

    // Construct fine symbol start locations
    uint32 pss_timing_idx = symb_starts[N_symb]+(phy_struct->N_samps_per_slot*N_s)+timing;
    while((pss_timing_idx + phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_else) < phy_struct->N_samps_per_slot)
        pss_timing_idx += phy_struct->N_samps_per_frame;
    symb_starts[0] = pss_timing_idx + (phy_struct->N_samps_per_symb+phy_struct->N_samps_cp_l_else)*1 - phy_struct->N_samps_per_slot;
    for(uint32 i=1; i<7; i++)
        symb_starts[i] = pss_timing_idx +
            (phy_struct->N_samps_per_symb+phy_struct->N_samps_cp_l_else)*i +
            phy_struct->N_samps_per_symb+phy_struct->N_samps_cp_l_0 -
            phy_struct->N_samps_per_slot;

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_map_sss

    Description: Maps the Secondary Synchronization Signal to the
                 subframe.

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.11.2
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_map_sss(LIBLTE_PHY_STRUCT          *phy_struct,
                                     LIBLTE_PHY_SUBFRAME_STRUCT *subframe,
                                     uint32                      N_id_1,
                                     uint32                      N_id_2,
                                     uint8                       N_ant)
{
    if(phy_struct == NULL || subframe == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    generate_sss(phy_struct,
                 N_id_1,
                 N_id_2,
                 &phy_struct->sss_mod_0[0][0],
                 &phy_struct->sss_mod_5[0][0]);

    if(subframe->num == 0)
    {
        for(uint32 p=0; p<N_ant; p++)
            for(uint32 i=0; i<62; i++)
                subframe->tx_symb[p][5][i - 31 + (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl)/2] =
                    phy_struct->sss_mod_0[0][i];
        return LIBLTE_SUCCESS;
    }

    for(uint32 p=0; p<N_ant; p++)
        for(uint32 i=0; i<62; i++)
            subframe->tx_symb[p][5][i - 31 + (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl)/2] =
                phy_struct->sss_mod_5[0][i];
    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_find_sss

    Description: Searches for the Secondary Synchronization Signal.

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.11.2
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_find_sss(LIBLTE_PHY_STRUCT *phy_struct,
                                      complex           *samps,
                                      uint32             N_id_2,
                                      uint32            *symb_starts,
                                      float              pss_thresh,
                                      uint32            *N_id_1,
                                      uint32            *frame_start_idx)
{
    if(phy_struct == NULL || samps == NULL || symb_starts == NULL || N_id_1 == NULL ||
       frame_start_idx == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Generate secondary synchronization signals
    for(uint32 i=0; i<168; i++)
        for(uint32 j=0; j<LIBLTE_PHY_N_RB_DL_20MHZ*LIBLTE_PHY_N_SC_RB_DL_NORMAL_CP; j++)
        {
            phy_struct->sss_mod_0[i][j] = complex(0, 0);
            phy_struct->sss_mod_5[i][j] = complex(0, 0);
        }
    for(uint32 i=0; i<168; i++)
    {
        generate_sss(phy_struct,
                     i,
                     N_id_2,
                     phy_struct->sss_0,
                     phy_struct->sss_5);
        for(uint32 j=0; j<62; j++)
        {
            uint32 k                    = j - 31 + (phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl)/2;
            phy_struct->sss_mod_0[i][k] = phy_struct->sss_0[j];
            phy_struct->sss_mod_5[i][k] = phy_struct->sss_5[j];
        }
    }
    float sss_thresh = pss_thresh * 0.9;

    // Demod symbol and search for secondary synchronization signals
    samples_to_symbols_dl(phy_struct,
                          samps,
                          symb_starts[5],
                          0,
                          0,
                          phy_struct->rx_symb);
    for(uint32 i=0; i<168; i++)
    {
        complex corr = complex(0, 0);
        for(uint32 j=0; j<(phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl); j++)
            corr += phy_struct->sss_mod_0[i][j] * std::conj(phy_struct->rx_symb[j]);
        float abs_corr = std::abs(corr);
        if(abs_corr > sss_thresh)
        {
            while(symb_starts[5] < ((phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_else)*4 + phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_0))
                symb_starts[5] += phy_struct->N_samps_per_frame;
            *N_id_1          = i;
            *frame_start_idx = symb_starts[5] - ((phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_else)*4 + phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_0);
            return LIBLTE_SUCCESS;
        }

        corr = complex(0, 0);
        for(uint32 j=0; j<(phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl); j++)
            corr += phy_struct->sss_mod_5[i][j] * std::conj(phy_struct->rx_symb[j]);
        abs_corr = std::abs(corr);
        if(abs_corr > sss_thresh)
        {
            while(symb_starts[5] < (((phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_else)*4 + phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_0) + phy_struct->N_samps_per_slot*10))
                symb_starts[5] += phy_struct->N_samps_per_frame;
            *N_id_1          = i;
            *frame_start_idx = symb_starts[5] - ((phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_else)*4 + phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_0) - phy_struct->N_samps_per_slot*10;
            return LIBLTE_SUCCESS;
        }
    }

    return LIBLTE_ERROR_INVALID_INPUTS;
}

/*********************************************************************
    Name: liblte_phy_dl_find_coarse_timing_and_freq_offset

    Description: Finds coarse time syncronization and frequency offset
                 by auto-correlating to find the cyclic prefix on
                 reference signal symbols of the downlink

    Document Reference: 3GPP TS 36.211 v10.1.0
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_dl_find_coarse_timing_and_freq_offset(LIBLTE_PHY_STRUCT               *phy_struct,
                                                                   complex                         *samps,
                                                                   uint32                           N_slots,
                                                                   LIBLTE_PHY_COARSE_TIMING_STRUCT *timing_struct)
{
    if(phy_struct == NULL || samps == NULL || timing_struct == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Timing correlation
    for(uint32 i=0; i<phy_struct->N_samps_per_slot; i++)
        phy_struct->dl_timing_abs_corr[i] = 0;
    for(uint32 slot=0; slot<N_slots; slot++)
    {
        for(uint32 i=0; i<phy_struct->N_samps_per_slot; i++)
        {
            complex corr = complex(0, 0);
            for(uint32 j=0; j<phy_struct->N_samps_cp_l_else; j++)
            {
                uint32 idx  = (slot*phy_struct->N_samps_per_slot) + i + j;
                corr       += samps[idx+phy_struct->N_samps_per_symb] * std::conj(samps[idx]);
            }
            phy_struct->dl_timing_abs_corr[i] += std::norm(corr);
        }
    }

    // Find mean of correlation and gate correlation results
    float corr_mean = 0;
    for(uint32 i=0; i<phy_struct->N_samps_per_slot; i++)
    {
        corr_mean                                                      += phy_struct->dl_timing_abs_corr[i];
        phy_struct->dl_timing_abs_corr[i+phy_struct->N_samps_per_slot]  = phy_struct->dl_timing_abs_corr[i];
    }
    corr_mean /= phy_struct->N_samps_per_slot;
    for(uint32 i=0; i<phy_struct->N_samps_per_slot; i++)
    {
        if(phy_struct->dl_timing_abs_corr[i] <= corr_mean)
        {
            phy_struct->dl_timing_abs_corr[i]                              = 0;
            phy_struct->dl_timing_abs_corr[i+phy_struct->N_samps_per_slot] = 0;
        }
    }

    // Multiply to get (first_symbol * fourth_symbol)
    for(uint32 i=0; i<phy_struct->N_samps_per_slot; i++)
        phy_struct->dl_timing_abs_corr[i] *= phy_struct->dl_timing_abs_corr[(phy_struct->N_samps_per_symb+phy_struct->N_samps_cp_l_0+(phy_struct->N_samps_per_symb+phy_struct->N_samps_cp_l_else)*3)+i];

    // Search for all of the eNB signals
    timing_struct->n_corr_peaks = LIBLTE_PHY_N_MAX_ROUGH_CORR_SEARCH_PEAKS;
    float  abs_corr_idx[LIBLTE_PHY_N_MAX_ROUGH_CORR_SEARCH_PEAKS];
    uint32 N_samps_per_symb_else = phy_struct->N_samps_per_symb + phy_struct->N_samps_cp_l_else;
    uint32 N_samps_to_blank      = N_samps_per_symb_else / 10;
    for(uint32 i=0; i<LIBLTE_PHY_N_MAX_ROUGH_CORR_SEARCH_PEAKS; i++)
    {
        float abs_corr_max = 0;
        abs_corr_idx[i]    = 0;
        for(uint32 j=0; j<phy_struct->N_samps_per_slot; j++)
        {
            if(phy_struct->dl_timing_abs_corr[j] > abs_corr_max)
            {
                abs_corr_max    = phy_struct->dl_timing_abs_corr[j];
                abs_corr_idx[i] = j;
            }
        }

        if(0 == abs_corr_max)
        {
            timing_struct->n_corr_peaks = i;
            break;
        }else{
            // Get rid of max and peaks
            int32 tmp_idx = abs_corr_idx[i];
            while(tmp_idx > 0)
                tmp_idx -= N_samps_per_symb_else;
            for(uint32 j=0; j<7; j++)
            {
                tmp_idx += N_samps_per_symb_else;
                for(uint32 k=0; k<N_samps_to_blank; k++)
                {
                    int32 idx = tmp_idx - (N_samps_to_blank/2) + k;
                    if(idx >= 0 &&
                       idx <= (LIBLTE_PHY_N_SAMPS_PER_SLOT_30_72MHZ*2))
                        phy_struct->dl_timing_abs_corr[idx] = 0;
                }
            }
        }
    }

    // Determine frequency offset
    float freq_err[LIBLTE_PHY_N_MAX_ROUGH_CORR_SEARCH_PEAKS];
    for(uint32 i=0; i<timing_struct->n_corr_peaks; i++)
        freq_err[i] = 0;
    for(uint32 slot=0; slot<N_slots; slot++)
    {
        for(uint32 i=0; i<timing_struct->n_corr_peaks; i++)
        {
            complex corr = complex(0, 0);
            for(uint32 j=0; j<phy_struct->N_samps_cp_l_else; j++)
            {
                uint32 idx  = (slot*phy_struct->N_samps_per_slot) + abs_corr_idx[i] + j;
                corr       += samps[idx+phy_struct->N_samps_per_symb] * std::conj(samps[idx]);
            }
            freq_err[i] += std::arg(corr)/(phy_struct->N_samps_per_symb*2*M_PI*(0.0005/phy_struct->N_samps_per_slot));
        }
    }
    // FIXME: No integer offset is calculated
    for(uint32 i=0; i<timing_struct->n_corr_peaks; i++)
        timing_struct->freq_offset[i] = freq_err[i]/N_slots;

    // Determine the symbol start locations
    for(uint32 i=0; i<timing_struct->n_corr_peaks; i++)
    {
        while(abs_corr_idx[i] > 0)
            abs_corr_idx[i] -= N_samps_per_symb_else;
        for(uint32 j=0; j<7; j++)
            timing_struct->symb_starts[i][j] = abs_corr_idx[i] + ((j+1)*N_samps_per_symb_else);
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_create_dl_subframe

    Description: Creates the baseband signal for a particular
                 downlink subframe

    Document Reference: 3GPP TS 36.211 v10.1.0
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_create_dl_subframe(LIBLTE_PHY_STRUCT          *phy_struct,
                                                LIBLTE_PHY_SUBFRAME_STRUCT *subframe,
                                                uint8                       ant,
                                                complex                    *samps)
{
    if(phy_struct == NULL || subframe == NULL || samps == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Modulate symbols
    uint32 idx     = 0;
    uint32 N_samps = 0;
    for(uint32 i=0; i<14; i++)
    {
        idx += N_samps;
        symbols_to_samples_dl(phy_struct,
                              &subframe->tx_symb[ant][i][0],
                              i,
                              &samps[idx],
                              &N_samps);
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_get_dl_subframe_and_ce

    Description: Resolves all symbols and channel estimates for a
                 particular downlink subframe

    Document Reference: 3GPP TS 36.211 v10.1.0
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_get_dl_subframe_and_ce(LIBLTE_PHY_STRUCT          *phy_struct,
                                                    complex                    *samps,
                                                    uint32                      frame_start_idx,
                                                    uint8                       subfr_num,
                                                    uint32                      N_id_cell,
                                                    uint8                       N_ant,
                                                    LIBLTE_PHY_SUBFRAME_STRUCT *subframe)
{
    if(phy_struct == NULL || samps == NULL || subframe == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;
    if(N_ant != 1 && N_ant != 2 && N_ant != 4)
        return LIBLTE_ERROR_INVALID_INPUTS;

    subframe->num = subfr_num;
    uint32 subfr_start_idx = frame_start_idx + subfr_num*phy_struct->N_samps_per_subfr;
    // Demodulate symbols
    for(uint32 i=0; i<16; i++)
        samples_to_symbols_dl(phy_struct,
                              samps,
                              subfr_start_idx + (i/7)*phy_struct->N_samps_per_slot,
                              i%7,
                              0,
                              &subframe->rx_symb[i][0]);

    // Generate cell specific reference signals
    generate_crs((subfr_num*2+0)%20, 0, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->dl_ce_crs[0]);
    generate_crs((subfr_num*2+0)%20, 1, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->dl_ce_crs[1]);
    generate_crs((subfr_num*2+0)%20, 4, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->dl_ce_crs[4]);
    generate_crs((subfr_num*2+1)%20, 0, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->dl_ce_crs[7]);
    generate_crs((subfr_num*2+1)%20, 1, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->dl_ce_crs[8]);
    generate_crs((subfr_num*2+1)%20, 4, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->dl_ce_crs[11]);
    generate_crs((subfr_num*2+2)%20, 0, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->dl_ce_crs[14]);
    generate_crs((subfr_num*2+2)%20, 1, N_id_cell, phy_struct->N_sc_rb_dl, phy_struct->dl_ce_crs[15]);

    // Determine channel estimates
    for(uint32 p=0; p<N_ant; p++)
    {
        // Define v, sym, and N_sym
        uint32 *v;
        uint32 *sym;
        uint32  N_sym;
        uint32  v_p0[5]      = {0, 3, 0, 3, 0};
        uint32  v_p1[5]      = {3, 0, 3, 0, 3};
        uint32  v_p2[3]      = {0, 3, 0};
        uint32  v_p3[3]      = {3, 6, 3};
        uint32  sym_p0_p1[5] = {0, 4, 7, 11, 14};
        uint32  sym_p2_p3[3] = {1, 8, 15};
        if(p == 0)
        {
            v     = v_p0;
            sym   = sym_p0_p1;
            N_sym = 5;
        }else if(p == 1){
            v     = v_p1;
            sym   = sym_p0_p1;
            N_sym = 5;
        }else if(p == 2){
            v     = v_p2;
            sym   = sym_p2_p3;
            N_sym = 3;
        }else{ // p == 3
            v     = v_p3;
            sym   = sym_p2_p3;
            N_sym = 3;
        }

        float  frac_mag = 0;
        float  frac_ang = 0;
        uint32 v_shift  = N_id_cell % 6;
        for(uint32 i=0; i<N_sym; i++)
        {
            complex *sym_c = &subframe->rx_symb[sym[i]][0];
            complex *rs    = &phy_struct->dl_ce_crs[sym[i]][0];
            uint32   k     = 0;

            for(uint32 j=0; j<2*phy_struct->N_rb_dl; j++)
            {
                k                           = 6*j + (v[i] + v_shift)%6;
                uint32  m_prime             = j + LIBLTE_PHY_N_RB_DL_MAX - phy_struct->N_rb_dl;
                complex tmp                 = sym_c[k] / rs[m_prime];
                phy_struct->dl_ce_mag[i][k] = std::abs(tmp);
                phy_struct->dl_ce_ang[i][k] = std::arg(tmp);

                // Unwrap phase
                if(j > 0)
                {
                    wrap_phase(&phy_struct->dl_ce_ang[i][k], phy_struct->dl_ce_ang[i][k-6]);

                    // Linearly interpolate between CRSs
                    frac_mag = (phy_struct->dl_ce_mag[i][k] - phy_struct->dl_ce_mag[i][k-6])/6;
                    frac_ang = (phy_struct->dl_ce_ang[i][k] - phy_struct->dl_ce_ang[i][k-6])/6;
                    for(uint32 z=1; z<6; z++)
                    {
                        phy_struct->dl_ce_mag[i][k-z] = phy_struct->dl_ce_mag[i][k-(z-1)] - frac_mag;
                        phy_struct->dl_ce_ang[i][k-z] = phy_struct->dl_ce_ang[i][k-(z-1)] - frac_ang;
                    }
                }

                // Linearly interpolate before 1st CRS
                if(j == 1)
                {
                    for(uint32 z=1; z<((v[i] + v_shift)%6)+1; z++)
                    {
                        phy_struct->dl_ce_mag[i][k-6-z] = phy_struct->dl_ce_mag[i][k-6-(z-1)] - frac_mag;
                        phy_struct->dl_ce_ang[i][k-6-z] = phy_struct->dl_ce_ang[i][k-6-(z-1)] - frac_ang;
                    }
                }
            }

            // Linearly interpolate after last CRS
            for(uint32 z=1; z<(5-(v[i] + v_shift)%6)+1; z++)
            {
                phy_struct->dl_ce_mag[i][k+z] = phy_struct->dl_ce_mag[i][k+(z-1)] + frac_mag;
                phy_struct->dl_ce_ang[i][k+z] = phy_struct->dl_ce_ang[i][k+(z-1)] + frac_ang;
            }
        }

        // Linearly interpolate between symbols to construct all channel estimates
        float ce_mag;
        float ce_ang;
        if(N_sym == 3)
        {
            for(uint32 j=0; j<phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl; j++)
            {
                // Construct symbol 1 and 8 channel estimates directly
                subframe->rx_ce[p][1][j] = complex_polar(phy_struct->dl_ce_mag[0][j], phy_struct->dl_ce_ang[0][j]);
                subframe->rx_ce[p][8][j] = complex_polar(phy_struct->dl_ce_mag[1][j], phy_struct->dl_ce_ang[1][j]);

                // Interpolate for symbol 2, 3, 4, 5, 6, and 7 channel estimates
                frac_mag = (phy_struct->dl_ce_mag[1][j] - phy_struct->dl_ce_mag[0][j])/7;
                wrap_phase(&phy_struct->dl_ce_ang[1][j], phy_struct->dl_ce_ang[0][j]);
                frac_ang = (phy_struct->dl_ce_ang[1][j] - phy_struct->dl_ce_ang[0][j]);
                wrap_phase(&frac_ang, 0);
                frac_ang /= 7;
                ce_mag    = phy_struct->dl_ce_mag[1][j];
                ce_ang    = phy_struct->dl_ce_ang[1][j];
                for(uint32 z=7; z>1; z--)
                {
                    ce_mag                   -= frac_mag;
                    ce_ang                   -= frac_ang;
                    subframe->rx_ce[p][z][j]  = complex_polar(ce_mag, ce_ang);
                }

                // Interpolate for symbol 0 channel estimate
                // FIXME: Use previous slot to do this correctly
                ce_mag                   = phy_struct->dl_ce_mag[0][j] - frac_mag;
                ce_ang                   = phy_struct->dl_ce_ang[0][j] - frac_ang;
                subframe->rx_ce[p][0][j] = complex_polar(ce_mag, ce_ang);

                // Interpolate for symbol 9, 10, 11, 12, and 13 channel estimates
                frac_mag = (phy_struct->dl_ce_mag[2][j] - phy_struct->dl_ce_mag[1][j])/7;
                wrap_phase(&phy_struct->dl_ce_ang[2][j], phy_struct->dl_ce_ang[1][j]);
                frac_ang = (phy_struct->dl_ce_ang[2][j] - phy_struct->dl_ce_ang[1][j]);
                wrap_phase(&frac_ang, 0);
                frac_ang /= 7;
                ce_mag    = phy_struct->dl_ce_mag[2][j] - frac_mag;
                ce_ang    = phy_struct->dl_ce_ang[2][j] - frac_ang;
                for(uint32 z=13; z>8; z--)
                {
                    ce_mag                   -= frac_mag;
                    ce_ang                   -= frac_ang;
                    subframe->rx_ce[p][z][j]  = complex_polar(ce_mag, ce_ang);
                }
            }
        }else{
            for(uint32 j=0; j<phy_struct->N_rb_dl*phy_struct->N_sc_rb_dl; j++)
            {
                // Construct symbol 0, 4, 7, and 11 channel estimates directly
                subframe->rx_ce[p][0][j]  = complex_polar(phy_struct->dl_ce_mag[0][j], phy_struct->dl_ce_ang[0][j]);
                subframe->rx_ce[p][4][j]  = complex_polar(phy_struct->dl_ce_mag[1][j], phy_struct->dl_ce_ang[1][j]);
                subframe->rx_ce[p][7][j]  = complex_polar(phy_struct->dl_ce_mag[2][j], phy_struct->dl_ce_ang[2][j]);
                subframe->rx_ce[p][11][j] = complex_polar(phy_struct->dl_ce_mag[3][j], phy_struct->dl_ce_ang[3][j]);

                // Interpolate for symbol 1, 2, and 3 channel estimates
                frac_mag = (phy_struct->dl_ce_mag[1][j] - phy_struct->dl_ce_mag[0][j])/4;
                wrap_phase(&phy_struct->dl_ce_ang[1][j], phy_struct->dl_ce_ang[0][j]);
                frac_ang = (phy_struct->dl_ce_ang[1][j] - phy_struct->dl_ce_ang[0][j]);
                wrap_phase(&frac_ang, 0);
                frac_ang /= 4;
                ce_mag    = phy_struct->dl_ce_mag[1][j];
                ce_ang    = phy_struct->dl_ce_ang[1][j];
                for(uint32 z=3; z>0; z--)
                {
                    ce_mag                   -= frac_mag;
                    ce_ang                   -= frac_ang;
                    subframe->rx_ce[p][z][j]  = complex_polar(ce_mag, ce_ang);
                }

                // Interpolate for symbol 5 and 6 channel estimates
                frac_mag = (phy_struct->dl_ce_mag[2][j] - phy_struct->dl_ce_mag[1][j])/3;
                wrap_phase(&phy_struct->dl_ce_ang[2][j], phy_struct->dl_ce_ang[1][j]);
                frac_ang = (phy_struct->dl_ce_ang[2][j] - phy_struct->dl_ce_ang[1][j]);
                wrap_phase(&frac_ang, 0);
                frac_ang /= 3;
                ce_mag    = phy_struct->dl_ce_mag[2][j];
                ce_ang    = phy_struct->dl_ce_ang[2][j];
                for(uint32 z=6; z>4; z--)
                {
                    ce_mag                   -= frac_mag;
                    ce_ang                   -= frac_ang;
                    subframe->rx_ce[p][z][j]  = complex_polar(ce_mag, ce_ang);
                }

                // Interpolate for symbol 8, 9, and 10 channel estimates
                frac_mag = (phy_struct->dl_ce_mag[3][j] - phy_struct->dl_ce_mag[2][j])/4;
                wrap_phase(&phy_struct->dl_ce_ang[3][j], phy_struct->dl_ce_ang[2][j]);
                frac_ang = (phy_struct->dl_ce_ang[3][j] - phy_struct->dl_ce_ang[2][j]);
                wrap_phase(&frac_ang, 0);
                frac_ang /= 4;
                ce_mag    = phy_struct->dl_ce_mag[3][j];
                ce_ang    = phy_struct->dl_ce_ang[3][j];
                for(uint32 z=10; z>7; z--)
                {
                    ce_mag                   -= frac_mag;
                    ce_ang                   -= frac_ang;
                    subframe->rx_ce[p][z][j]  = complex_polar(ce_mag, ce_ang);
                }

                // Linearly interpolate for symbol 12 and 13 channel estimates
                ce_mag = phy_struct->dl_ce_mag[3][j];
                ce_ang = phy_struct->dl_ce_ang[3][j];
                for(uint32 z=12; z<14; z++)
                {
                    ce_mag                   += frac_mag;
                    ce_ang                   += frac_ang;
                    subframe->rx_ce[p][z][j]  = complex_polar(ce_mag, ce_ang);
                }
            }
        }
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_create_ul_subframe

    Description: Creates the baseband signal for a particular
                 uplink subframe

    Document Reference: 3GPP TS 36.211 v10.1.0
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_create_ul_subframe(LIBLTE_PHY_STRUCT          *phy_struct,
                                                LIBLTE_PHY_SUBFRAME_STRUCT *subframe,
                                                uint8                       ant,
                                                complex                    *samps)
{
    if(phy_struct == NULL || subframe == NULL || samps == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Modulate symbols
    uint32 idx     = 0;
    uint32 N_samps = 0;
    for(uint32 i=0; i<14; i++)
    {
        idx += N_samps;
        symbols_to_samples_ul(phy_struct,
                              &subframe->tx_symb[ant][i][0],
                              i,
                              &samps[idx],
                              &N_samps);
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_get_ul_subframe

    Description: Resolves all symbols for a particular uplink subframe

    Document Reference: 3GPP TS 36.211 v10.1.0
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_get_ul_subframe(LIBLTE_PHY_STRUCT          *phy_struct,
                                             complex                    *samps,
                                             LIBLTE_PHY_SUBFRAME_STRUCT *subframe)
{
    if(phy_struct == NULL || samps == NULL || subframe == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Demodulate symbols
    for(uint32 i=0; i<14; i++)
        samples_to_symbols_ul(phy_struct,
                              samps,
                              (i/7)*phy_struct->N_samps_per_slot,
                              i%7,
                              &subframe->rx_symb[i][0]);

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_get_tbs_mcs_and_n_prb_for_dl

    Description: Determines the transport block size, modulation and
                 coding scheme, and the number of PRBs needed to send
                 the specified number of DL bits

    Document Reference: 3GPP TS 36.213 v10.3.0 section 7.1.7

    NOTES: Currently only supports DCI format 1A
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_get_tbs_mcs_and_n_prb_for_dl(uint32  N_bits,
                                                          uint32  N_subframe,
                                                          uint32  N_rb_dl,
                                                          uint16  rnti,
                                                          uint32 *tbs,
                                                          uint8  *mcs,
                                                          uint32 *N_prb)
{
    if(tbs == NULL || mcs == NULL || N_prb == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    if(LIBLTE_MAC_SI_RNTI        == rnti ||
       LIBLTE_MAC_P_RNTI         == rnti ||
       (LIBLTE_MAC_RA_RNTI_START <= rnti &&
        LIBLTE_MAC_RA_RNTI_END   >= rnti))
    {
        // Choose N_prb == 2 to give the largest possible tbs
        uint32 N_prb_tmp = 2;
        for(uint32 i=0; i<27; i++)
        {
            if(N_bits <= TBS_71721[i][N_prb_tmp])
            {
                *tbs = TBS_71721[i][N_prb_tmp];
                *mcs = i;
                break;
            }
        }
        // Target coding rate is 4:1, will allow down to 3:1
        uint32 N_bits_per_prb = get_num_bits_in_prb(N_subframe, 3, N_rb_dl/2, N_rb_dl, 2, LIBLTE_PHY_MODULATION_TYPE_QPSK);
        *N_prb                = 0;
        for(uint32 code_rate=4; code_rate>2; code_rate--)
        {
            for(uint32 i=1; i<=N_rb_dl; i++)
            {
                if((*tbs * code_rate) < (N_bits_per_prb*i))
                {
                    *N_prb = i;
                    break;
                }
            }
            if(*N_prb != 0)
                break;
        }
        if(*N_prb != 0)
            return LIBLTE_SUCCESS;

        return LIBLTE_ERROR_INVALID_INPUTS;
    }

    *N_prb = 0;
    for(uint32 i=0; i<27; i++)
    {
        uint32 I_tbs;
        for(uint32 j=0; j<N_rb_dl; j++)
        {
            if(N_bits <= TBS_71721[i][j])
            {
                *tbs   = TBS_71721[i][j];
                I_tbs  = i;
                *N_prb = j + 1;
                break;
            }
        }
        if(*N_prb != 0)
        {
            *mcs = get_mcs_from_I_tbs(I_tbs);
            break;
        }
    }
    if(*N_prb != 0)
        return LIBLTE_SUCCESS;
    return LIBLTE_ERROR_INVALID_INPUTS;
}

/*********************************************************************
    Name: liblte_phy_get_tbs_and_n_prb_for_dl

    Description: Determines the transport block size and the number of
                 PRBs needed to send the specified number of DL bits
                 according to the specified modulation and coding
                 scheme

    Document Reference: 3GPP TS 36.213 v10.3.0 section 7.1.7

    NOTES: Currently only supports single layer transport blocks
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_get_tbs_and_n_prb_for_dl(uint32  N_bits,
                                                      uint32  N_rb_dl,
                                                      uint8   mcs,
                                                      uint32 *tbs,
                                                      uint32 *N_prb)
{
    if(tbs == NULL || N_prb == NULL || mcs > 28)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Determine I_tbs
    uint32 I_tbs = get_I_tbs_from_mcs(mcs);

    // Determine N_prb
    for(uint32 i=0; i<N_rb_dl; i++)
        if(N_bits <= TBS_71721[I_tbs][i])
        {
            *tbs   = TBS_71721[I_tbs][i];
            *N_prb = i + 1;
            break;
        }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_get_tbs_mcs_and_n_prb_for_ul

    Description: Determines the transport block size, modulation and
                 coding scheme, and the number of PRBs needed to send
                 the specified number of UL bits

    Document Reference: 3GPP TS 36.213 v10.3.0 section 7.1.7
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_get_tbs_mcs_and_n_prb_for_ul(uint32  N_bits,
                                                          uint32  N_rb_ul,
                                                          uint32 *tbs,
                                                          uint8  *mcs,
                                                          uint32 *N_prb)
{
    if(tbs == NULL || mcs == NULL || N_prb == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Determine I_tbs and N_prb
    uint32 I_tbs = 1000;
    for(uint32 i=0; i<27; i++)
    {
//        for(uint32 j=0; j<N_rb_ul; j++)
        // FIXME: This keeps processing reasonable
        for(uint32 j=0; j<11; j++)
        {
            if(N_bits <= TBS_71721[i][j])
            {
                if(((j + 1) % 2) == 0 ||
                   ((j + 1) % 3) == 0 ||
                   ((j + 1) % 5) == 0)
                {
                    I_tbs  = i;
                    *tbs   = TBS_71721[i][j];
                    *N_prb = j + 1;
                    break;
                }
            }
        }
        if(I_tbs != 1000)
            break;
    }

    if(I_tbs != 1000)
    {
        // Determine mcs
        *mcs = get_mcs_from_I_tbs(I_tbs);
        return LIBLTE_SUCCESS;
    }

    return LIBLTE_ERROR_INVALID_INPUTS;
}

/*********************************************************************
    Name: liblte_phy_get_tbs_and_n_prb_for_ul

    Description: Determines the transport block size and the number of
                 PRBs needed to send the specified number of UL bits
                 according to the specified modulation and coding
                 scheme

    Document Reference: 3GPP TS 36.213 v10.3.0 section 7.1.7
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_get_tbs_and_n_prb_for_ul(uint32  N_bits,
                                                      uint32  N_rb_ul,
                                                      uint8   mcs,
                                                      uint32 *tbs,
                                                      uint32 *N_prb)
{
    if(tbs == NULL || N_prb == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Determine I_tbs
    uint32 I_tbs = get_I_tbs_from_mcs(mcs);

    // Determine N_prb
    for(uint32 i=0; i<N_rb_ul; i++)
        if(N_bits <= TBS_71721[I_tbs][i])
            if(((i + 1) % 2) == 0 ||
               ((i + 1) % 3) == 0 ||
               ((i + 1) % 5) == 0)
            {
                *tbs   = TBS_71721[I_tbs][i];
                *N_prb = i + 1;
                return LIBLTE_SUCCESS;
            }
    return LIBLTE_ERROR_INVALID_INPUTS;
}

/*********************************************************************
    Name: liblte_phy_get_n_cce

    Description: Determines the number of control channel elements
                 available in the specified subframe

    Document Reference: 3GPP TS 36.211 v10.1.0 section 6.8.1
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_phy_get_n_cce(LIBLTE_PHY_STRUCT *phy_struct,
                                       float              phich_res,
                                       uint32             N_pdcch_symbs,
                                       uint8              N_ant,
                                       uint32            *N_cce)
{
    if(phy_struct == NULL || N_cce == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    uint32 N_reg_pcfich = 4;
    uint32 N_reg_rb     = 3;
    uint32 N_reg_phich  = phy_struct->N_group_phich*3;
    uint32 N_reg_pdcch  = N_pdcch_symbs*(phy_struct->N_rb_dl*N_reg_rb) - phy_struct->N_rb_dl - N_reg_pcfich - N_reg_phich;
    if(N_ant == 4)
        N_reg_pdcch -= phy_struct->N_rb_dl;

    *N_cce = N_reg_pdcch/LIBLTE_PHY_PDCCH_N_REG_CCE;

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    Name: liblte_phy_add_to_tti

    Description: Adds the specified amount to a TTI ensuring proper
                 modulo.

    Document Reference: N/A
*********************************************************************/
uint32 liblte_phy_add_to_tti(uint32 tti,
                             uint32 addition)
{
    return (tti + addition) % (LIBLTE_PHY_TTI_MAX + 1);
}

/*********************************************************************
    Name: liblte_phy_sub_from_tti

    Description: Subtracts the specified amount from a TTI ensuring
                 proper modulo.

    Document Reference: N/A
*********************************************************************/
uint32 liblte_phy_sub_from_tti(uint32 tti,
                               uint32 subtraction)
{
    if(subtraction > tti)
        return (tti + LIBLTE_PHY_TTI_MAX + 1) - subtraction;
    return tti - subtraction;
}

/*********************************************************************
    Name: liblte_phy_is_tti_in_future

    Description: Checks if a TTI is in the future compared to a
                 reference TTI.

    Document Reference: N/A
*********************************************************************/
bool liblte_phy_is_tti_in_future(uint32 tti_to_check,
                                 uint32 reference_tti)
{
    int32 tti_diff = reference_tti - tti_to_check;
    if(tti_diff > (LIBLTE_PHY_TTI_MAX / 2))
        tti_diff = reference_tti - (tti_to_check + LIBLTE_PHY_TTI_MAX + 1);
    if(tti_diff < 0)
        return true;
    return false;
}

/*********************************************************************
    Name: liblte_phy_is_tti_in_past

    Description: Checks if a TTI is in the past compared to a
                 reference TTI.

    Document Reference: N/A
*********************************************************************/
bool liblte_phy_is_tti_in_past(uint32 tti_to_check,
                               uint32 reference_tti)
{
    int32 tti_diff = tti_to_check - reference_tti;
    if(tti_diff > (LIBLTE_PHY_TTI_MAX / 2))
        tti_diff = tti_to_check - (reference_tti + LIBLTE_PHY_TTI_MAX + 1);
    if(tti_diff < 0)
        return true;
    return false;
}

/*********************************************************************
    Name: liblte_phy_rate_match_turbo

    Description: Rate matches turbo encoded data

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.4.1
*********************************************************************/
void liblte_phy_rate_match_turbo(LIBLTE_PHY_STRUCT         *phy_struct,
                                 uint8                     *d_bits,
                                 uint32                     N_d_bits,
                                 uint32                     N_codeblocks,
                                 uint32                     tx_mode,
                                 uint32                     N_soft,
                                 uint32                     M_dl_harq,
                                 LIBLTE_PHY_CHAN_TYPE_ENUM  chan_type,
                                 uint32                     rv_idx,
                                 uint32                     N_e_bits,
                                 uint8                     *e_bits)
{
    // Step 1: Assign C_tc_sb to 32
    uint32 C_tc_sb = 32;

    // Sub-block interleaving
    // Step 2: Determine the number of rows
    uint32 R_tc_sb = 0;
    while((N_d_bits/3) > (C_tc_sb*R_tc_sb))
        R_tc_sb++;

    // Steps 3, 4, and 5
    uint32 K_pi;
    for(uint32 x=0; x<3; x++)
    {
        // Step 3: Pack data into matrix and pad with dummy
        uint32 N_dummy = 0;
        if((N_d_bits/3) < (C_tc_sb*R_tc_sb))
            N_dummy = C_tc_sb*R_tc_sb - (N_d_bits/3);
        for(uint32 i=0; i<N_dummy; i++)
            phy_struct->rmt_tmp[i] = TX_NULL_BIT;
        uint32 d_idx = 0;
        for(uint32 i=N_dummy; i<C_tc_sb*R_tc_sb; i++)
        {
            phy_struct->rmt_tmp[i] = d_bits[(N_d_bits/3)*x+d_idx];
            d_idx++;
        }
        uint32 idx = 0;
        for(uint32 i=0; i<R_tc_sb; i++)
            for(uint32 j=0; j<C_tc_sb; j++)
                phy_struct->rmt_sb_mat[i][j] = phy_struct->rmt_tmp[idx++];

        uint32 w_idx = 0;
        if(x != 2)
        {
            // Step 4: Inter-column permutation
            for(uint32 i=0; i<R_tc_sb; i++)
                for(uint32 j=0; j<C_tc_sb; j++)
                    phy_struct->rmt_sb_perm_mat[i][j] = phy_struct->rmt_sb_mat[i][IC_PERM_TC[j]];

            // Step 5: Read out the bits
            K_pi = R_tc_sb*C_tc_sb;
            for(uint32 j=0; j<C_tc_sb; j++)
            {
                for(uint32 i=0; i<R_tc_sb; i++)
                {
                    if(x == 0)
                    {
                        phy_struct->rmt_w[w_idx++] = phy_struct->rmt_sb_perm_mat[i][j];
                    }else{
                        phy_struct->rmt_w[K_pi+(2*w_idx)] = phy_struct->rmt_sb_perm_mat[i][j];
                        w_idx++;
                    }
                }
            }
        }else{
            // Step 4: Permutation for the last output
            K_pi = R_tc_sb*C_tc_sb;
            idx  = 0;
            for(uint32 i=0; i<R_tc_sb; i++)
                for(uint32 j=0; j<C_tc_sb; j++)
                    phy_struct->rmt_y[idx++] = phy_struct->rmt_sb_mat[i][j];
            for(uint32 i=0; i<K_pi; i++)
            {
                uint32 pi_idx                       = (IC_PERM_TC[i/R_tc_sb]+C_tc_sb*(i%R_tc_sb)+1) % K_pi;
                phy_struct->rmt_w[K_pi+(2*w_idx)+1] = phy_struct->rmt_y[pi_idx];
                w_idx++;
            }
        }
    }

    // Bit collection, selection, and transmission
    // Create circular buffer
    uint32 K_w    = 3*K_pi;
    uint32 K_mimo = 1;
    if(tx_mode == 3 || tx_mode == 4 || tx_mode == 8 || tx_mode == 9)
        K_mimo = 2;
    uint32 N_ir = N_soft/(K_mimo*8);
    if(M_dl_harq < 8)
        N_ir = N_soft/(K_mimo*M_dl_harq);
    uint32 N_cb = K_w;
    if(LIBLTE_PHY_CHAN_TYPE_DLSCH == chan_type || LIBLTE_PHY_CHAN_TYPE_PCH == chan_type)
        if((N_ir/N_codeblocks) < K_w)
            N_cb = N_ir/N_codeblocks;
    uint32 k_0 = R_tc_sb*(2*(uint32)ceilf((float)N_cb/(float)(8*R_tc_sb))*rv_idx+2);
    uint32 k   = 0;
    uint32 j   = 0;
    while(k < N_e_bits)
    {
        if(phy_struct->rmt_w[(k_0+j)%N_cb] != TX_NULL_BIT)
            e_bits[k++] = phy_struct->rmt_w[(k_0+j)%N_cb];
        j++;
    }
}

/*********************************************************************
    Name: liblte_phy_rate_unmatch_turbo

    Description: Rate unmatches turbo encoded data

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.4.1
*********************************************************************/
void liblte_phy_rate_unmatch_turbo(LIBLTE_PHY_STRUCT         *phy_struct,
                                   float                     *e_bits,
                                   uint32                     N_e_bits,
                                   uint8                     *dummy_bits,
                                   uint32                     N_dummy_bits,
                                   uint32                     N_codeblocks,
                                   uint32                     tx_mode,
                                   uint32                     N_soft,
                                   uint32                     M_dl_harq,
                                   LIBLTE_PHY_CHAN_TYPE_ENUM  chan_type,
                                   uint32                     rv_idx,
                                   float                     *d_bits,
                                   uint32                    *N_d_bits)
{
    // Step 1: Assign C_tc_sb to 32
    uint32 C_tc_sb = 32;

    // In order to undo bit collection, selection, and transmission
    // a dummy block must be sub-block interleaved to determine
    // where NULL bits are to be inserted
    // Sub-block interleaving
    // Step 2: Determine the number of rows
    uint32 R_tc_sb = 0;
    while(N_dummy_bits > (C_tc_sb*R_tc_sb))
        R_tc_sb++;

    // Steps 3, 4, and 5
    uint32 K_pi;
    for(uint32 x=0; x<3; x++)
    {
        // Step 3: Pack data into matrix and pad with dummy
        uint32 N_dummy = 0;
        if(N_dummy_bits < (C_tc_sb*R_tc_sb))
            N_dummy = C_tc_sb*R_tc_sb - N_dummy_bits;
        for(uint32 i=0; i<N_dummy; i++)
            phy_struct->rut_tmp[i] = RX_NULL_BIT;
        uint32 d_idx = 0;
        for(uint32 i=N_dummy; i<C_tc_sb*R_tc_sb; i++)
        {
            phy_struct->rut_tmp[i] = dummy_bits[N_dummy_bits*x+d_idx];
            d_idx++;
        }
        uint32 idx = 0;
        for(uint32 i=0; i<R_tc_sb; i++)
            for(uint32 j=0; j<C_tc_sb; j++)
                phy_struct->rut_sb_mat[i][j] = phy_struct->rut_tmp[idx++];

        uint32 w_idx = 0;
        if(x != 2)
        {
            // Step 4: Inter-column permutation
            for(uint32 i=0; i<R_tc_sb; i++)
                for(uint32 j=0; j<C_tc_sb; j++)
                    phy_struct->rut_sb_perm_mat[i][j] = phy_struct->rut_sb_mat[i][IC_PERM_TC[j]];

            // Step 5: Read out the bits
            K_pi = R_tc_sb*C_tc_sb;
            for(uint32 j=0; j<C_tc_sb; j++)
            {
                for(uint32 i=0; i<R_tc_sb; i++)
                {
                    if(x == 0)
                    {
                        phy_struct->rut_w_dum[w_idx] = phy_struct->rut_sb_perm_mat[i][j];
                        phy_struct->rut_w[w_idx]     = RX_NULL_BIT;
                        w_idx++;
                    }else{
                        phy_struct->rut_w_dum[K_pi+(2*w_idx)] = phy_struct->rut_sb_perm_mat[i][j];
                        phy_struct->rut_w[K_pi+(2*w_idx)]     = RX_NULL_BIT;
                        w_idx++;
                    }
                }
            }
        }else{
            // Step 4: Permutation for the last output
            K_pi = R_tc_sb*C_tc_sb;
            idx  = 0;
            for(uint32 i=0; i<R_tc_sb; i++)
                for(uint32 j=0; j<C_tc_sb; j++)
                    phy_struct->rut_y[idx++] = phy_struct->rut_sb_mat[i][j];
            for(uint32 i=0; i<K_pi; i++)
            {
                uint32 pi_idx                           = (IC_PERM_TC[i/R_tc_sb]+C_tc_sb*(i%R_tc_sb)+1) % K_pi;
                phy_struct->rut_w_dum[K_pi+(2*w_idx)+1] = phy_struct->rut_y[pi_idx];
                phy_struct->rut_w[K_pi+(2*w_idx)+1]     = RX_NULL_BIT;
                w_idx++;
            }
        }
    }

    // Undo bit collection, selection, and transmission by
    // recreating the circular buffer
    uint32 K_w    = 3*K_pi;
    uint32 K_mimo = 1;
    if(tx_mode == 3 || tx_mode == 4 || tx_mode == 8 || tx_mode == 9)
        K_mimo = 2;
    uint32 N_ir = N_soft/(K_mimo*8);
    if(M_dl_harq < 8)
        N_ir = N_soft/(K_mimo*M_dl_harq);
    uint32 N_cb = K_w;
    if(LIBLTE_PHY_CHAN_TYPE_DLSCH == chan_type || LIBLTE_PHY_CHAN_TYPE_PCH == chan_type)
        if((N_ir/N_codeblocks) < K_w)
            N_cb = N_ir/N_codeblocks;
    uint32 k_0 = R_tc_sb*(2*(uint32)ceilf((float)N_cb/(float)(8*R_tc_sb))*rv_idx+2);
    uint32 k   = 0;
    uint32 j   = 0;
    while(k < N_e_bits)
    {
        if(phy_struct->rut_w_dum[(k_0+j)%N_cb] != RX_NULL_BIT)
        {
            // Soft combine the inputs
            if(phy_struct->rut_w[(k_0+j)%N_cb] == RX_NULL_BIT)
            {
                phy_struct->rut_w[(k_0+j)%N_cb] = e_bits[k];
            }else if(e_bits[k] != RX_NULL_BIT){
                phy_struct->rut_w[(k_0+j)%N_cb] += e_bits[k];
                phy_struct->rut_w[(k_0+j)%N_cb] /= 2;
            }
            k++;
        }
        j++;
    }

    // Sub-block deinterleaving
    // Steps 5, 4, and 3
    uint32 d_idx;
    for(uint32 x=0; x<3; x++)
    {
        uint32 w_idx = 0;
        if(x != 2)
        {
            // Step 5: Load the permuted matrix
            for(j=0; j<C_tc_sb; j++)
            {
                for(uint32 i=0; i<R_tc_sb; i++)
                {
                    if(x == 0)
                    {
                        phy_struct->rut_sb_perm_mat[i][j] = phy_struct->rut_w[w_idx++];
                    }else{
                        phy_struct->rut_sb_perm_mat[i][j] = phy_struct->rut_w[K_pi+(2*w_idx)];
                        w_idx++;
                    }
                }
            }

            // Step 4: Undo permutation
            for(uint32 i=0; i<R_tc_sb; i++)
                for(j=0; j<C_tc_sb; j++)
                    phy_struct->rut_sb_mat[i][IC_PERM_TC[j]] = phy_struct->rut_sb_perm_mat[i][j];
        }else{
            // Step 4: Permutation for the last output
            for(uint32 i=0; i<K_pi; i++)
            {
                uint32 pi_idx             = (IC_PERM_TC[i/R_tc_sb]+C_tc_sb*(i%R_tc_sb)+1) % K_pi;
                phy_struct->rut_y[pi_idx] = phy_struct->rut_w[K_pi+(2*w_idx)+1];
                w_idx++;
            }
            uint32 idx = 0;
            for(uint32 i=0; i<R_tc_sb; i++)
                for(j=0; j<C_tc_sb; j++)
                    phy_struct->rut_sb_mat[i][j] = phy_struct->rut_y[idx++];
        }

        // Step 3: Unpack the data and remove dummy
        uint32 N_dummy = 0;
        if(N_dummy_bits < (C_tc_sb*R_tc_sb))
            N_dummy = C_tc_sb*R_tc_sb - N_dummy_bits;
        uint32 idx = 0;
        for(uint32 i=0; i<R_tc_sb; i++)
            for(j=0; j<C_tc_sb; j++)
                phy_struct->rut_tmp[idx++] = phy_struct->rut_sb_mat[i][j];
        d_idx     = 0;
        *N_d_bits = ((C_tc_sb*R_tc_sb)-N_dummy)*3;
        for(uint32 i=N_dummy; i<C_tc_sb*R_tc_sb; i++)
        {
            d_bits[(*N_d_bits/3)*x+d_idx] = phy_struct->rut_tmp[i];
            d_idx++;
        }
    }
}

/*********************************************************************
    Name: liblte_phy_code_block_segmentation

    Description: Performs code block segmentation for turbo coded
                 channels

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.2
*********************************************************************/
void liblte_phy_code_block_segmentation(uint8                    *b_bits,
                                        uint32                    N_b_bits,
                                        uint32                   *N_codeblocks,
                                        uint32                   *N_filler_bits,
                                        LIBLTE_PHY_C_BITS_STRUCT *c)
{
    // Determine L, C, B', K+, C+, K-, and C-
    uint32 L;
    uint32 B_prime;
    uint32 K_plus;
    uint32 C_plus;
    uint32 K_minus;
    uint32 C_minus;
    get_code_block_segmentation_parameters(N_b_bits, &L, N_codeblocks, &B_prime, &K_plus,
                                           &C_plus,  &K_minus, &C_minus, N_filler_bits);

    // Add filler bits
    for(uint32 i=0; i<*N_filler_bits; i++)
        c->bits[0][i] = TX_NULL_SYMB;

    // Add the input bits
    uint32 k = *N_filler_bits;
    uint32 s = 0;
    for(uint32 r=0; r<*N_codeblocks; r++)
    {
        // Determine the K for this code block
        uint32 K_r = K_plus;
        if(r < C_minus)
            K_r = K_minus;
        c->N_bits[r] = K_r;

        // Add the input bits
        while(k < (K_r - L))
            c->bits[r][k++] = b_bits[s++];

        // Add CRC if more than 1 code block is needed
        if(*N_codeblocks > 1)
        {
            uint8 p_cb_bits[24];
            calc_crc(c->bits[r], c->N_bits[r]-L, CRC24B, p_cb_bits, L);
            while(k < K_r)
            {
                c->bits[r][k] = p_cb_bits[k+L-K_r];
                k++;
            }
        }
        k = 0;
    }
}

/*********************************************************************
    Name: liblte_phy_code_block_desegmentation

    Description: Performs code block desegmentation for turbo coded
                 channels

    Document Reference: 3GPP TS 36.212 v10.1.0 section 5.1.2
*********************************************************************/
void liblte_phy_code_block_desegmentation(LIBLTE_PHY_C_BITS_STRUCT *c,
                                          uint32                    tbs,
                                          uint8                    *b_bits,
                                          uint32                    N_b_bits)
{
    // Determine L, C, B', K+, C+, K-, and C-
    uint32 L;
    uint32 C;
    uint32 B_prime;
    uint32 K_plus;
    uint32 C_plus;
    uint32 K_minus;
    uint32 C_minus;
    uint32 F;
    get_code_block_segmentation_parameters(N_b_bits, &L, &C, &B_prime, &K_plus, &C_plus,
                                           &K_minus, &C_minus, &F);

    // Determine the output bits
    uint32 k = F;
    uint32 s = 0;
    for(uint32 r=0; r<C; r++)
    {
        // Determine the K for this code block
        uint32 K_r = K_plus;
        if(r < C_minus)
            K_r = K_minus;

        // Check CRC if more than 1 code block is present
        if(C > 1)
        {
            uint8 calc_p_cb_bits[24];
            calc_crc(c->bits[r], c->N_bits[r]-L, CRC24B, calc_p_cb_bits, L);
            uint8  *p_cb_bits = &c->bits[r][c->N_bits[r]-L];
            if(0 == check_crc(p_cb_bits, calc_p_cb_bits, L))
            {
                printf("CB CRC CORRECT\n");
            }else{
                printf("CB CRC INCORRECT\n");
            }
        }

        // Create the output bits
        while(k < (K_r - L))
            b_bits[s++] = c->bits[r][k++];
        k = 0;
    }
}
