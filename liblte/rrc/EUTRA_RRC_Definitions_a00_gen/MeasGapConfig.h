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

#ifndef __MeasGapConfig_H__
#define __MeasGapConfig_H__

#include <array>
#include <cstdint>
#include <vector>

class MeasGapConfig
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
        setup() : gapOffset_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // gapOffset
    public:
        enum gapOffset_Enum {
            k_gapOffset_gp0 = 0,
            k_gapOffset_gp1,
        };
        int gapOffset_Pack(std::vector<uint8_t> &bits);
        int gapOffset_Unpack(std::vector<uint8_t> bits);
        int gapOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        gapOffset_Enum gapOffset_Choice() const;
        int gapOffset_SetChoice(gapOffset_Enum choice);
        std::string gapOffset_ChoiceToString(gapOffset_Enum value) const;
        uint64_t gapOffset_NumberOfChoices() const;
        std::string gapOffset_ToString(uint32_t indent) const;
        std::string gapOffset_ToStringNoNewLines() const;
        int gapOffset_Clear();
        bool gapOffset_IsPresent() const;
    private:
        bool gapOffset_present;
        gapOffset_Enum gapOffset_internal_choice;

        // gp0
    public:
        int gapOffset_gp0_Pack(std::vector<uint8_t> &bits);
        int gapOffset_gp0_Unpack(std::vector<uint8_t> bits);
        int gapOffset_gp0_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t gapOffset_gp0_Value() const;
        int gapOffset_gp0_SetValue(int64_t value);
        std::string gapOffset_gp0_ToString(uint32_t indent) const;
        std::string gapOffset_gp0_ToStringNoNewLines() const;
        int gapOffset_gp0_Clear();
        bool gapOffset_gp0_IsPresent() const;
    private:
        bool gapOffset_gp0_present;
        int64_t gapOffset_gp0_internal_value;

        // gp1
    public:
        int gapOffset_gp1_Pack(std::vector<uint8_t> &bits);
        int gapOffset_gp1_Unpack(std::vector<uint8_t> bits);
        int gapOffset_gp1_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t gapOffset_gp1_Value() const;
        int gapOffset_gp1_SetValue(int64_t value);
        std::string gapOffset_gp1_ToString(uint32_t indent) const;
        std::string gapOffset_gp1_ToStringNoNewLines() const;
        int gapOffset_gp1_Clear();
        bool gapOffset_gp1_IsPresent() const;
    private:
        bool gapOffset_gp1_present;
        int64_t gapOffset_gp1_internal_value;


    };

    setup setup_value;

};

#endif
