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

#ifndef __CSFB_RegistrationParam1XRTT_H__
#define __CSFB_RegistrationParam1XRTT_H__

#include <array>
#include <cstdint>
#include <vector>

class CSFB_RegistrationParam1XRTT
{
public:
    CSFB_RegistrationParam1XRTT() : sid_present{false}, nid_present{false}, multipleSID_present{false}, multipleNID_present{false}, homeReg_present{false}, foreignSIDReg_present{false}, foreignNIDReg_present{false}, parameterReg_present{false}, powerUpReg_present{false}, registrationPeriod_present{false}, registrationZone_present{false}, totalZone_present{false}, zoneTimer_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // sid
public:
    int sid_Pack(std::vector<uint8_t> &bits);
    int sid_Unpack(std::vector<uint8_t> bits);
    int sid_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t sid_Value() const;
    int sid_SetValue(uint16_t value);
    std::string sid_ToString(uint32_t indent) const;
    std::string sid_ToStringNoNewLines() const;
    int sid_Clear();
    bool sid_IsPresent() const;
private:
    bool sid_present;
    uint16_t sid_internal_value;

    // nid
public:
    int nid_Pack(std::vector<uint8_t> &bits);
    int nid_Unpack(std::vector<uint8_t> bits);
    int nid_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t nid_Value() const;
    int nid_SetValue(uint16_t value);
    std::string nid_ToString(uint32_t indent) const;
    std::string nid_ToStringNoNewLines() const;
    int nid_Clear();
    bool nid_IsPresent() const;
private:
    bool nid_present;
    uint16_t nid_internal_value;

    // multipleSID
public:
    int multipleSID_Pack(std::vector<uint8_t> &bits);
    int multipleSID_Unpack(std::vector<uint8_t> bits);
    int multipleSID_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool multipleSID_Value() const;
    int multipleSID_SetValue(bool value);
    std::string multipleSID_ToString(uint32_t indent) const;
    std::string multipleSID_ToStringNoNewLines() const;
    int multipleSID_Clear();
    bool multipleSID_IsPresent() const;
private:
    bool multipleSID_present;
    bool multipleSID_internal_value;

    // multipleNID
public:
    int multipleNID_Pack(std::vector<uint8_t> &bits);
    int multipleNID_Unpack(std::vector<uint8_t> bits);
    int multipleNID_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool multipleNID_Value() const;
    int multipleNID_SetValue(bool value);
    std::string multipleNID_ToString(uint32_t indent) const;
    std::string multipleNID_ToStringNoNewLines() const;
    int multipleNID_Clear();
    bool multipleNID_IsPresent() const;
private:
    bool multipleNID_present;
    bool multipleNID_internal_value;

    // homeReg
public:
    int homeReg_Pack(std::vector<uint8_t> &bits);
    int homeReg_Unpack(std::vector<uint8_t> bits);
    int homeReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool homeReg_Value() const;
    int homeReg_SetValue(bool value);
    std::string homeReg_ToString(uint32_t indent) const;
    std::string homeReg_ToStringNoNewLines() const;
    int homeReg_Clear();
    bool homeReg_IsPresent() const;
private:
    bool homeReg_present;
    bool homeReg_internal_value;

    // foreignSIDReg
public:
    int foreignSIDReg_Pack(std::vector<uint8_t> &bits);
    int foreignSIDReg_Unpack(std::vector<uint8_t> bits);
    int foreignSIDReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool foreignSIDReg_Value() const;
    int foreignSIDReg_SetValue(bool value);
    std::string foreignSIDReg_ToString(uint32_t indent) const;
    std::string foreignSIDReg_ToStringNoNewLines() const;
    int foreignSIDReg_Clear();
    bool foreignSIDReg_IsPresent() const;
private:
    bool foreignSIDReg_present;
    bool foreignSIDReg_internal_value;

    // foreignNIDReg
public:
    int foreignNIDReg_Pack(std::vector<uint8_t> &bits);
    int foreignNIDReg_Unpack(std::vector<uint8_t> bits);
    int foreignNIDReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool foreignNIDReg_Value() const;
    int foreignNIDReg_SetValue(bool value);
    std::string foreignNIDReg_ToString(uint32_t indent) const;
    std::string foreignNIDReg_ToStringNoNewLines() const;
    int foreignNIDReg_Clear();
    bool foreignNIDReg_IsPresent() const;
private:
    bool foreignNIDReg_present;
    bool foreignNIDReg_internal_value;

    // parameterReg
public:
    int parameterReg_Pack(std::vector<uint8_t> &bits);
    int parameterReg_Unpack(std::vector<uint8_t> bits);
    int parameterReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool parameterReg_Value() const;
    int parameterReg_SetValue(bool value);
    std::string parameterReg_ToString(uint32_t indent) const;
    std::string parameterReg_ToStringNoNewLines() const;
    int parameterReg_Clear();
    bool parameterReg_IsPresent() const;
private:
    bool parameterReg_present;
    bool parameterReg_internal_value;

    // powerUpReg
public:
    int powerUpReg_Pack(std::vector<uint8_t> &bits);
    int powerUpReg_Unpack(std::vector<uint8_t> bits);
    int powerUpReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool powerUpReg_Value() const;
    int powerUpReg_SetValue(bool value);
    std::string powerUpReg_ToString(uint32_t indent) const;
    std::string powerUpReg_ToStringNoNewLines() const;
    int powerUpReg_Clear();
    bool powerUpReg_IsPresent() const;
private:
    bool powerUpReg_present;
    bool powerUpReg_internal_value;

    // registrationPeriod
public:
    int registrationPeriod_Pack(std::vector<uint8_t> &bits);
    int registrationPeriod_Unpack(std::vector<uint8_t> bits);
    int registrationPeriod_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t registrationPeriod_Value() const;
    int registrationPeriod_SetValue(uint8_t value);
    std::string registrationPeriod_ToString(uint32_t indent) const;
    std::string registrationPeriod_ToStringNoNewLines() const;
    int registrationPeriod_Clear();
    bool registrationPeriod_IsPresent() const;
private:
    bool registrationPeriod_present;
    uint8_t registrationPeriod_internal_value;

    // registrationZone
public:
    int registrationZone_Pack(std::vector<uint8_t> &bits);
    int registrationZone_Unpack(std::vector<uint8_t> bits);
    int registrationZone_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t registrationZone_Value() const;
    int registrationZone_SetValue(uint16_t value);
    std::string registrationZone_ToString(uint32_t indent) const;
    std::string registrationZone_ToStringNoNewLines() const;
    int registrationZone_Clear();
    bool registrationZone_IsPresent() const;
private:
    bool registrationZone_present;
    uint16_t registrationZone_internal_value;

    // totalZone
public:
    int totalZone_Pack(std::vector<uint8_t> &bits);
    int totalZone_Unpack(std::vector<uint8_t> bits);
    int totalZone_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t totalZone_Value() const;
    int totalZone_SetValue(uint8_t value);
    std::string totalZone_ToString(uint32_t indent) const;
    std::string totalZone_ToStringNoNewLines() const;
    int totalZone_Clear();
    bool totalZone_IsPresent() const;
private:
    bool totalZone_present;
    uint8_t totalZone_internal_value;

    // zoneTimer
public:
    int zoneTimer_Pack(std::vector<uint8_t> &bits);
    int zoneTimer_Unpack(std::vector<uint8_t> bits);
    int zoneTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t zoneTimer_Value() const;
    int zoneTimer_SetValue(uint8_t value);
    std::string zoneTimer_ToString(uint32_t indent) const;
    std::string zoneTimer_ToStringNoNewLines() const;
    int zoneTimer_Clear();
    bool zoneTimer_IsPresent() const;
private:
    bool zoneTimer_present;
    uint8_t zoneTimer_internal_value;

};

#endif
