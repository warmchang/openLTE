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

#ifndef __SoundingRS_UL_ConfigDedicated_H__
#define __SoundingRS_UL_ConfigDedicated_H__

#include <array>
#include <cstdint>
#include <vector>

class SoundingRS_UL_ConfigDedicated
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
        setup() : srs_Bandwidth_present{false}, srs_HoppingBandwidth_present{false}, freqDomainPosition_present{false}, duration_present{false}, srs_ConfigIndex_present{false}, transmissionComb_present{false}, cyclicShift_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // srs-Bandwidth
    public:
        enum srs_Bandwidth_Enum {
            k_srs_Bandwidth_bw0 = 0,
            k_srs_Bandwidth_bw1,
            k_srs_Bandwidth_bw2,
            k_srs_Bandwidth_bw3,
        };
        int srs_Bandwidth_Pack(std::vector<uint8_t> &bits);
        int srs_Bandwidth_Unpack(std::vector<uint8_t> bits);
        int srs_Bandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        srs_Bandwidth_Enum srs_Bandwidth_Value() const;
        int srs_Bandwidth_SetValue(srs_Bandwidth_Enum value);
        int srs_Bandwidth_SetValue(std::string value);
        std::string srs_Bandwidth_ValueToString(srs_Bandwidth_Enum value) const;
        uint64_t srs_Bandwidth_NumberOfValues() const;
        std::string srs_Bandwidth_ToString(uint32_t indent) const;
        std::string srs_Bandwidth_ToStringNoNewLines() const;
        int srs_Bandwidth_Clear();
        bool srs_Bandwidth_IsPresent() const;
    private:
        bool srs_Bandwidth_present;
        srs_Bandwidth_Enum srs_Bandwidth_internal_value;

        // srs-HoppingBandwidth
    public:
        enum srs_HoppingBandwidth_Enum {
            k_srs_HoppingBandwidth_hbw0 = 0,
            k_srs_HoppingBandwidth_hbw1,
            k_srs_HoppingBandwidth_hbw2,
            k_srs_HoppingBandwidth_hbw3,
        };
        int srs_HoppingBandwidth_Pack(std::vector<uint8_t> &bits);
        int srs_HoppingBandwidth_Unpack(std::vector<uint8_t> bits);
        int srs_HoppingBandwidth_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        srs_HoppingBandwidth_Enum srs_HoppingBandwidth_Value() const;
        int srs_HoppingBandwidth_SetValue(srs_HoppingBandwidth_Enum value);
        int srs_HoppingBandwidth_SetValue(std::string value);
        std::string srs_HoppingBandwidth_ValueToString(srs_HoppingBandwidth_Enum value) const;
        uint64_t srs_HoppingBandwidth_NumberOfValues() const;
        std::string srs_HoppingBandwidth_ToString(uint32_t indent) const;
        std::string srs_HoppingBandwidth_ToStringNoNewLines() const;
        int srs_HoppingBandwidth_Clear();
        bool srs_HoppingBandwidth_IsPresent() const;
    private:
        bool srs_HoppingBandwidth_present;
        srs_HoppingBandwidth_Enum srs_HoppingBandwidth_internal_value;

        // freqDomainPosition
    public:
        int freqDomainPosition_Pack(std::vector<uint8_t> &bits);
        int freqDomainPosition_Unpack(std::vector<uint8_t> bits);
        int freqDomainPosition_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t freqDomainPosition_Value() const;
        int freqDomainPosition_SetValue(int64_t value);
        std::string freqDomainPosition_ToString(uint32_t indent) const;
        std::string freqDomainPosition_ToStringNoNewLines() const;
        int freqDomainPosition_Clear();
        bool freqDomainPosition_IsPresent() const;
    private:
        bool freqDomainPosition_present;
        int64_t freqDomainPosition_internal_value;

        // duration
    public:
        int duration_Pack(std::vector<uint8_t> &bits);
        int duration_Unpack(std::vector<uint8_t> bits);
        int duration_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool duration_Value() const;
        int duration_SetValue(bool value);
        std::string duration_ToString(uint32_t indent) const;
        std::string duration_ToStringNoNewLines() const;
        int duration_Clear();
        bool duration_IsPresent() const;
    private:
        bool duration_present;
        bool duration_internal_value;

        // srs-ConfigIndex
    public:
        int srs_ConfigIndex_Pack(std::vector<uint8_t> &bits);
        int srs_ConfigIndex_Unpack(std::vector<uint8_t> bits);
        int srs_ConfigIndex_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t srs_ConfigIndex_Value() const;
        int srs_ConfigIndex_SetValue(int64_t value);
        std::string srs_ConfigIndex_ToString(uint32_t indent) const;
        std::string srs_ConfigIndex_ToStringNoNewLines() const;
        int srs_ConfigIndex_Clear();
        bool srs_ConfigIndex_IsPresent() const;
    private:
        bool srs_ConfigIndex_present;
        int64_t srs_ConfigIndex_internal_value;

        // transmissionComb
    public:
        int transmissionComb_Pack(std::vector<uint8_t> &bits);
        int transmissionComb_Unpack(std::vector<uint8_t> bits);
        int transmissionComb_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t transmissionComb_Value() const;
        int transmissionComb_SetValue(int64_t value);
        std::string transmissionComb_ToString(uint32_t indent) const;
        std::string transmissionComb_ToStringNoNewLines() const;
        int transmissionComb_Clear();
        bool transmissionComb_IsPresent() const;
    private:
        bool transmissionComb_present;
        int64_t transmissionComb_internal_value;

        // cyclicShift
    public:
        enum cyclicShift_Enum {
            k_cyclicShift_cs0 = 0,
            k_cyclicShift_cs1,
            k_cyclicShift_cs2,
            k_cyclicShift_cs3,
            k_cyclicShift_cs4,
            k_cyclicShift_cs5,
            k_cyclicShift_cs6,
            k_cyclicShift_cs7,
        };
        int cyclicShift_Pack(std::vector<uint8_t> &bits);
        int cyclicShift_Unpack(std::vector<uint8_t> bits);
        int cyclicShift_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        cyclicShift_Enum cyclicShift_Value() const;
        int cyclicShift_SetValue(cyclicShift_Enum value);
        int cyclicShift_SetValue(std::string value);
        std::string cyclicShift_ValueToString(cyclicShift_Enum value) const;
        uint64_t cyclicShift_NumberOfValues() const;
        std::string cyclicShift_ToString(uint32_t indent) const;
        std::string cyclicShift_ToStringNoNewLines() const;
        int cyclicShift_Clear();
        bool cyclicShift_IsPresent() const;
    private:
        bool cyclicShift_present;
        cyclicShift_Enum cyclicShift_internal_value;

    };

    setup setup_value;

};

#endif
