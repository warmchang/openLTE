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

#include "SI_OrPSI_GERAN.h"

#include <cmath>

int SI_OrPSI_GERAN::Pack(std::vector<uint8_t> &bits)
{
    if(!present)
    {
        printf("SI_OrPSI_GERAN::Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((internal_choice >> (1-i-1)) & 1);

    // Fields
    if(internal_choice == k_si)
    {
        if(0 != si.Pack(bits))
        {
            printf("SI_OrPSI_GERAN::si pack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_psi)
    {
        if(0 != psi.Pack(bits))
        {
            printf("SI_OrPSI_GERAN::psi pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SI_OrPSI_GERAN::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SI_OrPSI_GERAN::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SI_OrPSI_GERAN::Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SI_OrPSI_GERAN::Enum)packed_val > k_psi)
    {
        printf("SI_OrPSI_GERAN::Unpack() choice range failure\n");
        return -1;
    }
    internal_choice = (SI_OrPSI_GERAN::Enum)packed_val;
    present = true;

    // Fields
    if(internal_choice == k_si)
    {
        if(0 != si.Unpack(bits, idx))
        {
            printf("SI_OrPSI_GERAN::si unpack failure\n");
            return -1;
        }
    }
    if(internal_choice == k_psi)
    {
        if(0 != psi.Unpack(bits, idx))
        {
            printf("SI_OrPSI_GERAN::psi unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SI_OrPSI_GERAN::Enum SI_OrPSI_GERAN::Choice() const
{
    if(present)
        return internal_choice;
    return (SI_OrPSI_GERAN::Enum)0;
}

int SI_OrPSI_GERAN::SetChoice(SI_OrPSI_GERAN::Enum choice)
{
    internal_choice = choice;
    present = true;
    return 0;
}

std::string SI_OrPSI_GERAN::ChoiceToString(Enum value) const
{
    if(k_si == value)
        return "si";
    if(k_psi == value)
        return "psi";
    return "";
}

uint64_t SI_OrPSI_GERAN::NumberOfChoices() const
{
    return 2;
}

std::string SI_OrPSI_GERAN::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SI_OrPSI_GERAN = " + ChoiceToString(internal_choice) + ":\n";
    if(internal_choice == k_si)
        out += si.ToString(indent+1);
    if(internal_choice == k_psi)
        out += psi.ToString(indent+1);
    return out;
}

std::string SI_OrPSI_GERAN::ToStringNoNewLines() const
{
    std::string out = "SI_OrPSI_GERAN=" + ChoiceToString(internal_choice) + ",";
    if(internal_choice == k_si)
        out += si.ToStringNoNewLines();
    if(internal_choice == k_psi)
        out += psi.ToStringNoNewLines();
    return out;
}

int SI_OrPSI_GERAN::Clear()
{
    present = false;
    return 0;
}

bool SI_OrPSI_GERAN::IsPresent() const
{
    return present;
}

SystemInfoListGERAN* SI_OrPSI_GERAN::si_Set()
{
    si_present = true;
    return &si;
}

int SI_OrPSI_GERAN::si_Set(SystemInfoListGERAN &value)
{
    si_present = true;
    si = value;
    return 0;
}

const SystemInfoListGERAN& SI_OrPSI_GERAN::si_Get() const
{
    return si;
}

std::string SI_OrPSI_GERAN::si_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "si:\n";
    out += si.ToString(indent+1);
    return out;
}

std::string SI_OrPSI_GERAN::si_ToStringNoNewLines() const
{
    std::string out = "si:";
    out += si.ToStringNoNewLines();
    return out;
}

int SI_OrPSI_GERAN::si_Clear()
{
    si_present = false;
    return 0;
}

bool SI_OrPSI_GERAN::si_IsPresent() const
{
    return si_present;
}

SystemInfoListGERAN* SI_OrPSI_GERAN::psi_Set()
{
    psi_present = true;
    return &psi;
}

int SI_OrPSI_GERAN::psi_Set(SystemInfoListGERAN &value)
{
    psi_present = true;
    psi = value;
    return 0;
}

const SystemInfoListGERAN& SI_OrPSI_GERAN::psi_Get() const
{
    return psi;
}

std::string SI_OrPSI_GERAN::psi_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "psi:\n";
    out += psi.ToString(indent+1);
    return out;
}

std::string SI_OrPSI_GERAN::psi_ToStringNoNewLines() const
{
    std::string out = "psi:";
    out += psi.ToStringNoNewLines();
    return out;
}

int SI_OrPSI_GERAN::psi_Clear()
{
    psi_present = false;
    return 0;
}

bool SI_OrPSI_GERAN::psi_IsPresent() const
{
    return psi_present;
}

