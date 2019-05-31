//-------------------------------------------------------------------
#ifndef __arduino_H__
#define __arduino_H__
//-------------------------------------------------------------------

#include "ArduiEmulator.hpp"

//#define ARDUINO_ARCH_ESP32

#define ARDUINO_ARCH_AVR

#ifdef ARDUINO_ARCH_AVR
	#define ARDUINO_AVR_MEGA
	#define __AVR_ATmega2560__
#endif

//#define pgm_read_byte(TT)			ArduiEmulator::Arduino::_pgm_read_byte(TT)

/*
#define pgm_read_word(TT)			ArduiEmulator::Arduino::_pgm_read_word(TT)
#define pgm_read_byte(BUFF)			((char)*(BUFF))
#define pgm_read_byte_near(BUFF)	((char)*(BUFF))

#define pinSetup()					ArduiEmulator::Arduino::_pinSetup()
#define pinMode(PIN, MODE)			ArduiEmulator::Arduino::_pinMode(PIN, MODE)
#define digitalWrite(PIN, VAL)		ArduiEmulator::Arduino::_digitalWrite(PIN, VAL)
#define digitalRead(PIN)			ArduiEmulator::Arduino::_digitalRead(PIN)
#define analogWrite(PIN, VAL)		ArduiEmulator::Arduino::_analogWrite(PIN, VAL)
#define analogRead(PIN)				ArduiEmulator::Arduino::_analogRead(PIN)
#define millis()					ArduiEmulator::Arduino::_millis()
#define micros()					ArduiEmulator::Arduino::_micros()
#define delay(TT)					ArduiEmulator::Arduino::_delay(TT)
#define delayMicroseconds(TT)		ArduiEmulator::Arduino::_delayMicroseconds(TT)

#define map(v1, v2, v3, v4, v5)		ArduiEmulator::Arduino::_map(v1, v2, v3, v4, v5)
#define power(VAL, EXP)				ArduiEmulator::Arduino::_power(VAL, EXP)

#define noInterrupts()				ArduiEmulator::Arduino::_noInterrupts()
#define interrupts()				ArduiEmulator::Arduino::_interrupts()
#define attachInterrupt(TT, FF, MM)	ArduiEmulator::Arduino::_attachInterrupt(TT, FF, MM)
#define detachInterrupt(TT)			ArduiEmulator::Arduino::_detachInterrupt(TT)
#define digitalPinToInterrupt(TT)	ArduiEmulator::Arduino::_digitalPinToInterrupt(TT)	 */

//#define makeWord(WW)				ArduiEmulator::Arduino::_makeWord(WW)
/*#define makeWord(HH, LL)			ArduiEmulator::Arduino::_makeWord(WW, LL)

#define freeMemory()				ArduiEmulator::Arduino::_freeMemory()

#define pinName(PIN, NAME)			ArduiEmulator::Arduino::__pinName(PIN, NAME)

#define eeprom_read_byte(AA)							EEPROMClass::EEPROMInstance._eeprom_read_byte(AA)
#define eeprom_write_byte(AA, VV)						EEPROMClass::EEPROMInstance._eeprom_write_byte(AA, VV)
#define eeprom_update_byte(AA, VV)						EEPROMClass::EEPROMInstance._eeprom_update_byte(AA, VV)
#define eeprom_write_block(__SRC, __DST, __SIZE)		EEPROMClass::EEPROMInstance._eeprom_write_block((__SRC), (__DST), (__SIZE))
#define eeprom_read_block(__SRC, __DST, __SIZE)			EEPROMClass::EEPROMInstance._eeprom_read_block(__SRC, __DST, __SIZE)
#define eeprom_update_block(__SRC, __DST, __SIZE)		EEPROMClass::EEPROMInstance._eeprom_update_block(__SRC, __DST, __SIZE)

#define pinName(PIN, NAME)			ArduiEmulator::Arduino::__pinName(PIN, NAME)*/

//#define strcpy_P(D, S)				strcpy(D, S)

/*#define HardwareSerial		SerialClass
#define Serial		SerialClass::SerialInstance
#define Serial1		SerialClass::SerialInstance
#define Serial2		SerialClass::SerialInstance
#define Serial3		SerialClass::SerialInstance*/

//#include "EEPROM.h"
//#define EEPROM		EEPROMClass::EEPROMInstance

#ifdef ARDUINO_ARCH_AVR
#define NUM_DIGITAL_PINS            70
#define NUM_ANALOG_INPUTS           16

#define	CS00		0
#define	CS01		1
#define	CS02		2
#define	CS03		3
#define	CS04		4
#define	CS05		5
#define	CS06		6
#define	CS07		7
#define	CS08		8
#define	CS09		9
#define	CS10		0
#define	CS11		1
#define	CS12		2
#define	CS13		3
#define	CS14		4
#define	CS15		5
#define	CS16		6
#define	CS17		7
#define	CS18		8
#define	CS19		9
#define	CS20		0
#define	CS21		1
#define	CS22		2
#define	CS23		3
#define	CS24		4
#define	CS25		5
#define	CS26		6
#define	CS27		7
#define	CS28		8
#define	CS29		9
#define	CS30		0
#define	CS31		1
#define	CS32		2

#define	WGM00		0
#define	WGM01		1
#define	WGM02		2
#define	WGM03		3
#define	WGM10		4
#define	WGM11		5
#define	WGM12		6
#define	WGM13		7
#define	WGM30		8
#define	WGM31		9
#define	WGM32		10
#define	WGM33		11

#define COM0B0		0
#define COM0B1		1
#define COM1B0		0
#define COM1B1		1
#define COM3B0		0
#define COM3B1		1

#define OCIE0B		0
#define OCIE1B		1
#define OCIE2B		2
#define OCIE3B		3

#define TCCR0A	ArduiEmulator::Arduino::_TCCR0A
#define TCCR0B	ArduiEmulator::Arduino::_TCCR0B
#define TCCR1A	ArduiEmulator::Arduino::_TCCR1A
#define TCCR1B	ArduiEmulator::Arduino::_TCCR1B
#define TCCR2A	ArduiEmulator::Arduino::_TCCR2A
#define TCCR2B	ArduiEmulator::Arduino::_TCCR2B
#define TCCR3A	ArduiEmulator::Arduino::_TCCR3A	
#define TCCR3B	ArduiEmulator::Arduino::_TCCR3B

#define TIMSK0	ArduiEmulator::Arduino::_TIMSK0	
#define TIMSK1	ArduiEmulator::Arduino::_TIMSK1	
#define TIMSK2	ArduiEmulator::Arduino::_TIMSK2	
#define TIMSK3	ArduiEmulator::Arduino::_TIMSK3	

#define OCR0A	ArduiEmulator::Arduino::_OCR0A	
#define OCR0B	ArduiEmulator::Arduino::_OCR0B	
#define OCR1A	ArduiEmulator::Arduino::_OCR1A	
#define OCR1B	ArduiEmulator::Arduino::_OCR1B	
#define OCR2A	ArduiEmulator::Arduino::_OCR2A	
#define OCR2B	ArduiEmulator::Arduino::_OCR2B	
#define OCR3A	ArduiEmulator::Arduino::_OCR3A	
#define OCR3B 	ArduiEmulator::Arduino::_OCR3B 	

#define CLKPR	ArduiEmulator::Arduino::_CLKPR	

//#define __heap_start	ArduiEmulator::Arduino::__heap_start__
//#define __brkval		ArduiEmulator::Arduino::__brkval__

#define ISR(NAME)	void NAME##FUNC()

#define A0		54
#define A1		55
#define A2		56
#define A3		57
#define A4		58
#define A5		59
#define A6		60
#define A7		61
#define A8		62
#define A9		63
#define A10		64
#define A11		65
#define A12		66
#define A13		67
#define A14		68
#define A15		69
#endif

#define __attribute__(x)
#define E2END		10000

#ifdef ARDUINO_ARCH_ESP32
#define EXTERNAL_NUM_INTERRUPTS 16
#define NUM_DIGITAL_PINS        40
#define NUM_ANALOG_INPUTS       16

#define analogInputToDigitalPin(p)  (((p)<20)?(esp32_adc2gpio[(p)]):-1)
//#define digitalPinToInterrupt(p)    (((p)<40)?(p):-1)
#define digitalPinHasPWM(p)         (p < 34)

static const uint8_t TX = 1;
static const uint8_t RX = 3;

static const uint8_t SDA = 21;
static const uint8_t SCL = 22;

static const uint8_t SS = 5;
static const uint8_t MOSI = 23;
static const uint8_t MISO = 19;
static const uint8_t SCK = 18;

static const uint8_t A0 = 36;
static const uint8_t A3 = 39;
static const uint8_t A4 = 32;
static const uint8_t A5 = 33;
static const uint8_t A6 = 34;
static const uint8_t A7 = 35;
static const uint8_t A10 = 4;
static const uint8_t A11 = 0;
static const uint8_t A12 = 2;
static const uint8_t A13 = 15;
static const uint8_t A14 = 13;
static const uint8_t A15 = 12;
static const uint8_t A16 = 14;
static const uint8_t A17 = 27;
static const uint8_t A18 = 25;
static const uint8_t A19 = 26;

static const uint8_t T0 = 4;
static const uint8_t T1 = 0;
static const uint8_t T2 = 2;
static const uint8_t T3 = 15;
static const uint8_t T4 = 13;
static const uint8_t T5 = 12;
static const uint8_t T6 = 14;
static const uint8_t T7 = 27;
static const uint8_t T8 = 33;
static const uint8_t T9 = 32;

static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26; 
#endif

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------
