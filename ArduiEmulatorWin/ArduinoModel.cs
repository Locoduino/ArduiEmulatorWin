using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduiEmulatorWin
{
	public class ArduinoModel
	{
		public string Name;
		public int PinNumberMax;
		public int AnalogMax;
		public PinFunc[] pinFlags;

		public ArduinoModel()
		{
			this.pinFlags = null;
		}

		[Flags]
		public enum PinFunc
		{
			Led = 1<<0,
			Digital = 1<<1,
			AnalogRead = 1<<2,
			PWM = 1<<3,
			Interrupt = 1<<4,
			SPI = 1<<5,
			I2C = 1<<6,
			CAN = 1<<7,
			Serial = 1<<8
		}
	}
}
