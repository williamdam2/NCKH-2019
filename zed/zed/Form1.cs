using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ZedGraph;
using System.IO.Ports;
using System.IO;
using System.Threading;


namespace zed
{
    public partial class Form1 : Form
    {
        
       
         

        public Form1()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;
            serialPort.DataReceived += SerialPort_DataReceived;
            
            
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            ThreadStart threadStart = new ThreadStart(getData);
            Thread thread = new Thread(threadStart);
            thread.IsBackground = true;
            thread.Start();
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            grapInitial();
            reFreshCbbComPort();
        }

     
       

        private void BtRefreshF3_Click(object sender, EventArgs e)
        {
            reFreshCbbComPort();
        }

        private void BtOpenF3_Click(object sender, EventArgs e)
        {
            setPropertise();
            try
            {
                serialPort.Open();               
            }
            catch (Exception ex)
            {
                lbStatus.Text = "OFF";
                MessageBox.Show(ex.Message);
                serialPort.Close();
                return ;
            }
            lbStatus.Text = "ON";
        }

        private void BtCloseF3_Click(object sender, EventArgs e)
        {
            serialPort.Close();
            lbStatus.Text = "OFF";
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            test();
        }
    }
}
