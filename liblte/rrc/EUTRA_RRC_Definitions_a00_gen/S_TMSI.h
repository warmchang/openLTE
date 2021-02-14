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

#ifndef __S_TMSI_H__
#define __S_TMSI_H__

#include "MMEC.h"

#include <array>
#include <cstdint>
#include <vector>

class S_TMSI
{
public:
    S_TMSI() : mmec_present{false}, m_TMSI_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // mmec
public:
    MMEC* mmec_Set();
    int mmec_Set(MMEC &value);
    const MMEC& mmec_Get() const;
    std::string mmec_ToString(uint32_t indent) const;
    std::string mmec_ToStringNoNewLines() const;
    int mmec_Clear();
    bool mmec_IsPresent() const;
private:
    bool mmec_present;
    MMEC mmec;

    // m-TMSI
public:
    int m_TMSI_Pack(std::vector<uint8_t> &bits);
    int m_TMSI_Unpack(std::vector<uint8_t> bits);
    int m_TMSI_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint32_t m_TMSI_Value() const;
    int m_TMSI_SetValue(uint32_t value);
    std::string m_TMSI_ToString(uint32_t indent) const;
    std::string m_TMSI_ToStringNoNewLines() const;
    int m_TMSI_Clear();
    bool m_TMSI_IsPresent() const;
private:
    bool m_TMSI_present;
    uint32_t m_TMSI_internal_value;

};

#endif
