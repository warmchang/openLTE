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

#include "RadioResourceConfigCommon.h"

#include <cmath>

int RadioResourceConfigCommon::Pack(std::vector<uint8_t> &bits)
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
    bits.push_back(rach_ConfigCommon_IsPresent());
    bits.push_back(pdsch_ConfigCommon_IsPresent());
    bits.push_back(phich_Config_IsPresent());
    bits.push_back(pucch_ConfigCommon_IsPresent());
    bits.push_back(soundingRS_UL_ConfigCommon_IsPresent());
    bits.push_back(uplinkPowerControlCommon_IsPresent());
    bits.push_back(antennaInfoCommon_IsPresent());
    bits.push_back(p_Max_IsPresent());
    bits.push_back(tdd_Config_IsPresent());

    // Fields
    if(rach_ConfigCommon_IsPresent())
    {
        if(0 != rach_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != prach_Config.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    if(pdsch_ConfigCommon_IsPresent())
    {
        if(0 != pdsch_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != pusch_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    if(phich_Config_IsPresent())
    {
        if(0 != phich_Config.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    if(pucch_ConfigCommon_IsPresent())
    {
        if(0 != pucch_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigCommon_IsPresent())
    {
        if(0 != soundingRS_UL_ConfigCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    if(uplinkPowerControlCommon_IsPresent())
    {
        if(0 != uplinkPowerControlCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    if(antennaInfoCommon_IsPresent())
    {
        if(0 != antennaInfoCommon.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    if(p_Max_IsPresent())
    {
        if(0 != p_Max.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    if(tdd_Config_IsPresent())
    {
        if(0 != tdd_Config.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != ul_CyclicPrefixLength.Pack(bits))
        {
            printf("RadioResourceConfigCommon:: field pack failure\n");
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
            printf("RadioResourceConfigCommon:: Extension list size too large failure\n");
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
                printf("RadioResourceConfigCommon:: field pack failure\n");
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

int RadioResourceConfigCommon::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int RadioResourceConfigCommon::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator rach_ConfigCommon\n");
        return -1;
    }
    rach_ConfigCommon_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator pdsch_ConfigCommon\n");
        return -1;
    }
    pdsch_ConfigCommon_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator phich_Config\n");
        return -1;
    }
    phich_Config_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator pucch_ConfigCommon\n");
        return -1;
    }
    pucch_ConfigCommon_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator soundingRS_UL_ConfigCommon\n");
        return -1;
    }
    soundingRS_UL_ConfigCommon_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator uplinkPowerControlCommon\n");
        return -1;
    }
    uplinkPowerControlCommon_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator antennaInfoCommon\n");
        return -1;
    }
    antennaInfoCommon_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator p_Max\n");
        return -1;
    }
    p_Max_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator tdd_Config\n");
        return -1;
    }
    tdd_Config_present = bits[idx++];

    // Fields
    if(rach_ConfigCommon_present)
    {
        if(0 != rach_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != prach_Config.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    if(pdsch_ConfigCommon_present)
    {
        if(0 != pdsch_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != pusch_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    if(phich_Config_present)
    {
        if(0 != phich_Config.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    if(pucch_ConfigCommon_present)
    {
        if(0 != pucch_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    if(soundingRS_UL_ConfigCommon_present)
    {
        if(0 != soundingRS_UL_ConfigCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    if(uplinkPowerControlCommon_present)
    {
        if(0 != uplinkPowerControlCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    if(antennaInfoCommon_present)
    {
        if(0 != antennaInfoCommon.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    if(p_Max_present)
    {
        if(0 != p_Max.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    if(tdd_Config_present)
    {
        if(0 != tdd_Config.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != ul_CyclicPrefixLength.Unpack(bits, idx))
        {
            printf("RadioResourceConfigCommon:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("RadioResourceConfigCommon::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("RadioResourceConfigCommon:: Extension list size too large failure\n");
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
                printf("RadioResourceConfigCommon::Unpack() index out of bounds for optional indiator uplinkPowerControlCommon_v10x0\n");
                return -1;
            }
            uplinkPowerControlCommon_v10x0_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("RadioResourceConfigCommon::Unpack() index out of bounds for extension optional indicators\n");
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
                printf("RadioResourceConfigCommon:: field unpack failure\n");
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
            printf("RadioResourceConfigCommon::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string RadioResourceConfigCommon::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "RadioResourceConfigCommon:\n";
    if(rach_ConfigCommon_IsPresent())
        out += rach_ConfigCommon_ToString(indent+1);
    out += prach_Config_ToString(indent+1);
    if(pdsch_ConfigCommon_IsPresent())
        out += pdsch_ConfigCommon_ToString(indent+1);
    out += pusch_ConfigCommon_ToString(indent+1);
    if(phich_Config_IsPresent())
        out += phich_Config_ToString(indent+1);
    if(pucch_ConfigCommon_IsPresent())
        out += pucch_ConfigCommon_ToString(indent+1);
    if(soundingRS_UL_ConfigCommon_IsPresent())
        out += soundingRS_UL_ConfigCommon_ToString(indent+1);
    if(uplinkPowerControlCommon_IsPresent())
        out += uplinkPowerControlCommon_ToString(indent+1);
    if(antennaInfoCommon_IsPresent())
        out += antennaInfoCommon_ToString(indent+1);
    if(p_Max_IsPresent())
        out += p_Max_ToString(indent+1);
    if(tdd_Config_IsPresent())
        out += tdd_Config_ToString(indent+1);
    out += ul_CyclicPrefixLength_ToString(indent+1);
    if(uplinkPowerControlCommon_v10x0_IsPresent())
        out += uplinkPowerControlCommon_v10x0_ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::ToStringNoNewLines() const
{
    std::string out = "RadioResourceConfigCommon:";
    if(rach_ConfigCommon_IsPresent())
        out += rach_ConfigCommon_ToStringNoNewLines();
    out += prach_Config_ToStringNoNewLines();
    if(pdsch_ConfigCommon_IsPresent())
        out += pdsch_ConfigCommon_ToStringNoNewLines();
    out += pusch_ConfigCommon_ToStringNoNewLines();
    if(phich_Config_IsPresent())
        out += phich_Config_ToStringNoNewLines();
    if(pucch_ConfigCommon_IsPresent())
        out += pucch_ConfigCommon_ToStringNoNewLines();
    if(soundingRS_UL_ConfigCommon_IsPresent())
        out += soundingRS_UL_ConfigCommon_ToStringNoNewLines();
    if(uplinkPowerControlCommon_IsPresent())
        out += uplinkPowerControlCommon_ToStringNoNewLines();
    if(antennaInfoCommon_IsPresent())
        out += antennaInfoCommon_ToStringNoNewLines();
    if(p_Max_IsPresent())
        out += p_Max_ToStringNoNewLines();
    if(tdd_Config_IsPresent())
        out += tdd_Config_ToStringNoNewLines();
    out += ul_CyclicPrefixLength_ToStringNoNewLines();
    if(uplinkPowerControlCommon_v10x0_IsPresent())
        out += uplinkPowerControlCommon_v10x0_ToStringNoNewLines();
    return out;
}

RACH_ConfigCommon* RadioResourceConfigCommon::rach_ConfigCommon_Set()
{
    rach_ConfigCommon_present = true;
    return &rach_ConfigCommon;
}

int RadioResourceConfigCommon::rach_ConfigCommon_Set(RACH_ConfigCommon &value)
{
    rach_ConfigCommon_present = true;
    rach_ConfigCommon = value;
    return 0;
}

const RACH_ConfigCommon& RadioResourceConfigCommon::rach_ConfigCommon_Get() const
{
    return rach_ConfigCommon;
}

std::string RadioResourceConfigCommon::rach_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rach_ConfigCommon:\n";
    out += rach_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::rach_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "rach_ConfigCommon:";
    out += rach_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::rach_ConfigCommon_Clear()
{
    rach_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommon::rach_ConfigCommon_IsPresent() const
{
    return rach_ConfigCommon_present;
}

PRACH_Config* RadioResourceConfigCommon::prach_Config_Set()
{
    prach_Config_present = true;
    return &prach_Config;
}

int RadioResourceConfigCommon::prach_Config_Set(PRACH_Config &value)
{
    prach_Config_present = true;
    prach_Config = value;
    return 0;
}

const PRACH_Config& RadioResourceConfigCommon::prach_Config_Get() const
{
    return prach_Config;
}

std::string RadioResourceConfigCommon::prach_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "prach_Config:\n";
    out += prach_Config.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::prach_Config_ToStringNoNewLines() const
{
    std::string out = "prach_Config:";
    out += prach_Config.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::prach_Config_Clear()
{
    prach_Config_present = false;
    return 0;
}

bool RadioResourceConfigCommon::prach_Config_IsPresent() const
{
    return prach_Config_present;
}

PDSCH_ConfigCommon* RadioResourceConfigCommon::pdsch_ConfigCommon_Set()
{
    pdsch_ConfigCommon_present = true;
    return &pdsch_ConfigCommon;
}

int RadioResourceConfigCommon::pdsch_ConfigCommon_Set(PDSCH_ConfigCommon &value)
{
    pdsch_ConfigCommon_present = true;
    pdsch_ConfigCommon = value;
    return 0;
}

const PDSCH_ConfigCommon& RadioResourceConfigCommon::pdsch_ConfigCommon_Get() const
{
    return pdsch_ConfigCommon;
}

std::string RadioResourceConfigCommon::pdsch_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pdsch_ConfigCommon:\n";
    out += pdsch_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::pdsch_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "pdsch_ConfigCommon:";
    out += pdsch_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::pdsch_ConfigCommon_Clear()
{
    pdsch_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommon::pdsch_ConfigCommon_IsPresent() const
{
    return pdsch_ConfigCommon_present;
}

PUSCH_ConfigCommon* RadioResourceConfigCommon::pusch_ConfigCommon_Set()
{
    pusch_ConfigCommon_present = true;
    return &pusch_ConfigCommon;
}

int RadioResourceConfigCommon::pusch_ConfigCommon_Set(PUSCH_ConfigCommon &value)
{
    pusch_ConfigCommon_present = true;
    pusch_ConfigCommon = value;
    return 0;
}

const PUSCH_ConfigCommon& RadioResourceConfigCommon::pusch_ConfigCommon_Get() const
{
    return pusch_ConfigCommon;
}

std::string RadioResourceConfigCommon::pusch_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pusch_ConfigCommon:\n";
    out += pusch_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::pusch_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "pusch_ConfigCommon:";
    out += pusch_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::pusch_ConfigCommon_Clear()
{
    pusch_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommon::pusch_ConfigCommon_IsPresent() const
{
    return pusch_ConfigCommon_present;
}

PHICH_Config* RadioResourceConfigCommon::phich_Config_Set()
{
    phich_Config_present = true;
    return &phich_Config;
}

int RadioResourceConfigCommon::phich_Config_Set(PHICH_Config &value)
{
    phich_Config_present = true;
    phich_Config = value;
    return 0;
}

const PHICH_Config& RadioResourceConfigCommon::phich_Config_Get() const
{
    return phich_Config;
}

std::string RadioResourceConfigCommon::phich_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "phich_Config:\n";
    out += phich_Config.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::phich_Config_ToStringNoNewLines() const
{
    std::string out = "phich_Config:";
    out += phich_Config.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::phich_Config_Clear()
{
    phich_Config_present = false;
    return 0;
}

bool RadioResourceConfigCommon::phich_Config_IsPresent() const
{
    return phich_Config_present;
}

PUCCH_ConfigCommon* RadioResourceConfigCommon::pucch_ConfigCommon_Set()
{
    pucch_ConfigCommon_present = true;
    return &pucch_ConfigCommon;
}

int RadioResourceConfigCommon::pucch_ConfigCommon_Set(PUCCH_ConfigCommon &value)
{
    pucch_ConfigCommon_present = true;
    pucch_ConfigCommon = value;
    return 0;
}

const PUCCH_ConfigCommon& RadioResourceConfigCommon::pucch_ConfigCommon_Get() const
{
    return pucch_ConfigCommon;
}

std::string RadioResourceConfigCommon::pucch_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "pucch_ConfigCommon:\n";
    out += pucch_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::pucch_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "pucch_ConfigCommon:";
    out += pucch_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::pucch_ConfigCommon_Clear()
{
    pucch_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommon::pucch_ConfigCommon_IsPresent() const
{
    return pucch_ConfigCommon_present;
}

SoundingRS_UL_ConfigCommon* RadioResourceConfigCommon::soundingRS_UL_ConfigCommon_Set()
{
    soundingRS_UL_ConfigCommon_present = true;
    return &soundingRS_UL_ConfigCommon;
}

int RadioResourceConfigCommon::soundingRS_UL_ConfigCommon_Set(SoundingRS_UL_ConfigCommon &value)
{
    soundingRS_UL_ConfigCommon_present = true;
    soundingRS_UL_ConfigCommon = value;
    return 0;
}

const SoundingRS_UL_ConfigCommon& RadioResourceConfigCommon::soundingRS_UL_ConfigCommon_Get() const
{
    return soundingRS_UL_ConfigCommon;
}

std::string RadioResourceConfigCommon::soundingRS_UL_ConfigCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "soundingRS_UL_ConfigCommon:\n";
    out += soundingRS_UL_ConfigCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::soundingRS_UL_ConfigCommon_ToStringNoNewLines() const
{
    std::string out = "soundingRS_UL_ConfigCommon:";
    out += soundingRS_UL_ConfigCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::soundingRS_UL_ConfigCommon_Clear()
{
    soundingRS_UL_ConfigCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommon::soundingRS_UL_ConfigCommon_IsPresent() const
{
    return soundingRS_UL_ConfigCommon_present;
}

UplinkPowerControlCommon* RadioResourceConfigCommon::uplinkPowerControlCommon_Set()
{
    uplinkPowerControlCommon_present = true;
    return &uplinkPowerControlCommon;
}

int RadioResourceConfigCommon::uplinkPowerControlCommon_Set(UplinkPowerControlCommon &value)
{
    uplinkPowerControlCommon_present = true;
    uplinkPowerControlCommon = value;
    return 0;
}

const UplinkPowerControlCommon& RadioResourceConfigCommon::uplinkPowerControlCommon_Get() const
{
    return uplinkPowerControlCommon;
}

std::string RadioResourceConfigCommon::uplinkPowerControlCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "uplinkPowerControlCommon:\n";
    out += uplinkPowerControlCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::uplinkPowerControlCommon_ToStringNoNewLines() const
{
    std::string out = "uplinkPowerControlCommon:";
    out += uplinkPowerControlCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::uplinkPowerControlCommon_Clear()
{
    uplinkPowerControlCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommon::uplinkPowerControlCommon_IsPresent() const
{
    return uplinkPowerControlCommon_present;
}

AntennaInfoCommon* RadioResourceConfigCommon::antennaInfoCommon_Set()
{
    antennaInfoCommon_present = true;
    return &antennaInfoCommon;
}

int RadioResourceConfigCommon::antennaInfoCommon_Set(AntennaInfoCommon &value)
{
    antennaInfoCommon_present = true;
    antennaInfoCommon = value;
    return 0;
}

const AntennaInfoCommon& RadioResourceConfigCommon::antennaInfoCommon_Get() const
{
    return antennaInfoCommon;
}

std::string RadioResourceConfigCommon::antennaInfoCommon_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "antennaInfoCommon:\n";
    out += antennaInfoCommon.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::antennaInfoCommon_ToStringNoNewLines() const
{
    std::string out = "antennaInfoCommon:";
    out += antennaInfoCommon.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::antennaInfoCommon_Clear()
{
    antennaInfoCommon_present = false;
    return 0;
}

bool RadioResourceConfigCommon::antennaInfoCommon_IsPresent() const
{
    return antennaInfoCommon_present;
}

P_Max* RadioResourceConfigCommon::p_Max_Set()
{
    p_Max_present = true;
    return &p_Max;
}

int RadioResourceConfigCommon::p_Max_Set(P_Max &value)
{
    p_Max_present = true;
    p_Max = value;
    return 0;
}

const P_Max& RadioResourceConfigCommon::p_Max_Get() const
{
    return p_Max;
}

std::string RadioResourceConfigCommon::p_Max_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "p_Max:\n";
    out += p_Max.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::p_Max_ToStringNoNewLines() const
{
    std::string out = "p_Max:";
    out += p_Max.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::p_Max_Clear()
{
    p_Max_present = false;
    return 0;
}

bool RadioResourceConfigCommon::p_Max_IsPresent() const
{
    return p_Max_present;
}

TDD_Config* RadioResourceConfigCommon::tdd_Config_Set()
{
    tdd_Config_present = true;
    return &tdd_Config;
}

int RadioResourceConfigCommon::tdd_Config_Set(TDD_Config &value)
{
    tdd_Config_present = true;
    tdd_Config = value;
    return 0;
}

const TDD_Config& RadioResourceConfigCommon::tdd_Config_Get() const
{
    return tdd_Config;
}

std::string RadioResourceConfigCommon::tdd_Config_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "tdd_Config:\n";
    out += tdd_Config.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::tdd_Config_ToStringNoNewLines() const
{
    std::string out = "tdd_Config:";
    out += tdd_Config.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::tdd_Config_Clear()
{
    tdd_Config_present = false;
    return 0;
}

bool RadioResourceConfigCommon::tdd_Config_IsPresent() const
{
    return tdd_Config_present;
}

UL_CyclicPrefixLength* RadioResourceConfigCommon::ul_CyclicPrefixLength_Set()
{
    ul_CyclicPrefixLength_present = true;
    return &ul_CyclicPrefixLength;
}

int RadioResourceConfigCommon::ul_CyclicPrefixLength_Set(UL_CyclicPrefixLength &value)
{
    ul_CyclicPrefixLength_present = true;
    ul_CyclicPrefixLength = value;
    return 0;
}

const UL_CyclicPrefixLength& RadioResourceConfigCommon::ul_CyclicPrefixLength_Get() const
{
    return ul_CyclicPrefixLength;
}

std::string RadioResourceConfigCommon::ul_CyclicPrefixLength_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "ul_CyclicPrefixLength:\n";
    out += ul_CyclicPrefixLength.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::ul_CyclicPrefixLength_ToStringNoNewLines() const
{
    std::string out = "ul_CyclicPrefixLength:";
    out += ul_CyclicPrefixLength.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::ul_CyclicPrefixLength_Clear()
{
    ul_CyclicPrefixLength_present = false;
    return 0;
}

bool RadioResourceConfigCommon::ul_CyclicPrefixLength_IsPresent() const
{
    return ul_CyclicPrefixLength_present;
}

UplinkPowerControlCommon_v10x0* RadioResourceConfigCommon::uplinkPowerControlCommon_v10x0_Set()
{
    uplinkPowerControlCommon_v10x0_present = true;
    return &uplinkPowerControlCommon_v10x0;
}

int RadioResourceConfigCommon::uplinkPowerControlCommon_v10x0_Set(UplinkPowerControlCommon_v10x0 &value)
{
    uplinkPowerControlCommon_v10x0_present = true;
    uplinkPowerControlCommon_v10x0 = value;
    return 0;
}

const UplinkPowerControlCommon_v10x0& RadioResourceConfigCommon::uplinkPowerControlCommon_v10x0_Get() const
{
    return uplinkPowerControlCommon_v10x0;
}

std::string RadioResourceConfigCommon::uplinkPowerControlCommon_v10x0_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "uplinkPowerControlCommon_v10x0:\n";
    out += uplinkPowerControlCommon_v10x0.ToString(indent+1);
    return out;
}

std::string RadioResourceConfigCommon::uplinkPowerControlCommon_v10x0_ToStringNoNewLines() const
{
    std::string out = "uplinkPowerControlCommon_v10x0:";
    out += uplinkPowerControlCommon_v10x0.ToStringNoNewLines();
    return out;
}

int RadioResourceConfigCommon::uplinkPowerControlCommon_v10x0_Clear()
{
    uplinkPowerControlCommon_v10x0_present = false;
    return 0;
}

bool RadioResourceConfigCommon::uplinkPowerControlCommon_v10x0_IsPresent() const
{
    return uplinkPowerControlCommon_v10x0_present;
}

