//-------------------------------------------------------------------
#ifndef __bluetoothSerial_H__
#define __bluetoothSerial_H__
//-------------------------------------------------------------------

class BluetoothSerial
{
public:
	void begin(const char *name) {}
	void end() {}
	void flush() {}

	/*void print(const char *line);
	void println(const char *line);
	void print(const CString &line);
	void println(const CString &line);
	void print(int value);
	void print(int value, int i);
	void println(int value);
	void println(int value, int i);*/

	int available() { return 0;}
	char read() { return 0; }
	void write(char) {}
	//char peek();
};

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------