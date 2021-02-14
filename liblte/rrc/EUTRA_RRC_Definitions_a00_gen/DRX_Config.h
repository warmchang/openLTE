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

#ifndef __DRX_Config_H__
#define __DRX_Config_H__

#include <array>
#include <cstdint>
#include <vector>

class DRX_Config
{
public:
    enum Enum {
        k_release = 0,
        k_setup,
    };
    int Pack(std::vector<uint8_t> &bits);
    int Unpack(std::vector<uint8_t> bits);
    int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
    Enum Choice() const;
    int SetChoice(Enum choice);
    std::string ChoiceToString(Enum value) const;
    uint64_t NumberOfChoices() const;
    std::string ToString(uint32_t indent) const;
    std::string ToStringNoNewLines() const;
    int Clear();
    bool IsPresent() const;
private:
    bool present;
    Enum internal_choice;

    // release
public:
    int release_Pack(std::vector<uint8_t> &bits) {return 0;};
    int release_Unpack(std::vector<uint8_t> bits) {return 0;};
    int release_Unpack(std::vector<uint8_t> bits, uint32_t &idx) {return 0;};
    bool release_IsPresent() const {return true;};
    std::string release_ToString(uint32_t indent) {return "";};
    std::string release_ToStringNoNewLines() {return "";};

    // setup
public:
    class setup
    {
    public:
        setup() : onDurationTimer_present{false}, drx_InactivityTimer_present{false}, drx_RetransmissionTimer_present{false}, longDRX_CycleStartOffset_present{false} {};
    public:
        int Pack(std::vector<uint8_t> &bits);
        int Unpack(std::vector<uint8_t> bits);
        int Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        std::string ToString(uint32_t indent) const;
        std::string ToStringNoNewLines() const;

        // onDurationTimer
    public:
        enum onDurationTimer_Enum {
            k_onDurationTimer_psf1 = 0,
            k_onDurationTimer_psf2,
            k_onDurationTimer_psf3,
            k_onDurationTimer_psf4,
            k_onDurationTimer_psf5,
            k_onDurationTimer_psf6,
            k_onDurationTimer_psf8,
            k_onDurationTimer_psf10,
            k_onDurationTimer_psf20,
            k_onDurationTimer_psf30,
            k_onDurationTimer_psf40,
            k_onDurationTimer_psf50,
            k_onDurationTimer_psf60,
            k_onDurationTimer_psf80,
            k_onDurationTimer_psf100,
            k_onDurationTimer_psf200,
        };
        int onDurationTimer_Pack(std::vector<uint8_t> &bits);
        int onDurationTimer_Unpack(std::vector<uint8_t> bits);
        int onDurationTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        onDurationTimer_Enum onDurationTimer_Value() const;
        int onDurationTimer_SetValue(onDurationTimer_Enum value);
        int onDurationTimer_SetValue(std::string value);
        std::string onDurationTimer_ValueToString(onDurationTimer_Enum value) const;
        uint64_t onDurationTimer_NumberOfValues() const;
        std::string onDurationTimer_ToString(uint32_t indent) const;
        std::string onDurationTimer_ToStringNoNewLines() const;
        int onDurationTimer_Clear();
        bool onDurationTimer_IsPresent() const;
    private:
        bool onDurationTimer_present;
        onDurationTimer_Enum onDurationTimer_internal_value;

        // drx-InactivityTimer
    public:
        enum drx_InactivityTimer_Enum {
            k_drx_InactivityTimer_psf1 = 0,
            k_drx_InactivityTimer_psf2,
            k_drx_InactivityTimer_psf3,
            k_drx_InactivityTimer_psf4,
            k_drx_InactivityTimer_psf5,
            k_drx_InactivityTimer_psf6,
            k_drx_InactivityTimer_psf8,
            k_drx_InactivityTimer_psf10,
            k_drx_InactivityTimer_psf20,
            k_drx_InactivityTimer_psf30,
            k_drx_InactivityTimer_psf40,
            k_drx_InactivityTimer_psf50,
            k_drx_InactivityTimer_psf60,
            k_drx_InactivityTimer_psf80,
            k_drx_InactivityTimer_psf100,
            k_drx_InactivityTimer_psf200,
            k_drx_InactivityTimer_psf300,
            k_drx_InactivityTimer_psf500,
            k_drx_InactivityTimer_psf750,
            k_drx_InactivityTimer_psf1280,
            k_drx_InactivityTimer_psf1920,
            k_drx_InactivityTimer_psf2560,
            k_drx_InactivityTimer_spare10,
            k_drx_InactivityTimer_spare9,
            k_drx_InactivityTimer_spare8,
            k_drx_InactivityTimer_spare7,
            k_drx_InactivityTimer_spare6,
            k_drx_InactivityTimer_spare5,
            k_drx_InactivityTimer_spare4,
            k_drx_InactivityTimer_spare3,
            k_drx_InactivityTimer_spare2,
            k_drx_InactivityTimer_spare1,
        };
        int drx_InactivityTimer_Pack(std::vector<uint8_t> &bits);
        int drx_InactivityTimer_Unpack(std::vector<uint8_t> bits);
        int drx_InactivityTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        drx_InactivityTimer_Enum drx_InactivityTimer_Value() const;
        int drx_InactivityTimer_SetValue(drx_InactivityTimer_Enum value);
        int drx_InactivityTimer_SetValue(std::string value);
        std::string drx_InactivityTimer_ValueToString(drx_InactivityTimer_Enum value) const;
        uint64_t drx_InactivityTimer_NumberOfValues() const;
        std::string drx_InactivityTimer_ToString(uint32_t indent) const;
        std::string drx_InactivityTimer_ToStringNoNewLines() const;
        int drx_InactivityTimer_Clear();
        bool drx_InactivityTimer_IsPresent() const;
    private:
        bool drx_InactivityTimer_present;
        drx_InactivityTimer_Enum drx_InactivityTimer_internal_value;

        // drx-RetransmissionTimer
    public:
        enum drx_RetransmissionTimer_Enum {
            k_drx_RetransmissionTimer_psf1 = 0,
            k_drx_RetransmissionTimer_psf2,
            k_drx_RetransmissionTimer_psf4,
            k_drx_RetransmissionTimer_psf6,
            k_drx_RetransmissionTimer_psf8,
            k_drx_RetransmissionTimer_psf16,
            k_drx_RetransmissionTimer_psf24,
            k_drx_RetransmissionTimer_psf33,
        };
        int drx_RetransmissionTimer_Pack(std::vector<uint8_t> &bits);
        int drx_RetransmissionTimer_Unpack(std::vector<uint8_t> bits);
        int drx_RetransmissionTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        drx_RetransmissionTimer_Enum drx_RetransmissionTimer_Value() const;
        int drx_RetransmissionTimer_SetValue(drx_RetransmissionTimer_Enum value);
        int drx_RetransmissionTimer_SetValue(std::string value);
        std::string drx_RetransmissionTimer_ValueToString(drx_RetransmissionTimer_Enum value) const;
        uint64_t drx_RetransmissionTimer_NumberOfValues() const;
        std::string drx_RetransmissionTimer_ToString(uint32_t indent) const;
        std::string drx_RetransmissionTimer_ToStringNoNewLines() const;
        int drx_RetransmissionTimer_Clear();
        bool drx_RetransmissionTimer_IsPresent() const;
    private:
        bool drx_RetransmissionTimer_present;
        drx_RetransmissionTimer_Enum drx_RetransmissionTimer_internal_value;

        // longDRX-CycleStartOffset
    public:
        enum longDRX_CycleStartOffset_Enum {
            k_longDRX_CycleStartOffset_sf10 = 0,
            k_longDRX_CycleStartOffset_sf20,
            k_longDRX_CycleStartOffset_sf32,
            k_longDRX_CycleStartOffset_sf40,
            k_longDRX_CycleStartOffset_sf64,
            k_longDRX_CycleStartOffset_sf80,
            k_longDRX_CycleStartOffset_sf128,
            k_longDRX_CycleStartOffset_sf160,
            k_longDRX_CycleStartOffset_sf256,
            k_longDRX_CycleStartOffset_sf320,
            k_longDRX_CycleStartOffset_sf512,
            k_longDRX_CycleStartOffset_sf640,
            k_longDRX_CycleStartOffset_sf1024,
            k_longDRX_CycleStartOffset_sf1280,
            k_longDRX_CycleStartOffset_sf2048,
            k_longDRX_CycleStartOffset_sf2560,
        };
        int longDRX_CycleStartOffset_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        longDRX_CycleStartOffset_Enum longDRX_CycleStartOffset_Choice() const;
        int longDRX_CycleStartOffset_SetChoice(longDRX_CycleStartOffset_Enum choice);
        std::string longDRX_CycleStartOffset_ChoiceToString(longDRX_CycleStartOffset_Enum value) const;
        uint64_t longDRX_CycleStartOffset_NumberOfChoices() const;
        std::string longDRX_CycleStartOffset_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_Clear();
        bool longDRX_CycleStartOffset_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_present;
        longDRX_CycleStartOffset_Enum longDRX_CycleStartOffset_internal_choice;

        // sf10
    public:
        int longDRX_CycleStartOffset_sf10_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf10_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf10_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf10_Value() const;
        int longDRX_CycleStartOffset_sf10_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf10_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf10_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf10_Clear();
        bool longDRX_CycleStartOffset_sf10_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf10_present;
        int64_t longDRX_CycleStartOffset_sf10_internal_value;

        // sf20
    public:
        int longDRX_CycleStartOffset_sf20_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf20_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf20_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf20_Value() const;
        int longDRX_CycleStartOffset_sf20_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf20_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf20_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf20_Clear();
        bool longDRX_CycleStartOffset_sf20_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf20_present;
        int64_t longDRX_CycleStartOffset_sf20_internal_value;

        // sf32
    public:
        int longDRX_CycleStartOffset_sf32_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf32_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf32_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf32_Value() const;
        int longDRX_CycleStartOffset_sf32_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf32_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf32_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf32_Clear();
        bool longDRX_CycleStartOffset_sf32_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf32_present;
        int64_t longDRX_CycleStartOffset_sf32_internal_value;

        // sf40
    public:
        int longDRX_CycleStartOffset_sf40_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf40_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf40_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf40_Value() const;
        int longDRX_CycleStartOffset_sf40_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf40_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf40_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf40_Clear();
        bool longDRX_CycleStartOffset_sf40_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf40_present;
        int64_t longDRX_CycleStartOffset_sf40_internal_value;

        // sf64
    public:
        int longDRX_CycleStartOffset_sf64_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf64_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf64_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf64_Value() const;
        int longDRX_CycleStartOffset_sf64_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf64_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf64_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf64_Clear();
        bool longDRX_CycleStartOffset_sf64_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf64_present;
        int64_t longDRX_CycleStartOffset_sf64_internal_value;

        // sf80
    public:
        int longDRX_CycleStartOffset_sf80_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf80_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf80_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf80_Value() const;
        int longDRX_CycleStartOffset_sf80_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf80_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf80_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf80_Clear();
        bool longDRX_CycleStartOffset_sf80_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf80_present;
        int64_t longDRX_CycleStartOffset_sf80_internal_value;

        // sf128
    public:
        int longDRX_CycleStartOffset_sf128_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf128_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf128_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf128_Value() const;
        int longDRX_CycleStartOffset_sf128_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf128_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf128_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf128_Clear();
        bool longDRX_CycleStartOffset_sf128_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf128_present;
        int64_t longDRX_CycleStartOffset_sf128_internal_value;

        // sf160
    public:
        int longDRX_CycleStartOffset_sf160_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf160_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf160_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf160_Value() const;
        int longDRX_CycleStartOffset_sf160_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf160_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf160_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf160_Clear();
        bool longDRX_CycleStartOffset_sf160_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf160_present;
        int64_t longDRX_CycleStartOffset_sf160_internal_value;

        // sf256
    public:
        int longDRX_CycleStartOffset_sf256_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf256_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf256_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf256_Value() const;
        int longDRX_CycleStartOffset_sf256_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf256_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf256_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf256_Clear();
        bool longDRX_CycleStartOffset_sf256_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf256_present;
        int64_t longDRX_CycleStartOffset_sf256_internal_value;

        // sf320
    public:
        int longDRX_CycleStartOffset_sf320_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf320_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf320_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf320_Value() const;
        int longDRX_CycleStartOffset_sf320_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf320_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf320_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf320_Clear();
        bool longDRX_CycleStartOffset_sf320_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf320_present;
        int64_t longDRX_CycleStartOffset_sf320_internal_value;

        // sf512
    public:
        int longDRX_CycleStartOffset_sf512_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf512_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf512_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf512_Value() const;
        int longDRX_CycleStartOffset_sf512_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf512_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf512_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf512_Clear();
        bool longDRX_CycleStartOffset_sf512_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf512_present;
        int64_t longDRX_CycleStartOffset_sf512_internal_value;

        // sf640
    public:
        int longDRX_CycleStartOffset_sf640_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf640_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf640_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf640_Value() const;
        int longDRX_CycleStartOffset_sf640_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf640_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf640_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf640_Clear();
        bool longDRX_CycleStartOffset_sf640_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf640_present;
        int64_t longDRX_CycleStartOffset_sf640_internal_value;

        // sf1024
    public:
        int longDRX_CycleStartOffset_sf1024_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf1024_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf1024_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf1024_Value() const;
        int longDRX_CycleStartOffset_sf1024_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf1024_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf1024_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf1024_Clear();
        bool longDRX_CycleStartOffset_sf1024_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf1024_present;
        int64_t longDRX_CycleStartOffset_sf1024_internal_value;

        // sf1280
    public:
        int longDRX_CycleStartOffset_sf1280_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf1280_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf1280_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf1280_Value() const;
        int longDRX_CycleStartOffset_sf1280_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf1280_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf1280_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf1280_Clear();
        bool longDRX_CycleStartOffset_sf1280_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf1280_present;
        int64_t longDRX_CycleStartOffset_sf1280_internal_value;

        // sf2048
    public:
        int longDRX_CycleStartOffset_sf2048_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf2048_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf2048_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf2048_Value() const;
        int longDRX_CycleStartOffset_sf2048_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf2048_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf2048_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf2048_Clear();
        bool longDRX_CycleStartOffset_sf2048_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf2048_present;
        int64_t longDRX_CycleStartOffset_sf2048_internal_value;

        // sf2560
    public:
        int longDRX_CycleStartOffset_sf2560_Pack(std::vector<uint8_t> &bits);
        int longDRX_CycleStartOffset_sf2560_Unpack(std::vector<uint8_t> bits);
        int longDRX_CycleStartOffset_sf2560_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
        int64_t longDRX_CycleStartOffset_sf2560_Value() const;
        int longDRX_CycleStartOffset_sf2560_SetValue(int64_t value);
        std::string longDRX_CycleStartOffset_sf2560_ToString(uint32_t indent) const;
        std::string longDRX_CycleStartOffset_sf2560_ToStringNoNewLines() const;
        int longDRX_CycleStartOffset_sf2560_Clear();
        bool longDRX_CycleStartOffset_sf2560_IsPresent() const;
    private:
        bool longDRX_CycleStartOffset_sf2560_present;
        int64_t longDRX_CycleStartOffset_sf2560_internal_value;


        // shortDRX
    public:
        class shortDRX
        {
        public:
            shortDRX() : present{false}, shortDRX_Cycle_present{false}, drxShortCycleTimer_present{false} {};
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

            // shortDRX-Cycle
        public:
            enum shortDRX_Cycle_Enum {
                k_shortDRX_Cycle_sf2 = 0,
                k_shortDRX_Cycle_sf5,
                k_shortDRX_Cycle_sf8,
                k_shortDRX_Cycle_sf10,
                k_shortDRX_Cycle_sf16,
                k_shortDRX_Cycle_sf20,
                k_shortDRX_Cycle_sf32,
                k_shortDRX_Cycle_sf40,
                k_shortDRX_Cycle_sf64,
                k_shortDRX_Cycle_sf80,
                k_shortDRX_Cycle_sf128,
                k_shortDRX_Cycle_sf160,
                k_shortDRX_Cycle_sf256,
                k_shortDRX_Cycle_sf320,
                k_shortDRX_Cycle_sf512,
                k_shortDRX_Cycle_sf640,
            };
            int shortDRX_Cycle_Pack(std::vector<uint8_t> &bits);
            int shortDRX_Cycle_Unpack(std::vector<uint8_t> bits);
            int shortDRX_Cycle_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            shortDRX_Cycle_Enum shortDRX_Cycle_Value() const;
            int shortDRX_Cycle_SetValue(shortDRX_Cycle_Enum value);
            int shortDRX_Cycle_SetValue(std::string value);
            std::string shortDRX_Cycle_ValueToString(shortDRX_Cycle_Enum value) const;
            uint64_t shortDRX_Cycle_NumberOfValues() const;
            std::string shortDRX_Cycle_ToString(uint32_t indent) const;
            std::string shortDRX_Cycle_ToStringNoNewLines() const;
            int shortDRX_Cycle_Clear();
            bool shortDRX_Cycle_IsPresent() const;
        private:
            bool shortDRX_Cycle_present;
            shortDRX_Cycle_Enum shortDRX_Cycle_internal_value;

            // drxShortCycleTimer
        public:
            int drxShortCycleTimer_Pack(std::vector<uint8_t> &bits);
            int drxShortCycleTimer_Unpack(std::vector<uint8_t> bits);
            int drxShortCycleTimer_Unpack(std::vector<uint8_t> bits, uint32_t &idx);
            int64_t drxShortCycleTimer_Value() const;
            int drxShortCycleTimer_SetValue(int64_t value);
            std::string drxShortCycleTimer_ToString(uint32_t indent) const;
            std::string drxShortCycleTimer_ToStringNoNewLines() const;
            int drxShortCycleTimer_Clear();
            bool drxShortCycleTimer_IsPresent() const;
        private:
            bool drxShortCycleTimer_present;
            int64_t drxShortCycleTimer_internal_value;

        };

        shortDRX shortDRX_value;

    };

    setup setup_value;

};

#endif
