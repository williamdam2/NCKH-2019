namespace zed
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.zedGrap = new ZedGraph.ZedGraphControl();
            this.gbSettingCom = new System.Windows.Forms.GroupBox();
            this.cbbDataBit = new System.Windows.Forms.ComboBox();
            this.lbStatus = new System.Windows.Forms.Label();
            this.cbbComPort = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.cbbBaudRate = new System.Windows.Forms.ComboBox();
            this.btCloseF3 = new System.Windows.Forms.Button();
            this.cbbStopBit = new System.Windows.Forms.ComboBox();
            this.btOpenF3 = new System.Windows.Forms.Button();
            this.cbbParity = new System.Windows.Forms.ComboBox();
            this.btRefreshF3 = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.lbparity = new System.Windows.Forms.Label();
            this.lbDataBit = new System.Windows.Forms.Label();
            this.lbStopBit = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.button1 = new System.Windows.Forms.Button();
            this.gbSettingCom.SuspendLayout();
            this.SuspendLayout();
            // 
            // zedGrap
            // 
            this.zedGrap.Location = new System.Drawing.Point(384, 13);
            this.zedGrap.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.zedGrap.Name = "zedGrap";
            this.zedGrap.ScrollGrace = 0D;
            this.zedGrap.ScrollMaxX = 0D;
            this.zedGrap.ScrollMaxY = 0D;
            this.zedGrap.ScrollMaxY2 = 0D;
            this.zedGrap.ScrollMinX = 0D;
            this.zedGrap.ScrollMinY = 0D;
            this.zedGrap.ScrollMinY2 = 0D;
            this.zedGrap.Size = new System.Drawing.Size(867, 435);
            this.zedGrap.TabIndex = 0;
            // 
            // gbSettingCom
            // 
            this.gbSettingCom.Controls.Add(this.button1);
            this.gbSettingCom.Controls.Add(this.cbbDataBit);
            this.gbSettingCom.Controls.Add(this.lbStatus);
            this.gbSettingCom.Controls.Add(this.cbbComPort);
            this.gbSettingCom.Controls.Add(this.label5);
            this.gbSettingCom.Controls.Add(this.cbbBaudRate);
            this.gbSettingCom.Controls.Add(this.btCloseF3);
            this.gbSettingCom.Controls.Add(this.cbbStopBit);
            this.gbSettingCom.Controls.Add(this.btOpenF3);
            this.gbSettingCom.Controls.Add(this.cbbParity);
            this.gbSettingCom.Controls.Add(this.btRefreshF3);
            this.gbSettingCom.Controls.Add(this.label7);
            this.gbSettingCom.Controls.Add(this.lbparity);
            this.gbSettingCom.Controls.Add(this.lbDataBit);
            this.gbSettingCom.Controls.Add(this.lbStopBit);
            this.gbSettingCom.Controls.Add(this.label3);
            this.gbSettingCom.Location = new System.Drawing.Point(12, 13);
            this.gbSettingCom.Name = "gbSettingCom";
            this.gbSettingCom.Size = new System.Drawing.Size(330, 435);
            this.gbSettingCom.TabIndex = 31;
            this.gbSettingCom.TabStop = false;
            this.gbSettingCom.Text = "Setting COM";
            // 
            // cbbDataBit
            // 
            this.cbbDataBit.FormattingEnabled = true;
            this.cbbDataBit.Items.AddRange(new object[] {
            "6",
            "7",
            "8"});
            this.cbbDataBit.Location = new System.Drawing.Point(166, 97);
            this.cbbDataBit.Name = "cbbDataBit";
            this.cbbDataBit.Size = new System.Drawing.Size(121, 24);
            this.cbbDataBit.TabIndex = 16;
            this.cbbDataBit.Text = "8";
            // 
            // lbStatus
            // 
            this.lbStatus.AutoSize = true;
            this.lbStatus.ForeColor = System.Drawing.SystemColors.Highlight;
            this.lbStatus.Location = new System.Drawing.Point(247, 302);
            this.lbStatus.Name = "lbStatus";
            this.lbStatus.Size = new System.Drawing.Size(35, 17);
            this.lbStatus.TabIndex = 29;
            this.lbStatus.Text = "OFF";
            // 
            // cbbComPort
            // 
            this.cbbComPort.FormattingEnabled = true;
            this.cbbComPort.Location = new System.Drawing.Point(166, 29);
            this.cbbComPort.Name = "cbbComPort";
            this.cbbComPort.Size = new System.Drawing.Size(121, 24);
            this.cbbComPort.TabIndex = 15;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(181, 240);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(56, 17);
            this.label5.TabIndex = 28;
            this.label5.Text = "Status :";
            // 
            // cbbBaudRate
            // 
            this.cbbBaudRate.FormattingEnabled = true;
            this.cbbBaudRate.Items.AddRange(new object[] {
            "300",
            "1200",
            "2400",
            "9600",
            "19800",
            "38400",
            "57600",
            "74880",
            "115200"});
            this.cbbBaudRate.Location = new System.Drawing.Point(166, 63);
            this.cbbBaudRate.Name = "cbbBaudRate";
            this.cbbBaudRate.Size = new System.Drawing.Size(121, 24);
            this.cbbBaudRate.TabIndex = 17;
            this.cbbBaudRate.SelectedIndex = 8;
            // 
            // btCloseF3
            // 
            this.btCloseF3.BackColor = System.Drawing.SystemColors.ControlDark;
            this.btCloseF3.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btCloseF3.Location = new System.Drawing.Point(33, 344);
            this.btCloseF3.Name = "btCloseF3";
            this.btCloseF3.Size = new System.Drawing.Size(127, 32);
            this.btCloseF3.TabIndex = 27;
            this.btCloseF3.Text = "CLOSE";
            this.btCloseF3.UseVisualStyleBackColor = false;
            this.btCloseF3.Click += new System.EventHandler(this.BtCloseF3_Click);
            // 
            // cbbStopBit
            // 
            this.cbbStopBit.FormattingEnabled = true;
            this.cbbStopBit.Items.AddRange(new object[] {
            "One",
            "Two"});
            this.cbbStopBit.Location = new System.Drawing.Point(166, 131);
            this.cbbStopBit.Name = "cbbStopBit";
            this.cbbStopBit.Size = new System.Drawing.Size(121, 24);
            this.cbbStopBit.TabIndex = 18;
            this.cbbStopBit.Text = "One";
            // 
            // btOpenF3
            // 
            this.btOpenF3.BackColor = System.Drawing.SystemColors.ControlDark;
            this.btOpenF3.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btOpenF3.Location = new System.Drawing.Point(33, 287);
            this.btOpenF3.Name = "btOpenF3";
            this.btOpenF3.Size = new System.Drawing.Size(127, 32);
            this.btOpenF3.TabIndex = 26;
            this.btOpenF3.Text = "OPEN";
            this.btOpenF3.UseVisualStyleBackColor = false;
            this.btOpenF3.Click += new System.EventHandler(this.BtOpenF3_Click);
            // 
            // cbbParity
            // 
            this.cbbParity.FormattingEnabled = true;
            this.cbbParity.Items.AddRange(new object[] {
            "None",
            "Odd",
            "Even"});
            this.cbbParity.Location = new System.Drawing.Point(166, 165);
            this.cbbParity.Name = "cbbParity";
            this.cbbParity.Size = new System.Drawing.Size(121, 24);
            this.cbbParity.TabIndex = 19;
            this.cbbParity.Text = "None";
            // 
            // btRefreshF3
            // 
            this.btRefreshF3.BackColor = System.Drawing.SystemColors.ControlDark;
            this.btRefreshF3.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btRefreshF3.Location = new System.Drawing.Point(33, 230);
            this.btRefreshF3.Name = "btRefreshF3";
            this.btRefreshF3.Size = new System.Drawing.Size(127, 32);
            this.btRefreshF3.TabIndex = 25;
            this.btRefreshF3.Text = "REFRESH";
            this.btRefreshF3.UseVisualStyleBackColor = false;
            this.btRefreshF3.Click += new System.EventHandler(this.BtRefreshF3_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(7, 32);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(86, 17);
            this.label7.TabIndex = 20;
            this.label7.Text = "COM PORT:";
            // 
            // lbparity
            // 
            this.lbparity.AutoSize = true;
            this.lbparity.Location = new System.Drawing.Point(16, 172);
            this.lbparity.Name = "lbparity";
            this.lbparity.Size = new System.Drawing.Size(65, 17);
            this.lbparity.TabIndex = 24;
            this.lbparity.Text = "PARITY :";
            // 
            // lbDataBit
            // 
            this.lbDataBit.AutoSize = true;
            this.lbDataBit.Location = new System.Drawing.Point(11, 100);
            this.lbDataBit.Name = "lbDataBit";
            this.lbDataBit.Size = new System.Drawing.Size(70, 17);
            this.lbDataBit.TabIndex = 21;
            this.lbDataBit.Text = "DATABIT:";
            // 
            // lbStopBit
            // 
            this.lbStopBit.AutoSize = true;
            this.lbStopBit.Location = new System.Drawing.Point(6, 131);
            this.lbStopBit.Name = "lbStopBit";
            this.lbStopBit.Size = new System.Drawing.Size(75, 17);
            this.lbStopBit.TabIndex = 23;
            this.lbStopBit.Text = "STOP BIT:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 66);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(87, 17);
            this.label3.TabIndex = 22;
            this.label3.Text = "BAUDRATE:";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(62, 401);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 30;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 464);
            this.Controls.Add(this.gbSettingCom);
            this.Controls.Add(this.zedGrap);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.gbSettingCom.ResumeLayout(false);
            this.gbSettingCom.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private ZedGraph.ZedGraphControl zedGrap;
        private System.Windows.Forms.GroupBox gbSettingCom;
        private System.Windows.Forms.ComboBox cbbDataBit;
        private System.Windows.Forms.Label lbStatus;
        private System.Windows.Forms.ComboBox cbbComPort;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cbbBaudRate;
        private System.Windows.Forms.Button btCloseF3;
        private System.Windows.Forms.ComboBox cbbStopBit;
        private System.Windows.Forms.Button btOpenF3;
        private System.Windows.Forms.ComboBox cbbParity;
        private System.Windows.Forms.Button btRefreshF3;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label lbparity;
        private System.Windows.Forms.Label lbDataBit;
        private System.Windows.Forms.Label lbStopBit;
        private System.Windows.Forms.Label label3;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.Button button1;
    }
}

