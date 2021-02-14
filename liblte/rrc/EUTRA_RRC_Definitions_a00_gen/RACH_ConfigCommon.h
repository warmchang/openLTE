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

#ifndef __RACH_ConfigCommon_H__
#define __RACH_ConfigCommon_H__

#include <array>
#include <cstdint>
#include <vector>

class RACH_ConfigCommon
{
public:
    RACH_ConfigCommon() : maxHARQ_Msg3Tx_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // preambleInfo
public:
    class preambleInfo
    {
    public:
        preambleInfo() : numberOfRA_Preambles_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // numberOfRA-Preambles
    public:
        enum numberOfRA_Preambles_Enum {
            k_numberOfRA_Preambles_n4 = 0,
            k_numberOfRA_Preambles_n8,
            k_numberOfRA_Preambles_n12,
            k_numberOfRA_Preambles_n16,
            k_numberOfRA_Preambles_n20,
            k_numberOfRA_Preambles_n24,
            k_numberOfRA_Preambles_n28,
            k_numberOfRA_Preambles_n32,
            k_numberOfRA_Preambles_n36,
            k_numberOfRA_Preambles_n40,
            k_numberOfRA_Preambles_n44,
            k_numberOfRA_Preambles_n48,
            k_numberOfRA_Preambles_n52,
            k_numberOfRA_Preambles_n56,
            k_numberOfRA_Preambles_n60,
            k_numberOfRA_Preambles_n64,
        };
        int numberOfRA_Preambles_Pack(std::vector<uint8_t> &bits);
        int numberOfRA_Preambles_Unpack(std::vector<uint8_t> bits);
        int numberOfRA_Preambles_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        numberOfRA_Preambles_Enum numberOfRA_Preambles_Value() const;
        int numberOfRA_Preambles_SetValue(numberOfRA_Preambles_Enum value);
        int numberOfRA_Preambles_SetValue(std::string value);
        std::string numberOfRA_Preambles_ValueToString(numberOfRA_Preambles_Enum value) const;
        uint64_t numberOfRA_Preambles_NumberOfValues() const;
        std::string numberOfRA_Preambles_ToString(uint32_t indent) const;
        std::string numberOfRA_Preambles_ToStringNoNewLines() const;
        int numberOfRA_Preambles_Clear();
        bool numberOfRA_Preambles_IsPresent() const;
    private:
        bool numberOfRA_Preambles_present;
        numberOfRA_Preambles_Enum numberOfRA_Preambles_internal_value;

        // preamblesGroupAConfig
    public:
        class preamblesGroupAConfig
        {
        public:
            preamblesGroupAConfig() : present{false}, sizeOfRA_PreamblesGroupA_present{false}, messageSizeGroupA_present{false}, messagePowerOffsetGroupB_present{false} {};
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

            // sizeOfRA-PreamblesGroupA
        public:
            enum sizeOfRA_PreamblesGroupA_Enum {
                k_sizeOfRA_PreamblesGroupA_n4 = 0,
                k_sizeOfRA_PreamblesGroupA_n8,
                k_sizeOfRA_PreamblesGroupA_n12,
                k_sizeOfRA_PreamblesGroupA_n16,
                k_sizeOfRA_PreamblesGroupA_n20,
                k_sizeOfRA_PreamblesGroupA_n24,
                k_sizeOfRA_PreamblesGroupA_n28,
                k_sizeOfRA_PreamblesGroupA_n32,
                k_sizeOfRA_PreamblesGroupA_n36,
                k_sizeOfRA_PreamblesGroupA_n40,
                k_sizeOfRA_PreamblesGroupA_n44,
                k_sizeOfRA_PreamblesGroupA_n48,
                k_sizeOfRA_PreamblesGroupA_n52,
                k_sizeOfRA_PreamblesGroupA_n56,
                k_sizeOfRA_PreamblesGroupA_n60,
            };
            int sizeOfRA_PreamblesGroupA_Pack(std::vector<uint8_t> &bits);
            int sizeOfRA_PreamblesGroupA_Unpack(std::vector<uint8_t> bits);
            int sizeOfRA_PreamblesGroupA_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            sizeOfRA_PreamblesGroupA_Enum sizeOfRA_PreamblesGroupA_Value() const;
            int sizeOfRA_PreamblesGroupA_SetValue(sizeOfRA_PreamblesGroupA_Enum value);
            int sizeOfRA_PreamblesGroupA_SetValue(std::string value);
            std::string sizeOfRA_PreamblesGroupA_ValueToString(sizeOfRA_PreamblesGroupA_Enum value) const;
            uint64_t sizeOfRA_PreamblesGroupA_NumberOfValues() const;
            std::string sizeOfRA_PreamblesGroupA_ToString(uint32_t indent) const;
            std::string sizeOfRA_PreamblesGroupA_ToStringNoNewLines() const;
            int sizeOfRA_PreamblesGroupA_Clear();
            bool sizeOfRA_PreamblesGroupA_IsPresent() const;
        private:
            bool sizeOfRA_PreamblesGroupA_present;
            sizeOfRA_PreamblesGroupA_Enum sizeOfRA_PreamblesGroupA_internal_value;

            // messageSizeGroupA
        public:
            enum messageSizeGroupA_Enum {
                k_messageSizeGroupA_b56 = 0,
                k_messageSizeGroupA_b144,
                k_messageSizeGroupA_b208,
                k_messageSizeGroupA_b256,
            };
            int messageSizeGroupA_Pack(std::vector<uint8_t> &bits);
            int messageSizeGroupA_Unpack(std::vector<uint8_t> bits);
            int messageSizeGroupA_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            messageSizeGroupA_Enum messageSizeGroupA_Value() const;
            int messageSizeGroupA_SetValue(messageSizeGroupA_Enum value);
            int messageSizeGroupA_SetValue(std::string value);
            std::string messageSizeGroupA_ValueToString(messageSizeGroupA_Enum value) const;
            uint64_t messageSizeGroupA_NumberOfValues() const;
            std::string messageSizeGroupA_ToString(uint32_t indent) const;
            std::string messageSizeGroupA_ToStringNoNewLines() const;
            int messageSizeGroupA_Clear();
            bool messageSizeGroupA_IsPresent() const;
        private:
            bool messageSizeGroupA_present;
            messageSizeGroupA_Enum messageSizeGroupA_internal_value;

            // messagePowerOffsetGroupB
        public:
            enum messagePowerOffsetGroupB_Enum {
                k_messagePowerOffsetGroupB_minusinfinity = 0,
                k_messagePowerOffsetGroupB_dB0,
                k_messagePowerOffsetGroupB_dB5,
                k_messagePowerOffsetGroupB_dB8,
                k_messagePowerOffsetGroupB_dB10,
                k_messagePowerOffsetGroupB_dB12,
                k_messagePowerOffsetGroupB_dB15,
                k_messagePowerOffsetGroupB_dB18,
            };
            int messagePowerOffsetGroupB_Pack(std::vector<uint8_t> &bits);
            int messagePowerOffsetGroupB_Unpack(std::vector<uint8_t> bits);
            int messagePowerOffsetGroupB_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            messagePowerOffsetGroupB_Enum messagePowerOffsetGroupB_Value() const;
            int messagePowerOffsetGroupB_SetValue(messagePowerOffsetGroupB_Enum value);
            int messagePowerOffsetGroupB_SetValue(std::string value);
            std::string messagePowerOffsetGroupB_ValueToString(messagePowerOffsetGroupB_Enum value) const;
            uint64_t messagePowerOffsetGroupB_NumberOfValues() const;
            std::string messagePowerOffsetGroupB_ToString(uint32_t indent) const;
            std::string messagePowerOffsetGroupB_ToStringNoNewLines() const;
            int messagePowerOffsetGroupB_Clear();
            bool messagePowerOffsetGroupB_IsPresent() const;
        private:
            bool messagePowerOffsetGroupB_present;
            messagePowerOffsetGroupB_Enum messagePowerOffsetGroupB_internal_value;

        };

        preamblesGroupAConfig preamblesGroupAConfig_value;

    };

    preambleInfo preambleInfo_value;

    // powerRampingParameters
public:
    class powerRampingParameters
    {
    public:
        powerRampingParameters() : powerRampingStep_present{false}, preambleInitialReceivedTargetPower_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // powerRampingStep
    public:
        enum powerRampingStep_Enum {
            k_powerRampingStep_dB0 = 0,
            k_powerRampingStep_dB2,
            k_powerRampingStep_dB4,
            k_powerRampingStep_dB6,
        };
        int powerRampingStep_Pack(std::vector<uint8_t> &bits);
        int powerRampingStep_Unpack(std::vector<uint8_t> bits);
        int powerRampingStep_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        powerRampingStep_Enum powerRampingStep_Value() const;
        int powerRampingStep_SetValue(powerRampingStep_Enum value);
        int powerRampingStep_SetValue(std::string value);
        std::string powerRampingStep_ValueToString(powerRampingStep_Enum value) const;
        uint64_t powerRampingStep_NumberOfValues() const;
        std::string powerRampingStep_ToString(uint32_t indent) const;
        std::string powerRampingStep_ToStringNoNewLines() const;
        int powerRampingStep_Clear();
        bool powerRampingStep_IsPresent() const;
    private:
        bool powerRampingStep_present;
        powerRampingStep_Enum powerRampingStep_internal_value;

        // preambleInitialReceivedTargetPower
    public:
        enum preambleInitialReceivedTargetPower_Enum {
            k_preambleInitialReceivedTargetPower_dBm_120 = 0,
            k_preambleInitialReceivedTargetPower_dBm_118,
            k_preambleInitialReceivedTargetPower_dBm_116,
            k_preambleInitialReceivedTargetPower_dBm_114,
            k_preambleInitialReceivedTargetPower_dBm_112,
            k_preambleInitialReceivedTargetPower_dBm_110,
            k_preambleInitialReceivedTargetPower_dBm_108,
            k_preambleInitialReceivedTargetPower_dBm_106,
            k_preambleInitialReceivedTargetPower_dBm_104,
            k_preambleInitialReceivedTargetPower_dBm_102,
            k_preambleInitialReceivedTargetPower_dBm_100,
            k_preambleInitialReceivedTargetPower_dBm_98,
            k_preambleInitialReceivedTargetPower_dBm_96,
            k_preambleInitialReceivedTargetPower_dBm_94,
            k_preambleInitialReceivedTargetPower_dBm_92,
            k_preambleInitialReceivedTargetPower_dBm_90,
        };
        int preambleInitialReceivedTargetPower_Pack(std::vector<uint8_t> &bits);
        int preambleInitialReceivedTargetPower_Unpack(std::vector<uint8_t> bits);
        int preambleInitialReceivedTargetPower_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        preambleInitialReceivedTargetPower_Enum preambleInitialReceivedTargetPower_Value() const;
        int preambleInitialReceivedTargetPower_SetValue(preambleInitialReceivedTargetPower_Enum value);
        int preambleInitialReceivedTargetPower_SetValue(std::string value);
        std::string preambleInitialReceivedTargetPower_ValueToString(preambleInitialReceivedTargetPower_Enum value) const;
        uint64_t preambleInitialReceivedTargetPower_NumberOfValues() const;
        std::string preambleInitialReceivedTargetPower_ToString(uint32_t indent) const;
        std::string preambleInitialReceivedTargetPower_ToStringNoNewLines() const;
        int preambleInitialReceivedTargetPower_Clear();
        bool preambleInitialReceivedTargetPower_IsPresent() const;
    private:
        bool preambleInitialReceivedTargetPower_present;
        preambleInitialReceivedTargetPower_Enum preambleInitialReceivedTargetPower_internal_value;

    };

    powerRampingParameters powerRampingParameters_value;

    // ra-SupervisionInfo
public:
    class ra_SupervisionInfo
    {
    public:
        ra_SupervisionInfo() : preambleTransMax_present{false}, ra_ResponseWindowSize_present{false}, mac_ContentionResolutionTimer_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // preambleTransMax
    public:
        enum preambleTransMax_Enum {
            k_preambleTransMax_n3 = 0,
            k_preambleTransMax_n4,
            k_preambleTransMax_n5,
            k_preambleTransMax_n6,
            k_preambleTransMax_n7,
            k_preambleTransMax_n8,
            k_preambleTransMax_n10,
            k_preambleTransMax_n20,
            k_preambleTransMax_n50,
            k_preambleTransMax_n100,
            k_preambleTransMax_n200,
        };
        int preambleTransMax_Pack(std::vector<uint8_t> &bits);
        int preambleTransMax_Unpack(std::vector<uint8_t> bits);
        int preambleTransMax_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        preambleTransMax_Enum preambleTransMax_Value() const;
        int preambleTransMax_SetValue(preambleTransMax_Enum value);
        int preambleTransMax_SetValue(std::string value);
        std::string preambleTransMax_ValueToString(preambleTransMax_Enum value) const;
        uint64_t preambleTransMax_NumberOfValues() const;
        std::string preambleTransMax_ToString(uint32_t indent) const;
        std::string preambleTransMax_ToStringNoNewLines() const;
        int preambleTransMax_Clear();
        bool preambleTransMax_IsPresent() const;
    private:
        bool preambleTransMax_present;
        preambleTransMax_Enum preambleTransMax_internal_value;

        // ra-ResponseWindowSize
    public:
        enum ra_ResponseWindowSize_Enum {
            k_ra_ResponseWindowSize_sf2 = 0,
            k_ra_ResponseWindowSize_sf3,
            k_ra_ResponseWindowSize_sf4,
            k_ra_ResponseWindowSize_sf5,
            k_ra_ResponseWindowSize_sf6,
            k_ra_ResponseWindowSize_sf7,
            k_ra_ResponseWindowSize_sf8,
            k_ra_ResponseWindowSize_sf10,
        };
        int ra_ResponseWindowSize_Pack(std::vector<uint8_t> &bits);
        int ra_ResponseWindowSize_Unpack(std::vector<uint8_t> bits);
        int ra_ResponseWindowSize_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        ra_ResponseWindowSize_Enum ra_ResponseWindowSize_Value() const;
        int ra_ResponseWindowSize_SetValue(ra_ResponseWindowSize_Enum value);
        int ra_ResponseWindowSize_SetValue(std::string value);
        std::string ra_ResponseWindowSize_ValueToString(ra_ResponseWindowSize_Enum value) const;
        uint64_t ra_ResponseWindowSize_NumberOfValues() const;
        std::string ra_ResponseWindowSize_ToString(uint32_t indent) const;
        std::string ra_ResponseWindowSize_ToStringNoNewLines() const;
        int ra_ResponseWindowSize_Clear();
        bool ra_ResponseWindowSize_IsPresent() const;
    private:
        bool ra_ResponseWindowSize_present;
        ra_ResponseWindowSize_Enum ra_ResponseWindowSize_internal_value;

        // mac-ContentionResolutionTimer
    public:
        enum mac_ContentionResolutionTimer_Enum {
            k_mac_ContentionResolutionTimer_sf8 = 0,
            k_mac_ContentionResolutionTimer_sf16,
            k_mac_ContentionResolutionTimer_sf24,
            k_mac_ContentionResolutionTimer_sf32,
            k_mac_ContentionResolutionTimer_sf40,
            k_mac_ContentionResolutionTimer_sf48,
            k_mac_ContentionResolutionTimer_sf56,
            k_mac_ContentionResolutionTimer_sf64,
        };
        int mac_ContentionResolutionTimer_Pack(std::vector<uint8_t> &bits);
        int mac_ContentionResolutionTimer_Unpack(std::vector<uint8_t> bits);
        int mac_ContentionResolutionTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        mac_ContentionResolutionTimer_Enum mac_ContentionResolutionTimer_Value() const;
        int mac_ContentionResolutionTimer_SetValue(mac_ContentionResolutionTimer_Enum value);
        int mac_ContentionResolutionTimer_SetValue(std::string value);
        std::string mac_ContentionResolutionTimer_ValueToString(mac_ContentionResolutionTimer_Enum value) const;
        uint64_t mac_ContentionResolutionTimer_NumberOfValues() const;
        std::string mac_ContentionResolutionTimer_ToString(uint32_t indent) const;
        std::string mac_ContentionResolutionTimer_ToStringNoNewLines() const;
        int mac_ContentionResolutionTimer_Clear();
        bool mac_ContentionResolutionTimer_IsPresent() const;
    private:
        bool mac_ContentionResolutionTimer_present;
        mac_ContentionResolutionTimer_Enum mac_ContentionResolutionTimer_internal_value;

    };

    ra_SupervisionInfo ra_SupervisionInfo_value;

    // maxHARQ-Msg3Tx
public:
    int maxHARQ_Msg3Tx_Pack(std::vector<uint8_t> &bits);
    int maxHARQ_Msg3Tx_Unpack(std::vector<uint8_t> bits);
    int maxHARQ_Msg3Tx_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t maxHARQ_Msg3Tx_Value() const;
    int maxHARQ_Msg3Tx_SetValue(int64_t value);
    std::string maxHARQ_Msg3Tx_ToString(uint32_t indent) const;
    std::string maxHARQ_Msg3Tx_ToStringNoNewLines() const;
    int maxHARQ_Msg3Tx_Clear();
    bool maxHARQ_Msg3Tx_IsPresent() const;
private:
    bool maxHARQ_Msg3Tx_present;
    int64_t maxHARQ_Msg3Tx_internal_value;

};

#endif
