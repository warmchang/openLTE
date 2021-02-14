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

#ifndef __UE_EUTRA_Capability_v920_IEs_H__
#define __UE_EUTRA_Capability_v920_IEs_H__

#include "PhyLayerParameters_v920.h"
#include "IRAT_ParametersGERAN_v920.h"
#include "IRAT_ParametersUTRA_v920.h"
#include "IRAT_ParametersCDMA2000_1XRTT_v920.h"
#include "CSG_ProximityIndicationParameters_r9.h"
#include "NeighCellSI_AcquisitionParameters_r9.h"
#include "SON_Parameters_r9.h"
#include "UE_EUTRA_Capability_v940_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class UE_EUTRA_Capability_v920_IEs
{
public:
    UE_EUTRA_Capability_v920_IEs() : phyLayerParameters_v920_present{false}, interRAT_ParametersGERAN_v920_present{false}, interRAT_ParametersUTRA_v920_present{false}, interRAT_ParametersCDMA2000_v920_present{false}, deviceType_r9_present{false}, csg_ProximityIndicationParameters_r9_present{false}, neighCellSI_AcquisitionParameters_r9_present{false}, son_Parameters_r9_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // phyLayerParameters-v920
public:
    PhyLayerParameters_v920* phyLayerParameters_v920_Set();
    int phyLayerParameters_v920_Set(PhyLayerParameters_v920 &value);
    const PhyLayerParameters_v920& phyLayerParameters_v920_Get() const;
    std::string phyLayerParameters_v920_ToString(uint32_t indent) const;
    std::string phyLayerParameters_v920_ToStringNoNewLines() const;
    int phyLayerParameters_v920_Clear();
    bool phyLayerParameters_v920_IsPresent() const;
private:
    bool phyLayerParameters_v920_present;
    PhyLayerParameters_v920 phyLayerParameters_v920;

    // interRAT-ParametersGERAN-v920
public:
    IRAT_ParametersGERAN_v920* interRAT_ParametersGERAN_v920_Set();
    int interRAT_ParametersGERAN_v920_Set(IRAT_ParametersGERAN_v920 &value);
    const IRAT_ParametersGERAN_v920& interRAT_ParametersGERAN_v920_Get() const;
    std::string interRAT_ParametersGERAN_v920_ToString(uint32_t indent) const;
    std::string interRAT_ParametersGERAN_v920_ToStringNoNewLines() const;
    int interRAT_ParametersGERAN_v920_Clear();
    bool interRAT_ParametersGERAN_v920_IsPresent() const;
private:
    bool interRAT_ParametersGERAN_v920_present;
    IRAT_ParametersGERAN_v920 interRAT_ParametersGERAN_v920;

    // interRAT-ParametersUTRA-v920
public:
    IRAT_ParametersUTRA_v920* interRAT_ParametersUTRA_v920_Set();
    int interRAT_ParametersUTRA_v920_Set(IRAT_ParametersUTRA_v920 &value);
    const IRAT_ParametersUTRA_v920& interRAT_ParametersUTRA_v920_Get() const;
    std::string interRAT_ParametersUTRA_v920_ToString(uint32_t indent) const;
    std::string interRAT_ParametersUTRA_v920_ToStringNoNewLines() const;
    int interRAT_ParametersUTRA_v920_Clear();
    bool interRAT_ParametersUTRA_v920_IsPresent() const;
private:
    bool interRAT_ParametersUTRA_v920_present;
    IRAT_ParametersUTRA_v920 interRAT_ParametersUTRA_v920;

    // interRAT-ParametersCDMA2000-v920
public:
    IRAT_ParametersCDMA2000_1XRTT_v920* interRAT_ParametersCDMA2000_v920_Set();
    int interRAT_ParametersCDMA2000_v920_Set(IRAT_ParametersCDMA2000_1XRTT_v920 &value);
    const IRAT_ParametersCDMA2000_1XRTT_v920& interRAT_ParametersCDMA2000_v920_Get() const;
    std::string interRAT_ParametersCDMA2000_v920_ToString(uint32_t indent) const;
    std::string interRAT_ParametersCDMA2000_v920_ToStringNoNewLines() const;
    int interRAT_ParametersCDMA2000_v920_Clear();
    bool interRAT_ParametersCDMA2000_v920_IsPresent() const;
private:
    bool interRAT_ParametersCDMA2000_v920_present;
    IRAT_ParametersCDMA2000_1XRTT_v920 interRAT_ParametersCDMA2000_v920;

    // deviceType-r9
public:
    enum deviceType_r9_Enum {
        k_deviceType_r9_noBenFromBatConsumpOpt = 0,
    };
    int deviceType_r9_Pack(std::vector<uint8_t> &bits);
    int deviceType_r9_Unpack(std::vector<uint8_t> bits);
    int deviceType_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    deviceType_r9_Enum deviceType_r9_Value() const;
    int deviceType_r9_SetValue(deviceType_r9_Enum value);
    int deviceType_r9_SetValue(std::string value);
    std::string deviceType_r9_ValueToString(deviceType_r9_Enum value) const;
    uint64_t deviceType_r9_NumberOfValues() const;
    std::string deviceType_r9_ToString(uint32_t indent) const;
    std::string deviceType_r9_ToStringNoNewLines() const;
    int deviceType_r9_Clear();
    bool deviceType_r9_IsPresent() const;
private:
    bool deviceType_r9_present;
    deviceType_r9_Enum deviceType_r9_internal_value;

    // csg-ProximityIndicationParameters-r9
public:
    CSG_ProximityIndicationParameters_r9* csg_ProximityIndicationParameters_r9_Set();
    int csg_ProximityIndicationParameters_r9_Set(CSG_ProximityIndicationParameters_r9 &value);
    const CSG_ProximityIndicationParameters_r9& csg_ProximityIndicationParameters_r9_Get() const;
    std::string csg_ProximityIndicationParameters_r9_ToString(uint32_t indent) const;
    std::string csg_ProximityIndicationParameters_r9_ToStringNoNewLines() const;
    int csg_ProximityIndicationParameters_r9_Clear();
    bool csg_ProximityIndicationParameters_r9_IsPresent() const;
private:
    bool csg_ProximityIndicationParameters_r9_present;
    CSG_ProximityIndicationParameters_r9 csg_ProximityIndicationParameters_r9;

    // neighCellSI-AcquisitionParameters-r9
public:
    NeighCellSI_AcquisitionParameters_r9* neighCellSI_AcquisitionParameters_r9_Set();
    int neighCellSI_AcquisitionParameters_r9_Set(NeighCellSI_AcquisitionParameters_r9 &value);
    const NeighCellSI_AcquisitionParameters_r9& neighCellSI_AcquisitionParameters_r9_Get() const;
    std::string neighCellSI_AcquisitionParameters_r9_ToString(uint32_t indent) const;
    std::string neighCellSI_AcquisitionParameters_r9_ToStringNoNewLines() const;
    int neighCellSI_AcquisitionParameters_r9_Clear();
    bool neighCellSI_AcquisitionParameters_r9_IsPresent() const;
private:
    bool neighCellSI_AcquisitionParameters_r9_present;
    NeighCellSI_AcquisitionParameters_r9 neighCellSI_AcquisitionParameters_r9;

    // son-Parameters-r9
public:
    SON_Parameters_r9* son_Parameters_r9_Set();
    int son_Parameters_r9_Set(SON_Parameters_r9 &value);
    const SON_Parameters_r9& son_Parameters_r9_Get() const;
    std::string son_Parameters_r9_ToString(uint32_t indent) const;
    std::string son_Parameters_r9_ToStringNoNewLines() const;
    int son_Parameters_r9_Clear();
    bool son_Parameters_r9_IsPresent() const;
private:
    bool son_Parameters_r9_present;
    SON_Parameters_r9 son_Parameters_r9;

    // nonCriticalExtension
public:
    UE_EUTRA_Capability_v940_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(UE_EUTRA_Capability_v940_IEs &value);
    const UE_EUTRA_Capability_v940_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    UE_EUTRA_Capability_v940_IEs nonCriticalExtension;

};

#endif
