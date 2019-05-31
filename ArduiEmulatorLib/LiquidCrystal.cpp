#include "stdafx.h"

#include "ArduiEmulator.hpp"
#include "NamedPipes.h"
#include "LiquidCrystal.hpp"

// LiquidCrystal

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
	uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
	this->init(0, rs, 0, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}
LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
	uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
	this->init(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}
LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
	this->init(1, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}
LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
	this->init(1, rs, 0, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

void LiquidCrystal::init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
	uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
	//lcd = new LiquidCrystalManaged(); 
	_rs = rs;
	_rw = rw;
	_enable = enable;
	_d0 = d0;
	_d1 = d1;
	_d2 = d2;
	_d3 = d3;
	_d4 = d4;
	_d5 = d5;
	_d6 = d6;
	_d7 = d7;

	this->posCol = 0; 
	this->posRow = 0;
}

void LiquidCrystal::begin(uint8_t cols, uint8_t rows)
{
	this->begin(cols, rows, LCD_5x8DOTS);
}

void LiquidCrystal::begin(uint8_t cols, uint8_t rows, uint8_t charsize)
{
	CString str;
	str.Format(_T("BG %d %d"), (int) rows, (int) cols);
	NamedPipesSend(MessagesTypes::LcdMessage, str);

	if (_rs > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _rs, 0, OUTPUT_RESERVED);
	if (_rw > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _rw, 0, OUTPUT_RESERVED);
	if (_enable > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _enable, 0, OUTPUT_RESERVED);
	if (_d0 > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _d0, 0, OUTPUT_RESERVED);
	if (_d1 > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _d1, 0, OUTPUT_RESERVED);
	if (_d2 > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _d2, 0, OUTPUT_RESERVED);
	if (_d3 > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _d3, 0, OUTPUT_RESERVED);
	if (_d4 > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _d4, 0, OUTPUT_RESERVED);
	if (_d5 > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _d5, 0, OUTPUT_RESERVED);
	if (_d6 > 0)	NamedPipesSend(MessagesTypes::PinMessagePinMode, _d6, 0, OUTPUT_RESERVED);

	this->nbCols = cols;
	this->nbRows = rows;
}

void LiquidCrystal::clear()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("CL"));
	this->posCol = 0;
	this->posRow = 0;
}

void LiquidCrystal::setCursor(uint8_t col, uint8_t row)
{
	CString str;
	str.Format(_T("PR %d %d"), (int) row, (int) col);
	NamedPipesSend(MessagesTypes::LcdMessage, str);
	this->posCol = col;
	this->posRow = row;
}

void LiquidCrystal::home()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("HOME"));
	this->posCol = 0;
	this->posRow = 0;
}

size_t LiquidCrystal::write(uint8_t ch)
{
	CString str;
	str.Format(_T("WR %d"), (int) ch);
	NamedPipesSend(MessagesTypes::LcdMessage, str);
	return 1;
}

void LiquidCrystal::noDisplay()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("DISP 0"));
}

void LiquidCrystal::display()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("DISP 1"));
}

void LiquidCrystal::noBlink()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("BLK 0"));
}

void LiquidCrystal::blink()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("BLK 1"));
}

void LiquidCrystal::noCursor()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("CSR 0"));
}

void LiquidCrystal::cursor()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("CSR 1"));
}

void LiquidCrystal::scrollDisplayLeft()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("SCDISP 1"));
}

void LiquidCrystal::scrollDisplayRight()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("SCDISP 0"));
}

void LiquidCrystal::leftToRight()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("LTOR 1"));
}

void LiquidCrystal::rightToLeft()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("LTOR 0"));
}

void LiquidCrystal::noAutoscroll()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("AUTOSC 0"));
}

void LiquidCrystal::autoscroll()
{
	NamedPipesSend(MessagesTypes::LcdMessage, _T("AUTOSC 1"));
}

void LiquidCrystal::setRowOffsets(int row1, int row2, int row3, int row4) {}
void LiquidCrystal::createChar(uint8_t, uint8_t[]) {}
void LiquidCrystal::command(uint8_t) {}

// Print part

void LiquidCrystal::print(const CString &text)
{
	CString str;
	str.Format(_T("PR %d %d \"%s\""), this->posRow, this->posCol, (LPCTSTR)text);
	NamedPipesSend(MessagesTypes::LcdMessage, str);
	if (this->posCol < this->nbCols)
		this->posCol += text.GetLength();
}

void LiquidCrystal::print(const char *ptext)
{
	print(CString(ptext));
}

void LiquidCrystal::print(int value)
{
	print(value, DEC);
}

void LiquidCrystal::print(int value, int i)
{
	CString str;
	CString format = _T("%d");
	switch (i)
	{
	case DEC:
		break;
	case HEX:
		format = _T("%x");
		break;
	case BIN:
		format = _T("%b");
		break;
	}

	str.Format(format, value);
	print(str);
}

/*	void LiquidCrystal::println(String^ line)
{
	lcd->println(line);
}

	void LiquidCrystal::println(int value)
	{
		lcd->println(value);
	}

	void LiquidCrystal::println(int value, int i)
	{
		lcd->println(value, i);
	}*/
