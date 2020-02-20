
/**************************************************************************//**
 * @file     ALTFUNCT
 * @brief    alternate-function Peripheral Access Layer STM32F10x
 * @version  V1.0
 * @date     2019
 * @author   Dam Quang Dat UTC 
 ******************************************************************************/
 
#include "altfunct.h"
#define GPIO_CLOCK_ENABLE_ALT_FUNC   (RCC->APB2ENR |= (1<<0))
#define GPIO_CLOCK_ENABLE_PORTA   (RCC->APB2ENR |= (1<<2))
#define GPIO_CLOCK_ENABLE_PORTB   (RCC->APB2ENR |= (1<<3))
#define GPIO_CLOCK_ENABLE_PORTC   (RCC->APB2ENR |= (1<<4))
#define GPIO_CLOCK_ENABLE_PORTD  (RCC->APB2ENR |= (1<<5))

void initPWMPin(PWM_TYPE *PWMPinpt)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//PWM_TYPE PWMPin = *(PWMPinpt);	
		
	if((*PWMPinpt).Timer == TIM1)
		{
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN |RCC_APB2ENR_IOPBEN; 
			if((*PWMPinpt).Channel == 1)
				{
					GPIOB->CRH |= GPIO_CRH_CNF8_1|GPIO_CRH_MODE8_0|GPIO_CRH_MODE8_1;
					GPIOB->CRH &= ~(GPIO_CRH_CNF8_0);
				}
			else if((*PWMPinpt).Channel == 2)
				{
					GPIOB->CRH |= GPIO_CRH_CNF9_1|GPIO_CRH_MODE9_0|GPIO_CRH_MODE9_1;
					GPIOB->CRH &= ~(GPIO_CRH_CNF9_0);
				}
			else if((*PWMPinpt).Channel == 3)
				{
					GPIOB->CRH |= GPIO_CRH_CNF10_1|GPIO_CRH_MODE10_0|GPIO_CRH_MODE10_1;
					GPIOB->CRH &= ~(GPIO_CRH_CNF10_0);
				}
			else if((*PWMPinpt).Channel == 4)
				{
					GPIOB->CRH |= GPIO_CRH_CNF11_1|GPIO_CRH_MODE11_0|GPIO_CRH_MODE11_1;
					GPIOB->CRH &= ~(GPIO_CRH_CNF11_0);
				}
		}
		else if((*PWMPinpt).Timer == TIM2)
		{
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ;
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 
			if((*PWMPinpt).Channel == 1)
				{
					GPIOA->CRL |= GPIO_CRL_CNF0_1|GPIO_CRL_MODE0_0|GPIO_CRL_MODE0_1;
					GPIOA->CRL &= ~(GPIO_CRL_CNF0_0);
				}
			else if((*PWMPinpt).Channel == 2)
				{
					GPIOA->CRL |= GPIO_CRL_CNF1_1|GPIO_CRL_MODE1_0|GPIO_CRL_MODE1_1;
					GPIOA->CRL &= ~(GPIO_CRL_CNF1_0);
				}
			else if((*PWMPinpt).Channel == 3)
				{
					GPIOA->CRL |= GPIO_CRL_CNF2_1|GPIO_CRL_MODE2_0|GPIO_CRL_MODE2_1;
					GPIOA->CRL &= ~(GPIO_CRH_CNF10_0);
				}
			else if((*PWMPinpt).Channel == 4)
				{
					GPIOA->CRL |= GPIO_CRL_CNF3_1|GPIO_CRL_MODE3_0|GPIO_CRL_MODE3_1;
					GPIOA->CRL &= ~(GPIO_CRL_CNF3_0);
				}
		}
	else if((*PWMPinpt).Timer == TIM3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		if((*PWMPinpt).Channel==1||(*PWMPinpt).Channel==2)
			{
				RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
				if((*PWMPinpt).Channel == 1)
				{
					GPIOA->CRL |= GPIO_CRL_CNF6_1|GPIO_CRL_MODE6_0|GPIO_CRL_MODE6_1;
					GPIOA->CRL &= ~(GPIO_CRL_CNF6_0);
				}
			else if((*PWMPinpt).Channel == 2)
				{
					GPIOA->CRL |= GPIO_CRL_CNF7_1|GPIO_CRL_MODE7_0|GPIO_CRL_MODE7_1;
					GPIOA->CRL &= ~(GPIO_CRL_CNF7_0);
				}
			}
			
		if((*PWMPinpt).Channel==3||(*PWMPinpt).Channel==4)
			{
				RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
				if((*PWMPinpt).Channel == 3)
				{
					GPIOB->CRL |= GPIO_CRL_CNF0_1|GPIO_CRL_MODE0_0|GPIO_CRL_MODE0_1;
					GPIOB->CRL &= ~(GPIO_CRL_CNF0_0);
				}
			else if((*PWMPinpt).Channel == 4)
				{
					GPIOB->CRL |= GPIO_CRL_CNF1_1|GPIO_CRL_MODE1_0|GPIO_CRL_MODE1_1;
					GPIOB->CRL &= ~(GPIO_CRL_CNF1_0);
				}
			}
	}
	else if((*PWMPinpt).Timer ==TIM4)
	{
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		if((*PWMPinpt).Channel == 1)
		{
			GPIOB->CRL |= GPIO_CRL_CNF6_1|GPIO_CRL_MODE6_0|GPIO_CRL_MODE6_1;
      GPIOB->CRL &= ~(GPIO_CRL_CNF6_0);  //output alt function 50mhz
		}	
		else if((*PWMPinpt).Channel == 2)
		{
			GPIOB->CRL |= GPIO_CRL_CNF7_1|GPIO_CRL_MODE7_0|GPIO_CRL_MODE7_1;
			GPIOB->CRL &= ~(GPIO_CRL_CNF7_0);
		}	
		else if((*PWMPinpt).Channel ==3)
		{
			GPIOB->CRH |= GPIO_CRH_CNF8_1|GPIO_CRH_MODE8_0|GPIO_CRH_MODE8_1;
			GPIOB->CRH &= ~(GPIO_CRH_CNF8_0);
		}
		else if((*PWMPinpt).Channel ==4)
		{
			GPIOB->CRH |= GPIO_CRH_CNF9_1|GPIO_CRH_MODE9_0|GPIO_CRH_MODE9_1;
			GPIOB->CRH &= ~(GPIO_CRH_CNF9_0);
		}
	}	
	
	switch((*PWMPinpt).Channel)
		{
			case 1 :
				{
					(*PWMPinpt).PWMChannelAddress = (int16_t*)(&((*PWMPinpt).Timer->CCR1));
					(*PWMPinpt).Timer->CCER |= TIM_CCER_CC1E;
					(*PWMPinpt).Timer->CCMR1 |= TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1PE;
					
					break;
				}
			case 2 :
				{
					(*PWMPinpt).PWMChannelAddress = (int16_t*)(&((*PWMPinpt).Timer->CCR2));
					(*PWMPinpt).Timer->CCER |= TIM_CCER_CC2E;
					(*PWMPinpt).Timer->CCMR1 |= TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2PE;
					break;
				}
			case 3 :
				{
					(*PWMPinpt).PWMChannelAddress = (int16_t*)(&((*PWMPinpt).Timer->CCR3));
					(*PWMPinpt).Timer->CCER |= TIM_CCER_CC3E;
					(*PWMPinpt).Timer->CCMR2 |= TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3M_2|TIM_CCMR2_OC3PE;
					break;
				}
			case 4 :
				{
					(*PWMPinpt).PWMChannelAddress = (int16_t*)(&((*PWMPinpt).Timer->CCR4));
					(*PWMPinpt).Timer->CCER |= TIM_CCER_CC4E;
					(*PWMPinpt).Timer->CCMR2 |= TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4M_2|TIM_CCMR2_OC4PE;
					break;
				}
		}
	
	if((*PWMPinpt).PWMSpeed == LOW_SPEED_500)
	{
		(*PWMPinpt).Timer->PSC = 143;
		(*PWMPinpt).Timer->ARR = 1000;
	}	
	else if((*PWMPinpt).PWMSpeed == MEDIUM_SPEED_1K)
	{
		(*PWMPinpt).Timer -> PSC = 71;
		(*PWMPinpt).Timer->ARR = 1000;
	}
	else if((*PWMPinpt).PWMSpeed == HIGH_SPEED_9K)
	{
		(*PWMPinpt).Timer -> PSC = 7;
		(*PWMPinpt).Timer -> ARR =1000;
	}
	else if((*PWMPinpt).PWMSpeed == ULTRA_SPEED_36K)
	{
		(*PWMPinpt).Timer -> PSC = 1;
		(*PWMPinpt).Timer -> ARR =1000;
	}	
  
	
	(*PWMPinpt).Timer ->CR1 |= TIM_CR1_ARPE;
	(*PWMPinpt).Timer ->EGR |= TIM_EGR_UG;
  	
}

void PWMPin_Start(PWM_TYPE PWMPin)
{
	PWMPin.Timer->CR1 |= TIM_CR1_CEN;
}
void PWMPin_Stop(PWM_TYPE PWMPin);

void PWMPin_SetDuty(PWM_TYPE PWMPin,uint16_t duty0_1k)
{
	*(PWMPin.PWMChannelAddress) = duty0_1k;
	
}


// in the 72MHz
