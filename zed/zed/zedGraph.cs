using ZedGraph;
using System;

namespace zed
{
    public partial class Form1
    {
        GraphPane mPane = new GraphPane();
        PointPairList listPoint1 = new PointPairList();
        LineItem mCurve;
        
        static double time = 0;
        void grapInitial()
        {

            mPane = zedGrap.GraphPane;
            mPane.Title.Text = "Đồ thị gì đó";
            mPane.XAxis.Title.Text = "Time";
            mPane.YAxis.Title.Text = "Temp";
            mCurve = mPane.AddCurve("analog", listPoint1, System.Drawing.Color.Blue, SymbolType.None);

        }
        void getTemp(bool info,double temp)
        {
            if(info)
            {
                drawGraph(temp, time);
            }
            time += 0.1;
        }

        void drawGraph(double temp,double time)
        {
            PointPair pointPair = new PointPair(time, temp);
            listPoint1.Add(pointPair);
            lbDataBit.Text = temp.ToString();
            lbStopBit.Text = time.ToString();
           
            mPane.XAxis.Scale.Max = time;
            
            zedGrap.AxisChange();

            zedGrap.Refresh();
            
        }
        void test()
        {
            time = 0;
            serialPort.Close();
            lbStatus.Text = "OFF";
            listPoint1.Clear();
            zedGrap.Refresh();
        }


        
    }
}