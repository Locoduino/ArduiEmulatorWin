using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduiEmulatorWin
{
	public class ArduinoEsp32Devkit : ArduinoModel
	{
		public ArduinoEsp32Devkit()
		{
			this.Name = "DOIT ESP32 DEVKIT V1";
			this.RSName = "ESP32";

			this.PinNumberMax = 40;
			this.AnalogMax = 4095;

			this.pinFlags = new PinFunc[this.PinNumberMax];

			this.pinFlags[0] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;
			this.pinFlags[1] = PinFunc.Digital | PinFunc.PWM | PinFunc.Serial;
			this.pinFlags[2] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;
			this.pinFlags[3] = PinFunc.Digital | PinFunc.PWM | PinFunc.Serial;
			this.pinFlags[4] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;
			this.pinFlags[5] = PinFunc.Digital | PinFunc.PWM | PinFunc.SPI;
			this.pinFlags[6] = 0;
			this.pinFlags[7] = 0;
			this.pinFlags[8] = 0;
			this.pinFlags[9] = 0;
			this.pinFlags[10] = 0;
			this.pinFlags[11] = 0;
			this.pinFlags[12] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead; //D12
			this.pinFlags[13] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead; //D13
			this.pinFlags[14] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;	//D14
			this.pinFlags[15] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;	//D15
			this.pinFlags[16] = PinFunc.Digital | PinFunc.PWM | PinFunc.Serial; //RX2
			this.pinFlags[17] = PinFunc.Digital | PinFunc.PWM | PinFunc.Serial; //TX2
			this.pinFlags[18] = PinFunc.Digital | PinFunc.PWM | PinFunc.SPI;	//D18
			this.pinFlags[19] = PinFunc.Digital | PinFunc.PWM | PinFunc.SPI;	//D19
			this.pinFlags[20] = 0;
			this.pinFlags[21] = PinFunc.Digital | PinFunc.PWM | PinFunc.I2C;	//D21
			this.pinFlags[22] = PinFunc.Digital | PinFunc.PWM | PinFunc.Serial | PinFunc.I2C; //D22
			this.pinFlags[23] = PinFunc.Digital | PinFunc.PWM | PinFunc.SPI; //D23
			this.pinFlags[24] = 0;
			this.pinFlags[25] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;	//D25
			this.pinFlags[26] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;	//D26
			this.pinFlags[27] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;	//D27			
			this.pinFlags[28] = 0;
			this.pinFlags[29] = 0;
			this.pinFlags[30] = 0;
			this.pinFlags[31] = 0;
			this.pinFlags[32] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead; //D32
			this.pinFlags[33] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead; //D33
			this.pinFlags[34] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;	//D34
			this.pinFlags[35] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;	//D35
			this.pinFlags[36] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead;	//VP
			this.pinFlags[37] = 0;
			this.pinFlags[38] = 0;
			this.pinFlags[39] = PinFunc.Digital | PinFunc.PWM | PinFunc.AnalogRead | PinFunc.I2C;   //VN

			this.TimerNumberMax = 4;
			this.Timers = new List<Timer>(4);
			this.Timers.Add(new Timer());
			this.Timers.Add(new Timer());
			this.Timers.Add(new Timer());
			this.Timers.Add(new Timer());

			this.Timers[0].Caps = TimerCaps._16bits;
			this.Timers[1].Caps = TimerCaps._16bits;
			this.Timers[2].Caps = TimerCaps._16bits;
			this.Timers[3].Caps = TimerCaps._16bits;
		}
	}
}
