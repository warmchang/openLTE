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

#ifndef __RRCConnectionReconfigurationComplete_v10xy_IEs_H__
#define __RRCConnectionReconfigurationComplete_v10xy_IEs_H__

#include <array>
#include <cstdint>
#include <vector>

class RRCConnectionReconfigurationComplete_v10xy_IEs
{
public:
    RRCConnectionReconfigurationComplete_v10xy_IEs() : logMeasAvailable_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // logMeasAvailable-r10
public:
    enum logMeasAvailable_r10_Enum {
        k_logMeasAvailable_r10_true = 0,
    };
    int logMeasAvailable_r10_Pack(std::vector<uint8_t> &bits);
    int logMeasAvailable_r10_Unpack(std::vector<uint8_t> bits);
    int logMeasAvailable_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    logMeasAvailable_r10_Enum logMeasAvailable_r10_Value() const;
    int logMeasAvailable_r10_SetValue(logMeasAvailable_r10_Enum value);
    int logMeasAvailable_r10_SetValue(std::string value);
    std::string logMeasAvailable_r10_ValueToString(logMeasAvailable_r10_Enum value) const;
    uint64_t logMeasAvailable_r10_NumberOfValues() const;
    std::string logMeasAvailable_r10_ToString(uint32_t indent) const;
    std::string logMeasAvailable_r10_ToStringNoNewLines() const;
    int logMeasAvailable_r10_Clear();
    bool logMeasAvailable_r10_IsPresent() const;
private:
    bool logMeasAvailable_r10_present;
    logMeasAvailable_r10_Enum logMeasAvailable_r10_internal_value;

    // nonCriticalExtension

};

#endif
