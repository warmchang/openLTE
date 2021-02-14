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

#ifndef __PLMN_Identity_H__
#define __PLMN_Identity_H__

#include "MCC.h"
#include "MNC.h"

#include <array>
#include <cstdint>
#include <vector>

class PLMN_Identity
{
public:
    PLMN_Identity() : mcc_present{false}, mnc_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // mcc
public:
    MCC* mcc_Set();
    int mcc_Set(MCC &value);
    const MCC& mcc_Get() const;
    std::string mcc_ToString(uint32_t indent) const;
    std::string mcc_ToStringNoNewLines() const;
    int mcc_Clear();
    bool mcc_IsPresent() const;
private:
    bool mcc_present;
    MCC mcc;

    // mnc
public:
    MNC* mnc_Set();
    int mnc_Set(MNC &value);
    const MNC& mnc_Get() const;
    std::string mnc_ToString(uint32_t indent) const;
    std::string mnc_ToStringNoNewLines() const;
    int mnc_Clear();
    bool mnc_IsPresent() const;
private:
    bool mnc_present;
    MNC mnc;

};

#endif
