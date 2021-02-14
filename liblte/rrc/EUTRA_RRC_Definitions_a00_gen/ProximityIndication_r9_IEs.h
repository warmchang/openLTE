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

#ifndef __ProximityIndication_r9_IEs_H__
#define __ProximityIndication_r9_IEs_H__

#include "ARFCN_ValueEUTRA.h"
#include "ARFCN_ValueUTRA.h"
#include "ProximityIndication_v930_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class ProximityIndication_r9_IEs
{
public:
    ProximityIndication_r9_IEs() : type_r9_present{false}, carrierFreq_r9_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // type-r9
public:
    enum type_r9_Enum {
        k_type_r9_entering = 0,
        k_type_r9_leaving,
    };
    int type_r9_Pack(std::vector<uint8_t> &bits);
    int type_r9_Unpack(std::vector<uint8_t> bits);
    int type_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    type_r9_Enum type_r9_Value() const;
    int type_r9_SetValue(type_r9_Enum value);
    int type_r9_SetValue(std::string value);
    std::string type_r9_ValueToString(type_r9_Enum value) const;
    uint64_t type_r9_NumberOfValues() const;
    std::string type_r9_ToString(uint32_t indent) const;
    std::string type_r9_ToStringNoNewLines() const;
    int type_r9_Clear();
    bool type_r9_IsPresent() const;
private:
    bool type_r9_present;
    type_r9_Enum type_r9_internal_value;

    // carrierFreq-r9
public:
    enum carrierFreq_r9_Enum {
        k_carrierFreq_r9_eutra_r9 = 0,
        k_carrierFreq_r9_utra_r9,
    };
    int carrierFreq_r9_Pack(std::vector<uint8_t> &bits);
    int carrierFreq_r9_Unpack(std::vector<uint8_t> bits);
    int carrierFreq_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    carrierFreq_r9_Enum carrierFreq_r9_Choice() const;
    int carrierFreq_r9_SetChoice(carrierFreq_r9_Enum choice);
    std::string carrierFreq_r9_ChoiceToString(carrierFreq_r9_Enum value) const;
    uint64_t carrierFreq_r9_NumberOfChoices() const;
    std::string carrierFreq_r9_ToString(uint32_t indent) const;
    std::string carrierFreq_r9_ToStringNoNewLines() const;
    int carrierFreq_r9_Clear();
    bool carrierFreq_r9_IsPresent() const;
private:
    bool carrierFreq_r9_present;
    carrierFreq_r9_Enum carrierFreq_r9_internal_choice;

    // eutra-r9
public:
    ARFCN_ValueEUTRA* carrierFreq_r9_eutra_r9_Set();
    int carrierFreq_r9_eutra_r9_Set(ARFCN_ValueEUTRA &value);
    const ARFCN_ValueEUTRA& carrierFreq_r9_eutra_r9_Get() const;
    std::string carrierFreq_r9_eutra_r9_ToString(uint32_t indent) const;
    std::string carrierFreq_r9_eutra_r9_ToStringNoNewLines() const;
    int carrierFreq_r9_eutra_r9_Clear();
    bool carrierFreq_r9_eutra_r9_IsPresent() const;
private:
    bool carrierFreq_r9_eutra_r9_present;
    ARFCN_ValueEUTRA carrierFreq_r9_eutra_r9;

    // utra-r9
public:
    ARFCN_ValueUTRA* carrierFreq_r9_utra_r9_Set();
    int carrierFreq_r9_utra_r9_Set(ARFCN_ValueUTRA &value);
    const ARFCN_ValueUTRA& carrierFreq_r9_utra_r9_Get() const;
    std::string carrierFreq_r9_utra_r9_ToString(uint32_t indent) const;
    std::string carrierFreq_r9_utra_r9_ToStringNoNewLines() const;
    int carrierFreq_r9_utra_r9_Clear();
    bool carrierFreq_r9_utra_r9_IsPresent() const;
private:
    bool carrierFreq_r9_utra_r9_present;
    ARFCN_ValueUTRA carrierFreq_r9_utra_r9;


    // nonCriticalExtension
public:
    ProximityIndication_v930_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(ProximityIndication_v930_IEs &value);
    const ProximityIndication_v930_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    ProximityIndication_v930_IEs nonCriticalExtension;

};

#endif
