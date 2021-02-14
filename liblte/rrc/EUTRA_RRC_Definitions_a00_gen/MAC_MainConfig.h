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

#ifndef __MAC_MainConfig_H__
#define __MAC_MainConfig_H__

#include "DRX_Config.h"
#include "TimeAlignmentTimer.h"

#include <array>
#include <cstdint>
#include <vector>

class MAC_MainConfig
{
public:
    MAC_MainConfig() : drx_Config_present{false}, timeAlignmentTimerDedicated_present{false}, phr_Config_present{false}, sr_ProhibitTimer_r9_present{false}, sCellDeactivationTimer_r10_present{false}, extendedBSR_Sizes_r10_present{false}, extendedPHR_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // ul-SCH-Config
public:
    class ul_SCH_Config
    {
    public:
        ul_SCH_Config() : present{false}, maxHARQ_Tx_present{false}, periodicBSR_Timer_present{false}, retxBSR_Timer_present{false}, ttiBundling_present{false} {};
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

        // maxHARQ-Tx
    public:
        enum maxHARQ_Tx_Enum {
            k_maxHARQ_Tx_n1 = 0,
            k_maxHARQ_Tx_n2,
            k_maxHARQ_Tx_n3,
            k_maxHARQ_Tx_n4,
            k_maxHARQ_Tx_n5,
            k_maxHARQ_Tx_n6,
            k_maxHARQ_Tx_n7,
            k_maxHARQ_Tx_n8,
            k_maxHARQ_Tx_n10,
            k_maxHARQ_Tx_n12,
            k_maxHARQ_Tx_n16,
            k_maxHARQ_Tx_n20,
            k_maxHARQ_Tx_n24,
            k_maxHARQ_Tx_n28,
            k_maxHARQ_Tx_spare2,
            k_maxHARQ_Tx_spare1,
        };
        int maxHARQ_Tx_Pack(std::vector<uint8_t> &bits);
        int maxHARQ_Tx_Unpack(std::vector<uint8_t> bits);
        int maxHARQ_Tx_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        maxHARQ_Tx_Enum maxHARQ_Tx_Value() const;
        int maxHARQ_Tx_SetValue(maxHARQ_Tx_Enum value);
        int maxHARQ_Tx_SetValue(std::string value);
        std::string maxHARQ_Tx_ValueToString(maxHARQ_Tx_Enum value) const;
        uint64_t maxHARQ_Tx_NumberOfValues() const;
        std::string maxHARQ_Tx_ToString(uint32_t indent) const;
        std::string maxHARQ_Tx_ToStringNoNewLines() const;
        int maxHARQ_Tx_Clear();
        bool maxHARQ_Tx_IsPresent() const;
    private:
        bool maxHARQ_Tx_present;
        maxHARQ_Tx_Enum maxHARQ_Tx_internal_value;

        // periodicBSR-Timer
    public:
        enum periodicBSR_Timer_Enum {
            k_periodicBSR_Timer_sf5 = 0,
            k_periodicBSR_Timer_sf10,
            k_periodicBSR_Timer_sf16,
            k_periodicBSR_Timer_sf20,
            k_periodicBSR_Timer_sf32,
            k_periodicBSR_Timer_sf40,
            k_periodicBSR_Timer_sf64,
            k_periodicBSR_Timer_sf80,
            k_periodicBSR_Timer_sf128,
            k_periodicBSR_Timer_sf160,
            k_periodicBSR_Timer_sf320,
            k_periodicBSR_Timer_sf640,
            k_periodicBSR_Timer_sf1280,
            k_periodicBSR_Timer_sf2560,
            k_periodicBSR_Timer_infinity,
            k_periodicBSR_Timer_spare1,
        };
        int periodicBSR_Timer_Pack(std::vector<uint8_t> &bits);
        int periodicBSR_Timer_Unpack(std::vector<uint8_t> bits);
        int periodicBSR_Timer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        periodicBSR_Timer_Enum periodicBSR_Timer_Value() const;
        int periodicBSR_Timer_SetValue(periodicBSR_Timer_Enum value);
        int periodicBSR_Timer_SetValue(std::string value);
        std::string periodicBSR_Timer_ValueToString(periodicBSR_Timer_Enum value) const;
        uint64_t periodicBSR_Timer_NumberOfValues() const;
        std::string periodicBSR_Timer_ToString(uint32_t indent) const;
        std::string periodicBSR_Timer_ToStringNoNewLines() const;
        int periodicBSR_Timer_Clear();
        bool periodicBSR_Timer_IsPresent() const;
    private:
        bool periodicBSR_Timer_present;
        periodicBSR_Timer_Enum periodicBSR_Timer_internal_value;

        // retxBSR-Timer
    public:
        enum retxBSR_Timer_Enum {
            k_retxBSR_Timer_sf320 = 0,
            k_retxBSR_Timer_sf640,
            k_retxBSR_Timer_sf1280,
            k_retxBSR_Timer_sf2560,
            k_retxBSR_Timer_sf5120,
            k_retxBSR_Timer_sf10240,
            k_retxBSR_Timer_spare2,
            k_retxBSR_Timer_spare1,
        };
        int retxBSR_Timer_Pack(std::vector<uint8_t> &bits);
        int retxBSR_Timer_Unpack(std::vector<uint8_t> bits);
        int retxBSR_Timer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        retxBSR_Timer_Enum retxBSR_Timer_Value() const;
        int retxBSR_Timer_SetValue(retxBSR_Timer_Enum value);
        int retxBSR_Timer_SetValue(std::string value);
        std::string retxBSR_Timer_ValueToString(retxBSR_Timer_Enum value) const;
        uint64_t retxBSR_Timer_NumberOfValues() const;
        std::string retxBSR_Timer_ToString(uint32_t indent) const;
        std::string retxBSR_Timer_ToStringNoNewLines() const;
        int retxBSR_Timer_Clear();
        bool retxBSR_Timer_IsPresent() const;
    private:
        bool retxBSR_Timer_present;
        retxBSR_Timer_Enum retxBSR_Timer_internal_value;

        // ttiBundling
    public:
        int ttiBundling_Pack(std::vector<uint8_t> &bits);
        int ttiBundling_Unpack(std::vector<uint8_t> bits);
        int ttiBundling_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        bool ttiBundling_Value() const;
        int ttiBundling_SetValue(bool value);
        std::string ttiBundling_ToString(uint32_t indent) const;
        std::string ttiBundling_ToStringNoNewLines() const;
        int ttiBundling_Clear();
        bool ttiBundling_IsPresent() const;
    private:
        bool ttiBundling_present;
        bool ttiBundling_internal_value;

    };

    ul_SCH_Config ul_SCH_Config_value;

    // drx-Config
public:
    DRX_Config* drx_Config_Set();
    int drx_Config_Set(DRX_Config &value);
    const DRX_Config& drx_Config_Get() const;
    std::string drx_Config_ToString(uint32_t indent) const;
    std::string drx_Config_ToStringNoNewLines() const;
    int drx_Config_Clear();
    bool drx_Config_IsPresent() const;
private:
    bool drx_Config_present;
    DRX_Config drx_Config;

    // timeAlignmentTimerDedicated
public:
    TimeAlignmentTimer* timeAlignmentTimerDedicated_Set();
    int timeAlignmentTimerDedicated_Set(TimeAlignmentTimer &value);
    const TimeAlignmentTimer& timeAlignmentTimerDedicated_Get() const;
    std::string timeAlignmentTimerDedicated_ToString(uint32_t indent) const;
    std::string timeAlignmentTimerDedicated_ToStringNoNewLines() const;
    int timeAlignmentTimerDedicated_Clear();
    bool timeAlignmentTimerDedicated_IsPresent() const;
private:
    bool timeAlignmentTimerDedicated_present;
    TimeAlignmentTimer timeAlignmentTimerDedicated;

    // phr-Config
public:
    enum phr_Config_Enum {
        k_phr_Config_release = 0,
        k_phr_Config_setup,
    };
    int phr_Config_Pack(std::vector<uint8_t> &bits);
    int phr_Config_Unpack(std::vector<uint8_t> bits);
    int phr_Config_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    phr_Config_Enum phr_Config_Choice() const;
    int phr_Config_SetChoice(phr_Config_Enum choice);
    std::string phr_Config_ChoiceToString(phr_Config_Enum value) const;
    uint64_t phr_Config_NumberOfChoices() const;
    std::string phr_Config_ToString(uint32_t indent) const;
    std::string phr_Config_ToStringNoNewLines() const;
    int phr_Config_Clear();
    bool phr_Config_IsPresent() const;
private:
    bool phr_Config_present;
    phr_Config_Enum phr_Config_internal_choice;

    // release
public:
    int phr_Config_release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int phr_Config_release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int phr_Config_release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool phr_Config_release_IsPresent() const {return true;};
    std::string phr_Config_release_ToString(uint32_t indent) {return "";};
    std::string phr_Config_release_ToStringNoNewLines() {return "";};

    // setup
public:
    class phr_Config_setup
    {
    public:
        phr_Config_setup() : periodicPHR_Timer_present{false}, prohibitPHR_Timer_present{false}, dl_PathlossChange_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // periodicPHR-Timer
    public:
        enum periodicPHR_Timer_Enum {
            k_periodicPHR_Timer_sf10 = 0,
            k_periodicPHR_Timer_sf20,
            k_periodicPHR_Timer_sf50,
            k_periodicPHR_Timer_sf100,
            k_periodicPHR_Timer_sf200,
            k_periodicPHR_Timer_sf500,
            k_periodicPHR_Timer_sf1000,
            k_periodicPHR_Timer_infinity,
        };
        int periodicPHR_Timer_Pack(std::vector<uint8_t> &bits);
        int periodicPHR_Timer_Unpack(std::vector<uint8_t> bits);
        int periodicPHR_Timer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        periodicPHR_Timer_Enum periodicPHR_Timer_Value() const;
        int periodicPHR_Timer_SetValue(periodicPHR_Timer_Enum value);
        int periodicPHR_Timer_SetValue(std::string value);
        std::string periodicPHR_Timer_ValueToString(periodicPHR_Timer_Enum value) const;
        uint64_t periodicPHR_Timer_NumberOfValues() const;
        std::string periodicPHR_Timer_ToString(uint32_t indent) const;
        std::string periodicPHR_Timer_ToStringNoNewLines() const;
        int periodicPHR_Timer_Clear();
        bool periodicPHR_Timer_IsPresent() const;
    private:
        bool periodicPHR_Timer_present;
        periodicPHR_Timer_Enum periodicPHR_Timer_internal_value;

        // prohibitPHR-Timer
    public:
        enum prohibitPHR_Timer_Enum {
            k_prohibitPHR_Timer_sf0 = 0,
            k_prohibitPHR_Timer_sf10,
            k_prohibitPHR_Timer_sf20,
            k_prohibitPHR_Timer_sf50,
            k_prohibitPHR_Timer_sf100,
            k_prohibitPHR_Timer_sf200,
            k_prohibitPHR_Timer_sf500,
            k_prohibitPHR_Timer_sf1000,
        };
        int prohibitPHR_Timer_Pack(std::vector<uint8_t> &bits);
        int prohibitPHR_Timer_Unpack(std::vector<uint8_t> bits);
        int prohibitPHR_Timer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        prohibitPHR_Timer_Enum prohibitPHR_Timer_Value() const;
        int prohibitPHR_Timer_SetValue(prohibitPHR_Timer_Enum value);
        int prohibitPHR_Timer_SetValue(std::string value);
        std::string prohibitPHR_Timer_ValueToString(prohibitPHR_Timer_Enum value) const;
        uint64_t prohibitPHR_Timer_NumberOfValues() const;
        std::string prohibitPHR_Timer_ToString(uint32_t indent) const;
        std::string prohibitPHR_Timer_ToStringNoNewLines() const;
        int prohibitPHR_Timer_Clear();
        bool prohibitPHR_Timer_IsPresent() const;
    private:
        bool prohibitPHR_Timer_present;
        prohibitPHR_Timer_Enum prohibitPHR_Timer_internal_value;

        // dl-PathlossChange
    public:
        enum dl_PathlossChange_Enum {
            k_dl_PathlossChange_dB1 = 0,
            k_dl_PathlossChange_dB3,
            k_dl_PathlossChange_dB6,
            k_dl_PathlossChange_infinity,
        };
        int dl_PathlossChange_Pack(std::vector<uint8_t> &bits);
        int dl_PathlossChange_Unpack(std::vector<uint8_t> bits);
        int dl_PathlossChange_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        dl_PathlossChange_Enum dl_PathlossChange_Value() const;
        int dl_PathlossChange_SetValue(dl_PathlossChange_Enum value);
        int dl_PathlossChange_SetValue(std::string value);
        std::string dl_PathlossChange_ValueToString(dl_PathlossChange_Enum value) const;
        uint64_t dl_PathlossChange_NumberOfValues() const;
        std::string dl_PathlossChange_ToString(uint32_t indent) const;
        std::string dl_PathlossChange_ToStringNoNewLines() const;
        int dl_PathlossChange_Clear();
        bool dl_PathlossChange_IsPresent() const;
    private:
        bool dl_PathlossChange_present;
        dl_PathlossChange_Enum dl_PathlossChange_internal_value;

    };

    phr_Config_setup phr_Config_setup_value;


    // sr-ProhibitTimer-r9
public:
    int sr_ProhibitTimer_r9_Pack(std::vector<uint8_t> &bits);
    int sr_ProhibitTimer_r9_Unpack(std::vector<uint8_t> bits);
    int sr_ProhibitTimer_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t sr_ProhibitTimer_r9_Value() const;
    int sr_ProhibitTimer_r9_SetValue(int64_t value);
    std::string sr_ProhibitTimer_r9_ToString(uint32_t indent) const;
    std::string sr_ProhibitTimer_r9_ToStringNoNewLines() const;
    int sr_ProhibitTimer_r9_Clear();
    bool sr_ProhibitTimer_r9_IsPresent() const;
private:
    bool sr_ProhibitTimer_r9_present;
    int64_t sr_ProhibitTimer_r9_internal_value;

    // sCellDeactivationTimer-r10
public:
    enum sCellDeactivationTimer_r10_Enum {
        k_sCellDeactivationTimer_r10_rf2 = 0,
        k_sCellDeactivationTimer_r10_rf4,
        k_sCellDeactivationTimer_r10_rf8,
        k_sCellDeactivationTimer_r10_rf16,
        k_sCellDeactivationTimer_r10_rf32,
        k_sCellDeactivationTimer_r10_rf64,
        k_sCellDeactivationTimer_r10_rf128,
        k_sCellDeactivationTimer_r10_infinity,
    };
    int sCellDeactivationTimer_r10_Pack(std::vector<uint8_t> &bits);
    int sCellDeactivationTimer_r10_Unpack(std::vector<uint8_t> bits);
    int sCellDeactivationTimer_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    sCellDeactivationTimer_r10_Enum sCellDeactivationTimer_r10_Value() const;
    int sCellDeactivationTimer_r10_SetValue(sCellDeactivationTimer_r10_Enum value);
    int sCellDeactivationTimer_r10_SetValue(std::string value);
    std::string sCellDeactivationTimer_r10_ValueToString(sCellDeactivationTimer_r10_Enum value) const;
    uint64_t sCellDeactivationTimer_r10_NumberOfValues() const;
    std::string sCellDeactivationTimer_r10_ToString(uint32_t indent) const;
    std::string sCellDeactivationTimer_r10_ToStringNoNewLines() const;
    int sCellDeactivationTimer_r10_Clear();
    bool sCellDeactivationTimer_r10_IsPresent() const;
private:
    bool sCellDeactivationTimer_r10_present;
    sCellDeactivationTimer_r10_Enum sCellDeactivationTimer_r10_internal_value;

    // extendedBSR-Sizes-r10
public:
    int extendedBSR_Sizes_r10_Pack(std::vector<uint8_t> &bits);
    int extendedBSR_Sizes_r10_Unpack(std::vector<uint8_t> bits);
    int extendedBSR_Sizes_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool extendedBSR_Sizes_r10_Value() const;
    int extendedBSR_Sizes_r10_SetValue(bool value);
    std::string extendedBSR_Sizes_r10_ToString(uint32_t indent) const;
    std::string extendedBSR_Sizes_r10_ToStringNoNewLines() const;
    int extendedBSR_Sizes_r10_Clear();
    bool extendedBSR_Sizes_r10_IsPresent() const;
private:
    bool extendedBSR_Sizes_r10_present;
    bool extendedBSR_Sizes_r10_internal_value;

    // extendedPHR-r10
public:
    int extendedPHR_r10_Pack(std::vector<uint8_t> &bits);
    int extendedPHR_r10_Unpack(std::vector<uint8_t> bits);
    int extendedPHR_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool extendedPHR_r10_Value() const;
    int extendedPHR_r10_SetValue(bool value);
    std::string extendedPHR_r10_ToString(uint32_t indent) const;
    std::string extendedPHR_r10_ToStringNoNewLines() const;
    int extendedPHR_r10_Clear();
    bool extendedPHR_r10_IsPresent() const;
private:
    bool extendedPHR_r10_present;
    bool extendedPHR_r10_internal_value;

};

#endif
