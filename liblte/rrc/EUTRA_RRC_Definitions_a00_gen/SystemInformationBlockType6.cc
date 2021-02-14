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

#include "SystemInformationBlockType6.h"

#include <cmath>

int SystemInformationBlockType6::Pack(std::vector<uint8_t> &bits)
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
    bits.push_back(carrierFreqListUTRA_FDD_IsPresent());
    bits.push_back(carrierFreqListUTRA_TDD_IsPresent());
    bits.push_back(t_ReselectionUTRA_SF_IsPresent());

    // Fields
    if(carrierFreqListUTRA_FDD_IsPresent())
    {
        if(0 != carrierFreqListUTRA_FDD.Pack(bits))
        {
            printf("SystemInformationBlockType6:: field pack failure\n");
            return -1;
        }
    }
    if(carrierFreqListUTRA_TDD_IsPresent())
    {
        if(0 != carrierFreqListUTRA_TDD.Pack(bits))
        {
            printf("SystemInformationBlockType6:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_ReselectionUTRA.Pack(bits))
        {
            printf("SystemInformationBlockType6:: field pack failure\n");
            return -1;
        }
    }
    if(t_ReselectionUTRA_SF_IsPresent())
    {
        if(0 != t_ReselectionUTRA_SF.Pack(bits))
        {
            printf("SystemInformationBlockType6:: field pack failure\n");
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
            printf("SystemInformationBlockType6:: Extension list size too large failure\n");
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
                printf("SystemInformationBlockType6:: field pack failure\n");
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

int SystemInformationBlockType6::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SystemInformationBlockType6::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType6::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType6::Unpack() index out of bounds for optional indiator carrierFreqListUTRA_FDD\n");
        return -1;
    }
    carrierFreqListUTRA_FDD_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType6::Unpack() index out of bounds for optional indiator carrierFreqListUTRA_TDD\n");
        return -1;
    }
    carrierFreqListUTRA_TDD_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SystemInformationBlockType6::Unpack() index out of bounds for optional indiator t_ReselectionUTRA_SF\n");
        return -1;
    }
    t_ReselectionUTRA_SF_present = bits[idx++];

    // Fields
    if(carrierFreqListUTRA_FDD_present)
    {
        if(0 != carrierFreqListUTRA_FDD.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType6:: field unpack failure\n");
            return -1;
        }
    }
    if(carrierFreqListUTRA_TDD_present)
    {
        if(0 != carrierFreqListUTRA_TDD.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType6:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != t_ReselectionUTRA.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType6:: field unpack failure\n");
            return -1;
        }
    }
    if(t_ReselectionUTRA_SF_present)
    {
        if(0 != t_ReselectionUTRA_SF.Unpack(bits, idx))
        {
            printf("SystemInformationBlockType6:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("SystemInformationBlockType6::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("SystemInformationBlockType6:: Extension list size too large failure\n");
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
                printf("SystemInformationBlockType6::Unpack() index out of bounds for optional indiator lateNonCriticalExtension\n");
                return -1;
            }
            lateNonCriticalExtension_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("SystemInformationBlockType6::Unpack() index out of bounds for extension optional indicators\n");
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
                printf("SystemInformationBlockType6:: field unpack failure\n");
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
            printf("SystemInformationBlockType6::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string SystemInformationBlockType6::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SystemInformationBlockType6:\n";
    if(carrierFreqListUTRA_FDD_IsPresent())
        out += carrierFreqListUTRA_FDD_ToString(indent+1);
    if(carrierFreqListUTRA_TDD_IsPresent())
        out += carrierFreqListUTRA_TDD_ToString(indent+1);
    out += t_ReselectionUTRA_ToString(indent+1);
    if(t_ReselectionUTRA_SF_IsPresent())
        out += t_ReselectionUTRA_SF_ToString(indent+1);
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType6::ToStringNoNewLines() const
{
    std::string out = "SystemInformationBlockType6:";
    if(carrierFreqListUTRA_FDD_IsPresent())
        out += carrierFreqListUTRA_FDD_ToStringNoNewLines();
    if(carrierFreqListUTRA_TDD_IsPresent())
        out += carrierFreqListUTRA_TDD_ToStringNoNewLines();
    out += t_ReselectionUTRA_ToStringNoNewLines();
    if(t_ReselectionUTRA_SF_IsPresent())
        out += t_ReselectionUTRA_SF_ToStringNoNewLines();
    if(lateNonCriticalExtension_IsPresent())
        out += lateNonCriticalExtension_ToStringNoNewLines();
    return out;
}

CarrierFreqListUTRA_FDD* SystemInformationBlockType6::carrierFreqListUTRA_FDD_Set()
{
    carrierFreqListUTRA_FDD_present = true;
    return &carrierFreqListUTRA_FDD;
}

int SystemInformationBlockType6::carrierFreqListUTRA_FDD_Set(CarrierFreqListUTRA_FDD &value)
{
    carrierFreqListUTRA_FDD_present = true;
    carrierFreqListUTRA_FDD = value;
    return 0;
}

const CarrierFreqListUTRA_FDD& SystemInformationBlockType6::carrierFreqListUTRA_FDD_Get() const
{
    return carrierFreqListUTRA_FDD;
}

std::string SystemInformationBlockType6::carrierFreqListUTRA_FDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreqListUTRA_FDD:\n";
    out += carrierFreqListUTRA_FDD.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType6::carrierFreqListUTRA_FDD_ToStringNoNewLines() const
{
    std::string out = "carrierFreqListUTRA_FDD:";
    out += carrierFreqListUTRA_FDD.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType6::carrierFreqListUTRA_FDD_Clear()
{
    carrierFreqListUTRA_FDD_present = false;
    return 0;
}

bool SystemInformationBlockType6::carrierFreqListUTRA_FDD_IsPresent() const
{
    return carrierFreqListUTRA_FDD_present;
}

CarrierFreqListUTRA_TDD* SystemInformationBlockType6::carrierFreqListUTRA_TDD_Set()
{
    carrierFreqListUTRA_TDD_present = true;
    return &carrierFreqListUTRA_TDD;
}

int SystemInformationBlockType6::carrierFreqListUTRA_TDD_Set(CarrierFreqListUTRA_TDD &value)
{
    carrierFreqListUTRA_TDD_present = true;
    carrierFreqListUTRA_TDD = value;
    return 0;
}

const CarrierFreqListUTRA_TDD& SystemInformationBlockType6::carrierFreqListUTRA_TDD_Get() const
{
    return carrierFreqListUTRA_TDD;
}

std::string SystemInformationBlockType6::carrierFreqListUTRA_TDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreqListUTRA_TDD:\n";
    out += carrierFreqListUTRA_TDD.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType6::carrierFreqListUTRA_TDD_ToStringNoNewLines() const
{
    std::string out = "carrierFreqListUTRA_TDD:";
    out += carrierFreqListUTRA_TDD.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType6::carrierFreqListUTRA_TDD_Clear()
{
    carrierFreqListUTRA_TDD_present = false;
    return 0;
}

bool SystemInformationBlockType6::carrierFreqListUTRA_TDD_IsPresent() const
{
    return carrierFreqListUTRA_TDD_present;
}

T_Reselection* SystemInformationBlockType6::t_ReselectionUTRA_Set()
{
    t_ReselectionUTRA_present = true;
    return &t_ReselectionUTRA;
}

int SystemInformationBlockType6::t_ReselectionUTRA_Set(T_Reselection &value)
{
    t_ReselectionUTRA_present = true;
    t_ReselectionUTRA = value;
    return 0;
}

const T_Reselection& SystemInformationBlockType6::t_ReselectionUTRA_Get() const
{
    return t_ReselectionUTRA;
}

std::string SystemInformationBlockType6::t_ReselectionUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_ReselectionUTRA:\n";
    out += t_ReselectionUTRA.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType6::t_ReselectionUTRA_ToStringNoNewLines() const
{
    std::string out = "t_ReselectionUTRA:";
    out += t_ReselectionUTRA.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType6::t_ReselectionUTRA_Clear()
{
    t_ReselectionUTRA_present = false;
    return 0;
}

bool SystemInformationBlockType6::t_ReselectionUTRA_IsPresent() const
{
    return t_ReselectionUTRA_present;
}

SpeedStateScaleFactors* SystemInformationBlockType6::t_ReselectionUTRA_SF_Set()
{
    t_ReselectionUTRA_SF_present = true;
    return &t_ReselectionUTRA_SF;
}

int SystemInformationBlockType6::t_ReselectionUTRA_SF_Set(SpeedStateScaleFactors &value)
{
    t_ReselectionUTRA_SF_present = true;
    t_ReselectionUTRA_SF = value;
    return 0;
}

const SpeedStateScaleFactors& SystemInformationBlockType6::t_ReselectionUTRA_SF_Get() const
{
    return t_ReselectionUTRA_SF;
}

std::string SystemInformationBlockType6::t_ReselectionUTRA_SF_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "t_ReselectionUTRA_SF:\n";
    out += t_ReselectionUTRA_SF.ToString(indent+1);
    return out;
}

std::string SystemInformationBlockType6::t_ReselectionUTRA_SF_ToStringNoNewLines() const
{
    std::string out = "t_ReselectionUTRA_SF:";
    out += t_ReselectionUTRA_SF.ToStringNoNewLines();
    return out;
}

int SystemInformationBlockType6::t_ReselectionUTRA_SF_Clear()
{
    t_ReselectionUTRA_SF_present = false;
    return 0;
}

bool SystemInformationBlockType6::t_ReselectionUTRA_SF_IsPresent() const
{
    return t_ReselectionUTRA_SF_present;
}

int SystemInformationBlockType6::lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits)
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

int SystemInformationBlockType6::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return lateNonCriticalExtension_Unpack(bits, idx);
}

int SystemInformationBlockType6::lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
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
        printf("SystemInformationBlockType6::lateNonCriticalExtension_Unpack() index out of bounds\n");
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

std::vector<uint8_t> SystemInformationBlockType6::lateNonCriticalExtension_Value() const
{
    if(lateNonCriticalExtension_present)
        return lateNonCriticalExtension_internal_value;
    std::vector<uint8_t> tmp;
    return tmp;
}

int SystemInformationBlockType6::lateNonCriticalExtension_SetValue(std::vector<uint8_t> value)
{
    lateNonCriticalExtension_internal_value = value;
    lateNonCriticalExtension_present = true;
    return 0;
}

std::string SystemInformationBlockType6::lateNonCriticalExtension_ToString(uint32_t indent) const
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

std::string SystemInformationBlockType6::lateNonCriticalExtension_ToStringNoNewLines() const
{
    std::string out = "lateNonCriticalExtension={";
    for(auto byte : lateNonCriticalExtension_internal_value)
        out += std::to_string(byte) + ",";
    out = out.substr(0, out.length()-1) + "},";
    return out;
}

int SystemInformationBlockType6::lateNonCriticalExtension_Clear()
{
    lateNonCriticalExtension_present = false;
    return 0;
}

bool SystemInformationBlockType6::lateNonCriticalExtension_IsPresent() const
{
    return lateNonCriticalExtension_present;
}

