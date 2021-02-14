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

#ifndef __UL_ReferenceSignalsPUSCH_H__
#define __UL_ReferenceSignalsPUSCH_H__

#include <array>
#include <cstdint>
#include <vector>

class UL_ReferenceSignalsPUSCH
{
public:
    UL_ReferenceSignalsPUSCH() : groupHoppingEnabled_present{false}, groupAssignmentPUSCH_present{false}, sequenceHoppingEnabled_present{false}, cyclicShift_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // groupHoppingEnabled
public:
    int groupHoppingEnabled_Pack(std::vector<uint8_t> &bits);
    int groupHoppingEnabled_Unpack(std::vector<uint8_t> bits);
    int groupHoppingEnabled_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool groupHoppingEnabled_Value() const;
    int groupHoppingEnabled_SetValue(bool value);
    std::string groupHoppingEnabled_ToString(uint32_t indent) const;
    std::string groupHoppingEnabled_ToStringNoNewLines() const;
    int groupHoppingEnabled_Clear();
    bool groupHoppingEnabled_IsPresent() const;
private:
    bool groupHoppingEnabled_present;
    bool groupHoppingEnabled_internal_value;

    // groupAssignmentPUSCH
public:
    int groupAssignmentPUSCH_Pack(std::vector<uint8_t> &bits);
    int groupAssignmentPUSCH_Unpack(std::vector<uint8_t> bits);
    int groupAssignmentPUSCH_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t groupAssignmentPUSCH_Value() const;
    int groupAssignmentPUSCH_SetValue(int64_t value);
    std::string groupAssignmentPUSCH_ToString(uint32_t indent) const;
    std::string groupAssignmentPUSCH_ToStringNoNewLines() const;
    int groupAssignmentPUSCH_Clear();
    bool groupAssignmentPUSCH_IsPresent() const;
private:
    bool groupAssignmentPUSCH_present;
    int64_t groupAssignmentPUSCH_internal_value;

    // sequenceHoppingEnabled
public:
    int sequenceHoppingEnabled_Pack(std::vector<uint8_t> &bits);
    int sequenceHoppingEnabled_Unpack(std::vector<uint8_t> bits);
    int sequenceHoppingEnabled_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool sequenceHoppingEnabled_Value() const;
    int sequenceHoppingEnabled_SetValue(bool value);
    std::string sequenceHoppingEnabled_ToString(uint32_t indent) const;
    std::string sequenceHoppingEnabled_ToStringNoNewLines() const;
    int sequenceHoppingEnabled_Clear();
    bool sequenceHoppingEnabled_IsPresent() const;
private:
    bool sequenceHoppingEnabled_present;
    bool sequenceHoppingEnabled_internal_value;

    // cyclicShift
public:
    int cyclicShift_Pack(std::vector<uint8_t> &bits);
    int cyclicShift_Unpack(std::vector<uint8_t> bits);
    int cyclicShift_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t cyclicShift_Value() const;
    int cyclicShift_SetValue(int64_t value);
    std::string cyclicShift_ToString(uint32_t indent) const;
    std::string cyclicShift_ToStringNoNewLines() const;
    int cyclicShift_Clear();
    bool cyclicShift_IsPresent() const;
private:
    bool cyclicShift_present;
    int64_t cyclicShift_internal_value;

};

#endif
