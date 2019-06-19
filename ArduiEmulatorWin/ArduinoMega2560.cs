using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduiEmulatorWin
{
	public class ArduinoMega2560 : ArduinoModel
	{
		public ArduinoMega2560()
		{
			this.Name = "Mega 2560";
			this.RSName = "MEGA2560";
			this.PinNumberMax = 70;
			this.AnalogMax = 1023;

			this.pinFlags = new PinFunc[this.PinNumberMax];

			this.pinFlags[0] = PinFunc.Digital | PinFunc.Serial;
			this.pinFlags[1] = PinFunc.Digital | PinFunc.Serial;
			this.pinFlags[2] = PinFunc.Digital | PinFunc.Interrupt | PinFunc.PWM;
			this.pinFlags[3] = PinFunc.Digital | PinFunc.Interrupt | PinFunc.PWM;
			this.pinFlags[4] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[5] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[6] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[7] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[8] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[9] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[10] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[11] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[12] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[13] = PinFunc.Digital | PinFunc.PWM | PinFunc.Led;
			this.pinFlags[14] = PinFunc.Digital | PinFunc.Serial;
			this.pinFlags[15] = PinFunc.Digital | PinFunc.Serial;
			this.pinFlags[16] = PinFunc.Digital | PinFunc.Serial;
			this.pinFlags[17] = PinFunc.Digital | PinFunc.Serial;
			this.pinFlags[18] = PinFunc.Digital | PinFunc.Serial | PinFunc.Interrupt;
			this.pinFlags[19] = PinFunc.Digital | PinFunc.Serial | PinFunc.Interrupt;
			this.pinFlags[20] = PinFunc.Digital | PinFunc.I2C | PinFunc.Interrupt;
			this.pinFlags[21] = PinFunc.Digital | PinFunc.I2C | PinFunc.Interrupt;
			this.pinFlags[22] = PinFunc.Digital;
			this.pinFlags[23] = PinFunc.Digital;
			this.pinFlags[24] = PinFunc.Digital;
			this.pinFlags[25] = PinFunc.Digital;
			this.pinFlags[26] = PinFunc.Digital;
			this.pinFlags[27] = PinFunc.Digital;
			this.pinFlags[28] = PinFunc.Digital;
			this.pinFlags[29] = PinFunc.Digital;
			this.pinFlags[30] = PinFunc.Digital;
			this.pinFlags[31] = PinFunc.Digital;
			this.pinFlags[32] = PinFunc.Digital;
			this.pinFlags[33] = PinFunc.Digital;
			this.pinFlags[34] = PinFunc.Digital;
			this.pinFlags[35] = PinFunc.Digital;
			this.pinFlags[36] = PinFunc.Digital;
			this.pinFlags[37] = PinFunc.Digital;
			this.pinFlags[38] = PinFunc.Digital;
			this.pinFlags[39] = PinFunc.Digital;
			this.pinFlags[40] = PinFunc.Digital;
			this.pinFlags[41] = PinFunc.Digital;
			this.pinFlags[42] = PinFunc.Digital;
			this.pinFlags[43] = PinFunc.Digital;
			this.pinFlags[44] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[45] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[46] = PinFunc.Digital | PinFunc.PWM;
			this.pinFlags[47] = PinFunc.Digital;
			this.pinFlags[48] = PinFunc.Digital;
			this.pinFlags[49] = PinFunc.Digital;
			this.pinFlags[50] = PinFunc.Digital | PinFunc.SPI;
			this.pinFlags[51] = PinFunc.Digital | PinFunc.SPI;
			this.pinFlags[52] = PinFunc.Digital | PinFunc.PWM | PinFunc.SPI;
			this.pinFlags[53] = PinFunc.Digital | PinFunc.SPI;
			this.pinFlags[54] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[55] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[56] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[57] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[58] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[59] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[60] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[61] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[62] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[63] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[64] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[65] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[66] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[67] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[68] = PinFunc.Digital | PinFunc.AnalogRead;
			this.pinFlags[69] = PinFunc.Digital | PinFunc.AnalogRead;
		}
	}
}
