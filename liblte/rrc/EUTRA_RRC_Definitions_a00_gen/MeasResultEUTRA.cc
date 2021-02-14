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

#include "MeasResultEUTRA.h"

#include <cmath>

int MeasResultEUTRA::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(cgi_Info_value.IsPresent());

    // Fields
    {
        if(0 != physCellId.Pack(bits))
        {
            printf("MeasResultEUTRA:: field pack failure\n");
            return -1;
        }
    }
    if(cgi_Info_value.IsPresent())
    {
        if(0 != cgi_Info_value.Pack(bits))
        {
            printf("MeasResultEUTRA:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResult_value.Pack(bits))
        {
            printf("MeasResultEUTRA:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultEUTRA::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultEUTRA::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("MeasResultEUTRA::Unpack() index out of bounds for optional indiator cgi_Info\n");
        return -1;
    }
    cgi_Info_value.SetPresence(bits[idx++]);

    // Fields
    {
        if(0 != physCellId.Unpack(bits, idx))
        {
            printf("MeasResultEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    if(cgi_Info_value.IsPresent())
    {
        if(0 != cgi_Info_value.Unpack(bits, idx))
        {
            printf("MeasResultEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != measResult_value.Unpack(bits, idx))
        {
            printf("MeasResultEUTRA:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultEUTRA::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "MeasResultEUTRA:\n";
    out += physCellId_ToString(indent+1);
    if(cgi_Info_value.IsPresent())
        out += cgi_Info_value.ToString(indent+1);
    out += measResult_value.ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::ToStringNoNewLines() const
{
    std::string out = "MeasResultEUTRA:";
    out += physCellId_ToStringNoNewLines();
    if(cgi_Info_value.IsPresent())
        out += cgi_Info_value.ToStringNoNewLines();
    out += measResult_value.ToStringNoNewLines();
    return out;
}

PhysCellId* MeasResultEUTRA::physCellId_Set()
{
    physCellId_present = true;
    return &physCellId;
}

int MeasResultEUTRA::physCellId_Set(PhysCellId &value)
{
    physCellId_present = true;
    physCellId = value;
    return 0;
}

const PhysCellId& MeasResultEUTRA::physCellId_Get() const
{
    return physCellId;
}

std::string MeasResultEUTRA::physCellId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "physCellId:\n";
    out += physCellId.ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::physCellId_ToStringNoNewLines() const
{
    std::string out = "physCellId:";
    out += physCellId.ToStringNoNewLines();
    return out;
}

int MeasResultEUTRA::physCellId_Clear()
{
    physCellId_present = false;
    return 0;
}

bool MeasResultEUTRA::physCellId_IsPresent() const
{
    return physCellId_present;
}

int MeasResultEUTRA::cgi_Info::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator

    // Optional indicators
    bits.push_back(plmn_IdentityList_IsPresent());

    // Fields
    {
        if(0 != cellGlobalId.Pack(bits))
        {
            printf("MeasResultEUTRA::cgi_Info:: field pack failure\n");
            return -1;
        }
    }
    {
        if(0 != trackingAreaCode.Pack(bits))
        {
            printf("MeasResultEUTRA::cgi_Info:: field pack failure\n");
            return -1;
        }
    }
    if(plmn_IdentityList_IsPresent())
    {
        if(0 != plmn_IdentityList.Pack(bits))
        {
            printf("MeasResultEUTRA::cgi_Info:: field pack failure\n");
            return -1;
        }
    }
    return 0;
}

int MeasResultEUTRA::cgi_Info::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultEUTRA::cgi_Info::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("cgi_Info::Unpack() index out of bounds for optional indiator plmn_IdentityList\n");
        return -1;
    }
    plmn_IdentityList_present = bits[idx++];

    // Fields
    {
        if(0 != cellGlobalId.Unpack(bits, idx))
        {
            printf("MeasResultEUTRA::cgi_Info:: field unpack failure\n");
            return -1;
        }
    }
    {
        if(0 != trackingAreaCode.Unpack(bits, idx))
        {
            printf("MeasResultEUTRA::cgi_Info:: field unpack failure\n");
            return -1;
        }
    }
    if(plmn_IdentityList_present)
    {
        if(0 != plmn_IdentityList.Unpack(bits, idx))
        {
            printf("MeasResultEUTRA::cgi_Info:: field unpack failure\n");
            return -1;
        }
    }
    return 0;
}

std::string MeasResultEUTRA::cgi_Info::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cgi_Info:\n";
    out += cellGlobalId_ToString(indent+1);
    out += trackingAreaCode_ToString(indent+1);
    if(plmn_IdentityList_IsPresent())
        out += plmn_IdentityList_ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::cgi_Info::ToStringNoNewLines() const
{
    std::string out = "cgi_Info:";
    out += cellGlobalId_ToStringNoNewLines();
    out += trackingAreaCode_ToStringNoNewLines();
    if(plmn_IdentityList_IsPresent())
        out += plmn_IdentityList_ToStringNoNewLines();
    return out;
}

int MeasResultEUTRA::cgi_Info::Set()
{
    present = true;
    return 0;
}

int MeasResultEUTRA::cgi_Info::SetPresence(bool is_present)
{
    present = is_present;
    return 0;
}

int MeasResultEUTRA::cgi_Info::Clear()
{
    present = false;
    return 0;
}

bool MeasResultEUTRA::cgi_Info::IsPresent() const
{
    return present;
}

CellGlobalIdEUTRA* MeasResultEUTRA::cgi_Info::cellGlobalId_Set()
{
    cellGlobalId_present = true;
    return &cellGlobalId;
}

int MeasResultEUTRA::cgi_Info::cellGlobalId_Set(CellGlobalIdEUTRA &value)
{
    cellGlobalId_present = true;
    cellGlobalId = value;
    return 0;
}

const CellGlobalIdEUTRA& MeasResultEUTRA::cgi_Info::cellGlobalId_Get() const
{
    return cellGlobalId;
}

std::string MeasResultEUTRA::cgi_Info::cellGlobalId_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "cellGlobalId:\n";
    out += cellGlobalId.ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::cgi_Info::cellGlobalId_ToStringNoNewLines() const
{
    std::string out = "cellGlobalId:";
    out += cellGlobalId.ToStringNoNewLines();
    return out;
}

int MeasResultEUTRA::cgi_Info::cellGlobalId_Clear()
{
    cellGlobalId_present = false;
    return 0;
}

bool MeasResultEUTRA::cgi_Info::cellGlobalId_IsPresent() const
{
    return cellGlobalId_present;
}

TrackingAreaCode* MeasResultEUTRA::cgi_Info::trackingAreaCode_Set()
{
    trackingAreaCode_present = true;
    return &trackingAreaCode;
}

int MeasResultEUTRA::cgi_Info::trackingAreaCode_Set(TrackingAreaCode &value)
{
    trackingAreaCode_present = true;
    trackingAreaCode = value;
    return 0;
}

const TrackingAreaCode& MeasResultEUTRA::cgi_Info::trackingAreaCode_Get() const
{
    return trackingAreaCode;
}

std::string MeasResultEUTRA::cgi_Info::trackingAreaCode_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "trackingAreaCode:\n";
    out += trackingAreaCode.ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::cgi_Info::trackingAreaCode_ToStringNoNewLines() const
{
    std::string out = "trackingAreaCode:";
    out += trackingAreaCode.ToStringNoNewLines();
    return out;
}

int MeasResultEUTRA::cgi_Info::trackingAreaCode_Clear()
{
    trackingAreaCode_present = false;
    return 0;
}

bool MeasResultEUTRA::cgi_Info::trackingAreaCode_IsPresent() const
{
    return trackingAreaCode_present;
}

PLMN_IdentityList2* MeasResultEUTRA::cgi_Info::plmn_IdentityList_Set()
{
    plmn_IdentityList_present = true;
    return &plmn_IdentityList;
}

int MeasResultEUTRA::cgi_Info::plmn_IdentityList_Set(PLMN_IdentityList2 &value)
{
    plmn_IdentityList_present = true;
    plmn_IdentityList = value;
    return 0;
}

const PLMN_IdentityList2& MeasResultEUTRA::cgi_Info::plmn_IdentityList_Get() const
{
    return plmn_IdentityList;
}

std::string MeasResultEUTRA::cgi_Info::plmn_IdentityList_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "plmn_IdentityList:\n";
    out += plmn_IdentityList.ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::cgi_Info::plmn_IdentityList_ToStringNoNewLines() const
{
    std::string out = "plmn_IdentityList:";
    out += plmn_IdentityList.ToStringNoNewLines();
    return out;
}

int MeasResultEUTRA::cgi_Info::plmn_IdentityList_Clear()
{
    plmn_IdentityList_present = false;
    return 0;
}

bool MeasResultEUTRA::cgi_Info::plmn_IdentityList_IsPresent() const
{
    return plmn_IdentityList_present;
}

int MeasResultEUTRA::measResult::Pack(std::vector<uint8_t> &bits)
{
    // Extension indicator
    bool has_extension = false;
    if(additionalSI_Info_r9_IsPresent())
    {
        bits.push_back(1);
        has_extension = true;
    }else{
        bits.push_back(0);
    }

    // Optional indicators
    bits.push_back(rsrpResult_IsPresent());
    bits.push_back(rsrqResult_IsPresent());

    // Fields
    if(rsrpResult_IsPresent())
    {
        if(0 != rsrpResult.Pack(bits))
        {
            printf("MeasResultEUTRA::measResult:: field pack failure\n");
            return -1;
        }
    }
    if(rsrqResult_IsPresent())
    {
        if(0 != rsrqResult.Pack(bits))
        {
            printf("MeasResultEUTRA::measResult:: field pack failure\n");
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
            printf("measResult:: Extension list size too large failure\n");
            return -1;
        }

        // Extension field presence indicators
        bits.push_back(additionalSI_Info_r9_IsPresent());

        // Extension fields
        if(additionalSI_Info_r9_IsPresent())
        {
            std::vector<uint8_t> field_bits;
            if(0 != additionalSI_Info_r9.Pack(field_bits))
            {
                printf("MeasResultEUTRA::measResult:: field pack failure\n");
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

int MeasResultEUTRA::measResult::Unpack(std::vector<uint8_t> bits)
{
    uint32_t idx = 0;
    return Unpack(bits, idx);
}

int MeasResultEUTRA::measResult::Unpack(std::vector<uint8_t> bits, uint32_t &idx)
{
    // Extension indicator
    if((idx + 1) > bits.size())
    {
        printf("measResult::Unpack() index out of bounds for extension\n");
        return -1;
    }
    bool has_extension = bits[idx++];

    // Optional indicators
    if((idx + 1) > bits.size())
    {
        printf("measResult::Unpack() index out of bounds for optional indiator rsrpResult\n");
        return -1;
    }
    rsrpResult_present = bits[idx++];
    if((idx + 1) > bits.size())
    {
        printf("measResult::Unpack() index out of bounds for optional indiator rsrqResult\n");
        return -1;
    }
    rsrqResult_present = bits[idx++];

    // Fields
    if(rsrpResult_present)
    {
        if(0 != rsrpResult.Unpack(bits, idx))
        {
            printf("MeasResultEUTRA::measResult:: field unpack failure\n");
            return -1;
        }
    }
    if(rsrqResult_present)
    {
        if(0 != rsrqResult.Unpack(bits, idx))
        {
            printf("MeasResultEUTRA::measResult:: field unpack failure\n");
            return -1;
        }
    }

    // Extension
    if(has_extension)
    {
        if((idx + 7) > bits.size())
        {
            printf("measResult::Unpack() index out of bounds for extension size\n");
            return -1;
        }
        // Number of extension fields
        if(bits[idx++] != 0)
        {
            printf("measResult:: Extension list size too large failure\n");
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
                printf("measResult::Unpack() index out of bounds for optional indiator additionalSI_Info_r9\n");
                return -1;
            }
            additionalSI_Info_r9_present = bits[idx++];
        }
        if((idx + (N_ext_fields - opt_ind_count)) > bits.size())
        {
            printf("measResult::Unpack() index out of bounds for extension optional indicators\n");
            return -1;
        }
        idx += (N_ext_fields - opt_ind_count);

        // Extension fields
        if(additionalSI_Info_r9_present)
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
            if(0 != additionalSI_Info_r9.Unpack(bits, idx))
            {
                printf("MeasResultEUTRA::measResult:: field unpack failure\n");
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
            printf("measResult::Unpack() index out of bounds for extension fields\n");
            return -1;
        }
            idx += N_octets * 8;
        }
    }
    return 0;
}

std::string MeasResultEUTRA::measResult::ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "measResult:\n";
    if(rsrpResult_IsPresent())
        out += rsrpResult_ToString(indent+1);
    if(rsrqResult_IsPresent())
        out += rsrqResult_ToString(indent+1);
    if(additionalSI_Info_r9_IsPresent())
        out += additionalSI_Info_r9_ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::measResult::ToStringNoNewLines() const
{
    std::string out = "measResult:";
    if(rsrpResult_IsPresent())
        out += rsrpResult_ToStringNoNewLines();
    if(rsrqResult_IsPresent())
        out += rsrqResult_ToStringNoNewLines();
    if(additionalSI_Info_r9_IsPresent())
        out += additionalSI_Info_r9_ToStringNoNewLines();
    return out;
}

RSRP_Range* MeasResultEUTRA::measResult::rsrpResult_Set()
{
    rsrpResult_present = true;
    return &rsrpResult;
}

int MeasResultEUTRA::measResult::rsrpResult_Set(RSRP_Range &value)
{
    rsrpResult_present = true;
    rsrpResult = value;
    return 0;
}

const RSRP_Range& MeasResultEUTRA::measResult::rsrpResult_Get() const
{
    return rsrpResult;
}

std::string MeasResultEUTRA::measResult::rsrpResult_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrpResult:\n";
    out += rsrpResult.ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::measResult::rsrpResult_ToStringNoNewLines() const
{
    std::string out = "rsrpResult:";
    out += rsrpResult.ToStringNoNewLines();
    return out;
}

int MeasResultEUTRA::measResult::rsrpResult_Clear()
{
    rsrpResult_present = false;
    return 0;
}

bool MeasResultEUTRA::measResult::rsrpResult_IsPresent() const
{
    return rsrpResult_present;
}

RSRQ_Range* MeasResultEUTRA::measResult::rsrqResult_Set()
{
    rsrqResult_present = true;
    return &rsrqResult;
}

int MeasResultEUTRA::measResult::rsrqResult_Set(RSRQ_Range &value)
{
    rsrqResult_present = true;
    rsrqResult = value;
    return 0;
}

const RSRQ_Range& MeasResultEUTRA::measResult::rsrqResult_Get() const
{
    return rsrqResult;
}

std::string MeasResultEUTRA::measResult::rsrqResult_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "rsrqResult:\n";
    out += rsrqResult.ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::measResult::rsrqResult_ToStringNoNewLines() const
{
    std::string out = "rsrqResult:";
    out += rsrqResult.ToStringNoNewLines();
    return out;
}

int MeasResultEUTRA::measResult::rsrqResult_Clear()
{
    rsrqResult_present = false;
    return 0;
}

bool MeasResultEUTRA::measResult::rsrqResult_IsPresent() const
{
    return rsrqResult_present;
}

AdditionalSI_Info_r9* MeasResultEUTRA::measResult::additionalSI_Info_r9_Set()
{
    additionalSI_Info_r9_present = true;
    return &additionalSI_Info_r9;
}

int MeasResultEUTRA::measResult::additionalSI_Info_r9_Set(AdditionalSI_Info_r9 &value)
{
    additionalSI_Info_r9_present = true;
    additionalSI_Info_r9 = value;
    return 0;
}

const AdditionalSI_Info_r9& MeasResultEUTRA::measResult::additionalSI_Info_r9_Get() const
{
    return additionalSI_Info_r9;
}

std::string MeasResultEUTRA::measResult::additionalSI_Info_r9_ToString(uint32_t indent) const
{
    std::string out;
    for(uint32_t i=0; i<indent; i++)
        out += "    ";
    out += "additionalSI_Info_r9:\n";
    out += additionalSI_Info_r9.ToString(indent+1);
    return out;
}

std::string MeasResultEUTRA::measResult::additionalSI_Info_r9_ToStringNoNewLines() const
{
    std::string out = "additionalSI_Info_r9:";
    out += additionalSI_Info_r9.ToStringNoNewLines();
    return out;
}

int MeasResultEUTRA::measResult::additionalSI_Info_r9_Clear()
{
    additionalSI_Info_r9_present = false;
    return 0;
}

bool MeasResultEUTRA::measResult::additionalSI_Info_r9_IsPresent() const
{
    return additionalSI_Info_r9_present;
}

