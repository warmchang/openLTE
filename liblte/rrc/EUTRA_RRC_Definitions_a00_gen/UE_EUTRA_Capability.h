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

#ifndef __UE_EUTRA_Capability_H__
#define __UE_EUTRA_Capability_H__

#include "AccessStratumRelease.h"
#include "PDCP_Parameters.h"
#include "PhyLayerParameters.h"
#include "RF_Parameters.h"
#include "MeasParameters.h"
#include "IRAT_ParametersUTRA_FDD.h"
#include "IRAT_ParametersUTRA_TDD128.h"
#include "IRAT_ParametersUTRA_TDD384.h"
#include "IRAT_ParametersUTRA_TDD768.h"
#include "IRAT_ParametersGERAN.h"
#include "IRAT_ParametersCDMA2000_HRPD.h"
#include "IRAT_ParametersCDMA2000_1XRTT.h"
#include "UE_EUTRA_Capability_v920_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class UE_EUTRA_Capability
{
public:
    UE_EUTRA_Capability() : accessStratumRelease_present{false}, ue_Category_present{false}, pdcp_Parameters_present{false}, phyLayerParameters_present{false}, rf_Parameters_present{false}, measParameters_present{false}, featureGroupIndicators_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // accessStratumRelease
public:
    AccessStratumRelease* accessStratumRelease_Set();
    int accessStratumRelease_Set(AccessStratumRelease &value);
    const AccessStratumRelease& accessStratumRelease_Get() const;
    std::string accessStratumRelease_ToString(uint32_t indent) const;
    std::string accessStratumRelease_ToStringNoNewLines() const;
    int accessStratumRelease_Clear();
    bool accessStratumRelease_IsPresent() const;
private:
    bool accessStratumRelease_present;
    AccessStratumRelease accessStratumRelease;

    // ue-Category
public:
    int ue_Category_Pack(std::vector<uint8_t> &bits);
    int ue_Category_Unpack(std::vector<uint8_t> bits);
    int ue_Category_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    int64_t ue_Category_Value() const;
    int ue_Category_SetValue(int64_t value);
    std::string ue_Category_ToString(uint32_t indent) const;
    std::string ue_Category_ToStringNoNewLines() const;
    int ue_Category_Clear();
    bool ue_Category_IsPresent() const;
private:
    bool ue_Category_present;
    int64_t ue_Category_internal_value;

    // pdcp-Parameters
public:
    PDCP_Parameters* pdcp_Parameters_Set();
    int pdcp_Parameters_Set(PDCP_Parameters &value);
    const PDCP_Parameters& pdcp_Parameters_Get() const;
    std::string pdcp_Parameters_ToString(uint32_t indent) const;
    std::string pdcp_Parameters_ToStringNoNewLines() const;
    int pdcp_Parameters_Clear();
    bool pdcp_Parameters_IsPresent() const;
private:
    bool pdcp_Parameters_present;
    PDCP_Parameters pdcp_Parameters;

    // phyLayerParameters
public:
    PhyLayerParameters* phyLayerParameters_Set();
    int phyLayerParameters_Set(PhyLayerParameters &value);
    const PhyLayerParameters& phyLayerParameters_Get() const;
    std::string phyLayerParameters_ToString(uint32_t indent) const;
    std::string phyLayerParameters_ToStringNoNewLines() const;
    int phyLayerParameters_Clear();
    bool phyLayerParameters_IsPresent() const;
private:
    bool phyLayerParameters_present;
    PhyLayerParameters phyLayerParameters;

    // rf-Parameters
public:
    RF_Parameters* rf_Parameters_Set();
    int rf_Parameters_Set(RF_Parameters &value);
    const RF_Parameters& rf_Parameters_Get() const;
    std::string rf_Parameters_ToString(uint32_t indent) const;
    std::string rf_Parameters_ToStringNoNewLines() const;
    int rf_Parameters_Clear();
    bool rf_Parameters_IsPresent() const;
private:
    bool rf_Parameters_present;
    RF_Parameters rf_Parameters;

    // measParameters
public:
    MeasParameters* measParameters_Set();
    int measParameters_Set(MeasParameters &value);
    const MeasParameters& measParameters_Get() const;
    std::string measParameters_ToString(uint32_t indent) const;
    std::string measParameters_ToStringNoNewLines() const;
    int measParameters_Clear();
    bool measParameters_IsPresent() const;
private:
    bool measParameters_present;
    MeasParameters measParameters;

    // featureGroupIndicators
public:
    int featureGroupIndicators_Pack(std::vector<uint8_t> &bits);
    int featureGroupIndicators_Unpack(std::vector<uint8_t> bits);
    int featureGroupIndicators_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint32_t featureGroupIndicators_Value() const;
    int featureGroupIndicators_SetValue(uint32_t value);
    std::string featureGroupIndicators_ToString(uint32_t indent) const;
    std::string featureGroupIndicators_ToStringNoNewLines() const;
    int featureGroupIndicators_Clear();
    bool featureGroupIndicators_IsPresent() const;
private:
    bool featureGroupIndicators_present;
    uint32_t featureGroupIndicators_internal_value;

    // interRAT-Parameters
public:
    class interRAT_Parameters
    {
    public:
        interRAT_Parameters() : utraFDD_present{false}, utraTDD128_present{false}, utraTDD384_present{false}, utraTDD768_present{false}, geran_present{false}, cdma2000_HRPD_present{false}, cdma2000_1xRTT_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // utraFDD
    public:
        IRAT_ParametersUTRA_FDD* utraFDD_Set();
        int utraFDD_Set(IRAT_ParametersUTRA_FDD &value);
        const IRAT_ParametersUTRA_FDD& utraFDD_Get() const;
        std::string utraFDD_ToString(uint32_t indent) const;
        std::string utraFDD_ToStringNoNewLines() const;
        int utraFDD_Clear();
        bool utraFDD_IsPresent() const;
    private:
        bool utraFDD_present;
        IRAT_ParametersUTRA_FDD utraFDD;

        // utraTDD128
    public:
        IRAT_ParametersUTRA_TDD128* utraTDD128_Set();
        int utraTDD128_Set(IRAT_ParametersUTRA_TDD128 &value);
        const IRAT_ParametersUTRA_TDD128& utraTDD128_Get() const;
        std::string utraTDD128_ToString(uint32_t indent) const;
        std::string utraTDD128_ToStringNoNewLines() const;
        int utraTDD128_Clear();
        bool utraTDD128_IsPresent() const;
    private:
        bool utraTDD128_present;
        IRAT_ParametersUTRA_TDD128 utraTDD128;

        // utraTDD384
    public:
        IRAT_ParametersUTRA_TDD384* utraTDD384_Set();
        int utraTDD384_Set(IRAT_ParametersUTRA_TDD384 &value);
        const IRAT_ParametersUTRA_TDD384& utraTDD384_Get() const;
        std::string utraTDD384_ToString(uint32_t indent) const;
        std::string utraTDD384_ToStringNoNewLines() const;
        int utraTDD384_Clear();
        bool utraTDD384_IsPresent() const;
    private:
        bool utraTDD384_present;
        IRAT_ParametersUTRA_TDD384 utraTDD384;

        // utraTDD768
    public:
        IRAT_ParametersUTRA_TDD768* utraTDD768_Set();
        int utraTDD768_Set(IRAT_ParametersUTRA_TDD768 &value);
        const IRAT_ParametersUTRA_TDD768& utraTDD768_Get() const;
        std::string utraTDD768_ToString(uint32_t indent) const;
        std::string utraTDD768_ToStringNoNewLines() const;
        int utraTDD768_Clear();
        bool utraTDD768_IsPresent() const;
    private:
        bool utraTDD768_present;
        IRAT_ParametersUTRA_TDD768 utraTDD768;

        // geran
    public:
        IRAT_ParametersGERAN* geran_Set();
        int geran_Set(IRAT_ParametersGERAN &value);
        const IRAT_ParametersGERAN& geran_Get() const;
        std::string geran_ToString(uint32_t indent) const;
        std::string geran_ToStringNoNewLines() const;
        int geran_Clear();
        bool geran_IsPresent() const;
    private:
        bool geran_present;
        IRAT_ParametersGERAN geran;

        // cdma2000-HRPD
    public:
        IRAT_ParametersCDMA2000_HRPD* cdma2000_HRPD_Set();
        int cdma2000_HRPD_Set(IRAT_ParametersCDMA2000_HRPD &value);
        const IRAT_ParametersCDMA2000_HRPD& cdma2000_HRPD_Get() const;
        std::string cdma2000_HRPD_ToString(uint32_t indent) const;
        std::string cdma2000_HRPD_ToStringNoNewLines() const;
        int cdma2000_HRPD_Clear();
        bool cdma2000_HRPD_IsPresent() const;
    private:
        bool cdma2000_HRPD_present;
        IRAT_ParametersCDMA2000_HRPD cdma2000_HRPD;

        // cdma2000-1xRTT
    public:
        IRAT_ParametersCDMA2000_1XRTT* cdma2000_1xRTT_Set();
        int cdma2000_1xRTT_Set(IRAT_ParametersCDMA2000_1XRTT &value);
        const IRAT_ParametersCDMA2000_1XRTT& cdma2000_1xRTT_Get() const;
        std::string cdma2000_1xRTT_ToString(uint32_t indent) const;
        std::string cdma2000_1xRTT_ToStringNoNewLines() const;
        int cdma2000_1xRTT_Clear();
        bool cdma2000_1xRTT_IsPresent() const;
    private:
        bool cdma2000_1xRTT_present;
        IRAT_ParametersCDMA2000_1XRTT cdma2000_1xRTT;

    };

    interRAT_Parameters interRAT_Parameters_value;

    // nonCriticalExtension
public:
    UE_EUTRA_Capability_v920_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(UE_EUTRA_Capability_v920_IEs &value);
    const UE_EUTRA_Capability_v920_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    UE_EUTRA_Capability_v920_IEs nonCriticalExtension;

};

#endif
