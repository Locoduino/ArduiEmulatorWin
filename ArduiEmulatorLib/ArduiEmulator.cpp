#include "stdafx.h"
#include "string.h"
#include <time.h>
#include <chrono>
#include <thread>

#include "ArduiEmulator.hpp"
#include "NamedPipes.h"

long int _TCCR0A;
long int _TCCR0B;
long int _TCCR1A;
long int _TCCR1B;
long int _TCCR2A;
long int _TCCR2B;
long int _TCCR3A;
long int _TCCR3B;

long int _TIMSK0;
long int _TIMSK1;
long int _TIMSK2;
long int _TIMSK3;

long int _OCR0A;
long int _OCR0B;
long int _OCR1A;
long int _OCR1B;
long int _OCR2A;
long int _OCR2B;
long int _OCR3A;
long int _OCR3B;

long int _CLKPR;

long int _PORTA;
long int _PORTB;
long int _PORTC;
long int _PORTD;
long int _PORTE;
long int _PORTF;

long int _PINA;
long int _PINB;
long int _PINC;
long int _PIND;
long int _PINE;
long int _PINF;


unsigned char *__heap_start__;
unsigned char *__brkval__;

struct Pin
{
	int PinNumber;
	int ExpID;
	int State;
};

static Pin VCPins[VCPINNUMBER];
static int VC_pins[VCPINNUMBER];
byte dontCheckNextPinAccess = 2;  // 2 when the pins are not initialized !

// Emulator setup -----------------------------------------------------
void pinSetup()
{
	for (int i = 0; i < VCPINNUMBER; i++)
		VC_pins[i] = -1;
	for (int i = 0; i < VCPINNUMBER; i++)
		VCPins[i].PinNumber = -1;

	dontCheckNextPinAccess = __FALSE;
}

Pin* AddPin(int inPin, int inExp, int inState)
{
	if (dontCheckNextPinAccess == 2)
		pinSetup();

	for (int i = 0; i < VCPINNUMBER; i++)
	{
		if (VCPins[i].PinNumber == -1)
		{
			VCPins[i].PinNumber = inPin;
			VCPins[i].ExpID = inExp;
			VCPins[i].State = inState;
			return VCPins + i;
		}
	}

	// No more place !
	return NULL;	
}

Pin* GetPin(int inPin, int inExp)
{
	if (dontCheckNextPinAccess == 2)
		pinSetup();

	for (int i = 0; i < VCPINNUMBER; i++)
	{
		if (VCPins[i].PinNumber == inPin && VCPins[i].ExpID == inExp)
			return VCPins + i;
	}

	return NULL;
}

void AddExpander(int inPrefix, int inNumber, int inPinType, const CString &inName)
{
	if (dontCheckNextPinAccess == 2)
		pinSetup();

	NamedPipesSend(MessagesTypes::NewExpander, inPrefix, inNumber, inPinType, inName);
}

void ErrorMsg(const CString &message)
{
	if (dontCheckNextPinAccess == 2)
		pinSetup();

	NamedPipesSend(DebugMessage, message);
}

// Beware of the COMMANDERS_EVENT_TYPE and MOVE_TYPE modifications !

enum PRINT_MOVE_TYPE
{
	PRINT_MOVE_MORE = +1,
	PRINT_MOVE_LESS = -1,
	PRINT_MOVE_STOP = 0,
	PRINT_MOVE_LEFT = -2,
	PRINT_MOVE_RIGHT = -3,
	PRINT_MOVE_CENTER = -4,
	PRINT_MOVE_TOP = -5,
	PRINT_MOVE_BOTTOM = -6,
	PRINT_MOVE_STRAIGHT = -7,
	PRINT_MOVE_DIVERGE = -8,
	PRINT_MOVE_ON = -9,
	PRINT_MOVE_OFF = -10,
	PRINT_MOVE_LEAVE = -11
};

enum PRINT_EVENT_TYPE
{
	PRINT_EVENT_NONE = 0,			// Should never appear
	PRINT_EVENT_TOGGLE = 1,		// If a push button or similar is pressed, invert the state/position
	PRINT_EVENT_MOVE = 2,			// If a push 'left' button or similar is pressed, data is a COMMANDERS_MOVE_TYPE
	PRINT_EVENT_MOVEPOSITION = 3,	// If a potentiometer or similar is moved, data is the position to reach
	PRINT_EVENT_MOVEPOSITIONINDEX = 4,// Move to an indexed position from pMovingPosition given by data.
	PRINT_EVENT_MOVEPOSITIONID = 5,	// Move to an identified position from pMovingPosition, given by the event id.
	PRINT_EVENT_CONFIG = 6			// Data is the configuration address and value
};

#ifndef PRINTUNDEFINED_ID
#define PRINTUNDEFINED_ID	((unsigned long)-1)
#endif

#define PRINTCONFIGADDRESS(data)		highByte((int)data)
#define PRINTCONFIGVALUE(data)			lowByte((int)data)

CString _buildFormEventString(const CString &inPrefix, unsigned long inId, int inEventType, int inEventData)
{
	CString strId = _T("");
	CString strEvent = _T("");
	CString strData = _T("");

	if (inId == PRINTUNDEFINED_ID)
		strId = "UNDEFID";
	else
		strId.Format(_T("%d"), inId);

	switch (inEventType)
	{
	case PRINT_EVENT_NONE:			strEvent = "NONE";		break;
	case PRINT_EVENT_TOGGLE:		strEvent = "TOGGLE";	break;
	case PRINT_EVENT_MOVE:
		strEvent = "MOVE ";
		switch ((PRINT_MOVE_TYPE)inEventData)
		{
		case PRINT_MOVE_MORE:		strData = "MORE";		break;
		case PRINT_MOVE_LESS:		strData = "LESS";		break;
		case PRINT_MOVE_STOP:		strData = "STOP";		break;
		case PRINT_MOVE_LEFT:		strData = "LEFT";		break;
		case PRINT_MOVE_RIGHT:		strData = "RIGHT";		break;
		case PRINT_MOVE_CENTER:	strData = "CENTER";		break;
		case PRINT_MOVE_TOP:		strData = "TOP";		break;
		case PRINT_MOVE_BOTTOM:	strData = "BOTTOM";		break;
		case PRINT_MOVE_STRAIGHT:	strData = "STRAIGHT";	break;
		case PRINT_MOVE_DIVERGE:	strData = "DIVERGE";	break;
		case PRINT_MOVE_ON:		strData = "ON";			break;
		case PRINT_MOVE_OFF:		strData = "OFF";		break;
		case PRINT_MOVE_LEAVE:		strData = "LEAVE";		break;
		}
		break;
	case PRINT_EVENT_MOVEPOSITION:
		strEvent = "MOVEPOSITION";
		strData.Format(_T("%d"), inEventData);
		break;
	case PRINT_EVENT_MOVEPOSITIONID:
		strEvent = "MOVEPOSITIONID";
		break;
	case PRINT_EVENT_MOVEPOSITIONINDEX:
		strEvent = "MOVEPOSITIONINDEX";
		strData.Format(_T("%d"), inEventData);
		break;
	case PRINT_EVENT_CONFIG:
		strEvent = "CONFIG";
		strData.Format(_T("%d / %d"), PRINTCONFIGADDRESS(inEventData), PRINTCONFIGVALUE(inEventData));
		break;
	}

	CString buf;
	buf.Format(_T("%15s : %7s %10s %s"), (LPCTSTR)inPrefix, (LPCTSTR)strId, (LPCTSTR)strEvent, (LPCTSTR)strData);
	return buf;
}

void _eventLog(const CString &inPrefix, unsigned long inId, int inEventType, int inData)
{
	CString str = _buildFormEventString(inPrefix, inId, inEventType, inData);

	NamedPipesSend(MessagesTypes::DebugMessage, str);
}

// Emulator functions -------------------------------------------------
void delay(int millis)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
	//System::Threading::Thread::Sleep(millis);
}

void delayMicroseconds(int micros)
{
	//System::Threading::Thread::Sleep(millis);
}

uint8_t pgm_read_byte(const uint8_t *str)
{
	delay(10);
	return (uint8_t)*str;
}

int pgm_read_word(const char *str)
{
	return (int) (__int64)str;
}

void pinMode(int inPin, int inType)
{
	pinMode(inPin, 0, inType);
}

void pinMode(int inPin, int inExpID, int inType)
{
	Pin* pin = GetPin(inPin, inExpID);
	if (pin == NULL)
	{
		pin = AddPin(inPin, inExpID, VS_LOW);
	}

	switch (inType)
	{
	case INPUT:
		pin->State = VS_LOW;
		break;
	case INPUT_PULLUP:
		pin->State = VS_HIGH;
		break;
	case OUTPUT:
		pin->State = VS_LOW;
		break;
	case OUTPUT_RESERVED:
		pin->State = OUTPUT_RESERVED;
		break;
	case OUTPUT_INTERRUPT:
		pin->State = OUTPUT_INTERRUPT;
		break;
	}

	NamedPipesSend(MessagesTypes::PinMessagePinMode, inPin, inExpID, inType);
	NamedPipesSend(MessagesTypes::PinMessagePinState, inPin, inExpID, pin->State);
}

void digitalWrite(int inPin, int inValue)
{		
	digitalWrite(inPin, 0, inValue);
}

void digitalWrite(int inPin, int inExpID, int inValue)
{
	Pin* pin = GetPin(inPin, inExpID);

	if (dontCheckNextPinAccess == __FALSE)
	{
		if (inPin < 0 || inPin >= VCPINNUMBER)
			return;
	}

	int newvalue = inValue > 0 ? VS_HIGH : VS_LOW;

	if (pin == NULL)
		pin = AddPin(inPin, inExpID, newvalue);
	else 
	{
		if (pin->State != newvalue)
		{
			pin->State = newvalue;
			NamedPipesSend(MessagesTypes::PinMessagePinState, inPin, inExpID, pin->State);
		}
	}
}

int digitalRead(int inPin)
{		
	return digitalRead(inPin, 0);
}

int digitalRead(int inPin, int inExpID)
{
	Pin* pin = GetPin(inPin, inExpID);

	if (pin == NULL)
		pin = AddPin(inPin, inExpID, VS_LOW);

	return pin->State == VS_LOW ? LOW : HIGH;
}

void analogWrite(int inPin, int inValue)
{		
	analogWrite(inPin, 0, inValue);
}

void analogWrite(int inPin, int inExpID, int inValue)
{
	Pin* pin = GetPin(inPin, inExpID);

	if (pin == NULL)
		pin = AddPin(inPin, inExpID, inValue);
	else
	{
		if (inValue != pin->State)
		{
			pin->State = inValue;
			NamedPipesSend(MessagesTypes::PinMessagePinState, inPin, inExpID, pin->State);
		}
	}
}

int analogRead(int inPin)
{
	return analogRead(inPin, 0);
}

int analogRead(int inPin, int inExpID)
{
	Pin* pin = GetPin(inPin, inExpID);

	if (pin == NULL)
	{
		pin = AddPin(inPin, inExpID, 0);
		NamedPipesSend(MessagesTypes::PinMessagePinState, inPin, inExpID, pin->State);
	}

	return pin->State;
}

void pinStateRaw(int inPin, int inExpID, int inState)
{
	Pin* pin = GetPin(inPin, inExpID);

	if (inPin < 0 || inPin >= VCPINNUMBER)
		return;

	if (pin == NULL)
		pin = AddPin(inPin, inExpID, inState);
	else
	{
		if (pin->State != inState)
		{
			pin->State = inState;
			NamedPipesSend(MessagesTypes::PinMessagePinState, inPin, inExpID, pin->State);
		}
	}
}

unsigned long millis()
{
	return clock() / CLOCKS_PER_SEC * 1000;
}

unsigned long micros()
{
	return millis() * 1000;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double power(double val, int exp)
{
	double res = val;
	for (int i = 0; i < exp; i++)
		res *= val;

	return res;
}

void noInterrupts(void)
{}

void interrupts(void)
{}

void attachInterrupt(uint8_t nb, void(*f)(void) , int mode)
{}

void detachInterrupt(uint8_t nb)
{}

uint8_t digitalPinToInterrupt(uint8_t pin)
{
	// In Visual Studio mode, just use the pin itself !
	return pin;
}

/*uint16_t makeWord(uint16_t w)
{
	return w;
}	*/

uint16_t makeWord(uint8_t h, uint8_t l)
{
	return (h << (uint16_t)8) + l;
}

int freeMemory()
{
	// There is always free memory !
	return 20000;
}

void _pinName(int inPin, int inExpID, const char *inName)
{
	CString str = CString(inName);
	NamedPipesSend(MessagesTypes::PinMessagePinName, inPin, inExpID, str);
}
