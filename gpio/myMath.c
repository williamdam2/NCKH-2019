/**************************************************************************//**
 * @file     myMath
 * @brief    Some basic math
 * @version  V1.5
 * @date     2019
 * @author   Dam Quang Dat UTC 
 ******************************************************************************/
#include "myMath.h"
static double calSLn(double a);
static void PhanTichSo(double A , double* a, int16_t* b);  

static void PhanTichSo(double A , double* a, int16_t* b)
{
	int i = 0;
 
	if(A>10)
	{
			while(A>10)
			{
					A = A / 10;
					i++;
			}
	}
	else if(A<1)
	{
			while(A<1)
			{
					A = A * 10;
					i--;
			}
	}
	
	if (A >= 1 && A <= 10)
	{
			*b = i;
			*a = A;
	}
}

double Math_Ln(double A)
{
		double Ln=0;
		int16_t b=0;
		double a=0;
		uint16_t k = 1;
		PhanTichSo(A,&a,&b);
		
		k = (uint16_t)a;
		a = a / k;
		Ln = sLn[k] + sLn[10] * b;
		Ln = Ln + calSLn(a);
		return Ln;
}

static double calSLn(double a)
{
		double cal=0;
		double y = a - 1;
		y = y / (a + 1);
		for(int i=0;i<50;i++)
		{
				cal += (1 / (2 * i + 1)) * Math_IPOW(y, 2 * i);
		}
		cal = cal * 2 * y;

		return cal;
}

double Math_IPOW(double  x,long  y)
{
		double pow = x;
		
		if(y==0)
		{
				return 1;
		}
		 else
		{
				for (int i = 0; i < y - 1; i++)
				{
						pow = pow * x;
				}
				return pow;
		}
		
}
