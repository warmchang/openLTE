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

#ifndef __SystemInformationBlockType12_r9_H__
#define __SystemInformationBlockType12_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType12_r9
{
public:
    SystemInformationBlockType12_r9() : messageIdentifier_r9_present{false}, serialNumber_r9_present{false}, warningMessageSegmentType_r9_present{false}, warningMessageSegmentNumber_r9_present{false}, warningMessageSegment_r9_present{false}, dataCodingScheme_r9_present{false}, lateNonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // messageIdentifier-r9
public:
    int messageIdentifier_r9_Pack(std::vector<uint8_t> &bits);
    int messageIdentifier_r9_Unpack(std::vector<uint8_t> bits);
    int messageIdentifier_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t messageIdentifier_r9_Value() const;
    int messageIdentifier_r9_SetValue(uint16_t value);
    std::string messageIdentifier_r9_ToString(uint32_t indent) const;
    std::string messageIdentifier_r9_ToStringNoNewLines() const;
    int messageIdentifier_r9_Clear();
    bool messageIdentifier_r9_IsPresent() const;
private:
    bool messageIdentifier_r9_present;
    uint16_t messageIdentifier_r9_internal_value;

    // serialNumber-r9
public:
    int serialNumber_r9_Pack(std::vector<uint8_t> &bits);
    int serialNumber_r9_Unpack(std::vector<uint8_t> bits);
    int serialNumber_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t serialNumber_r9_Value() const;
    int serialNumber_r9_SetValue(uint16_t value);
    std::string serialNumber_r9_ToString(uint32_t indent) const;
    std::string serialNumber_r9_ToStringNoNewLines() const;
    int serialNumber_r9_Clear();
    bool serialNumber_r9_IsPresent() const;
private:
    bool serialNumber_r9_present;
    uint16_t serialNumber_r9_internal_value;

    // warningMessageSegmentType-r9
public:
    enum warningMessageSegmentType_r9_Enum {
        k_warningMessageSegmentType_r9_notLastSegment = 0,
        k_warningMessageSegmentType_r9_lastSegment,
    };
    int warningMessageSegmentType_r9_Pack(std::vector<uint8_t> &bits);
    int warningMessageSegmentType_r9_Unpack(std::vector<uint8_t> bits);
    int warningMessageSegmentType_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    warningMessageSegmentType_r9_Enum warningMessageSegmentType_r9_Value() const;
    int warningMessageSegmentType_r9_SetValue(warningMessageSegmentType_r9_Enum value);
    int warningMessageSegmentType_r9_SetValue(std::string value);
    std::string warningMessageSegmentType_r9_ValueToString(warningMessageSegmentType_r9_Enum value) const;
    uint64_t warningMessageSegmentType_r9_NumberOfValues() const;
    std::string warningMessageSegmentType_r9_ToString(uint32_t indent) const;
    std::string warningMessageSegmentType_r9_ToStringNoNewLines() const;
    int warningMessageSegmentType_r9_Clear();
    bool warningMessageSegmentType_r9_IsPresent() const;
private:
    bool warningMessageSegmentType_r9_present;
    warningMessageSegmentType_r9_Enum warningMessageSegmentType_r9_internal_value;

    // warningMessageSegmentNumber-r9
public:
    int warningMessageSegmentNumber_r9_Pack(std::vector<uint8_t> &bits);
    int warningMessageSegmentNumber_r9_Unpack(std::vector<uint8_t> bits);
    int warningMessageSegmentNumber_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t warningMessageSegmentNumber_r9_Value() const;
    int warningMessageSegmentNumber_r9_SetValue(int64_t value);
    std::string warningMessageSegmentNumber_r9_ToString(uint32_t indent) const;
    std::string warningMessageSegmentNumber_r9_ToStringNoNewLines() const;
    int warningMessageSegmentNumber_r9_Clear();
    bool warningMessageSegmentNumber_r9_IsPresent() const;
private:
    bool warningMessageSegmentNumber_r9_present;
    int64_t warningMessageSegmentNumber_r9_internal_value;

    // warningMessageSegment-r9
public:
    int warningMessageSegment_r9_Pack(std::vector<uint8_t> &bits);
    int warningMessageSegment_r9_Unpack(std::vector<uint8_t> bits);
    int warningMessageSegment_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> warningMessageSegment_r9_Value() const;
    int warningMessageSegment_r9_SetValue(std::vector<uint8_t> value);
    std::string warningMessageSegment_r9_ToString(uint32_t indent) const;
    std::string warningMessageSegment_r9_ToStringNoNewLines() const;
    int warningMessageSegment_r9_Clear();
    bool warningMessageSegment_r9_IsPresent() const;
private:
    bool warningMessageSegment_r9_present;
    std::vector<uint8_t> warningMessageSegment_r9_internal_value;

    // dataCodingScheme-r9
public:
    int dataCodingScheme_r9_Pack(std::vector<uint8_t> &bits);
    int dataCodingScheme_r9_Unpack(std::vector<uint8_t> bits);
    int dataCodingScheme_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> dataCodingScheme_r9_Value() const;
    int dataCodingScheme_r9_SetValue(std::vector<uint8_t> value);
    std::string dataCodingScheme_r9_ToString(uint32_t indent) const;
    std::string dataCodingScheme_r9_ToStringNoNewLines() const;
    int dataCodingScheme_r9_Clear();
    bool dataCodingScheme_r9_IsPresent() const;
private:
    bool dataCodingScheme_r9_present;
    std::vector<uint8_t> dataCodingScheme_r9_internal_value;

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
