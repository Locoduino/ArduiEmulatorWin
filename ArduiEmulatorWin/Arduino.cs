using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace ArduiEmulatorWin
{
	public partial class Arduino
	{
		public const int HIGH = 1;
		public const int LOW = 0;

		public const int VS_LOW = -10;
		public const int VS_HIGH = -20;

		public const int UNDEFINEDSTATE = -1;
		public const int INPUT = 1;
		public const int INPUT_PULLUP = 3;
		public const int OUTPUT = 2;
		public const int OUTPUT_RESERVED = -4;
		public const int OUTPUT_INTERRUPT = -5;

		public const int TIMER_STARTED = 1;
		public const int TIMER_STOPPED = 0;

		public static bool dontCheckNextPinAccess;
		public static ArduinoModel arduinoModel = null;

		public static List<ArduinoModel> ArduinoModels;

		public static void ArduinoModelInit()
		{
			ArduinoModels = new List<ArduinoModel>(10);

			Type[] types = Assembly.GetExecutingAssembly().GetTypes();
			Type[] possible = (from Type type in types where type.IsSubclassOf(typeof(ArduinoModel)) select type).ToArray();

			Type[] ctypes = new Type[0];

			foreach (Type typ in possible)
			{
				ConstructorInfo c = typ.GetConstructor(ctypes);

				if (c != null)
				{
					var model = c.Invoke(null);
					ArduinoModels.Add((ArduinoModel)model);
				}
			}
		}

		public static void pinsSetup()
		{
			ArduinoWindow.MainForm.mModifWindowVM.Clear_Content();
			dontCheckNextPinAccess = false;
		}

		private static bool CheckPin(int inPin, int inExpID)
		{
			if (inPin < 0)
			{
				ArduinoWindow.MainForm.Error("invalid pin number :" + inPin.ToString());
				return false;
			}
			if (inExpID == 0 && inPin >= arduinoModel.PinNumberMax)
			{
				ArduinoWindow.MainForm.Error("invalid Arduino pin number :" + inPin.ToString());
				return false;
			}

			if (inExpID > 0)
			{
				Expander exp = ArduinoWindow.MainForm.mModifWindowVM.GetExpander(inExpID);

				if (exp == null)
				{
					ArduinoWindow.MainForm.Error("invalid expander id :" + inExpID.ToString());
					return false;
				}

				if (inPin >= exp.NbPin)
				{
					ArduinoWindow.MainForm.Error("invalid pin number :" + inPin.ToString() + "for expander " + exp.Name);
					return false;
				}
			}

			return true;
		}

		public static bool PinName(int inPin, int inExpID, String inName)
		{
			if (CheckPin(inPin, inExpID) == false)
				return false;

			bool res = ArduinoWindow.MainForm.mModifWindowVM.SetName(inPin, inExpID, inName);

			return res;
		}

		public static bool pinMode(int inPin, int inExpID, int inType)
		{
			if (CheckPin(inPin, inExpID) == false)
				return false;

			if (!dontCheckNextPinAccess)
			{
				if (ArduinoWindow.MainForm.mModifWindowVM.GetState(inPin, inExpID) != UNDEFINEDSTATE)
				{
					ArduinoWindow.MainForm.Error("pin " + inPin.ToString() + " is already declared !");
				}
			}
			dontCheckNextPinAccess = false;
			int state = UNDEFINEDSTATE;
			switch (inType)
			{
				case INPUT:
					state = VS_LOW;
					break;
				case INPUT_PULLUP:
					state = VS_HIGH;
					break;
				case OUTPUT:
					state = VS_LOW;
					break;
				case OUTPUT_RESERVED:
					state = OUTPUT_RESERVED;
					break;
				case OUTPUT_INTERRUPT:
					state = OUTPUT_INTERRUPT;
					break;
			}
			return ArduinoWindow.MainForm.mModifWindowVM.SetState(inPin, inExpID, state);
		}

		public static bool pinState(int inPin, int inExpID, int inState)
		{
			if (CheckPin(inPin, inExpID) == false)
				return false;

			ArduinoItem pin = ArduinoWindow.MainForm.mModifWindowVM.GetPin(inPin, inExpID);

			if (pin == null)
			{
				if (inState < 0)
				{
					ArduinoWindow.MainForm.Error("pin " + inPin.ToString() + " is not declared !");
					return false;
				}
			}
			else
				if (inState > 0 && inState <= Arduino.arduinoModel.AnalogMax && pin.State < 0)
					ArduinoWindow.MainForm.Error("pin " + inPin.ToString() + " is already in analog mode !");

			if (inState == VS_LOW || inState == VS_HIGH)
			{
				if (pin.State == UNDEFINEDSTATE)
					ArduinoWindow.MainForm.Error("pin " + inPin.ToString() + " is not declared OUTPUT !");

				if (pin.State == OUTPUT_RESERVED)
					ArduinoWindow.MainForm.Error("pin " + inPin.ToString() + " is already reserved !");

				if (pin.State == OUTPUT_INTERRUPT)
					ArduinoWindow.MainForm.Error("pin " + inPin.ToString() + " is already used by interruption !");
			}

			return ArduinoWindow.MainForm.mModifWindowVM.SetState(inPin, inExpID, inState);
		}

		public static bool timerState(int inId, int inState)
		{
			return ArduinoWindow.MainForm.mModifWindowVM.SetTimerState(inId, inState);
		}
	}
}
