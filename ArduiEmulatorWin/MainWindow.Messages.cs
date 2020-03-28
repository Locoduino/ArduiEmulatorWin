using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ArduiEmulatorWin
{
	public partial class ArduinoWindow
	{
		// A message is a text received from NamedPipes
		// The syntax is :
		//
		// EXP id pinnb type "name" : new expander
		//												where id is the unic expander id.
		//												where pinb is total number of pins forthis expander.
		//												where type is the default input/output mode.
		//												and 'name' is the ... name !
		// PM pinnb expid type		: pinMode 
		//												where pinnb is a pin number, 
		//												where expid is an expander id, 0 for Arduino pin.
		//												and type a 'O' for output, 'I' for input, 'IP' for input_pullup
		// PS pinnb expid value		: Move pin value
		//												where pinnb is a pin number, 
		//												where expid is an expander id, 0 for Arduino pin.
		//												and value the new value of the pin : digital 0 for LOW and 1 for HIGH, and the value [0-4095] in analog.
		// PN pinnb expid "name"	: Change pin name
		//												where pinnb is a pin number, 
		//												where expid is an expander id, 0 for Arduino pin.
		//												and name the new name of the pin.
		// SC "string"									Serial print
		//												where "string" has to be printed to the serial console without the '"' ...
		// DB "string"									Debug print
		//												where "string" has to be printed to the debug console without the '"' ...
		// 
		// RS "arduino"									Reset the emulator to empty default, to start a new emulation. "arduino" argument is an optional information to set the current arduino model.
		// TP 											Internally declare some pins and expander pins to test the emulator...
		// TI id state									Timer 
		//												id of the timer		
		//												state : 'D'eclared, 'R'emoved, 'B'egin, 'E'nd

		public bool ParseMessage(string inMessage)
		{
			if (this.DebugPipeMode)
			{
				string mess = "Pipe Received : " + inMessage;
				this.debug(mess);
			}

			string[] items;
			if (inMessage.Contains('\"'))
			{
				string[] itemsFirst = inMessage.Substring(0, inMessage.IndexOf('\"')).TrimEnd().Split(' ');
				items = new string[itemsFirst.Length + 1];
				for (int i = 0; i < itemsFirst.Length; i++)
					items[i] = itemsFirst[i];
				items[itemsFirst.Length] = inMessage.Substring(inMessage.IndexOf('\"'));
			}
			else
				items = inMessage.Split(' ');

			switch (items[0].ToUpper())
			{
				case "RS":  // initial connect
					ClearSerialLog();
					ClearDebug();
					Arduino.pinsSetup();
					if (items.Length > 1)
					{
						string mess = inMessage.Remove(0, 3);
						if (mess[0] == '\"' && mess.EndsWith("\""))
						{
							foreach (ComboBoxItem model in this.ArduinoModelCombo.Items)
							{
								if (model.model.RSName == mess.Substring(1, mess.Length - 2))
								{
									this.ArduinoModelCombo.SelectedItem = model;
									break;
								}
							}
							return true;
						}
					}
					return true;

				case "EXP":
					if (items.Length == 5)
					{
						int expid = int.Parse(items[1]);
						int pinNb = int.Parse(items[2]);
						int type = int.Parse(items[3]);

						if (items[4][0] == '\"' && items[4].EndsWith("\""))
						{
							var exp1 = new Expander();
							exp1.ID = expid;
							exp1.Name = items[4].Substring(1, items[4].Length - 2);
							exp1.NbPin = pinNb;
							exp1.Type = type;
							ArduinoItem.Expanders.Add(exp1);
							return true;
						}
					}
					break;

				case "PM":  // pin mode
					if (items.Length == 4)
					{
						int pinnb = int.Parse(items[1]);
						int expid = int.Parse(items[2]);

						int value = Arduino.UNDEFINEDSTATE;

						switch (items[3].ToUpper())
						{
							case "I":
							case "INPUT":
								value = Arduino.INPUT;
								break;

							case "IP":
							case "PULLUP":
							case "INPUT_PULLUP":
								value = Arduino.INPUT_PULLUP;
								break;

							case "O":
							case "OUTPUT":
								value = Arduino.OUTPUT;
								break;

							default:
								value = int.Parse(items[3]);
								break;
						}

						return Arduino.pinMode(pinnb, expid, value);
					}
					break;

				case "PN":  // pin name
					if (items.Length == 4)
					{
						int pinnb = int.Parse(items[1]);
						int expid = int.Parse(items[2]);

						if (items[3][0] == '\"' && items[3].EndsWith("\""))
						{
							return Arduino.PinName(pinnb, expid, items[3].Substring(1, items[3].Length - 2));
						}
					}
					break;

				case "PS":	// pin state
					if (items.Length == 4)
					{
						int pinnb = int.Parse(items[1]);
						int expid = int.Parse(items[2]);

						int value = Arduino.UNDEFINEDSTATE;

						switch (items[3].ToUpper())
						{
							case "H":
							case "HIGH":
								value = Arduino.VS_HIGH;
								break;

							case "L":
							case "LOW":
								value = Arduino.VS_LOW;
								break;

							default:
								value = int.Parse(items[3]);
								break;
						}

						return Arduino.pinState(pinnb, expid, value);
					}
					break;

				case "SC":	//	serial print
					if (items.Length > 1)
					{
						string mess = items[1];
						if (mess[0] == '\"' && mess.EndsWith("\""))
						{
							this.serial_log(mess.Substring(1, mess.Length - 2));
							return true;
						}
					}
					break;

				case "DB":  // debug print
					if (items.Length > 1)
					{
						string mess = items[1];
						if (mess[0] == '\"' && mess.EndsWith("\""))
						{
							this.serial_log(mess.Substring(1, mess.Length - 2));
							return true;
						}
					}
					break;

				case "TP": // test pins

					ClearSerialLog();
					ClearDebug();
					Arduino.pinsSetup();

					var exp = new Expander();
					exp.ID = 100;
					exp.Name = "74HC595-1";
					exp.NbPin = 8;
					exp.Type = Arduino.OUTPUT;
					ArduinoItem.Expanders.Add(exp);

					exp = new Expander();
					exp.ID = 101;
					exp.Name = "74HC595-2";
					exp.NbPin = 8;
					exp.Type = Arduino.OUTPUT;
					ArduinoItem.Expanders.Add(exp);

					Arduino.pinMode(3, 0, Arduino.INPUT);
					Arduino.pinMode(4, 0, Arduino.INPUT_PULLUP);
					Arduino.pinMode(5, 0, Arduino.OUTPUT);
					Arduino.pinMode(6, 0, Arduino.OUTPUT_INTERRUPT);
					Arduino.pinMode(7, 0, Arduino.OUTPUT_RESERVED);

					Arduino.pinMode(1, 100, Arduino.OUTPUT);
					Arduino.pinMode(5, 101, Arduino.OUTPUT);

					Arduino.pinState(10, 0, 120);
					Arduino.pinState(5, 101, Arduino.VS_HIGH);

					Arduino.PinName(10, 0, "Analog 10");

					return true;

				case "LCD":
					return Lcd.ParseMessage(items);

				case "TI":
					if (items.Length == 2)
					{
						int id = int.Parse(items[1]);
						Arduino.timerState(id, Arduino.TIMER_STOPPED);
					}
					if (items.Length > 2)
					{
						int id = int.Parse(items[1]);
						char state = items[2][1];

						if (id >= 0 && id < Arduino.arduinoModel.TimerNumberMax)
						{
							switch (state)
							{
								case 'D':
									Arduino.arduinoModel.Timers[id].declared = true;
									Arduino.timerState(id, Arduino.TIMER_STOPPED);
									break;
								case 'R':
									Arduino.arduinoModel.Timers[id].declared = false;
									Arduino.timerState(id, Arduino.TIMER_STOPPED);
									break;
								case 'B':
									Arduino.arduinoModel.Timers[id].enabled = true;
									Arduino.timerState(id, Arduino.TIMER_STARTED);
									break;
								case 'E':
									Arduino.arduinoModel.Timers[id].enabled = false;
									Arduino.timerState(id, Arduino.TIMER_STOPPED);
									break;
							}
							return true;
						}
					}
					break;
			}

			return false;
		}
	}
}
