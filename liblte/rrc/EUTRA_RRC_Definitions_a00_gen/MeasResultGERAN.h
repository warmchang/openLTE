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

#ifndef __MeasResultGERAN_H__
#define __MeasResultGERAN_H__

#include "CarrierFreqGERAN.h"
#include "PhysCellIdGERAN.h"
#include "CellGlobalIdGERAN.h"

#include <array>
#include <cstdint>
#include <vector>

class MeasResultGERAN
{
public:
    MeasResultGERAN() : carrierFreq_present{false}, physCellId_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // carrierFreq
public:
    CarrierFreqGERAN* carrierFreq_Set();
    int carrierFreq_Set(CarrierFreqGERAN &value);
    const CarrierFreqGERAN& carrierFreq_Get() const;
    std::string carrierFreq_ToString(uint32_t indent) const;
    std::string carrierFreq_ToStringNoNewLines() const;
    int carrierFreq_Clear();
    bool carrierFreq_IsPresent() const;
private:
    bool carrierFreq_present;
    CarrierFreqGERAN carrierFreq;

    // physCellId
public:
    PhysCellIdGERAN* physCellId_Set();
    int physCellId_Set(PhysCellIdGERAN &value);
    const PhysCellIdGERAN& physCellId_Get() const;
    std::string physCellId_ToString(uint32_t indent) const;
    std::string physCellId_ToStringNoNewLines() const;
    int physCellId_Clear();
    bool physCellId_IsPresent() const;
private:
    bool physCellId_present;
    PhysCellIdGERAN physCellId;

    // cgi-Info
public:
    class cgi_Info
    {
    public:
        cgi_Info() : present{false}, cellGlobalId_present{false}, routingAreaCode_present{false} {};
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
        CellGlobalIdGERAN* cellGlobalId_Set();
        int cellGlobalId_Set(CellGlobalIdGERAN &value);
        const CellGlobalIdGERAN& cellGlobalId_Get() const;
        std::string cellGlobalId_ToString(uint32_t indent) const;
        std::string cellGlobalId_ToStringNoNewLines() const;
        int cellGlobalId_Clear();
        bool cellGlobalId_IsPresent() const;
    private:
        bool cellGlobalId_present;
        CellGlobalIdGERAN cellGlobalId;

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

    };

    cgi_Info cgi_Info_value;

    // measResult
public:
    class measResult
    {
    public:
        measResult() : rssi_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // rssi
    public:
        int rssi_Pack(std::vector<uint8_t> &bits);
        int rssi_Unpack(std::vector<uint8_t> bits);
        int rssi_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t rssi_Value() const;
        int rssi_SetValue(int64_t value);
        std::string rssi_ToString(uint32_t indent) const;
        std::string rssi_ToStringNoNewLines() const;
        int rssi_Clear();
        bool rssi_IsPresent() const;
    private:
        bool rssi_present;
        int64_t rssi_internal_value;

    };

    measResult measResult_value;

};

#endif
