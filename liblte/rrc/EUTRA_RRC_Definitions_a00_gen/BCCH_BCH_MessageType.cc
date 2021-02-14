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

#include "BCCH_BCH_MessageType.h"

#include <cmath>

int BCCH_BCH_MessageType::Pack(std::vector<uint8_t> &bits)
{
    return MasterInformationBlock_value.Pack(bits);
}

int BCCH_BCH_MessageType::Unpack(std::vector<uint8_t> &bits)
{
    return MasterInformationBlock_value.Unpack(bits);
}

int BCCH_BCH_MessageType::Unpack(std::vector<uint8_t> &bits, uint32_t &idx)
{
    return MasterInformationBlock_value.Unpack(bits, idx);
}

std::string BCCH_BCH_MessageType::ToString(uint32_t indent) const
{
    return MasterInformationBlock_value.ToString(indent);
}

std::string BCCH_BCH_MessageType::ToStringNoNewLines() const
{
    return MasterInformationBlock_value.ToStringNoNewLines();
}

MasterInformationBlock* BCCH_BCH_MessageType::MasterInformationBlock_value_Set()
{
    MasterInformationBlock_value_present = true;
    return &MasterInformationBlock_value;
}

int BCCH_BCH_MessageType::MasterInformationBlock_value_Set(MasterInformationBlock &value)
{
    MasterInformationBlock_value_present = true;
    MasterInformationBlock_value = value;
    return 0;
}

const MasterInformationBlock& BCCH_BCH_MessageType::MasterInformationBlock_value_Get() const
{
    return MasterInformationBlock_value;
}

std::string BCCH_BCH_MessageType::MasterInformationBlock_value_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "BCCH_BCH_MessageType:\n";
    out += MasterInformationBlock_value.ToString(indent+1);
    return out;
}

std::string BCCH_BCH_MessageType::MasterInformationBlock_value_ToStringNoNewLines() const
{
    std::string out = "BCCH_BCH_MessageType:";
    out += MasterInformationBlock_value.ToStringNoNewLines();
    return out;
}

int BCCH_BCH_MessageType::MasterInformationBlock_value_Clear()
{
    MasterInformationBlock_value_present = false;
    return 0;
}

bool BCCH_BCH_MessageType::MasterInformationBlock_value_IsPresent() const
{
    return MasterInformationBlock_value_present;
}

