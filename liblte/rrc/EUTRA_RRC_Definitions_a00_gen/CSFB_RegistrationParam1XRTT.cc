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

#include "CSFB_RegistrationParam1XRTT.h"

#include <cmath>

int CSFB_RegistrationParam1XRTT::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sid_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != nid_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != multipleSID_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != multipleNID_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != homeReg_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != foreignSIDReg_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != foreignNIDReg_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != parameterReg_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != powerUpReg_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != registrationPeriod_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != registrationZone_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != totalZone_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != zoneTimer_Pack(bits))
        {
            printf("CSFB_RegistrationParam1XRTT:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int CSFB_RegistrationParam1XRTT::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators

    // Fields
    {
        if(0 != sid_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != nid_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != multipleSID_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != multipleNID_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != homeReg_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != foreignSIDReg_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != foreignNIDReg_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != parameterReg_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != powerUpReg_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != registrationPeriod_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != registrationZone_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != totalZone_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != zoneTimer_Unpack(bits, idx))
        {
            printf("CSFB_RegistrationParam1XRTT:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "CSFB_RegistrationParam1XRTT:\n";
    out += sid_ToString(indent+1);
    out += nid_ToString(indent+1);
    out += multipleSID_ToString(indent+1);
    out += multipleNID_ToString(indent+1);
    out += homeReg_ToString(indent+1);
    out += foreignSIDReg_ToString(indent+1);
    out += foreignNIDReg_ToString(indent+1);
    out += parameterReg_ToString(indent+1);
    out += powerUpReg_ToString(indent+1);
    out += registrationPeriod_ToString(indent+1);
    out += registrationZone_ToString(indent+1);
    out += totalZone_ToString(indent+1);
    out += zoneTimer_ToString(indent+1);
    return out;
}

std::string CSFB_RegistrationParam1XRTT::ToStringNoNewLines() const
{
    std::string out = "CSFB_RegistrationParam1XRTT:";
    out += sid_ToStringNoNewLines();
    out += nid_ToStringNoNewLines();
    out += multipleSID_ToStringNoNewLines();
    out += multipleNID_ToStringNoNewLines();
    out += homeReg_ToStringNoNewLines();
    out += foreignSIDReg_ToStringNoNewLines();
    out += foreignNIDReg_ToStringNoNewLines();
    out += parameterReg_ToStringNoNewLines();
    out += powerUpReg_ToStringNoNewLines();
    out += registrationPeriod_ToStringNoNewLines();
    out += registrationZone_ToStringNoNewLines();
    out += totalZone_ToStringNoNewLines();
    out += zoneTimer_ToStringNoNewLines();
    return out;
}

int CSFB_RegistrationParam1XRTT::sid_Pack(std::vector<uint8_t> &bits)
{
    if(!sid_present)
    {
        printf("CSFB_RegistrationParam1XRTT::sid_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 15;
    if(size < 15 || size > 15)
    {
        printf("CSFB_RegistrationParam1XRTT::sid_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((sid_internal_value >> (15-i-1)) & 1);
    return 0;
}

int CSFB_RegistrationParam1XRTT::sid_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return sid_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::sid_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 15;
    if(size < 15 || size > 15)
    {
        printf("CSFB_RegistrationParam1XRTT::sid_Unpack() size failure\n");
        return -1;
    }
    sid_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::sid_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        sid_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(15-i-1);
    sid_present = true;
    return 0;
}

uint16_t CSFB_RegistrationParam1XRTT::sid_Value() const
{
    if(sid_present)
        return sid_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int CSFB_RegistrationParam1XRTT::sid_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 15)
    {
        printf("CSFB_RegistrationParam1XRTT::sid_SetValue() size failure\n");
        return -1;
    }
    sid_internal_value = value;
    sid_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::sid_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "sid = ";
    out += std::to_string(sid_internal_value);
    out += "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::sid_ToStringNoNewLines() const
{
    std::string out = "sid=";
    out += std::to_string(sid_internal_value);
    out += ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::sid_Clear()
{
    sid_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::sid_IsPresent() const
{
    return sid_present;
}

int CSFB_RegistrationParam1XRTT::nid_Pack(std::vector<uint8_t> &bits)
{
    if(!nid_present)
    {
        printf("CSFB_RegistrationParam1XRTT::nid_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CSFB_RegistrationParam1XRTT::nid_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((nid_internal_value >> (16-i-1)) & 1);
    return 0;
}

int CSFB_RegistrationParam1XRTT::nid_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return nid_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::nid_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 16;
    if(size < 16 || size > 16)
    {
        printf("CSFB_RegistrationParam1XRTT::nid_Unpack() size failure\n");
        return -1;
    }
    nid_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::nid_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        nid_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(16-i-1);
    nid_present = true;
    return 0;
}

uint16_t CSFB_RegistrationParam1XRTT::nid_Value() const
{
    if(nid_present)
        return nid_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int CSFB_RegistrationParam1XRTT::nid_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 16)
    {
        printf("CSFB_RegistrationParam1XRTT::nid_SetValue() size failure\n");
        return -1;
    }
    nid_internal_value = value;
    nid_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::nid_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "nid = ";
    out += std::to_string(nid_internal_value);
    out += "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::nid_ToStringNoNewLines() const
{
    std::string out = "nid=";
    out += std::to_string(nid_internal_value);
    out += ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::nid_Clear()
{
    nid_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::nid_IsPresent() const
{
    return nid_present;
}

int CSFB_RegistrationParam1XRTT::multipleSID_Pack(std::vector<uint8_t> &bits)
{
    if(!multipleSID_present)
    {
        printf("CSFB_RegistrationParam1XRTT::multipleSID_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(multipleSID_internal_value);
    return 0;
}

int CSFB_RegistrationParam1XRTT::multipleSID_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return multipleSID_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::multipleSID_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::multipleSID_Unpack() index out of bounds\n");
        return -1;
    }
    multipleSID_internal_value = bits[idx++];
    multipleSID_present = true;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::multipleSID_Value() const
{
    if(multipleSID_present)
        return multipleSID_internal_value;
    return false;
}

int CSFB_RegistrationParam1XRTT::multipleSID_SetValue(bool value)
{
    multipleSID_internal_value = value;
    multipleSID_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::multipleSID_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "multipleSID = " + std::to_string(multipleSID_internal_value) + "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::multipleSID_ToStringNoNewLines() const
{
    std::string out = "multipleSID=" + std::to_string(multipleSID_internal_value) + ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::multipleSID_Clear()
{
    multipleSID_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::multipleSID_IsPresent() const
{
    return multipleSID_present;
}

int CSFB_RegistrationParam1XRTT::multipleNID_Pack(std::vector<uint8_t> &bits)
{
    if(!multipleNID_present)
    {
        printf("CSFB_RegistrationParam1XRTT::multipleNID_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(multipleNID_internal_value);
    return 0;
}

int CSFB_RegistrationParam1XRTT::multipleNID_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return multipleNID_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::multipleNID_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::multipleNID_Unpack() index out of bounds\n");
        return -1;
    }
    multipleNID_internal_value = bits[idx++];
    multipleNID_present = true;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::multipleNID_Value() const
{
    if(multipleNID_present)
        return multipleNID_internal_value;
    return false;
}

int CSFB_RegistrationParam1XRTT::multipleNID_SetValue(bool value)
{
    multipleNID_internal_value = value;
    multipleNID_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::multipleNID_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "multipleNID = " + std::to_string(multipleNID_internal_value) + "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::multipleNID_ToStringNoNewLines() const
{
    std::string out = "multipleNID=" + std::to_string(multipleNID_internal_value) + ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::multipleNID_Clear()
{
    multipleNID_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::multipleNID_IsPresent() const
{
    return multipleNID_present;
}

int CSFB_RegistrationParam1XRTT::homeReg_Pack(std::vector<uint8_t> &bits)
{
    if(!homeReg_present)
    {
        printf("CSFB_RegistrationParam1XRTT::homeReg_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(homeReg_internal_value);
    return 0;
}

int CSFB_RegistrationParam1XRTT::homeReg_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return homeReg_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::homeReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::homeReg_Unpack() index out of bounds\n");
        return -1;
    }
    homeReg_internal_value = bits[idx++];
    homeReg_present = true;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::homeReg_Value() const
{
    if(homeReg_present)
        return homeReg_internal_value;
    return false;
}

int CSFB_RegistrationParam1XRTT::homeReg_SetValue(bool value)
{
    homeReg_internal_value = value;
    homeReg_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::homeReg_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "homeReg = " + std::to_string(homeReg_internal_value) + "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::homeReg_ToStringNoNewLines() const
{
    std::string out = "homeReg=" + std::to_string(homeReg_internal_value) + ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::homeReg_Clear()
{
    homeReg_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::homeReg_IsPresent() const
{
    return homeReg_present;
}

int CSFB_RegistrationParam1XRTT::foreignSIDReg_Pack(std::vector<uint8_t> &bits)
{
    if(!foreignSIDReg_present)
    {
        printf("CSFB_RegistrationParam1XRTT::foreignSIDReg_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(foreignSIDReg_internal_value);
    return 0;
}

int CSFB_RegistrationParam1XRTT::foreignSIDReg_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return foreignSIDReg_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::foreignSIDReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::foreignSIDReg_Unpack() index out of bounds\n");
        return -1;
    }
    foreignSIDReg_internal_value = bits[idx++];
    foreignSIDReg_present = true;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::foreignSIDReg_Value() const
{
    if(foreignSIDReg_present)
        return foreignSIDReg_internal_value;
    return false;
}

int CSFB_RegistrationParam1XRTT::foreignSIDReg_SetValue(bool value)
{
    foreignSIDReg_internal_value = value;
    foreignSIDReg_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::foreignSIDReg_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "foreignSIDReg = " + std::to_string(foreignSIDReg_internal_value) + "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::foreignSIDReg_ToStringNoNewLines() const
{
    std::string out = "foreignSIDReg=" + std::to_string(foreignSIDReg_internal_value) + ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::foreignSIDReg_Clear()
{
    foreignSIDReg_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::foreignSIDReg_IsPresent() const
{
    return foreignSIDReg_present;
}

int CSFB_RegistrationParam1XRTT::foreignNIDReg_Pack(std::vector<uint8_t> &bits)
{
    if(!foreignNIDReg_present)
    {
        printf("CSFB_RegistrationParam1XRTT::foreignNIDReg_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(foreignNIDReg_internal_value);
    return 0;
}

int CSFB_RegistrationParam1XRTT::foreignNIDReg_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return foreignNIDReg_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::foreignNIDReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::foreignNIDReg_Unpack() index out of bounds\n");
        return -1;
    }
    foreignNIDReg_internal_value = bits[idx++];
    foreignNIDReg_present = true;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::foreignNIDReg_Value() const
{
    if(foreignNIDReg_present)
        return foreignNIDReg_internal_value;
    return false;
}

int CSFB_RegistrationParam1XRTT::foreignNIDReg_SetValue(bool value)
{
    foreignNIDReg_internal_value = value;
    foreignNIDReg_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::foreignNIDReg_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "foreignNIDReg = " + std::to_string(foreignNIDReg_internal_value) + "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::foreignNIDReg_ToStringNoNewLines() const
{
    std::string out = "foreignNIDReg=" + std::to_string(foreignNIDReg_internal_value) + ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::foreignNIDReg_Clear()
{
    foreignNIDReg_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::foreignNIDReg_IsPresent() const
{
    return foreignNIDReg_present;
}

int CSFB_RegistrationParam1XRTT::parameterReg_Pack(std::vector<uint8_t> &bits)
{
    if(!parameterReg_present)
    {
        printf("CSFB_RegistrationParam1XRTT::parameterReg_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(parameterReg_internal_value);
    return 0;
}

int CSFB_RegistrationParam1XRTT::parameterReg_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return parameterReg_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::parameterReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::parameterReg_Unpack() index out of bounds\n");
        return -1;
    }
    parameterReg_internal_value = bits[idx++];
    parameterReg_present = true;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::parameterReg_Value() const
{
    if(parameterReg_present)
        return parameterReg_internal_value;
    return false;
}

int CSFB_RegistrationParam1XRTT::parameterReg_SetValue(bool value)
{
    parameterReg_internal_value = value;
    parameterReg_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::parameterReg_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "parameterReg = " + std::to_string(parameterReg_internal_value) + "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::parameterReg_ToStringNoNewLines() const
{
    std::string out = "parameterReg=" + std::to_string(parameterReg_internal_value) + ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::parameterReg_Clear()
{
    parameterReg_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::parameterReg_IsPresent() const
{
    return parameterReg_present;
}

int CSFB_RegistrationParam1XRTT::powerUpReg_Pack(std::vector<uint8_t> &bits)
{
    if(!powerUpReg_present)
    {
        printf("CSFB_RegistrationParam1XRTT::powerUpReg_Pack() presence failure\n");
        return -1;
    }
    bits.push_back(powerUpReg_internal_value);
    return 0;
}

int CSFB_RegistrationParam1XRTT::powerUpReg_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return powerUpReg_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::powerUpReg_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    if((idx + 1) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::powerUpReg_Unpack() index out of bounds\n");
        return -1;
    }
    powerUpReg_internal_value = bits[idx++];
    powerUpReg_present = true;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::powerUpReg_Value() const
{
    if(powerUpReg_present)
        return powerUpReg_internal_value;
    return false;
}

int CSFB_RegistrationParam1XRTT::powerUpReg_SetValue(bool value)
{
    powerUpReg_internal_value = value;
    powerUpReg_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::powerUpReg_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "powerUpReg = " + std::to_string(powerUpReg_internal_value) + "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::powerUpReg_ToStringNoNewLines() const
{
    std::string out = "powerUpReg=" + std::to_string(powerUpReg_internal_value) + ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::powerUpReg_Clear()
{
    powerUpReg_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::powerUpReg_IsPresent() const
{
    return powerUpReg_present;
}

int CSFB_RegistrationParam1XRTT::registrationPeriod_Pack(std::vector<uint8_t> &bits)
{
    if(!registrationPeriod_present)
    {
        printf("CSFB_RegistrationParam1XRTT::registrationPeriod_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 7;
    if(size < 7 || size > 7)
    {
        printf("CSFB_RegistrationParam1XRTT::registrationPeriod_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((registrationPeriod_internal_value >> (7-i-1)) & 1);
    return 0;
}

int CSFB_RegistrationParam1XRTT::registrationPeriod_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return registrationPeriod_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::registrationPeriod_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 7;
    if(size < 7 || size > 7)
    {
        printf("CSFB_RegistrationParam1XRTT::registrationPeriod_Unpack() size failure\n");
        return -1;
    }
    registrationPeriod_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::registrationPeriod_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        registrationPeriod_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(7-i-1);
    registrationPeriod_present = true;
    return 0;
}

uint8_t CSFB_RegistrationParam1XRTT::registrationPeriod_Value() const
{
    if(registrationPeriod_present)
        return registrationPeriod_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int CSFB_RegistrationParam1XRTT::registrationPeriod_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 7)
    {
        printf("CSFB_RegistrationParam1XRTT::registrationPeriod_SetValue() size failure\n");
        return -1;
    }
    registrationPeriod_internal_value = value;
    registrationPeriod_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::registrationPeriod_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "registrationPeriod = ";
    out += std::to_string(registrationPeriod_internal_value);
    out += "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::registrationPeriod_ToStringNoNewLines() const
{
    std::string out = "registrationPeriod=";
    out += std::to_string(registrationPeriod_internal_value);
    out += ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::registrationPeriod_Clear()
{
    registrationPeriod_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::registrationPeriod_IsPresent() const
{
    return registrationPeriod_present;
}

int CSFB_RegistrationParam1XRTT::registrationZone_Pack(std::vector<uint8_t> &bits)
{
    if(!registrationZone_present)
    {
        printf("CSFB_RegistrationParam1XRTT::registrationZone_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 12;
    if(size < 12 || size > 12)
    {
        printf("CSFB_RegistrationParam1XRTT::registrationZone_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((registrationZone_internal_value >> (12-i-1)) & 1);
    return 0;
}

int CSFB_RegistrationParam1XRTT::registrationZone_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return registrationZone_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::registrationZone_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 12;
    if(size < 12 || size > 12)
    {
        printf("CSFB_RegistrationParam1XRTT::registrationZone_Unpack() size failure\n");
        return -1;
    }
    registrationZone_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::registrationZone_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        registrationZone_internal_value |= (uint16_t)bits[idx++] << (uint16_t)(12-i-1);
    registrationZone_present = true;
    return 0;
}

uint16_t CSFB_RegistrationParam1XRTT::registrationZone_Value() const
{
    if(registrationZone_present)
        return registrationZone_internal_value;
    uint16_t tmp = 0;
    return tmp;
}

int CSFB_RegistrationParam1XRTT::registrationZone_SetValue(uint16_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 12)
    {
        printf("CSFB_RegistrationParam1XRTT::registrationZone_SetValue() size failure\n");
        return -1;
    }
    registrationZone_internal_value = value;
    registrationZone_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::registrationZone_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "registrationZone = ";
    out += std::to_string(registrationZone_internal_value);
    out += "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::registrationZone_ToStringNoNewLines() const
{
    std::string out = "registrationZone=";
    out += std::to_string(registrationZone_internal_value);
    out += ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::registrationZone_Clear()
{
    registrationZone_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::registrationZone_IsPresent() const
{
    return registrationZone_present;
}

int CSFB_RegistrationParam1XRTT::totalZone_Pack(std::vector<uint8_t> &bits)
{
    if(!totalZone_present)
    {
        printf("CSFB_RegistrationParam1XRTT::totalZone_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 3;
    if(size < 3 || size > 3)
    {
        printf("CSFB_RegistrationParam1XRTT::totalZone_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((totalZone_internal_value >> (3-i-1)) & 1);
    return 0;
}

int CSFB_RegistrationParam1XRTT::totalZone_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return totalZone_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::totalZone_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 3;
    if(size < 3 || size > 3)
    {
        printf("CSFB_RegistrationParam1XRTT::totalZone_Unpack() size failure\n");
        return -1;
    }
    totalZone_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::totalZone_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        totalZone_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(3-i-1);
    totalZone_present = true;
    return 0;
}

uint8_t CSFB_RegistrationParam1XRTT::totalZone_Value() const
{
    if(totalZone_present)
        return totalZone_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int CSFB_RegistrationParam1XRTT::totalZone_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 3)
    {
        printf("CSFB_RegistrationParam1XRTT::totalZone_SetValue() size failure\n");
        return -1;
    }
    totalZone_internal_value = value;
    totalZone_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::totalZone_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "totalZone = ";
    out += std::to_string(totalZone_internal_value);
    out += "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::totalZone_ToStringNoNewLines() const
{
    std::string out = "totalZone=";
    out += std::to_string(totalZone_internal_value);
    out += ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::totalZone_Clear()
{
    totalZone_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::totalZone_IsPresent() const
{
    return totalZone_present;
}

int CSFB_RegistrationParam1XRTT::zoneTimer_Pack(std::vector<uint8_t> &bits)
{
    if(!zoneTimer_present)
    {
        printf("CSFB_RegistrationParam1XRTT::zoneTimer_Pack() presence failure\n");
        return -1;
    }
    uint32_t size = 3;
    if(size < 3 || size > 3)
    {
        printf("CSFB_RegistrationParam1XRTT::zoneTimer_Pack() size failure\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        bits.push_back((zoneTimer_internal_value >> (3-i-1)) & 1);
    return 0;
}

int CSFB_RegistrationParam1XRTT::zoneTimer_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return zoneTimer_Unpack(bits, idx);
}

int CSFB_RegistrationParam1XRTT::zoneTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    uint32_t size = 3;
    if(size < 3 || size > 3)
    {
        printf("CSFB_RegistrationParam1XRTT::zoneTimer_Unpack() size failure\n");
        return -1;
    }
    zoneTimer_internal_value = 0;
    if((idx + size) > bits.size())
    {
        printf("CSFB_RegistrationParam1XRTT::zoneTimer_Unpack() index out of bounds\n");
        return -1;
    }
    for(uint32_t i=0; i<size; i++)
        zoneTimer_internal_value |= (uint8_t)bits[idx++] << (uint8_t)(3-i-1);
    zoneTimer_present = true;
    return 0;
}

uint8_t CSFB_RegistrationParam1XRTT::zoneTimer_Value() const
{
    if(zoneTimer_present)
        return zoneTimer_internal_value;
    uint8_t tmp = 0;
    return tmp;
}

int CSFB_RegistrationParam1XRTT::zoneTimer_SetValue(uint8_t value)
{
    uint32_t size = 1;
    while(pow(2, size) <= value)
        size++;
    if(size > 3)
    {
        printf("CSFB_RegistrationParam1XRTT::zoneTimer_SetValue() size failure\n");
        return -1;
    }
    zoneTimer_internal_value = value;
    zoneTimer_present = true;
    return 0;
}

std::string CSFB_RegistrationParam1XRTT::zoneTimer_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "zoneTimer = ";
    out += std::to_string(zoneTimer_internal_value);
    out += "\n";
    return out;
}

std::string CSFB_RegistrationParam1XRTT::zoneTimer_ToStringNoNewLines() const
{
    std::string out = "zoneTimer=";
    out += std::to_string(zoneTimer_internal_value);
    out += ",";
    return out;
}

int CSFB_RegistrationParam1XRTT::zoneTimer_Clear()
{
    zoneTimer_present = false;
    return 0;
}

bool CSFB_RegistrationParam1XRTT::zoneTimer_IsPresent() const
{
    return zoneTimer_present;
}

