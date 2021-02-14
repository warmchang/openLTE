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

#ifndef __MeasResultEUTRA_H__
#define __MeasResultEUTRA_H__

#include "PhysCellId.h"
#include "CellGlobalIdEUTRA.h"
#include "TrackingAreaCode.h"
#include "PLMN_IdentityList2.h"
#include "RSRP_Range.h"
#include "RSRQ_Range.h"
#include "AdditionalSI_Info_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasResultEUTRA
{
public:
    MeasResultEUTRA() : physCellId_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // physCellId
public:
    PhysCellId* physCellId_Set();
    int physCellId_Set(PhysCellId &value);
    const PhysCellId& physCellId_Get() const;
    std::string physCellId_ToString(uint32_t indent) const;
    std::string physCellId_ToStringNoNewLines() const;
    int physCellId_Clear();
    bool physCellId_IsPresent() const;
private:
    bool physCellId_present;
    PhysCellId physCellId;

    // cgi-Info
public:
    class cgi_Info
    {
    public:
        cgi_Info() : present{false}, cellGlobalId_present{false}, trackingAreaCode_present{false}, plmn_IdentityList_present{false} {};
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

        // cellGlobalId
    public:
        CellGlobalIdEUTRA* cellGlobalId_Set();
        int cellGlobalId_Set(CellGlobalIdEUTRA &value);
        const CellGlobalIdEUTRA& cellGlobalId_Get() const;
        std::string cellGlobalId_ToString(uint32_t indent) const;
        std::string cellGlobalId_ToStringNoNewLines() const;
        int cellGlobalId_Clear();
        bool cellGlobalId_IsPresent() const;
    private:
        bool cellGlobalId_present;
        CellGlobalIdEUTRA cellGlobalId;

        // trackingAreaCode
    public:
        TrackingAreaCode* trackingAreaCode_Set();
        int trackingAreaCode_Set(TrackingAreaCode &value);
        const TrackingAreaCode& trackingAreaCode_Get() const;
        std::string trackingAreaCode_ToString(uint32_t indent) const;
        std::string trackingAreaCode_ToStringNoNewLines() const;
        int trackingAreaCode_Clear();
        bool trackingAreaCode_IsPresent() const;
    private:
        bool trackingAreaCode_present;
        TrackingAreaCode trackingAreaCode;

        // plmn-IdentityList
    public:
        PLMN_IdentityList2* plmn_IdentityList_Set();
        int plmn_IdentityList_Set(PLMN_IdentityList2 &value);
        const PLMN_IdentityList2& plmn_IdentityList_Get() const;
        std::string plmn_IdentityList_ToString(uint32_t indent) const;
        std::string plmn_IdentityList_ToStringNoNewLines() const;
        int plmn_IdentityList_Clear();
        bool plmn_IdentityList_IsPresent() const;
    private:
        bool plmn_IdentityList_present;
        PLMN_IdentityList2 plmn_IdentityList;

    };

    cgi_Info cgi_Info_value;

    // measResult
public:
    class measResult
    {
    public:
        measResult() : rsrpResult_present{false}, rsrqResult_present{false}, additionalSI_Info_r9_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // rsrpResult
    public:
        RSRP_Range* rsrpResult_Set();
        int rsrpResult_Set(RSRP_Range &value);
        const RSRP_Range& rsrpResult_Get() const;
        std::string rsrpResult_ToString(uint32_t indent) const;
        std::string rsrpResult_ToStringNoNewLines() const;
        int rsrpResult_Clear();
        bool rsrpResult_IsPresent() const;
    private:
        bool rsrpResult_present;
        RSRP_Range rsrpResult;

        // rsrqResult
    public:
        RSRQ_Range* rsrqResult_Set();
        int rsrqResult_Set(RSRQ_Range &value);
        const RSRQ_Range& rsrqResult_Get() const;
        std::string rsrqResult_ToString(uint32_t indent) const;
        std::string rsrqResult_ToStringNoNewLines() const;
        int rsrqResult_Clear();
        bool rsrqResult_IsPresent() const;
    private:
        bool rsrqResult_present;
        RSRQ_Range rsrqResult;

        // additionalSI-Info-r9
    public:
        AdditionalSI_Info_r9* additionalSI_Info_r9_Set();
        int additionalSI_Info_r9_Set(AdditionalSI_Info_r9 &value);
        const AdditionalSI_Info_r9& additionalSI_Info_r9_Get() const;
        std::string additionalSI_Info_r9_ToString(uint32_t indent) const;
        std::string additionalSI_Info_r9_ToStringNoNewLines() const;
        int additionalSI_Info_r9_Clear();
        bool additionalSI_Info_r9_IsPresent() const;
    private:
        bool additionalSI_Info_r9_present;
        AdditionalSI_Info_r9 additionalSI_Info_r9;

    };

    measResult measResult_value;

};

#endif
