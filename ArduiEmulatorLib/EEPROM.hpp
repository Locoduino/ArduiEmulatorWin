//-------------------------------------------------------------------
#ifndef __EEPROM_HPP__
#define __EEPROM_HPP__
//-------------------------------------------------------------------

#include "ArduiEmulator.hpp"

#define INT64	(__int64)

#define EEPROMSIZE	8192
#define EEPROM		EEPROMClass::EEPROMInstance 

class EEPROMClass
{
private:
	char eeprom_image[8192];

public:
	EEPROMClass();
	unsigned char read(int);
	void write(int, unsigned char);
	void update(int, unsigned char);
	inline int length() { return 4096; }

	void get(int idx, void *data, unsigned long long inSize) {
		int e = idx;
		uint8_t *ptr = (uint8_t*)data;
		for (unsigned long long count = inSize; count; --count, ++e)
			*ptr++ = read(e);
	}

	void put(int idx, void *data, unsigned long long inSize) {
		int e = idx;
		const uint8_t *ptr = (const uint8_t*)data;
		for (unsigned long long count = inSize; count; --count, ++e)
			update(e, *ptr++);
	}

	static EEPROMClass EEPROMInstance;
	void writeFile();

	uint8_t _eeprom_read_byte(uint8_t *inAddress)
	{
		return EEPROMClass::EEPROMInstance.read((int)INT64 inAddress);
	}

	void _eeprom_write_byte(uint8_t *inAddress, uint8_t inValue)
	{
		EEPROMClass::EEPROMInstance.write((int)INT64 inAddress, inValue);
		//	EEPROMClass::EEPROMInstance.writeFile();
	}

	void _eeprom_update_byte(uint8_t *inAddress, uint8_t inValue)
	{
		if (_eeprom_read_byte(inAddress) == inValue)
			return;

		_eeprom_write_byte(inAddress, inValue);
	}

	void _eeprom_write_block(const void *inSrc, void *inDst, size_t inSize)
	{
		const byte* p = (const byte*)inSrc;
		int dst = (int)INT64 inDst;
		for (size_t i = 0; i < inSize; i++)
			EEPROMClass::EEPROMInstance.write((int)INT64 dst++, *(p++));
	}

	void _eeprom_read_block(void *inDst, const void *inSrc, size_t inSize)
	{
		byte* p = (byte*)inDst;
		int src = (int)INT64 inSrc;
		for (size_t i = 0; i < inSize; i++)
			*(p++) = EEPROMClass::EEPROMInstance.read((int)INT64 src++);
	}

	void _eeprom_update_block(const void *inSrc, void *inDst, size_t inSize)
	{
		_eeprom_write_block(inSrc, inDst, inSize);
	}
};

void eeprom_write_block(const void* inSrc, void* inDst, size_t inSize);
void eeprom_read_block(void* inDst, const void* inSrc, size_t inSize);
void eeprom_update_block(const void* inSrc, void* inDst, size_t inSize);

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------