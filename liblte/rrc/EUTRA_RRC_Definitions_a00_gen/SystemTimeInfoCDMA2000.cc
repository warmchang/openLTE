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

#include "SystemTimeInfoCDMA2000.h"

#include <cmath>

int SystemTimeInfoCDMA2000::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cdma_EUTRA_Synchronisation_Pack(bits))
        {
            printf("SystemTimeInfoCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != cdma_SystemTime_Pack(bits))
        {
            printf("SystemTimeInfoCDMA2000:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemTimeInfoCDMA2000::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemTimeInfoCDMA2000::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != cdma_EUTRA_Synchronisation_Unpack(bits, idx))
        {
            printf("SystemTimeInfoCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != cdma_SystemTime_Unpack(bits, idx))
        {
            printf("SystemTimeInfoCDMA2000:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SystemTimeInfoCDMA2000::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemTimeInfoCDMA2000:\n";
    out += cdma_EUTRA_Synchronisation_ToString(indent+1);
    out += cdma_SystemTime_ToString(indent+1);
    return out;
}

std::string SystemTimeInfoCDMA2000::ToStringNoNewLines() const
{
    std::string out = "SystemTimeInfoCDMA2000:";
    out += cdma_EUTRA_Synchronisation_ToStringNoNewLines();
    out += cdma_SystemTime_ToStringNoNewLines();
    return out;
}

int SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_Pack(std::vector<uint8_t> &bits)
{
    if(!cdma_EUTRA_Synchronisation_present)
    {
        printf("SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(cdma_EUTRA_Synchronisation_internal_value);
    return 0;
}

int SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cdma_EUTRA_Synchronisation_Unpack(bits, idx);
}

int SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_Unpack() index out of bounds\n");
        return -1;
    }
    cdma_EUTRA_Synchronisation_internal_value = bits[idx++];
    cdma_EUTRA_Synchronisation_present = true;
    return 0;
}

bool SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_Value() const
{
    if(cdma_EUTRA_Synchronisation_present)
        return cdma_EUTRA_Synchronisation_internal_value;
    return false;
}

int SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_SetValue(bool value)
{
    cdma_EUTRA_Synchronisation_internal_value = value;
    cdma_EUTRA_Synchronisation_present = true;
    return 0;
}

std::string SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cdma_EUTRA_Synchronisation = " + std::to_string(cdma_EUTRA_Synchronisation_internal_value) + "\n";
    return out;
}

std::string SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_ToStringNoNewLines() const
{
    std::string out = "cdma_EUTRA_Synchronisation=" + std::to_string(cdma_EUTRA_Synchronisation_internal_value) + ",";
    return out;
}

int SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_Clear()
{
    cdma_EUTRA_Synchronisation_present = false;
    return 0;
}

bool SystemTimeInfoCDMA2000::cdma_EUTRA_Synchronisation_IsPresent() const
{
    return cdma_EUTRA_Synchronisation_present;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_Pack(std::vector<uint8_t> &bits)
{
    if(!cdma_SystemTime_present)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((cdma_SystemTime_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(cdma_SystemTime_internal_choice == k_cdma_SystemTime_synchronousSystemTime)
    {
        if(0 != cdma_SystemTime_synchronousSystemTime_Pack(bits))
        {
            printf("SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime pack failure\n");
            return -1;
        }
    }
    if(cdma_SystemTime_internal_choice == k_cdma_SystemTime_asynchronousSystemTime)
    {
        if(0 != cdma_SystemTime_asynchronousSystemTime_Pack(bits))
        {
            printf("SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cdma_SystemTime_Unpack(bits, idx);
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((SystemTimeInfoCDMA2000::cdma_SystemTime_Enum)packed_val > k_cdma_SystemTime_asynchronousSystemTime)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_Unpack() choice range failure\n");
        return -1;
    }
    cdma_SystemTime_internal_choice = (SystemTimeInfoCDMA2000::cdma_SystemTime_Enum)packed_val;
    cdma_SystemTime_present = true;

    // Fields
    if(cdma_SystemTime_internal_choice == k_cdma_SystemTime_synchronousSystemTime)
    {
        if(0 != cdma_SystemTime_synchronousSystemTime_Unpack(bits, idx))
        {
            printf("SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime unpack failure\n");
            return -1;
        }
    }
    if(cdma_SystemTime_internal_choice == k_cdma_SystemTime_asynchronousSystemTime)
    {
        if(0 != cdma_SystemTime_asynchronousSystemTime_Unpack(bits, idx))
        {
            printf("SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime unpack failure\n");
            return -1;
        }
    }
    return 0;
}

SystemTimeInfoCDMA2000::cdma_SystemTime_Enum SystemTimeInfoCDMA2000::cdma_SystemTime_Choice() const
{
    if(cdma_SystemTime_present)
        return cdma_SystemTime_internal_choice;
    return (SystemTimeInfoCDMA2000::cdma_SystemTime_Enum)0;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_SetChoice(SystemTimeInfoCDMA2000::cdma_SystemTime_Enum choice)
{
    cdma_SystemTime_internal_choice = choice;
    cdma_SystemTime_present = true;
    return 0;
}

std::string SystemTimeInfoCDMA2000::cdma_SystemTime_ChoiceToString(cdma_SystemTime_Enum value) const
{
    if(k_cdma_SystemTime_synchronousSystemTime == value)
        return "cdma_SystemTime_synchronousSystemTime";
    if(k_cdma_SystemTime_asynchronousSystemTime == value)
        return "cdma_SystemTime_asynchronousSystemTime";
    return "";
}

uint64_t SystemTimeInfoCDMA2000::cdma_SystemTime_NumberOfChoices() const
{
    return 2;
}

std::string SystemTimeInfoCDMA2000::cdma_SystemTime_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cdma_SystemTime = " + cdma_SystemTime_ChoiceToString(cdma_SystemTime_internal_choice) + ":\n";
    if(cdma_SystemTime_internal_choice == k_cdma_SystemTime_synchronousSystemTime)
        out += cdma_SystemTime_synchronousSystemTime_ToString(indent+1);
    if(cdma_SystemTime_internal_choice == k_cdma_SystemTime_asynchronousSystemTime)
        out += cdma_SystemTime_asynchronousSystemTime_ToString(indent+1);
    return out;
}

std::string SystemTimeInfoCDMA2000::cdma_SystemTime_ToStringNoNewLines() const
{
    std::string out = "cdma_SystemTime=" + cdma_SystemTime_ChoiceToString(cdma_SystemTime_internal_choice) + ",";
    if(cdma_SystemTime_internal_choice == k_cdma_SystemTime_synchronousSystemTime)
        out += cdma_SystemTime_synchronousSystemTime_ToStringNoNewLines();
    if(cdma_SystemTime_internal_choice == k_cdma_SystemTime_asynchronousSystemTime)
        out += cdma_SystemTime_asynchronousSystemTime_ToStringNoNewLines();
    return out;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_Clear()
{
    cdma_SystemTime_present = false;
    return 0;
}

bool SystemTimeInfoCDMA2000::cdma_SystemTime_IsPresent() const
{
    return cdma_SystemTime_present;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_Pack(std::vector<uint8_t> &bits)
{
    if(!cdma_SystemTime_synchronousSystemTime_present)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 39;
    if(size < 39 || size > 39)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((cdma_SystemTime_synchronousSystemTime_internal_value >> (39-i-1)) & 1);
    return 0;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cdma_SystemTime_synchronousSystemTime_Unpack(bits, idx);
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 39;
    if(size < 39 || size > 39)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_Unpack() size failure\n");
        return -1;
    }
    cdma_SystemTime_synchronousSystemTime_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        cdma_SystemTime_synchronousSystemTime_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(39-i-1);
    cdma_SystemTime_synchronousSystemTime_present = true;
    return 0;
}

uint64_t SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_Value() const
{
    if(cdma_SystemTime_synchronousSystemTime_present)
        return cdma_SystemTime_synchronousSystemTime_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 39)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_SetValue() size failure\n");
        return -1;
    }
    cdma_SystemTime_synchronousSystemTime_internal_value = value;
    cdma_SystemTime_synchronousSystemTime_present = true;
    return 0;
}

std::string SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "synchronousSystemTime = ";
    out += std::to_string(cdma_SystemTime_synchronousSystemTime_internal_value);
    out += "\n";
    return out;
}

std::string SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_ToStringNoNewLines() const
{
    std::string out = "synchronousSystemTime=";
    out += std::to_string(cdma_SystemTime_synchronousSystemTime_internal_value);
    out += ",";
    return out;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_Clear()
{
    cdma_SystemTime_synchronousSystemTime_present = false;
    return 0;
}

bool SystemTimeInfoCDMA2000::cdma_SystemTime_synchronousSystemTime_IsPresent() const
{
    return cdma_SystemTime_synchronousSystemTime_present;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_Pack(std::vector<uint8_t> &bits)
{
    if(!cdma_SystemTime_asynchronousSystemTime_present)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 49;
    if(size < 49 || size > 49)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((cdma_SystemTime_asynchronousSystemTime_internal_value >> (49-i-1)) & 1);
    return 0;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cdma_SystemTime_asynchronousSystemTime_Unpack(bits, idx);
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 49;
    if(size < 49 || size > 49)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_Unpack() size failure\n");
        return -1;
    }
    cdma_SystemTime_asynchronousSystemTime_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        cdma_SystemTime_asynchronousSystemTime_internal_value |= (uint64_t)bits[idx++] << (uint64_t)(49-i-1);
    cdma_SystemTime_asynchronousSystemTime_present = true;
    return 0;
}

uint64_t SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_Value() const
{
    if(cdma_SystemTime_asynchronousSystemTime_present)
        return cdma_SystemTime_asynchronousSystemTime_internal_value;
    uint64_t tmp = 0;
    return tmp;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_SetValue(uint64_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 49)
    {
        printf("SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_SetValue() size failure\n");
        return -1;
    }
    cdma_SystemTime_asynchronousSystemTime_internal_value = value;
    cdma_SystemTime_asynchronousSystemTime_present = true;
    return 0;
}

std::string SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "asynchronousSystemTime = ";
    out += std::to_string(cdma_SystemTime_asynchronousSystemTime_internal_value);
    out += "\n";
    return out;
}

std::string SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_ToStringNoNewLines() const
{
    std::string out = "asynchronousSystemTime=";
    out += std::to_string(cdma_SystemTime_asynchronousSystemTime_internal_value);
    out += ",";
    return out;
}

int SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_Clear()
{
    cdma_SystemTime_asynchronousSystemTime_present = false;
    return 0;
}

bool SystemTimeInfoCDMA2000::cdma_SystemTime_asynchronousSystemTime_IsPresent() const
{
    return cdma_SystemTime_asynchronousSystemTime_present;
}

