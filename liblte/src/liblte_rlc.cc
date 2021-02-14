/*******************************************************************************

    Copyright 2014-2017, 2021 Ben Wojtowicz

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

    File: liblte_rlc.cc

    Description: Contains all the implementations for the LTE Radio Link
                 Control Layer library.

    Revision History
    ----------    -------------    --------------------------------------------
    06/15/2014    Ben Wojtowicz    Created file.
    08/03/2014    Ben Wojtowicz    Added NACK support and using the common
                                   value_2_bits and bits_2_value functions.
    11/29/2014    Ben Wojtowicz    Added UMD support and using the byte message
                                   struct.
    02/15/2015    Ben Wojtowicz    Added header extension handling to UMD.
    03/11/2015    Ben Wojtowicz    Added header extension handling to AMD.
    12/06/2015    Ben Wojtowicz    Added a return to unpack status PDU, thanks
                                   to Mikhail Gudkov for reporting this.
    07/03/2016    Ben Wojtowicz    Added AMD PDU segment support.
    12/18/2016    Ben Wojtowicz    Properly handling multiple AMD PDUs.
    07/29/2017    Ben Wojtowicz    Properly handle FI flags for multiple AMD
                                   PDUs.
    02/14/2021    Ben Wojtowicz    Massive reformat.

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
                              PDU FUNCTIONS
*******************************************************************************/

/*********************************************************************
    PDU Type: Unacknowledged Mode Data PDU

    Document Reference: 36.322 v10.0.0 Section 6.2.1.3
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_rlc_pack_umd_pdu(LIBLTE_RLC_UMD_PDU_STRUCT *umd,
                                          LIBLTE_BYTE_MSG_STRUCT    *pdu)
{
    if(umd == NULL || pdu == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    if(1 == umd->N_data)
        return liblte_rlc_pack_umd_pdu(umd, &umd->data[0], pdu);

    // Header
    uint8 *pdu_ptr = pdu->msg;
    if(LIBLTE_RLC_UMD_SN_SIZE_5_BITS == umd->hdr.sn_size)
    {
        *pdu_ptr  = (umd->hdr.fi & 0x03) << 6;
        *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_EXTENDED & 0x01) << 5;
        *pdu_ptr |= umd->hdr.sn & 0x1F;
        pdu_ptr++;
    }else{
        *pdu_ptr  = (umd->hdr.fi & 0x03) << 3;
        *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_EXTENDED & 0x01) << 2;
        *pdu_ptr |= (umd->hdr.sn & 0x300) >> 8;
        pdu_ptr++;
        *pdu_ptr = umd->hdr.sn & 0xFF;
        pdu_ptr++;
    }
    for(uint32 i=0; i<umd->N_data-1; i++)
    {
        if((i % 2) == 0)
        {
            *pdu_ptr = (LIBLTE_RLC_E_FIELD_HEADER_NOT_EXTENDED & 0x01) << 7;
            if(i != umd->N_data-2)
                *pdu_ptr = (LIBLTE_RLC_E_FIELD_HEADER_EXTENDED & 0x01) << 7;
            *pdu_ptr |= (umd->data[i].N_bytes & 0x7F0) >> 4;
            pdu_ptr++;
            *pdu_ptr = (umd->data[i].N_bytes & 0x00F) << 4;
        }else{
            *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_NOT_EXTENDED & 0x01) << 3;
            if(i != umd->N_data-2)
                *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_EXTENDED & 0x01) << 3;
            *pdu_ptr |= (umd->data[i].N_bytes & 0x700) >> 8;
            pdu_ptr++;
            *pdu_ptr = umd->data[i].N_bytes & 0x0FF;
            pdu_ptr++;
        }
    }
    if((umd->N_data % 2) == 0)
        pdu_ptr++;

    // Data
    for(uint32 i=0; i<umd->N_data; i++)
    {
        memcpy(pdu_ptr, umd->data[i].msg, umd->data[i].N_bytes);
        pdu_ptr += umd->data[i].N_bytes;
    }

    // Fill in the number of bytes used
    pdu->N_bytes = pdu_ptr - pdu->msg;

    return LIBLTE_SUCCESS;
}
LIBLTE_ERROR_ENUM liblte_rlc_pack_umd_pdu(LIBLTE_RLC_UMD_PDU_STRUCT *umd,
                                          LIBLTE_BYTE_MSG_STRUCT    *data,
                                          LIBLTE_BYTE_MSG_STRUCT    *pdu)
{
    if(umd == NULL || data == NULL || pdu == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Header
    uint8 *pdu_ptr = pdu->msg;
    if(LIBLTE_RLC_UMD_SN_SIZE_5_BITS == umd->hdr.sn_size)
    {
        *pdu_ptr  = (umd->hdr.fi & 0x03) << 6;
        *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_NOT_EXTENDED & 0x01) << 5;
        *pdu_ptr |= umd->hdr.sn & 0x1F;
        pdu_ptr++;
    }else{
        *pdu_ptr  = (umd->hdr.fi & 0x03) << 3;
        *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_NOT_EXTENDED & 0x01) << 2;
        *pdu_ptr |= (umd->hdr.sn & 0x300) >> 8;
        pdu_ptr++;
        *pdu_ptr = umd->hdr.sn & 0xFF;
        pdu_ptr++;
    }

    // Data
    memcpy(pdu_ptr, data->msg, data->N_bytes);
    pdu_ptr += data->N_bytes;

    // Fill in the number of bytes used
    pdu->N_bytes = pdu_ptr - pdu->msg;

    return LIBLTE_SUCCESS;
}
LIBLTE_ERROR_ENUM liblte_rlc_unpack_umd_pdu(LIBLTE_BYTE_MSG_STRUCT    *pdu,
                                            LIBLTE_RLC_UMD_PDU_STRUCT *umd)
{
    if(pdu == NULL || umd == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Header
    LIBLTE_RLC_E_FIELD_ENUM  e;
    uint8                   *pdu_ptr = pdu->msg;
    if(LIBLTE_RLC_UMD_SN_SIZE_5_BITS == umd->hdr.sn_size)
    {
        umd->hdr.fi = (LIBLTE_RLC_FI_FIELD_ENUM)((*pdu_ptr >> 6) & 0x03);
        e           = (LIBLTE_RLC_E_FIELD_ENUM)((*pdu_ptr >> 5) & 0x01);
        umd->hdr.sn = *pdu_ptr & 0x1F;
        pdu_ptr++;
    }else{
        umd->hdr.fi = (LIBLTE_RLC_FI_FIELD_ENUM)((*pdu_ptr >> 3) & 0x03);
        e           = (LIBLTE_RLC_E_FIELD_ENUM)((*pdu_ptr >> 2) & 0x01);
        umd->hdr.sn = (*pdu_ptr & 0x03) << 8;
        pdu_ptr++;
        umd->hdr.sn |= *pdu_ptr;
        pdu_ptr++;
    }

    umd->N_data     = 0;
    uint32 data_len = 0;
    while(LIBLTE_RLC_E_FIELD_HEADER_EXTENDED == e)
    {
        if(LIBLTE_RLC_UMD_MAX_N_DATA == umd->N_data)
        {
            printf("TOO MANY LI FIELDS\n");
            return LIBLTE_ERROR_INVALID_INPUTS;
        }
        if((umd->N_data % 2) == 0)
        {
            e                              = (LIBLTE_RLC_E_FIELD_ENUM)((*pdu_ptr >> 7) & 0x01);
            umd->data[umd->N_data].N_bytes = (*pdu_ptr & 0x7F) << 4;
            pdu_ptr++;
            umd->data[umd->N_data].N_bytes |= (*pdu_ptr & 0xF0) >> 4;
        }else{
            e                              = (LIBLTE_RLC_E_FIELD_ENUM)((*pdu_ptr >> 3) & 0x01);
            umd->data[umd->N_data].N_bytes = (*pdu_ptr & 0x07) << 8;
            pdu_ptr++;
            umd->data[umd->N_data].N_bytes |= *pdu_ptr;
            pdu_ptr++;
        }
        data_len += umd->data[umd->N_data].N_bytes;
        umd->N_data++;
    }
    if(LIBLTE_RLC_UMD_MAX_N_DATA == umd->N_data)
    {
        printf("TOO MANY LI FIELDS\n");
        return LIBLTE_ERROR_INVALID_INPUTS;
    }
    umd->N_data++;
    if((umd->N_data % 2) == 0)
        pdu_ptr++;
    umd->data[umd->N_data-1].N_bytes = pdu->N_bytes - (pdu_ptr - pdu->msg) - data_len;

    // Data
    for(uint32 i=0; i<umd->N_data; i++)
    {
        memcpy(umd->data[i].msg, pdu_ptr, umd->data[i].N_bytes);
        pdu_ptr += umd->data[i].N_bytes;
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    PDU Type: Acknowledged Mode Data PDU

    Document Reference: 36.322 v10.0.0 Sections 6.2.1.4 & 6.2.1.5
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_rlc_pack_amd_pdu(LIBLTE_RLC_AMD_PDUS_STRUCT *amd,
                                          LIBLTE_BYTE_MSG_STRUCT     *pdu)
{
    if(amd == NULL || pdu == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    if(1 == amd->N_pdu)
        return liblte_rlc_pack_amd_pdu(&amd->pdu[0], &amd->pdu[0].data, pdu);

    // Header
    uint8 *pdu_ptr = pdu->msg;
    *pdu_ptr  = (amd->pdu[0].hdr.dc & 0x01) << 7;
    *pdu_ptr |= (amd->pdu[0].hdr.rf & 0x01) << 6;
    *pdu_ptr |= (amd->pdu[0].hdr.p & 0x01) << 5;
    *pdu_ptr |= (amd->pdu[0].hdr.fi & 0x03) << 3;
    *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_EXTENDED & 0x01) << 2;
    *pdu_ptr |= (amd->pdu[0].hdr.sn & 0x300) >> 8;
    pdu_ptr++;
    *pdu_ptr = amd->pdu[0].hdr.sn & 0xFF;
    pdu_ptr++;
    for(uint32 i=0; i<amd->N_pdu-1; i++)
    {
        if((i % 2) == 0)
        {
            *pdu_ptr = (LIBLTE_RLC_E_FIELD_HEADER_NOT_EXTENDED & 0x01) << 7;
            if(i != amd->N_pdu-2)
                *pdu_ptr = (LIBLTE_RLC_E_FIELD_HEADER_EXTENDED & 0x01) << 7;
            *pdu_ptr |= (amd->pdu[i].data.N_bytes & 0x7F0) >> 4;
            pdu_ptr++;
            *pdu_ptr = (amd->pdu[i].data.N_bytes & 0x00F) << 4;
        }else{
            *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_NOT_EXTENDED & 0x01) << 3;
            if(i != amd->N_pdu-2)
                *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_EXTENDED & 0x01) << 3;
            *pdu_ptr |= (amd->pdu[i].data.N_bytes & 0x700) >> 8;
            pdu_ptr++;
            *pdu_ptr = amd->pdu[i].data.N_bytes & 0x0FF;
            pdu_ptr++;
        }
    }
    if((amd->N_pdu % 2) == 0)
        pdu_ptr++;

    // Data
    for(uint32 i=0; i<amd->N_pdu; i++)
    {
        memcpy(pdu_ptr, amd->pdu[i].data.msg, amd->pdu[i].data.N_bytes);
        pdu_ptr += amd->pdu[i].data.N_bytes;
    }

    // Fill in the number of bytes used
    pdu->N_bytes = pdu_ptr - pdu->msg;

    return LIBLTE_SUCCESS;
}
LIBLTE_ERROR_ENUM liblte_rlc_pack_amd_pdu(LIBLTE_RLC_SINGLE_AMD_PDU_STRUCT *amd,
                                          LIBLTE_BYTE_MSG_STRUCT           *data,
                                          LIBLTE_BYTE_MSG_STRUCT           *pdu)
{
    if(amd == NULL || data == NULL || pdu == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Header
    uint8 *pdu_ptr = pdu->msg;
    *pdu_ptr  = (amd->hdr.dc & 0x01) << 7;
    *pdu_ptr |= (amd->hdr.rf & 0x01) << 6;
    *pdu_ptr |= (amd->hdr.p & 0x01) << 5;
    *pdu_ptr |= (amd->hdr.fi & 0x03) << 3;
    *pdu_ptr |= (LIBLTE_RLC_E_FIELD_HEADER_NOT_EXTENDED & 0x01) << 2;
    *pdu_ptr |= (amd->hdr.sn & 0x300) >> 8;
    pdu_ptr++;
    *pdu_ptr = amd->hdr.sn & 0xFF;
    pdu_ptr++;
    if(LIBLTE_RLC_RF_FIELD_AMD_PDU_SEGMENT == amd->hdr.rf)
    {
        *pdu_ptr  = (amd->hdr.lsf & 0x01) << 7;
        *pdu_ptr |= (amd->hdr.so & 0x7F00) >> 8;
        pdu_ptr++;
        *pdu_ptr = amd->hdr.so & 0xFF;
    }

    // Data
    memcpy(pdu_ptr, data->msg, data->N_bytes);
    pdu_ptr += data->N_bytes;

    // Fill in the number of bytes used
    pdu->N_bytes = pdu_ptr - pdu->msg;

    return LIBLTE_SUCCESS;
}
LIBLTE_ERROR_ENUM liblte_rlc_unpack_amd_pdu(LIBLTE_BYTE_MSG_STRUCT     *pdu,
                                            LIBLTE_RLC_AMD_PDUS_STRUCT *amd)
{
    if(pdu == NULL || amd == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Header
    uint8 *pdu_ptr = pdu->msg;
    amd->pdu[0].hdr.dc = (LIBLTE_RLC_DC_FIELD_ENUM)((*pdu_ptr >> 7) & 0x01);

    if(LIBLTE_RLC_DC_FIELD_DATA_PDU != amd->pdu[0].hdr.dc)
        return LIBLTE_ERROR_INVALID_INPUTS;

    // Header
    amd->pdu[0].hdr.rf        = (LIBLTE_RLC_RF_FIELD_ENUM)((*pdu_ptr >> 6) & 0x01);
    amd->pdu[0].hdr.p         = (LIBLTE_RLC_P_FIELD_ENUM)((*pdu_ptr >> 5) & 0x01);
    amd->pdu[0].hdr.fi        = (LIBLTE_RLC_FI_FIELD_ENUM)((*pdu_ptr >> 3) & 0x03);
    LIBLTE_RLC_E_FIELD_ENUM e = (LIBLTE_RLC_E_FIELD_ENUM)((*pdu_ptr >> 2) & 0x01);
    amd->pdu[0].hdr.sn        = (*pdu_ptr & 0x03) << 8;
    pdu_ptr++;
    amd->pdu[0].hdr.sn |= *pdu_ptr;
    pdu_ptr++;
    if(LIBLTE_RLC_RF_FIELD_AMD_PDU_SEGMENT == amd->pdu[0].hdr.rf)
    {
        amd->pdu[0].hdr.lsf = (LIBLTE_RLC_LSF_FIELD_ENUM)((*pdu_ptr >> 7) & 0x01);
        amd->pdu[0].hdr.so  = (*pdu_ptr & 0x7F) << 8;
        pdu_ptr++;
        amd->pdu[0].hdr.so |= *pdu_ptr;
    }

    amd->N_pdu      = 0;
    uint32 data_len = 0;
    while(LIBLTE_RLC_E_FIELD_HEADER_EXTENDED == e)
    {
        if(LIBLTE_RLC_AMD_MAX_N_PDU == amd->N_pdu)
        {
            printf("TOO MANY LI FIELDS\n");
            return LIBLTE_ERROR_INVALID_INPUTS;
        }
        if((amd->N_pdu % 2) == 0)
        {
            e                                 = (LIBLTE_RLC_E_FIELD_ENUM)((*pdu_ptr >> 7) & 0x01);
            amd->pdu[amd->N_pdu].data.N_bytes = (*pdu_ptr & 0x7F) << 4;
            pdu_ptr++;
            amd->pdu[amd->N_pdu].data.N_bytes |= (*pdu_ptr & 0xF0) >> 4;
        }else{
            e                                 = (LIBLTE_RLC_E_FIELD_ENUM)((*pdu_ptr >> 3) & 0x01);
            amd->pdu[amd->N_pdu].data.N_bytes = (*pdu_ptr & 0x07) << 8;
            pdu_ptr++;
            amd->pdu[amd->N_pdu].data.N_bytes |= *pdu_ptr;
            pdu_ptr++;
        }
        data_len += amd->pdu[amd->N_pdu].data.N_bytes;
        amd->N_pdu++;
    }
    if(LIBLTE_RLC_AMD_MAX_N_PDU == amd->N_pdu)
    {
        printf("TOO MANY LI FIELDS\n");
        return LIBLTE_ERROR_INVALID_INPUTS;
    }
    amd->N_pdu++;
    if((amd->N_pdu % 2) == 0)
        pdu_ptr++;
    amd->pdu[amd->N_pdu-1].data.N_bytes = pdu->N_bytes - (pdu_ptr - pdu->msg) - data_len;

    // Data
    for(uint32 i=0; i<amd->N_pdu; i++)
    {
        // Blindly copy the original header to all PDUs
        if(0 != i)
            memcpy(&amd->pdu[i].hdr, &amd->pdu[0].hdr, sizeof(amd->pdu[i].hdr));
        memcpy(amd->pdu[i].data.msg, pdu_ptr, amd->pdu[i].data.N_bytes);
        pdu_ptr += amd->pdu[i].data.N_bytes;
    }

    // Fix the FI field in all headers
    if(1 != amd->N_pdu)
    {
        // Check to see if it is a first segment
        if(LIBLTE_RLC_FI_FIELD_FIRST_SDU_SEGMENT == amd->pdu[0].hdr.fi ||
           LIBLTE_RLC_FI_FIELD_FULL_SDU          == amd->pdu[0].hdr.fi)
        {
            amd->pdu[0].hdr.fi = LIBLTE_RLC_FI_FIELD_FULL_SDU;
        }else{
            // Assume the first PDU is a last segment
            amd->pdu[0].hdr.fi = LIBLTE_RLC_FI_FIELD_LAST_SDU_SEGMENT;
        }

        // Check to see if it is a full segment
        if(LIBLTE_RLC_FI_FIELD_LAST_SDU_SEGMENT == amd->pdu[amd->N_pdu-1].hdr.fi ||
           LIBLTE_RLC_FI_FIELD_FULL_SDU         == amd->pdu[amd->N_pdu-1].hdr.fi)
        {
            amd->pdu[amd->N_pdu-1].hdr.fi = LIBLTE_RLC_FI_FIELD_FULL_SDU;
        }else{
            // Assume that the last PDU is a first segment
            amd->pdu[amd->N_pdu-1].hdr.fi = LIBLTE_RLC_FI_FIELD_FIRST_SDU_SEGMENT;
        }

        // All other PDUs must be full
        for(uint32 i=1; i<amd->N_pdu-1; i++)
            amd->pdu[i].hdr.fi = LIBLTE_RLC_FI_FIELD_FULL_SDU;
    }

    return LIBLTE_SUCCESS;
}

/*********************************************************************
    PDU Type: Status PDU

    Document Reference: 36.322 v10.0.0 Section 6.2.1.6
*********************************************************************/
LIBLTE_ERROR_ENUM liblte_rlc_pack_status_pdu(LIBLTE_RLC_STATUS_PDU_STRUCT *status,
                                             LIBLTE_BYTE_MSG_STRUCT       *pdu)
{
    if(status == NULL || pdu == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    LIBLTE_BIT_MSG_STRUCT  tmp_pdu;
    uint8                 *pdu_ptr = tmp_pdu.msg;

    // D/C Field
    liblte_value_2_bits(LIBLTE_RLC_DC_FIELD_CONTROL_PDU, &pdu_ptr, 1);

    // CPT Field
    liblte_value_2_bits(LIBLTE_RLC_CPT_FIELD_STATUS_PDU, &pdu_ptr, 3);

    // ACK SN
    liblte_value_2_bits(status->ack_sn, &pdu_ptr, 10);

    // E1
    if(status->N_nack == 0)
    {
        liblte_value_2_bits(LIBLTE_RLC_E1_FIELD_NOT_EXTENDED, &pdu_ptr, 1);
    }else{
        liblte_value_2_bits(LIBLTE_RLC_E1_FIELD_EXTENDED, &pdu_ptr, 1);
    }

    for(uint32 i=0; i<status->N_nack; i++)
    {
        // NACK SN
        liblte_value_2_bits(status->nack_sn[i], &pdu_ptr, 10);

        // E1
        if(i == (status->N_nack-1))
        {
            liblte_value_2_bits(LIBLTE_RLC_E1_FIELD_NOT_EXTENDED, &pdu_ptr, 1);
        }else{
            liblte_value_2_bits(LIBLTE_RLC_E1_FIELD_EXTENDED, &pdu_ptr, 1);
        }

        // E2
        liblte_value_2_bits(LIBLTE_RLC_E2_FIELD_NOT_EXTENDED, &pdu_ptr, 1);

        // FIXME: Skipping SOstart and SOend
    }

    tmp_pdu.N_bits = pdu_ptr - tmp_pdu.msg;

    // Padding
    if((tmp_pdu.N_bits % 8) != 0)
    {
        for(uint32 i=0; i<(8 - (tmp_pdu.N_bits % 8)); i++)
            liblte_value_2_bits(0, &pdu_ptr, 1);
        tmp_pdu.N_bits = pdu_ptr - tmp_pdu.msg;
    }

    // Convert from bit to byte struct
    pdu_ptr = tmp_pdu.msg;
    for(uint32 i=0; i<tmp_pdu.N_bits/8; i++)
        pdu->msg[i] = liblte_bits_2_value(&pdu_ptr, 8);
    pdu->N_bytes = tmp_pdu.N_bits/8;

    return LIBLTE_SUCCESS;
}
LIBLTE_ERROR_ENUM liblte_rlc_unpack_status_pdu(LIBLTE_BYTE_MSG_STRUCT       *pdu,
                                               LIBLTE_RLC_STATUS_PDU_STRUCT *status)
{
    if(pdu == NULL || status == NULL)
        return LIBLTE_ERROR_INVALID_INPUTS;

    LIBLTE_BIT_MSG_STRUCT  tmp_pdu;
    uint8                 *pdu_ptr = tmp_pdu.msg;

    // Convert from byte to bit struct
    for(uint32 i=0; i<pdu->N_bytes; i++)
        liblte_value_2_bits(pdu->msg[i], &pdu_ptr, 8);
    tmp_pdu.N_bits = pdu->N_bytes*8;
    pdu_ptr        = tmp_pdu.msg;

    // D/C Field
    if(LIBLTE_RLC_DC_FIELD_CONTROL_PDU != (LIBLTE_RLC_DC_FIELD_ENUM)liblte_bits_2_value(&pdu_ptr, 1))
        return LIBLTE_ERROR_INVALID_INPUTS;

    // CPT Field
    if(LIBLTE_RLC_CPT_FIELD_STATUS_PDU != liblte_bits_2_value(&pdu_ptr, 3))
        return LIBLTE_ERROR_INVALID_INPUTS;

    status->ack_sn             = liblte_bits_2_value(&pdu_ptr, 10);
    LIBLTE_RLC_E1_FIELD_ENUM e = (LIBLTE_RLC_E1_FIELD_ENUM)liblte_bits_2_value(&pdu_ptr, 1);
    status->N_nack             = 0;
    while(LIBLTE_RLC_E1_FIELD_EXTENDED == e)
    {
        status->nack_sn[status->N_nack++] = liblte_bits_2_value(&pdu_ptr, 10);
        e                                 = (LIBLTE_RLC_E1_FIELD_ENUM)liblte_bits_2_value(&pdu_ptr, 1);
        // FIXME: Skipping SOstart and SOend
        if(LIBLTE_RLC_E2_FIELD_EXTENDED == liblte_bits_2_value(&pdu_ptr, 1))
            liblte_bits_2_value(&pdu_ptr, 29);
    }

    return LIBLTE_SUCCESS;
}
