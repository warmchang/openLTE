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

#ifndef __LocationInfo_r10_H__
#define __LocationInfo_r10_H__

#include <array>
#include <cstdint>
#include <vector>

class LocationInfo_r10
{
public:
    LocationInfo_r10() : locationCoordinates_r10_present{false}, horizontalVelocity_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // locationCoordinates-r10
public:
    enum locationCoordinates_r10_Enum {
        k_locationCoordinates_r10_ellipsoid_Point_r10 = 0,
        k_locationCoordinates_r10_ellipsoidPointWithAltitude_r10,
    };
    int locationCoordinates_r10_Pack(std::vector<uint8_t> &bits);
    int locationCoordinates_r10_Unpack(std::vector<uint8_t> bits);
    int locationCoordinates_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    locationCoordinates_r10_Enum locationCoordinates_r10_Choice() const;
    int locationCoordinates_r10_SetChoice(locationCoordinates_r10_Enum choice);
    std::string locationCoordinates_r10_ChoiceToString(locationCoordinates_r10_Enum value) const;
    uint64_t locationCoordinates_r10_NumberOfChoices() const;
    std::string locationCoordinates_r10_ToString(uint32_t indent) const;
    std::string locationCoordinates_r10_ToStringNoNewLines() const;
    int locationCoordinates_r10_Clear();
    bool locationCoordinates_r10_IsPresent() const;
private:
    bool locationCoordinates_r10_present;
    locationCoordinates_r10_Enum locationCoordinates_r10_internal_choice;

    // ellipsoid-Point-r10
public:
    int locationCoordinates_r10_ellipsoid_Point_r10_Pack(std::vector<uint8_t> &bits);
    int locationCoordinates_r10_ellipsoid_Point_r10_Unpack(std::vector<uint8_t> bits);
    int locationCoordinates_r10_ellipsoid_Point_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> locationCoordinates_r10_ellipsoid_Point_r10_Value() const;
    int locationCoordinates_r10_ellipsoid_Point_r10_SetValue(std::vector<uint8_t> value);
    std::string locationCoordinates_r10_ellipsoid_Point_r10_ToString(uint32_t indent) const;
    std::string locationCoordinates_r10_ellipsoid_Point_r10_ToStringNoNewLines() const;
    int locationCoordinates_r10_ellipsoid_Point_r10_Clear();
    bool locationCoordinates_r10_ellipsoid_Point_r10_IsPresent() const;
private:
    bool locationCoordinates_r10_ellipsoid_Point_r10_present;
    std::vector<uint8_t> locationCoordinates_r10_ellipsoid_Point_r10_internal_value;

    // ellipsoidPointWithAltitude-r10
public:
    int locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Pack(std::vector<uint8_t> &bits);
    int locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Unpack(std::vector<uint8_t> bits);
    int locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Value() const;
    int locationCoordinates_r10_ellipsoidPointWithAltitude_r10_SetValue(std::vector<uint8_t> value);
    std::string locationCoordinates_r10_ellipsoidPointWithAltitude_r10_ToString(uint32_t indent) const;
    std::string locationCoordinates_r10_ellipsoidPointWithAltitude_r10_ToStringNoNewLines() const;
    int locationCoordinates_r10_ellipsoidPointWithAltitude_r10_Clear();
    bool locationCoordinates_r10_ellipsoidPointWithAltitude_r10_IsPresent() const;
private:
    bool locationCoordinates_r10_ellipsoidPointWithAltitude_r10_present;
    std::vector<uint8_t> locationCoordinates_r10_ellipsoidPointWithAltitude_r10_internal_value;


    // horizontalVelocity-r10
public:
    int horizontalVelocity_r10_Pack(std::vector<uint8_t> &bits);
    int horizontalVelocity_r10_Unpack(std::vector<uint8_t> bits);
    int horizontalVelocity_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> horizontalVelocity_r10_Value() const;
    int horizontalVelocity_r10_SetValue(std::vector<uint8_t> value);
    std::string horizontalVelocity_r10_ToString(uint32_t indent) const;
    std::string horizontalVelocity_r10_ToStringNoNewLines() const;
    int horizontalVelocity_r10_Clear();
    bool horizontalVelocity_r10_IsPresent() const;
private:
    bool horizontalVelocity_r10_present;
    std::vector<uint8_t> horizontalVelocity_r10_internal_value;

};

#endif
