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

#ifndef __BCCH_BCH_MessageType_H__
#define __BCCH_BCH_MessageType_H__

#include "MasterInformationBlock.h"

#include <array>
#include <cstdint>
#include <vector>

class BCCH_BCH_MessageType
{
public:
    BCCH_BCH_MessageType() : MasterInformationBlock_value_present{false} {};
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> &bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
public:
    MasterInformationBlock* MasterInformationBlock_value_Set();
    int MasterInformationBlock_value_Set(MasterInformationBlock &value);
    const MasterInformationBlock& MasterInformationBlock_value_Get() const;
    std::string MasterInformationBlock_value_ToString(uint32_t indent) const;
    std::string MasterInformationBlock_value_ToStringNoNewLines() const;
    int MasterInformationBlock_value_Clear();
    bool MasterInformationBlock_value_IsPresent() const;
private:
    bool MasterInformationBlock_value_present;
    MasterInformationBlock MasterInformationBlock_value;
};

#endif
