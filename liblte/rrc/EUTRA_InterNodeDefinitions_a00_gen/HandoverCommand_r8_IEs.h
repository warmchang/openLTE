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

#ifndef __HandoverCommand_r8_IEs_H__
#define __HandoverCommand_r8_IEs_H__

#include <array>
#include <cstdint>
#include <vector>

class HandoverCommand_r8_IEs
{
public:
    HandoverCommand_r8_IEs() : handoverCommandMessage_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // handoverCommandMessage
public:
    int handoverCommandMessage_Pack(std::vector<uint8_t> &bits);
    int handoverCommandMessage_Unpack(std::vector<uint8_t> bits);
    int handoverCommandMessage_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> handoverCommandMessage_Value() const;
    int handoverCommandMessage_SetValue(std::vector<uint8_t> value);
    std::string handoverCommandMessage_ToString(uint32_t indent) const;
    std::string handoverCommandMessage_ToStringNoNewLines() const;
    int handoverCommandMessage_Clear();
    bool handoverCommandMessage_IsPresent() const;
private:
    bool handoverCommandMessage_present;
    std::vector<uint8_t> handoverCommandMessage_internal_value;

    // nonCriticalExtension

};

#endif
