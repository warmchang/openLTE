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

#ifndef __Paging_H__
#define __Paging_H__

#include "PagingRecordList.h"
#include "Paging_v890_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class Paging
{
public:
    Paging() : pagingRecordList_present{false}, systemInfoModification_present{false}, etws_Indication_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // pagingRecordList
public:
    PagingRecordList* pagingRecordList_Set();
    int pagingRecordList_Set(PagingRecordList &value);
    const PagingRecordList& pagingRecordList_Get() const;
    std::string pagingRecordList_ToString(uint32_t indent) const;
    std::string pagingRecordList_ToStringNoNewLines() const;
    int pagingRecordList_Clear();
    bool pagingRecordList_IsPresent() const;
private:
    bool pagingRecordList_present;
    PagingRecordList pagingRecordList;

    // systemInfoModification
public:
    enum systemInfoModification_Enum {
        k_systemInfoModification_true = 0,
    };
    int systemInfoModification_Pack(std::vector<uint8_t> &bits);
    int systemInfoModification_Unpack(std::vector<uint8_t> bits);
    int systemInfoModification_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    systemInfoModification_Enum systemInfoModification_Value() const;
    int systemInfoModification_SetValue(systemInfoModification_Enum value);
    int systemInfoModification_SetValue(std::string value);
    std::string systemInfoModification_ValueToString(systemInfoModification_Enum value) const;
    uint64_t systemInfoModification_NumberOfValues() const;
    std::string systemInfoModification_ToString(uint32_t indent) const;
    std::string systemInfoModification_ToStringNoNewLines() const;
    int systemInfoModification_Clear();
    bool systemInfoModification_IsPresent() const;
private:
    bool systemInfoModification_present;
    systemInfoModification_Enum systemInfoModification_internal_value;

    // etws-Indication
public:
    enum etws_Indication_Enum {
        k_etws_Indication_true = 0,
    };
    int etws_Indication_Pack(std::vector<uint8_t> &bits);
    int etws_Indication_Unpack(std::vector<uint8_t> bits);
    int etws_Indication_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    etws_Indication_Enum etws_Indication_Value() const;
    int etws_Indication_SetValue(etws_Indication_Enum value);
    int etws_Indication_SetValue(std::string value);
    std::string etws_Indication_ValueToString(etws_Indication_Enum value) const;
    uint64_t etws_Indication_NumberOfValues() const;
    std::string etws_Indication_ToString(uint32_t indent) const;
    std::string etws_Indication_ToStringNoNewLines() const;
    int etws_Indication_Clear();
    bool etws_Indication_IsPresent() const;
private:
    bool etws_Indication_present;
    etws_Indication_Enum etws_Indication_internal_value;

    // nonCriticalExtension
public:
    Paging_v890_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(Paging_v890_IEs &value);
    const Paging_v890_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    Paging_v890_IEs nonCriticalExtension;

};

#endif
