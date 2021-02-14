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

#include "SPS_Config.h"

#include <cmath>

int SPS_Config::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(semiPersistSchedC_RNTI_IsPresent());
    bits.push_back(sps_ConfigDL_IsPresent());
    bits.push_back(sps_ConfigUL_IsPresent());

    // Fields
    if(semiPersistSchedC_RNTI_IsPresent())
    {
        if(0 != semiPersistSchedC_RNTI.Pack(bits))
        {
            printf("SPS_Config:: field pack failure\n");
            return -1;
        }
    }
    if(sps_ConfigDL_IsPresent())
    {
        if(0 != sps_ConfigDL.Pack(bits))
        {
            printf("SPS_Config:: field pack failure\n");
            return -1;
        }
    }
    if(sps_ConfigUL_IsPresent())
    {
        if(0 != sps_ConfigUL.Pack(bits))
        {
            printf("SPS_Config:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int SPS_Config::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int SPS_Config::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("SPS_Config::Unpack() index out of bounds for optional indiator semiPersistSchedC_RNTI\n");
        return -1;
    }
    semiPersistSchedC_RNTI_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SPS_Config::Unpack() index out of bounds for optional indiator sps_ConfigDL\n");
        return -1;
    }
    sps_ConfigDL_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("SPS_Config::Unpack() index out of bounds for optional indiator sps_ConfigUL\n");
        return -1;
    }
    sps_ConfigUL_present = bits[idx++];

    // Fields
    if(semiPersistSchedC_RNTI_present)
    {
        if(0 != semiPersistSchedC_RNTI.Unpack(bits, idx))
        {
            printf("SPS_Config:: field unpack failure\n");
            return -1;
        }
    }
    if(sps_ConfigDL_present)
    {
        if(0 != sps_ConfigDL.Unpack(bits, idx))
        {
            printf("SPS_Config:: field unpack failure\n");
            return -1;
        }
    }
    if(sps_ConfigUL_present)
    {
        if(0 != sps_ConfigUL.Unpack(bits, idx))
        {
            printf("SPS_Config:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string SPS_Config::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "SPS_Config:\n";
    if(semiPersistSchedC_RNTI_IsPresent())
        out += semiPersistSchedC_RNTI_ToString(indent+1);
    if(sps_ConfigDL_IsPresent())
        out += sps_ConfigDL_ToString(indent+1);
    if(sps_ConfigUL_IsPresent())
        out += sps_ConfigUL_ToString(indent+1);
    return out;
}

std::string SPS_Config::ToStringNoNewLines() const
{
    std::string out = "SPS_Config:";
    if(semiPersistSchedC_RNTI_IsPresent())
        out += semiPersistSchedC_RNTI_ToStringNoNewLines();
    if(sps_ConfigDL_IsPresent())
        out += sps_ConfigDL_ToStringNoNewLines();
    if(sps_ConfigUL_IsPresent())
        out += sps_ConfigUL_ToStringNoNewLines();
    return out;
}

C_RNTI* SPS_Config::semiPersistSchedC_RNTI_Set()
{
    semiPersistSchedC_RNTI_present = true;
    return &semiPersistSchedC_RNTI;
}

int SPS_Config::semiPersistSchedC_RNTI_Set(C_RNTI &value)
{
    semiPersistSchedC_RNTI_present = true;
    semiPersistSchedC_RNTI = value;
    return 0;
}

const C_RNTI& SPS_Config::semiPersistSchedC_RNTI_Get() const
{
    return semiPersistSchedC_RNTI;
}

std::string SPS_Config::semiPersistSchedC_RNTI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "semiPersistSchedC_RNTI:\n";
    out += semiPersistSchedC_RNTI.ToString(indent+1);
    return out;
}

std::string SPS_Config::semiPersistSchedC_RNTI_ToStringNoNewLines() const
{
    std::string out = "semiPersistSchedC_RNTI:";
    out += semiPersistSchedC_RNTI.ToStringNoNewLines();
    return out;
}

int SPS_Config::semiPersistSchedC_RNTI_Clear()
{
    semiPersistSchedC_RNTI_present = false;
    return 0;
}

bool SPS_Config::semiPersistSchedC_RNTI_IsPresent() const
{
    return semiPersistSchedC_RNTI_present;
}

SPS_ConfigDL* SPS_Config::sps_ConfigDL_Set()
{
    sps_ConfigDL_present = true;
    return &sps_ConfigDL;
}

int SPS_Config::sps_ConfigDL_Set(SPS_ConfigDL &value)
{
    sps_ConfigDL_present = true;
    sps_ConfigDL = value;
    return 0;
}

const SPS_ConfigDL& SPS_Config::sps_ConfigDL_Get() const
{
    return sps_ConfigDL;
}

std::string SPS_Config::sps_ConfigDL_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sps_ConfigDL:\n";
    out += sps_ConfigDL.ToString(indent+1);
    return out;
}

std::string SPS_Config::sps_ConfigDL_ToStringNoNewLines() const
{
    std::string out = "sps_ConfigDL:";
    out += sps_ConfigDL.ToStringNoNewLines();
    return out;
}

int SPS_Config::sps_ConfigDL_Clear()
{
    sps_ConfigDL_present = false;
    return 0;
}

bool SPS_Config::sps_ConfigDL_IsPresent() const
{
    return sps_ConfigDL_present;
}

SPS_ConfigUL* SPS_Config::sps_ConfigUL_Set()
{
    sps_ConfigUL_present = true;
    return &sps_ConfigUL;
}

int SPS_Config::sps_ConfigUL_Set(SPS_ConfigUL &value)
{
    sps_ConfigUL_present = true;
    sps_ConfigUL = value;
    return 0;
}

const SPS_ConfigUL& SPS_Config::sps_ConfigUL_Get() const
{
    return sps_ConfigUL;
}

std::string SPS_Config::sps_ConfigUL_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sps_ConfigUL:\n";
    out += sps_ConfigUL.ToString(indent+1);
    return out;
}

std::string SPS_Config::sps_ConfigUL_ToStringNoNewLines() const
{
    std::string out = "sps_ConfigUL:";
    out += sps_ConfigUL.ToStringNoNewLines();
    return out;
}

int SPS_Config::sps_ConfigUL_Clear()
{
    sps_ConfigUL_present = false;
    return 0;
}

bool SPS_Config::sps_ConfigUL_IsPresent() const
{
    return sps_ConfigUL_present;
}

