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

#ifndef __CarrierFreqsGERAN_H__
#define __CarrierFreqsGERAN_H__

#include "ARFCN_ValueGERAN.h"
#include "BandIndicatorGERAN.h"
#include "ExplicitListOfARFCNs.h"

#include <array>
#include <cstdint>
#include <vector>

class CarrierFreqsGERAN
{
public:
    CarrierFreqsGERAN() : startingARFCN_present{false}, bandIndicator_present{false}, followingARFCNs_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // startingARFCN
public:
    ARFCN_ValueGERAN* startingARFCN_Set();
    int startingARFCN_Set(ARFCN_ValueGERAN &value);
    const ARFCN_ValueGERAN& startingARFCN_Get() const;
    std::string startingARFCN_ToString(uint32_t indent) const;
    std::string startingARFCN_ToStringNoNewLines() const;
    int startingARFCN_Clear();
    bool startingARFCN_IsPresent() const;
private:
    bool startingARFCN_present;
    ARFCN_ValueGERAN startingARFCN;

    // bandIndicator
public:
    BandIndicatorGERAN* bandIndicator_Set();
    int bandIndicator_Set(BandIndicatorGERAN &value);
    const BandIndicatorGERAN& bandIndicator_Get() const;
    std::string bandIndicator_ToString(uint32_t indent) const;
    std::string bandIndicator_ToStringNoNewLines() const;
    int bandIndicator_Clear();
    bool bandIndicator_IsPresent() const;
private:
    bool bandIndicator_present;
    BandIndicatorGERAN bandIndicator;

    // followingARFCNs
public:
    enum followingARFCNs_Enum {
        k_followingARFCNs_explicitListOfARFCNs = 0,
        k_followingARFCNs_equallySpacedARFCNs,
        k_followingARFCNs_variableBitMapOfARFCNs,
    };
    int followingARFCNs_Pack(std::vector<uint8_t> &bits);
    int followingARFCNs_Unpack(std::vector<uint8_t> bits);
    int followingARFCNs_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    followingARFCNs_Enum followingARFCNs_Choice() const;
    int followingARFCNs_SetChoice(followingARFCNs_Enum choice);
    std::string followingARFCNs_ChoiceToString(followingARFCNs_Enum value) const;
    uint64_t followingARFCNs_NumberOfChoices() const;
    std::string followingARFCNs_ToString(uint32_t indent) const;
    std::string followingARFCNs_ToStringNoNewLines() const;
    int followingARFCNs_Clear();
    bool followingARFCNs_IsPresent() const;
private:
    bool followingARFCNs_present;
    followingARFCNs_Enum followingARFCNs_internal_choice;

    // explicitListOfARFCNs
public:
    ExplicitListOfARFCNs* followingARFCNs_explicitListOfARFCNs_Set();
    int followingARFCNs_explicitListOfARFCNs_Set(ExplicitListOfARFCNs &value);
    const ExplicitListOfARFCNs& followingARFCNs_explicitListOfARFCNs_Get() const;
    std::string followingARFCNs_explicitListOfARFCNs_ToString(uint32_t indent) const;
    std::string followingARFCNs_explicitListOfARFCNs_ToStringNoNewLines() const;
    int followingARFCNs_explicitListOfARFCNs_Clear();
    bool followingARFCNs_explicitListOfARFCNs_IsPresent() const;
private:
    bool followingARFCNs_explicitListOfARFCNs_present;
    ExplicitListOfARFCNs followingARFCNs_explicitListOfARFCNs;

    // equallySpacedARFCNs
public:
    class followingARFCNs_equallySpacedARFCNs
    {
    public:
        followingARFCNs_equallySpacedARFCNs() : arfcn_Spacing_present{false}, numberOfFollowingARFCNs_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // arfcn-Spacing
    public:
        int arfcn_Spacing_Pack(std::vector<uint8_t> &bits);
        int arfcn_Spacing_Unpack(std::vector<uint8_t> bits);
        int arfcn_Spacing_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t arfcn_Spacing_Value() const;
        int arfcn_Spacing_SetValue(int64_t value);
        std::string arfcn_Spacing_ToString(uint32_t indent) const;
        std::string arfcn_Spacing_ToStringNoNewLines() const;
        int arfcn_Spacing_Clear();
        bool arfcn_Spacing_IsPresent() const;
    private:
        bool arfcn_Spacing_present;
        int64_t arfcn_Spacing_internal_value;

        // numberOfFollowingARFCNs
    public:
        int numberOfFollowingARFCNs_Pack(std::vector<uint8_t> &bits);
        int numberOfFollowingARFCNs_Unpack(std::vector<uint8_t> bits);
        int numberOfFollowingARFCNs_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t numberOfFollowingARFCNs_Value() const;
        int numberOfFollowingARFCNs_SetValue(int64_t value);
        std::string numberOfFollowingARFCNs_ToString(uint32_t indent) const;
        std::string numberOfFollowingARFCNs_ToStringNoNewLines() const;
        int numberOfFollowingARFCNs_Clear();
        bool numberOfFollowingARFCNs_IsPresent() const;
    private:
        bool numberOfFollowingARFCNs_present;
        int64_t numberOfFollowingARFCNs_internal_value;

    };

    followingARFCNs_equallySpacedARFCNs followingARFCNs_equallySpacedARFCNs_value;

    // variableBitMapOfARFCNs
public:
    int followingARFCNs_variableBitMapOfARFCNs_Pack(std::vector<uint8_t> &bits);
    int followingARFCNs_variableBitMapOfARFCNs_Unpack(std::vector<uint8_t> bits);
    int followingARFCNs_variableBitMapOfARFCNs_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> followingARFCNs_variableBitMapOfARFCNs_Value() const;
    int followingARFCNs_variableBitMapOfARFCNs_SetValue(std::vector<uint8_t> value);
    std::string followingARFCNs_variableBitMapOfARFCNs_ToString(uint32_t indent) const;
    std::string followingARFCNs_variableBitMapOfARFCNs_ToStringNoNewLines() const;
    int followingARFCNs_variableBitMapOfARFCNs_Clear();
    bool followingARFCNs_variableBitMapOfARFCNs_IsPresent() const;
private:
    bool followingARFCNs_variableBitMapOfARFCNs_present;
    std::vector<uint8_t> followingARFCNs_variableBitMapOfARFCNs_internal_value;


};

#endif
