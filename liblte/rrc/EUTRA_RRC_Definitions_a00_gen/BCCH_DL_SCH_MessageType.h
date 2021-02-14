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

#ifndef __BCCH_DL_SCH_MessageType_H__
#define __BCCH_DL_SCH_MessageType_H__

#include "SystemInformation.h"
#include "SystemInformationBlockType1.h"

#include <array>
#include <cstdint>
#include <vector>

class BCCH_DL_SCH_MessageType
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
        k_c1_systemInformation = 0,
        k_c1_systemInformationBlockType1,
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

    // systemInformation
public:
    SystemInformation* c1_systemInformation_Set();
    int c1_systemInformation_Set(SystemInformation &value);
    const SystemInformation& c1_systemInformation_Get() const;
    std::string c1_systemInformation_ToString(uint32_t indent) const;
    std::string c1_systemInformation_ToStringNoNewLines() const;
    int c1_systemInformation_Clear();
    bool c1_systemInformation_IsPresent() const;
private:
    bool c1_systemInformation_present;
    SystemInformation c1_systemInformation;

    // systemInformationBlockType1
public:
    SystemInformationBlockType1* c1_systemInformationBlockType1_Set();
    int c1_systemInformationBlockType1_Set(SystemInformationBlockType1 &value);
    const SystemInformationBlockType1& c1_systemInformationBlockType1_Get() const;
    std::string c1_systemInformationBlockType1_ToString(uint32_t indent) const;
    std::string c1_systemInformationBlockType1_ToStringNoNewLines() const;
    int c1_systemInformationBlockType1_Clear();
    bool c1_systemInformationBlockType1_IsPresent() const;
private:
    bool c1_systemInformationBlockType1_present;
    SystemInformationBlockType1 c1_systemInformationBlockType1;


    // messageClassExtension

};

#endif
