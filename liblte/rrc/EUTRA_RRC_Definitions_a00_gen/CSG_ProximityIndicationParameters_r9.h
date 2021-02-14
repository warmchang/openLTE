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

#ifndef __CSG_ProximityIndicationParameters_r9_H__
#define __CSG_ProximityIndicationParameters_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class CSG_ProximityIndicationParameters_r9
{
public:
    CSG_ProximityIndicationParameters_r9() : intraFreqProximityIndication_r9_present{false}, interFreqProximityIndication_r9_present{false}, utran_ProximityIndication_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // intraFreqProximityIndication-r9
public:
    enum intraFreqProximityIndication_r9_Enum {
        k_intraFreqProximityIndication_r9_supported = 0,
    };
    int intraFreqProximityIndication_r9_Pack(std::vector<uint8_t> &bits);
    int intraFreqProximityIndication_r9_Unpack(std::vector<uint8_t> bits);
    int intraFreqProximityIndication_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    intraFreqProximityIndication_r9_Enum intraFreqProximityIndication_r9_Value() const;
    int intraFreqProximityIndication_r9_SetValue(intraFreqProximityIndication_r9_Enum value);
    int intraFreqProximityIndication_r9_SetValue(std::string value);
    std::string intraFreqProximityIndication_r9_ValueToString(intraFreqProximityIndication_r9_Enum value) const;
    uint64_t intraFreqProximityIndication_r9_NumberOfValues() const;
    std::string intraFreqProximityIndication_r9_ToString(uint32_t indent) const;
    std::string intraFreqProximityIndication_r9_ToStringNoNewLines() const;
    int intraFreqProximityIndication_r9_Clear();
    bool intraFreqProximityIndication_r9_IsPresent() const;
private:
    bool intraFreqProximityIndication_r9_present;
    intraFreqProximityIndication_r9_Enum intraFreqProximityIndication_r9_internal_value;

    // interFreqProximityIndication-r9
public:
    enum interFreqProximityIndication_r9_Enum {
        k_interFreqProximityIndication_r9_supported = 0,
    };
    int interFreqProximityIndication_r9_Pack(std::vector<uint8_t> &bits);
    int interFreqProximityIndication_r9_Unpack(std::vector<uint8_t> bits);
    int interFreqProximityIndication_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    interFreqProximityIndication_r9_Enum interFreqProximityIndication_r9_Value() const;
    int interFreqProximityIndication_r9_SetValue(interFreqProximityIndication_r9_Enum value);
    int interFreqProximityIndication_r9_SetValue(std::string value);
    std::string interFreqProximityIndication_r9_ValueToString(interFreqProximityIndication_r9_Enum value) const;
    uint64_t interFreqProximityIndication_r9_NumberOfValues() const;
    std::string interFreqProximityIndication_r9_ToString(uint32_t indent) const;
    std::string interFreqProximityIndication_r9_ToStringNoNewLines() const;
    int interFreqProximityIndication_r9_Clear();
    bool interFreqProximityIndication_r9_IsPresent() const;
private:
    bool interFreqProximityIndication_r9_present;
    interFreqProximityIndication_r9_Enum interFreqProximityIndication_r9_internal_value;

    // utran-ProximityIndication-r9
public:
    enum utran_ProximityIndication_r9_Enum {
        k_utran_ProximityIndication_r9_supported = 0,
    };
    int utran_ProximityIndication_r9_Pack(std::vector<uint8_t> &bits);
    int utran_ProximityIndication_r9_Unpack(std::vector<uint8_t> bits);
    int utran_ProximityIndication_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    utran_ProximityIndication_r9_Enum utran_ProximityIndication_r9_Value() const;
    int utran_ProximityIndication_r9_SetValue(utran_ProximityIndication_r9_Enum value);
    int utran_ProximityIndication_r9_SetValue(std::string value);
    std::string utran_ProximityIndication_r9_ValueToString(utran_ProximityIndication_r9_Enum value) const;
    uint64_t utran_ProximityIndication_r9_NumberOfValues() const;
    std::string utran_ProximityIndication_r9_ToString(uint32_t indent) const;
    std::string utran_ProximityIndication_r9_ToStringNoNewLines() const;
    int utran_ProximityIndication_r9_Clear();
    bool utran_ProximityIndication_r9_IsPresent() const;
private:
    bool utran_ProximityIndication_r9_present;
    utran_ProximityIndication_r9_Enum utran_ProximityIndication_r9_internal_value;

};

#endif
