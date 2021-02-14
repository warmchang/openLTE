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

#ifndef __CarrierBandwidthEUTRA_H__
#define __CarrierBandwidthEUTRA_H__

#include <array>
#include <cstdint>
#include <vector>

class CarrierBandwidthEUTRA
{
public:
    CarrierBandwidthEUTRA() : dl_Bandwidth_present{false}, ul_Bandwidth_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // dl-Bandwidth
public:
    enum dl_Bandwidth_Enum {
        k_dl_Bandwidth_n6 = 0,
        k_dl_Bandwidth_n15,
        k_dl_Bandwidth_n25,
        k_dl_Bandwidth_n50,
        k_dl_Bandwidth_n75,
        k_dl_Bandwidth_n100,
        k_dl_Bandwidth_spare10,
        k_dl_Bandwidth_spare9,
        k_dl_Bandwidth_spare8,
        k_dl_Bandwidth_spare7,
        k_dl_Bandwidth_spare6,
        k_dl_Bandwidth_spare5,
        k_dl_Bandwidth_spare4,
        k_dl_Bandwidth_spare3,
        k_dl_Bandwidth_spare2,
        k_dl_Bandwidth_spare1,
    };
    int dl_Bandwidth_Pack(std::vector<uint8_t> &bits);
    int dl_Bandwidth_Unpack(std::vector<uint8_t> bits);
    int dl_Bandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    dl_Bandwidth_Enum dl_Bandwidth_Value() const;
    int dl_Bandwidth_SetValue(dl_Bandwidth_Enum value);
    int dl_Bandwidth_SetValue(std::string value);
    std::string dl_Bandwidth_ValueToString(dl_Bandwidth_Enum value) const;
    uint64_t dl_Bandwidth_NumberOfValues() const;
    std::string dl_Bandwidth_ToString(uint32_t indent) const;
    std::string dl_Bandwidth_ToStringNoNewLines() const;
    int dl_Bandwidth_Clear();
    bool dl_Bandwidth_IsPresent() const;
private:
    bool dl_Bandwidth_present;
    dl_Bandwidth_Enum dl_Bandwidth_internal_value;

    // ul-Bandwidth
public:
    enum ul_Bandwidth_Enum {
        k_ul_Bandwidth_n6 = 0,
        k_ul_Bandwidth_n15,
        k_ul_Bandwidth_n25,
        k_ul_Bandwidth_n50,
        k_ul_Bandwidth_n75,
        k_ul_Bandwidth_n100,
        k_ul_Bandwidth_spare10,
        k_ul_Bandwidth_spare9,
        k_ul_Bandwidth_spare8,
        k_ul_Bandwidth_spare7,
        k_ul_Bandwidth_spare6,
        k_ul_Bandwidth_spare5,
        k_ul_Bandwidth_spare4,
        k_ul_Bandwidth_spare3,
        k_ul_Bandwidth_spare2,
        k_ul_Bandwidth_spare1,
    };
    int ul_Bandwidth_Pack(std::vector<uint8_t> &bits);
    int ul_Bandwidth_Unpack(std::vector<uint8_t> bits);
    int ul_Bandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ul_Bandwidth_Enum ul_Bandwidth_Value() const;
    int ul_Bandwidth_SetValue(ul_Bandwidth_Enum value);
    int ul_Bandwidth_SetValue(std::string value);
    std::string ul_Bandwidth_ValueToString(ul_Bandwidth_Enum value) const;
    uint64_t ul_Bandwidth_NumberOfValues() const;
    std::string ul_Bandwidth_ToString(uint32_t indent) const;
    std::string ul_Bandwidth_ToStringNoNewLines() const;
    int ul_Bandwidth_Clear();
    bool ul_Bandwidth_IsPresent() const;
private:
    bool ul_Bandwidth_present;
    ul_Bandwidth_Enum ul_Bandwidth_internal_value;

};

#endif
