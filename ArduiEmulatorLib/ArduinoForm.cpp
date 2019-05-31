#include "ArduinoForm.hpp"
#include "ArduiEmulator.hpp"

namespace ArduiEmulator
{
	void ArduinoForm::_lcdClear(void)
	{
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
			return;

		if (_lcdRows == 0)
			return;

		Graphics^ graf = mainForm->CreateGraphics();
		String^ maxStr = gcnew String('W', _lcdCols);
		SizeF size = graf->MeasureString(maxStr, mainForm->LcdLine1->Font);

		for (int i = 0; i < mainForm->lcdLines->Length; i++)
		{
			mainForm->lcdLines[i]->Text = mainForm->LcdLine1->Text->Empty;

			if (i >= _lcdRows)
				mainForm->lcdLines[i]->Visible = false;
			else
				mainForm->lcdLines[i]->Width = (int)size.Width;

			mainForm->lcdLines[i]->Refresh();
		}
	}

	void ArduinoForm::_lcdPrint(uint8_t inRow, uint8_t inCol, String^ inString)
	{
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
			return;

		if (inCol + inString->Length > _lcdCols && !mainForm->Autoscroll)
		{
			_Error("print out of the screen !");
			return;
		}

		if (inRow >= _lcdRows)
		{
			_Error("print out of the screen !");
			return;
		}

		if (inCol >= _lcdCols && !mainForm->Autoscroll)
			return;

		String^ control = mainForm->lcdLines[inRow]->Text;

		control = control->PadRight(100, ' ');

		String^ newString = String::Concat(control->Substring(0, inCol), inString, control->Substring(inCol + inString->Length));

		if (inCol >= _lcdCols && mainForm->Autoscroll)
		{
			newString = newString->Substring(0, inCol + inString->Length);
			mainForm->lcdLines[inRow]->Text = newString;
			_lcdScrollToLeft(inString->Length);
		}
		else
		{
			newString = newString->Substring(0, _lcdCols);
			mainForm->lcdLines[inRow]->Text = newString;
			mainForm->lcdLines[inRow]->Refresh();
		}
	}

	void ArduinoForm::_lcdScrollToLeft(uint8_t nbCols)
	{
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
			return;

		for each (System::Windows::Forms::Label^ line in mainForm->lcdLines)
		{
			line->Text = line->Text->PadRight(_lcdCols * 2, ' ');
			line->Text = line->Text->Substring(nbCols, _lcdCols);
			line->Refresh();
		}
	}

	void ArduinoForm::_lcdScrollToRight(uint8_t nbCols)
	{
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
			return;

		for each (System::Windows::Forms::Label^ line in mainForm->lcdLines)
		{
			line->Text = line->Text->PadRight(_lcdCols * 2, ' ');
			line->Text = line->Text->Substring(nbCols, _lcdCols);
			line->Refresh();
		}
	}

	void ArduinoForm::_lcdNoDisplay()
	{
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
			return;

		if (mainForm->displayMemo == nullptr)
			mainForm->displayMemo = gcnew array<String^>(_lcdRows);

		for (int i = 0; i < _lcdRows; i++)
		{
			mainForm->displayMemo[i] = mainForm->lcdLines[i]->Text;
			mainForm->lcdLines[i]->Text = mainForm->LcdLine1->Text->Empty;
			mainForm->lcdLines[i]->Refresh();
		}
	}

	void ArduinoForm::_lcdnoDisplay()
	{
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
			return;

		mainForm->Display = false;
		if (mainForm->displayMemo == nullptr)
			mainForm->displayMemo = gcnew array<String^>(_lcdRows);

		for (int i = 0; i < _lcdRows; i++)
		{
			mainForm->displayMemo[i] = mainForm->lcdLines[i]->Text;
			mainForm->lcdLines[i]->Text = mainForm->LcdLine1->Text->Empty;
			mainForm->lcdLines[i]->Refresh();
		}
	}

	void ArduinoForm::_lcddisplay()
	{
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
			return;

		mainForm->Display = true;
		if (mainForm->displayMemo == nullptr)
			return;

		for (int i = 0; i < _lcdRows; i++)
		{
			mainForm->lcdLines[i]->Text = mainForm->displayMemo[i];
			mainForm->lcdLines[i]->Refresh();
		}
	}

	void ArduinoForm::_lcdscrollDisplayLeft()
	{
		// The HD44780 have a 80 bytes DDRAM area, for the text, and a shift register.
		//        8 cols / 2 lines screen (values are decimal...)
		// +---------------------------------------+
		// + 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | ... | 39 |
		// +---------------------------------------+
		// + 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | 48 | ... | 79 |
		// +---------------------------------------+
		//
		//        shifted right :
		// +---------------------------------------+
		// + 39 | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | ... | 38 |
		// +---------------------------------------+
		// + 79 | 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 | ... | 78 |
		// +---------------------------------------+
		//
		//mainForm->ScrollToLeft = true; 
	}

	void ArduinoForm::_lcdscrollDisplayRight()
	{
		//mainForm->ScrollToLeft = false; 
	}

	void ArduinoForm::_lcdnoBlink() { mainForm->Blink = false; }
	void ArduinoForm::_lcdblink() { mainForm->Blink = true; }
	void ArduinoForm::_lcdnoCursor() { mainForm->Cursor = false; }
	void ArduinoForm::_lcdcursor() { mainForm->Cursor = true; }
	void ArduinoForm::_lcdleftToRight() { mainForm->LeftToRight = true; }
	void ArduinoForm::_lcdrightToLeft() { mainForm->LeftToRight = false; }
	void ArduinoForm::_lcdautoscroll() { mainForm->Autoscroll = true; }
	void ArduinoForm::_lcdnoAutoscroll() { mainForm->Autoscroll = false; }
	// End LCD part

	void ArduinoForm::_clear(void)
	{
		if (mainForm == nullptr)
			return;

		for (int i = 0; i < mainForm->lcdLines->Length; i++)
		{
			mainForm->lcdLines[i]->Text = mainForm->LcdLine1->Text->Empty;
			mainForm->lcdLines[i]->Refresh();
		}

		mainForm->PinList->Items->Clear();

		mainForm->SerialConsole->Text = mainForm->SerialConsole->Text->Empty;
		mainForm->textBoxEventLog->Text = mainForm->SerialConsole->Text->Empty;
		mainForm->Display = false;
		mainForm->Blink = false;
		mainForm->Cursor = false;
		mainForm->LeftToRight = true;
		mainForm->Autoscroll = false;
	}

	void ArduinoForm::_debug(String^ inString)
	{
		String^ str = gcnew String(inString);
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
		{
			if (preStartDebugs == nullptr)
			{
				preStartDebugs = gcnew array<String^>(100);
				preStartDebugsCount = 0;
			}

			if (preStartDebugsCount < 100)
				preStartDebugs[preStartDebugsCount++] = inString;
			return;
		}

		if (mainForm->SerialConsole->Text->Length > 0)
			str = str->Format("{0}\r\n{1}", mainForm->SerialConsole->Text, inString->ToString());
		if (str->Length > 65536)
			str = str->Remove(0, 1000);
		mainForm->SerialConsole->Text = str->ToString();
		mainForm->SerialConsole->Select(mainForm->SerialConsole->Text->Length, 0);
		mainForm->SerialConsole->ScrollToCaret();
	}

	void ArduinoForm::_Error(String^ inString)
	{
		_debug("*** ARDUINO ERROR : " + inString);
	}

	// Beware of the COMMANDERS_EVENT_TYPE and MOVE_TYPE modifications !

	enum PRINT_MOVE_TYPE
	{
		PRINT_MOVE_MORE = +1,
		PRINT_MOVE_LESS = -1,
		PRINT_MOVE_STOP = 0,
		PRINT_MOVE_LEFT = -2,
		PRINT_MOVE_RIGHT = -3,
		PRINT_MOVE_CENTER = -4,
		PRINT_MOVE_TOP = -5,
		PRINT_MOVE_BOTTOM = -6,
		PRINT_MOVE_STRAIGHT = -7,
		PRINT_MOVE_DIVERGE = -8,
		PRINT_MOVE_ON = -9,
		PRINT_MOVE_OFF = -10,
		PRINT_MOVE_LEAVE = -11
	};

	enum PRINT_EVENT_TYPE
	{
		PRINT_EVENT_NONE = 0,			// Should never appear
		PRINT_EVENT_TOGGLE = 1,		// If a push button or similar is pressed, invert the state/position
		PRINT_EVENT_MOVE = 2,			// If a push 'left' button or similar is pressed, data is a COMMANDERS_MOVE_TYPE
		PRINT_EVENT_MOVEPOSITION = 3,	// If a potentiometer or similar is moved, data is the position to reach
		PRINT_EVENT_MOVEPOSITIONINDEX = 4,// Move to an indexed position from pMovingPosition given by data.
		PRINT_EVENT_MOVEPOSITIONID = 5,	// Move to an identified position from pMovingPosition, given by the event id.
		PRINT_EVENT_CONFIG = 6			// Data is the configuration address and value
	};

#ifndef PRINTUNDEFINED_ID
#define PRINTUNDEFINED_ID	((unsigned long)-1)
#endif

#define PRINTCONFIGADDRESS(data)		highByte((int)data)
#define PRINTCONFIGVALUE(data)			lowByte((int)data)

	static String^ _buildFormEventString(String^ inPrefix, unsigned long inId, int inEventType, int inEventData)
	{
		String^ strId = gcnew String("");
		String^ strEvent = gcnew String("");
		String^ strData = gcnew String("");

		if (inId == PRINTUNDEFINED_ID)
			strId = "UNDEFID";
		else
			strId = inId.ToString();

		switch (inEventType)
		{
		case PRINT_EVENT_NONE:			strEvent = "NONE";		break;
		case PRINT_EVENT_TOGGLE:		strEvent = "TOGGLE";	break;
		case PRINT_EVENT_MOVE:
			strEvent = "MOVE ";
			switch ((PRINT_MOVE_TYPE)inEventData)
			{
			case PRINT_MOVE_MORE:		strData = "MORE";		break;
			case PRINT_MOVE_LESS:		strData = "LESS";		break;
			case PRINT_MOVE_STOP:		strData = "STOP";		break;
			case PRINT_MOVE_LEFT:		strData = "LEFT";		break;
			case PRINT_MOVE_RIGHT:		strData = "RIGHT";		break;
			case PRINT_MOVE_CENTER:	strData = "CENTER";		break;
			case PRINT_MOVE_TOP:		strData = "TOP";		break;
			case PRINT_MOVE_BOTTOM:	strData = "BOTTOM";		break;
			case PRINT_MOVE_STRAIGHT:	strData = "STRAIGHT";	break;
			case PRINT_MOVE_DIVERGE:	strData = "DIVERGE";	break;
			case PRINT_MOVE_ON:		strData = "ON";			break;
			case PRINT_MOVE_OFF:		strData = "OFF";		break;
			case PRINT_MOVE_LEAVE:		strData = "LEAVE";		break;
			}
			break;
		case PRINT_EVENT_MOVEPOSITION:
			strEvent = "MOVEPOSITION";
			strData = inEventData.ToString();
			break;
		case PRINT_EVENT_MOVEPOSITIONID:
			strEvent = "MOVEPOSITIONID";
			break;
		case PRINT_EVENT_MOVEPOSITIONINDEX:
			strEvent = "MOVEPOSITIONINDEX";
			strData = inEventData.ToString();
			break;
		case PRINT_EVENT_CONFIG:
			strEvent = "CONFIG";
			strData = PRINTCONFIGADDRESS(inEventData).ToString() + " / " + PRINTCONFIGVALUE(inEventData).ToString();
			break;
		}

		return String::Format("{0, -15} : {1,-7} {2,-10} {3}", inPrefix, strId, strEvent, strData);
	}

	void ArduinoForm::_eventLog(String^ inPrefix, unsigned long inId, int inEventType, int inData)
	{
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
		{
			return;
		}

		String^ str = _buildFormEventString(inPrefix, inId, inEventType, inData);

		if (mainForm->textBoxEventLog->Text->Length > 0)
			str = str->Format("{0}\r\n{1}", mainForm->textBoxEventLog->Text, str);
		if (str->Length > 4096)
			str = str->Remove(0, 100);
		mainForm->textBoxEventLog->Text = str->ToString();
		mainForm->textBoxEventLog->Select(mainForm->textBoxEventLog->Text->Length, 0);
		mainForm->textBoxEventLog->ScrollToCaret();
	}

	void ArduinoForm::_ShowPins(array<int>^ inpPins, array<String^>^ inpPinNames)
	{
		if (mainForm == nullptr || mainForm->PinList->Items == nullptr)
			return;

		int count = 0;
		for (int i = 1; i < inpPins->Length; i++)
		{
			if (inpPins[i] != -1)
				count++;
		}

		if (mainForm->PinList->Items->Count == 0 || count != mainForm->PinList->Items->Count)
		{
			mainForm->PinList->Items->Clear();

			// Fill the list
			for (int i = 1; i < inpPins->Length; i++)
			{
				if (inpPins[i] != -1)
				{
					mainForm->PinList->Items->Add(gcnew PinListItem(i, inpPins[i], inpPinNames[i]));
				}
			}
		}
																												  
		for (int i = 0; i < mainForm->PinList->Items->Count; i++)
		{
			PinListItem^ pinNode = (PinListItem^)(mainForm->PinList->Items[i]);
			if (pinNode->state != inpPins[pinNode->pin])
				mainForm->PinList->Items[i] = gcnew PinListItem(pinNode->pin, inpPins[pinNode->pin], inpPinNames[pinNode->pin]);
		}

		mainForm->PinList->Refresh();
	}

	void ArduinoForm::_pinName(int inPin, String^ inName)
	{
		for (int i = 0; i < mainForm->PinList->Items->Count; i++)
		{
			PinListItem^ pinNode = (PinListItem^)(mainForm->PinList->Items[i]);
			if (pinNode->pin == inPin)
				pinNode->name = inName;
		}
	}

	System::Void ArduinoForm::button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		/*
		Syntax for pin activation / inactivation :

		pin [,pin]:[LOW|HIGH|value]

		if nothing is specified as value, just toggle the digital output.
		No effect on PWM.

		value can be used for analog pins and is between 0 and 255.

		*/

		int value = -1000;		// toggle

		int end = this->textSerialInput->Text->IndexOf(':');

		if (end != -1)
		{
			String ^endOfString = this->textSerialInput->Text->Substring(end + 1);

			if (endOfString->ToUpper() == "HIGH")
				value = HIGH;
			else
				if (endOfString->ToUpper() == "LOW")
					value = LOW;
				else
					if (!System::Int32::TryParse(endOfString, value))
						value = HIGH;

			this->textSerialInput->Text = this->textSerialInput->Text->Substring(0, end);
		}			  

		array<String ^> ^pins = this->textSerialInput->Text->Split(',');

		for each (String ^str in pins)
		{
			int pin = -1;
			if (!System::Int32::TryParse(str, pin))
				pin = -1;
			if (pin != -1)
			{
				if (value == -1000)
				{ // Toggle
					if (ArduiEmulator::Arduino::VC_pins[pin] == VS_LOW)
						value = HIGH;
					if (ArduiEmulator::Arduino::VC_pins[pin] == VS_HIGH)
						value = LOW;
				}
				if (ArduiEmulator::Arduino::VC_pins[pin] >= 0)
					ArduiEmulator::Arduino::_analogWrite(pin, value);
				else
					ArduiEmulator::Arduino::_digitalWrite(pin, value);
			}
		}
	}

	void ArduiEmulator::ArduinoForm::OnDoubleClick(System::Object ^sender, System::EventArgs ^e)
	{
		if (mainForm->PinList->Items[mainForm->PinList->SelectedIndex] == nullptr)
			return;
		int pin = ((PinListItem ^)(mainForm->PinList->Items[mainForm->PinList->SelectedIndex]))->pin;
		int value = -10000;
		if (ArduiEmulator::Arduino::VC_pins[pin] == VS_LOW)
			value = HIGH;
		if (ArduiEmulator::Arduino::VC_pins[pin] == VS_HIGH)
			value = LOW;

		if (value > -10000)
			ArduiEmulator::Arduino::_digitalWrite(pin, value);
	}

	System::Void ArduinoForm::toggleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (mainForm->PinList->Items[mainForm->PinList->SelectedIndex] == nullptr)
			return;
		int pin = ((PinListItem ^)(mainForm->PinList->Items[mainForm->PinList->SelectedIndex]))->pin;
		int value = -10000;
		if (ArduiEmulator::Arduino::VC_pins[pin] == VS_LOW)
			value = HIGH;
		if (ArduiEmulator::Arduino::VC_pins[pin] == VS_HIGH)
			value = LOW;

		if (value > -10000)
			ArduiEmulator::Arduino::_digitalWrite(pin, value);
	}
}