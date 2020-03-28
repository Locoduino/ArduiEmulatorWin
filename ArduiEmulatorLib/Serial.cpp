#include "stdafx.h"
#include "string.h"

#include "Arduino.h"
#include "ArduiEmulator.hpp"
#include "Serial.hpp"
#include "NamedPipes.h"

SerialClass SerialClass::SerialInstance[];

void SerialClass::begin(int)
{
	/*ArduiEmulator::ArduinoForm::SerialBuffer = String::Empty;
	this->memo = this->memo->Empty;*/
	this->memo = "";
	this->inputBuffer = "";
}

void SerialClass::end()
{
}

void SerialClass::flush()
{
	this->memo = "";
}

void SerialClass::print(const char line[])
{
	this->memo.Append(CString(line));
}

void SerialClass::println(const char line[])
{
	this->memo.Append(CString(line));
	NamedPipesSend(MessagesTypes::SerialMessage, this->memo);
	this->memo = "";
}

void SerialClass::print(const CString &line)
{
	this->memo.Append(CString(line));
}

void SerialClass::println(const CString &line)
{
	this->memo.Append(CString(line));
	NamedPipesSend(MessagesTypes::SerialMessage, this->memo);
	this->memo = "";
}

void SerialClass::print(int value)
{
	print(value, DEC);
}

void SerialClass::print(int value, int i)
{
	CString str;
	switch (i)
	{
	case DEC:
		str.Format(_T("%d"), value);
		print(str);
		break;
	case HEX:
		str.Format(_T("%x"), value);
		print(str);
		break;
	case BIN:
		str.Format(_T("%d"), value);
		print(str);
		break;
	}
}

void SerialClass::println(int value)
{
	print(value, DEC);
	println("");
}

void SerialClass::println(int value, int i)
{
	print(value, i);
	println("");
}

int SerialClass::available()
{ 
	return this->inputBuffer.GetLength() > 0; 
}

char SerialClass::read()
{
	if (this->inputBuffer.GetLength() == 0)
	{
		CString buf = _T("Serial read without data");
		ErrorMsg(buf);
		return 0;
	}

	byte c =(byte) this->inputBuffer[0];
	this->inputBuffer.Delete(0);
	return c;
}

char SerialClass::peek()
{
	if (this->inputBuffer.GetLength() == 0)
	{
		CString buf = _T("Serial peek without data");
		ErrorMsg(buf);
		return 0;
	}

	return (char)this->inputBuffer[0];
}

void SerialClass::received(const CString& buffer)
{
	this->inputBuffer = buffer;
}
