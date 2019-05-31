using System;
using System.IO.Pipes;
using System.Text;
using System.Windows.Threading;

public class PipeServer
{
	private static NamedPipeServerStream namedPipeServer = null;
	private static StringBuilder messageBuilder = new StringBuilder();
	private static string bufferToSend;
	private static System.IO.StreamWriter sw;

	public static void Init()
	{
		namedPipeServer = new NamedPipeServerStream("ArduinoEmulatorPipe", PipeDirection.InOut, 1, PipeTransmissionMode.Message);
		namedPipeServer.WaitForConnectionAsync();
		sw = new System.IO.StreamWriter(namedPipeServer);
		bufferToSend = string.Empty;
	}

	public static void Loop()
	{
		if (!namedPipeServer.IsConnected)
		{
			namedPipeServer.WaitForConnection(); // retry to connect
		}

		do
		{
			int khar = namedPipeServer.ReadByte();
			if (khar == 13 || khar == 10)
			{
				if (messageBuilder.Length > 0)
					transmit(messageBuilder.ToString());
				messageBuilder.Length = 0;
				continue;
			}
			messageBuilder.Append((char) khar);
		}
		while (!namedPipeServer.IsMessageComplete);

		if (!string.IsNullOrEmpty(bufferToSend))
		{
			sw.WriteLine(bufferToSend);
			bufferToSend = string.Empty;
		}
	}

	// Assume the right thread to pass the received message...
	private static void transmit(string message)
	{
		if (Dispatcher.CurrentDispatcher != ArduiEmulatorWin.ArduinoWindow.MainForm.UIDispatcher)
		{
			ArduiEmulatorWin.ArduinoWindow.MainForm.UIDispatcher.Invoke(delegate ()
			{
				ArduiEmulatorWin.ArduinoWindow.MainForm.TreatMessage(message);
			});
		}
		else
		{
			ArduiEmulatorWin.ArduinoWindow.MainForm.TreatMessage(message);
		}
	}

	public static void SendMessage(string message)
	{
		bufferToSend = message;
	}
}
