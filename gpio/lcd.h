/**************************************************************************//**
 * @file     lcd
 * @brief    Normal lib for LCD 4 bit MODE
 * @version  V1.0
 * @date     2020
 * @author   Dam Quang Dat UTC 
 ******************************************************************************/

#ifndef _LCD_H
#define _LCD_H
#include "delay.h"
#include "_HAL_GPIO.h"

typedef struct 
{
	GPIO_TYPE RS_Pin;
	GPIO_TYPE EN_Pin;
	GPIO_TYPE D4_Pin;
	GPIO_TYPE D5_Pin;
	GPIO_TYPE D6_Pin;
	GPIO_TYPE D7_Pin;
}LCD_TYPE;

LCD_TYPE initLCDObject(GPIO_TypeDef* RSPort,unsigned char RSpin,GPIO_TypeDef* ENPort,unsigned char ENpin,GPIO_TypeDef* D4Port,unsigned char D4pin,GPIO_TypeDef* D5Port,unsigned char D5pin,GPIO_TypeDef* D6Port,unsigned char D6pin,GPIO_TypeDef* D7Port,unsigned char D7pin)
{
	LCD_TYPE olcd;
	GPIO_TYPE temp;
	temp.mode = OUTPUT_MODE;
	temp.mode_type = OUTPUT_GEN_PURPOSE;
	temp.speed = SPEED_50MHZ;
  // RS
	temp.portname = RSPort;
	temp.pin = RSpin;
	gpio_init(temp);
	olcd.RS_Pin = temp;
	
	// EN
	temp.portname = ENPort;
	temp.pin = ENpin;
	gpio_init(temp);
	olcd.EN_Pin = temp;
	
	// D4
	temp.portname = D4Port;
	temp.pin = D4pin;
	gpio_init(temp);
	olcd.D4_Pin = temp;
	
	// D5
	temp.portname = D5Port;
	temp.pin = D5pin;
	gpio_init(temp);
	olcd.D5_Pin = temp;
	
	// D6
	temp.portname = D6Port;
	temp.pin = D6pin;
	gpio_init(temp);
	olcd.D6_Pin = temp;
	
	// D7
	temp.portname = D7Port;
	temp.pin = D7pin;
	gpio_init(temp);
	olcd.D7_Pin = temp;	
	gpio_write_gpioObject(olcd.EN_Pin,LOW);
	gpio_write_gpioObject(olcd.RS_Pin,LOW);
	gpio_write_gpioObject(olcd.D4_Pin,LOW);
	gpio_write_gpioObject(olcd.D5_Pin,LOW);
	gpio_write_gpioObject(olcd.D6_Pin,LOW);
	gpio_write_gpioObject(olcd.D7_Pin,LOW);
	
	return olcd;
}	

void LCDENABLE(LCD_TYPE olcd)
{
	gpio_write_gpioObject(olcd.EN_Pin,HIGH);
	msDelay(1);
	gpio_write_gpioObject(olcd.EN_Pin,LOW);
	msDelay(1);
}

void LCDSend4Bit(unsigned char Data , LCD_TYPE olcd)
{
//	uint32_t D4data=0,D5data=0,D6
//	if((Data&0x01))
//	{
//		
//	}
	gpio_write_gpioObject(olcd.D4_Pin,(Data&0x01));
	gpio_write_gpioObject(olcd.D5_Pin,((Data>>1)&0x01));
	gpio_write_gpioObject(olcd.D6_Pin,((Data>>2)&0x01));
	gpio_write_gpioObject(olcd.D7_Pin,((Data>>3)&0x01));
}

void LCDSendCommand(unsigned char command,LCD_TYPE olcd)
{
	LCDSend4Bit(command>>4,olcd);
	LCDENABLE(olcd);
	LCDSend4Bit(command,olcd);
	LCDENABLE(olcd);
	
}

void LCDClear(LCD_TYPE olcd)
{
	LCDSendCommand(0x01,olcd);
	msDelay(1);
}

void LCDInit(LCD_TYPE olcd)
{
	initDelayTimer2();
	LCDSend4Bit(0x00,olcd);
	gpio_write_gpioObject(olcd.RS_Pin,LOW);
  LCDSend4Bit(0x03,olcd);
	LCDENABLE(olcd);
	LCDENABLE(olcd);
	LCDENABLE(olcd);
	LCDSend4Bit(0x02,olcd);
	LCDENABLE(olcd);
	LCDSendCommand(0x28,olcd);
	LCDSendCommand(0x0c,olcd);
	LCDSendCommand(0x06,olcd);
	LCDSendCommand(0x01,olcd);
	
}

void LCDGoToXY(unsigned char x, unsigned char y , LCD_TYPE olcd)
{
	unsigned char address;
	if(y==0)
	{
	address=0x80;
	}
	else if(y==1)
	{
	address=0xc0;
	}
	
	address+=x;
	LCDSendCommand(address,olcd);
}

void LCDPutChar(unsigned char Data,LCD_TYPE olcd)
{
	gpio_write_gpioObject(olcd.RS_Pin,HIGH);
	LCDSendCommand(Data,olcd);
	gpio_write_gpioObject(olcd.RS_Pin,LOW);
}

void LCDPutString(char* s,LCD_TYPE olcd)
{
	while(*s)
	{
		LCDPutChar(*s,olcd);
		s++;
	}
}

#endif

