using System;
using System.IO;
using System.Text;
using System.Windows;

namespace ArduiEmulatorWin
{
	/// <summary>
	/// Interaction logic for Window1.xaml
	/// </summary>
	public partial class WhatsNewWindow : Window
	{
		public WhatsNewWindow()
		{
			InitializeComponent();
			string path;
			var dir = AppDomain.CurrentDomain.BaseDirectory;
			path = System.IO.Path.Combine(dir, "QuoiDeNeuf.txt");
			if (!File.Exists(path))
				path = System.IO.Path.Combine(dir, "WhatsNew.txt");
			var sr = new StreamReader(path, Encoding.Default);
			var sb = new StringBuilder();
			string line;
			while ((line = sr.ReadLine()) != null)
				sb.Append("\r\n" + line);
			sr.Close();
			this.Whatsnew.Text = sb.ToString();
			this.Whatsnew.SelectionLength = 0;
			this.Whatsnew.SelectionStart = 0;
			//				this.Whatsnew.BackColor = Color.White;		
		}

		private void Window_Loaded(object sender, RoutedEventArgs e)
		{
			//string text = System.IO.File.ReadAllText("WhatsNew.txt");
			//this.Whatsnew.Text = text;
		}
	}
}
