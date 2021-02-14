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

#ifndef __AntennaInfoDedicated_r10_H__
#define __AntennaInfoDedicated_r10_H__

#include <array>
#include <cstdint>
#include <vector>

class AntennaInfoDedicated_r10
{
public:
    AntennaInfoDedicated_r10() : transmissionMode_r10_present{false}, codebookSubsetRestriction_r10_present{false}, ue_TransmitAntennaSelection_r10_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // transmissionMode-r10
public:
    enum transmissionMode_r10_Enum {
        k_transmissionMode_r10_tm1 = 0,
        k_transmissionMode_r10_tm2,
        k_transmissionMode_r10_tm3,
        k_transmissionMode_r10_tm4,
        k_transmissionMode_r10_tm5,
        k_transmissionMode_r10_tm6,
        k_transmissionMode_r10_tm7,
        k_transmissionMode_r10_tm8_v920,
        k_transmissionMode_r10_tm9_v10x0,
        k_transmissionMode_r10_spare7,
        k_transmissionMode_r10_spare6,
        k_transmissionMode_r10_spare5,
        k_transmissionMode_r10_spare4,
        k_transmissionMode_r10_spare3,
        k_transmissionMode_r10_spare2,
        k_transmissionMode_r10_spare1,
    };
    int transmissionMode_r10_Pack(std::vector<uint8_t> &bits);
    int transmissionMode_r10_Unpack(std::vector<uint8_t> bits);
    int transmissionMode_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    transmissionMode_r10_Enum transmissionMode_r10_Value() const;
    int transmissionMode_r10_SetValue(transmissionMode_r10_Enum value);
    int transmissionMode_r10_SetValue(std::string value);
    std::string transmissionMode_r10_ValueToString(transmissionMode_r10_Enum value) const;
    uint64_t transmissionMode_r10_NumberOfValues() const;
    std::string transmissionMode_r10_ToString(uint32_t indent) const;
    std::string transmissionMode_r10_ToStringNoNewLines() const;
    int transmissionMode_r10_Clear();
    bool transmissionMode_r10_IsPresent() const;
private:
    bool transmissionMode_r10_present;
    transmissionMode_r10_Enum transmissionMode_r10_internal_value;

    // codebookSubsetRestriction-r10
public:
    enum codebookSubsetRestriction_r10_Enum {
        k_codebookSubsetRestriction_r10_n2TxAntenna_tm3 = 0,
        k_codebookSubsetRestriction_r10_n4TxAntenna_tm3,
        k_codebookSubsetRestriction_r10_n2TxAntenna_tm4,
        k_codebookSubsetRestriction_r10_n4TxAntenna_tm4,
        k_codebookSubsetRestriction_r10_n2TxAntenna_tm5,
        k_codebookSubsetRestriction_r10_n4TxAntenna_tm5,
        k_codebookSubsetRestriction_r10_n2TxAntenna_tm6,
        k_codebookSubsetRestriction_r10_n4TxAntenna_tm6,
        k_codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9,
        k_codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9,
        k_codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10,
        k_codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10,
        k_codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10,
    };
    int codebookSubsetRestriction_r10_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    codebookSubsetRestriction_r10_Enum codebookSubsetRestriction_r10_Choice() const;
    int codebookSubsetRestriction_r10_SetChoice(codebookSubsetRestriction_r10_Enum choice);
    std::string codebookSubsetRestriction_r10_ChoiceToString(codebookSubsetRestriction_r10_Enum value) const;
    uint64_t codebookSubsetRestriction_r10_NumberOfChoices() const;
    std::string codebookSubsetRestriction_r10_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_Clear();
    bool codebookSubsetRestriction_r10_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_present;
    codebookSubsetRestriction_r10_Enum codebookSubsetRestriction_r10_internal_choice;

    // n2TxAntenna-tm3
public:
    int codebookSubsetRestriction_r10_n2TxAntenna_tm3_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm3_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm3_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm3_Value() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm3_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm3_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm3_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm3_Clear();
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm3_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm3_present;
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm3_internal_value;

    // n4TxAntenna-tm3
public:
    int codebookSubsetRestriction_r10_n4TxAntenna_tm3_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm3_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm3_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_r10_n4TxAntenna_tm3_Value() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm3_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm3_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm3_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm3_Clear();
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm3_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm3_present;
    uint8_t codebookSubsetRestriction_r10_n4TxAntenna_tm3_internal_value;

    // n2TxAntenna-tm4
public:
    int codebookSubsetRestriction_r10_n2TxAntenna_tm4_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm4_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm4_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm4_Value() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm4_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm4_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm4_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm4_Clear();
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm4_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm4_present;
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm4_internal_value;

    // n4TxAntenna-tm4
public:
    int codebookSubsetRestriction_r10_n4TxAntenna_tm4_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm4_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm4_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint64_t codebookSubsetRestriction_r10_n4TxAntenna_tm4_Value() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm4_SetValue(uint64_t value);
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm4_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm4_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm4_Clear();
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm4_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm4_present;
    uint64_t codebookSubsetRestriction_r10_n4TxAntenna_tm4_internal_value;

    // n2TxAntenna-tm5
public:
    int codebookSubsetRestriction_r10_n2TxAntenna_tm5_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm5_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm5_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm5_Value() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm5_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm5_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm5_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm5_Clear();
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm5_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm5_present;
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm5_internal_value;

    // n4TxAntenna-tm5
public:
    int codebookSubsetRestriction_r10_n4TxAntenna_tm5_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm5_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm5_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t codebookSubsetRestriction_r10_n4TxAntenna_tm5_Value() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm5_SetValue(uint16_t value);
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm5_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm5_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm5_Clear();
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm5_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm5_present;
    uint16_t codebookSubsetRestriction_r10_n4TxAntenna_tm5_internal_value;

    // n2TxAntenna-tm6
public:
    int codebookSubsetRestriction_r10_n2TxAntenna_tm6_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm6_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm6_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm6_Value() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm6_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm6_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm6_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm6_Clear();
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm6_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm6_present;
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm6_internal_value;

    // n4TxAntenna-tm6
public:
    int codebookSubsetRestriction_r10_n4TxAntenna_tm6_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm6_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm6_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t codebookSubsetRestriction_r10_n4TxAntenna_tm6_Value() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm6_SetValue(uint16_t value);
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm6_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm6_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm6_Clear();
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm6_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm6_present;
    uint16_t codebookSubsetRestriction_r10_n4TxAntenna_tm6_internal_value;

    // n2TxAntenna-tm8-r9
public:
    int codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Value() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_Clear();
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_present;
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm8_r9_internal_value;

    // n4TxAntenna-tm8-r9
public:
    int codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint32_t codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Value() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_SetValue(uint32_t value);
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_Clear();
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_present;
    uint32_t codebookSubsetRestriction_r10_n4TxAntenna_tm8_r9_internal_value;

    // n2TxAntenna-tm9-r10
public:
    int codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Value() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_Clear();
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_present;
    uint8_t codebookSubsetRestriction_r10_n2TxAntenna_tm9_r10_internal_value;

    // n4TxAntenna-tm9-r10
public:
    int codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint64_t codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Value() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_SetValue(uint64_t value);
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_Clear();
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_present;
    uint64_t codebookSubsetRestriction_r10_n4TxAntenna_tm9_r10_internal_value;

    // n8TxAntenna-tm9-r10
public:
    int codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Value() const;
    int codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_ToStringNoNewLines() const;
    int codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_Clear();
    bool codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_IsPresent() const;
private:
    bool codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_present;
    uint8_t codebookSubsetRestriction_r10_n8TxAntenna_tm9_r10_internal_value;


    // ue-TransmitAntennaSelection-r10
public:
    enum ue_TransmitAntennaSelection_r10_Enum {
        k_ue_TransmitAntennaSelection_r10_release = 0,
        k_ue_TransmitAntennaSelection_r10_setup,
    };
    int ue_TransmitAntennaSelection_r10_Pack(std::vector<uint8_t> &bits);
    int ue_TransmitAntennaSelection_r10_Unpack(std::vector<uint8_t> bits);
    int ue_TransmitAntennaSelection_r10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ue_TransmitAntennaSelection_r10_Enum ue_TransmitAntennaSelection_r10_Choice() const;
    int ue_TransmitAntennaSelection_r10_SetChoice(ue_TransmitAntennaSelection_r10_Enum choice);
    std::string ue_TransmitAntennaSelection_r10_ChoiceToString(ue_TransmitAntennaSelection_r10_Enum value) const;
    uint64_t ue_TransmitAntennaSelection_r10_NumberOfChoices() const;
    std::string ue_TransmitAntennaSelection_r10_ToString(uint32_t indent) const;
    std::string ue_TransmitAntennaSelection_r10_ToStringNoNewLines() const;
    int ue_TransmitAntennaSelection_r10_Clear();
    bool ue_TransmitAntennaSelection_r10_IsPresent() const;
private:
    bool ue_TransmitAntennaSelection_r10_present;
    ue_TransmitAntennaSelection_r10_Enum ue_TransmitAntennaSelection_r10_internal_choice;

    // release
public:
    int ue_TransmitAntennaSelection_r10_release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int ue_TransmitAntennaSelection_r10_release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int ue_TransmitAntennaSelection_r10_release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool ue_TransmitAntennaSelection_r10_release_IsPresent() const {return true;};
    std::string ue_TransmitAntennaSelection_r10_release_ToString(uint32_t indent) {return "";};
    std::string ue_TransmitAntennaSelection_r10_release_ToStringNoNewLines() {return "";};

    // setup
public:
    enum ue_TransmitAntennaSelection_r10_setup_Enum {
        k_ue_TransmitAntennaSelection_r10_setup_closedLoop = 0,
        k_ue_TransmitAntennaSelection_r10_setup_openLoop,
    };
    int ue_TransmitAntennaSelection_r10_setup_Pack(std::vector<uint8_t> &bits);
    int ue_TransmitAntennaSelection_r10_setup_Unpack(std::vector<uint8_t> bits);
    int ue_TransmitAntennaSelection_r10_setup_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ue_TransmitAntennaSelection_r10_setup_Enum ue_TransmitAntennaSelection_r10_setup_Value() const;
    int ue_TransmitAntennaSelection_r10_setup_SetValue(ue_TransmitAntennaSelection_r10_setup_Enum value);
    int ue_TransmitAntennaSelection_r10_setup_SetValue(std::string value);
    std::string ue_TransmitAntennaSelection_r10_setup_ValueToString(ue_TransmitAntennaSelection_r10_setup_Enum value) const;
    uint64_t ue_TransmitAntennaSelection_r10_setup_NumberOfValues() const;
    std::string ue_TransmitAntennaSelection_r10_setup_ToString(uint32_t indent) const;
    std::string ue_TransmitAntennaSelection_r10_setup_ToStringNoNewLines() const;
    int ue_TransmitAntennaSelection_r10_setup_Clear();
    bool ue_TransmitAntennaSelection_r10_setup_IsPresent() const;
private:
    bool ue_TransmitAntennaSelection_r10_setup_present;
    ue_TransmitAntennaSelection_r10_setup_Enum ue_TransmitAntennaSelection_r10_setup_internal_value;


};

#endif
