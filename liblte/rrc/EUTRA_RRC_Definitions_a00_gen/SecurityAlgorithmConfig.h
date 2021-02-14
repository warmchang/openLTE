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

#ifndef __SecurityAlgorithmConfig_H__
#define __SecurityAlgorithmConfig_H__

#include <array>
#include <cstdint>
#include <vector>

class SecurityAlgorithmConfig
{
public:
    SecurityAlgorithmConfig() : cipheringAlgorithm_present{false}, integrityProtAlgorithm_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cipheringAlgorithm
public:
    enum cipheringAlgorithm_Enum {
        k_cipheringAlgorithm_eea0 = 0,
        k_cipheringAlgorithm_eea1,
        k_cipheringAlgorithm_eea2,
        k_cipheringAlgorithm_spare5,
        k_cipheringAlgorithm_spare4,
        k_cipheringAlgorithm_spare3,
        k_cipheringAlgorithm_spare2,
        k_cipheringAlgorithm_spare1,
    };
    int cipheringAlgorithm_Pack(std::vector<uint8_t> &bits);
    int cipheringAlgorithm_Unpack(std::vector<uint8_t> bits);
    int cipheringAlgorithm_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cipheringAlgorithm_Enum cipheringAlgorithm_Value() const;
    int cipheringAlgorithm_SetValue(cipheringAlgorithm_Enum value);
    int cipheringAlgorithm_SetValue(std::string value);
    std::string cipheringAlgorithm_ValueToString(cipheringAlgorithm_Enum value) const;
    uint64_t cipheringAlgorithm_NumberOfValues() const;
    std::string cipheringAlgorithm_ToString(uint32_t indent) const;
    std::string cipheringAlgorithm_ToStringNoNewLines() const;
    int cipheringAlgorithm_Clear();
    bool cipheringAlgorithm_IsPresent() const;
private:
    bool cipheringAlgorithm_present;
    cipheringAlgorithm_Enum cipheringAlgorithm_internal_value;

    // integrityProtAlgorithm
public:
    enum integrityProtAlgorithm_Enum {
        k_integrityProtAlgorithm_eia0_v920 = 0,
        k_integrityProtAlgorithm_eia1,
        k_integrityProtAlgorithm_eia2,
        k_integrityProtAlgorithm_spare5,
        k_integrityProtAlgorithm_spare4,
        k_integrityProtAlgorithm_spare3,
        k_integrityProtAlgorithm_spare2,
        k_integrityProtAlgorithm_spare1,
    };
    int integrityProtAlgorithm_Pack(std::vector<uint8_t> &bits);
    int integrityProtAlgorithm_Unpack(std::vector<uint8_t> bits);
    int integrityProtAlgorithm_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    integrityProtAlgorithm_Enum integrityProtAlgorithm_Value() const;
    int integrityProtAlgorithm_SetValue(integrityProtAlgorithm_Enum value);
    int integrityProtAlgorithm_SetValue(std::string value);
    std::string integrityProtAlgorithm_ValueToString(integrityProtAlgorithm_Enum value) const;
    uint64_t integrityProtAlgorithm_NumberOfValues() const;
    std::string integrityProtAlgorithm_ToString(uint32_t indent) const;
    std::string integrityProtAlgorithm_ToStringNoNewLines() const;
    int integrityProtAlgorithm_Clear();
    bool integrityProtAlgorithm_IsPresent() const;
private:
    bool integrityProtAlgorithm_present;
    integrityProtAlgorithm_Enum integrityProtAlgorithm_internal_value;

};

#endif
