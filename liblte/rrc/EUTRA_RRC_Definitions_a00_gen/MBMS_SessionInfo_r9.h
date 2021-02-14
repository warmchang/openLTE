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

#ifndef __MBMS_SessionInfo_r9_H__
#define __MBMS_SessionInfo_r9_H__

#include "TMGI_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class MBMS_SessionInfo_r9
{
public:
    MBMS_SessionInfo_r9() : tmgi_r9_present{false}, sessionId_r9_present{false}, logicalChannelIdentity_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // tmgi-r9
public:
    TMGI_r9* tmgi_r9_Set();
    int tmgi_r9_Set(TMGI_r9 &value);
    const TMGI_r9& tmgi_r9_Get() const;
    std::string tmgi_r9_ToString(uint32_t indent) const;
    std::string tmgi_r9_ToStringNoNewLines() const;
    int tmgi_r9_Clear();
    bool tmgi_r9_IsPresent() const;
private:
    bool tmgi_r9_present;
    TMGI_r9 tmgi_r9;

    // sessionId-r9
public:
    int sessionId_r9_Pack(std::vector<uint8_t> &bits);
    int sessionId_r9_Unpack(std::vector<uint8_t> bits);
    int sessionId_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> sessionId_r9_Value() const;
    int sessionId_r9_SetValue(std::vector<uint8_t> value);
    std::string sessionId_r9_ToString(uint32_t indent) const;
    std::string sessionId_r9_ToStringNoNewLines() const;
    int sessionId_r9_Clear();
    bool sessionId_r9_IsPresent() const;
private:
    bool sessionId_r9_present;
    std::vector<uint8_t> sessionId_r9_internal_value;

    // logicalChannelIdentity-r9
public:
    int logicalChannelIdentity_r9_Pack(std::vector<uint8_t> &bits);
    int logicalChannelIdentity_r9_Unpack(std::vector<uint8_t> bits);
    int logicalChannelIdentity_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t logicalChannelIdentity_r9_Value() const;
    int logicalChannelIdentity_r9_SetValue(int64_t value);
    std::string logicalChannelIdentity_r9_ToString(uint32_t indent) const;
    std::string logicalChannelIdentity_r9_ToStringNoNewLines() const;
    int logicalChannelIdentity_r9_Clear();
    bool logicalChannelIdentity_r9_IsPresent() const;
private:
    bool logicalChannelIdentity_r9_present;
    int64_t logicalChannelIdentity_r9_internal_value;

};

#endif
