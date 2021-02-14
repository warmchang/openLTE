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

#ifndef __CSFBParametersResponseCDMA2000_r8_IEs_H__
#define __CSFBParametersResponseCDMA2000_r8_IEs_H__

#include "RAND_CDMA2000.h"
#include "MobilityParametersCDMA2000.h"
#include "CSFBParametersResponseCDMA2000_v8a0_IEs.h"

#include <array>
#include <cstdint>
#include <vector>

class CSFBParametersResponseCDMA2000_r8_IEs
{
public:
    CSFBParametersResponseCDMA2000_r8_IEs() : rand_present{false}, mobilityParameters_present{false}, nonCriticalExtension_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

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
    CSFBParametersResponseCDMA2000_v8a0_IEs* nonCriticalExtension_Set();
    int nonCriticalExtension_Set(CSFBParametersResponseCDMA2000_v8a0_IEs &value);
    const CSFBParametersResponseCDMA2000_v8a0_IEs& nonCriticalExtension_Get() const;
    std::string nonCriticalExtension_ToString(uint32_t indent) const;
    std::string nonCriticalExtension_ToStringNoNewLines() const;
    int nonCriticalExtension_Clear();
    bool nonCriticalExtension_IsPresent() const;
private:
    bool nonCriticalExtension_present;
    CSFBParametersResponseCDMA2000_v8a0_IEs nonCriticalExtension;

};

#endif
