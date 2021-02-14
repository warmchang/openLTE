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

#include "MeasObjectUTRA.h"

#include <cmath>

int MeasObjectUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(csg_allowedReportingCells_v930_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    if(!offsetFreq_IsPresent() || offsetFreq_Get().Value() == offsetFreq_GetDefault())
    {
        bits.push_back(0);
    }else{
        bits.push_back(1);
    }
    bits.push_back(cellsToRemoveList_IsPresent());
    bits.push_back(cellsToAddModList_IsPresent());
    bits.push_back(cellForWhichToReportCGI_IsPresent());

    // Fields
    {
        if(0 != carrierFreq.Pack(bits))
        {
            printf("MeasObjectUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(offsetFreq_IsPresent() || offsetFreq_Get().Value() != offsetFreq_GetDefault())
    {
        if(0 != offsetFreq.Pack(bits))
        {
            printf("MeasObjectUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(cellsToRemoveList_IsPresent())
    {
        if(0 != cellsToRemoveList.Pack(bits))
        {
            printf("MeasObjectUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(cellsToAddModList_IsPresent())
    {
        if(0 != cellsToAddModList_Pack(bits))
        {
            printf("MeasObjectUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_IsPresent())
    {
        if(0 != cellForWhichToReportCGI_Pack(bits))
        {
            printf("MeasObjectUTRA:: field pack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        // Number of extension fields
        if(0 < 64)
        {
            bits.push_back(0);
            for(uint32_t i=0; i<6; i++)
                bits.push_back((0 >> (6-i-1)) & 1);
        }else{
            printf("MeasObjectUTRA:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(csg_allowedReportingCells_v930_IsPresent());

        // Extension fields
        if(csg_allowedReportingCells_v930_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != csg_allowedReportingCells_v930.Pack(field_bits))
            {
                printf("MeasObjectUTRA:: field pack failure\n");
                return -1;
            }
            while((field_bits.size() % 8) != 0)
                field_bits.push_back(0);
            uint32_t N_octets = field_bits.size() / 8;
            uint32_t local_size_length = 0;
            uint32_t local_size = N_octets;
            if(local_size < 128)
            {
                bits.push_back(0);
                local_size_length = 7;
            }else if(local_size < 16383){
                bits.push_back(1);
                bits.push_back(0);
                local_size_length = 14;
            }else{
                bits.push_back(1);
                bits.push_back(1);
                uint32_t N_16k_blocks = local_size / 16383;
                for(uint32_t i=0; i<6; i++)
                    bits.push_back((N_16k_blocks >> (6-i-1)) & 1);
                local_size %= 16383;
                if(local_size < 128)
                {
                    bits.push_back(0);
                    local_size_length = 7;
                }else{
                    bits.push_back(1);
                    bits.push_back(0);
                    local_size_length = 14;
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                bits.push_back((local_size >> (local_size_length-i-1)) & 1);
            for(auto b : field_bits)
                bits.push_back(b);
        }
    }
    return 0;
}

int MeasObjectUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasObjectUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectUTRA::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectUTRA::Unpack() index out of bounds for optional indiator offsetFreq\n");
        return -1;
    }
    offsetFreq_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectUTRA::Unpack() index out of bounds for optional indiator cellsToRemoveList\n");
        return -1;
    }
    cellsToRemoveList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectUTRA::Unpack() index out of bounds for optional indiator cellsToAddModList\n");
        return -1;
    }
    cellsToAddModList_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectUTRA::Unpack() index out of bounds for optional indiator cellForWhichToReportCGI\n");
        return -1;
    }
    cellForWhichToReportCGI_present = bits[idx++];

    // Fields
    {
        if(0 != carrierFreq.Unpack(bits, idx))
        {
            printf("MeasObjectUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != offsetFreq.Unpack(bits, idx))
        {
            printf("MeasObjectUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(cellsToRemoveList_present)
    {
        if(0 != cellsToRemoveList.Unpack(bits, idx))
        {
            printf("MeasObjectUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(cellsToAddModList_present)
    {
        if(0 != cellsToAddModList_Unpack(bits, idx))
        {
            printf("MeasObjectUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_present)
    {
        if(0 != cellForWhichToReportCGI_Unpack(bits, idx))
        {
            printf("MeasObjectUTRA:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("MeasObjectUTRA::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("MeasObjectUTRA:: Extension list size too large failure\n");
            return -1;
        }
        uint32_t N_ext_fields = 0;
        for(uint32_t i=0; i<6; i++)
            N_ext_fields |= bits[idx++] << (6-i-1);
        N_ext_fields++;

        // Extension field presence indicators
        uint32_t opt_ind_count = 0;
        if(opt_ind_count++ < N_ext_fields)
        {
            if((idx + 1) > bits.size())
            {
                printf("MeasObjectUTRA::Unpack() index out of bounds for optional indiator csg_allowedReportingCells_v930\n");
                return -1;
            }
            csg_allowedReportingCells_v930_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("MeasObjectUTRA::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(csg_allowedReportingCells_v930_present)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
                    if(0 == bits[idx++])
                    {
                        local_size_length = 7;
                    }else{
                        idx++;
                        local_size_length = 14;
                    }
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                N_octets |= bits[idx++] << (local_size_length-i-1);
            uint32_t orig_idx = idx;
            if(0 != csg_allowedReportingCells_v930.Unpack(bits, idx))
            {
                printf("MeasObjectUTRA:: field unpack failure\n");
                return -1;
            }
            idx = orig_idx + (N_octets * 8);
        }
        for(uint32_t i=1; i<N_ext_fields; i++)
        {
            uint32_t local_size_length = 0;
            uint32_t N_octets = 0;
            if(0 == bits[idx++])
            {
                local_size_length = 7;
            }else{
                if(0 == bits[idx++])
                {
                    local_size_length = 14;
                }else{
                    for(uint32_t i=0; i<6; i++)
                        N_octets |= bits[idx++] << (6-i-1);
                    N_octets *= 16383;
                    if(0 == bits[idx++])
                    {
                        local_size_length = 7;
                    }else{
                        idx++;
                        local_size_length = 14;
                    }
                }
            }
            for(uint32_t i=0; i<local_size_length; i++)
                N_octets |= bits[idx++] << (local_size_length-i-1);
        if((idx + (N_octets * 8)) > bits.size())
        {
            printf("MeasObjectUTRA::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string MeasObjectUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasObjectUTRA:\n";
    out += carrierFreq_ToString(indent+1);
    out += offsetFreq_ToString(indent+1);
    if(cellsToRemoveList_IsPresent())
        out += cellsToRemoveList_ToString(indent+1);
    if(cellsToAddModList_IsPresent())
        out += cellsToAddModList_ToString(indent+1);
    if(cellForWhichToReportCGI_IsPresent())
        out += cellForWhichToReportCGI_ToString(indent+1);
    if(csg_allowedReportingCells_v930_IsPresent())
        out += csg_allowedReportingCells_v930_ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::ToStringNoNewLines() const
{
    std::string out = "MeasObjectUTRA:";
    out += carrierFreq_ToStringNoNewLines();
    out += offsetFreq_ToStringNoNewLines();
    if(cellsToRemoveList_IsPresent())
        out += cellsToRemoveList_ToStringNoNewLines();
    if(cellsToAddModList_IsPresent())
        out += cellsToAddModList_ToStringNoNewLines();
    if(cellForWhichToReportCGI_IsPresent())
        out += cellForWhichToReportCGI_ToStringNoNewLines();
    if(csg_allowedReportingCells_v930_IsPresent())
        out += csg_allowedReportingCells_v930_ToStringNoNewLines();
    return out;
}

ARFCN_ValueUTRA* MeasObjectUTRA::carrierFreq_Set()
{
    carrierFreq_present = true;
    return &carrierFreq;
}

int MeasObjectUTRA::carrierFreq_Set(ARFCN_ValueUTRA &value)
{
    carrierFreq_present = true;
    carrierFreq = value;
    return 0;
}

const ARFCN_ValueUTRA& MeasObjectUTRA::carrierFreq_Get() const
{
    return carrierFreq;
}

std::string MeasObjectUTRA::carrierFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "carrierFreq:\n";
    out += carrierFreq.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::carrierFreq_ToStringNoNewLines() const
{
    std::string out = "carrierFreq:";
    out += carrierFreq.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::carrierFreq_Clear()
{
    carrierFreq_present = false;
    return 0;
}

bool MeasObjectUTRA::carrierFreq_IsPresent() const
{
    return carrierFreq_present;
}

Q_OffsetRangeInterRAT* MeasObjectUTRA::offsetFreq_Set()
{
    offsetFreq_present = true;
    return &offsetFreq;
}

int MeasObjectUTRA::offsetFreq_Set(Q_OffsetRangeInterRAT &value)
{
    offsetFreq_present = true;
    offsetFreq = value;
    return 0;
}

const Q_OffsetRangeInterRAT& MeasObjectUTRA::offsetFreq_Get() const
{
    return offsetFreq;
}

int64_t MeasObjectUTRA::offsetFreq_GetDefault() const
{
    return 0;
}

std::string MeasObjectUTRA::offsetFreq_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "offsetFreq:\n";
    out += offsetFreq.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::offsetFreq_ToStringNoNewLines() const
{
    std::string out = "offsetFreq:";
    out += offsetFreq.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::offsetFreq_Clear()
{
    offsetFreq_present = false;
    return 0;
}

bool MeasObjectUTRA::offsetFreq_IsPresent() const
{
    return offsetFreq_present;
}

CellIndexList* MeasObjectUTRA::cellsToRemoveList_Set()
{
    cellsToRemoveList_present = true;
    return &cellsToRemoveList;
}

int MeasObjectUTRA::cellsToRemoveList_Set(CellIndexList &value)
{
    cellsToRemoveList_present = true;
    cellsToRemoveList = value;
    return 0;
}

const CellIndexList& MeasObjectUTRA::cellsToRemoveList_Get() const
{
    return cellsToRemoveList;
}

std::string MeasObjectUTRA::cellsToRemoveList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellsToRemoveList:\n";
    out += cellsToRemoveList.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::cellsToRemoveList_ToStringNoNewLines() const
{
    std::string out = "cellsToRemoveList:";
    out += cellsToRemoveList.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::cellsToRemoveList_Clear()
{
    cellsToRemoveList_present = false;
    return 0;
}

bool MeasObjectUTRA::cellsToRemoveList_IsPresent() const
{
    return cellsToRemoveList_present;
}

int MeasObjectUTRA::cellsToAddModList_Pack(std::vector<uint8_t> &bits)
{
    if(!cellsToAddModList_present)
    {
        printf("MeasObjectUTRA::cellsToAddModList_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((cellsToAddModList_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(cellsToAddModList_internal_choice == k_cellsToAddModList_cellsToAddModListUTRA_FDD)
    {
        if(0 != cellsToAddModList_cellsToAddModListUTRA_FDD.Pack(bits))
        {
            printf("MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_FDD pack failure\n");
            return -1;
        }
    }
    if(cellsToAddModList_internal_choice == k_cellsToAddModList_cellsToAddModListUTRA_TDD)
    {
        if(0 != cellsToAddModList_cellsToAddModListUTRA_TDD.Pack(bits))
        {
            printf("MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_TDD pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasObjectUTRA::cellsToAddModList_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellsToAddModList_Unpack(bits, idx);
}

int MeasObjectUTRA::cellsToAddModList_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectUTRA::cellsToAddModList_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MeasObjectUTRA::cellsToAddModList_Enum)packed_val > k_cellsToAddModList_cellsToAddModListUTRA_TDD)
    {
        printf("MeasObjectUTRA::cellsToAddModList_Unpack() choice range failure\n");
        return -1;
    }
    cellsToAddModList_internal_choice = (MeasObjectUTRA::cellsToAddModList_Enum)packed_val;
    cellsToAddModList_present = true;

    // Fields
    if(cellsToAddModList_internal_choice == k_cellsToAddModList_cellsToAddModListUTRA_FDD)
    {
        if(0 != cellsToAddModList_cellsToAddModListUTRA_FDD.Unpack(bits, idx))
        {
            printf("MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_FDD unpack failure\n");
            return -1;
        }
    }
    if(cellsToAddModList_internal_choice == k_cellsToAddModList_cellsToAddModListUTRA_TDD)
    {
        if(0 != cellsToAddModList_cellsToAddModListUTRA_TDD.Unpack(bits, idx))
        {
            printf("MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_TDD unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MeasObjectUTRA::cellsToAddModList_Enum MeasObjectUTRA::cellsToAddModList_Choice() const
{
    if(cellsToAddModList_present)
        return cellsToAddModList_internal_choice;
    return (MeasObjectUTRA::cellsToAddModList_Enum)0;
}

int MeasObjectUTRA::cellsToAddModList_SetChoice(MeasObjectUTRA::cellsToAddModList_Enum choice)
{
    cellsToAddModList_internal_choice = choice;
    cellsToAddModList_present = true;
    return 0;
}

std::string MeasObjectUTRA::cellsToAddModList_ChoiceToString(cellsToAddModList_Enum value) const
{
    if(k_cellsToAddModList_cellsToAddModListUTRA_FDD == value)
        return "cellsToAddModList_cellsToAddModListUTRA_FDD";
    if(k_cellsToAddModList_cellsToAddModListUTRA_TDD == value)
        return "cellsToAddModList_cellsToAddModListUTRA_TDD";
    return "";
}

uint64_t MeasObjectUTRA::cellsToAddModList_NumberOfChoices() const
{
    return 2;
}

std::string MeasObjectUTRA::cellsToAddModList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellsToAddModList = " + cellsToAddModList_ChoiceToString(cellsToAddModList_internal_choice) + ":\n";
    if(cellsToAddModList_internal_choice == k_cellsToAddModList_cellsToAddModListUTRA_FDD)
        out += cellsToAddModList_cellsToAddModListUTRA_FDD.ToString(indent+1);
    if(cellsToAddModList_internal_choice == k_cellsToAddModList_cellsToAddModListUTRA_TDD)
        out += cellsToAddModList_cellsToAddModListUTRA_TDD.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::cellsToAddModList_ToStringNoNewLines() const
{
    std::string out = "cellsToAddModList=" + cellsToAddModList_ChoiceToString(cellsToAddModList_internal_choice) + ",";
    if(cellsToAddModList_internal_choice == k_cellsToAddModList_cellsToAddModListUTRA_FDD)
        out += cellsToAddModList_cellsToAddModListUTRA_FDD.ToStringNoNewLines();
    if(cellsToAddModList_internal_choice == k_cellsToAddModList_cellsToAddModListUTRA_TDD)
        out += cellsToAddModList_cellsToAddModListUTRA_TDD.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::cellsToAddModList_Clear()
{
    cellsToAddModList_present = false;
    return 0;
}

bool MeasObjectUTRA::cellsToAddModList_IsPresent() const
{
    return cellsToAddModList_present;
}

CellsToAddModListUTRA_FDD* MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_FDD_Set()
{
    cellsToAddModList_cellsToAddModListUTRA_FDD_present = true;
    return &cellsToAddModList_cellsToAddModListUTRA_FDD;
}

int MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_FDD_Set(CellsToAddModListUTRA_FDD &value)
{
    cellsToAddModList_cellsToAddModListUTRA_FDD_present = true;
    cellsToAddModList_cellsToAddModListUTRA_FDD = value;
    return 0;
}

const CellsToAddModListUTRA_FDD& MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_FDD_Get() const
{
    return cellsToAddModList_cellsToAddModListUTRA_FDD;
}

std::string MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_FDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellsToAddModListUTRA_FDD:\n";
    out += cellsToAddModList_cellsToAddModListUTRA_FDD.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_FDD_ToStringNoNewLines() const
{
    std::string out = "cellsToAddModListUTRA_FDD:";
    out += cellsToAddModList_cellsToAddModListUTRA_FDD.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_FDD_Clear()
{
    cellsToAddModList_cellsToAddModListUTRA_FDD_present = false;
    return 0;
}

bool MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_FDD_IsPresent() const
{
    return cellsToAddModList_cellsToAddModListUTRA_FDD_present;
}

CellsToAddModListUTRA_TDD* MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_TDD_Set()
{
    cellsToAddModList_cellsToAddModListUTRA_TDD_present = true;
    return &cellsToAddModList_cellsToAddModListUTRA_TDD;
}

int MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_TDD_Set(CellsToAddModListUTRA_TDD &value)
{
    cellsToAddModList_cellsToAddModListUTRA_TDD_present = true;
    cellsToAddModList_cellsToAddModListUTRA_TDD = value;
    return 0;
}

const CellsToAddModListUTRA_TDD& MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_TDD_Get() const
{
    return cellsToAddModList_cellsToAddModListUTRA_TDD;
}

std::string MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_TDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellsToAddModListUTRA_TDD:\n";
    out += cellsToAddModList_cellsToAddModListUTRA_TDD.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_TDD_ToStringNoNewLines() const
{
    std::string out = "cellsToAddModListUTRA_TDD:";
    out += cellsToAddModList_cellsToAddModListUTRA_TDD.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_TDD_Clear()
{
    cellsToAddModList_cellsToAddModListUTRA_TDD_present = false;
    return 0;
}

bool MeasObjectUTRA::cellsToAddModList_cellsToAddModListUTRA_TDD_IsPresent() const
{
    return cellsToAddModList_cellsToAddModListUTRA_TDD_present;
}

int MeasObjectUTRA::cellForWhichToReportCGI_Pack(std::vector<uint8_t> &bits)
{
    if(!cellForWhichToReportCGI_present)
    {
        printf("MeasObjectUTRA::cellForWhichToReportCGI_Pack() presence failure\n");
        return -1;
    }
    // Extension indicator

    // Choice
    for(uint32_t i=0; i<1; i++)
        bits.push_back((cellForWhichToReportCGI_internal_choice >> (1-i-1)) & 1);

    // Fields
    if(cellForWhichToReportCGI_internal_choice == k_cellForWhichToReportCGI_utra_FDD)
    {
        if(0 != cellForWhichToReportCGI_utra_FDD.Pack(bits))
        {
            printf("MeasObjectUTRA::cellForWhichToReportCGI_utra_FDD pack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_internal_choice == k_cellForWhichToReportCGI_utra_TDD)
    {
        if(0 != cellForWhichToReportCGI_utra_TDD.Pack(bits))
        {
            printf("MeasObjectUTRA::cellForWhichToReportCGI_utra_TDD pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasObjectUTRA::cellForWhichToReportCGI_Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return cellForWhichToReportCGI_Unpack(bits, idx);
}

int MeasObjectUTRA::cellForWhichToReportCGI_Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Choice
    uint32_t packed_val = 0;
    if((idx + 1) > bits.size())
    {
        printf("MeasObjectUTRA::cellForWhichToReportCGI_Unpack() index out of bounds for choice\n");
        return -1;
    }
    for(uint32_t i=0; i<1; i++)
        packed_val |= bits[idx++] << (1-i-1);

    if((MeasObjectUTRA::cellForWhichToReportCGI_Enum)packed_val > k_cellForWhichToReportCGI_utra_TDD)
    {
        printf("MeasObjectUTRA::cellForWhichToReportCGI_Unpack() choice range failure\n");
        return -1;
    }
    cellForWhichToReportCGI_internal_choice = (MeasObjectUTRA::cellForWhichToReportCGI_Enum)packed_val;
    cellForWhichToReportCGI_present = true;

    // Fields
    if(cellForWhichToReportCGI_internal_choice == k_cellForWhichToReportCGI_utra_FDD)
    {
        if(0 != cellForWhichToReportCGI_utra_FDD.Unpack(bits, idx))
        {
            printf("MeasObjectUTRA::cellForWhichToReportCGI_utra_FDD unpack failure\n");
            return -1;
        }
    }
    if(cellForWhichToReportCGI_internal_choice == k_cellForWhichToReportCGI_utra_TDD)
    {
        if(0 != cellForWhichToReportCGI_utra_TDD.Unpack(bits, idx))
        {
            printf("MeasObjectUTRA::cellForWhichToReportCGI_utra_TDD unpack failure\n");
            return -1;
        }
    }
    return 0;
}

MeasObjectUTRA::cellForWhichToReportCGI_Enum MeasObjectUTRA::cellForWhichToReportCGI_Choice() const
{
    if(cellForWhichToReportCGI_present)
        return cellForWhichToReportCGI_internal_choice;
    return (MeasObjectUTRA::cellForWhichToReportCGI_Enum)0;
}

int MeasObjectUTRA::cellForWhichToReportCGI_SetChoice(MeasObjectUTRA::cellForWhichToReportCGI_Enum choice)
{
    cellForWhichToReportCGI_internal_choice = choice;
    cellForWhichToReportCGI_present = true;
    return 0;
}

std::string MeasObjectUTRA::cellForWhichToReportCGI_ChoiceToString(cellForWhichToReportCGI_Enum value) const
{
    if(k_cellForWhichToReportCGI_utra_FDD == value)
        return "cellForWhichToReportCGI_utra_FDD";
    if(k_cellForWhichToReportCGI_utra_TDD == value)
        return "cellForWhichToReportCGI_utra_TDD";
    return "";
}

uint64_t MeasObjectUTRA::cellForWhichToReportCGI_NumberOfChoices() const
{
    return 2;
}

std::string MeasObjectUTRA::cellForWhichToReportCGI_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellForWhichToReportCGI = " + cellForWhichToReportCGI_ChoiceToString(cellForWhichToReportCGI_internal_choice) + ":\n";
    if(cellForWhichToReportCGI_internal_choice == k_cellForWhichToReportCGI_utra_FDD)
        out += cellForWhichToReportCGI_utra_FDD.ToString(indent+1);
    if(cellForWhichToReportCGI_internal_choice == k_cellForWhichToReportCGI_utra_TDD)
        out += cellForWhichToReportCGI_utra_TDD.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::cellForWhichToReportCGI_ToStringNoNewLines() const
{
    std::string out = "cellForWhichToReportCGI=" + cellForWhichToReportCGI_ChoiceToString(cellForWhichToReportCGI_internal_choice) + ",";
    if(cellForWhichToReportCGI_internal_choice == k_cellForWhichToReportCGI_utra_FDD)
        out += cellForWhichToReportCGI_utra_FDD.ToStringNoNewLines();
    if(cellForWhichToReportCGI_internal_choice == k_cellForWhichToReportCGI_utra_TDD)
        out += cellForWhichToReportCGI_utra_TDD.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::cellForWhichToReportCGI_Clear()
{
    cellForWhichToReportCGI_present = false;
    return 0;
}

bool MeasObjectUTRA::cellForWhichToReportCGI_IsPresent() const
{
    return cellForWhichToReportCGI_present;
}

PhysCellIdUTRA_FDD* MeasObjectUTRA::cellForWhichToReportCGI_utra_FDD_Set()
{
    cellForWhichToReportCGI_utra_FDD_present = true;
    return &cellForWhichToReportCGI_utra_FDD;
}

int MeasObjectUTRA::cellForWhichToReportCGI_utra_FDD_Set(PhysCellIdUTRA_FDD &value)
{
    cellForWhichToReportCGI_utra_FDD_present = true;
    cellForWhichToReportCGI_utra_FDD = value;
    return 0;
}

const PhysCellIdUTRA_FDD& MeasObjectUTRA::cellForWhichToReportCGI_utra_FDD_Get() const
{
    return cellForWhichToReportCGI_utra_FDD;
}

std::string MeasObjectUTRA::cellForWhichToReportCGI_utra_FDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_FDD:\n";
    out += cellForWhichToReportCGI_utra_FDD.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::cellForWhichToReportCGI_utra_FDD_ToStringNoNewLines() const
{
    std::string out = "utra_FDD:";
    out += cellForWhichToReportCGI_utra_FDD.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::cellForWhichToReportCGI_utra_FDD_Clear()
{
    cellForWhichToReportCGI_utra_FDD_present = false;
    return 0;
}

bool MeasObjectUTRA::cellForWhichToReportCGI_utra_FDD_IsPresent() const
{
    return cellForWhichToReportCGI_utra_FDD_present;
}

PhysCellIdUTRA_TDD* MeasObjectUTRA::cellForWhichToReportCGI_utra_TDD_Set()
{
    cellForWhichToReportCGI_utra_TDD_present = true;
    return &cellForWhichToReportCGI_utra_TDD;
}

int MeasObjectUTRA::cellForWhichToReportCGI_utra_TDD_Set(PhysCellIdUTRA_TDD &value)
{
    cellForWhichToReportCGI_utra_TDD_present = true;
    cellForWhichToReportCGI_utra_TDD = value;
    return 0;
}

const PhysCellIdUTRA_TDD& MeasObjectUTRA::cellForWhichToReportCGI_utra_TDD_Get() const
{
    return cellForWhichToReportCGI_utra_TDD;
}

std::string MeasObjectUTRA::cellForWhichToReportCGI_utra_TDD_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "utra_TDD:\n";
    out += cellForWhichToReportCGI_utra_TDD.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::cellForWhichToReportCGI_utra_TDD_ToStringNoNewLines() const
{
    std::string out = "utra_TDD:";
    out += cellForWhichToReportCGI_utra_TDD.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::cellForWhichToReportCGI_utra_TDD_Clear()
{
    cellForWhichToReportCGI_utra_TDD_present = false;
    return 0;
}

bool MeasObjectUTRA::cellForWhichToReportCGI_utra_TDD_IsPresent() const
{
    return cellForWhichToReportCGI_utra_TDD_present;
}

CSG_AllowedReportingCells_r9* MeasObjectUTRA::csg_allowedReportingCells_v930_Set()
{
    csg_allowedReportingCells_v930_present = true;
    return &csg_allowedReportingCells_v930;
}

int MeasObjectUTRA::csg_allowedReportingCells_v930_Set(CSG_AllowedReportingCells_r9 &value)
{
    csg_allowedReportingCells_v930_present = true;
    csg_allowedReportingCells_v930 = value;
    return 0;
}

const CSG_AllowedReportingCells_r9& MeasObjectUTRA::csg_allowedReportingCells_v930_Get() const
{
    return csg_allowedReportingCells_v930;
}

std::string MeasObjectUTRA::csg_allowedReportingCells_v930_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "csg_allowedReportingCells_v930:\n";
    out += csg_allowedReportingCells_v930.ToString(indent+1);
    return out;
}

std::string MeasObjectUTRA::csg_allowedReportingCells_v930_ToStringNoNewLines() const
{
    std::string out = "csg_allowedReportingCells_v930:";
    out += csg_allowedReportingCells_v930.ToStringNoNewLines();
    return out;
}

int MeasObjectUTRA::csg_allowedReportingCells_v930_Clear()
{
    csg_allowedReportingCells_v930_present = false;
    return 0;
}

bool MeasObjectUTRA::csg_allowedReportingCells_v930_IsPresent() const
{
    return csg_allowedReportingCells_v930_present;
}

