/**************************************************************************//**
 * @file     ALTFUNCT
 * @brief    alternate-function Peripheral Access Layer STM32F10x
 * @version  V1.0
 * @date     2019
 * @author   Dam Quang Dat UTC 
 ******************************************************************************/


#ifndef _ALTFUNCT_H
#define _ALTFUNCT_H

#include "stm32f10x.h"

typedef enum 
{
	LOW_SPEED_500,
	MEDIUM_SPEED_1K,
	HIGH_SPEED_9K,
	ULTRA_SPEED_36K
}PWM_SPEED;

typedef struct
{
	TIM_TypeDef *Timer;
	uint16_t Channel ;
	int16_t *PWMChannelAddress;
	PWM_SPEED PWMSpeed;
}PWM_TYPE;

void initPWMPin(PWM_TYPE *PWMPinpt);
void PWMPin_Start(PWM_TYPE PWMPin);
void PWMPin_Stop(PWM_TYPE PWMPin);
void PWMPin_SetDuty(PWM_TYPE PWMPin,uint16_t duty0_1k);


#endif