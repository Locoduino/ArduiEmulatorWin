#ifndef LiquidCrystal_h
#define LiquidCrystal_h

#include "string.h"
#include "ArduiEmulator.hpp"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

/*class LiquidCrystalManaged
{
private:
	uint8_t posRow, posCol;
	uint8_t nbRows, nbCols;

	bool Display, Blink, Cursor, Autoscroll, ScrollToLeft, LeftToRight;

public:
	LiquidCrystalManaged();
    
	void begin(uint8_t cols, uint8_t rows);
	void begin(uint8_t cols, uint8_t rows, uint8_t charsize);
	void clear();
	void setCursor(uint8_t col, uint8_t row);
	void home();
	size_t write(uint8_t ch);
	void noDisplay();
	void display();
	void noBlink();
	void blink();
	void noCursor();
	void cursor();
	void scrollDisplayLeft();
	void scrollDisplayRight();
	void leftToRight();
	void rightToLeft();
	void autoscroll();
	void noAutoscroll();
	void setRowOffsets(int row1, int row2, int row3, int row4);
	void createChar(uint8_t, uint8_t[]);
	void command(uint8_t);

	// Print part

	void print(const CString &text);
	void print(int value);
	void print(int value, int i);
};*/

class LiquidCrystal
{
private:
	//LiquidCrystalManaged *lcd;
	int posCol, posRow;
	int nbCols, nbRows;
	uint8_t _rs, _rw, _enable, _d0, _d1, _d2, _d3, _d4, _d5, _d6, _d7;

public:
	LiquidCrystal(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
	LiquidCrystal(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

	void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
		uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

	void begin(uint8_t cols, uint8_t rows);
	void begin(uint8_t cols, uint8_t rows, uint8_t charsize);
	void clear();
	void setCursor(uint8_t col, uint8_t row);
	void home();
	size_t write(uint8_t ch);
	void noDisplay();
	void display();
	void noBlink();
	void blink();
	void noCursor();
	void cursor();
	void scrollDisplayLeft();
	void scrollDisplayRight();
	void leftToRight();
	void rightToLeft();
	void autoscroll();
	void noAutoscroll();
	void setRowOffsets(int row1, int row2, int row3, int row4);
	void createChar(uint8_t, uint8_t[]);
	void command(uint8_t);

	// Print part

	void print(const CString &line);
	void print(const char *line);
	//	void println(String^ line);
	void print(int value);
	void print(int value, int i);
	//	void println(int value);
	// void println(int value, int i);
};
#endif
