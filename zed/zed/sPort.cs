using System.IO.Ports;
using System.IO;
using System;

namespace zed
{
    public partial class Form1 
    {
        static string dataBuffer = "";
        void reFreshCbbComPort()
        {
            string[] portname = SerialPort.GetPortNames();
            cbbComPort.DataSource = portname;
        }

        void setPropertise()
        {
            serialPort.BaudRate = int.Parse(cbbBaudRate.Text);
            serialPort.PortName = cbbComPort.Text;
            switch(cbbParity.Text)
            {
                case "None":
                    {
                        serialPort.Parity = Parity.None;
                        break;
                    }
                case "Odd":
                    {
                        serialPort.Parity = Parity.Odd;
                        break;
                    }
                case "Even":
                    {
                        serialPort.Parity = Parity.Even;
                        break;
                    }

            }

            switch(cbbStopBit.Text)
            {
                case "One":
                    {
                        serialPort.StopBits = StopBits.One;
                        break;
                    }
                case "Two":
                    {
                        serialPort.StopBits = StopBits.Two;
                        break; 
                    }

            }

            
        }

        void getData()
        {
            string substring = serialPort.ReadExisting();
            string target = "";
            if (substring.Contains(">")) // end of packet
            {
                dataBuffer += substring;
                while (dataBuffer.Contains(">"))
                {                    
                    int first = dataBuffer.IndexOf(">");
                    target = dataBuffer.Substring(0, first);                   
                    dataBuffer = dataBuffer.Substring(first + 2);
                    first = target.IndexOf("<");
                    target = target.Substring(first+1);
                    //lbparity.Text = target;
                    encrypt(target);
                }

            }
            else
            {
                dataBuffer += substring;
                return;
            }
            
        }
    }
}