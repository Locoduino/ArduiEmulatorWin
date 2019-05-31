using System;
using System.IO.Pipes;
using System.Text;
using System.Threading;
using System.IO;

public class PipeClient
{
	private static NamedPipeClientStream converterStream;
	public static bool EndConnection;
	public static string bufferToSend;

	public static void Init()
	{
		EndConnection = false;
		Thread converterPipeThread = new Thread(() => ConverterPipe());
		converterPipeThread.Start();
		bufferToSend = string.Empty;
	}

	/// <summary>
	/// Process default data and send it to pipe.
	/// </summary>
	static void ConverterPipe()
	{
		converterStream = new NamedPipeClientStream("ArduinoEmulatorPipeClient");
		converterStream.ConnectAsync();
		StreamWriter sw = new StreamWriter(converterStream);

		do
		{
			if (!converterStream.IsConnected)
				continue;

			if (bufferToSend.Length > 0)
			{
				sw.WriteLine(bufferToSend);
			}

		} while (!EndConnection);

		converterStream.Close();
	}
}
