//-------------------------------------------------------------------
#ifndef __serial_Hpp__
#define __serial_Hpp__
//-------------------------------------------------------------------

#include "IPAddress.h"

#define Serial	SerialClass::SerialInstance[0]
#define Serial1	SerialClass::SerialInstance[1]
#define Serial2	SerialClass::SerialInstance[2]
#define Serial3	SerialClass::SerialInstance[3]
#define Serial4	SerialClass::SerialInstance[4]
#define Serial5	SerialClass::SerialInstance[5]
#define Serial6	SerialClass::SerialInstance[6]
#define Serial7	SerialClass::SerialInstance[7]

class IPAddress;
class String;

class SerialClass
{
private:
	CString memo;
	CString inputBuffer;

public:
	static SerialClass SerialInstance[8];

	void begin(int);
	void end();
	void flush();

	size_t print(const char line[]);
	size_t println(const char line[] = "");
	size_t print(const CString& line);
	size_t println(const CString& line);
	size_t print(const String& line);
	size_t println(const String& line);
	size_t print(char value);
	size_t print(int value);
	size_t print(unsigned int value);
	size_t print(long value);
	size_t print(unsigned long value);
	size_t print(int value, int i);
	size_t println(int value);
	size_t println(unsigned int value);
	size_t println(long value);
	size_t println(unsigned long value);
	size_t println(int value, int i);
	size_t print(IPAddress inIp);
	size_t println(IPAddress inIp);
	size_t printf(const char* format, ...);

	void received(const CString &received);
	int available();
	char read();
	char peek();
	void write(char value);
};

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------
