/*
 Esp.h - ESP31B-specific APIs
 Copyright (c) 2015 Ivan Grokhotkov. All rights reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef ESP_H
#define ESP_H

#include "Arduino.h"

/**
 * AVR macros for WDT managment
 */
typedef enum {
    WDTO_0MS    = 0,   //!< WDTO_0MS
    WDTO_15MS   = 15,  //!< WDTO_15MS
    WDTO_30MS   = 30,  //!< WDTO_30MS
    WDTO_60MS   = 60,  //!< WDTO_60MS
    WDTO_120MS  = 120, //!< WDTO_120MS
    WDTO_250MS  = 250, //!< WDTO_250MS
    WDTO_500MS  = 500, //!< WDTO_500MS
    WDTO_1S     = 1000,//!< WDTO_1S
    WDTO_2S     = 2000,//!< WDTO_2S
    WDTO_4S     = 4000,//!< WDTO_4S
    WDTO_8S     = 8000 //!< WDTO_8S
} WDTO_t;


typedef enum {
    FM_QIO = 0x00,
    FM_QOUT = 0x01,
    FM_DIO = 0x02,
    FM_DOUT = 0x03,
    FM_FAST_READ = 0x04,
    FM_SLOW_READ = 0x05,
    FM_UNKNOWN = 0xff
} FlashMode_t;

class EspClass
{
public:
    EspClass() {}
    ~EspClass() {}
    void restart() {}
    uint32_t getFreeHeap() { return 0; }
    uint8_t getChipRevision() { return 0; }
    uint8_t getCpuFreqMHz(){ return 0; }
    uint32_t getCycleCount() { return 0; }
    const char * getSdkVersion() { return NULL; }

    void deepSleep(uint32_t time_us) {}

    uint32_t getFlashChipSize() { return 0; }
    uint32_t getFlashChipSpeed() { return 0; }
    FlashMode_t getFlashChipMode() { return FM_QIO; }

    uint32_t magicFlashChipSize(uint8_t byte) { return 0; }
    uint32_t magicFlashChipSpeed(uint8_t byte) { return 0; }
    FlashMode_t magicFlashChipMode(uint8_t byte) { return FM_QIO; }

    bool flashEraseSector(uint32_t sector) { return false; }
    bool flashWrite(uint32_t offset, uint32_t* data, size_t size) { return false; }
    bool flashRead(uint32_t offset, uint32_t* data, size_t size) { return false; }

    uint64_t getEfuseMac() { return 0; }

};

extern EspClass ESP;

#endif //ESP_H
