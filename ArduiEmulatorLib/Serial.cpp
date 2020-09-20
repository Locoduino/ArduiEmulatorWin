#include "stdafx.h"
#include "string.h"

#include "Arduino.h"
#include "ArduiEmulator.hpp"
#include "Serial.hpp"
#include "NamedPipes.h"
#include "WString.h"

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

size_t  SerialClass::print(const char line[])
{
	this->memo.Append(CString(line));
	return strlen(line);
}

size_t  SerialClass::println(const char line[])
{
	this->memo.Append(CString(line));
	NamedPipesSend(MessagesTypes::SerialMessage, this->memo);
	this->memo = "";
	return strlen(line);
}

size_t  SerialClass::print(const CString& line)
{
	this->memo.Append(CString(line));
	return line.GetLength();
}

size_t  SerialClass::println(const CString& line)
{
	this->memo.Append(CString(line));
	NamedPipesSend(MessagesTypes::SerialMessage, this->memo);
	this->memo = "";
	return line.GetLength();
}

size_t  SerialClass::print(const String& line)
{
	this->memo.Append(CString(line.c_str()));
	return line.length();
}

size_t  SerialClass::println(const String& line)
{
	this->memo.Append(CString(line.c_str()));
	NamedPipesSend(MessagesTypes::SerialMessage, this->memo);
	this->memo = "";
	return line.length();
}

size_t  SerialClass::print(char value)
{
	size_t size = this->memo.GetLength();
	this->memo.Append(CString(value));
	return this->memo.GetLength() - size;
}

size_t  SerialClass::print(int value)
{
	return print(value, DEC);
}

size_t  SerialClass::print(unsigned int value)
{
	return print((unsigned long) value);
}

size_t  SerialClass::print(long value)
{
	CString str;
	str.Format(_T("%ld"), value);
	print(str);
	return str.GetLength();
}

size_t  SerialClass::print(unsigned long value)
{
	CString str;
	str.Format(_T("%ld"), value);
	print(str);
	return str.GetLength();
}

size_t  SerialClass::print(int value, int i)
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

	return str.GetLength();
}

size_t  SerialClass::println(int value)
{
	size_t size = print(value, DEC);
	println("");
	return size;
}

size_t  SerialClass::println(unsigned int value)
{
	size_t size = print((long)value);
	println("");
	return size;
}

size_t  SerialClass::println(long value)
{
	size_t size = print(value);
	println("");
	return size;
}

size_t  SerialClass::println(unsigned long value)
{
	size_t size = print(value);
	println("");
	return size;
}

size_t  SerialClass::println(int value, int i)
{
	size_t size = print(value, i);
	println("");
	return size;
}

size_t  SerialClass::print(IPAddress inIp)
{
	CString str;
	str.Format(_T("%d.%d.%d.%d"), inIp[0], inIp[1], inIp[2], inIp[3]);
	print(str);
	return  str.GetLength();
}

size_t  SerialClass::println(IPAddress inIp)
{
	size_t size = print(inIp);
	println("");
	return size;
}

size_t SerialClass::printf(const char* format, ...)
{
	va_list argsList;
	char buffer[255];

	va_start(argsList, format);
	vsprintf_s(buffer, 255, format, argsList);
	va_end(argsList);
	print(buffer);
	return strlen(buffer);
}

int SerialClass::available()
{ 
	return this->inputBuffer.GetLength() > 0; 
}

void SerialClass::write(char value)
{
	print(value);
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
