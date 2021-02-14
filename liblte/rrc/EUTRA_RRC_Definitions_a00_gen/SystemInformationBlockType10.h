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

#ifndef __SystemInformationBlockType10_H__
#define __SystemInformationBlockType10_H__

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType10
{
public:
    SystemInformationBlockType10() : messageIdentifier_present{false}, serialNumber_present{false}, warningType_present{false}, warningSecurityInfo_present{false}, lateNonCriticalExtension_present{false} {};
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

    // warningType
public:
    int warningType_Pack(std::vector<uint8_t> &bits);
    int warningType_Unpack(std::vector<uint8_t> bits);
    int warningType_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> warningType_Value() const;
    int warningType_SetValue(std::vector<uint8_t> value);
    std::string warningType_ToString(uint32_t indent) const;
    std::string warningType_ToStringNoNewLines() const;
    int warningType_Clear();
    bool warningType_IsPresent() const;
private:
    bool warningType_present;
    std::vector<uint8_t> warningType_internal_value;

    // warningSecurityInfo
public:
    int warningSecurityInfo_Pack(std::vector<uint8_t> &bits);
    int warningSecurityInfo_Unpack(std::vector<uint8_t> bits);
    int warningSecurityInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> warningSecurityInfo_Value() const;
    int warningSecurityInfo_SetValue(std::vector<uint8_t> value);
    std::string warningSecurityInfo_ToString(uint32_t indent) const;
    std::string warningSecurityInfo_ToStringNoNewLines() const;
    int warningSecurityInfo_Clear();
    bool warningSecurityInfo_IsPresent() const;
private:
    bool warningSecurityInfo_present;
    std::vector<uint8_t> warningSecurityInfo_internal_value;

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
