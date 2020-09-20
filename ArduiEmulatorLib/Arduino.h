//-------------------------------------------------------------------
#ifndef __arduino_H__
#define __arduino_H__
//-------------------------------------------------------------------

#include "ArduiEmulator.hpp"

#define ARDUINO_ARCH_ESP32

//#define ARDUINO_ARCH_AVR

#ifdef ARDUINO_ARCH_AVR
	//#define ARDUINO_AVR_MEGA
	//#define __AVR_ATmega2560__
	#define ARDUINO_AVR_NANO
	#define __AVR_ATmega328P__
#endif

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

/*efine	WGM00		0
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

#define TCCR0A	_TCCR0A
#define TCCR0B	_TCCR0B
#define TCCR1A	_TCCR1A
#define TCCR1B	_TCCR1B
#define TCCR2A	_TCCR2A
#define TCCR2B	_TCCR2B
#define TCCR3A	_TCCR3A	
#define TCCR3B	_TCCR3B

#define TIMSK0	_TIMSK0	
#define TIMSK1	_TIMSK1	
#define TIMSK2	_TIMSK2	
#define TIMSK3	_TIMSK3	

#define OCR0A	_OCR0A	
#define OCR0B	_OCR0B	
#define OCR1A	_OCR1A	
#define OCR1B	_OCR1B	
#define OCR2A	_OCR2A	
#define OCR2B	_OCR2B	
#define OCR3A	_OCR3A	
#define OCR3B 	_OCR3B 	

#define CLKPR	_CLKPR

#define PINA		_PINA		
#define PINB		_PINB
#define PINC		_PINC
#define PIND		_PIND
#define PINE		_PINE
#define PINF		_PINF

#define PORTA		_PORTA
#define PORTB		_PORTB
#define PORTC		_PORTC
#define PORTD		_PORTD
#define PORTE		_PORTE
#define PORTF		_PORTF
*/
//#define __heap_start	ArduiEmulator::Arduino::__heap_start__
//#define __brkval		ArduiEmulator::Arduino::__brkval__

#define ISR(NAME)	void NAME##FUNC()

#ifdef ARDUINO_AVR_MEGA
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

#ifdef ARDUINO_AVR_NANO
#define A0		23
#define A1		24
#define A2		25
#define A3		26
#define A4		27
#define A5		28
#define A6		19
#define A7		22
#endif

#include "io.h"
//#include "avr/iocanxx.h"

#endif

#define __attribute__(x)
//efine E2END		10000

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

struct hw_timer_t
{
	byte id;
	int prescaler;
	int cntValue;
	int alarmValue;
	bool countUp;
	bool autoReload;
	bool edgeValue;

	void (*funcToCall)();

	bool enabled;
	bool alarmEnabled;
	int currentValue;

	hw_timer_t();
};

#define IRAM_ATTR

hw_timer_t* timerBegin(int id, int prescaler, bool restart);
void timerAttachInterrupt(hw_timer_t *pTimer, void (*funcToCall)(), bool edgeValue);
void timerAlarmWrite(hw_timer_t *pTimer, int timerDelay, bool alwaysRestart);
void timerWrite(hw_timer_t*, int);
void timerAlarmEnable(hw_timer_t*);
void timerStart(hw_timer_t*);
void timerStop(hw_timer_t *);
void timerAlarmDisable(hw_timer_t*);
void timerDetachInterrupt(hw_timer_t*);
void timerEnd(hw_timer_t*);

void timersLoop(void);

typedef int TaskHandle_t;

void xTaskCreatePinnedToCore(void (*) (void*), const char*, int, void*, int, TaskHandle_t*, int);
int xPortGetCoreID();

void disableCore0WDT(void);
void enableCore0WDT(void);
void disableCore1WDT(void);
void enableCore1WDT(void);

#include "esp.h"
#include "esp_event.h"
#endif

#define digitalPinToPort(P) ( P )
#define digitalPinToBitMask(P) ( P )
#define digitalPinToTimer(P) ( P )
#define analogInPinToBit(P) (P)
#define portOutputRegister(P) ( (volatile uint8_t *)( P ) )
#define portInputRegister(P) ( (volatile uint8_t *)( P ) )
#define portModeRegister(P) ( (volatile uint8_t *)( P ) )

//-------------------------------------------------------------------
#endif


//-------------------------------------------------------------------
