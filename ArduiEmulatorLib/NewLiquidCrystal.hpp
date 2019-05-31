//-------------------------------------------------------------------
#ifndef __NewLiquidCrystalEmulator_HPP__
#define __NewLiquidCrystalEmulator_HPP__
//-------------------------------------------------------------------

#include "LiquidCrystal.hpp"

#define LiquidCrystal_4bit_h

typedef enum { POSITIVE, NEGATIVE } t_backlighPol;

class LCD
{
protected:
	gcroot<LiquidCrystalManaged^> lcd;

public:

	LCD() {}

	virtual void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS) 
	{
		lcd = gcnew LiquidCrystalManaged();
		lcd->begin(cols, rows);
	}

	void noDisplay() { lcd->noDisplay(); }
	void display() { lcd->display(); }
	void noBlink() { lcd->noBlink(); }
	void blink() { lcd->blink(); }
	void noCursor() { lcd->noCursor(); }
	void cursor() { lcd->cursor(); }
	void scrollDisplayLeft() { lcd->scrollDisplayLeft(); }
	void scrollDisplayRight() { lcd->scrollDisplayRight(); }
	void leftToRight() { lcd->leftToRight(); }
	void rightToLeft() { lcd->rightToLeft(); }
	void autoscroll() { lcd->autoscroll(); }
	void noAutoscroll() { lcd->noAutoscroll(); }
	void setRowOffsets(int row1, int row2, int row3, int row4) {}
	void createChar(uint8_t, uint8_t[]) {}

	void clear()
	{
		lcd->clear();
	}

	void setCursor(uint8_t col, uint8_t row)
	{
		lcd->setCursor(col, row);
	}

	void home()
	{
		lcd->home();
	}
	
	size_t write(uint8_t ch)
	{
		return lcd->write(ch);
	}

	void moveCursorLeft() {}
	void moveCursorRight() {}
	void backlight(void) {}
	void on(void) {}
	void off(void) {}

	// Print part

	void print(String^ line)
	{
		lcd->print(line);
	}

	void print(const char *line)
	{
		lcd->print(gcnew String(line));
	}

	void print(int value)
	{
		lcd->print(value);
	}

	void print(int value, int i)
	{
		lcd->print(value, i);
	}
};

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------

class NewLiquidCrystal : public LCD
{
private:
	uint8_t _rs, _rw, _enable, _d0, _d1, _d2, _d3, _d4, _d5, _d6, _d7, _backlightPin;

public:
	NewLiquidCrystal(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
		this->init(0, rs, 0, enable, d0, d1, d2, d3, d4, d5, d6, d7, 0);
	}
	NewLiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
		this->init(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7, 0);
	}
	NewLiquidCrystal(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
		uint8_t backlightPin, t_backlighPol pol) {
		this->init(0, rs, 0, enable, d0, d1, d2, d3, d4, d5, d6, d7, backlightPin);
	}
	NewLiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
		uint8_t backlightPin, t_backlighPol pol) {
		this->init(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7, backlightPin);
	}
	NewLiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
		this->init(1, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0,0);
	}
	NewLiquidCrystal(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
		this->init(1, rs, 0, enable, d0, d1, d2, d3, 0, 0, 0, 0, 0);
	}
	NewLiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t backlightPin, t_backlighPol pol) {
		this->init(1, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0, backlightPin);
	}
	NewLiquidCrystal(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t backlightPin, t_backlighPol pol) {
		this->init(1, rs, 0, enable, d0, d1, d2, d3, 0, 0, 0, 0, backlightPin);
	}

	void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t backlightPin)
	{
		this->lcd = gcnew LiquidCrystalManaged();
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
		_backlightPin = backlightPin;
	}
};