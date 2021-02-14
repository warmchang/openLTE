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

#ifndef __NeighCellSI_AcquisitionParameters_r9_H__
#define __NeighCellSI_AcquisitionParameters_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class NeighCellSI_AcquisitionParameters_r9
{
public:
    NeighCellSI_AcquisitionParameters_r9() : intraFreqSI_AcquisitionForHO_r9_present{false}, interFreqSI_AcquisitionForHO_r9_present{false}, utran_SI_AcquisitionForHO_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // intraFreqSI-AcquisitionForHO-r9
public:
    enum intraFreqSI_AcquisitionForHO_r9_Enum {
        k_intraFreqSI_AcquisitionForHO_r9_supported = 0,
    };
    int intraFreqSI_AcquisitionForHO_r9_Pack(std::vector<uint8_t> &bits);
    int intraFreqSI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits);
    int intraFreqSI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    intraFreqSI_AcquisitionForHO_r9_Enum intraFreqSI_AcquisitionForHO_r9_Value() const;
    int intraFreqSI_AcquisitionForHO_r9_SetValue(intraFreqSI_AcquisitionForHO_r9_Enum value);
    int intraFreqSI_AcquisitionForHO_r9_SetValue(std::string value);
    std::string intraFreqSI_AcquisitionForHO_r9_ValueToString(intraFreqSI_AcquisitionForHO_r9_Enum value) const;
    uint64_t intraFreqSI_AcquisitionForHO_r9_NumberOfValues() const;
    std::string intraFreqSI_AcquisitionForHO_r9_ToString(uint32_t indent) const;
    std::string intraFreqSI_AcquisitionForHO_r9_ToStringNoNewLines() const;
    int intraFreqSI_AcquisitionForHO_r9_Clear();
    bool intraFreqSI_AcquisitionForHO_r9_IsPresent() const;
private:
    bool intraFreqSI_AcquisitionForHO_r9_present;
    intraFreqSI_AcquisitionForHO_r9_Enum intraFreqSI_AcquisitionForHO_r9_internal_value;

    // interFreqSI-AcquisitionForHO-r9
public:
    enum interFreqSI_AcquisitionForHO_r9_Enum {
        k_interFreqSI_AcquisitionForHO_r9_supported = 0,
    };
    int interFreqSI_AcquisitionForHO_r9_Pack(std::vector<uint8_t> &bits);
    int interFreqSI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits);
    int interFreqSI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    interFreqSI_AcquisitionForHO_r9_Enum interFreqSI_AcquisitionForHO_r9_Value() const;
    int interFreqSI_AcquisitionForHO_r9_SetValue(interFreqSI_AcquisitionForHO_r9_Enum value);
    int interFreqSI_AcquisitionForHO_r9_SetValue(std::string value);
    std::string interFreqSI_AcquisitionForHO_r9_ValueToString(interFreqSI_AcquisitionForHO_r9_Enum value) const;
    uint64_t interFreqSI_AcquisitionForHO_r9_NumberOfValues() const;
    std::string interFreqSI_AcquisitionForHO_r9_ToString(uint32_t indent) const;
    std::string interFreqSI_AcquisitionForHO_r9_ToStringNoNewLines() const;
    int interFreqSI_AcquisitionForHO_r9_Clear();
    bool interFreqSI_AcquisitionForHO_r9_IsPresent() const;
private:
    bool interFreqSI_AcquisitionForHO_r9_present;
    interFreqSI_AcquisitionForHO_r9_Enum interFreqSI_AcquisitionForHO_r9_internal_value;

    // utran-SI-AcquisitionForHO-r9
public:
    enum utran_SI_AcquisitionForHO_r9_Enum {
        k_utran_SI_AcquisitionForHO_r9_supported = 0,
    };
    int utran_SI_AcquisitionForHO_r9_Pack(std::vector<uint8_t> &bits);
    int utran_SI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits);
    int utran_SI_AcquisitionForHO_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    utran_SI_AcquisitionForHO_r9_Enum utran_SI_AcquisitionForHO_r9_Value() const;
    int utran_SI_AcquisitionForHO_r9_SetValue(utran_SI_AcquisitionForHO_r9_Enum value);
    int utran_SI_AcquisitionForHO_r9_SetValue(std::string value);
    std::string utran_SI_AcquisitionForHO_r9_ValueToString(utran_SI_AcquisitionForHO_r9_Enum value) const;
    uint64_t utran_SI_AcquisitionForHO_r9_NumberOfValues() const;
    std::string utran_SI_AcquisitionForHO_r9_ToString(uint32_t indent) const;
    std::string utran_SI_AcquisitionForHO_r9_ToStringNoNewLines() const;
    int utran_SI_AcquisitionForHO_r9_Clear();
    bool utran_SI_AcquisitionForHO_r9_IsPresent() const;
private:
    bool utran_SI_AcquisitionForHO_r9_present;
    utran_SI_AcquisitionForHO_r9_Enum utran_SI_AcquisitionForHO_r9_internal_value;

};

#endif
