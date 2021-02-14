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

#ifndef __SystemInformationBlockType9_H__
#define __SystemInformationBlockType9_H__

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType9
{
public:
    SystemInformationBlockType9() : hnb_Name_present{false}, lateNonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // hnb-Name
public:
    int hnb_Name_Pack(std::vector<uint8_t> &bits);
    int hnb_Name_Unpack(std::vector<uint8_t> bits);
    int hnb_Name_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> hnb_Name_Value() const;
    int hnb_Name_SetValue(std::vector<uint8_t> value);
    std::string hnb_Name_ToString(uint32_t indent) const;
    std::string hnb_Name_ToStringNoNewLines() const;
    int hnb_Name_Clear();
    bool hnb_Name_IsPresent() const;
private:
    bool hnb_Name_present;
    std::vector<uint8_t> hnb_Name_internal_value;

    // lateNonCriticalExtension
public:
    int lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> lateNonCriticalExtension_Value() const;
    int lateNonCriticalExtension_SetValue(std::vector<uint8_t> value);
    std::string lateNonCriticalExtension_ToString(uint32_t indent) const;
    std::string lateNonCriticalExtension_ToStringNoNewLines() const;
    int lateNonCriticalExtension_Clear();
    bool lateNonCriticalExtension_IsPresent() const;
private:
    bool lateNonCriticalExtension_present;
    std::vector<uint8_t> lateNonCriticalExtension_internal_value;

};

#endif
