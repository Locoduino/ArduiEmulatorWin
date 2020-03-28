using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduiEmulatorWin
{
	[Flags]
	public enum TimerCaps
	{
		_8bits = 1 << 0,
		_16bits = 1 << 1,
		_32bits = 1 << 2,
	}

	public class Timer
	{
		public TimerCaps Caps;
		public bool declared;
		public bool enabled; // started...
	}

	public class ArduinoModel
	{
		public string Name;
		public string RSName;	// Name used by 'RS' message...
		public int PinNumberMax;
		public int AnalogMax;
		public PinFunc[] pinFlags;

		public int TimerNumberMax;
		public List<Timer> Timers;

		public ArduinoModel()
		{
			this.PinNumberMax = 0;
			this.pinFlags = null;

			this.TimerNumberMax = 0;
			this.Timers = null;
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
