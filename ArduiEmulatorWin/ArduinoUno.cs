using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduiEmulatorWin
{
	public class ArduinoUno : ArduinoModel
	{
		public ArduinoUno()
		{
			this.Name = "Uno R3";
			this.RSName = "UNO";
			this.PinNumberMax = 20;
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
		}
	}
}
