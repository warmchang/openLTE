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

#ifndef __SoundingRS_UL_ConfigDedicatedAperiodic_r10_H__
#define __SoundingRS_UL_ConfigDedicatedAperiodic_r10_H__

#include <array>
#include <cstdint>
#include <vector>

class SoundingRS_UL_ConfigDedicatedAperiodic_r10
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
        setup() : srs_AntennaPortAp_r10_present{false}, srs_BandwidthAp_r10_present{false}, srs_HoppingBandwidthAp_r10_present{false}, freqDomainPositionAp_r10_present{false}, transmissionCombAp_r10_present{false}, cyclicShiftAp_r10_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // srs-AntennaPortAp-r10
    public:
        enum srs_AntennaPortAp_r10_Enum {
            k_srs_AntennaPortAp_r10_an1 = 0,
            k_srs_AntennaPortAp_r10_an2,
            k_srs_AntennaPortAp_r10_an4,
            k_srs_AntennaPortAp_r10_spare1,
        };
        int srs_AntennaPortAp_r10_Pack(std::vector<uint8_t> &bits);
        int srs_AntennaPortAp_r10_Unpack(std::vector<uint8_t> bits);
        int srs_AntennaPortAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        srs_AntennaPortAp_r10_Enum srs_AntennaPortAp_r10_Value() const;
        int srs_AntennaPortAp_r10_SetValue(srs_AntennaPortAp_r10_Enum value);
        int srs_AntennaPortAp_r10_SetValue(std::string value);
        std::string srs_AntennaPortAp_r10_ValueToString(srs_AntennaPortAp_r10_Enum value) const;
        uint64_t srs_AntennaPortAp_r10_NumberOfValues() const;
        std::string srs_AntennaPortAp_r10_ToString(uint32_t indent) const;
        std::string srs_AntennaPortAp_r10_ToStringNoNewLines() const;
        int srs_AntennaPortAp_r10_Clear();
        bool srs_AntennaPortAp_r10_IsPresent() const;
    private:
        bool srs_AntennaPortAp_r10_present;
        srs_AntennaPortAp_r10_Enum srs_AntennaPortAp_r10_internal_value;

        // srs-BandwidthAp-r10
    public:
        enum srs_BandwidthAp_r10_Enum {
            k_srs_BandwidthAp_r10_bw0 = 0,
            k_srs_BandwidthAp_r10_bw1,
            k_srs_BandwidthAp_r10_bw2,
            k_srs_BandwidthAp_r10_bw3,
        };
        int srs_BandwidthAp_r10_Pack(std::vector<uint8_t> &bits);
        int srs_BandwidthAp_r10_Unpack(std::vector<uint8_t> bits);
        int srs_BandwidthAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        srs_BandwidthAp_r10_Enum srs_BandwidthAp_r10_Value() const;
        int srs_BandwidthAp_r10_SetValue(srs_BandwidthAp_r10_Enum value);
        int srs_BandwidthAp_r10_SetValue(std::string value);
        std::string srs_BandwidthAp_r10_ValueToString(srs_BandwidthAp_r10_Enum value) const;
        uint64_t srs_BandwidthAp_r10_NumberOfValues() const;
        std::string srs_BandwidthAp_r10_ToString(uint32_t indent) const;
        std::string srs_BandwidthAp_r10_ToStringNoNewLines() const;
        int srs_BandwidthAp_r10_Clear();
        bool srs_BandwidthAp_r10_IsPresent() const;
    private:
        bool srs_BandwidthAp_r10_present;
        srs_BandwidthAp_r10_Enum srs_BandwidthAp_r10_internal_value;

        // srs-HoppingBandwidthAp-r10
    public:
        enum srs_HoppingBandwidthAp_r10_Enum {
            k_srs_HoppingBandwidthAp_r10_hbw0 = 0,
            k_srs_HoppingBandwidthAp_r10_hbw1,
            k_srs_HoppingBandwidthAp_r10_hbw2,
            k_srs_HoppingBandwidthAp_r10_hbw3,
        };
        int srs_HoppingBandwidthAp_r10_Pack(std::vector<uint8_t> &bits);
        int srs_HoppingBandwidthAp_r10_Unpack(std::vector<uint8_t> bits);
        int srs_HoppingBandwidthAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        srs_HoppingBandwidthAp_r10_Enum srs_HoppingBandwidthAp_r10_Value() const;
        int srs_HoppingBandwidthAp_r10_SetValue(srs_HoppingBandwidthAp_r10_Enum value);
        int srs_HoppingBandwidthAp_r10_SetValue(std::string value);
        std::string srs_HoppingBandwidthAp_r10_ValueToString(srs_HoppingBandwidthAp_r10_Enum value) const;
        uint64_t srs_HoppingBandwidthAp_r10_NumberOfValues() const;
        std::string srs_HoppingBandwidthAp_r10_ToString(uint32_t indent) const;
        std::string srs_HoppingBandwidthAp_r10_ToStringNoNewLines() const;
        int srs_HoppingBandwidthAp_r10_Clear();
        bool srs_HoppingBandwidthAp_r10_IsPresent() const;
    private:
        bool srs_HoppingBandwidthAp_r10_present;
        srs_HoppingBandwidthAp_r10_Enum srs_HoppingBandwidthAp_r10_internal_value;

        // freqDomainPositionAp-r10
    public:
        int freqDomainPositionAp_r10_Pack(std::vector<uint8_t> &bits);
        int freqDomainPositionAp_r10_Unpack(std::vector<uint8_t> bits);
        int freqDomainPositionAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t freqDomainPositionAp_r10_Value() const;
        int freqDomainPositionAp_r10_SetValue(int64_t value);
        std::string freqDomainPositionAp_r10_ToString(uint32_t indent) const;
        std::string freqDomainPositionAp_r10_ToStringNoNewLines() const;
        int freqDomainPositionAp_r10_Clear();
        bool freqDomainPositionAp_r10_IsPresent() const;
    private:
        bool freqDomainPositionAp_r10_present;
        int64_t freqDomainPositionAp_r10_internal_value;

        // transmissionCombAp-r10
    public:
        int transmissionCombAp_r10_Pack(std::vector<uint8_t> &bits);
        int transmissionCombAp_r10_Unpack(std::vector<uint8_t> bits);
        int transmissionCombAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t transmissionCombAp_r10_Value() const;
        int transmissionCombAp_r10_SetValue(int64_t value);
        std::string transmissionCombAp_r10_ToString(uint32_t indent) const;
        std::string transmissionCombAp_r10_ToStringNoNewLines() const;
        int transmissionCombAp_r10_Clear();
        bool transmissionCombAp_r10_IsPresent() const;
    private:
        bool transmissionCombAp_r10_present;
        int64_t transmissionCombAp_r10_internal_value;

        // cyclicShiftAp-r10
    public:
        enum cyclicShiftAp_r10_Enum {
            k_cyclicShiftAp_r10_cs0 = 0,
            k_cyclicShiftAp_r10_cs1,
            k_cyclicShiftAp_r10_cs2,
            k_cyclicShiftAp_r10_cs3,
            k_cyclicShiftAp_r10_cs4,
            k_cyclicShiftAp_r10_cs5,
            k_cyclicShiftAp_r10_cs6,
            k_cyclicShiftAp_r10_cs7,
        };
        int cyclicShiftAp_r10_Pack(std::vector<uint8_t> &bits);
        int cyclicShiftAp_r10_Unpack(std::vector<uint8_t> bits);
        int cyclicShiftAp_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        cyclicShiftAp_r10_Enum cyclicShiftAp_r10_Value() const;
        int cyclicShiftAp_r10_SetValue(cyclicShiftAp_r10_Enum value);
        int cyclicShiftAp_r10_SetValue(std::string value);
        std::string cyclicShiftAp_r10_ValueToString(cyclicShiftAp_r10_Enum value) const;
        uint64_t cyclicShiftAp_r10_NumberOfValues() const;
        std::string cyclicShiftAp_r10_ToString(uint32_t indent) const;
        std::string cyclicShiftAp_r10_ToStringNoNewLines() const;
        int cyclicShiftAp_r10_Clear();
        bool cyclicShiftAp_r10_IsPresent() const;
    private:
        bool cyclicShiftAp_r10_present;
        cyclicShiftAp_r10_Enum cyclicShiftAp_r10_internal_value;

    };

    setup setup_value;

};

#endif
