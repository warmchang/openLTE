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

#ifndef __SoundingRS_UL_ConfigCommon_H__
#define __SoundingRS_UL_ConfigCommon_H__

#include <array>
#include <cstdint>
#include <vector>

class SoundingRS_UL_ConfigCommon
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
        setup() : srs_BandwidthConfig_present{false}, srs_SubframeConfig_present{false}, ackNackSRS_SimultaneousTransmission_present{false}, srs_MaxUpPts_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // srs-BandwidthConfig
    public:
        enum srs_BandwidthConfig_Enum {
            k_srs_BandwidthConfig_bw0 = 0,
            k_srs_BandwidthConfig_bw1,
            k_srs_BandwidthConfig_bw2,
            k_srs_BandwidthConfig_bw3,
            k_srs_BandwidthConfig_bw4,
            k_srs_BandwidthConfig_bw5,
            k_srs_BandwidthConfig_bw6,
            k_srs_BandwidthConfig_bw7,
        };
        int srs_BandwidthConfig_Pack(std::vector<uint8_t> &bits);
        int srs_BandwidthConfig_Unpack(std::vector<uint8_t> bits);
        int srs_BandwidthConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        srs_BandwidthConfig_Enum srs_BandwidthConfig_Value() const;
        int srs_BandwidthConfig_SetValue(srs_BandwidthConfig_Enum value);
        int srs_BandwidthConfig_SetValue(std::string value);
        std::string srs_BandwidthConfig_ValueToString(srs_BandwidthConfig_Enum value) const;
        uint64_t srs_BandwidthConfig_NumberOfValues() const;
        std::string srs_BandwidthConfig_ToString(uint32_t indent) const;
        std::string srs_BandwidthConfig_ToStringNoNewLines() const;
        int srs_BandwidthConfig_Clear();
        bool srs_BandwidthConfig_IsPresent() const;
    private:
        bool srs_BandwidthConfig_present;
        srs_BandwidthConfig_Enum srs_BandwidthConfig_internal_value;

        // srs-SubframeConfig
    public:
        enum srs_SubframeConfig_Enum {
            k_srs_SubframeConfig_sc0 = 0,
            k_srs_SubframeConfig_sc1,
            k_srs_SubframeConfig_sc2,
            k_srs_SubframeConfig_sc3,
            k_srs_SubframeConfig_sc4,
            k_srs_SubframeConfig_sc5,
            k_srs_SubframeConfig_sc6,
            k_srs_SubframeConfig_sc7,
            k_srs_SubframeConfig_sc8,
            k_srs_SubframeConfig_sc9,
            k_srs_SubframeConfig_sc10,
            k_srs_SubframeConfig_sc11,
            k_srs_SubframeConfig_sc12,
            k_srs_SubframeConfig_sc13,
            k_srs_SubframeConfig_sc14,
            k_srs_SubframeConfig_sc15,
        };
        int srs_SubframeConfig_Pack(std::vector<uint8_t> &bits);
        int srs_SubframeConfig_Unpack(std::vector<uint8_t> bits);
        int srs_SubframeConfig_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        srs_SubframeConfig_Enum srs_SubframeConfig_Value() const;
        int srs_SubframeConfig_SetValue(srs_SubframeConfig_Enum value);
        int srs_SubframeConfig_SetValue(std::string value);
        std::string srs_SubframeConfig_ValueToString(srs_SubframeConfig_Enum value) const;
        uint64_t srs_SubframeConfig_NumberOfValues() const;
        std::string srs_SubframeConfig_ToString(uint32_t indent) const;
        std::string srs_SubframeConfig_ToStringNoNewLines() const;
        int srs_SubframeConfig_Clear();
        bool srs_SubframeConfig_IsPresent() const;
    private:
        bool srs_SubframeConfig_present;
        srs_SubframeConfig_Enum srs_SubframeConfig_internal_value;

        // ackNackSRS-SimultaneousTransmission
    public:
        int ackNackSRS_SimultaneousTransmission_Pack(std::vector<uint8_t> &bits);
        int ackNackSRS_SimultaneousTransmission_Unpack(std::vector<uint8_t> bits);
        int ackNackSRS_SimultaneousTransmission_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool ackNackSRS_SimultaneousTransmission_Value() const;
        int ackNackSRS_SimultaneousTransmission_SetValue(bool value);
        std::string ackNackSRS_SimultaneousTransmission_ToString(uint32_t indent) const;
        std::string ackNackSRS_SimultaneousTransmission_ToStringNoNewLines() const;
        int ackNackSRS_SimultaneousTransmission_Clear();
        bool ackNackSRS_SimultaneousTransmission_IsPresent() const;
    private:
        bool ackNackSRS_SimultaneousTransmission_present;
        bool ackNackSRS_SimultaneousTransmission_internal_value;

        // srs-MaxUpPts
    public:
        enum srs_MaxUpPts_Enum {
            k_srs_MaxUpPts_true = 0,
        };
        int srs_MaxUpPts_Pack(std::vector<uint8_t> &bits);
        int srs_MaxUpPts_Unpack(std::vector<uint8_t> bits);
        int srs_MaxUpPts_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        srs_MaxUpPts_Enum srs_MaxUpPts_Value() const;
        int srs_MaxUpPts_SetValue(srs_MaxUpPts_Enum value);
        int srs_MaxUpPts_SetValue(std::string value);
        std::string srs_MaxUpPts_ValueToString(srs_MaxUpPts_Enum value) const;
        uint64_t srs_MaxUpPts_NumberOfValues() const;
        std::string srs_MaxUpPts_ToString(uint32_t indent) const;
        std::string srs_MaxUpPts_ToStringNoNewLines() const;
        int srs_MaxUpPts_Clear();
        bool srs_MaxUpPts_IsPresent() const;
    private:
        bool srs_MaxUpPts_present;
        srs_MaxUpPts_Enum srs_MaxUpPts_internal_value;

    };

    setup setup_value;

};

#endif
