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

#ifndef __SecurityConfigHO_H__
#define __SecurityConfigHO_H__

#include "SecurityAlgorithmConfig.h"
#include "NextHopChainingCount.h"
#include "SecurityAlgorithmConfig.h"

#include <array>
#include <cstdint>
#include <vector>

class SecurityConfigHO
{
public:
    SecurityConfigHO() : handoverType_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // handoverType
public:
    enum handoverType_Enum {
        k_handoverType_intraLTE = 0,
        k_handoverType_interRAT,
    };
    int handoverType_Pack(std::vector<uint8_t> &bits);
    int handoverType_Unpack(std::vector<uint8_t> bits);
    int handoverType_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    handoverType_Enum handoverType_Choice() const;
    int handoverType_SetChoice(handoverType_Enum choice);
    std::string handoverType_ChoiceToString(handoverType_Enum value) const;
    uint64_t handoverType_NumberOfChoices() const;
    std::string handoverType_ToString(uint32_t indent) const;
    std::string handoverType_ToStringNoNewLines() const;
    int handoverType_Clear();
    bool handoverType_IsPresent() const;
private:
    bool handoverType_present;
    handoverType_Enum handoverType_internal_choice;

    // intraLTE
public:
    class handoverType_intraLTE
    {
    public:
        handoverType_intraLTE() : securityAlgorithmConfig_present{false}, keyChangeIndicator_present{false}, nextHopChainingCount_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // securityAlgorithmConfig
    public:
        SecurityAlgorithmConfig* securityAlgorithmConfig_Set();
        int securityAlgorithmConfig_Set(SecurityAlgorithmConfig &value);
        const SecurityAlgorithmConfig& securityAlgorithmConfig_Get() const;
        std::string securityAlgorithmConfig_ToString(uint32_t indent) const;
        std::string securityAlgorithmConfig_ToStringNoNewLines() const;
        int securityAlgorithmConfig_Clear();
        bool securityAlgorithmConfig_IsPresent() const;
    private:
        bool securityAlgorithmConfig_present;
        SecurityAlgorithmConfig securityAlgorithmConfig;

        // keyChangeIndicator
    public:
        int keyChangeIndicator_Pack(std::vector<uint8_t> &bits);
        int keyChangeIndicator_Unpack(std::vector<uint8_t> bits);
        int keyChangeIndicator_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool keyChangeIndicator_Value() const;
        int keyChangeIndicator_SetValue(bool value);
        std::string keyChangeIndicator_ToString(uint32_t indent) const;
        std::string keyChangeIndicator_ToStringNoNewLines() const;
        int keyChangeIndicator_Clear();
        bool keyChangeIndicator_IsPresent() const;
    private:
        bool keyChangeIndicator_present;
        bool keyChangeIndicator_internal_value;

        // nextHopChainingCount
    public:
        NextHopChainingCount* nextHopChainingCount_Set();
        int nextHopChainingCount_Set(NextHopChainingCount &value);
        const NextHopChainingCount& nextHopChainingCount_Get() const;
        std::string nextHopChainingCount_ToString(uint32_t indent) const;
        std::string nextHopChainingCount_ToStringNoNewLines() const;
        int nextHopChainingCount_Clear();
        bool nextHopChainingCount_IsPresent() const;
    private:
        bool nextHopChainingCount_present;
        NextHopChainingCount nextHopChainingCount;

    };

    handoverType_intraLTE handoverType_intraLTE_value;

    // interRAT
public:
    class handoverType_interRAT
    {
    public:
        handoverType_interRAT() : securityAlgorithmConfig_present{false}, nas_SecurityParamToEUTRA_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // securityAlgorithmConfig
    public:
        SecurityAlgorithmConfig* securityAlgorithmConfig_Set();
        int securityAlgorithmConfig_Set(SecurityAlgorithmConfig &value);
        const SecurityAlgorithmConfig& securityAlgorithmConfig_Get() const;
        std::string securityAlgorithmConfig_ToString(uint32_t indent) const;
        std::string securityAlgorithmConfig_ToStringNoNewLines() const;
        int securityAlgorithmConfig_Clear();
        bool securityAlgorithmConfig_IsPresent() const;
    private:
        bool securityAlgorithmConfig_present;
        SecurityAlgorithmConfig securityAlgorithmConfig;

        // nas-SecurityParamToEUTRA
    public:
        int nas_SecurityParamToEUTRA_Pack(std::vector<uint8_t> &bits);
        int nas_SecurityParamToEUTRA_Unpack(std::vector<uint8_t> bits);
        int nas_SecurityParamToEUTRA_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::vector<uint8_t> nas_SecurityParamToEUTRA_Value() const;
        int nas_SecurityParamToEUTRA_SetValue(std::vector<uint8_t> value);
        std::string nas_SecurityParamToEUTRA_ToString(uint32_t indent) const;
        std::string nas_SecurityParamToEUTRA_ToStringNoNewLines() const;
        int nas_SecurityParamToEUTRA_Clear();
        bool nas_SecurityParamToEUTRA_IsPresent() const;
    private:
        bool nas_SecurityParamToEUTRA_present;
        std::vector<uint8_t> nas_SecurityParamToEUTRA_internal_value;

    };

    handoverType_interRAT handoverType_interRAT_value;


};

#endif
