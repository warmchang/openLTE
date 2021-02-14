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

#ifndef __SystemTimeInfoCDMA2000_H__
#define __SystemTimeInfoCDMA2000_H__

#include <array>
#include <cstdint>
#include <vector>

class SystemTimeInfoCDMA2000
{
public:
    SystemTimeInfoCDMA2000() : cdma_EUTRA_Synchronisation_present{false}, cdma_SystemTime_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cdma-EUTRA-Synchronisation
public:
    int cdma_EUTRA_Synchronisation_Pack(std::vector<uint8_t> &bits);
    int cdma_EUTRA_Synchronisation_Unpack(std::vector<uint8_t> bits);
    int cdma_EUTRA_Synchronisation_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool cdma_EUTRA_Synchronisation_Value() const;
    int cdma_EUTRA_Synchronisation_SetValue(bool value);
    std::string cdma_EUTRA_Synchronisation_ToString(uint32_t indent) const;
    std::string cdma_EUTRA_Synchronisation_ToStringNoNewLines() const;
    int cdma_EUTRA_Synchronisation_Clear();
    bool cdma_EUTRA_Synchronisation_IsPresent() const;
private:
    bool cdma_EUTRA_Synchronisation_present;
    bool cdma_EUTRA_Synchronisation_internal_value;

    // cdma-SystemTime
public:
    enum cdma_SystemTime_Enum {
        k_cdma_SystemTime_synchronousSystemTime = 0,
        k_cdma_SystemTime_asynchronousSystemTime,
    };
    int cdma_SystemTime_Pack(std::vector<uint8_t> &bits);
    int cdma_SystemTime_Unpack(std::vector<uint8_t> bits);
    int cdma_SystemTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    cdma_SystemTime_Enum cdma_SystemTime_Choice() const;
    int cdma_SystemTime_SetChoice(cdma_SystemTime_Enum choice);
    std::string cdma_SystemTime_ChoiceToString(cdma_SystemTime_Enum value) const;
    uint64_t cdma_SystemTime_NumberOfChoices() const;
    std::string cdma_SystemTime_ToString(uint32_t indent) const;
    std::string cdma_SystemTime_ToStringNoNewLines() const;
    int cdma_SystemTime_Clear();
    bool cdma_SystemTime_IsPresent() const;
private:
    bool cdma_SystemTime_present;
    cdma_SystemTime_Enum cdma_SystemTime_internal_choice;

    // synchronousSystemTime
public:
    int cdma_SystemTime_synchronousSystemTime_Pack(std::vector<uint8_t> &bits);
    int cdma_SystemTime_synchronousSystemTime_Unpack(std::vector<uint8_t> bits);
    int cdma_SystemTime_synchronousSystemTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint64_t cdma_SystemTime_synchronousSystemTime_Value() const;
    int cdma_SystemTime_synchronousSystemTime_SetValue(uint64_t value);
    std::string cdma_SystemTime_synchronousSystemTime_ToString(uint32_t indent) const;
    std::string cdma_SystemTime_synchronousSystemTime_ToStringNoNewLines() const;
    int cdma_SystemTime_synchronousSystemTime_Clear();
    bool cdma_SystemTime_synchronousSystemTime_IsPresent() const;
private:
    bool cdma_SystemTime_synchronousSystemTime_present;
    uint64_t cdma_SystemTime_synchronousSystemTime_internal_value;

    // asynchronousSystemTime
public:
    int cdma_SystemTime_asynchronousSystemTime_Pack(std::vector<uint8_t> &bits);
    int cdma_SystemTime_asynchronousSystemTime_Unpack(std::vector<uint8_t> bits);
    int cdma_SystemTime_asynchronousSystemTime_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint64_t cdma_SystemTime_asynchronousSystemTime_Value() const;
    int cdma_SystemTime_asynchronousSystemTime_SetValue(uint64_t value);
    std::string cdma_SystemTime_asynchronousSystemTime_ToString(uint32_t indent) const;
    std::string cdma_SystemTime_asynchronousSystemTime_ToStringNoNewLines() const;
    int cdma_SystemTime_asynchronousSystemTime_Clear();
    bool cdma_SystemTime_asynchronousSystemTime_IsPresent() const;
private:
    bool cdma_SystemTime_asynchronousSystemTime_present;
    uint64_t cdma_SystemTime_asynchronousSystemTime_internal_value;


};

#endif
