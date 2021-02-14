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

#include "QuantityConfig.h"

#include <cmath>

int QuantityConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(quantityConfigUTRA_v10x0_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(quantityConfigEUTRA_IsPresent());
    bits.push_back(quantityConfigUTRA_IsPresent());
    bits.push_back(quantityConfigGERAN_IsPresent());
    bits.push_back(quantityConfigCDMA2000_IsPresent());

    // Fields
    if(quantityConfigEUTRA_IsPresent())
    {
        if(0 != quantityConfigEUTRA.Pack(bits))
        {
            printf("QuantityConfig:: field pack failure\n");
            return -1;
        }
    }
    if(quantityConfigUTRA_IsPresent())
    {
        if(0 != quantityConfigUTRA.Pack(bits))
        {
            printf("QuantityConfig:: field pack failure\n");
            return -1;
        }
    }
    if(quantityConfigGERAN_IsPresent())
    {
        if(0 != quantityConfigGERAN.Pack(bits))
        {
            printf("QuantityConfig:: field pack failure\n");
            return -1;
        }
    }
    if(quantityConfigCDMA2000_IsPresent())
    {
        if(0 != quantityConfigCDMA2000.Pack(bits))
        {
            printf("QuantityConfig:: field pack failure\n");
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
            printf("QuantityConfig:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(quantityConfigUTRA_v10x0_IsPresent());

        // Extension fields
        if(quantityConfigUTRA_v10x0_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != quantityConfigUTRA_v10x0.Pack(field_bits))
            {
                printf("QuantityConfig:: field pack failure\n");
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

int QuantityConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int QuantityConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfig::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfig::Unpack() index out of bounds for optional indiator quantityConfigEUTRA\n");
        return -1;
    }
    quantityConfigEUTRA_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfig::Unpack() index out of bounds for optional indiator quantityConfigUTRA\n");
        return -1;
    }
    quantityConfigUTRA_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfig::Unpack() index out of bounds for optional indiator quantityConfigGERAN\n");
        return -1;
    }
    quantityConfigGERAN_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("QuantityConfig::Unpack() index out of bounds for optional indiator quantityConfigCDMA2000\n");
        return -1;
    }
    quantityConfigCDMA2000_present = bits[idx++];

    // Fields
    if(quantityConfigEUTRA_present)
    {
        if(0 != quantityConfigEUTRA.Unpack(bits, idx))
        {
            printf("QuantityConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(quantityConfigUTRA_present)
    {
        if(0 != quantityConfigUTRA.Unpack(bits, idx))
        {
            printf("QuantityConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(quantityConfigGERAN_present)
    {
        if(0 != quantityConfigGERAN.Unpack(bits, idx))
        {
            printf("QuantityConfig:: field unpack failure\n");
            return -1;
        }
    }
    if(quantityConfigCDMA2000_present)
    {
        if(0 != quantityConfigCDMA2000.Unpack(bits, idx))
        {
            printf("QuantityConfig:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("QuantityConfig::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("QuantityConfig:: Extension list size too large failure\n");
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
                printf("QuantityConfig::Unpack() index out of bounds for optional indiator quantityConfigUTRA_v10x0\n");
                return -1;
            }
            quantityConfigUTRA_v10x0_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("QuantityConfig::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(quantityConfigUTRA_v10x0_present)
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
            if(0 != quantityConfigUTRA_v10x0.Unpack(bits, idx))
            {
                printf("QuantityConfig:: field unpack failure\n");
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
            printf("QuantityConfig::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string QuantityConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "QuantityConfig:\n";
    if(quantityConfigEUTRA_IsPresent())
        out += quantityConfigEUTRA_ToString(indent+1);
    if(quantityConfigUTRA_IsPresent())
        out += quantityConfigUTRA_ToString(indent+1);
    if(quantityConfigGERAN_IsPresent())
        out += quantityConfigGERAN_ToString(indent+1);
    if(quantityConfigCDMA2000_IsPresent())
        out += quantityConfigCDMA2000_ToString(indent+1);
    if(quantityConfigUTRA_v10x0_IsPresent())
        out += quantityConfigUTRA_v10x0_ToString(indent+1);
    return out;
}

std::string QuantityConfig::ToStringNoNewLines() const
{
    std::string out = "QuantityConfig:";
    if(quantityConfigEUTRA_IsPresent())
        out += quantityConfigEUTRA_ToStringNoNewLines();
    if(quantityConfigUTRA_IsPresent())
        out += quantityConfigUTRA_ToStringNoNewLines();
    if(quantityConfigGERAN_IsPresent())
        out += quantityConfigGERAN_ToStringNoNewLines();
    if(quantityConfigCDMA2000_IsPresent())
        out += quantityConfigCDMA2000_ToStringNoNewLines();
    if(quantityConfigUTRA_v10x0_IsPresent())
        out += quantityConfigUTRA_v10x0_ToStringNoNewLines();
    return out;
}

QuantityConfigEUTRA* QuantityConfig::quantityConfigEUTRA_Set()
{
    quantityConfigEUTRA_present = true;
    return &quantityConfigEUTRA;
}

int QuantityConfig::quantityConfigEUTRA_Set(QuantityConfigEUTRA &value)
{
    quantityConfigEUTRA_present = true;
    quantityConfigEUTRA = value;
    return 0;
}

const QuantityConfigEUTRA& QuantityConfig::quantityConfigEUTRA_Get() const
{
    return quantityConfigEUTRA;
}

std::string QuantityConfig::quantityConfigEUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "quantityConfigEUTRA:\n";
    out += quantityConfigEUTRA.ToString(indent+1);
    return out;
}

std::string QuantityConfig::quantityConfigEUTRA_ToStringNoNewLines() const
{
    std::string out = "quantityConfigEUTRA:";
    out += quantityConfigEUTRA.ToStringNoNewLines();
    return out;
}

int QuantityConfig::quantityConfigEUTRA_Clear()
{
    quantityConfigEUTRA_present = false;
    return 0;
}

bool QuantityConfig::quantityConfigEUTRA_IsPresent() const
{
    return quantityConfigEUTRA_present;
}

QuantityConfigUTRA* QuantityConfig::quantityConfigUTRA_Set()
{
    quantityConfigUTRA_present = true;
    return &quantityConfigUTRA;
}

int QuantityConfig::quantityConfigUTRA_Set(QuantityConfigUTRA &value)
{
    quantityConfigUTRA_present = true;
    quantityConfigUTRA = value;
    return 0;
}

const QuantityConfigUTRA& QuantityConfig::quantityConfigUTRA_Get() const
{
    return quantityConfigUTRA;
}

std::string QuantityConfig::quantityConfigUTRA_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "quantityConfigUTRA:\n";
    out += quantityConfigUTRA.ToString(indent+1);
    return out;
}

std::string QuantityConfig::quantityConfigUTRA_ToStringNoNewLines() const
{
    std::string out = "quantityConfigUTRA:";
    out += quantityConfigUTRA.ToStringNoNewLines();
    return out;
}

int QuantityConfig::quantityConfigUTRA_Clear()
{
    quantityConfigUTRA_present = false;
    return 0;
}

bool QuantityConfig::quantityConfigUTRA_IsPresent() const
{
    return quantityConfigUTRA_present;
}

QuantityConfigGERAN* QuantityConfig::quantityConfigGERAN_Set()
{
    quantityConfigGERAN_present = true;
    return &quantityConfigGERAN;
}

int QuantityConfig::quantityConfigGERAN_Set(QuantityConfigGERAN &value)
{
    quantityConfigGERAN_present = true;
    quantityConfigGERAN = value;
    return 0;
}

const QuantityConfigGERAN& QuantityConfig::quantityConfigGERAN_Get() const
{
    return quantityConfigGERAN;
}

std::string QuantityConfig::quantityConfigGERAN_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "quantityConfigGERAN:\n";
    out += quantityConfigGERAN.ToString(indent+1);
    return out;
}

std::string QuantityConfig::quantityConfigGERAN_ToStringNoNewLines() const
{
    std::string out = "quantityConfigGERAN:";
    out += quantityConfigGERAN.ToStringNoNewLines();
    return out;
}

int QuantityConfig::quantityConfigGERAN_Clear()
{
    quantityConfigGERAN_present = false;
    return 0;
}

bool QuantityConfig::quantityConfigGERAN_IsPresent() const
{
    return quantityConfigGERAN_present;
}

QuantityConfigCDMA2000* QuantityConfig::quantityConfigCDMA2000_Set()
{
    quantityConfigCDMA2000_present = true;
    return &quantityConfigCDMA2000;
}

int QuantityConfig::quantityConfigCDMA2000_Set(QuantityConfigCDMA2000 &value)
{
    quantityConfigCDMA2000_present = true;
    quantityConfigCDMA2000 = value;
    return 0;
}

const QuantityConfigCDMA2000& QuantityConfig::quantityConfigCDMA2000_Get() const
{
    return quantityConfigCDMA2000;
}

std::string QuantityConfig::quantityConfigCDMA2000_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "quantityConfigCDMA2000:\n";
    out += quantityConfigCDMA2000.ToString(indent+1);
    return out;
}

std::string QuantityConfig::quantityConfigCDMA2000_ToStringNoNewLines() const
{
    std::string out = "quantityConfigCDMA2000:";
    out += quantityConfigCDMA2000.ToStringNoNewLines();
    return out;
}

int QuantityConfig::quantityConfigCDMA2000_Clear()
{
    quantityConfigCDMA2000_present = false;
    return 0;
}

bool QuantityConfig::quantityConfigCDMA2000_IsPresent() const
{
    return quantityConfigCDMA2000_present;
}

QuantityConfigUTRA_v10x0* QuantityConfig::quantityConfigUTRA_v10x0_Set()
{
    quantityConfigUTRA_v10x0_present = true;
    return &quantityConfigUTRA_v10x0;
}

int QuantityConfig::quantityConfigUTRA_v10x0_Set(QuantityConfigUTRA_v10x0 &value)
{
    quantityConfigUTRA_v10x0_present = true;
    quantityConfigUTRA_v10x0 = value;
    return 0;
}

const QuantityConfigUTRA_v10x0& QuantityConfig::quantityConfigUTRA_v10x0_Get() const
{
    return quantityConfigUTRA_v10x0;
}

std::string QuantityConfig::quantityConfigUTRA_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "quantityConfigUTRA_v10x0:\n";
    out += quantityConfigUTRA_v10x0.ToString(indent+1);
    return out;
}

std::string QuantityConfig::quantityConfigUTRA_v10x0_ToStringNoNewLines() const
{
    std::string out = "quantityConfigUTRA_v10x0:";
    out += quantityConfigUTRA_v10x0.ToStringNoNewLines();
    return out;
}

int QuantityConfig::quantityConfigUTRA_v10x0_Clear()
{
    quantityConfigUTRA_v10x0_present = false;
    return 0;
}

bool QuantityConfig::quantityConfigUTRA_v10x0_IsPresent() const
{
    return quantityConfigUTRA_v10x0_present;
}

