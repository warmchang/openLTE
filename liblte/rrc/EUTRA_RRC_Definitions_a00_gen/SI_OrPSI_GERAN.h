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

#ifndef __SI_OrPSI_GERAN_H__
#define __SI_OrPSI_GERAN_H__

#include "SystemInfoListGERAN.h"
#include "SystemInfoListGERAN.h"

#include <array>
#include <cstdint>
#include <vector>

class SI_OrPSI_GERAN
{
public:
    enum Enum {
        k_si = 0,
        k_psi,
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

    // si
public:
    SystemInfoListGERAN* si_Set();
    int si_Set(SystemInfoListGERAN &value);
    const SystemInfoListGERAN& si_Get() const;
    std::string si_ToString(uint32_t indent) const;
    std::string si_ToStringNoNewLines() const;
    int si_Clear();
    bool si_IsPresent() const;
private:
    bool si_present;
    SystemInfoListGERAN si;

    // psi
public:
    SystemInfoListGERAN* psi_Set();
    int psi_Set(SystemInfoListGERAN &value);
    const SystemInfoListGERAN& psi_Get() const;
    std::string psi_ToString(uint32_t indent) const;
    std::string psi_ToStringNoNewLines() const;
    int psi_Clear();
    bool psi_IsPresent() const;
private:
    bool psi_present;
    SystemInfoListGERAN psi;

};

#endif
