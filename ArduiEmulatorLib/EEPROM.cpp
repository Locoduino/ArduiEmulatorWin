#include "EEPROM.hpp"

//////////////////////////////////////////
// EEPROM

#define EEPROM_FILE	"d:\\EEPROM.txt"

EEPROMClass EEPROMClass::EEPROMInstance;

void EEPROMClass::writeFile()
{
	FILE * fp;

	int err = fopen_s(&fp, EEPROM_FILE, "w+");
	fwrite(this->eeprom_image, 1, EEPROMSIZE, fp);
	fclose(fp);

/*	System::IO::FileStream^ fs = gcnew System::IO::FileStream(EEPROM_FILE, System::IO::FileMode::OpenOrCreate, System::IO::FileAccess::ReadWrite);
	fs->Write(this->eeprom_image, 0, 4096);
	fs->Close();*/
}

EEPROMClass::EEPROMClass()
{
	FILE * fp;

	int err = fopen_s(&fp, EEPROM_FILE, "r+");
	if (fp == NULL)
	{
		int err = fopen_s(&fp, EEPROM_FILE, "w+");
		fwrite("\0", 1, EEPROMSIZE, fp);
	}

	fclose(fp);

	/*
	System::IO::FileStream^ fs;
	if (!System::IO::File::Exists(EEPROM_FILE))
	{
		fs = gcnew System::IO::FileStream(EEPROM_FILE, System::IO::FileMode::OpenOrCreate, System::IO::FileAccess::ReadWrite);
		// to empty the file and have a good size !
		fs->Write(this->eeprom_image, 0, 4096);
	}
	else
	{
		fs = gcnew System::IO::FileStream(EEPROM_FILE, System::IO::FileMode::OpenOrCreate, System::IO::FileAccess::ReadWrite);
		fs->Read(this->eeprom_image, 0, 4096);
	}

	fs->Close();*/
}

unsigned char EEPROMClass::read(int inAddress)
{
	return this->eeprom_image[inAddress];
}

void EEPROMClass::write(int inAddress, unsigned char inValue)
{
	this->eeprom_image[inAddress] = inValue;

	int i = 0;
	if ((int)inAddress == 64)
		i = 10;

	this->writeFile();
}

void EEPROMClass::update(int inAddress, unsigned char inValue)
{
	if (this->read(inAddress) != inValue) {
		this->write(inAddress, inValue);
	}
}

#define INT64	(__int64)

uint8_t eeprom_read_byte(uint8_t *inAddress)
{
	return EEPROMClass::EEPROMInstance.read((int)INT64 inAddress);
}

void eeprom_write_byte(uint8_t *inAddress, uint8_t inValue)
{
	EEPROMClass::EEPROMInstance.write((int)INT64 inAddress, inValue);
	//	EEPROMClass::EEPROMInstance.writeFile();
}

void eeprom_update_byte(uint8_t *inAddress, uint8_t inValue)
{
	if (eeprom_read_byte(inAddress) == inValue)
		return;

	eeprom_write_byte(inAddress, inValue);
}

void eeprom_write_block(const void *inSrc, void *inDst, size_t inSize)
{
	const byte* p = (const byte*)inSrc;
	int dst = (int)INT64 inDst;
	for (size_t i = 0; i < inSize; i++)
		EEPROMClass::EEPROMInstance.write((int)INT64 dst++, *(p++));
}

void eeprom_read_block(void *inDst, const void *inSrc, size_t inSize)
{
	byte* p = (byte*)inDst;
	int src = (int)INT64 inSrc;
	for (size_t i = 0; i < inSize; i++)
		*(p++) = EEPROMClass::EEPROMInstance.read((int)INT64 src++);
}

void eeprom_update_block(const void *inSrc, void *inDst, size_t inSize)
{
	eeprom_write_block(inSrc, inDst, inSize);
}