using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows;

namespace ArduiEmulatorWin
{
	static class Extensions
	{
		public static void Sort<T>(this ObservableCollection<T> collection) where T : IComparable
		{
			List<T> sorted = collection.OrderBy(x => x).ToList();
			for (int i = 0; i < sorted.Count(); i++)
				collection.Move(collection.IndexOf(sorted[i]), i);
		}
	}

	public class ViewModelBase : INotifyPropertyChanged
	{
		public event PropertyChangedEventHandler PropertyChanged;

		public void NotifyPropertyChangedEvent(string propertyName)
		{
			if (PropertyChanged != null)
				PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
		}
	}

	public class Expander
	{
		public int ID;
		public string Name;
		public int NbPin;
		public int Type;	// INPUT, OUTPUT...
	}

	public class ArduinoItem : ViewModelBase, IComparable
	{
		static public FullyObservableCollection<ArduinoItem> ArduinoItems;
		static public List<Expander> Expanders;

		private int number;		// >= 10000 for timers
		private int state;		// pin : 0/1 or value in analog mode, Timer : Start(1) or Stop(0)
		protected string formattedName;
		private string name;
		private int expID;

		public bool IsTimer 
		{ 
			get { return this.number >= 10000; } 
		}

		public virtual int Number
		{
			get => this.number; set
			{
				this.number = value;
				this.BuildFormattedName();
			}
		}

		public int State
		{
			get => this.state; set
			{
				this.state = value;
				NotifyPropertyChangedEvent("State");
			}
		}

		public int ExpID
		{
			get => this.expID; set
			{
				this.expID= value;
				this.BuildFormattedName();
			}
		}

		public virtual string Name
		{
			get
			{
				return this.name;
			}

			set
			{
				this.name = value;
				this.BuildFormattedName();
			}
		}

		// The formatted name can be '##number' where number is the pin number, 'name' where name is the direct pin name.
		public string FormattedName
		{
			get => this.formattedName; set
			{
				this.formattedName = value;
				NotifyPropertyChangedEvent("FormattedName");
			}
		}

		// for Arduino pin without name : ##number 
		// for Arduino pin with name : number (name)
		// for expander pin without name : ##expname number 
		// for expander pin with name : expname number (name)
		private void BuildFormattedName()
		{
			if (this.expID == 0)
			{
				if (string.IsNullOrEmpty(this.name))
				{
					if (this.IsTimer)
						this.formattedName = "Timer" + (number-10000).ToString();
					else
						this.formattedName = "##" + number.ToString();
				}
				else
				{
					if (this.IsTimer)
						this.formattedName = this.name;
					else
						this.formattedName = number.ToString() + "(" + this.name + ")";
				}
			}
			else
			{
				Expander exp = ArduiEmulatorWin.ArduinoWindow.MainForm.mModifWindowVM.GetExpander(this.expID);
				if (string.IsNullOrEmpty(this.name))
				{
					this.formattedName = "##" + exp.Name + " " + number.ToString();
				}
				else
				{
					this.formattedName = exp.Name + " " + number.ToString() + "(" + this.name + ")";
				}
			}
		}
		
		public virtual int CompareTo(object o)
		{
			ArduinoItem a = this;
			var b = (ArduinoItem)o;
			if (a.expID.CompareTo(b.expID) == 0)
				return a.number.CompareTo(b.number);
			return a.expID.CompareTo(b.expID);
		}
	}

	public partial class Modif_Window_ViewModel : ViewModelBase
	{
		public ArduinoItem Add_Content(int inPin, int inExpID, int inState, string inName)
		{
			var pin = new ArduinoItem { Number = inPin, ExpID = inExpID, State = inState, Name = inName };
			ArduinoItem.ArduinoItems.Add(pin);
			ArduinoItem.ArduinoItems.Sort();

			if (inExpID == 0)
				if (Arduino.arduinoModel.pinFlags[inPin].HasFlag(ArduinoModel.PinFunc.Led))
					if (string.IsNullOrEmpty(inName))
						pin.Name = "Led";

			NotifyPropertyChangedEvent("Add");
			return pin;
		}

		public ArduinoItem Add_Timer_Content(int inId, int inState, string inName)
		{
			var timer = new ArduinoItem { Number = 10000+inId, State = inState, Name = inName };
			timer.ExpID = 0;
			ArduinoItem.ArduinoItems.Add(timer);
			ArduinoItem.ArduinoItems.Sort();

			NotifyPropertyChangedEvent("AddTimer");
			return timer;
		}

		public void Clear_Content()
		{
			if (ArduinoItem.ArduinoItems != null)
			{
				ArduinoItem.Expanders.Clear();
				ArduinoItem.ArduinoItems.Clear();
				Lcd.screen.clear();
				NotifyPropertyChangedEvent("Clear");
			}
		}

		public FullyObservableCollection<ArduinoItem> List_Content
		{
			get
			{
				if (ArduinoItem.ArduinoItems == null)
				{
					ArduinoItem.Expanders = new List<Expander>();
					ArduinoItem.ArduinoItems = new FullyObservableCollection<ArduinoItem>();
				}

				return ArduinoItem.ArduinoItems;
			}
			set { ArduinoItem.ArduinoItems = value; }
		}

		internal void display()
		{
			foreach (ArduinoItem txtvalue in ArduinoItem.ArduinoItems)
			{
				MessageBox.Show(txtvalue.Number + " " + txtvalue.Name);
			}
		}

		public ArduinoItem GetPin(int inPin, int inExpID = 0)
		{
			if (ArduinoItem.ArduinoItems == null)
				return null;
			foreach (var pin in ArduinoItem.ArduinoItems)
				if (pin.Number == inPin && pin.ExpID == inExpID)
					return pin;
			return null;
		}

		public ArduinoItem GetTimer(int inPin)
		{
			return this.GetPin(10000 + inPin, 0);
		}

		public ArduinoItem GetPin(string inName)
		{
			if (ArduinoItem.ArduinoItems == null)
				return null;
			foreach (var pin in ArduinoItem.ArduinoItems)
				if (pin.Name == inName)
					return pin;
			return null;
		}

		public Expander GetExpander(int inExpID)
		{
			if (ArduinoItem.Expanders == null)
				return null;
			foreach (var expander in ArduinoItem.Expanders)
				if (expander.ID == inExpID)
					return expander;
			return null;
		}

		public int GetState(int inPin, int inExpID = 0)
		{
			ArduinoItem pin = GetPin(inPin, inExpID);
			if (pin == null)
				return Arduino.UNDEFINEDSTATE;

			return pin.State;
		}

		public string GetName(int inPin, int inExpID = 0)
		{
			ArduinoItem pin = GetPin(inPin, inExpID);
			if (pin == null)
				return "";

			return pin.Name;
		}

		public bool SetName(int inPin, int inExpID, string inName)
		{
			ArduinoItem pin = GetPin(inPin, inExpID);
			if (pin == null)
			{
				pin = Add_Content(inPin, inExpID, Arduino.UNDEFINEDSTATE, inName);
			}
			if (inName.Length > 10)
				pin.Name = inName.Substring(0, 10);
			else
				pin.Name = inName;
			NotifyPropertyChangedEvent("Name");
			return true;
		}

		public bool SetTimerName(int inPin, string inName)
		{
			ArduinoItem timer = GetTimer(inPin);
			if (timer == null)
			{
				timer = Add_Timer_Content(inPin, Arduino.TIMER_STOPPED, inName);
			}
			if (inName.Length > 10)
				timer.Name = inName.Substring(0, 10);
			else
				timer.Name = inName;
			NotifyPropertyChangedEvent("Name");
			return true;
		}

		public bool SetState(int inPin, int inExpID, int inState)
		{
			ArduinoItem pin = GetPin(inPin, inExpID);
			if (pin == null)
			{
				pin = Add_Content(inPin, inExpID, Arduino.UNDEFINEDSTATE, string.Empty);
			}
			pin.State = inState;
			NotifyPropertyChangedEvent("State");
			return true;
		}

		public bool SetTimerState(int inPin, int inState)
		{
			ArduinoItem timer = GetTimer(inPin);
			if (timer == null)
			{
				timer = Add_Timer_Content(inPin, Arduino.TIMER_STOPPED, string.Empty);
			}
			timer.State = inState;
			NotifyPropertyChangedEvent("State");
			return true;
		}
	}

	public class PinNameConverter : System.Windows.Data.IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			string name = value as string;
			if (name == null)
				return "";

			if (name.StartsWith("##"))
				return name.Substring(2).PadRight(10);

			return name.PadRight(10);
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			throw new NotImplementedException();
		}
	}

	public class PinStateConverter : System.Windows.Data.IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			string str;
			switch ((int)value)
			{
				case Arduino.UNDEFINEDSTATE:
					str = "undef";
					break;
				case Arduino.VS_LOW:
					str = "LOW";
					break;
				case Arduino.VS_HIGH:
					str = "HIGH";
					break;
				case Arduino.OUTPUT_RESERVED:
					str = "RESERVED";
					break;
				case Arduino.OUTPUT_INTERRUPT:
					str = "INTERRUPT";
					break;
				default:    // analog...
					str = String.Format("{0,-4}", value.ToString());
					break;
			}
			return str;
		}

		public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
		{
			throw new NotImplementedException();
		}
	}
}
