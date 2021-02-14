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

#include "SystemInformationBlockType4.h"

#include <cmath>

int SystemInformationBlockType4::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(lateNonCriticalExtension_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(intraFreqNeighCellList_IsPresent());
    bits.push_back(intraFreqBlackCellList_IsPresent());
    bits.push_back(csg_PhysCellIdRange_IsPresent());

    // Fields
    if(intraFreqNeighCellList_IsPresent())
    {
        if(0 != intraFreqNeighCellList.Pack(bits))
        {
            printf("SystemInformationBlockType4:: field pack failure\n");
            return -1;
        }
    }
    if(intraFreqBlackCellList_IsPresent())
    {
        if(0 != intraFreqBlackCellList.Pack(bits))
        {
            printf("SystemInformationBlockType4:: field pack failure\n");
            return -1;
        }
    }
    if(csg_PhysCellIdRange_IsPresent())
    {
        if(0 != csg_PhysCellIdRange.Pack(bits))
        {
            printf("SystemInformationBlockType4:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(0 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((0 >> (6-i-1)) & 1);
        }else{
            printf("SystemInformationBlockType4:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(lateNonCriticalExtension_IsPresent());

        // Extension fields
        if(lateNonCriticalExtension_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != lateNonCriticalExtension_Pack(field_bits))
            {
                printf("SystemInformationBlockType4:: field pack failure\n");
                return -1;
            }
            while((field_bits.size() % 8) != 0)
                field_bits.push_back(0);
            uint32_t N_octets = field_bits.size() / 8;
            uint32_t local_size_length = 0;
            uint32_t local_size = N_octets;
            if(local_size < 128)
            {
                bits.push_back(0);
                local_size_length = 7;
            }else if(local_size < 16383){
                bits.push_back(1);
                bits.push_back(0);
                local_size_length = 14;
            }else{
                bits.push_back(1);
                bits.push_back(1);
                uint32_t N_16k_blocks = local_size / 16383;
                for(uint32_t i=0; i<6; i++)
                    bits.push_back((N_16k_blocks >> (6-i-1)) & 1);
                local_size %= 16383;
                if(local_size < 128)
                {
                    bits.push_back(0);
                    local_size_length = 7;
                }else{
                    bits.push_back(1);
                    bits.push_back(0);
                    local_size_length = 14;
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                bits.push_back((local_size >> (local_size_length-i-1)) & 1);
            for(auto b : field_bits)
                bits.push_back(b);
        }
    }
    return 0;
}

int SystemInformationBlockType4::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType4::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType4::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType4::Unpack() index out of bounds for optional indiator intraFreqNeighCellList\n");
        return -1;
    }
    intraFreqNeighCellList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType4::Unpack() index out of bounds for optional indiator intraFreqBlackCellList\n");
        return -1;
    }
    intraFreqBlackCellList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType4::Unpack() index out of bounds for optional indiator csg_PhysCellIdRange\n");
        return -1;
    }
    csg_PhysCellIdRange_present = bits[idx++];

    // Fields
    if(intraFreqNeighCellList_present)
    {
        if(0 != intraFreqNeighCellList.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType4:: field unpack failure\n");
            return -1;
        }
    }
    if(intraFreqBlackCellList_present)
    {
        if(0 != intraFreqBlackCellList.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType4:: field unpack failure\n");
            return -1;
        }
    }
    if(csg_PhysCellIdRange_present)
    {
        if(0 != csg_PhysCellIdRange.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType4:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("SystemInformationBlockType4::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("SystemInformationBlockType4:: Extension list size too large failure\n");
            return -1;
        }
        uint32_t N_ext_fields = 0;
        for(uint32_t i=0; i<6; i++)
            N_ext_fields |= bits[idx++] << (6-i-1);
        N_ext_fields++;

        // Extension field presence indicators
        uint32_t opt_ind_count = 0;
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("SystemInformationBlockType4::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
                return -1;
            }
            lateNonCriticalExtension_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("SystemInformationBlockType4::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(lateNonCriticalExtension_present)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
                    if(0 == bits[idx++])
                    {
                        local_size_length = 7;
                    }else{
                        idx++;
                        local_size_length = 14;
                    }
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                N_octets |= bits[idx++] << (local_size_length-i-1);
            uint32_t orig_idx = idx;
            if(0 != lateNonCriticalExtension_Unpack(bits, idx))
            {
                printf("SystemInformationBlockType4:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=1; i<N_ext_fields; i++)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
                    if(0 == bits[idx++])
                    {
                        local_size_length = 7;
                    }else{
                        idx++;
                        local_size_length = 14;
                    }
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                N_octets |= bits[idx++] << (local_size_length-i-1);
        if((idx + (N_octets * 8)) > bits.size())
        {
            printf("SystemInformationBlockType4::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string SystemInformationBlockType4::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType4:\n";
    if(intraFreqNeighCellList_IsPresent())
        out += intraFreqNeighCellList_ToString(indent+1);
    if(intraFreqBlackCellList_IsPresent())
        out += intraFreqBlackCellList_ToString(indent+1);
    if(csg_PhysCellIdRange_IsPresent())
        out += csg_PhysCellIdRange_ToString(indent+1);
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType4::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType4:";
    if(intraFreqNeighCellList_IsPresent())
        out += intraFreqNeighCellList_ToStringNoNewLines();
    if(intraFreqBlackCellList_IsPresent())
        out += intraFreqBlackCellList_ToStringNoNewLines();
    if(csg_PhysCellIdRange_IsPresent())
        out += csg_PhysCellIdRange_ToStringNoNewLines();
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    return out;
}

IntraFreqNeighCellList* SystemInformationBlockType4::intraFreqNeighCellList_Set()
{
    intraFreqNeighCellList_present = true;
    return &intraFreqNeighCellList;
}

int SystemInformationBlockType4::intraFreqNeighCellList_Set(IntraFreqNeighCellList &value)
{
    intraFreqNeighCellList_present = true;
    intraFreqNeighCellList = value;
    return 0;
}

const IntraFreqNeighCellList& SystemInformationBlockType4::intraFreqNeighCellList_Get() const
{
    return intraFreqNeighCellList;
}

std::string SystemInformationBlockType4::intraFreqNeighCellList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "intraFreqNeighCellList:\n";
    out += intraFreqNeighCellList.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType4::intraFreqNeighCellList_ToStringNoNewLines() const
{
    std::string out = "intraFreqNeighCellList:";
    out += intraFreqNeighCellList.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType4::intraFreqNeighCellList_Clear()
{
    intraFreqNeighCellList_present = false;
    return 0;
}

bool SystemInformationBlockType4::intraFreqNeighCellList_IsPresent() const
{
    return intraFreqNeighCellList_present;
}

IntraFreqBlackCellList* SystemInformationBlockType4::intraFreqBlackCellList_Set()
{
    intraFreqBlackCellList_present = true;
    return &intraFreqBlackCellList;
}

int SystemInformationBlockType4::intraFreqBlackCellList_Set(IntraFreqBlackCellList &value)
{
    intraFreqBlackCellList_present = true;
    intraFreqBlackCellList = value;
    return 0;
}

const IntraFreqBlackCellList& SystemInformationBlockType4::intraFreqBlackCellList_Get() const
{
    return intraFreqBlackCellList;
}

std::string SystemInformationBlockType4::intraFreqBlackCellList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "intraFreqBlackCellList:\n";
    out += intraFreqBlackCellList.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType4::intraFreqBlackCellList_ToStringNoNewLines() const
{
    std::string out = "intraFreqBlackCellList:";
    out += intraFreqBlackCellList.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType4::intraFreqBlackCellList_Clear()
{
    intraFreqBlackCellList_present = false;
    return 0;
}

bool SystemInformationBlockType4::intraFreqBlackCellList_IsPresent() const
{
    return intraFreqBlackCellList_present;
}

PhysCellIdRange* SystemInformationBlockType4::csg_PhysCellIdRange_Set()
{
    csg_PhysCellIdRange_present = true;
    return &csg_PhysCellIdRange;
}

int SystemInformationBlockType4::csg_PhysCellIdRange_Set(PhysCellIdRange &value)
{
    csg_PhysCellIdRange_present = true;
    csg_PhysCellIdRange = value;
    return 0;
}

const PhysCellIdRange& SystemInformationBlockType4::csg_PhysCellIdRange_Get() const
{
    return csg_PhysCellIdRange;
}

std::string SystemInformationBlockType4::csg_PhysCellIdRange_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csg_PhysCellIdRange:\n";
    out += csg_PhysCellIdRange.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType4::csg_PhysCellIdRange_ToStringNoNewLines() const
{
    std::string out = "csg_PhysCellIdRange:";
    out += csg_PhysCellIdRange.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType4::csg_PhysCellIdRange_Clear()
{
    csg_PhysCellIdRange_present = false;
    return 0;
}

bool SystemInformationBlockType4::csg_PhysCellIdRange_IsPresent() const
{
    return csg_PhysCellIdRange_present;
}

int SystemInformationBlockType4::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
{
    uint32_t local_size_length = 0;
    uint32_t local_size = lateNonCriticalExtension_internal_value.size();
    if(local_size < 128)
    {
        bits.push_back(0);
        local_size_length = 7;
    }else if(local_size < 16383){
        bits.push_back(1);
        bits.push_back(0);
        local_size_length = 14;
    }else{
        bits.push_back(1);
        bits.push_back(1);
        uint32_t N_16k_blocks = local_size / 16383;
        for(uint32_t i=0; i<6; i++)
            bits.push_back((N_16k_blocks >> (6-i-1)) & 1);
        local_size %= 16383;
        if(local_size < 128)
        {
            bits.push_back(0);
            local_size_length = 7;
        }else{
            bits.push_back(1);
            bits.push_back(0);
            local_size_length = 14;
        }
    }
    for(uint32_t i=0; i<local_size_length; i++)
        bits.push_back((local_size >> (local_size_length-i-1)) & 1);
    for(uint32_t i=0; i<lateNonCriticalExtension_internal_value.size(); i++)
        for(uint32_t j=0; j<8; j++)
            bits.push_back((lateNonCriticalExtension_internal_value[i] >> (8-j-1)) & 1);
    return 0;
}

int SystemInformationBlockType4::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformationBlockType4::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t local_size_length = 0;
    uint32_t size = 0;
    if(0 == bits[idx++])
    {
        local_size_length = 7;
    }else{
        if(0 == bits[idx++])
        {
            local_size_length = 14;
        }else{
            for(uint32_t i=0; i<6; i++)
                size |= bits[idx++] << (6-i-1);
            size *= 16383;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                idx++;
                local_size_length = 14;
            }
        }
    }
    for(uint32_t i=0; i<local_size_length; i++)
        size |= bits[idx++] << (local_size_length-i-1);
    lateNonCriticalExtension_internal_value.clear();
    if((idx +size*8) > bits.size())
    {
        printf("SystemInformationBlockType4::lateNonCriticalExtension_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
    {
        uint8_t value = 0;
        for(uint32_t j=0; j<8; j++)
            value |= bits[idx+j] << (8-j-1);
        lateNonCriticalExtension_internal_value.push_back(value);
        idx += 8;
    }
    lateNonCriticalExtension_present = true;
    return 0;
}

std::vector<uint8_t> SystemInformationBlockType4::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType4::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformationBlockType4::lateNonCriticalExtension_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "lateNonCriticalExtension = {";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "}\n";
    return out;
}

std::string SystemInformationBlockType4::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType4::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType4::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

