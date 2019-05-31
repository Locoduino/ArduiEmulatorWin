//-------------------------------------------------------------------
#ifndef __arduinoEmulator_INC__
#define __arduinoEmulator_INC__
//-------------------------------------------------------------------

#include "binary.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

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
typedef void (*debugLineEvent)(const char *inpLine);

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

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------
