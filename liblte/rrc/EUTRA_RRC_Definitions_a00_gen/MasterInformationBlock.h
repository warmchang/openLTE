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

#ifndef __MasterInformationBlock_H__
#define __MasterInformationBlock_H__

#include "PHICH_Config.h"

#include <array>
#include <cstdint>
#include <vector>

class MasterInformationBlock
{
public:
    MasterInformationBlock() : dl_Bandwidth_present{false}, phich_Config_present{false}, systemFrameNumber_present{false}, spare_present{false} {};
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

    // phich-Config
public:
    PHICH_Config* phich_Config_Set();
    int phich_Config_Set(PHICH_Config &value);
    const PHICH_Config& phich_Config_Get() const;
    std::string phich_Config_ToString(uint32_t indent) const;
    std::string phich_Config_ToStringNoNewLines() const;
    int phich_Config_Clear();
    bool phich_Config_IsPresent() const;
private:
    bool phich_Config_present;
    PHICH_Config phich_Config;

    // systemFrameNumber
public:
    int systemFrameNumber_Pack(std::vector<uint8_t> &bits);
    int systemFrameNumber_Unpack(std::vector<uint8_t> bits);
    int systemFrameNumber_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t systemFrameNumber_Value() const;
    int systemFrameNumber_SetValue(uint8_t value);
    std::string systemFrameNumber_ToString(uint32_t indent) const;
    std::string systemFrameNumber_ToStringNoNewLines() const;
    int systemFrameNumber_Clear();
    bool systemFrameNumber_IsPresent() const;
private:
    bool systemFrameNumber_present;
    uint8_t systemFrameNumber_internal_value;

    // spare
public:
    int spare_Pack(std::vector<uint8_t> &bits);
    int spare_Unpack(std::vector<uint8_t> bits);
    int spare_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t spare_Value() const;
    int spare_SetValue(uint16_t value);
    std::string spare_ToString(uint32_t indent) const;
    std::string spare_ToStringNoNewLines() const;
    int spare_Clear();
    bool spare_IsPresent() const;
private:
    bool spare_present;
    uint16_t spare_internal_value;

};

#endif
