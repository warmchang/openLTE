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

#include "RadioResourceConfigCommonSIB.h"

#include <cmath>

int RadioResourceConfigCommonSIB::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(uplinkPowerControlCommon_v10x0_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators

    // Fields
    {
        if(0 != rach_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != bcch_Config.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pcch_Config.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != prach_Config.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdsch_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pusch_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pucch_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != soundingRS_UL_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != uplinkPowerControlCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ul_CyclicPrefixLength.Pack(bits))
        {
            printf("RadioResourceConfigCommonSIB:: field pack failure\n");
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
            printf("RadioResourceConfigCommonSIB:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(uplinkPowerControlCommon_v10x0_IsPresent());

        // Extension fields
        if(uplinkPowerControlCommon_v10x0_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != uplinkPowerControlCommon_v10x0.Pack(field_bits))
            {
                printf("RadioResourceConfigCommonSIB:: field pack failure\n");
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

int RadioResourceConfigCommonSIB::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RadioResourceConfigCommonSIB::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommonSIB::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators

    // Fields
    {
        if(0 != rach_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != bcch_Config.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pcch_Config.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != prach_Config.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pdsch_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pusch_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pucch_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != soundingRS_UL_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != uplinkPowerControlCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ul_CyclicPrefixLength.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("RadioResourceConfigCommonSIB::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("RadioResourceConfigCommonSIB:: Extension list size too large failure\n");
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
                printf("RadioResourceConfigCommonSIB::Unpack() index out of bounds for optional indiator uplinkPowerControlCommon_v10x0\n");
                return -1;
            }
            uplinkPowerControlCommon_v10x0_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("RadioResourceConfigCommonSIB::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(uplinkPowerControlCommon_v10x0_present)
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
            if(0 != uplinkPowerControlCommon_v10x0.Unpack(bits, idx))
            {
                printf("RadioResourceConfigCommonSIB:: field unpack failure\n");
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
            printf("RadioResourceConfigCommonSIB::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string RadioResourceConfigCommonSIB::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RadioResourceConfigCommonSIB:\n";
    out += rach_ConfigCommon_ToString(indent+1);
    out += bcch_Config_ToString(indent+1);
    out += pcch_Config_ToString(indent+1);
    out += prach_Config_ToString(indent+1);
    out += pdsch_ConfigCommon_ToString(indent+1);
    out += pusch_ConfigCommon_ToString(indent+1);
    out += pucch_ConfigCommon_ToString(indent+1);
    out += soundingRS_UL_ConfigCommon_ToString(indent+1);
    out += uplinkPowerControlCommon_ToString(indent+1);
    out += ul_CyclicPrefixLength_ToString(indent+1);
    if(uplinkPowerControlCommon_v10x0_IsPresent())
        out += uplinkPowerControlCommon_v10x0_ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::ToStringNoNewLines() const
{
    std::string out = "RadioResourceConfigCommonSIB:";
    out += rach_ConfigCommon_ToStringNoNewLines();
    out += bcch_Config_ToStringNoNewLines();
    out += pcch_Config_ToStringNoNewLines();
    out += prach_Config_ToStringNoNewLines();
    out += pdsch_ConfigCommon_ToStringNoNewLines();
    out += pusch_ConfigCommon_ToStringNoNewLines();
    out += pucch_ConfigCommon_ToStringNoNewLines();
    out += soundingRS_UL_ConfigCommon_ToStringNoNewLines();
    out += uplinkPowerControlCommon_ToStringNoNewLines();
    out += ul_CyclicPrefixLength_ToStringNoNewLines();
    if(uplinkPowerControlCommon_v10x0_IsPresent())
        out += uplinkPowerControlCommon_v10x0_ToStringNoNewLines();
    return out;
}

RACH_ConfigCommon* RadioResourceConfigCommonSIB::rach_ConfigCommon_Set()
{
    rach_ConfigCommon_present = true;
    return &rach_ConfigCommon;
}

int RadioResourceConfigCommonSIB::rach_ConfigCommon_Set(RACH_ConfigCommon &value)
{
    rach_ConfigCommon_present = true;
    rach_ConfigCommon = value;
    return 0;
}

const RACH_ConfigCommon& RadioResourceConfigCommonSIB::rach_ConfigCommon_Get() const
{
    return rach_ConfigCommon;
}

std::string RadioResourceConfigCommonSIB::rach_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rach_ConfigCommon:\n";
    out += rach_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::rach_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "rach_ConfigCommon:";
    out += rach_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::rach_ConfigCommon_Clear()
{
    rach_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::rach_ConfigCommon_IsPresent() const
{
    return rach_ConfigCommon_present;
}

BCCH_Config* RadioResourceConfigCommonSIB::bcch_Config_Set()
{
    bcch_Config_present = true;
    return &bcch_Config;
}

int RadioResourceConfigCommonSIB::bcch_Config_Set(BCCH_Config &value)
{
    bcch_Config_present = true;
    bcch_Config = value;
    return 0;
}

const BCCH_Config& RadioResourceConfigCommonSIB::bcch_Config_Get() const
{
    return bcch_Config;
}

std::string RadioResourceConfigCommonSIB::bcch_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "bcch_Config:\n";
    out += bcch_Config.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::bcch_Config_ToStringNoNewLines() const
{
    std::string out = "bcch_Config:";
    out += bcch_Config.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::bcch_Config_Clear()
{
    bcch_Config_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::bcch_Config_IsPresent() const
{
    return bcch_Config_present;
}

PCCH_Config* RadioResourceConfigCommonSIB::pcch_Config_Set()
{
    pcch_Config_present = true;
    return &pcch_Config;
}

int RadioResourceConfigCommonSIB::pcch_Config_Set(PCCH_Config &value)
{
    pcch_Config_present = true;
    pcch_Config = value;
    return 0;
}

const PCCH_Config& RadioResourceConfigCommonSIB::pcch_Config_Get() const
{
    return pcch_Config;
}

std::string RadioResourceConfigCommonSIB::pcch_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pcch_Config:\n";
    out += pcch_Config.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::pcch_Config_ToStringNoNewLines() const
{
    std::string out = "pcch_Config:";
    out += pcch_Config.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::pcch_Config_Clear()
{
    pcch_Config_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::pcch_Config_IsPresent() const
{
    return pcch_Config_present;
}

PRACH_ConfigSIB* RadioResourceConfigCommonSIB::prach_Config_Set()
{
    prach_Config_present = true;
    return &prach_Config;
}

int RadioResourceConfigCommonSIB::prach_Config_Set(PRACH_ConfigSIB &value)
{
    prach_Config_present = true;
    prach_Config = value;
    return 0;
}

const PRACH_ConfigSIB& RadioResourceConfigCommonSIB::prach_Config_Get() const
{
    return prach_Config;
}

std::string RadioResourceConfigCommonSIB::prach_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "prach_Config:\n";
    out += prach_Config.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::prach_Config_ToStringNoNewLines() const
{
    std::string out = "prach_Config:";
    out += prach_Config.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::prach_Config_Clear()
{
    prach_Config_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::prach_Config_IsPresent() const
{
    return prach_Config_present;
}

PDSCH_ConfigCommon* RadioResourceConfigCommonSIB::pdsch_ConfigCommon_Set()
{
    pdsch_ConfigCommon_present = true;
    return &pdsch_ConfigCommon;
}

int RadioResourceConfigCommonSIB::pdsch_ConfigCommon_Set(PDSCH_ConfigCommon &value)
{
    pdsch_ConfigCommon_present = true;
    pdsch_ConfigCommon = value;
    return 0;
}

const PDSCH_ConfigCommon& RadioResourceConfigCommonSIB::pdsch_ConfigCommon_Get() const
{
    return pdsch_ConfigCommon;
}

std::string RadioResourceConfigCommonSIB::pdsch_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdsch_ConfigCommon:\n";
    out += pdsch_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::pdsch_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "pdsch_ConfigCommon:";
    out += pdsch_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::pdsch_ConfigCommon_Clear()
{
    pdsch_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::pdsch_ConfigCommon_IsPresent() const
{
    return pdsch_ConfigCommon_present;
}

PUSCH_ConfigCommon* RadioResourceConfigCommonSIB::pusch_ConfigCommon_Set()
{
    pusch_ConfigCommon_present = true;
    return &pusch_ConfigCommon;
}

int RadioResourceConfigCommonSIB::pusch_ConfigCommon_Set(PUSCH_ConfigCommon &value)
{
    pusch_ConfigCommon_present = true;
    pusch_ConfigCommon = value;
    return 0;
}

const PUSCH_ConfigCommon& RadioResourceConfigCommonSIB::pusch_ConfigCommon_Get() const
{
    return pusch_ConfigCommon;
}

std::string RadioResourceConfigCommonSIB::pusch_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pusch_ConfigCommon:\n";
    out += pusch_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::pusch_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "pusch_ConfigCommon:";
    out += pusch_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::pusch_ConfigCommon_Clear()
{
    pusch_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::pusch_ConfigCommon_IsPresent() const
{
    return pusch_ConfigCommon_present;
}

PUCCH_ConfigCommon* RadioResourceConfigCommonSIB::pucch_ConfigCommon_Set()
{
    pucch_ConfigCommon_present = true;
    return &pucch_ConfigCommon;
}

int RadioResourceConfigCommonSIB::pucch_ConfigCommon_Set(PUCCH_ConfigCommon &value)
{
    pucch_ConfigCommon_present = true;
    pucch_ConfigCommon = value;
    return 0;
}

const PUCCH_ConfigCommon& RadioResourceConfigCommonSIB::pucch_ConfigCommon_Get() const
{
    return pucch_ConfigCommon;
}

std::string RadioResourceConfigCommonSIB::pucch_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pucch_ConfigCommon:\n";
    out += pucch_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::pucch_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "pucch_ConfigCommon:";
    out += pucch_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::pucch_ConfigCommon_Clear()
{
    pucch_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::pucch_ConfigCommon_IsPresent() const
{
    return pucch_ConfigCommon_present;
}

SoundingRS_UL_ConfigCommon* RadioResourceConfigCommonSIB::soundingRS_UL_ConfigCommon_Set()
{
    soundingRS_UL_ConfigCommon_present = true;
    return &soundingRS_UL_ConfigCommon;
}

int RadioResourceConfigCommonSIB::soundingRS_UL_ConfigCommon_Set(SoundingRS_UL_ConfigCommon &value)
{
    soundingRS_UL_ConfigCommon_present = true;
    soundingRS_UL_ConfigCommon = value;
    return 0;
}

const SoundingRS_UL_ConfigCommon& RadioResourceConfigCommonSIB::soundingRS_UL_ConfigCommon_Get() const
{
    return soundingRS_UL_ConfigCommon;
}

std::string RadioResourceConfigCommonSIB::soundingRS_UL_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "soundingRS_UL_ConfigCommon:\n";
    out += soundingRS_UL_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::soundingRS_UL_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "soundingRS_UL_ConfigCommon:";
    out += soundingRS_UL_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::soundingRS_UL_ConfigCommon_Clear()
{
    soundingRS_UL_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::soundingRS_UL_ConfigCommon_IsPresent() const
{
    return soundingRS_UL_ConfigCommon_present;
}

UplinkPowerControlCommon* RadioResourceConfigCommonSIB::uplinkPowerControlCommon_Set()
{
    uplinkPowerControlCommon_present = true;
    return &uplinkPowerControlCommon;
}

int RadioResourceConfigCommonSIB::uplinkPowerControlCommon_Set(UplinkPowerControlCommon &value)
{
    uplinkPowerControlCommon_present = true;
    uplinkPowerControlCommon = value;
    return 0;
}

const UplinkPowerControlCommon& RadioResourceConfigCommonSIB::uplinkPowerControlCommon_Get() const
{
    return uplinkPowerControlCommon;
}

std::string RadioResourceConfigCommonSIB::uplinkPowerControlCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "uplinkPowerControlCommon:\n";
    out += uplinkPowerControlCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::uplinkPowerControlCommon_ToStringNoNewLines() const
{
    std::string out = "uplinkPowerControlCommon:";
    out += uplinkPowerControlCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::uplinkPowerControlCommon_Clear()
{
    uplinkPowerControlCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::uplinkPowerControlCommon_IsPresent() const
{
    return uplinkPowerControlCommon_present;
}

UL_CyclicPrefixLength* RadioResourceConfigCommonSIB::ul_CyclicPrefixLength_Set()
{
    ul_CyclicPrefixLength_present = true;
    return &ul_CyclicPrefixLength;
}

int RadioResourceConfigCommonSIB::ul_CyclicPrefixLength_Set(UL_CyclicPrefixLength &value)
{
    ul_CyclicPrefixLength_present = true;
    ul_CyclicPrefixLength = value;
    return 0;
}

const UL_CyclicPrefixLength& RadioResourceConfigCommonSIB::ul_CyclicPrefixLength_Get() const
{
    return ul_CyclicPrefixLength;
}

std::string RadioResourceConfigCommonSIB::ul_CyclicPrefixLength_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_CyclicPrefixLength:\n";
    out += ul_CyclicPrefixLength.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::ul_CyclicPrefixLength_ToStringNoNewLines() const
{
    std::string out = "ul_CyclicPrefixLength:";
    out += ul_CyclicPrefixLength.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::ul_CyclicPrefixLength_Clear()
{
    ul_CyclicPrefixLength_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::ul_CyclicPrefixLength_IsPresent() const
{
    return ul_CyclicPrefixLength_present;
}

UplinkPowerControlCommon_v10x0* RadioResourceConfigCommonSIB::uplinkPowerControlCommon_v10x0_Set()
{
    uplinkPowerControlCommon_v10x0_present = true;
    return &uplinkPowerControlCommon_v10x0;
}

int RadioResourceConfigCommonSIB::uplinkPowerControlCommon_v10x0_Set(UplinkPowerControlCommon_v10x0 &value)
{
    uplinkPowerControlCommon_v10x0_present = true;
    uplinkPowerControlCommon_v10x0 = value;
    return 0;
}

const UplinkPowerControlCommon_v10x0& RadioResourceConfigCommonSIB::uplinkPowerControlCommon_v10x0_Get() const
{
    return uplinkPowerControlCommon_v10x0;
}

std::string RadioResourceConfigCommonSIB::uplinkPowerControlCommon_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "uplinkPowerControlCommon_v10x0:\n";
    out += uplinkPowerControlCommon_v10x0.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommonSIB::uplinkPowerControlCommon_v10x0_ToStringNoNewLines() const
{
    std::string out = "uplinkPowerControlCommon_v10x0:";
    out += uplinkPowerControlCommon_v10x0.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommonSIB::uplinkPowerControlCommon_v10x0_Clear()
{
    uplinkPowerControlCommon_v10x0_present = false;
    return 0;
}

bool RadioResourceConfigCommonSIB::uplinkPowerControlCommon_v10x0_IsPresent() const
{
    return uplinkPowerControlCommon_v10x0_present;
}

