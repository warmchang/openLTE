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

#ifndef __UEInformationResponse_r9_IEs_H__
#define __UEInformationResponse_r9_IEs_H__

#include "RLF_Report_r9.h"
#include "UEInformationResponse_v930_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class UEInformationResponse_r9_IEs
{
public:
    UEInformationResponse_r9_IEs() : rlfReport_r9_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // rach-Report-r9
public:
    class rach_Report_r9
    {
    public:
        rach_Report_r9() : present{false}, numberOfPreamblesSent_r9_present{false}, contentionDetected_r9_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;
        int Set();
        int SetPresence(bool is_present);
        int Clear();
        bool IsPresent() const;
    private:
        bool present;

        // numberOfPreamblesSent-r9
    public:
        int numberOfPreamblesSent_r9_Pack(std::vector<uint8_t> &bits);
        int numberOfPreamblesSent_r9_Unpack(std::vector<uint8_t> bits);
        int numberOfPreamblesSent_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t numberOfPreamblesSent_r9_Value() const;
        int numberOfPreamblesSent_r9_SetValue(int64_t value);
        std::string numberOfPreamblesSent_r9_ToString(uint32_t indent) const;
        std::string numberOfPreamblesSent_r9_ToStringNoNewLines() const;
        int numberOfPreamblesSent_r9_Clear();
        bool numberOfPreamblesSent_r9_IsPresent() const;
    private:
        bool numberOfPreamblesSent_r9_present;
        int64_t numberOfPreamblesSent_r9_internal_value;

        // contentionDetected-r9
    public:
        int contentionDetected_r9_Pack(std::vector<uint8_t> &bits);
        int contentionDetected_r9_Unpack(std::vector<uint8_t> bits);
        int contentionDetected_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool contentionDetected_r9_Value() const;
        int contentionDetected_r9_SetValue(bool value);
        std::string contentionDetected_r9_ToString(uint32_t indent) const;
        std::string contentionDetected_r9_ToStringNoNewLines() const;
        int contentionDetected_r9_Clear();
        bool contentionDetected_r9_IsPresent() const;
    private:
        bool contentionDetected_r9_present;
        bool contentionDetected_r9_internal_value;

    };

    rach_Report_r9 rach_Report_r9_value;

    // rlfReport-r9
public:
    RLF_Report_r9* rlfReport_r9_Set();
    int rlfReport_r9_Set(RLF_Report_r9 &value);
    const RLF_Report_r9& rlfReport_r9_Get() const;
    std::string rlfReport_r9_ToString(uint32_t indent) const;
    std::string rlfReport_r9_ToStringNoNewLines() const;
    int rlfReport_r9_Clear();
    bool rlfReport_r9_IsPresent() const;
private:
    bool rlfReport_r9_present;
    RLF_Report_r9 rlfReport_r9;

    // nonCriticalExtension
public:
    UEInformationResponse_v930_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(UEInformationResponse_v930_IEs &value);
    const UEInformationResponse_v930_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    UEInformationResponse_v930_IEs nonCriticalExtension;

};

#endif
