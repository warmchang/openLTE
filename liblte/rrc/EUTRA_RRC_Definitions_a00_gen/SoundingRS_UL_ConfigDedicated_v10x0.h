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

#ifndef __SoundingRS_UL_ConfigDedicated_v10x0_H__
#define __SoundingRS_UL_ConfigDedicated_v10x0_H__

#include <array>
#include <cstdint>
#include <vector>

class SoundingRS_UL_ConfigDedicated_v10x0
{
public:
    SoundingRS_UL_ConfigDedicated_v10x0() : srs_AntennaPort_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // srs-AntennaPort-r10
public:
    enum srs_AntennaPort_r10_Enum {
        k_srs_AntennaPort_r10_an1 = 0,
        k_srs_AntennaPort_r10_an2,
        k_srs_AntennaPort_r10_an4,
        k_srs_AntennaPort_r10_spare1,
    };
    int srs_AntennaPort_r10_Pack(std::vector<uint8_t> &bits);
    int srs_AntennaPort_r10_Unpack(std::vector<uint8_t> bits);
    int srs_AntennaPort_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    srs_AntennaPort_r10_Enum srs_AntennaPort_r10_Value() const;
    int srs_AntennaPort_r10_SetValue(srs_AntennaPort_r10_Enum value);
    int srs_AntennaPort_r10_SetValue(std::string value);
    std::string srs_AntennaPort_r10_ValueToString(srs_AntennaPort_r10_Enum value) const;
    uint64_t srs_AntennaPort_r10_NumberOfValues() const;
    std::string srs_AntennaPort_r10_ToString(uint32_t indent) const;
    std::string srs_AntennaPort_r10_ToStringNoNewLines() const;
    int srs_AntennaPort_r10_Clear();
    bool srs_AntennaPort_r10_IsPresent() const;
private:
    bool srs_AntennaPort_r10_present;
    srs_AntennaPort_r10_Enum srs_AntennaPort_r10_internal_value;

};

#endif
