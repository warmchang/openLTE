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

#ifndef __CSI_RS_Config_r10_H__
#define __CSI_RS_Config_r10_H__

#include <array>
#include <cstdint>
#include <vector>

class CSI_RS_Config_r10
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
        setup() : csi_RS_Ports_r10_present{false}, locationIndex_r10_present{false}, csi_RS_SubframeConfig_r10_present{false}, rho_C_r10_present{false}, csi_RS_WithZeroTransmissionPower_r10_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // csi-RS-Ports-r10
    public:
        enum csi_RS_Ports_r10_Enum {
            k_csi_RS_Ports_r10_an1 = 0,
            k_csi_RS_Ports_r10_an2,
            k_csi_RS_Ports_r10_an4,
            k_csi_RS_Ports_r10_an8,
        };
        int csi_RS_Ports_r10_Pack(std::vector<uint8_t> &bits);
        int csi_RS_Ports_r10_Unpack(std::vector<uint8_t> bits);
        int csi_RS_Ports_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        csi_RS_Ports_r10_Enum csi_RS_Ports_r10_Value() const;
        int csi_RS_Ports_r10_SetValue(csi_RS_Ports_r10_Enum value);
        int csi_RS_Ports_r10_SetValue(std::string value);
        std::string csi_RS_Ports_r10_ValueToString(csi_RS_Ports_r10_Enum value) const;
        uint64_t csi_RS_Ports_r10_NumberOfValues() const;
        std::string csi_RS_Ports_r10_ToString(uint32_t indent) const;
        std::string csi_RS_Ports_r10_ToStringNoNewLines() const;
        int csi_RS_Ports_r10_Clear();
        bool csi_RS_Ports_r10_IsPresent() const;
    private:
        bool csi_RS_Ports_r10_present;
        csi_RS_Ports_r10_Enum csi_RS_Ports_r10_internal_value;

        // locationIndex-r10
    public:
        int locationIndex_r10_Pack(std::vector<uint8_t> &bits);
        int locationIndex_r10_Unpack(std::vector<uint8_t> bits);
        int locationIndex_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t locationIndex_r10_Value() const;
        int locationIndex_r10_SetValue(int64_t value);
        std::string locationIndex_r10_ToString(uint32_t indent) const;
        std::string locationIndex_r10_ToStringNoNewLines() const;
        int locationIndex_r10_Clear();
        bool locationIndex_r10_IsPresent() const;
    private:
        bool locationIndex_r10_present;
        int64_t locationIndex_r10_internal_value;

        // csi-RS-SubframeConfig-r10
    public:
        int csi_RS_SubframeConfig_r10_Pack(std::vector<uint8_t> &bits);
        int csi_RS_SubframeConfig_r10_Unpack(std::vector<uint8_t> bits);
        int csi_RS_SubframeConfig_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t csi_RS_SubframeConfig_r10_Value() const;
        int csi_RS_SubframeConfig_r10_SetValue(int64_t value);
        std::string csi_RS_SubframeConfig_r10_ToString(uint32_t indent) const;
        std::string csi_RS_SubframeConfig_r10_ToStringNoNewLines() const;
        int csi_RS_SubframeConfig_r10_Clear();
        bool csi_RS_SubframeConfig_r10_IsPresent() const;
    private:
        bool csi_RS_SubframeConfig_r10_present;
        int64_t csi_RS_SubframeConfig_r10_internal_value;

        // rho-C-r10
    public:
        int rho_C_r10_Pack(std::vector<uint8_t> &bits);
        int rho_C_r10_Unpack(std::vector<uint8_t> bits);
        int rho_C_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint16_t rho_C_r10_Value() const;
        int rho_C_r10_SetValue(uint16_t value);
        std::string rho_C_r10_ToString(uint32_t indent) const;
        std::string rho_C_r10_ToStringNoNewLines() const;
        int rho_C_r10_Clear();
        bool rho_C_r10_IsPresent() const;
    private:
        bool rho_C_r10_present;
        uint16_t rho_C_r10_internal_value;

        // csi-RS-WithZeroTransmissionPower-r10
    public:
        int csi_RS_WithZeroTransmissionPower_r10_Pack(std::vector<uint8_t> &bits);
        int csi_RS_WithZeroTransmissionPower_r10_Unpack(std::vector<uint8_t> bits);
        int csi_RS_WithZeroTransmissionPower_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint16_t csi_RS_WithZeroTransmissionPower_r10_Value() const;
        int csi_RS_WithZeroTransmissionPower_r10_SetValue(uint16_t value);
        std::string csi_RS_WithZeroTransmissionPower_r10_ToString(uint32_t indent) const;
        std::string csi_RS_WithZeroTransmissionPower_r10_ToStringNoNewLines() const;
        int csi_RS_WithZeroTransmissionPower_r10_Clear();
        bool csi_RS_WithZeroTransmissionPower_r10_IsPresent() const;
    private:
        bool csi_RS_WithZeroTransmissionPower_r10_present;
        uint16_t csi_RS_WithZeroTransmissionPower_r10_internal_value;

    };

    setup setup_value;

};

#endif
