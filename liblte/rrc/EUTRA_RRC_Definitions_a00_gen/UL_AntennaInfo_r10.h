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

#ifndef __UL_AntennaInfo_r10_H__
#define __UL_AntennaInfo_r10_H__

#include <array>
#include <cstdint>
#include <vector>

class UL_AntennaInfo_r10
{
public:
    UL_AntennaInfo_r10() : ul_TransmissionMode_r10_present{false}, fourAntennaPortActivated_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ul-TransmissionMode-r10
public:
    enum ul_TransmissionMode_r10_Enum {
        k_ul_TransmissionMode_r10_tm1 = 0,
        k_ul_TransmissionMode_r10_tm2,
        k_ul_TransmissionMode_r10_spare6,
        k_ul_TransmissionMode_r10_spare5,
        k_ul_TransmissionMode_r10_spare4,
        k_ul_TransmissionMode_r10_spare3,
        k_ul_TransmissionMode_r10_spare2,
        k_ul_TransmissionMode_r10_spare1,
    };
    int ul_TransmissionMode_r10_Pack(std::vector<uint8_t> &bits);
    int ul_TransmissionMode_r10_Unpack(std::vector<uint8_t> bits);
    int ul_TransmissionMode_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ul_TransmissionMode_r10_Enum ul_TransmissionMode_r10_Value() const;
    int ul_TransmissionMode_r10_SetValue(ul_TransmissionMode_r10_Enum value);
    int ul_TransmissionMode_r10_SetValue(std::string value);
    std::string ul_TransmissionMode_r10_ValueToString(ul_TransmissionMode_r10_Enum value) const;
    uint64_t ul_TransmissionMode_r10_NumberOfValues() const;
    std::string ul_TransmissionMode_r10_ToString(uint32_t indent) const;
    std::string ul_TransmissionMode_r10_ToStringNoNewLines() const;
    int ul_TransmissionMode_r10_Clear();
    bool ul_TransmissionMode_r10_IsPresent() const;
private:
    bool ul_TransmissionMode_r10_present;
    ul_TransmissionMode_r10_Enum ul_TransmissionMode_r10_internal_value;

    // fourAntennaPortActivated-r10
public:
    int fourAntennaPortActivated_r10_Pack(std::vector<uint8_t> &bits);
    int fourAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits);
    int fourAntennaPortActivated_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool fourAntennaPortActivated_r10_Value() const;
    int fourAntennaPortActivated_r10_SetValue(bool value);
    std::string fourAntennaPortActivated_r10_ToString(uint32_t indent) const;
    std::string fourAntennaPortActivated_r10_ToStringNoNewLines() const;
    int fourAntennaPortActivated_r10_Clear();
    bool fourAntennaPortActivated_r10_IsPresent() const;
private:
    bool fourAntennaPortActivated_r10_present;
    bool fourAntennaPortActivated_r10_internal_value;

};

#endif
