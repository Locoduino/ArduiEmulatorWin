#include "stdafx.h"
#include "string.h"
#include "NamedPipes.h"
#include "Arduino.h"
#include "ArduiEmulator.hpp"
#include <cctype>

//void TimerIdleBegin();

unsigned long __stdcall Receiver(void * pParam);
HANDLE hPipeSender = NULL, hPipeReceiver = NULL;
BOOL Finished;

//Pipe Init Data
CString bufferReceived;
int bufferReceivedPos = 0;
DWORD idleDelay = 0;

static bool initialized = false;
CString lpszPipenameSender;
CString lpszPipenameListener;

//Thread Init Data
HANDLE hThread = NULL;
HANDLE hTimer = NULL;

char startBuffer[100][200];
int startBufferCount = 0;

unsigned long __stdcall Receiver(void * pParam)
{
	BOOL fSuccess;
	char chBuf[500];
	DWORD cbRead;

	while (1)
	{
		if (hPipeReceiver == NULL)
		{
			do
			{
				hPipeReceiver = CreateNamedPipe(lpszPipenameListener,//The unique pipe name. This string must have the following form:  \\.\pipe\pipename
					PIPE_ACCESS_DUPLEX,
					PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_NOWAIT, //write and read and return right away
					PIPE_UNLIMITED_INSTANCES,//The maximum number of instances that can be created for this pipe
					4096, // output time-out 
					4096, // input time-out 
					0,//client time-out 
					NULL);
			}
			while (hPipeReceiver == NULL || hPipeReceiver == INVALID_HANDLE_VALUE);
		}

		fSuccess = ReadFile(hPipeReceiver, chBuf, 500, &cbRead, NULL);
		if (fSuccess)
		{
			CloseHandle(hPipeReceiver);
			hPipeReceiver = NULL;

			chBuf[cbRead] = 0;
			bufferReceived = chBuf;
//			printf(chBuf);
//			printf("\n");
		}

		if (Finished)
			break;
	}

	return 0;
}

void NamedPipesBegin(const CString &pipeSenderName, const CString &pipeListenerName, unsigned int inIdleDelay)
{
	Finished = FALSE;

	lpszPipenameSender = pipeSenderName;
	lpszPipenameListener = pipeListenerName;
	idleDelay = inIdleDelay;

	hThread = CreateThread(NULL, 0, &Receiver, NULL, 0, NULL);
	initialized = true;
}

void NamedPipesDispose()
{
	Finished = TRUE;
	CloseHandle(hPipeReceiver);
	CloseHandle(hPipeSender);
	CloseHandle(hTimer);
}

void startNamedPipes()
{
	NamedPipesBegin(L"\\\\.\\pipe\\ToArduino", L"\\\\.\\pipe\\FromArduino");

	NamedPipesSend(MessagesTypes::Reset, _T(""));
}

int NamedPipesSenderConnect()
{
	if (!initialized)
		return 0;

	hPipeSender = CreateFile(
		lpszPipenameSender, 
		GENERIC_WRITE, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);

	if (hPipeSender == NULL || hPipeSender == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	return 1;
}

void NamedPipesSend(MessagesTypes inType, int inPin, int inExpID, const CString &inMess)
{
	CString mess;

	mess.Format(_T("%d %d \"%s\""), inPin, inExpID, (LPCTSTR) inMess);
	NamedPipesSend(inType, mess);
}

void NamedPipesSend(MessagesTypes inType, int inPin, int inExpID, int inInt1, int inInt2)
{
	CString mess;

	mess.Format(_T("%d %d %d %d"), inPin, inExpID, inInt1, inInt2);
	NamedPipesSend(inType, mess);
}

void NamedPipesSend(MessagesTypes inType, int int1, int int2, int int3, const CString& inMess)
{
	CString mess;

	mess.Format(_T("%d %d %d \"%s\""), int1, int2, int3, (LPCTSTR) inMess);
	NamedPipesSend(inType, mess);
}

void NamedPipesSend(MessagesTypes inType, int inPin, int inExpID, int inInt)
{
	CString mess;

	mess.Format(_T("%d %d %d"), inPin, inExpID, inInt);
	NamedPipesSend(inType, mess);
}

void NamedPipesSend(MessagesTypes inType, const CString &mess) 
{
	CString str;

	if (inType != Reset && inType != Idle && mess.GetLength() == 0)
		return;

	switch (inType)
	{
	case Reset:
	{
		CString arduinoType;
#if defined(ARDUINO_ARCH_AVR)
#if defined(__AVR_ATmega328P__)
#if defined(ARDUINO_AVR_UNO)
		arduinoType = _T("UNO");
#elif defined(ARDUINO_AVR_NANO)
		arduinoType = _T("NANO");
#elif defined(ARDUINO_AVR_MINI)
		arduinoType = _T("MINI");
#endif
#elif defined(__AVR_ATmega32U4__)
		arduinoType = _T("PROMICRO");
#elif defined(__AVR_ATmega2560__)
		arduinoType = _T("MEGA2560");
#endif
#elif defined(ARDUINO_ARCH_ESP32)
		arduinoType = _T("ESP32");
#elif defined(ARDUINO_ARCH_STM32F1)
		arduinoType = _T("STM32F1");
#endif

		str.Format(_T("RS \"%s\""), (LPCTSTR) arduinoType);
	}
		break;
	case Idle:								str = "IDLE";		break;
	case SerialMessage:				str.Format(_T("SC \"%s\""), (LPCTSTR)mess);			break;
	case DebugMessage:				str.Format(_T("DB \"%s\""), (LPCTSTR)mess);			break;
	case PinMessagePinMode:		str.Format(_T("PM %s"), (LPCTSTR)mess);			break;
	case PinMessagePinState:	str.Format(_T("PS %s"), (LPCTSTR)mess);			break;
	case PinMessagePinName:		str.Format(_T("PN %s"), (LPCTSTR)mess);			break;
	case NewExpander:					str.Format(_T("EXP %s"), (LPCTSTR)mess);			break;
	case LcdMessage:					str.Format(_T("LCD %s"), (LPCTSTR)mess);			break;
	}

	if (!initialized)
	{
		CT2A ascii(str);
		strncpy_s(startBuffer[startBufferCount++], ascii.m_psz, 100);
		return;
	}

	if (inType == Reset)
		NamedPipesSendRaw(str);

	if (startBufferCount > 0)
	{
		for (int i = 0; i < startBufferCount; i++)
			NamedPipesSendRaw(CString(startBuffer[i]));
	}

	startBufferCount = 0;

	if (inType != Reset)
		NamedPipesSendRaw(str);
}

void NamedPipesSendRaw(const CString& mess)
{
	int count = 0;
	while (NamedPipesSenderConnect() == 0 && count < 50)
	{
		count++;
		Sleep(100);
	}

	if (hPipeSender == NULL || hPipeSender == INVALID_HANDLE_VALUE)
	{
		printf("Could not open the pipeSender  - (error %d), cannot send %Ls\n", GetLastError(), (LPCTSTR)mess);
		return;
	}

	DWORD cbWritten;

	WriteFile(hPipeSender, mess, mess.GetLength() * sizeof(TCHAR), &cbWritten, NULL);
}



bool ParseMessage(const CString &inMessage)
{
	CString tokens[10];
	CString Seperator = _T(" ");
	int Position = 0;
	int tokenNb = 0;
	CString Token;

	Token = inMessage.Tokenize(Seperator, Position);
	while (!Token.IsEmpty())
	{
		tokens[tokenNb++] = Token.MakeUpper();

		// Get next token.
		Token = inMessage.Tokenize(Seperator, Position);
	}

	if (tokens[0] == "PS")
	{
		int typeIndex = 0;
		CStringA charstr(tokens[1]);
		int pin = atoi((const char*)charstr);
		int exp = 0;

		if (tokenNb == 3)
			typeIndex = 2;
		if (tokenNb == 4)
		{
			charstr = CStringA(tokens[2]);
			exp = atoi((const char*)charstr);
			typeIndex = 3;
		}

		if (tokens[typeIndex][0] == 'H')
			pinStateRaw(pin, exp, VS_HIGH);
		if (tokens[typeIndex][0] == 'L')
			pinStateRaw(pin, exp, VS_LOW);
		if (std::isdigit(tokens[typeIndex][0]))
		{
			CStringA charstr(tokens[typeIndex]);
			int value = atoi((const char*)charstr);
			pinStateRaw(pin, exp, value);
		}
	}

	if (tokens[0] == "KBD")
	{
		CStringA charstr(tokens[1]);
		int key = (int) charstr[0];
		lastKeyPressed = key;
	}

	return false;
}

DWORD idleDate = 0;

int NamedPipesIdle()
{
	if (bufferReceived.GetLength() > 0)
	{
		ParseMessage(bufferReceived);
		bufferReceived.Empty();
	}

	if (GetTickCount() - idleDate > idleDelay)
	{
		NamedPipesSend(MessagesTypes::Idle, _T(""));
		idleDate = GetTickCount();
		return true;
	}
	return false;
}

void NamedPipesIdleReset()
{
	idleDate = GetTickCount();
}