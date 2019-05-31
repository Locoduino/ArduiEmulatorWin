#define RELEASE		1
#define FORWARD		2
#define BACKWARD	3

#define MOTOR12_1KHZ		1
#define MOTOR34_1KHZ		4

class AF_DCMotor
{
public:
	AF_DCMotor(int, int) {}

	void run(int) {}
	void setSpeed(uint8_t) {}

	int pwmfreq;
};
