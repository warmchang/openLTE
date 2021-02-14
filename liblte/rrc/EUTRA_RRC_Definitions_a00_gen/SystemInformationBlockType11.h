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

#ifndef __SystemInformationBlockType11_H__
#define __SystemInformationBlockType11_H__

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType11
{
public:
    SystemInformationBlockType11() : messageIdentifier_present{false}, serialNumber_present{false}, warningMessageSegmentType_present{false}, warningMessageSegmentNumber_present{false}, warningMessageSegment_present{false}, dataCodingScheme_present{false}, lateNonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // messageIdentifier
public:
    int messageIdentifier_Pack(std::vector<uint8_t> &bits);
    int messageIdentifier_Unpack(std::vector<uint8_t> bits);
    int messageIdentifier_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t messageIdentifier_Value() const;
    int messageIdentifier_SetValue(uint16_t value);
    std::string messageIdentifier_ToString(uint32_t indent) const;
    std::string messageIdentifier_ToStringNoNewLines() const;
    int messageIdentifier_Clear();
    bool messageIdentifier_IsPresent() const;
private:
    bool messageIdentifier_present;
    uint16_t messageIdentifier_internal_value;

    // serialNumber
public:
    int serialNumber_Pack(std::vector<uint8_t> &bits);
    int serialNumber_Unpack(std::vector<uint8_t> bits);
    int serialNumber_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t serialNumber_Value() const;
    int serialNumber_SetValue(uint16_t value);
    std::string serialNumber_ToString(uint32_t indent) const;
    std::string serialNumber_ToStringNoNewLines() const;
    int serialNumber_Clear();
    bool serialNumber_IsPresent() const;
private:
    bool serialNumber_present;
    uint16_t serialNumber_internal_value;

    // warningMessageSegmentType
public:
    enum warningMessageSegmentType_Enum {
        k_warningMessageSegmentType_notLastSegment = 0,
        k_warningMessageSegmentType_lastSegment,
    };
    int warningMessageSegmentType_Pack(std::vector<uint8_t> &bits);
    int warningMessageSegmentType_Unpack(std::vector<uint8_t> bits);
    int warningMessageSegmentType_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    warningMessageSegmentType_Enum warningMessageSegmentType_Value() const;
    int warningMessageSegmentType_SetValue(warningMessageSegmentType_Enum value);
    int warningMessageSegmentType_SetValue(std::string value);
    std::string warningMessageSegmentType_ValueToString(warningMessageSegmentType_Enum value) const;
    uint64_t warningMessageSegmentType_NumberOfValues() const;
    std::string warningMessageSegmentType_ToString(uint32_t indent) const;
    std::string warningMessageSegmentType_ToStringNoNewLines() const;
    int warningMessageSegmentType_Clear();
    bool warningMessageSegmentType_IsPresent() const;
private:
    bool warningMessageSegmentType_present;
    warningMessageSegmentType_Enum warningMessageSegmentType_internal_value;

    // warningMessageSegmentNumber
public:
    int warningMessageSegmentNumber_Pack(std::vector<uint8_t> &bits);
    int warningMessageSegmentNumber_Unpack(std::vector<uint8_t> bits);
    int warningMessageSegmentNumber_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t warningMessageSegmentNumber_Value() const;
    int warningMessageSegmentNumber_SetValue(int64_t value);
    std::string warningMessageSegmentNumber_ToString(uint32_t indent) const;
    std::string warningMessageSegmentNumber_ToStringNoNewLines() const;
    int warningMessageSegmentNumber_Clear();
    bool warningMessageSegmentNumber_IsPresent() const;
private:
    bool warningMessageSegmentNumber_present;
    int64_t warningMessageSegmentNumber_internal_value;

    // warningMessageSegment
public:
    int warningMessageSegment_Pack(std::vector<uint8_t> &bits);
    int warningMessageSegment_Unpack(std::vector<uint8_t> bits);
    int warningMessageSegment_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> warningMessageSegment_Value() const;
    int warningMessageSegment_SetValue(std::vector<uint8_t> value);
    std::string warningMessageSegment_ToString(uint32_t indent) const;
    std::string warningMessageSegment_ToStringNoNewLines() const;
    int warningMessageSegment_Clear();
    bool warningMessageSegment_IsPresent() const;
private:
    bool warningMessageSegment_present;
    std::vector<uint8_t> warningMessageSegment_internal_value;

    // dataCodingScheme
public:
    int dataCodingScheme_Pack(std::vector<uint8_t> &bits);
    int dataCodingScheme_Unpack(std::vector<uint8_t> bits);
    int dataCodingScheme_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> dataCodingScheme_Value() const;
    int dataCodingScheme_SetValue(std::vector<uint8_t> value);
    std::string dataCodingScheme_ToString(uint32_t indent) const;
    std::string dataCodingScheme_ToStringNoNewLines() const;
    int dataCodingScheme_Clear();
    bool dataCodingScheme_IsPresent() const;
private:
    bool dataCodingScheme_present;
    std::vector<uint8_t> dataCodingScheme_internal_value;

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
