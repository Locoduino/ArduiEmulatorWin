//-------------------------------------------------------------------
#ifndef __Wire_H__
#define __Wire_H__
//-------------------------------------------------------------------

#include "IPAddress.h"
#include "Arduino.h"

class WireClass
{
private:
	uint8_t bufferID = 0;
	byte buffer[1];
	unsigned char writeCount;
	unsigned char readCount;

public:
	void begin() {}
	void begin(uint8_t address) {}
	void begin(int address) {}
	void beginTransmission(uint8_t val) { this->writeCount = 0; bufferID = val; }
	uint8_t endTransmission() { return 0; }
	uint8_t endTransmission(bool stop) { return 0; }
	void onReceive(void(*)(int)) {}
	void onRequest(void(*)(void)) {}
	size_t write(uint8_t value) { buffer[this->writeCount++] = value; return 1; }
	size_t write(const uint8_t* pValue, size_t inSize)
	{
		for (size_t i = 0; i < inSize; i++)
			buffer[this->writeCount++] = pValue[i];

		return inSize;
	}
	uint8_t requestFrom(uint8_t inID, uint8_t size)
	{
		//		this->readCount = 0; 
		if (inID != bufferID)
			return 0;
		return this->writeCount;
	}
	int available() { return this->readCount < this->writeCount; }
	int read() { return buffer[this->readCount++]; }

	static WireClass WireInstance;
};

#define TwoWire		WireClass
#define HardwareWire	WireClass
#define Wire			WireClass::WireInstance

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------
