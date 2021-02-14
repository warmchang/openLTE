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

#ifndef __MeasResultCDMA2000_H__
#define __MeasResultCDMA2000_H__

#include "PhysCellIdCDMA2000.h"
#include "CellGlobalIdCDMA2000.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasResultCDMA2000
{
public:
    MeasResultCDMA2000() : physCellId_present{false}, cgi_Info_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // physCellId
public:
    PhysCellIdCDMA2000* physCellId_Set();
    int physCellId_Set(PhysCellIdCDMA2000 &value);
    const PhysCellIdCDMA2000& physCellId_Get() const;
    std::string physCellId_ToString(uint32_t indent) const;
    std::string physCellId_ToStringNoNewLines() const;
    int physCellId_Clear();
    bool physCellId_IsPresent() const;
private:
    bool physCellId_present;
    PhysCellIdCDMA2000 physCellId;

    // cgi-Info
public:
    CellGlobalIdCDMA2000* cgi_Info_Set();
    int cgi_Info_Set(CellGlobalIdCDMA2000 &value);
    const CellGlobalIdCDMA2000& cgi_Info_Get() const;
    std::string cgi_Info_ToString(uint32_t indent) const;
    std::string cgi_Info_ToStringNoNewLines() const;
    int cgi_Info_Clear();
    bool cgi_Info_IsPresent() const;
private:
    bool cgi_Info_present;
    CellGlobalIdCDMA2000 cgi_Info;

    // measResult
public:
    class measResult
    {
    public:
        measResult() : pilotPnPhase_present{false}, pilotStrength_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // pilotPnPhase
    public:
        int pilotPnPhase_Pack(std::vector<uint8_t> &bits);
        int pilotPnPhase_Unpack(std::vector<uint8_t> bits);
        int pilotPnPhase_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t pilotPnPhase_Value() const;
        int pilotPnPhase_SetValue(int64_t value);
        std::string pilotPnPhase_ToString(uint32_t indent) const;
        std::string pilotPnPhase_ToStringNoNewLines() const;
        int pilotPnPhase_Clear();
        bool pilotPnPhase_IsPresent() const;
    private:
        bool pilotPnPhase_present;
        int64_t pilotPnPhase_internal_value;

        // pilotStrength
    public:
        int pilotStrength_Pack(std::vector<uint8_t> &bits);
        int pilotStrength_Unpack(std::vector<uint8_t> bits);
        int pilotStrength_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t pilotStrength_Value() const;
        int pilotStrength_SetValue(int64_t value);
        std::string pilotStrength_ToString(uint32_t indent) const;
        std::string pilotStrength_ToStringNoNewLines() const;
        int pilotStrength_Clear();
        bool pilotStrength_IsPresent() const;
    private:
        bool pilotStrength_present;
        int64_t pilotStrength_internal_value;

    };

    measResult measResult_value;

};

#endif
