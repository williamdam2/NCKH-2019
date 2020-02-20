using System;

namespace zed
{
    public partial class Form1
    {
        double temp = 0;
        void encrypt(string substring)
        {
            if (substring.StartsWith("TA"))
            {
                //lbStopBit.Text = "OK";
                substring = substring.Substring(2);
                
                try
                {
                    temp = Convert.ToDouble(substring);
                    getTemp(true, temp);
                    //lbDataBit.Text = temp.ToString();
                }
                catch
                {
                    getTemp(false, 0);
                }
            }

        }
    }
}