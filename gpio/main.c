#include "stm32f10x.h"
#include "_HAL_GPIO.h"
#include "altfunct.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
#include "stdarg.h"
#include "myMath.h"
#include "delay.h"
#include "74hc595.h"
#include "lcd.h"


#define CORE_CLOCK_72MHZ


//global variable
unsigned char seg7Code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
static int adcValue = 0 ;
static bool bdv = true;
static unsigned char Numbdv,Numbchuc;
static unsigned char buffer[2]={15,170};
GPIO_TYPE leddv,ledchuc;
struct74HC595_TYPE seg74 ;
struct74HC595_TYPE o74hc;
LCD_TYPE olcd;


// function prototype
void setADC_Single();
void initUART();
static void printMsg(char *msg,...);


void out7seg(bool dv)
{
	if(dv==true)
	{
		gpio_write_gpioObject(ledchuc,LOW);
		tranfer74HC595(&Numbdv,1,seg74);
		gpio_write_gpioObject(leddv,HIGH);
	}
	else if(dv==false)
	{
		gpio_write_gpioObject(leddv,LOW);
		tranfer74HC595(&Numbchuc,1,seg74);
		gpio_write_gpioObject(ledchuc,HIGH);
	}
}
void test()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN|RCC_APB2ENR_IOPAEN;
  
	TIM3->DIER |= TIM_DIER_CC1IE;
	TIM3->CCR1 = 100;
	//TIM3->CCR2 = 700;
	TIM3->CCMR1 =0x00;
	TIM3->ARR = 0xffff;
	TIM3->PSC = 7200;
	NVIC_EnableIRQ(TIM3_IRQn);
	TIM3->EGR |= TIM_EGR_UG;
	TIM3->CR1 |= TIM_CR1_CEN;
}





int main()
{
//	int count=0;
//	char testchar;
//	Numbdv = seg7Code[1]<<1;
//	Numbchuc = seg7Code[7]<<1;
//	initDelayTimer2();
//	test();
//	
////	led.portname = PORTB;
////	led.pin = 0;
////	led.mode =OUTPUT_MODE;
////	led.mode_type = OUTPUT_GEN_PURPOSE;
////	led.speed = SPEED_50MHZ;
////	gpio_init(led);
////	gpio_write_gpioObject(led,HIGH);
//  config_gpio_interrupt(PORTC,14,FALLING_EGDE);
//	enable_gpio_interrupt(14,EXTI15_10_IRQn);
//	GPIO_TYPE builtInPin;
//	builtInPin.portname = PORTC;
//	builtInPin.pin = 13;
//	builtInPin.mode = OUTPUT_MODE;
//	builtInPin.mode_type =OUTPUT_GEN_PURPOSE;
//	builtInPin.speed = SPEED_50MHZ;
//	gpio_init(builtInPin);
//	gpio_write_gpioObject(builtInPin,HIGH);
//	
//	seg74 = init74HC595Object(PORTB,12,PORTB,14,PORTB,13);
//	
//	leddv.portname = PORTA;
//	leddv.pin = 8;
//	leddv.mode =OUTPUT_MODE;
//	leddv.mode_type = OUTPUT_GEN_PURPOSE;
//	leddv.speed = SPEED_50MHZ;
//	gpio_init(leddv);
//	gpio_write_gpioObject(leddv,LOW);
//	
//	ledchuc.portname = PORTB;
//	ledchuc.pin = 15;
//	ledchuc.mode =OUTPUT_MODE;
//	ledchuc.mode_type = OUTPUT_GEN_PURPOSE;
//	ledchuc.speed = SPEED_50MHZ;
//	gpio_init(ledchuc);
//	gpio_write_gpioObject(ledchuc,LOW);
//	
//	while(1)
//	{
//		msDelay(100);
//		count++;
//		if(count>99)
//			{
//				count = 0 ;
//			}
//		Numbchuc = seg7Code[count/10]<<1;
//			Numbdv = seg7Code[count%10]<<1;
//		
//	}
  olcd = initLCDObject(PORTB,11,PORTB,10,PORTB,1,PORTB,0,PORTA,7,PORTA,6);
	LCDInit(olcd);
	LCDGoToXY(1,0,olcd);
	LCDPutString("Hello",olcd);
	LCDGoToXY(2,1,olcd);
	LCDPutString("Plzzz",olcd); 
	while(1);
	
	
}



void initUART()
{
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		
		GPIOA->CRH |= GPIO_CRH_CNF9_1|GPIO_CRH_MODE9_0|GPIO_CRH_MODE9_1;
		GPIOA->CRH &= ~(GPIO_CRH_CNF9_0);
		
		//115200  0x271
		USART1->BRR = 0x271;
		USART1->CR1 |=USART_CR1_TE;
		USART1->CR1 |=USART_CR1_UE;
		printMsg("Hello %d ,every one ",201);
}

static void printMsg(char *msg,...)
{
	char buff[80];
	va_list args;
	va_start(args,msg);
	vsprintf(buff,msg,args);
	
	for(int i=0 ; i<strlen(buff);i++)
	{
		USART1->DR=buff[i];
		while(!(USART1->SR & USART_SR_TXE)); 
	}
}


	
void setADC_Single()
{
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN|RCC_APB2ENR_AFIOEN;
	
	GPIOA->CRL |= GPIO_CRL_CNF5_1;
	GPIOA->CRL &= ~(GPIO_CRL_CNF5_0);
	
	ADC1->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ(ADC1_2_IRQn);
	
	
	
	ADC1->SMPR2 |= ADC_SMPR2_SMP5;
	ADC1->SQR3 |= ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_2;
	ADC1->CR2 |= ADC_CR2_ADON|ADC_CR2_CONT;
	
	msDelay(1);
	ADC1->CR2 |= ADC_CR2_ADON;
	msDelay(1);
	ADC1->CR2 |= ADC_CR2_CAL;
	msDelay(2);
}



		
/******************************************************************************/
		//IRQ Handler

void ADC1_2_IRQHandler()
{
	if(ADC1->SR & ADC_SR_EOC)
	{
		adcValue = ADC1->DR ;
	}
}

void EXTI15_10_IRQHandler()
{
	clear_gpio_interrupt(14);
	gpio_toggle(PORTC,13);
}




void TIM3_IRQHandler()
{
	if(((TIM3->SR) & (TIM_SR_CC1IF))) 
	{
		//gpio_toggle_gpioObject(led);
		TIM3->CCR1 +=100;
		if(bdv==true)
		{						
			bdv = false;
			
		}
		else if(bdv==false)
		{
			bdv = true;
			
		}
		out7seg(bdv);
		TIM3->SR &= ~TIM_SR_CC1IF;
		
	}
	else if(((TIM3->SR) & (TIM_SR_CC2IF))) 
	{
		//gpio_toggle_gpioObject(led1);
		//TIM3->CCR2 +=700;
		//TIM3->SR &= ~TIM_SR_CC2IF;
	}
}




