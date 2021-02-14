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

#ifndef __SystemInformation_r8_IEs_H__
#define __SystemInformation_r8_IEs_H__

#include "SystemInformationBlockType2.h"
#include "SystemInformationBlockType3.h"
#include "SystemInformationBlockType4.h"
#include "SystemInformationBlockType5.h"
#include "SystemInformationBlockType6.h"
#include "SystemInformationBlockType7.h"
#include "SystemInformationBlockType8.h"
#include "SystemInformationBlockType9.h"
#include "SystemInformationBlockType10.h"
#include "SystemInformationBlockType11.h"
#include "SystemInformationBlockType12_r9.h"
#include "SystemInformationBlockType13_r9.h"
#include "SystemInformation_v8a0_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformation_r8_IEs
{
public:
    SystemInformation_r8_IEs() : sib_TypeAndInfo_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // sib-TypeAndInfo
public:
    class sib_TypeAndInfo_
    {
    public:
        enum sib_TypeAndInfo_Enum {
            k_sib_TypeAndInfo_sib2 = 0,
            k_sib_TypeAndInfo_sib3,
            k_sib_TypeAndInfo_sib4,
            k_sib_TypeAndInfo_sib5,
            k_sib_TypeAndInfo_sib6,
            k_sib_TypeAndInfo_sib7,
            k_sib_TypeAndInfo_sib8,
            k_sib_TypeAndInfo_sib9,
            k_sib_TypeAndInfo_sib10,
            k_sib_TypeAndInfo_sib11,
            k_sib_TypeAndInfo_sib12_v920,
            k_sib_TypeAndInfo_sib13_v920,
        };
        int sib_TypeAndInfo_Pack(std::vector<uint8_t> &bits);
        int sib_TypeAndInfo_Unpack(std::vector<uint8_t> bits);
        int sib_TypeAndInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        sib_TypeAndInfo_Enum sib_TypeAndInfo_Choice() const;
        int sib_TypeAndInfo_SetChoice(sib_TypeAndInfo_Enum choice);
        std::string sib_TypeAndInfo_ChoiceToString(sib_TypeAndInfo_Enum value) const;
        uint64_t sib_TypeAndInfo_NumberOfChoices() const;
        std::string sib_TypeAndInfo_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_ToStringNoNewLines() const;
        int sib_TypeAndInfo_Clear();
        bool sib_TypeAndInfo_IsPresent() const;
    private:
        bool sib_TypeAndInfo_present;
        sib_TypeAndInfo_Enum sib_TypeAndInfo_internal_choice;

        // sib2
    public:
        SystemInformationBlockType2* sib_TypeAndInfo_sib2_Set();
        int sib_TypeAndInfo_sib2_Set(SystemInformationBlockType2 &value);
        const SystemInformationBlockType2& sib_TypeAndInfo_sib2_Get() const;
        std::string sib_TypeAndInfo_sib2_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib2_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib2_Clear();
        bool sib_TypeAndInfo_sib2_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib2_present;
        SystemInformationBlockType2 sib_TypeAndInfo_sib2;

        // sib3
    public:
        SystemInformationBlockType3* sib_TypeAndInfo_sib3_Set();
        int sib_TypeAndInfo_sib3_Set(SystemInformationBlockType3 &value);
        const SystemInformationBlockType3& sib_TypeAndInfo_sib3_Get() const;
        std::string sib_TypeAndInfo_sib3_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib3_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib3_Clear();
        bool sib_TypeAndInfo_sib3_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib3_present;
        SystemInformationBlockType3 sib_TypeAndInfo_sib3;

        // sib4
    public:
        SystemInformationBlockType4* sib_TypeAndInfo_sib4_Set();
        int sib_TypeAndInfo_sib4_Set(SystemInformationBlockType4 &value);
        const SystemInformationBlockType4& sib_TypeAndInfo_sib4_Get() const;
        std::string sib_TypeAndInfo_sib4_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib4_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib4_Clear();
        bool sib_TypeAndInfo_sib4_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib4_present;
        SystemInformationBlockType4 sib_TypeAndInfo_sib4;

        // sib5
    public:
        SystemInformationBlockType5* sib_TypeAndInfo_sib5_Set();
        int sib_TypeAndInfo_sib5_Set(SystemInformationBlockType5 &value);
        const SystemInformationBlockType5& sib_TypeAndInfo_sib5_Get() const;
        std::string sib_TypeAndInfo_sib5_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib5_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib5_Clear();
        bool sib_TypeAndInfo_sib5_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib5_present;
        SystemInformationBlockType5 sib_TypeAndInfo_sib5;

        // sib6
    public:
        SystemInformationBlockType6* sib_TypeAndInfo_sib6_Set();
        int sib_TypeAndInfo_sib6_Set(SystemInformationBlockType6 &value);
        const SystemInformationBlockType6& sib_TypeAndInfo_sib6_Get() const;
        std::string sib_TypeAndInfo_sib6_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib6_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib6_Clear();
        bool sib_TypeAndInfo_sib6_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib6_present;
        SystemInformationBlockType6 sib_TypeAndInfo_sib6;

        // sib7
    public:
        SystemInformationBlockType7* sib_TypeAndInfo_sib7_Set();
        int sib_TypeAndInfo_sib7_Set(SystemInformationBlockType7 &value);
        const SystemInformationBlockType7& sib_TypeAndInfo_sib7_Get() const;
        std::string sib_TypeAndInfo_sib7_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib7_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib7_Clear();
        bool sib_TypeAndInfo_sib7_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib7_present;
        SystemInformationBlockType7 sib_TypeAndInfo_sib7;

        // sib8
    public:
        SystemInformationBlockType8* sib_TypeAndInfo_sib8_Set();
        int sib_TypeAndInfo_sib8_Set(SystemInformationBlockType8 &value);
        const SystemInformationBlockType8& sib_TypeAndInfo_sib8_Get() const;
        std::string sib_TypeAndInfo_sib8_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib8_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib8_Clear();
        bool sib_TypeAndInfo_sib8_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib8_present;
        SystemInformationBlockType8 sib_TypeAndInfo_sib8;

        // sib9
    public:
        SystemInformationBlockType9* sib_TypeAndInfo_sib9_Set();
        int sib_TypeAndInfo_sib9_Set(SystemInformationBlockType9 &value);
        const SystemInformationBlockType9& sib_TypeAndInfo_sib9_Get() const;
        std::string sib_TypeAndInfo_sib9_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib9_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib9_Clear();
        bool sib_TypeAndInfo_sib9_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib9_present;
        SystemInformationBlockType9 sib_TypeAndInfo_sib9;

        // sib10
    public:
        SystemInformationBlockType10* sib_TypeAndInfo_sib10_Set();
        int sib_TypeAndInfo_sib10_Set(SystemInformationBlockType10 &value);
        const SystemInformationBlockType10& sib_TypeAndInfo_sib10_Get() const;
        std::string sib_TypeAndInfo_sib10_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib10_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib10_Clear();
        bool sib_TypeAndInfo_sib10_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib10_present;
        SystemInformationBlockType10 sib_TypeAndInfo_sib10;

        // sib11
    public:
        SystemInformationBlockType11* sib_TypeAndInfo_sib11_Set();
        int sib_TypeAndInfo_sib11_Set(SystemInformationBlockType11 &value);
        const SystemInformationBlockType11& sib_TypeAndInfo_sib11_Get() const;
        std::string sib_TypeAndInfo_sib11_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib11_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib11_Clear();
        bool sib_TypeAndInfo_sib11_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib11_present;
        SystemInformationBlockType11 sib_TypeAndInfo_sib11;

        // sib12-v920
    public:
        SystemInformationBlockType12_r9* sib_TypeAndInfo_sib12_v920_Set();
        int sib_TypeAndInfo_sib12_v920_Set(SystemInformationBlockType12_r9 &value);
        const SystemInformationBlockType12_r9& sib_TypeAndInfo_sib12_v920_Get() const;
        std::string sib_TypeAndInfo_sib12_v920_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib12_v920_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib12_v920_Clear();
        bool sib_TypeAndInfo_sib12_v920_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib12_v920_present;
        SystemInformationBlockType12_r9 sib_TypeAndInfo_sib12_v920;

        // sib13-v920
    public:
        SystemInformationBlockType13_r9* sib_TypeAndInfo_sib13_v920_Set();
        int sib_TypeAndInfo_sib13_v920_Set(SystemInformationBlockType13_r9 &value);
        const SystemInformationBlockType13_r9& sib_TypeAndInfo_sib13_v920_Get() const;
        std::string sib_TypeAndInfo_sib13_v920_ToString(uint32_t indent) const;
        std::string sib_TypeAndInfo_sib13_v920_ToStringNoNewLines() const;
        int sib_TypeAndInfo_sib13_v920_Clear();
        bool sib_TypeAndInfo_sib13_v920_IsPresent() const;
    private:
        bool sib_TypeAndInfo_sib13_v920_present;
        SystemInformationBlockType13_r9 sib_TypeAndInfo_sib13_v920;

    };

public:
    int sib_TypeAndInfo_Pack(std::vector<uint8_t> &bits);
    int sib_TypeAndInfo_Unpack(std::vector<uint8_t> bits);
    int sib_TypeAndInfo_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<sib_TypeAndInfo_> sib_TypeAndInfo_Value() const;
    int sib_TypeAndInfo_SetValue(std::vector<sib_TypeAndInfo_>);
    std::string sib_TypeAndInfo_ToString(uint32_t indent) const;
    std::string sib_TypeAndInfo_ToStringNoNewLines() const;
private:
    std::vector<sib_TypeAndInfo_> sib_TypeAndInfo_internal_value;
    bool sib_TypeAndInfo_present;

    // nonCriticalExtension
public:
    SystemInformation_v8a0_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(SystemInformation_v8a0_IEs &value);
    const SystemInformation_v8a0_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    SystemInformation_v8a0_IEs nonCriticalExtension;

};

#endif
