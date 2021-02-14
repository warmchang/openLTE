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

#ifndef __SystemInformationBlockType8_H__
#define __SystemInformationBlockType8_H__

#include "SystemTimeInfoCDMA2000.h"
#include "PreRegistrationInfoHRPD.h"
#include "CellReselectionParametersCDMA2000.h"
#include "CSFB_RegistrationParam1XRTT.h"
#include "CellReselectionParametersCDMA2000.h"
#include "CellReselectionParametersCDMA2000_v920.h"
#include "CellReselectionParametersCDMA2000_v920.h"
#include "CSFB_RegistrationParam1XRTT_v920.h"
#include "AC_BarringConfig1XRTT_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class SystemInformationBlockType8
{
public:
    SystemInformationBlockType8() : systemTimeInfo_present{false}, searchWindowSize_present{false}, lateNonCriticalExtension_present{false}, csfb_SupportForDualRxUEs_r9_present{false}, cellReselectionParametersHRPD_v920_present{false}, cellReselectionParameters1XRTT_v920_present{false}, csfb_RegistrationParam1XRTT_v920_present{false}, ac_BarringConfig1XRTT_r9_present{false}, csfb_DualRxTxSupport_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // systemTimeInfo
public:
    SystemTimeInfoCDMA2000* systemTimeInfo_Set();
    int systemTimeInfo_Set(SystemTimeInfoCDMA2000 &value);
    const SystemTimeInfoCDMA2000& systemTimeInfo_Get() const;
    std::string systemTimeInfo_ToString(uint32_t indent) const;
    std::string systemTimeInfo_ToStringNoNewLines() const;
    int systemTimeInfo_Clear();
    bool systemTimeInfo_IsPresent() const;
private:
    bool systemTimeInfo_present;
    SystemTimeInfoCDMA2000 systemTimeInfo;

    // searchWindowSize
public:
    int searchWindowSize_Pack(std::vector<uint8_t> &bits);
    int searchWindowSize_Unpack(std::vector<uint8_t> bits);
    int searchWindowSize_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t searchWindowSize_Value() const;
    int searchWindowSize_SetValue(int64_t value);
    std::string searchWindowSize_ToString(uint32_t indent) const;
    std::string searchWindowSize_ToStringNoNewLines() const;
    int searchWindowSize_Clear();
    bool searchWindowSize_IsPresent() const;
private:
    bool searchWindowSize_present;
    int64_t searchWindowSize_internal_value;

    // parametersHRPD
public:
    class parametersHRPD
    {
    public:
        parametersHRPD() : present{false}, preRegistrationInfoHRPD_present{false}, cellReselectionParametersHRPD_present{false} {};
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

        // preRegistrationInfoHRPD
    public:
        PreRegistrationInfoHRPD* preRegistrationInfoHRPD_Set();
        int preRegistrationInfoHRPD_Set(PreRegistrationInfoHRPD &value);
        const PreRegistrationInfoHRPD& preRegistrationInfoHRPD_Get() const;
        std::string preRegistrationInfoHRPD_ToString(uint32_t indent) const;
        std::string preRegistrationInfoHRPD_ToStringNoNewLines() const;
        int preRegistrationInfoHRPD_Clear();
        bool preRegistrationInfoHRPD_IsPresent() const;
    private:
        bool preRegistrationInfoHRPD_present;
        PreRegistrationInfoHRPD preRegistrationInfoHRPD;

        // cellReselectionParametersHRPD
    public:
        CellReselectionParametersCDMA2000* cellReselectionParametersHRPD_Set();
        int cellReselectionParametersHRPD_Set(CellReselectionParametersCDMA2000 &value);
        const CellReselectionParametersCDMA2000& cellReselectionParametersHRPD_Get() const;
        std::string cellReselectionParametersHRPD_ToString(uint32_t indent) const;
        std::string cellReselectionParametersHRPD_ToStringNoNewLines() const;
        int cellReselectionParametersHRPD_Clear();
        bool cellReselectionParametersHRPD_IsPresent() const;
    private:
        bool cellReselectionParametersHRPD_present;
        CellReselectionParametersCDMA2000 cellReselectionParametersHRPD;

    };

    parametersHRPD parametersHRPD_value;

    // parameters1XRTT
public:
    class parameters1XRTT
    {
    public:
        parameters1XRTT() : present{false}, csfb_RegistrationParam1XRTT_present{false}, longCodeState1XRTT_present{false}, cellReselectionParameters1XRTT_present{false} {};
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

        // csfb-RegistrationParam1XRTT
    public:
        CSFB_RegistrationParam1XRTT* csfb_RegistrationParam1XRTT_Set();
        int csfb_RegistrationParam1XRTT_Set(CSFB_RegistrationParam1XRTT &value);
        const CSFB_RegistrationParam1XRTT& csfb_RegistrationParam1XRTT_Get() const;
        std::string csfb_RegistrationParam1XRTT_ToString(uint32_t indent) const;
        std::string csfb_RegistrationParam1XRTT_ToStringNoNewLines() const;
        int csfb_RegistrationParam1XRTT_Clear();
        bool csfb_RegistrationParam1XRTT_IsPresent() const;
    private:
        bool csfb_RegistrationParam1XRTT_present;
        CSFB_RegistrationParam1XRTT csfb_RegistrationParam1XRTT;

        // longCodeState1XRTT
    public:
        int longCodeState1XRTT_Pack(std::vector<uint8_t> &bits);
        int longCodeState1XRTT_Unpack(std::vector<uint8_t> bits);
        int longCodeState1XRTT_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint64_t longCodeState1XRTT_Value() const;
        int longCodeState1XRTT_SetValue(uint64_t value);
        std::string longCodeState1XRTT_ToString(uint32_t indent) const;
        std::string longCodeState1XRTT_ToStringNoNewLines() const;
        int longCodeState1XRTT_Clear();
        bool longCodeState1XRTT_IsPresent() const;
    private:
        bool longCodeState1XRTT_present;
        uint64_t longCodeState1XRTT_internal_value;

        // cellReselectionParameters1XRTT
    public:
        CellReselectionParametersCDMA2000* cellReselectionParameters1XRTT_Set();
        int cellReselectionParameters1XRTT_Set(CellReselectionParametersCDMA2000 &value);
        const CellReselectionParametersCDMA2000& cellReselectionParameters1XRTT_Get() const;
        std::string cellReselectionParameters1XRTT_ToString(uint32_t indent) const;
        std::string cellReselectionParameters1XRTT_ToStringNoNewLines() const;
        int cellReselectionParameters1XRTT_Clear();
        bool cellReselectionParameters1XRTT_IsPresent() const;
    private:
        bool cellReselectionParameters1XRTT_present;
        CellReselectionParametersCDMA2000 cellReselectionParameters1XRTT;

    };

    parameters1XRTT parameters1XRTT_value;

    // lateNonCriticalExtension
public:
    int lateNonCriticalExtension_Pack(std::vector<uint8_t> &bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits);
    int lateNonCriticalExtension_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::vector<uint8_t> lateNonCriticalExtension_Value() const;
    int lateNonCriticalExtension_SetValue(std::vector<uint8_t> value);
    std::string lateNonCriticalExtension_ToString(uint32_t indent) const;
    std::string lateNonCriticalExtension_ToStringNoNewLines() const;
    int lateNonCriticalExtension_Clear();
    bool lateNonCriticalExtension_IsPresent() const;
private:
    bool lateNonCriticalExtension_present;
    std::vector<uint8_t> lateNonCriticalExtension_internal_value;

    // csfb-SupportForDualRxUEs-r9
public:
    int csfb_SupportForDualRxUEs_r9_Pack(std::vector<uint8_t> &bits);
    int csfb_SupportForDualRxUEs_r9_Unpack(std::vector<uint8_t> bits);
    int csfb_SupportForDualRxUEs_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    bool csfb_SupportForDualRxUEs_r9_Value() const;
    int csfb_SupportForDualRxUEs_r9_SetValue(bool value);
    std::string csfb_SupportForDualRxUEs_r9_ToString(uint32_t indent) const;
    std::string csfb_SupportForDualRxUEs_r9_ToStringNoNewLines() const;
    int csfb_SupportForDualRxUEs_r9_Clear();
    bool csfb_SupportForDualRxUEs_r9_IsPresent() const;
private:
    bool csfb_SupportForDualRxUEs_r9_present;
    bool csfb_SupportForDualRxUEs_r9_internal_value;

    // cellReselectionParametersHRPD-v920
public:
    CellReselectionParametersCDMA2000_v920* cellReselectionParametersHRPD_v920_Set();
    int cellReselectionParametersHRPD_v920_Set(CellReselectionParametersCDMA2000_v920 &value);
    const CellReselectionParametersCDMA2000_v920& cellReselectionParametersHRPD_v920_Get() const;
    std::string cellReselectionParametersHRPD_v920_ToString(uint32_t indent) const;
    std::string cellReselectionParametersHRPD_v920_ToStringNoNewLines() const;
    int cellReselectionParametersHRPD_v920_Clear();
    bool cellReselectionParametersHRPD_v920_IsPresent() const;
private:
    bool cellReselectionParametersHRPD_v920_present;
    CellReselectionParametersCDMA2000_v920 cellReselectionParametersHRPD_v920;

    // cellReselectionParameters1XRTT-v920
public:
    CellReselectionParametersCDMA2000_v920* cellReselectionParameters1XRTT_v920_Set();
    int cellReselectionParameters1XRTT_v920_Set(CellReselectionParametersCDMA2000_v920 &value);
    const CellReselectionParametersCDMA2000_v920& cellReselectionParameters1XRTT_v920_Get() const;
    std::string cellReselectionParameters1XRTT_v920_ToString(uint32_t indent) const;
    std::string cellReselectionParameters1XRTT_v920_ToStringNoNewLines() const;
    int cellReselectionParameters1XRTT_v920_Clear();
    bool cellReselectionParameters1XRTT_v920_IsPresent() const;
private:
    bool cellReselectionParameters1XRTT_v920_present;
    CellReselectionParametersCDMA2000_v920 cellReselectionParameters1XRTT_v920;

    // csfb-RegistrationParam1XRTT-v920
public:
    CSFB_RegistrationParam1XRTT_v920* csfb_RegistrationParam1XRTT_v920_Set();
    int csfb_RegistrationParam1XRTT_v920_Set(CSFB_RegistrationParam1XRTT_v920 &value);
    const CSFB_RegistrationParam1XRTT_v920& csfb_RegistrationParam1XRTT_v920_Get() const;
    std::string csfb_RegistrationParam1XRTT_v920_ToString(uint32_t indent) const;
    std::string csfb_RegistrationParam1XRTT_v920_ToStringNoNewLines() const;
    int csfb_RegistrationParam1XRTT_v920_Clear();
    bool csfb_RegistrationParam1XRTT_v920_IsPresent() const;
private:
    bool csfb_RegistrationParam1XRTT_v920_present;
    CSFB_RegistrationParam1XRTT_v920 csfb_RegistrationParam1XRTT_v920;

    // ac-BarringConfig1XRTT-r9
public:
    AC_BarringConfig1XRTT_r9* ac_BarringConfig1XRTT_r9_Set();
    int ac_BarringConfig1XRTT_r9_Set(AC_BarringConfig1XRTT_r9 &value);
    const AC_BarringConfig1XRTT_r9& ac_BarringConfig1XRTT_r9_Get() const;
    std::string ac_BarringConfig1XRTT_r9_ToString(uint32_t indent) const;
    std::string ac_BarringConfig1XRTT_r9_ToStringNoNewLines() const;
    int ac_BarringConfig1XRTT_r9_Clear();
    bool ac_BarringConfig1XRTT_r9_IsPresent() const;
private:
    bool ac_BarringConfig1XRTT_r9_present;
    AC_BarringConfig1XRTT_r9 ac_BarringConfig1XRTT_r9;

    // csfb-DualRxTxSupport-r10
public:
    enum csfb_DualRxTxSupport_r10_Enum {
        k_csfb_DualRxTxSupport_r10_true = 0,
    };
    int csfb_DualRxTxSupport_r10_Pack(std::vector<uint8_t> &bits);
    int csfb_DualRxTxSupport_r10_Unpack(std::vector<uint8_t> bits);
    int csfb_DualRxTxSupport_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    csfb_DualRxTxSupport_r10_Enum csfb_DualRxTxSupport_r10_Value() const;
    int csfb_DualRxTxSupport_r10_SetValue(csfb_DualRxTxSupport_r10_Enum value);
    int csfb_DualRxTxSupport_r10_SetValue(std::string value);
    std::string csfb_DualRxTxSupport_r10_ValueToString(csfb_DualRxTxSupport_r10_Enum value) const;
    uint64_t csfb_DualRxTxSupport_r10_NumberOfValues() const;
    std::string csfb_DualRxTxSupport_r10_ToString(uint32_t indent) const;
    std::string csfb_DualRxTxSupport_r10_ToStringNoNewLines() const;
    int csfb_DualRxTxSupport_r10_Clear();
    bool csfb_DualRxTxSupport_r10_IsPresent() const;
private:
    bool csfb_DualRxTxSupport_r10_present;
    csfb_DualRxTxSupport_r10_Enum csfb_DualRxTxSupport_r10_internal_value;

};

#endif
