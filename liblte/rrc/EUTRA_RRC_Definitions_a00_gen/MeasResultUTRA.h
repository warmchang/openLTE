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

#ifndef __MeasResultUTRA_H__
#define __MeasResultUTRA_H__

#include "PhysCellIdUTRA_FDD.h"
#include "PhysCellIdUTRA_TDD.h"
#include "CellGlobalIdUTRA.h"
#include "PLMN_IdentityList2.h"
#include "AdditionalSI_Info_r9.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasResultUTRA
{
public:
    MeasResultUTRA() : physCellId_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // physCellId
public:
    enum physCellId_Enum {
        k_physCellId_fdd = 0,
        k_physCellId_tdd,
    };
    int physCellId_Pack(std::vector<uint8_t> &bits);
    int physCellId_Unpack(std::vector<uint8_t> bits);
    int physCellId_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    physCellId_Enum physCellId_Choice() const;
    int physCellId_SetChoice(physCellId_Enum choice);
    std::string physCellId_ChoiceToString(physCellId_Enum value) const;
    uint64_t physCellId_NumberOfChoices() const;
    std::string physCellId_ToString(uint32_t indent) const;
    std::string physCellId_ToStringNoNewLines() const;
    int physCellId_Clear();
    bool physCellId_IsPresent() const;
private:
    bool physCellId_present;
    physCellId_Enum physCellId_internal_choice;

    // fdd
public:
    PhysCellIdUTRA_FDD* physCellId_fdd_Set();
    int physCellId_fdd_Set(PhysCellIdUTRA_FDD &value);
    const PhysCellIdUTRA_FDD& physCellId_fdd_Get() const;
    std::string physCellId_fdd_ToString(uint32_t indent) const;
    std::string physCellId_fdd_ToStringNoNewLines() const;
    int physCellId_fdd_Clear();
    bool physCellId_fdd_IsPresent() const;
private:
    bool physCellId_fdd_present;
    PhysCellIdUTRA_FDD physCellId_fdd;

    // tdd
public:
    PhysCellIdUTRA_TDD* physCellId_tdd_Set();
    int physCellId_tdd_Set(PhysCellIdUTRA_TDD &value);
    const PhysCellIdUTRA_TDD& physCellId_tdd_Get() const;
    std::string physCellId_tdd_ToString(uint32_t indent) const;
    std::string physCellId_tdd_ToStringNoNewLines() const;
    int physCellId_tdd_Clear();
    bool physCellId_tdd_IsPresent() const;
private:
    bool physCellId_tdd_present;
    PhysCellIdUTRA_TDD physCellId_tdd;


    // cgi-Info
public:
    class cgi_Info
    {
    public:
        cgi_Info() : present{false}, cellGlobalId_present{false}, locationAreaCode_present{false}, routingAreaCode_present{false}, plmn_IdentityList_present{false} {};
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
        CellGlobalIdUTRA* cellGlobalId_Set();
        int cellGlobalId_Set(CellGlobalIdUTRA &value);
        const CellGlobalIdUTRA& cellGlobalId_Get() const;
        std::string cellGlobalId_ToString(uint32_t indent) const;
        std::string cellGlobalId_ToStringNoNewLines() const;
        int cellGlobalId_Clear();
        bool cellGlobalId_IsPresent() const;
    private:
        bool cellGlobalId_present;
        CellGlobalIdUTRA cellGlobalId;

        // locationAreaCode
    public:
        int locationAreaCode_Pack(std::vector<uint8_t> &bits);
        int locationAreaCode_Unpack(std::vector<uint8_t> bits);
        int locationAreaCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint16_t locationAreaCode_Value() const;
        int locationAreaCode_SetValue(uint16_t value);
        std::string locationAreaCode_ToString(uint32_t indent) const;
        std::string locationAreaCode_ToStringNoNewLines() const;
        int locationAreaCode_Clear();
        bool locationAreaCode_IsPresent() const;
    private:
        bool locationAreaCode_present;
        uint16_t locationAreaCode_internal_value;

        // routingAreaCode
    public:
        int routingAreaCode_Pack(std::vector<uint8_t> &bits);
        int routingAreaCode_Unpack(std::vector<uint8_t> bits);
        int routingAreaCode_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        uint8_t routingAreaCode_Value() const;
        int routingAreaCode_SetValue(uint8_t value);
        std::string routingAreaCode_ToString(uint32_t indent) const;
        std::string routingAreaCode_ToStringNoNewLines() const;
        int routingAreaCode_Clear();
        bool routingAreaCode_IsPresent() const;
    private:
        bool routingAreaCode_present;
        uint8_t routingAreaCode_internal_value;

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
        measResult() : utra_RSCP_present{false}, utra_EcN0_present{false}, additionalSI_Info_r9_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // utra-RSCP
    public:
        int utra_RSCP_Pack(std::vector<uint8_t> &bits);
        int utra_RSCP_Unpack(std::vector<uint8_t> bits);
        int utra_RSCP_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t utra_RSCP_Value() const;
        int utra_RSCP_SetValue(int64_t value);
        std::string utra_RSCP_ToString(uint32_t indent) const;
        std::string utra_RSCP_ToStringNoNewLines() const;
        int utra_RSCP_Clear();
        bool utra_RSCP_IsPresent() const;
    private:
        bool utra_RSCP_present;
        int64_t utra_RSCP_internal_value;

        // utra-EcN0
    public:
        int utra_EcN0_Pack(std::vector<uint8_t> &bits);
        int utra_EcN0_Unpack(std::vector<uint8_t> bits);
        int utra_EcN0_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t utra_EcN0_Value() const;
        int utra_EcN0_SetValue(int64_t value);
        std::string utra_EcN0_ToString(uint32_t indent) const;
        std::string utra_EcN0_ToStringNoNewLines() const;
        int utra_EcN0_Clear();
        bool utra_EcN0_IsPresent() const;
    private:
        bool utra_EcN0_present;
        int64_t utra_EcN0_internal_value;

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
