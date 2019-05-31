using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows;

namespace ArduiEmulatorWin
{
	public class Lcd
	{
		const int MaxNbRows = 5;

		public int rowsNb, colsNb;
		public int rowPos, colPos;
		private bool Display, Blink, Cursor, Autoscroll, LeftToRight;
		private string[] displayMemo = new string[MaxNbRows];
		public string[] lines = new string[MaxNbRows];

		public void init(int nbRows, int nbCols)
		{
			this.rowsNb = nbRows;
			this.colsNb = nbCols;

			this.rowPos = 0;
			this.colPos = 0;

			this.clear();
		}

		public void clear()
		{
			if (this.rowsNb == 0)
				return;

			for (int i = 0; i < MaxNbRows; i++)
			{
				NotifyLcdPropertyChanged(i, string.Empty);
			}

			this.rowPos = 0;
			this.colPos = 0;
		}

		public void home()
		{
			this.rowPos = 0;
			this.colPos = 0;
		}

		int write(char ch)
		{
			var str = new StringBuilder();
			str.Append(ch);
			lcdPrint(this.rowPos, this.colPos, str.ToString());
			return 1;
		}

		public void setCursor(int inRow, int inCol)
		{
			if (inCol >= this.colsNb)
			{
				ArduinoWindow.MainForm.debug("move out of the screen !");
				return;
			}

			if (inRow >= this.rowsNb)
			{
				ArduinoWindow.MainForm.debug("move out of the screen !");
				return;
			}

			this.rowPos = inRow;
			this.colPos = inCol;
		}

		public void lcdPrint(int inRow, int inCol, string inString)
		{
			if (inCol + inString.Length > this.colsNb)
			{
				ArduinoWindow.MainForm.debug("print out of the screen !");
				return;
			}

			if (inRow >= this.rowsNb)
			{
				ArduinoWindow.MainForm.debug("print out of the screen !");
				return;
			}

			String control = this.lines[inRow];

			control = control.PadRight(100, ' ');

			String newString = String.Concat(control.Substring(0, inCol), inString, control.Substring(inCol + inString.Length));

			/*if (inCol >= _lcdCols && mainForm->Autoscroll)
			{
				newString = newString->Substring(0, inCol + inString->Length);
				mainForm->lcdLines[inRow]->Text = newString;
				_lcdScrollToLeft(inString->Length);
			}
			else*/
			{
				newString = newString.Substring(0, this.colsNb);
				NotifyLcdPropertyChanged(inRow, newString);
			}

			this.rowPos = inRow;
			this.colPos = inCol;
		}

		public void lcdScrollToLeft(int nbCols)
		{
			/*
			foreach(System::Windows::Forms::Label ^ line in mainForm->lcdLines)
			{
				line->Text = line->Text->PadRight(_lcdCols * 2, ' ');
				line->Text = line->Text->Substring(nbCols, _lcdCols);
				line->Refresh();
			}	*/
		}

		public void lcdScrollToRight(int nbCols)
		{
			/*
			foreach(System::Windows::Forms::Label ^ line in mainForm->lcdLines)
			{
				line->Text = line->Text->PadRight(_lcdCols * 2, ' ');
				line->Text = line->Text->Substring(nbCols, _lcdCols);
				line->Refresh();
			}	*/
		}

		public void lcdNoDisplay()
		{
			for (int i = 0; i < this.rowsNb; i++)
			{
				displayMemo[i] = lines[i];
				NotifyLcdPropertyChanged(i, string.Empty);
			}

			this.Display = false;
		}

		public void lcdnoDisplay()
		{
			this.lcdNoDisplay();
		}

		public void lcddisplay()
		{
			for (int i = 0; i < this.rowsNb; i++)
			{
				NotifyLcdPropertyChanged(i, displayMemo[i]);
				displayMemo[i] = string.Empty;
			}
			this.Display = true;
		}

		public void lcdscrollDisplayLeft()
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

		public void lcdscrollDisplayRight()
		{

		}

		public void lcdnoBlink()
		{
			if (this.Blink != false)
			{
				this.Blink = false;
				NotifyLcdPropertyChanged(this.rowPos, "##DNU##");
			}
		}

		public void lcdblink()
		{
			if (this.Blink != true)
			{
				this.Blink = true;
				NotifyLcdPropertyChanged(this.rowPos, "##DNU##");
			}
		}

		public void lcdnoCursor()
		{
			if (this.Cursor != false)
			{
				this.Cursor = false;
				NotifyLcdPropertyChanged(this.rowPos, "##DNU##");
			}
		}

		public void lcdcursor()
		{
			if (this.Cursor != true)
			{
				this.Cursor = true;
				NotifyLcdPropertyChanged(this.rowPos, "##DNU##");
			}
		}

		public void lcdleftToRight()
		{
			if (this.LeftToRight != true)
			{
				this.LeftToRight = true;
				NotifyLcdPropertyChanged(this.rowPos, "##DNU##");
			}
		}

		public void lcdrightToLeft()
		{
			if (this.LeftToRight != false)
			{
				this.LeftToRight = false;
				NotifyLcdPropertyChanged(this.rowPos, "##DNU##");
			}
		}

		public void lcdautoscroll()
		{
			if (this.Autoscroll != true)
			{
				this.Autoscroll = true;
				NotifyLcdPropertyChanged(this.rowPos, "##DNU##");
			}
		}

		public void lcdnoAutoscroll()
		{
			if (this.Autoscroll != false)
			{
				this.Autoscroll = false;
				NotifyLcdPropertyChanged(this.rowPos, "##DNU##");
			}
		}

		// A message is a text received from NamedPipes for Lcd print
		// The syntax is :
		// Begin : LCD BG rows cols
		//		where row is a row number
		//		where col is a column number
		// clear : LCD CL
		// home : LCD HOME
		// write : LCD WR 'char'
		//		where char is the character to output at the current cursor position.
		// Print : LCD PR row col "mess"
		//		where row is a row number
		//		where col is a column number
		//		and mess the text to print, surrounded by double quotes. If no text, do a setCursor only.
		// Scroll : LCD SC cols
		//		where cols is the number of columns : positive to move to the right, negative to the left.
		// Display : LCD DISP bool
		//		where bool means display if true, or hide (no display) if false;
		// ScrollDisplay : LCD SCDISP bool
		//		where bool means scroll display to left if true (default), or scroll display to right if false;
		// Blink : LCD BLK bool
		//		where bool means blink if true, or no blink if false;
		// Cursor : LCD CSR bool
		//		where bool means cursor if true, or no cursor if false;
		// LeftToRight : LCD LTOR bool
		//		where bool means Left to Right if true (default), or Right to Left if false;
		// Autoscroll : LCD AUTOSC bool
		//		where bool means autoscroll if true, or no autoscroll if false;
		// 
		public static bool ParseMessage(string[] inItems)
		{
			// inItems[0] is always 'LCD' .
			switch (inItems[1].ToUpper())
			{
				case "BG":
					if (inItems.Length < 4)
						break;
					if (inItems.Length == 4)
					{
						Lcd.screen.init(int.Parse(inItems[2]), int.Parse(inItems[3]));
						return true;
					}
					break;

				case "CL":
					Lcd.screen.clear();
					return true;

				case "HOME":
					Lcd.screen.home();
					return true;

				case "PR":
					if (inItems.Length < 4)
						break;
					if (inItems.Length == 4)
						Lcd.screen.setCursor(int.Parse(inItems[2]), int.Parse(inItems[3]));
					else
						Lcd.screen.lcdPrint(int.Parse(inItems[2]), int.Parse(inItems[3]), inItems[4].Substring(1, inItems[4].Length - 2));
					return true;

				case "SC":
					if (inItems.Length < 3)
						break;
					if (inItems.Length < 3)
						break;
					int cols = int.Parse(inItems[2]);
					if (cols > 0)
						Lcd.screen.lcdScrollToRight(cols);
					else
						Lcd.screen.lcdScrollToLeft(-cols);
					return true;

				case "DISP":
					if (inItems.Length < 3)
						break;
					int val = int.Parse(inItems[2]);
					if (val > 0)
						Lcd.screen.lcddisplay();
					else
						Lcd.screen.lcdNoDisplay();
					return true;

				case "SCDISP":
					if (inItems.Length < 3)
						break;
					int valsd = int.Parse(inItems[2]);
					if (valsd > 0)
						Lcd.screen.lcdscrollDisplayLeft();
					else
						Lcd.screen.lcdscrollDisplayRight();
					return true;		 

				case "BLK":
					if (inItems.Length < 3)
						break;
					int valb = int.Parse(inItems[2]);
					if (valb > 0)
						Lcd.screen.lcdblink();
					else
						Lcd.screen.lcdnoBlink();
					return true;

				case "CSR":
					if (inItems.Length < 3)
						break;
					int valc = int.Parse(inItems[2]);
					if (valc > 0)
						Lcd.screen.lcdcursor();
					else
						Lcd.screen.lcdnoCursor();
					return true;

				case "WR":
					if (inItems.Length < 3)
						break;
					int valchar = int.Parse(inItems[2]);
					Lcd.screen.write((char) valchar);
					return true;

				case "LTOP":
					if (inItems.Length < 3)
						break;
					int vallr = int.Parse(inItems[2]);
					if (vallr > 0)
						Lcd.screen.lcdleftToRight();
					else
						Lcd.screen.lcdrightToLeft();
					return true;

				case "AUTOSC":
					if (inItems.Length < 3)
						break;
					int valas = int.Parse(inItems[2]);
					if (valas > 0)
						Lcd.screen.lcdautoscroll();
					else
						Lcd.screen.lcdnoAutoscroll();
					return true;
			}

			return false;
		}

		public static Lcd screen = new Lcd();

		void NotifyLcdPropertyChanged(int line, string newString)
		{
			ArduinoWindow.MainForm.mModifWindowVM.UpdateLine(line, newString);
			//Application.Current.Run();
			ArduinoWindow.MainForm.InvalidateVisual();
			System.Threading.Thread.Sleep(40);
		}
	}

	public partial class Modif_Window_ViewModel
	{
		public string[] lcdLines
		{
			get { return Lcd.screen.lines; }
			set { Lcd.screen.lines = value; }
		}

		public void UpdateLine(int row, string newString)
		{
			switch (row)
			{
				case 0:	this.lcdLine1 = newString; break;
				case 1: this.lcdLine2 = newString; break;
				case 2: this.lcdLine3 = newString; break;
				case 3: this.lcdLine4 = newString; break;
				case 4: this.lcdLine5 = newString; break;
				default:
					return;
			}
		}

		public string lcdLine1
		{
			get { return Lcd.screen.lines[0]; }
			set
			{
				if (value != "##DNU##")
					Lcd.screen.lines[0] = value;
				NotifyPropertyChangedEvent("LcdLine1");
			}
		}
		public string lcdLine2
		{
			get { return Lcd.screen.lines[1]; }
			set
			{
				if (value != "##DNU##")
					Lcd.screen.lines[1] = value;
				NotifyPropertyChangedEvent("LcdLine2");
			}

		}
		public string lcdLine3
		{
			get { return Lcd.screen.lines[2]; }
			set
			{
				if (value != "##DNU##")
					Lcd.screen.lines[2] = value;
				NotifyPropertyChangedEvent("LcdLine3");
			}

		}
		public string lcdLine4
		{
			get { return Lcd.screen.lines[3]; }
			set
			{
				if (value != "##DNU##")
					Lcd.screen.lines[3] = value;
				NotifyPropertyChangedEvent("LcdLine4");
			}

		}
		public string lcdLine5
		{
			get { return Lcd.screen.lines[4]; }
			set
			{
				if (value != "##DNU##")
					Lcd.screen.lines[4] = value;
				NotifyPropertyChangedEvent("LcdLine5");
			}
		}
	}
}
