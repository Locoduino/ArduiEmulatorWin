//-------------------------------------------------------------------
#ifndef __serial_Hpp__
#define __serial_Hpp__
//-------------------------------------------------------------------

#define Serial	SerialClass::SerialInstance[0]
#define Serial1	SerialClass::SerialInstance[1]
#define Serial2	SerialClass::SerialInstance[2]
#define Serial3	SerialClass::SerialInstance[3]
#define Serial4	SerialClass::SerialInstance[4]
#define Serial5	SerialClass::SerialInstance[5]
#define Serial6	SerialClass::SerialInstance[6]
#define Serial7	SerialClass::SerialInstance[7]

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

	void print(const char line[]);
	void println(const char line[]);
	void print(const CString &line);
	void println(const CString &line);
	void print(int value);
	void print(int value, int i);
	void println(int value);
	void println(int value, int i);

	void received(const CString &received);
	int available();
	char read();
	char peek();
};

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------