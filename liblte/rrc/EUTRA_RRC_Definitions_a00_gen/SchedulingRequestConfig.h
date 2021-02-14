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

#ifndef __SchedulingRequestConfig_H__
#define __SchedulingRequestConfig_H__

#include <array>
#include <cstdint>
#include <vector>

class SchedulingRequestConfig
{
public:
    enum Enum {
        k_release = 0,
        k_setup,
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

    // release
public:
    int release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool release_IsPresent() const {return true;};
    std::string release_ToString(uint32_t indent) {return "";};
    std::string release_ToStringNoNewLines() {return "";};

    // setup
public:
    class setup
    {
    public:
        setup() : sr_PUCCH_ResourceIndex_present{false}, sr_ConfigIndex_present{false}, dsr_TransMax_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // sr-PUCCH-ResourceIndex
    public:
        int sr_PUCCH_ResourceIndex_Pack(std::vector<uint8_t> &bits);
        int sr_PUCCH_ResourceIndex_Unpack(std::vector<uint8_t> bits);
        int sr_PUCCH_ResourceIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t sr_PUCCH_ResourceIndex_Value() const;
        int sr_PUCCH_ResourceIndex_SetValue(int64_t value);
        std::string sr_PUCCH_ResourceIndex_ToString(uint32_t indent) const;
        std::string sr_PUCCH_ResourceIndex_ToStringNoNewLines() const;
        int sr_PUCCH_ResourceIndex_Clear();
        bool sr_PUCCH_ResourceIndex_IsPresent() const;
    private:
        bool sr_PUCCH_ResourceIndex_present;
        int64_t sr_PUCCH_ResourceIndex_internal_value;

        // sr-ConfigIndex
    public:
        int sr_ConfigIndex_Pack(std::vector<uint8_t> &bits);
        int sr_ConfigIndex_Unpack(std::vector<uint8_t> bits);
        int sr_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t sr_ConfigIndex_Value() const;
        int sr_ConfigIndex_SetValue(int64_t value);
        std::string sr_ConfigIndex_ToString(uint32_t indent) const;
        std::string sr_ConfigIndex_ToStringNoNewLines() const;
        int sr_ConfigIndex_Clear();
        bool sr_ConfigIndex_IsPresent() const;
    private:
        bool sr_ConfigIndex_present;
        int64_t sr_ConfigIndex_internal_value;

        // dsr-TransMax
    public:
        enum dsr_TransMax_Enum {
            k_dsr_TransMax_n4 = 0,
            k_dsr_TransMax_n8,
            k_dsr_TransMax_n16,
            k_dsr_TransMax_n32,
            k_dsr_TransMax_n64,
            k_dsr_TransMax_spare3,
            k_dsr_TransMax_spare2,
            k_dsr_TransMax_spare1,
        };
        int dsr_TransMax_Pack(std::vector<uint8_t> &bits);
        int dsr_TransMax_Unpack(std::vector<uint8_t> bits);
        int dsr_TransMax_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        dsr_TransMax_Enum dsr_TransMax_Value() const;
        int dsr_TransMax_SetValue(dsr_TransMax_Enum value);
        int dsr_TransMax_SetValue(std::string value);
        std::string dsr_TransMax_ValueToString(dsr_TransMax_Enum value) const;
        uint64_t dsr_TransMax_NumberOfValues() const;
        std::string dsr_TransMax_ToString(uint32_t indent) const;
        std::string dsr_TransMax_ToStringNoNewLines() const;
        int dsr_TransMax_Clear();
        bool dsr_TransMax_IsPresent() const;
    private:
        bool dsr_TransMax_present;
        dsr_TransMax_Enum dsr_TransMax_internal_value;

    };

    setup setup_value;

};

#endif
