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

#ifndef __UL_CCCH_MessageType_H__
#define __UL_CCCH_MessageType_H__

#include "RRCConnectionReestablishmentRequest.h"
#include "RRCConnectionRequest.h"

#include <array>
#include <cstdint>
#include <vector>

class UL_CCCH_MessageType
{
public:
    enum Enum {
        k_c1 = 0,
        k_messageClassExtension,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Choice() const;
    int SetChoice(Enum choice);
    std::string ChoiceToString(Enum value) const;
    uint64_t NumberOfChoices() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_choice;

    // c1
public:
    enum c1_Enum {
        k_c1_rrcConnectionReestablishmentRequest = 0,
        k_c1_rrcConnectionRequest,
    };
    int c1_Pack(std::vector<uint8_t> &bits);
    int c1_Unpack(std::vector<uint8_t> bits);
    int c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    c1_Enum c1_Choice() const;
    int c1_SetChoice(c1_Enum choice);
    std::string c1_ChoiceToString(c1_Enum value) const;
    uint64_t c1_NumberOfChoices() const;
    std::string c1_ToString(uint32_t indent) const;
    std::string c1_ToStringNoNewLines() const;
    int c1_Clear();
    bool c1_IsPresent() const;
private:
    bool c1_present;
    c1_Enum c1_internal_choice;

    // rrcConnectionReestablishmentRequest
public:
    RRCConnectionReestablishmentRequest* c1_rrcConnectionReestablishmentRequest_Set();
    int c1_rrcConnectionReestablishmentRequest_Set(RRCConnectionReestablishmentRequest &value);
    const RRCConnectionReestablishmentRequest& c1_rrcConnectionReestablishmentRequest_Get() const;
    std::string c1_rrcConnectionReestablishmentRequest_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionReestablishmentRequest_ToStringNoNewLines() const;
    int c1_rrcConnectionReestablishmentRequest_Clear();
    bool c1_rrcConnectionReestablishmentRequest_IsPresent() const;
private:
    bool c1_rrcConnectionReestablishmentRequest_present;
    RRCConnectionReestablishmentRequest c1_rrcConnectionReestablishmentRequest;

    // rrcConnectionRequest
public:
    RRCConnectionRequest* c1_rrcConnectionRequest_Set();
    int c1_rrcConnectionRequest_Set(RRCConnectionRequest &value);
    const RRCConnectionRequest& c1_rrcConnectionRequest_Get() const;
    std::string c1_rrcConnectionRequest_ToString(uint32_t indent) const;
    std::string c1_rrcConnectionRequest_ToStringNoNewLines() const;
    int c1_rrcConnectionRequest_Clear();
    bool c1_rrcConnectionRequest_IsPresent() const;
private:
    bool c1_rrcConnectionRequest_present;
    RRCConnectionRequest c1_rrcConnectionRequest;


    // messageClassExtension

};

#endif
