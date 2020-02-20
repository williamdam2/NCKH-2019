#ifndef _DELAY_H
#define _DELAY_H
#include "stm32f10x.h"

#define CORE_CLOCK_72MHZ

static int usTick = 0 ;

void Delay()
{
	for(int i;i<50000000;i++);
}



void usDelay(int us)
{
	usTick = 0 ;
	TIM2->CR1 |= TIM_CR1_CEN;
	while(usTick<us);
	TIM2->CR1 &= ~TIM_CR1_CEN;
}

void msDelay(int ms)
{
	usTick = 0 ;
	TIM2->CR1 |= TIM_CR1_CEN;
	while(usTick<ms*1000);
	TIM2->CR1 &= ~TIM_CR1_CEN;
}

void TIM2_IRQHandler()
{
  usTick++;
	TIM2->SR &= ~TIM_SR_UIF;
}

#ifdef CORE_CLOCK_72MHZ

void initDelayTimer2()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 1;
	TIM2->ARR = 72;
	TIM2->CR1 |= TIM_CR1_URS;
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->EGR |= TIM_EGR_UG;
	NVIC_EnableIRQ(TIM2_IRQn);
}
	
#endif



#endif