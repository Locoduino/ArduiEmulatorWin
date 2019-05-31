class Servo
{
public:
	Servo() { this->pin = -1;  }

	void attach(int inPin) { analogRead(inPin);  this->pin = inPin; }
	void detach() { this->pin = -1; }
	void write(int) {}
	int read() { return 0; }
	bool attached() { return this->pin != -1; }

	int servoIndex;
	int pin;
};
