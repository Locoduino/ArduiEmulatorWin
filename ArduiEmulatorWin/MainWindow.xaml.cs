using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;

namespace ArduiEmulatorWin
{
	/// <summary>
	/// Interaction logic for ArduinoWindow.xaml
	/// </summary>
	public partial class ArduinoWindow
	{
		public static ArduinoWindow MainForm;

		private Queue<string> bufferSerialLog;

		const int BUFFERSIZE = 1000;

		private Queue<string> bufferDebug;
		const int DEBUGBUFFERSIZE = 200;

		public Modif_Window_ViewModel mModifWindowVM = new Modif_Window_ViewModel();

		public ArduinoWindow()
		{
			InitializeComponent();

			DataContext = mModifWindowVM;

			MainForm = this;
			this.ListPins.ItemsSource = this.mModifWindowVM.List_Content;
			ClearSerialLog();
			ClearDebug();

			Arduino.ArduinoModelInit();

			foreach (ArduinoModel model in Arduino.ArduinoModels)
			{
				if (Arduino.arduinoModel == null)
					Arduino.arduinoModel = model;
				var item = new ComboBoxItem(model);
				this.ArduinoModelCombo.Items.Add(item);
				if (Arduino.arduinoModel == model)
					this.ArduinoModelCombo.SelectedItem = item;
			}

			Arduino.pinsSetup();
			this.NamedPipesBegin();
		}

		class ComboBoxItem
		{
			public ArduinoModel model;

			public ComboBoxItem(ArduinoModel inModel)
			{
				this.model = inModel;
			}

			public override string ToString()
			{
				return model.Name;
			}
		}

		public void ClearSerialLog()
		{
			this.bufferSerialLog = new Queue<string>(BUFFERSIZE);
			this.Console.Clear();
		}

		public void ClearDebug()
		{
			this.bufferDebug = new Queue<string>(DEBUGBUFFERSIZE);
			this.Debug.Clear();
		}

		public void serial_log(String inString)
		{
			StringBuilder console = new StringBuilder();

			this.bufferSerialLog.Enqueue(inString);
			if (this.bufferSerialLog.Count > BUFFERSIZE)
				this.bufferSerialLog.Dequeue();

			foreach (string line in bufferSerialLog)
			{
				if (console.Length > 0)
					console.Append("\r\n");
				console.Append(line);
			}

			this.Console.Text = console.ToString();
			this.Console.Select(Console.Text.Length, 0);
			this.Console.ScrollToLine(Console.GetLineIndexFromCharacterIndex(Console.SelectionStart));
		}

		public void debug(String inString)
		{
			//if (this.ListPins.Items == null)
			{
				this.bufferDebug.Enqueue(inString);
				if (this.bufferDebug.Count > DEBUGBUFFERSIZE)
					this.bufferDebug.Dequeue();
				//return;
			}

			StringBuilder console = new StringBuilder();

			foreach (string line in bufferDebug)
			{
				if (console.Length > 0)
					console.Append("\r\n");
				console.Append(line);
			}

			Debug.Text = console.ToString();
			Debug.Select(Debug.Text.Length, 0);
			Debug.ScrollToLine(Debug.GetLineIndexFromCharacterIndex(Debug.SelectionStart));
		}

		public void Error(String inString)
		{
			debug("*** ARDUINO ERROR : " + inString);
		}

		private void SerialButton_Click(object sender, RoutedEventArgs e)
		{
			this.Send(this.SerialInput.Text);
			this.SerialInput.Text = string.Empty;
		}

		public bool DebugPipeMode;

		private void CheckBoxDebugPipe_Click(object sender, RoutedEventArgs e)
		{
			this.DebugPipeMode = this.checkBoxDebugPipeMode.IsChecked.GetValueOrDefault(false);
		}

		private void PinsButton_Click(object sender, RoutedEventArgs e)
		{
			this.ParseMessage(this.SerialInput.Text);
			//this.mModifWindowVM.lcdLine1 = this.SerialInput.Text;
			this.SerialInput.Text = string.Empty;
		}

		private void ListPins_MouseDoubleClick(object sender, MouseButtonEventArgs e)
		{
			var selection = this.ListPins.SelectedItem as ArduinoPin;

			if (selection != null)
			{
				if (selection.State == Arduino.VS_HIGH)
				{
					selection.State = Arduino.VS_LOW;
					NamedPipes.PipeSender.Send("PS " + selection.Number + " LOW");
				}
				else 
				if (selection.State == Arduino.VS_LOW)
				{
					selection.State = Arduino.VS_HIGH;
					NamedPipes.PipeSender.Send("PS " + selection.Number + " HIGH");
				}
			}
		}

		private void ArduinoModelCombo_SelectionChanged(object sender, SelectionChangedEventArgs e)
		{
			Arduino.arduinoModel = ((ComboBoxItem)this.ArduinoModelCombo.SelectedItem).model;
		}

		private void AboutButton_Click(object sender, RoutedEventArgs e)
		{
			var dlg = new WindowAbout();

			dlg.ShowDialog();
		}

		private void ArduiEmulator_KeyDown(object sender, KeyEventArgs e)
		{
			string key = e.Key.ToString();
			key = key.Replace("NumPad", "");

			NamedPipes.PipeSender.Send("KBD " + key);
		}
	}
}
