/**************************************************************************//**
 * @file     myMath
 * @brief    Some basic math
 * @version  V1.5
 * @date     2019
 * @author   Dam Quang Dat UTC 
 ******************************************************************************/

#ifndef _MYMATH_H
#define _MYMATH_H

#include <stdint.h>

static double sLn[]= { 0,0, 0.69314718056, 1.09861228867, 1.38629436112, 1.60943791243, 1.79175946923, 1.945910149066,2.07944154168,2.19722457734,2.30258509299};     
double Math_Ln(double a);
double Math_IPOW(double  x,long  y);

#endif