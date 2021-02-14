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

#ifndef __HandoverFromEUTRAPreparationRequest_r8_IEs_H__
#define __HandoverFromEUTRAPreparationRequest_r8_IEs_H__

#include "CDMA2000_Type.h"
#include "RAND_CDMA2000.h"
#include "MobilityParametersCDMA2000.h"
#include "HandoverFromEUTRAPreparationRequest_v890_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class HandoverFromEUTRAPreparationRequest_r8_IEs
{
public:
    HandoverFromEUTRAPreparationRequest_r8_IEs() : cdma2000_Type_present{false}, rand_present{false}, mobilityParameters_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // cdma2000-Type
public:
    CDMA2000_Type* cdma2000_Type_Set();
    int cdma2000_Type_Set(CDMA2000_Type &value);
    const CDMA2000_Type& cdma2000_Type_Get() const;
    std::string cdma2000_Type_ToString(uint32_t indent) const;
    std::string cdma2000_Type_ToStringNoNewLines() const;
    int cdma2000_Type_Clear();
    bool cdma2000_Type_IsPresent() const;
private:
    bool cdma2000_Type_present;
    CDMA2000_Type cdma2000_Type;

    // rand
public:
    RAND_CDMA2000* rand_Set();
    int rand_Set(RAND_CDMA2000 &value);
    const RAND_CDMA2000& rand_Get() const;
    std::string rand_ToString(uint32_t indent) const;
    std::string rand_ToStringNoNewLines() const;
    int rand_Clear();
    bool rand_IsPresent() const;
private:
    bool rand_present;
    RAND_CDMA2000 rand;

    // mobilityParameters
public:
    MobilityParametersCDMA2000* mobilityParameters_Set();
    int mobilityParameters_Set(MobilityParametersCDMA2000 &value);
    const MobilityParametersCDMA2000& mobilityParameters_Get() const;
    std::string mobilityParameters_ToString(uint32_t indent) const;
    std::string mobilityParameters_ToStringNoNewLines() const;
    int mobilityParameters_Clear();
    bool mobilityParameters_IsPresent() const;
private:
    bool mobilityParameters_present;
    MobilityParametersCDMA2000 mobilityParameters;

    // nonCriticalExtension
public:
    HandoverFromEUTRAPreparationRequest_v890_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(HandoverFromEUTRAPreparationRequest_v890_IEs &value);
    const HandoverFromEUTRAPreparationRequest_v890_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    HandoverFromEUTRAPreparationRequest_v890_IEs nonCriticalExtension;

};

#endif
