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

#ifndef __CellInfoGERAN_r9_H__
#define __CellInfoGERAN_r9_H__

#include "PhysCellIdGERAN.h"
#include "CarrierFreqGERAN.h"
#include "SystemInfoListGERAN.h"

#include <array>
#include <cstdint>
#include <vector>

class CellInfoGERAN_r9
{
public:
    CellInfoGERAN_r9() : physCellId_r9_present{false}, carrierFreq_r9_present{false}, systemInformation_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // physCellId-r9
public:
    PhysCellIdGERAN* physCellId_r9_Set();
    int physCellId_r9_Set(PhysCellIdGERAN &value);
    const PhysCellIdGERAN& physCellId_r9_Get() const;
    std::string physCellId_r9_ToString(uint32_t indent) const;
    std::string physCellId_r9_ToStringNoNewLines() const;
    int physCellId_r9_Clear();
    bool physCellId_r9_IsPresent() const;
private:
    bool physCellId_r9_present;
    PhysCellIdGERAN physCellId_r9;

    // carrierFreq-r9
public:
    CarrierFreqGERAN* carrierFreq_r9_Set();
    int carrierFreq_r9_Set(CarrierFreqGERAN &value);
    const CarrierFreqGERAN& carrierFreq_r9_Get() const;
    std::string carrierFreq_r9_ToString(uint32_t indent) const;
    std::string carrierFreq_r9_ToStringNoNewLines() const;
    int carrierFreq_r9_Clear();
    bool carrierFreq_r9_IsPresent() const;
private:
    bool carrierFreq_r9_present;
    CarrierFreqGERAN carrierFreq_r9;

    // systemInformation-r9
public:
    SystemInfoListGERAN* systemInformation_r9_Set();
    int systemInformation_r9_Set(SystemInfoListGERAN &value);
    const SystemInfoListGERAN& systemInformation_r9_Get() const;
    std::string systemInformation_r9_ToString(uint32_t indent) const;
    std::string systemInformation_r9_ToStringNoNewLines() const;
    int systemInformation_r9_Clear();
    bool systemInformation_r9_IsPresent() const;
private:
    bool systemInformation_r9_present;
    SystemInfoListGERAN systemInformation_r9;

};

#endif
