//-------------------------------------------------------------------
#pragma once
#ifndef __arduinoEmulator_H__
#define __arduinoEmulator_H__
//-------------------------------------------------------------------

#include "binary.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include <atlstr.h>

typedef signed char		int8_t;
typedef unsigned char	uint8_t;
typedef unsigned short  uint16_t;
//typedef unsigned long   uint32_t;
typedef unsigned int 	word;
typedef short 	int16_t;
#define boolean			bool
typedef unsigned char	byte;

#define strcpy_P(d, s)	strcpy_s(d, this->sizex + 1, s)
#define memcpy_P(d, s, size)	memcpy(d, s, size)
#define strcmp_P(d, s)	strcmp(d, s)
#define strncmp_P(d, s, l)	strncmp(d, s, l)
#define strlen_P(s)	strlen(s)

#define HIGH	1
#define LOW		0

#define VS_LOW	-10
#define VS_HIGH	-20

#define INPUT			1
#define INPUT_PULLUP	3
#define OUTPUT			2
#define OUTPUT_RESERVED		-4
#define OUTPUT_INTERRUPT	-5

#define DEC		1
#define BIN		2
#define HEX		3
//#define NULL	0
#define PROGMEM
#define PGM_P   const char *

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define LED_BUILTIN	13

#define NOT_A_PIN -1
#define NOT_A_PORT -1
#define NOT_AN_INTERRUPT -1
#define NOT_ON_TIMER 0

#define F(__stringConstant)	__stringConstant
#define __FlashStringHelper	char

typedef void (*pinEvent)(int inPin);
typedef void (*debugLineEvent)(const char* inpLine);

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))
//#define max(i1, i2)	((i1)>(i2)?(i1):(i2))

#define word(...) makeWord(__VA_ARGS__)

#define bit(b) (1UL << (b))
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// avr-libc defines _NOP() since 1.6.2
#ifndef _NOP
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

#define VCPINNUMBER	200

extern long int _TCCR0A;
extern long int _TCCR0B;
extern long int _TCCR1A;
extern long int _TCCR1B;
extern long int _TCCR2A;
extern long int _TCCR2B;
extern long int _TCCR3A;
extern long int _TCCR3B;

extern long int _TIMSK0;
extern long int _TIMSK1;
extern long int _TIMSK2;
extern long int _TIMSK3;

extern long int _OCR0A;
extern long int _OCR0B;
extern long int _OCR1A;
extern long int _OCR1B;
extern long int _OCR2A;
extern long int _OCR2B;
extern long int _OCR3A;
extern long int _OCR3B;

extern long int _CLKPR;

extern unsigned char *__heap_start__;
extern unsigned char *__brkval__;

extern byte dontCheckNextPinAccess;

extern void delay(int millis);
extern void delayMicroseconds(int micros);

extern uint8_t pgm_read_byte(const uint8_t *str);
extern int pgm_read_word(const char *str);
extern void pinSetup();

extern void pinMode(int inPin, int inType);
extern void digitalWrite(int inPin, int inValue);
extern int digitalRead(int inPin);
extern void analogWrite(int inPin, int inValue);
extern int analogRead(int inPin);

extern void pinMode(int inPin, int inExpID, int inType);
extern void digitalWrite(int inPin, int inExpID, int inValue);
extern int digitalRead(int inPin, int inExpID);
extern void analogWrite(int inPin, int inExpID, int inValue);
extern int analogRead(int inPin, int inExpID);
extern void pinStateRaw(int inPin, int inExpID, int inState);

extern unsigned long millis();
extern unsigned long micros();

extern void noInterrupts();
extern void interrupts();
extern void attachInterrupt(uint8_t nb, void(*f)(void), int mode);
extern void detachInterrupt(uint8_t nb);
extern uint8_t digitalPinToInterrupt(uint8_t);

extern long map(long x, long in_min, long in_max, long out_min, long out_max);
extern double power(double val, int exp);
//extern uint16_t makeWord(uint16_t w);
extern uint16_t makeWord(uint8_t h, uint8_t l);
extern int freeMemory();

// Visual special commands
void AddExpander(int inPrefix, int inNumber, int inPinType, const CString &inName);
void ErrorMsg(const CString &message);
void _pinName(int inPin, int inExpID, const char *inName);

extern void _eventLog(const CString &inPrefix, unsigned long inId, int inEventType, int inData);

#define __TRUE	1
#define __FALSE	0

#include "Serial.hpp"
#include "EEPROM.hpp"

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------
