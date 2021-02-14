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

#ifndef __AdditionalReestabInfo_H__
#define __AdditionalReestabInfo_H__

#include "CellIdentity.h"
#include "Key_eNodeB_Star.h"
#include "ShortMAC_I.h"

#include <array>
#include <cstdint>
#include <vector>

class AdditionalReestabInfo
{
public:
    AdditionalReestabInfo() : cellIdentity_present{false}, key_eNodeB_Star_present{false}, shortMAC_I_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cellIdentity
public:
    CellIdentity* cellIdentity_Set();
    int cellIdentity_Set(CellIdentity &value);
    const CellIdentity& cellIdentity_Get() const;
    std::string cellIdentity_ToString(uint32_t indent) const;
    std::string cellIdentity_ToStringNoNewLines() const;
    int cellIdentity_Clear();
    bool cellIdentity_IsPresent() const;
private:
    bool cellIdentity_present;
    CellIdentity cellIdentity;

    // key-eNodeB-Star
public:
    Key_eNodeB_Star* key_eNodeB_Star_Set();
    int key_eNodeB_Star_Set(Key_eNodeB_Star &value);
    const Key_eNodeB_Star& key_eNodeB_Star_Get() const;
    std::string key_eNodeB_Star_ToString(uint32_t indent) const;
    std::string key_eNodeB_Star_ToStringNoNewLines() const;
    int key_eNodeB_Star_Clear();
    bool key_eNodeB_Star_IsPresent() const;
private:
    bool key_eNodeB_Star_present;
    Key_eNodeB_Star key_eNodeB_Star;

    // shortMAC-I
public:
    ShortMAC_I* shortMAC_I_Set();
    int shortMAC_I_Set(ShortMAC_I &value);
    const ShortMAC_I& shortMAC_I_Get() const;
    std::string shortMAC_I_ToString(uint32_t indent) const;
    std::string shortMAC_I_ToStringNoNewLines() const;
    int shortMAC_I_Clear();
    bool shortMAC_I_IsPresent() const;
private:
    bool shortMAC_I_present;
    ShortMAC_I shortMAC_I;

};

#endif
