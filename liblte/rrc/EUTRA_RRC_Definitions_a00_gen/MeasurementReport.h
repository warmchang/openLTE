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

#ifndef __MeasurementReport_H__
#define __MeasurementReport_H__

#include "MeasurementReport_r8_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasurementReport
{
public:
    MeasurementReport() : criticalExtensions_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // criticalExtensions
public:
    enum criticalExtensions_Enum {
        k_criticalExtensions_c1 = 0,
        k_criticalExtensions_criticalExtensionsFuture,
    };
    int criticalExtensions_Pack(std::vector<uint8_t> &bits);
    int criticalExtensions_Unpack(std::vector<uint8_t> bits);
    int criticalExtensions_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    criticalExtensions_Enum criticalExtensions_Choice() const;
    int criticalExtensions_SetChoice(criticalExtensions_Enum choice);
    std::string criticalExtensions_ChoiceToString(criticalExtensions_Enum value) const;
    uint64_t criticalExtensions_NumberOfChoices() const;
    std::string criticalExtensions_ToString(uint32_t indent) const;
    std::string criticalExtensions_ToStringNoNewLines() const;
    int criticalExtensions_Clear();
    bool criticalExtensions_IsPresent() const;
private:
    bool criticalExtensions_present;
    criticalExtensions_Enum criticalExtensions_internal_choice;

    // c1
public:
    enum criticalExtensions_c1_Enum {
        k_criticalExtensions_c1_measurementReport_r8 = 0,
        k_criticalExtensions_c1_spare7,
        k_criticalExtensions_c1_spare6,
        k_criticalExtensions_c1_spare5,
        k_criticalExtensions_c1_spare4,
        k_criticalExtensions_c1_spare3,
        k_criticalExtensions_c1_spare2,
        k_criticalExtensions_c1_spare1,
    };
    int criticalExtensions_c1_Pack(std::vector<uint8_t> &bits);
    int criticalExtensions_c1_Unpack(std::vector<uint8_t> bits);
    int criticalExtensions_c1_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    criticalExtensions_c1_Enum criticalExtensions_c1_Choice() const;
    int criticalExtensions_c1_SetChoice(criticalExtensions_c1_Enum choice);
    std::string criticalExtensions_c1_ChoiceToString(criticalExtensions_c1_Enum value) const;
    uint64_t criticalExtensions_c1_NumberOfChoices() const;
    std::string criticalExtensions_c1_ToString(uint32_t indent) const;
    std::string criticalExtensions_c1_ToStringNoNewLines() const;
    int criticalExtensions_c1_Clear();
    bool criticalExtensions_c1_IsPresent() const;
private:
    bool criticalExtensions_c1_present;
    criticalExtensions_c1_Enum criticalExtensions_c1_internal_choice;

    // measurementReport-r8
public:
    MeasurementReport_r8_IEs* criticalExtensions_c1_measurementReport_r8_Set();
    int criticalExtensions_c1_measurementReport_r8_Set(MeasurementReport_r8_IEs &value);
    const MeasurementReport_r8_IEs& criticalExtensions_c1_measurementReport_r8_Get() const;
    std::string criticalExtensions_c1_measurementReport_r8_ToString(uint32_t indent) const;
    std::string criticalExtensions_c1_measurementReport_r8_ToStringNoNewLines() const;
    int criticalExtensions_c1_measurementReport_r8_Clear();
    bool criticalExtensions_c1_measurementReport_r8_IsPresent() const;
private:
    bool criticalExtensions_c1_measurementReport_r8_present;
    MeasurementReport_r8_IEs criticalExtensions_c1_measurementReport_r8;

    // spare7
public:
    int criticalExtensions_c1_spare7_Pack(std::vector<uint8_t> &bits) {return 0;};
    int criticalExtensions_c1_spare7_Unpack(std::vector<uint8_t> bits) {return 0;};
    int criticalExtensions_c1_spare7_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool criticalExtensions_c1_spare7_IsPresent() const {return true;};
    std::string criticalExtensions_c1_spare7_ToString(uint32_t indent) {return "";};
    std::string criticalExtensions_c1_spare7_ToStringNoNewLines() {return "";};

    // spare6
public:
    int criticalExtensions_c1_spare6_Pack(std::vector<uint8_t> &bits) {return 0;};
    int criticalExtensions_c1_spare6_Unpack(std::vector<uint8_t> bits) {return 0;};
    int criticalExtensions_c1_spare6_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool criticalExtensions_c1_spare6_IsPresent() const {return true;};
    std::string criticalExtensions_c1_spare6_ToString(uint32_t indent) {return "";};
    std::string criticalExtensions_c1_spare6_ToStringNoNewLines() {return "";};

    // spare5
public:
    int criticalExtensions_c1_spare5_Pack(std::vector<uint8_t> &bits) {return 0;};
    int criticalExtensions_c1_spare5_Unpack(std::vector<uint8_t> bits) {return 0;};
    int criticalExtensions_c1_spare5_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool criticalExtensions_c1_spare5_IsPresent() const {return true;};
    std::string criticalExtensions_c1_spare5_ToString(uint32_t indent) {return "";};
    std::string criticalExtensions_c1_spare5_ToStringNoNewLines() {return "";};

    // spare4
public:
    int criticalExtensions_c1_spare4_Pack(std::vector<uint8_t> &bits) {return 0;};
    int criticalExtensions_c1_spare4_Unpack(std::vector<uint8_t> bits) {return 0;};
    int criticalExtensions_c1_spare4_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool criticalExtensions_c1_spare4_IsPresent() const {return true;};
    std::string criticalExtensions_c1_spare4_ToString(uint32_t indent) {return "";};
    std::string criticalExtensions_c1_spare4_ToStringNoNewLines() {return "";};

    // spare3
public:
    int criticalExtensions_c1_spare3_Pack(std::vector<uint8_t> &bits) {return 0;};
    int criticalExtensions_c1_spare3_Unpack(std::vector<uint8_t> bits) {return 0;};
    int criticalExtensions_c1_spare3_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool criticalExtensions_c1_spare3_IsPresent() const {return true;};
    std::string criticalExtensions_c1_spare3_ToString(uint32_t indent) {return "";};
    std::string criticalExtensions_c1_spare3_ToStringNoNewLines() {return "";};

    // spare2
public:
    int criticalExtensions_c1_spare2_Pack(std::vector<uint8_t> &bits) {return 0;};
    int criticalExtensions_c1_spare2_Unpack(std::vector<uint8_t> bits) {return 0;};
    int criticalExtensions_c1_spare2_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool criticalExtensions_c1_spare2_IsPresent() const {return true;};
    std::string criticalExtensions_c1_spare2_ToString(uint32_t indent) {return "";};
    std::string criticalExtensions_c1_spare2_ToStringNoNewLines() {return "";};

    // spare1
public:
    int criticalExtensions_c1_spare1_Pack(std::vector<uint8_t> &bits) {return 0;};
    int criticalExtensions_c1_spare1_Unpack(std::vector<uint8_t> bits) {return 0;};
    int criticalExtensions_c1_spare1_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool criticalExtensions_c1_spare1_IsPresent() const {return true;};
    std::string criticalExtensions_c1_spare1_ToString(uint32_t indent) {return "";};
    std::string criticalExtensions_c1_spare1_ToStringNoNewLines() {return "";};


    // criticalExtensionsFuture


};

#endif
