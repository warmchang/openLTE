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

#ifndef __PhyLayerParameters_H__
#define __PhyLayerParameters_H__

#include <array>
#include <cstdint>
#include <vector>

class PhyLayerParameters
{
public:
    PhyLayerParameters() : ue_TxAntennaSelectionSupported_present{false}, ue_SpecificRefSigsSupported_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-TxAntennaSelectionSupported
public:
    int ue_TxAntennaSelectionSupported_Pack(std::vector<uint8_t> &bits);
    int ue_TxAntennaSelectionSupported_Unpack(std::vector<uint8_t> bits);
    int ue_TxAntennaSelectionSupported_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool ue_TxAntennaSelectionSupported_Value() const;
    int ue_TxAntennaSelectionSupported_SetValue(bool value);
    std::string ue_TxAntennaSelectionSupported_ToString(uint32_t indent) const;
    std::string ue_TxAntennaSelectionSupported_ToStringNoNewLines() const;
    int ue_TxAntennaSelectionSupported_Clear();
    bool ue_TxAntennaSelectionSupported_IsPresent() const;
private:
    bool ue_TxAntennaSelectionSupported_present;
    bool ue_TxAntennaSelectionSupported_internal_value;

    // ue-SpecificRefSigsSupported
public:
    int ue_SpecificRefSigsSupported_Pack(std::vector<uint8_t> &bits);
    int ue_SpecificRefSigsSupported_Unpack(std::vector<uint8_t> bits);
    int ue_SpecificRefSigsSupported_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool ue_SpecificRefSigsSupported_Value() const;
    int ue_SpecificRefSigsSupported_SetValue(bool value);
    std::string ue_SpecificRefSigsSupported_ToString(uint32_t indent) const;
    std::string ue_SpecificRefSigsSupported_ToStringNoNewLines() const;
    int ue_SpecificRefSigsSupported_Clear();
    bool ue_SpecificRefSigsSupported_IsPresent() const;
private:
    bool ue_SpecificRefSigsSupported_present;
    bool ue_SpecificRefSigsSupported_internal_value;

};

#endif
