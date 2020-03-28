using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduiEmulatorWin
{
	public class ArduinoNano : ArduinoModel
	{
		public ArduinoNano()
		{
			this.Name = "Nano R3";
			this.RSName = "NANO";
			this.PinNumberMax = 22;
			this.AnalogMax = 1023;

			this.pinFlags = new PinFunc[this.PinNumberMax];

			this.pinFlags[0] = PinFunc.Digital | PinFunc.Serial;
			this.pinFlags[1] = PinFunc.Digital | PinFunc.Serial;
			this.pinFlags[2] = PinFunc.Digital | PinFunc.Interrupt;
			this.pinFlags[3] = PinFunc.Digital | PinFunc.Interrupt | PinFunc.PWM;
			this.pinFlags[4] = PinFunc.Digital;
			this.pinFlags[5] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[6] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[7] = PinFunc.Digital;
			this.pinFlags[8] = PinFunc.Digital;
			this.pinFlags[9] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[10] = PinFunc.Digital | PinFunc.PWM | PinFunc.SPI;
			this.pinFlags[11] = PinFunc.Digital | PinFunc.PWM | PinFunc.SPI;
			this.pinFlags[12] = PinFunc.Digital | PinFunc.SPI;
			this.pinFlags[13] = PinFunc.Digital | PinFunc.Led | PinFunc.SPI;
			this.pinFlags[14] = PinFunc.Digital | PinFunc.AnalogRead;	//A0
			this.pinFlags[15] = PinFunc.Digital | PinFunc.AnalogRead;	//A1
			this.pinFlags[16] = PinFunc.Digital | PinFunc.AnalogRead;	//A2
			this.pinFlags[17] = PinFunc.Digital | PinFunc.AnalogRead;	//A3
			this.pinFlags[18] = PinFunc.Digital | PinFunc.AnalogRead | PinFunc.I2C;	//A4
			this.pinFlags[19] = PinFunc.Digital | PinFunc.AnalogRead | PinFunc.I2C;	//A5
			this.pinFlags[20] = PinFunc.AnalogRead;	//A6
			this.pinFlags[21] = PinFunc.AnalogRead; //A7

			this.TimerNumberMax = 3;
			this.Timers = new List<Timer>(this.TimerNumberMax);
			this.Timers.Add(new Timer());
			this.Timers.Add(new Timer());
			this.Timers.Add(new Timer());

			this.Timers[0].Caps = TimerCaps._8bits;
			this.Timers[1].Caps = TimerCaps._16bits;
			this.Timers[2].Caps = TimerCaps._8bits;
		}
	}
}
