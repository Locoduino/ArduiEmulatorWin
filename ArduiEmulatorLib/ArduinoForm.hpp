#pragma once

#include "ArduiEmulator.inc"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#define LCDNBLINES	5

namespace ArduiEmulator
{
	/// <summary>
	/// Summary for ArduinoForm
	/// </summary>
	public ref class ArduinoForm : public System::Windows::Forms::Form
	{
	private: ref class PinListItem
		{
		public:
			int pin;
			int state;
			String^ name;

			PinListItem(int inPin, int inState, String^ inName)
			{
				this->pin = inPin;
				this->state = inState;
				this->name = inName;
			}

			virtual String ^ToString() override
			{
				String^ str = gcnew String("     ");
				String^ textName;

				if (String::IsNullOrEmpty(this->name))
					textName = String::Format("{0,-4}", this->pin.ToString());
				else
					textName = String::Format("{0,-4}", this->name);

				switch (this->state)
				{
				case VS_LOW:
					str = String::Format("{0}  LOW", textName);
					break;
				case VS_HIGH:
					str = String::Format("{0} HIGH", textName);
					break;
				case OUTPUT_RESERVED:
					str = String::Format("{0} ----", textName);
					break;
				case OUTPUT_INTERRUPT:
					str = String::Format("{0} INTR", textName);
					break;
				default:
					str = String::Format("{0} {1,4}", textName, this->state.ToString());
					break;
				}
				return str;
			}
		};

	public:
		bool LoopStarted;
		bool LoopPaused;

		void (*SetupPointer)(void);
		void (*LoopPointer)(void);
		array<System::Windows::Forms::Label^>^ lcdLines;
	
		static ArduinoForm^ mainForm;
		static String^ SerialBuffer;

	private: System::Windows::Forms::TextBox^  textBoxEventLog;
	private: System::Windows::Forms::TextBox^  textSerialInput;
	private: System::Windows::Forms::Button^  buttonSerialSend;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripPin;
	private: System::Windows::Forms::ToolStripMenuItem^  toggleToolStripMenuItem;
	private: System::Windows::Forms::Panel^  panelLCD;

	private: System::Windows::Forms::Panel^  panelSerial;
	private: System::Windows::Forms::Panel^  panelButtons;
	public:
		static wchar_t lastKeyPressed;

	public:
		ArduinoForm(void(*inSetupPointer)(void), void(*inLoopPointer)(void))
		{
			InitializeComponent();

			this->SetupPointer = inSetupPointer;
			this->LoopPointer = inLoopPointer;
			this->LoopStarted = false;
			this->LoopPaused = false;
			mainForm = this;

			this->lcdLines = gcnew array<System::Windows::Forms::Label^>(LCDNBLINES);
			this->lcdLines[0] = mainForm->LcdLine1;
			this->lcdLines[1] = mainForm->LcdLine2;
			this->lcdLines[2] = mainForm->LcdLine3;
			this->lcdLines[3] = mainForm->LcdLine4;
			this->lcdLines[4] = mainForm->LcdLine5;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ArduinoForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public:
		// LCD PART
		static uint8_t _lcdRows, _lcdCols;
		static bool Display, Blink, Cursor, Autoscroll,  LeftToRight;
		static array<String^>^ displayMemo;

		static void _lcdClear(void);
		static void _lcdPrint(uint8_t inRow, uint8_t inCol, String^ inString);
		static void _lcdScrollToLeft(uint8_t nbCols);
		static void _lcdScrollToRight(uint8_t nbCols);
		static void _lcdNoDisplay();
		static void _lcdnoDisplay();
		static void _lcddisplay();
		static void _lcdscrollDisplayLeft();
		static void _lcdscrollDisplayRight();
		static void _lcdnoBlink();
		static void _lcdblink();
		static void _lcdnoCursor();
		static void _lcdcursor();
		static void _lcdleftToRight();
		static void _lcdrightToLeft();
		static void _lcdautoscroll();
		static void _lcdnoAutoscroll();
		// End LCD part

		static void _clear(void);
		static void _debug(String^ inString);
		static void _ShowPins(array<int>^ inpPins, array<String^>^ inpPinNames);
		static void _pinName(int inPin, String^ inName);

		static void _Error(String^ inString);
		static void _eventLog(String^ inPrefix, unsigned long inId, int inEventType, int inData);

	private: System::Windows::Forms::Timer^  timerLoop;

	private: System::Windows::Forms::Label^  LcdLine1;
	private: System::Windows::Forms::Label^  LcdLine2;
	private: System::Windows::Forms::Label^  LcdLine3;
	private: System::Windows::Forms::Label^  LcdLine4;
	private: System::Windows::Forms::Label^  LcdLine5;

	private: System::Windows::Forms::ListBox^  PinList;

	private: System::Windows::Forms::TextBox^  SerialConsole;
	public: System::Windows::Forms::Button^  buttonStart;
	private: System::Windows::Forms::Button^  buttonExit;
	private: System::Windows::Forms::Button^  buttonAbout;
	private: System::Windows::Forms::Button^  buttonPause;
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		static array<String ^>^ preStartDebugs;
		static int preStartDebugsCount = 0;

		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->LcdLine1 = (gcnew System::Windows::Forms::Label());
			this->PinList = (gcnew System::Windows::Forms::ListBox());
			this->contextMenuStripPin = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toggleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LcdLine2 = (gcnew System::Windows::Forms::Label());
			this->LcdLine3 = (gcnew System::Windows::Forms::Label());
			this->LcdLine4 = (gcnew System::Windows::Forms::Label());
			this->LcdLine5 = (gcnew System::Windows::Forms::Label());
			this->SerialConsole = (gcnew System::Windows::Forms::TextBox());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->buttonExit = (gcnew System::Windows::Forms::Button());
			this->buttonAbout = (gcnew System::Windows::Forms::Button());
			this->timerLoop = (gcnew System::Windows::Forms::Timer(this->components));
			this->buttonPause = (gcnew System::Windows::Forms::Button());
			this->textBoxEventLog = (gcnew System::Windows::Forms::TextBox());
			this->textSerialInput = (gcnew System::Windows::Forms::TextBox());
			this->buttonSerialSend = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panelLCD = (gcnew System::Windows::Forms::Panel());
			this->panelSerial = (gcnew System::Windows::Forms::Panel());
			this->panelButtons = (gcnew System::Windows::Forms::Panel());
			this->contextMenuStripPin->SuspendLayout();
			this->panelLCD->SuspendLayout();
			this->panelSerial->SuspendLayout();
			this->panelButtons->SuspendLayout();
			this->SuspendLayout();
			// 
			// LcdLine1
			// 
			this->LcdLine1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LcdLine1->Dock = System::Windows::Forms::DockStyle::Top;
			this->LcdLine1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 27.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LcdLine1->Location = System::Drawing::Point(0, 0);
			this->LcdLine1->Name = L"LcdLine1";
			this->LcdLine1->Size = System::Drawing::Size(579, 37);
			this->LcdLine1->TabIndex = 0;
			this->LcdLine1->Text = L"Click on";
			// 
			// PinList
			// 
			this->PinList->ContextMenuStrip = this->contextMenuStripPin;
			this->PinList->Dock = System::Windows::Forms::DockStyle::Right;
			this->PinList->Font = (gcnew System::Drawing::Font(L"Lucida Console", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->PinList->FormattingEnabled = true;
			this->PinList->ItemHeight = 16;
			this->PinList->Location = System::Drawing::Point(579, 0);
			this->PinList->Name = L"PinList";
			this->PinList->Size = System::Drawing::Size(131, 604);
			this->PinList->TabIndex = 1;
			this->PinList->DoubleClick += gcnew System::EventHandler(this, &ArduinoForm::OnDoubleClick);
			this->PinList->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ArduinoForm::ArduinoForm_KeyPress);
			// 
			// contextMenuStripPin
			// 
			this->contextMenuStripPin->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toggleToolStripMenuItem });
			this->contextMenuStripPin->Name = L"contextMenuStripPin";
			this->contextMenuStripPin->Size = System::Drawing::Size(111, 26);
			// 
			// toggleToolStripMenuItem
			// 
			this->toggleToolStripMenuItem->Name = L"toggleToolStripMenuItem";
			this->toggleToolStripMenuItem->Size = System::Drawing::Size(110, 22);
			this->toggleToolStripMenuItem->Text = L"Toggle";
			this->toggleToolStripMenuItem->Click += gcnew System::EventHandler(this, &ArduinoForm::toggleToolStripMenuItem_Click);
			// 
			// LcdLine2
			// 
			this->LcdLine2->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LcdLine2->Dock = System::Windows::Forms::DockStyle::Top;
			this->LcdLine2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 27.75F));
			this->LcdLine2->Location = System::Drawing::Point(0, 37);
			this->LcdLine2->Name = L"LcdLine2";
			this->LcdLine2->Size = System::Drawing::Size(579, 37);
			this->LcdLine2->TabIndex = 2;
			this->LcdLine2->Text = L"Start button";
			// 
			// LcdLine3
			// 
			this->LcdLine3->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LcdLine3->Dock = System::Windows::Forms::DockStyle::Top;
			this->LcdLine3->Font = (gcnew System::Drawing::Font(L"Lucida Console", 27.75F));
			this->LcdLine3->Location = System::Drawing::Point(0, 74);
			this->LcdLine3->Name = L"LcdLine3";
			this->LcdLine3->Size = System::Drawing::Size(579, 37);
			this->LcdLine3->TabIndex = 3;
			this->LcdLine3->Text = L"To execute";
			// 
			// LcdLine4
			// 
			this->LcdLine4->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LcdLine4->Dock = System::Windows::Forms::DockStyle::Top;
			this->LcdLine4->Font = (gcnew System::Drawing::Font(L"Lucida Console", 27.75F));
			this->LcdLine4->Location = System::Drawing::Point(0, 111);
			this->LcdLine4->Name = L"LcdLine4";
			this->LcdLine4->Size = System::Drawing::Size(579, 37);
			this->LcdLine4->TabIndex = 4;
			this->LcdLine4->Text = L"Your Ino";
			// 
			// LcdLine5
			// 
			this->LcdLine5->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->LcdLine5->Dock = System::Windows::Forms::DockStyle::Top;
			this->LcdLine5->Font = (gcnew System::Drawing::Font(L"Lucida Console", 27.75F));
			this->LcdLine5->Location = System::Drawing::Point(0, 148);
			this->LcdLine5->Name = L"LcdLine5";
			this->LcdLine5->Size = System::Drawing::Size(579, 37);
			this->LcdLine5->TabIndex = 5;
			this->LcdLine5->Text = L"File !";
			// 
			// SerialConsole
			// 
			this->SerialConsole->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SerialConsole->Location = System::Drawing::Point(0, 195);
			this->SerialConsole->Multiline = true;
			this->SerialConsole->Name = L"SerialConsole";
			this->SerialConsole->ReadOnly = true;
			this->SerialConsole->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->SerialConsole->Size = System::Drawing::Size(579, 240);
			this->SerialConsole->TabIndex = 6;
			this->SerialConsole->WordWrap = false;
			this->SerialConsole->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ArduinoForm::ArduinoForm_KeyPress);
			// 
			// buttonStart
			// 
			this->buttonStart->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonStart->Dock = System::Windows::Forms::DockStyle::Left;
			this->buttonStart->Location = System::Drawing::Point(0, 0);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(75, 32);
			this->buttonStart->TabIndex = 7;
			this->buttonStart->Text = L"Start";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &ArduinoForm::buttonStart_Click);
			// 
			// buttonExit
			// 
			this->buttonExit->DialogResult = System::Windows::Forms::DialogResult::Abort;
			this->buttonExit->Dock = System::Windows::Forms::DockStyle::Right;
			this->buttonExit->Location = System::Drawing::Point(504, 0);
			this->buttonExit->Name = L"buttonExit";
			this->buttonExit->Size = System::Drawing::Size(75, 32);
			this->buttonExit->TabIndex = 8;
			this->buttonExit->Text = L"Exit";
			this->buttonExit->UseVisualStyleBackColor = true;
			this->buttonExit->Click += gcnew System::EventHandler(this, &ArduinoForm::buttonExit_Click);
			// 
			// buttonAbout
			// 
			this->buttonAbout->Dock = System::Windows::Forms::DockStyle::Right;
			this->buttonAbout->Location = System::Drawing::Point(429, 0);
			this->buttonAbout->Name = L"buttonAbout";
			this->buttonAbout->Size = System::Drawing::Size(75, 32);
			this->buttonAbout->TabIndex = 9;
			this->buttonAbout->Text = L"About...";
			this->buttonAbout->UseVisualStyleBackColor = true;
			// 
			// timerLoop
			// 
			this->timerLoop->Tick += gcnew System::EventHandler(this, &ArduinoForm::timerLoop_Tick);
			// 
			// buttonPause
			// 
			this->buttonPause->DialogResult = System::Windows::Forms::DialogResult::Abort;
			this->buttonPause->Dock = System::Windows::Forms::DockStyle::Left;
			this->buttonPause->Enabled = false;
			this->buttonPause->Location = System::Drawing::Point(75, 0);
			this->buttonPause->Name = L"buttonPause";
			this->buttonPause->Size = System::Drawing::Size(75, 32);
			this->buttonPause->TabIndex = 10;
			this->buttonPause->Text = L"Pause";
			this->buttonPause->UseVisualStyleBackColor = true;
			this->buttonPause->Click += gcnew System::EventHandler(this, &ArduinoForm::buttonPause_Click);
			// 
			// textBoxEventLog
			// 
			this->textBoxEventLog->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->textBoxEventLog->Font = (gcnew System::Drawing::Font(L"Lucida Console", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBoxEventLog->Location = System::Drawing::Point(0, 464);
			this->textBoxEventLog->Multiline = true;
			this->textBoxEventLog->Name = L"textBoxEventLog";
			this->textBoxEventLog->ReadOnly = true;
			this->textBoxEventLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBoxEventLog->Size = System::Drawing::Size(579, 108);
			this->textBoxEventLog->TabIndex = 11;
			this->textBoxEventLog->WordWrap = false;
			// 
			// textSerialInput
			// 
			this->textSerialInput->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textSerialInput->Location = System::Drawing::Point(44, 0);
			this->textSerialInput->Name = L"textSerialInput";
			this->textSerialInput->Size = System::Drawing::Size(491, 20);
			this->textSerialInput->TabIndex = 12;
			// 
			// buttonSerialSend
			// 
			this->buttonSerialSend->Dock = System::Windows::Forms::DockStyle::Left;
			this->buttonSerialSend->Location = System::Drawing::Point(0, 0);
			this->buttonSerialSend->Name = L"buttonSerialSend";
			this->buttonSerialSend->Size = System::Drawing::Size(44, 29);
			this->buttonSerialSend->TabIndex = 13;
			this->buttonSerialSend->Text = L"Serial";
			this->buttonSerialSend->UseVisualStyleBackColor = true;
			this->buttonSerialSend->Click += gcnew System::EventHandler(this, &ArduinoForm::buttonSerialSend_Click);
			// 
			// button1
			// 
			this->button1->Dock = System::Windows::Forms::DockStyle::Right;
			this->button1->Location = System::Drawing::Point(535, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(44, 29);
			this->button1->TabIndex = 14;
			this->button1->Text = L"Pins";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ArduinoForm::button1_Click);
			// 
			// panelLCD
			// 
			this->panelLCD->Controls->Add(this->LcdLine5);
			this->panelLCD->Controls->Add(this->LcdLine4);
			this->panelLCD->Controls->Add(this->LcdLine3);
			this->panelLCD->Controls->Add(this->LcdLine2);
			this->panelLCD->Controls->Add(this->LcdLine1);
			this->panelLCD->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelLCD->Location = System::Drawing::Point(0, 0);
			this->panelLCD->Name = L"panelLCD";
			this->panelLCD->Size = System::Drawing::Size(579, 195);
			this->panelLCD->TabIndex = 15;
			// 
			// panelSerial
			// 
			this->panelSerial->Controls->Add(this->textSerialInput);
			this->panelSerial->Controls->Add(this->button1);
			this->panelSerial->Controls->Add(this->buttonSerialSend);
			this->panelSerial->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panelSerial->Location = System::Drawing::Point(0, 435);
			this->panelSerial->Name = L"panelSerial";
			this->panelSerial->Size = System::Drawing::Size(579, 29);
			this->panelSerial->TabIndex = 16;
			// 
			// panelButtons
			// 
			this->panelButtons->Controls->Add(this->buttonPause);
			this->panelButtons->Controls->Add(this->buttonAbout);
			this->panelButtons->Controls->Add(this->buttonExit);
			this->panelButtons->Controls->Add(this->buttonStart);
			this->panelButtons->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panelButtons->Location = System::Drawing::Point(0, 572);
			this->panelButtons->Name = L"panelButtons";
			this->panelButtons->Size = System::Drawing::Size(579, 32);
			this->panelButtons->TabIndex = 17;
			// 
			// ArduinoForm
			// 
			this->AcceptButton = this->buttonSerialSend;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->buttonExit;
			this->ClientSize = System::Drawing::Size(710, 604);
			this->Controls->Add(this->SerialConsole);
			this->Controls->Add(this->panelSerial);
			this->Controls->Add(this->textBoxEventLog);
			this->Controls->Add(this->panelButtons);
			this->Controls->Add(this->panelLCD);
			this->Controls->Add(this->PinList);
			this->KeyPreview = true;
			this->Name = L"ArduinoForm";
			this->Text = L"ArduiEmulator";
			this->Load += gcnew System::EventHandler(this, &ArduinoForm::MyForm_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ArduinoForm::ArduinoForm_KeyPress);
			this->contextMenuStripPin->ResumeLayout(false);
			this->panelLCD->ResumeLayout(false);
			this->panelSerial->ResumeLayout(false);
			this->panelSerial->PerformLayout();
			this->panelButtons->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			if (!this->LoopStarted)
			{
				this->LoopStarted = true;
				this->LoopPaused = false;
				this->buttonStart->Text = "Stop";
				this->buttonPause->Text = "Pause";
				this->buttonPause->Enabled = true;
				SerialBuffer = String::Empty;
				_clear();

				for (int i = 0; i < preStartDebugsCount; i++)
					_debug(preStartDebugs[i]);

				this->SetupPointer();		// run setup
				this->timerLoop->Start();	// start loops
			}
			else
			{
				this->timerLoop->Stop();
				this->LoopStarted = false;
				this->LoopPaused = false;
				this->buttonStart->Text = "Start";
				this->buttonPause->Enabled = false;
				SerialBuffer = String::Empty;
			}
		}

		private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) 
		{
			//_clear();

			SerialBuffer = String::Empty;
		}

		private: System::Void buttonExit_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			this->Close();
		}

		private: System::Void timerLoop_Tick(System::Object^  sender, System::EventArgs^  e) 
		{
			if (this->LoopStarted && !this->LoopPaused)
				this->LoopPointer();
		}

		private: System::Void buttonPause_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			this->LoopPaused = !this->LoopPaused;
			if (this->LoopPaused)
				this->buttonPause->Text = "Continue";
			else
				this->buttonPause->Text = "Pause";
		}

		private: System::Void ArduinoForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
		{
			if (!this->textSerialInput->Focused)
				this->lastKeyPressed = e->KeyChar;
		}

		private: System::Void buttonSerialSend_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			SerialBuffer = this->textSerialInput->Text + "\n";
			this->textSerialInput->Text = String::Empty;
		}

		private:
			System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);

		private: 
			System::Void toggleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
			void OnDoubleClick(System::Object ^sender, System::EventArgs ^e);
};
}
