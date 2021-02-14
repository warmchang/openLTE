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

#include "VarLogMeasConfig.h"

#include <cmath>

int VarLogMeasConfig::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != loggedMeasurementsConfiguration_r10.Pack(bits))
        {
            printf("VarLogMeasConfig:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != plmn_Identity_r10.Pack(bits))
        {
            printf("VarLogMeasConfig:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int VarLogMeasConfig::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int VarLogMeasConfig::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != loggedMeasurementsConfiguration_r10.Unpack(bits, idx))
        {
            printf("VarLogMeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != plmn_Identity_r10.Unpack(bits, idx))
        {
            printf("VarLogMeasConfig:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string VarLogMeasConfig::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "VarLogMeasConfig:\n";
    out += loggedMeasurementsConfiguration_r10_ToString(indent+1);
    out += plmn_Identity_r10_ToString(indent+1);
    return out;
}

std::string VarLogMeasConfig::ToStringNoNewLines() const
{
    std::string out = "VarLogMeasConfig:";
    out += loggedMeasurementsConfiguration_r10_ToStringNoNewLines();
    out += plmn_Identity_r10_ToStringNoNewLines();
    return out;
}

LoggedMeasurementsConfiguration_r10* VarLogMeasConfig::loggedMeasurementsConfiguration_r10_Set()
{
    loggedMeasurementsConfiguration_r10_present = true;
    return &loggedMeasurementsConfiguration_r10;
}

int VarLogMeasConfig::loggedMeasurementsConfiguration_r10_Set(LoggedMeasurementsConfiguration_r10 &value)
{
    loggedMeasurementsConfiguration_r10_present = true;
    loggedMeasurementsConfiguration_r10 = value;
    return 0;
}

const LoggedMeasurementsConfiguration_r10& VarLogMeasConfig::loggedMeasurementsConfiguration_r10_Get() const
{
    return loggedMeasurementsConfiguration_r10;
}

std::string VarLogMeasConfig::loggedMeasurementsConfiguration_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "loggedMeasurementsConfiguration_r10:\n";
    out += loggedMeasurementsConfiguration_r10.ToString(indent+1);
    return out;
}

std::string VarLogMeasConfig::loggedMeasurementsConfiguration_r10_ToStringNoNewLines() const
{
    std::string out = "loggedMeasurementsConfiguration_r10:";
    out += loggedMeasurementsConfiguration_r10.ToStringNoNewLines();
    return out;
}

int VarLogMeasConfig::loggedMeasurementsConfiguration_r10_Clear()
{
    loggedMeasurementsConfiguration_r10_present = false;
    return 0;
}

bool VarLogMeasConfig::loggedMeasurementsConfiguration_r10_IsPresent() const
{
    return loggedMeasurementsConfiguration_r10_present;
}

PLMN_Identity* VarLogMeasConfig::plmn_Identity_r10_Set()
{
    plmn_Identity_r10_present = true;
    return &plmn_Identity_r10;
}

int VarLogMeasConfig::plmn_Identity_r10_Set(PLMN_Identity &value)
{
    plmn_Identity_r10_present = true;
    plmn_Identity_r10 = value;
    return 0;
}

const PLMN_Identity& VarLogMeasConfig::plmn_Identity_r10_Get() const
{
    return plmn_Identity_r10;
}

std::string VarLogMeasConfig::plmn_Identity_r10_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_Identity_r10:\n";
    out += plmn_Identity_r10.ToString(indent+1);
    return out;
}

std::string VarLogMeasConfig::plmn_Identity_r10_ToStringNoNewLines() const
{
    std::string out = "plmn_Identity_r10:";
    out += plmn_Identity_r10.ToStringNoNewLines();
    return out;
}

int VarLogMeasConfig::plmn_Identity_r10_Clear()
{
    plmn_Identity_r10_present = false;
    return 0;
}

bool VarLogMeasConfig::plmn_Identity_r10_IsPresent() const
{
    return plmn_Identity_r10_present;
}

