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

#ifndef __MeasResultForECID_r9_H__
#define __MeasResultForECID_r9_H__

#include <array>
#include <cstdint>
#include <vector>

class MeasResultForECID_r9
{
public:
    MeasResultForECID_r9() : ue_RxTxTimeDiffResult_r9_present{false}, currentSFN_r9_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ue-RxTxTimeDiffResult-r9
public:
    int ue_RxTxTimeDiffResult_r9_Pack(std::vector<uint8_t> &bits);
    int ue_RxTxTimeDiffResult_r9_Unpack(std::vector<uint8_t> bits);
    int ue_RxTxTimeDiffResult_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ue_RxTxTimeDiffResult_r9_Value() const;
    int ue_RxTxTimeDiffResult_r9_SetValue(int64_t value);
    std::string ue_RxTxTimeDiffResult_r9_ToString(uint32_t indent) const;
    std::string ue_RxTxTimeDiffResult_r9_ToStringNoNewLines() const;
    int ue_RxTxTimeDiffResult_r9_Clear();
    bool ue_RxTxTimeDiffResult_r9_IsPresent() const;
private:
    bool ue_RxTxTimeDiffResult_r9_present;
    int64_t ue_RxTxTimeDiffResult_r9_internal_value;

    // currentSFN-r9
public:
    int currentSFN_r9_Pack(std::vector<uint8_t> &bits);
    int currentSFN_r9_Unpack(std::vector<uint8_t> bits);
    int currentSFN_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t currentSFN_r9_Value() const;
    int currentSFN_r9_SetValue(uint16_t value);
    std::string currentSFN_r9_ToString(uint32_t indent) const;
    std::string currentSFN_r9_ToStringNoNewLines() const;
    int currentSFN_r9_Clear();
    bool currentSFN_r9_IsPresent() const;
private:
    bool currentSFN_r9_present;
    uint16_t currentSFN_r9_internal_value;

};

#endif
