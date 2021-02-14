// Copyright 2021 Ben Wojtowicz
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "RedirectedCarrierInfo.h"

#include <cmath>

int RedirectedCarrierInfo::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("RedirectedCarrierInfo::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator
    bits.push_back(0);

    // Choice
    for(uint32_t i=0; i<3; i++)
        bits.push_back((internal_choice >> (3-i-1)) & 1);

    // Fields
    if(internal_choice == k_eutra)
    {
        if(0 != eutra.Pack(bits))
        {
            printf("RedirectedCarrierInfo::eutra pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_geran)
    {
        if(0 != geran.Pack(bits))
        {
            printf("RedirectedCarrierInfo::geran pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_utra_FDD)
    {
        if(0 != utra_FDD.Pack(bits))
        {
            printf("RedirectedCarrierInfo::utra_FDD pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_utra_TDD)
    {
        if(0 != utra_TDD.Pack(bits))
        {
            printf("RedirectedCarrierInfo::utra_TDD pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_cdma2000_HRPD)
    {
        if(0 != cdma2000_HRPD.Pack(bits))
        {
            printf("RedirectedCarrierInfo::cdma2000_HRPD pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_cdma2000_1xRTT)
    {
        if(0 != cdma2000_1xRTT.Pack(bits))
        {
            printf("RedirectedCarrierInfo::cdma2000_1xRTT pack failure\n");
            return -1;
        }
    }
    return 0;
}

int RedirectedCarrierInfo::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RedirectedCarrierInfo::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RedirectedCarrierInfo::Unpack() index out of bounds for extension\n");
        return -1;
    }
    idx++;

    // Choice
    uint32_t packed_val = 0;
    if((idx + 3) > bits.size())
    {
        printf("RedirectedCarrierInfo::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<3; i++)
        packed_val |= bits[idx++] << (3-i-1);

    if((RedirectedCarrierInfo::Enum)packed_val > k_cdma2000_1xRTT)
    {
        printf("RedirectedCarrierInfo::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (RedirectedCarrierInfo::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_eutra)
    {
        if(0 != eutra.Unpack(bits, idx))
        {
            printf("RedirectedCarrierInfo::eutra unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_geran)
    {
        if(0 != geran.Unpack(bits, idx))
        {
            printf("RedirectedCarrierInfo::geran unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_utra_FDD)
    {
        if(0 != utra_FDD.Unpack(bits, idx))
        {
            printf("RedirectedCarrierInfo::utra_FDD unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_utra_TDD)
    {
        if(0 != utra_TDD.Unpack(bits, idx))
        {
            printf("RedirectedCarrierInfo::utra_TDD unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_cdma2000_HRPD)
    {
        if(0 != cdma2000_HRPD.Unpack(bits, idx))
        {
            printf("RedirectedCarrierInfo::cdma2000_HRPD unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_cdma2000_1xRTT)
    {
        if(0 != cdma2000_1xRTT.Unpack(bits, idx))
        {
            printf("RedirectedCarrierInfo::cdma2000_1xRTT unpack failure\n");
            return -1;
        }
    }
    return 0;
}

RedirectedCarrierInfo::Enum RedirectedCarrierInfo::Choice() const
{
    if(present)
        return internal_choice;
    return (RedirectedCarrierInfo::Enum)0;
}

int RedirectedCarrierInfo::SetChoice(RedirectedCarrierInfo::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string RedirectedCarrierInfo::ChoiceToString(Enum value) const
{
    if(k_eutra == value)
        return "eutra";
    if(k_geran == value)
        return "geran";
    if(k_utra_FDD == value)
        return "utra_FDD";
    if(k_utra_TDD == value)
        return "utra_TDD";
    if(k_cdma2000_HRPD == value)
        return "cdma2000_HRPD";
    if(k_cdma2000_1xRTT == value)
        return "cdma2000_1xRTT";
    return "";
}

uint64_t RedirectedCarrierInfo::NumberOfChoices() const
{
    return 6;
}

std::string RedirectedCarrierInfo::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RedirectedCarrierInfo = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_eutra)
        out += eutra.ToString(indent+1);
    if(internal_choice == k_geran)
        out += geran.ToString(indent+1);
    if(internal_choice == k_utra_FDD)
        out += utra_FDD.ToString(indent+1);
    if(internal_choice == k_utra_TDD)
        out += utra_TDD.ToString(indent+1);
    if(internal_choice == k_cdma2000_HRPD)
        out += cdma2000_HRPD.ToString(indent+1);
    if(internal_choice == k_cdma2000_1xRTT)
        out += cdma2000_1xRTT.ToString(indent+1);
    return out;
}

std::string RedirectedCarrierInfo::ToStringNoNewLines() const
{
    std::string out = "RedirectedCarrierInfo=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_eutra)
        out += eutra.ToStringNoNewLines();
    if(internal_choice == k_geran)
        out += geran.ToStringNoNewLines();
    if(internal_choice == k_utra_FDD)
        out += utra_FDD.ToStringNoNewLines();
    if(internal_choice == k_utra_TDD)
        out += utra_TDD.ToStringNoNewLines();
    if(internal_choice == k_cdma2000_HRPD)
        out += cdma2000_HRPD.ToStringNoNewLines();
    if(internal_choice == k_cdma2000_1xRTT)
        out += cdma2000_1xRTT.ToStringNoNewLines();
    return out;
}

int RedirectedCarrierInfo::Clear()
{
    present = false;
    return 0;
}

bool RedirectedCarrierInfo::IsPresent() const
{
    return present;
}

ARFCN_ValueEUTRA* RedirectedCarrierInfo::eutra_Set()
{
    eutra_present = true;
    return &eutra;
}

int RedirectedCarrierInfo::eutra_Set(ARFCN_ValueEUTRA &value)
{
    eutra_present = true;
    eutra = value;
    return 0;
}

const ARFCN_ValueEUTRA& RedirectedCarrierInfo::eutra_Get() const
{
    return eutra;
}

std::string RedirectedCarrierInfo::eutra_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "eutra:\n";
    out += eutra.ToString(indent+1);
    return out;
}

std::string RedirectedCarrierInfo::eutra_ToStringNoNewLines() const
{
    std::string out = "eutra:";
    out += eutra.ToStringNoNewLines();
    return out;
}

int RedirectedCarrierInfo::eutra_Clear()
{
    eutra_present = false;
    return 0;
}

bool RedirectedCarrierInfo::eutra_IsPresent() const
{
    return eutra_present;
}

CarrierFreqsGERAN* RedirectedCarrierInfo::geran_Set()
{
    geran_present = true;
    return &geran;
}

int RedirectedCarrierInfo::geran_Set(CarrierFreqsGERAN &value)
{
    geran_present = true;
    geran = value;
    return 0;
}

const CarrierFreqsGERAN& RedirectedCarrierInfo::geran_Get() const
{
    return geran;
}

std::string RedirectedCarrierInfo::geran_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "geran:\n";
    out += geran.ToString(indent+1);
    return out;
}

std::string RedirectedCarrierInfo::geran_ToStringNoNewLines() const
{
    std::string out = "geran:";
    out += geran.ToStringNoNewLines();
    return out;
}

int RedirectedCarrierInfo::geran_Clear()
{
    geran_present = false;
    return 0;
}

bool RedirectedCarrierInfo::geran_IsPresent() const
{
    return geran_present;
}

ARFCN_ValueUTRA* RedirectedCarrierInfo::utra_FDD_Set()
{
    utra_FDD_present = true;
    return &utra_FDD;
}

int RedirectedCarrierInfo::utra_FDD_Set(ARFCN_ValueUTRA &value)
{
    utra_FDD_present = true;
    utra_FDD = value;
    return 0;
}

const ARFCN_ValueUTRA& RedirectedCarrierInfo::utra_FDD_Get() const
{
    return utra_FDD;
}

std::string RedirectedCarrierInfo::utra_FDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_FDD:\n";
    out += utra_FDD.ToString(indent+1);
    return out;
}

std::string RedirectedCarrierInfo::utra_FDD_ToStringNoNewLines() const
{
    std::string out = "utra_FDD:";
    out += utra_FDD.ToStringNoNewLines();
    return out;
}

int RedirectedCarrierInfo::utra_FDD_Clear()
{
    utra_FDD_present = false;
    return 0;
}

bool RedirectedCarrierInfo::utra_FDD_IsPresent() const
{
    return utra_FDD_present;
}

ARFCN_ValueUTRA* RedirectedCarrierInfo::utra_TDD_Set()
{
    utra_TDD_present = true;
    return &utra_TDD;
}

int RedirectedCarrierInfo::utra_TDD_Set(ARFCN_ValueUTRA &value)
{
    utra_TDD_present = true;
    utra_TDD = value;
    return 0;
}

const ARFCN_ValueUTRA& RedirectedCarrierInfo::utra_TDD_Get() const
{
    return utra_TDD;
}

std::string RedirectedCarrierInfo::utra_TDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_TDD:\n";
    out += utra_TDD.ToString(indent+1);
    return out;
}

std::string RedirectedCarrierInfo::utra_TDD_ToStringNoNewLines() const
{
    std::string out = "utra_TDD:";
    out += utra_TDD.ToStringNoNewLines();
    return out;
}

int RedirectedCarrierInfo::utra_TDD_Clear()
{
    utra_TDD_present = false;
    return 0;
}

bool RedirectedCarrierInfo::utra_TDD_IsPresent() const
{
    return utra_TDD_present;
}

CarrierFreqCDMA2000* RedirectedCarrierInfo::cdma2000_HRPD_Set()
{
    cdma2000_HRPD_present = true;
    return &cdma2000_HRPD;
}

int RedirectedCarrierInfo::cdma2000_HRPD_Set(CarrierFreqCDMA2000 &value)
{
    cdma2000_HRPD_present = true;
    cdma2000_HRPD = value;
    return 0;
}

const CarrierFreqCDMA2000& RedirectedCarrierInfo::cdma2000_HRPD_Get() const
{
    return cdma2000_HRPD;
}

std::string RedirectedCarrierInfo::cdma2000_HRPD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cdma2000_HRPD:\n";
    out += cdma2000_HRPD.ToString(indent+1);
    return out;
}

std::string RedirectedCarrierInfo::cdma2000_HRPD_ToStringNoNewLines() const
{
    std::string out = "cdma2000_HRPD:";
    out += cdma2000_HRPD.ToStringNoNewLines();
    return out;
}

int RedirectedCarrierInfo::cdma2000_HRPD_Clear()
{
    cdma2000_HRPD_present = false;
    return 0;
}

bool RedirectedCarrierInfo::cdma2000_HRPD_IsPresent() const
{
    return cdma2000_HRPD_present;
}

CarrierFreqCDMA2000* RedirectedCarrierInfo::cdma2000_1xRTT_Set()
{
    cdma2000_1xRTT_present = true;
    return &cdma2000_1xRTT;
}

int RedirectedCarrierInfo::cdma2000_1xRTT_Set(CarrierFreqCDMA2000 &value)
{
    cdma2000_1xRTT_present = true;
    cdma2000_1xRTT = value;
    return 0;
}

const CarrierFreqCDMA2000& RedirectedCarrierInfo::cdma2000_1xRTT_Get() const
{
    return cdma2000_1xRTT;
}

std::string RedirectedCarrierInfo::cdma2000_1xRTT_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cdma2000_1xRTT:\n";
    out += cdma2000_1xRTT.ToString(indent+1);
    return out;
}

std::string RedirectedCarrierInfo::cdma2000_1xRTT_ToStringNoNewLines() const
{
    std::string out = "cdma2000_1xRTT:";
    out += cdma2000_1xRTT.ToStringNoNewLines();
    return out;
}

int RedirectedCarrierInfo::cdma2000_1xRTT_Clear()
{
    cdma2000_1xRTT_present = false;
    return 0;
}

bool RedirectedCarrierInfo::cdma2000_1xRTT_IsPresent() const
{
    return cdma2000_1xRTT_present;
}

