using System;
using System.Text;
using System.IO.Pipes;
using System.Diagnostics;

namespace NamedPipes
{
    // Delegate for passing received message back to caller
	public delegate void NewMessageDelegate(string NewMessage);

	// A listener is created from the beggining and stay open all the time.
	class PipeListener
    {
        public static PipeListener pipeServerListener;
		public event NewMessageDelegate PipeMessage;
        static string pipeName;
		static public bool connected;

		public static void begin(string inPipeName, NewMessageDelegate inDelegate)
		{
			pipeName = inPipeName;
			pipeServerListener = new PipeListener();
			pipeServerListener.PipeMessage += inDelegate;
			pipeServerListener.Listen();
			connected = false;
		}

		public static void dispose(NewMessageDelegate inDelegate)
		{
			pipeServerListener.PipeMessage -= inDelegate;
			pipeServerListener = null;
		}

		public void Listen()
        {
            try
            {
                // Create the new async pipe 
                var pipeServer = new NamedPipeServerStream(pipeName, PipeDirection.In, 1, PipeTransmissionMode.Byte, PipeOptions.Asynchronous);

				// Wait for a connection
				pipeServer.BeginWaitForConnection(new AsyncCallback(WaitForConnectionCallBack), pipeServer);
            }
            catch (Exception oEX)
            {
                Debug.WriteLine(oEX.Message);
            }
        }

        private void WaitForConnectionCallBack(IAsyncResult iar)
        {
            try
            {
                // Get the pipe
                var pipeServer = (NamedPipeServerStream)iar.AsyncState;
                // End waiting for the connection
				pipeServer.EndWaitForConnection(iar);

                byte[] buffer = new byte[1000];

                // Read the incoming message
                int count = pipeServer.Read(buffer, 0, 1000);
                
                // Convert byte buffer to string
                string stringData = Encoding.Unicode.GetString(buffer, 0, buffer.Length);
				stringData = stringData.Substring(0, count / sizeof(char));
                Debug.WriteLine(stringData + Environment.NewLine);

				// Pass message back to calling form
				if (this.PipeMessage != null && !string.IsNullOrEmpty(stringData))
				{
					connected = true;

					this.PipeMessage.Invoke(stringData);
				}

                // Kill original sever and create new wait server
                pipeServer.Close();
                pipeServer = null;
                pipeServer = new NamedPipeServerStream(pipeName, PipeDirection.In, 1, PipeTransmissionMode.Byte, PipeOptions.Asynchronous);

				// Recursively wait for the connection again and again....
                pipeServer.BeginWaitForConnection(new AsyncCallback(WaitForConnectionCallBack), pipeServer);
            }
            catch
            {
                return;
            }
        }
    }

	// A NamedPipeClientStream is only created when needed...
	class PipeSender
	{
		public static PipeSender pipeClientSender;
		static string pipeName;

		public static void begin(string inPipeName)
		{
			pipeName = inPipeName;
		}

		public static void dispose()
		{
			pipeClientSender = null;
		}

		public static void Send(string SendStr, int TimeOut = 1000)
		{
			pipeClientSender = new PipeSender();
			pipeClientSender.send(SendStr, TimeOut);
		}

		private void send(string SendStr, int TimeOut = 1000)
		{
			try
			{
				var pipeStream = new NamedPipeClientStream(".", pipeName, PipeDirection.Out, PipeOptions.Asynchronous);

				// The connect function will indefinitely wait for the pipe to become available
				// If that is not acceptable specify a maximum waiting time (in ms)
				if (!pipeStream.IsConnected)
					pipeStream.Connect(0);
				Debug.WriteLine("[Client] Pipe connection established");

				byte[] _buffer = Encoding.UTF8.GetBytes(SendStr);
				pipeStream.BeginWrite(_buffer, 0, _buffer.Length, AsyncSend, pipeStream);
			}
			catch (TimeoutException oEX)
			{
				Debug.WriteLine(oEX.Message);
			}
		}

		private void AsyncSend(IAsyncResult iar)
		{
			try
			{
				// Get the pipe
				var pipeStream = (NamedPipeClientStream)iar.AsyncState;

				// End the write
				pipeStream.EndWrite(iar);
				pipeStream.Flush();
				pipeStream.Close();
				pipeStream.Dispose();
			}
			catch (Exception oEX)
			{
				Debug.WriteLine(oEX.Message);
			}
		}
	}
}
