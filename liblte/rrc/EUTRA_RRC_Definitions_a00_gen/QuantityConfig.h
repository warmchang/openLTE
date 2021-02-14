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

#ifndef __QuantityConfig_H__
#define __QuantityConfig_H__

#include "QuantityConfigEUTRA.h"
#include "QuantityConfigUTRA.h"
#include "QuantityConfigGERAN.h"
#include "QuantityConfigCDMA2000.h"
#include "QuantityConfigUTRA_v10x0.h"

#include <array>
#include <cstdint>
#include <vector>

class QuantityConfig
{
public:
    QuantityConfig() : quantityConfigEUTRA_present{false}, quantityConfigUTRA_present{false}, quantityConfigGERAN_present{false}, quantityConfigCDMA2000_present{false}, quantityConfigUTRA_v10x0_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // quantityConfigEUTRA
public:
    QuantityConfigEUTRA* quantityConfigEUTRA_Set();
    int quantityConfigEUTRA_Set(QuantityConfigEUTRA &value);
    const QuantityConfigEUTRA& quantityConfigEUTRA_Get() const;
    std::string quantityConfigEUTRA_ToString(uint32_t indent) const;
    std::string quantityConfigEUTRA_ToStringNoNewLines() const;
    int quantityConfigEUTRA_Clear();
    bool quantityConfigEUTRA_IsPresent() const;
private:
    bool quantityConfigEUTRA_present;
    QuantityConfigEUTRA quantityConfigEUTRA;

    // quantityConfigUTRA
public:
    QuantityConfigUTRA* quantityConfigUTRA_Set();
    int quantityConfigUTRA_Set(QuantityConfigUTRA &value);
    const QuantityConfigUTRA& quantityConfigUTRA_Get() const;
    std::string quantityConfigUTRA_ToString(uint32_t indent) const;
    std::string quantityConfigUTRA_ToStringNoNewLines() const;
    int quantityConfigUTRA_Clear();
    bool quantityConfigUTRA_IsPresent() const;
private:
    bool quantityConfigUTRA_present;
    QuantityConfigUTRA quantityConfigUTRA;

    // quantityConfigGERAN
public:
    QuantityConfigGERAN* quantityConfigGERAN_Set();
    int quantityConfigGERAN_Set(QuantityConfigGERAN &value);
    const QuantityConfigGERAN& quantityConfigGERAN_Get() const;
    std::string quantityConfigGERAN_ToString(uint32_t indent) const;
    std::string quantityConfigGERAN_ToStringNoNewLines() const;
    int quantityConfigGERAN_Clear();
    bool quantityConfigGERAN_IsPresent() const;
private:
    bool quantityConfigGERAN_present;
    QuantityConfigGERAN quantityConfigGERAN;

    // quantityConfigCDMA2000
public:
    QuantityConfigCDMA2000* quantityConfigCDMA2000_Set();
    int quantityConfigCDMA2000_Set(QuantityConfigCDMA2000 &value);
    const QuantityConfigCDMA2000& quantityConfigCDMA2000_Get() const;
    std::string quantityConfigCDMA2000_ToString(uint32_t indent) const;
    std::string quantityConfigCDMA2000_ToStringNoNewLines() const;
    int quantityConfigCDMA2000_Clear();
    bool quantityConfigCDMA2000_IsPresent() const;
private:
    bool quantityConfigCDMA2000_present;
    QuantityConfigCDMA2000 quantityConfigCDMA2000;

    // quantityConfigUTRA-v10x0
public:
    QuantityConfigUTRA_v10x0* quantityConfigUTRA_v10x0_Set();
    int quantityConfigUTRA_v10x0_Set(QuantityConfigUTRA_v10x0 &value);
    const QuantityConfigUTRA_v10x0& quantityConfigUTRA_v10x0_Get() const;
    std::string quantityConfigUTRA_v10x0_ToString(uint32_t indent) const;
    std::string quantityConfigUTRA_v10x0_ToStringNoNewLines() const;
    int quantityConfigUTRA_v10x0_Clear();
    bool quantityConfigUTRA_v10x0_IsPresent() const;
private:
    bool quantityConfigUTRA_v10x0_present;
    QuantityConfigUTRA_v10x0 quantityConfigUTRA_v10x0;

};

#endif
