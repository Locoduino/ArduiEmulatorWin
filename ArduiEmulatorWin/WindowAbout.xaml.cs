using System.Windows;
using System.Diagnostics;
using System.Windows.Navigation;

namespace ArduiEmulatorWin
{
	/// <summary>
	/// Interaction logic for Window1.xaml
	/// </summary>
	public partial class WindowAbout : Window
	{
		public WindowAbout()
		{
			this.InitializeComponent();
		}
		private void Hyperlink_RequestNavigate(object sender, RequestNavigateEventArgs e)
		{
			Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri));
			e.Handled = true;
		}

		private void OkButton_Click(object sender, RoutedEventArgs e)
		{
			var dlg = new WhatsNewWindow();

			dlg.ShowDialog();

		}
	}
}
