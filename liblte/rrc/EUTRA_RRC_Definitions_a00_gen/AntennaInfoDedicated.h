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

#ifndef __AntennaInfoDedicated_H__
#define __AntennaInfoDedicated_H__

#include <array>
#include <cstdint>
#include <vector>

class AntennaInfoDedicated
{
public:
    AntennaInfoDedicated() : transmissionMode_present{false}, codebookSubsetRestriction_present{false}, ue_TransmitAntennaSelection_present{false} {};
public:
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;

    // transmissionMode
public:
    enum transmissionMode_Enum {
        k_transmissionMode_tm1 = 0,
        k_transmissionMode_tm2,
        k_transmissionMode_tm3,
        k_transmissionMode_tm4,
        k_transmissionMode_tm5,
        k_transmissionMode_tm6,
        k_transmissionMode_tm7,
        k_transmissionMode_tm8_v920,
    };
    int transmissionMode_Pack(std::vector<uint8_t> &bits);
    int transmissionMode_Unpack(std::vector<uint8_t> bits);
    int transmissionMode_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    transmissionMode_Enum transmissionMode_Value() const;
    int transmissionMode_SetValue(transmissionMode_Enum value);
    int transmissionMode_SetValue(std::string value);
    std::string transmissionMode_ValueToString(transmissionMode_Enum value) const;
    uint64_t transmissionMode_NumberOfValues() const;
    std::string transmissionMode_ToString(uint32_t indent) const;
    std::string transmissionMode_ToStringNoNewLines() const;
    int transmissionMode_Clear();
    bool transmissionMode_IsPresent() const;
private:
    bool transmissionMode_present;
    transmissionMode_Enum transmissionMode_internal_value;

    // codebookSubsetRestriction
public:
    enum codebookSubsetRestriction_Enum {
        k_codebookSubsetRestriction_n2TxAntenna_tm3 = 0,
        k_codebookSubsetRestriction_n4TxAntenna_tm3,
        k_codebookSubsetRestriction_n2TxAntenna_tm4,
        k_codebookSubsetRestriction_n4TxAntenna_tm4,
        k_codebookSubsetRestriction_n2TxAntenna_tm5,
        k_codebookSubsetRestriction_n4TxAntenna_tm5,
        k_codebookSubsetRestriction_n2TxAntenna_tm6,
        k_codebookSubsetRestriction_n4TxAntenna_tm6,
    };
    int codebookSubsetRestriction_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    codebookSubsetRestriction_Enum codebookSubsetRestriction_Choice() const;
    int codebookSubsetRestriction_SetChoice(codebookSubsetRestriction_Enum choice);
    std::string codebookSubsetRestriction_ChoiceToString(codebookSubsetRestriction_Enum value) const;
    uint64_t codebookSubsetRestriction_NumberOfChoices() const;
    std::string codebookSubsetRestriction_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_ToStringNoNewLines() const;
    int codebookSubsetRestriction_Clear();
    bool codebookSubsetRestriction_IsPresent() const;
private:
    bool codebookSubsetRestriction_present;
    codebookSubsetRestriction_Enum codebookSubsetRestriction_internal_choice;

    // n2TxAntenna-tm3
public:
    int codebookSubsetRestriction_n2TxAntenna_tm3_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_n2TxAntenna_tm3_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_n2TxAntenna_tm3_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_n2TxAntenna_tm3_Value() const;
    int codebookSubsetRestriction_n2TxAntenna_tm3_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_n2TxAntenna_tm3_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_n2TxAntenna_tm3_ToStringNoNewLines() const;
    int codebookSubsetRestriction_n2TxAntenna_tm3_Clear();
    bool codebookSubsetRestriction_n2TxAntenna_tm3_IsPresent() const;
private:
    bool codebookSubsetRestriction_n2TxAntenna_tm3_present;
    uint8_t codebookSubsetRestriction_n2TxAntenna_tm3_internal_value;

    // n4TxAntenna-tm3
public:
    int codebookSubsetRestriction_n4TxAntenna_tm3_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_n4TxAntenna_tm3_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_n4TxAntenna_tm3_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_n4TxAntenna_tm3_Value() const;
    int codebookSubsetRestriction_n4TxAntenna_tm3_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_n4TxAntenna_tm3_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_n4TxAntenna_tm3_ToStringNoNewLines() const;
    int codebookSubsetRestriction_n4TxAntenna_tm3_Clear();
    bool codebookSubsetRestriction_n4TxAntenna_tm3_IsPresent() const;
private:
    bool codebookSubsetRestriction_n4TxAntenna_tm3_present;
    uint8_t codebookSubsetRestriction_n4TxAntenna_tm3_internal_value;

    // n2TxAntenna-tm4
public:
    int codebookSubsetRestriction_n2TxAntenna_tm4_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_n2TxAntenna_tm4_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_n2TxAntenna_tm4_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_n2TxAntenna_tm4_Value() const;
    int codebookSubsetRestriction_n2TxAntenna_tm4_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_n2TxAntenna_tm4_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_n2TxAntenna_tm4_ToStringNoNewLines() const;
    int codebookSubsetRestriction_n2TxAntenna_tm4_Clear();
    bool codebookSubsetRestriction_n2TxAntenna_tm4_IsPresent() const;
private:
    bool codebookSubsetRestriction_n2TxAntenna_tm4_present;
    uint8_t codebookSubsetRestriction_n2TxAntenna_tm4_internal_value;

    // n4TxAntenna-tm4
public:
    int codebookSubsetRestriction_n4TxAntenna_tm4_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_n4TxAntenna_tm4_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_n4TxAntenna_tm4_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint64_t codebookSubsetRestriction_n4TxAntenna_tm4_Value() const;
    int codebookSubsetRestriction_n4TxAntenna_tm4_SetValue(uint64_t value);
    std::string codebookSubsetRestriction_n4TxAntenna_tm4_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_n4TxAntenna_tm4_ToStringNoNewLines() const;
    int codebookSubsetRestriction_n4TxAntenna_tm4_Clear();
    bool codebookSubsetRestriction_n4TxAntenna_tm4_IsPresent() const;
private:
    bool codebookSubsetRestriction_n4TxAntenna_tm4_present;
    uint64_t codebookSubsetRestriction_n4TxAntenna_tm4_internal_value;

    // n2TxAntenna-tm5
public:
    int codebookSubsetRestriction_n2TxAntenna_tm5_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_n2TxAntenna_tm5_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_n2TxAntenna_tm5_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_n2TxAntenna_tm5_Value() const;
    int codebookSubsetRestriction_n2TxAntenna_tm5_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_n2TxAntenna_tm5_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_n2TxAntenna_tm5_ToStringNoNewLines() const;
    int codebookSubsetRestriction_n2TxAntenna_tm5_Clear();
    bool codebookSubsetRestriction_n2TxAntenna_tm5_IsPresent() const;
private:
    bool codebookSubsetRestriction_n2TxAntenna_tm5_present;
    uint8_t codebookSubsetRestriction_n2TxAntenna_tm5_internal_value;

    // n4TxAntenna-tm5
public:
    int codebookSubsetRestriction_n4TxAntenna_tm5_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_n4TxAntenna_tm5_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_n4TxAntenna_tm5_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t codebookSubsetRestriction_n4TxAntenna_tm5_Value() const;
    int codebookSubsetRestriction_n4TxAntenna_tm5_SetValue(uint16_t value);
    std::string codebookSubsetRestriction_n4TxAntenna_tm5_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_n4TxAntenna_tm5_ToStringNoNewLines() const;
    int codebookSubsetRestriction_n4TxAntenna_tm5_Clear();
    bool codebookSubsetRestriction_n4TxAntenna_tm5_IsPresent() const;
private:
    bool codebookSubsetRestriction_n4TxAntenna_tm5_present;
    uint16_t codebookSubsetRestriction_n4TxAntenna_tm5_internal_value;

    // n2TxAntenna-tm6
public:
    int codebookSubsetRestriction_n2TxAntenna_tm6_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_n2TxAntenna_tm6_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_n2TxAntenna_tm6_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint8_t codebookSubsetRestriction_n2TxAntenna_tm6_Value() const;
    int codebookSubsetRestriction_n2TxAntenna_tm6_SetValue(uint8_t value);
    std::string codebookSubsetRestriction_n2TxAntenna_tm6_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_n2TxAntenna_tm6_ToStringNoNewLines() const;
    int codebookSubsetRestriction_n2TxAntenna_tm6_Clear();
    bool codebookSubsetRestriction_n2TxAntenna_tm6_IsPresent() const;
private:
    bool codebookSubsetRestriction_n2TxAntenna_tm6_present;
    uint8_t codebookSubsetRestriction_n2TxAntenna_tm6_internal_value;

    // n4TxAntenna-tm6
public:
    int codebookSubsetRestriction_n4TxAntenna_tm6_Pack(std::vector<uint8_t> &bits);
    int codebookSubsetRestriction_n4TxAntenna_tm6_Unpack(std::vector<uint8_t> bits);
    int codebookSubsetRestriction_n4TxAntenna_tm6_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    uint16_t codebookSubsetRestriction_n4TxAntenna_tm6_Value() const;
    int codebookSubsetRestriction_n4TxAntenna_tm6_SetValue(uint16_t value);
    std::string codebookSubsetRestriction_n4TxAntenna_tm6_ToString(uint32_t indent) const;
    std::string codebookSubsetRestriction_n4TxAntenna_tm6_ToStringNoNewLines() const;
    int codebookSubsetRestriction_n4TxAntenna_tm6_Clear();
    bool codebookSubsetRestriction_n4TxAntenna_tm6_IsPresent() const;
private:
    bool codebookSubsetRestriction_n4TxAntenna_tm6_present;
    uint16_t codebookSubsetRestriction_n4TxAntenna_tm6_internal_value;


    // ue-TransmitAntennaSelection
public:
    enum ue_TransmitAntennaSelection_Enum {
        k_ue_TransmitAntennaSelection_release = 0,
        k_ue_TransmitAntennaSelection_setup,
    };
    int ue_TransmitAntennaSelection_Pack(std::vector<uint8_t> &bits);
    int ue_TransmitAntennaSelection_Unpack(std::vector<uint8_t> bits);
    int ue_TransmitAntennaSelection_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ue_TransmitAntennaSelection_Enum ue_TransmitAntennaSelection_Choice() const;
    int ue_TransmitAntennaSelection_SetChoice(ue_TransmitAntennaSelection_Enum choice);
    std::string ue_TransmitAntennaSelection_ChoiceToString(ue_TransmitAntennaSelection_Enum value) const;
    uint64_t ue_TransmitAntennaSelection_NumberOfChoices() const;
    std::string ue_TransmitAntennaSelection_ToString(uint32_t indent) const;
    std::string ue_TransmitAntennaSelection_ToStringNoNewLines() const;
    int ue_TransmitAntennaSelection_Clear();
    bool ue_TransmitAntennaSelection_IsPresent() const;
private:
    bool ue_TransmitAntennaSelection_present;
    ue_TransmitAntennaSelection_Enum ue_TransmitAntennaSelection_internal_choice;

    // release
public:
    int ue_TransmitAntennaSelection_release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int ue_TransmitAntennaSelection_release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int ue_TransmitAntennaSelection_release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool ue_TransmitAntennaSelection_release_IsPresent() const {return true;};
    std::string ue_TransmitAntennaSelection_release_ToString(uint32_t indent) {return "";};
    std::string ue_TransmitAntennaSelection_release_ToStringNoNewLines() {return "";};

    // setup
public:
    enum ue_TransmitAntennaSelection_setup_Enum {
        k_ue_TransmitAntennaSelection_setup_closedLoop = 0,
        k_ue_TransmitAntennaSelection_setup_openLoop,
    };
    int ue_TransmitAntennaSelection_setup_Pack(std::vector<uint8_t> &bits);
    int ue_TransmitAntennaSelection_setup_Unpack(std::vector<uint8_t> bits);
    int ue_TransmitAntennaSelection_setup_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    ue_TransmitAntennaSelection_setup_Enum ue_TransmitAntennaSelection_setup_Value() const;
    int ue_TransmitAntennaSelection_setup_SetValue(ue_TransmitAntennaSelection_setup_Enum value);
    int ue_TransmitAntennaSelection_setup_SetValue(std::string value);
    std::string ue_TransmitAntennaSelection_setup_ValueToString(ue_TransmitAntennaSelection_setup_Enum value) const;
    uint64_t ue_TransmitAntennaSelection_setup_NumberOfValues() const;
    std::string ue_TransmitAntennaSelection_setup_ToString(uint32_t indent) const;
    std::string ue_TransmitAntennaSelection_setup_ToStringNoNewLines() const;
    int ue_TransmitAntennaSelection_setup_Clear();
    bool ue_TransmitAntennaSelection_setup_IsPresent() const;
private:
    bool ue_TransmitAntennaSelection_setup_present;
    ue_TransmitAntennaSelection_setup_Enum ue_TransmitAntennaSelection_setup_internal_value;


};

#endif
