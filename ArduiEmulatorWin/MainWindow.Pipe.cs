using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Threading;
using System.Threading.Tasks;
using System.Timers;
using NamedPipes;

namespace ArduiEmulatorWin
{
	public partial class ArduinoWindow
	{
		private Dispatcher UIDispatcher;
		private DispatcherTimer connectionTestTimer;

		private void NamedPipesBegin()
		{
			UseThisThreadForEvents();

			PipeSender.begin("FromArduino");
			PipeListener.begin("ToArduino", new NewMessageDelegate(PipesMessageHandler));

			connectionTestTimer = new DispatcherTimer();

			connectionTestTimer.Tick += ConnectionTestTimer_Tick;
			connectionTestTimer.Interval = new TimeSpan(0, 0, 2);
			connectionTestTimer.Start();
		}

		static bool previousConnected = false;

		private void ConnectionTestTimer_Tick(object sender, EventArgs e)
		{
			if (previousConnected == NamedPipes.PipeListener.connected)
			{
				NamedPipes.PipeListener.connected = false;
				return;
			}

			Uri conn = new Uri(@"Connected.png", UriKind.Relative);
			if (NamedPipes.PipeListener.connected == false)
				conn = new Uri(@"Disconnected.png", UriKind.Relative);

			this.Connected.Source = new System.Windows.Media.Imaging.BitmapImage(conn);
			previousConnected = NamedPipes.PipeListener.connected;
			// Reset to false to check the next data reception...
			NamedPipes.PipeListener.connected = false;
		}

		private void Send(string inMessage)
		{
			PipeSender.Send(inMessage, 1000);
		}

		private void PipesMessageHandler(string message)
		{
			try
			{
				if (UIDispatcher.CheckAccess())
				{
					ParseMessage(message);
				}
				else
				{
					UIDispatcher.Invoke(new NewMessageDelegate(PipesMessageHandler), message);
				}
			}
			catch (Exception ex)
			{
				MainForm.debug(ex.Message);
			}

		}

		private void dispose()
		{
			PipeSender.dispose();
			PipeListener.dispose(new NewMessageDelegate(PipesMessageHandler));
		}

		// Call from the main thread
		private void UseThisThreadForEvents()
		{
			UIDispatcher = System.Windows.Threading.Dispatcher.CurrentDispatcher;
		}
	}
}
