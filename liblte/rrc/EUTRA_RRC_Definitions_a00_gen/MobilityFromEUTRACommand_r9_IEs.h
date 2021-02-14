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

#ifndef __MobilityFromEUTRACommand_r9_IEs_H__
#define __MobilityFromEUTRACommand_r9_IEs_H__

#include "Handover.h"
#include "CellChangeOrder.h"
#include "E_CSFB_r9.h"
#include "MobilityFromEUTRACommand_v930_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class MobilityFromEUTRACommand_r9_IEs
{
public:
    MobilityFromEUTRACommand_r9_IEs() : cs_FallbackIndicator_present{false}, purpose_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cs-FallbackIndicator
public:
    int cs_FallbackIndicator_Pack(std::vector<uint8_t> &bits);
    int cs_FallbackIndicator_Unpack(std::vector<uint8_t> bits);
    int cs_FallbackIndicator_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool cs_FallbackIndicator_Value() const;
    int cs_FallbackIndicator_SetValue(bool value);
    std::string cs_FallbackIndicator_ToString(uint32_t indent) const;
    std::string cs_FallbackIndicator_ToStringNoNewLines() const;
    int cs_FallbackIndicator_Clear();
    bool cs_FallbackIndicator_IsPresent() const;
private:
    bool cs_FallbackIndicator_present;
    bool cs_FallbackIndicator_internal_value;

    // purpose
public:
    enum purpose_Enum {
        k_purpose_handover = 0,
        k_purpose_cellChangeOrder,
        k_purpose_e_CSFB_r9,
    };
    int purpose_Pack(std::vector<uint8_t> &bits);
    int purpose_Unpack(std::vector<uint8_t> bits);
    int purpose_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    purpose_Enum purpose_Choice() const;
    int purpose_SetChoice(purpose_Enum choice);
    std::string purpose_ChoiceToString(purpose_Enum value) const;
    uint64_t purpose_NumberOfChoices() const;
    std::string purpose_ToString(uint32_t indent) const;
    std::string purpose_ToStringNoNewLines() const;
    int purpose_Clear();
    bool purpose_IsPresent() const;
private:
    bool purpose_present;
    purpose_Enum purpose_internal_choice;

    // handover
public:
    Handover* purpose_handover_Set();
    int purpose_handover_Set(Handover &value);
    const Handover& purpose_handover_Get() const;
    std::string purpose_handover_ToString(uint32_t indent) const;
    std::string purpose_handover_ToStringNoNewLines() const;
    int purpose_handover_Clear();
    bool purpose_handover_IsPresent() const;
private:
    bool purpose_handover_present;
    Handover purpose_handover;

    // cellChangeOrder
public:
    CellChangeOrder* purpose_cellChangeOrder_Set();
    int purpose_cellChangeOrder_Set(CellChangeOrder &value);
    const CellChangeOrder& purpose_cellChangeOrder_Get() const;
    std::string purpose_cellChangeOrder_ToString(uint32_t indent) const;
    std::string purpose_cellChangeOrder_ToStringNoNewLines() const;
    int purpose_cellChangeOrder_Clear();
    bool purpose_cellChangeOrder_IsPresent() const;
private:
    bool purpose_cellChangeOrder_present;
    CellChangeOrder purpose_cellChangeOrder;

    // e-CSFB-r9
public:
    E_CSFB_r9* purpose_e_CSFB_r9_Set();
    int purpose_e_CSFB_r9_Set(E_CSFB_r9 &value);
    const E_CSFB_r9& purpose_e_CSFB_r9_Get() const;
    std::string purpose_e_CSFB_r9_ToString(uint32_t indent) const;
    std::string purpose_e_CSFB_r9_ToStringNoNewLines() const;
    int purpose_e_CSFB_r9_Clear();
    bool purpose_e_CSFB_r9_IsPresent() const;
private:
    bool purpose_e_CSFB_r9_present;
    E_CSFB_r9 purpose_e_CSFB_r9;


    // nonCriticalExtension
public:
    MobilityFromEUTRACommand_v930_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(MobilityFromEUTRACommand_v930_IEs &value);
    const MobilityFromEUTRACommand_v930_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    MobilityFromEUTRACommand_v930_IEs nonCriticalExtension;

};

#endif
