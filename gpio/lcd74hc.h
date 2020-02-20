/**************************************************************************//**
 * @file     lcd74hc
 * @brief    Using 75hc595 to control LCD16x2
 * @version  V1.0
 * @date     2020
 * @author   Dam Quang Dat UTC 
 ******************************************************************************/
#ifndef _LCD74HC_H
#define _LCD74HC_H

#define CORE_CLOCK_72MHZ
#include "delay.h"
#include "74hc595.h"

static unsigned char outByte=0x00;

typedef struct
{
	struct74HC595_TYPE o74hc595;
	unsigned char lcdD4BitNumb_0to7;
	unsigned char lcdD5BitNumb_0to7;
	unsigned char lcdD6BitNumb_0to7;
	unsigned char lcdD7BitNumb_0to7;
	unsigned char lcdRSBitNumb_0to7;
	unsigned char lcdENBitNumb_0to7;
}lcd74hc_TYPE;

void setBit(unsigned char bitNumber ,unsigned char* targetByte);
void resetBit(unsigned char bitNumber, unsigned char* targetByte);
void LCD_Enable(lcd74hc_TYPE olcd74hc );
void LCD_Send4Bit(unsigned char Data,lcd74hc_TYPE olcd74hc );
void LCD_SendCommand(unsigned char command,lcd74hc_TYPE olcd74hc);
void LCD_Clear(lcd74hc_TYPE olcd75hc);
void LCD_Init(lcd74hc_TYPE olcd7);
void LCD_Gotoxy(unsigned char x, unsigned char y,lcd74hc_TYPE olcd74hc);
void LCD_PutChar(unsigned char Data,lcd74hc_TYPE olcd74hc);
void LCD_PutString(char *s,lcd74hc_TYPE olcd74hc);


void resetBit(unsigned char bitNumber, unsigned char* targetByte)
{
	*targetByte &= ~(1<<bitNumber);
}

void setBit(unsigned char bitNumber ,unsigned char* targetByte)
{
	*targetByte |= 1<<bitNumber;
}

void LCD_Enable(lcd74hc_TYPE olcd74hc)
{
//	 LCD_EN =1;
//   delay_us(3);
//   LCD_EN =0;
//   delay_us(50); 
	setBit(olcd74hc.lcdENBitNumb_0to7,&outByte);
	tranfer74HC595(&outByte,1,olcd74hc.o74hc595);
	usDelay(3);
	setBit(olcd74hc.lcdENBitNumb_0to7,&outByte);
	tranfer74HC595(&outByte,1,olcd74hc.o74hc595);
	usDelay(50);
}

void LCD_Send4Bit(unsigned char Data,lcd74hc_TYPE olcd74hc ){
//        LCD_D4=Data & 0x01;
//        LCD_D5=(Data>>1)&1;
//        LCD_D6=(Data>>2)&1;
//        LCD_D7=(Data>>3)&1;
	if(Data & 0x01)
	{
		setBit(olcd74hc.lcdD4BitNumb_0to7,&outByte);
	}
	else
	{
		resetBit(olcd74hc.lcdD4BitNumb_0to7,&outByte);
	}
	//************* D4
	
	if((Data>>1)&0x01)
	{
		setBit(olcd74hc.lcdD5BitNumb_0to7,&outByte);
	}
	else
	{
		resetBit(olcd74hc.lcdD5BitNumb_0to7,&outByte);
	}
	//************* D5
	
	if((Data>>2)&0x01)
	{
		setBit(olcd74hc.lcdD6BitNumb_0to7,&outByte);
	}
	else
	{
		resetBit(olcd74hc.lcdD6BitNumb_0to7,&outByte);
	}
	//************* D6
	
	if((Data>>3)&0x01)
	{
		setBit(olcd74hc.lcdD7BitNumb_0to7,&outByte);
	}
	else
	{
		resetBit(olcd74hc.lcdD7BitNumb_0to7,&outByte);
	}
	//************* D7
	
	tranfer74HC595(&outByte,1,olcd74hc.o74hc595);
	
}

void LCD_SendCommand(unsigned char command,lcd74hc_TYPE olcd74hc){
//	      LCD_Send4Bit(command >>4);/* Gui 4 bit cao */
//        LCD_Enable();
//        LCD_Send4Bit(command); /* Gui 4 bit thap*/
//        LCD_Enable();
        LCD_Send4Bit((command >>4),olcd74hc);/* Gui 4 bit cao */
        LCD_Enable(olcd74hc);
        LCD_Send4Bit(command,olcd74hc); /* Gui 4 bit thap*/
        LCD_Enable(olcd74hc);
	      usDelay(10);
}

void LCD_Clear(lcd74hc_TYPE olcd75hc){// Ham Xoa Man Hinh LCD
//        LCD_SendCommand(0x01); 
//        delay_us(10);
	      LCD_SendCommand(0x01,olcd75hc);
	      usDelay(10);
}

void LCD_Init(lcd74hc_TYPE olcd74hc){
//        LCD_Send4Bit(0x00);	  //turn on LCD
//        delay_ms(20);
//        LCD_RS=0;
//        LCD_RW=0;
//        LCD_Send4Bit(0x03);	  //function setting
//        LCD_Enable();
//        delay_ms(5);
//        LCD_Enable();
//        delay_us(100);
//        LCD_Enable();
//        LCD_Send4Bit(0x02);	  //di chuyen con tro ve dau man hnh
//        LCD_Enable();
//        LCD_SendCommand( 0x28 ); //lua chon che do 4 bit
//        LCD_SendCommand( 0x0c);  // bat hien thi va tat con tro di
//        LCD_SendCommand( 0x06 );
//        LCD_SendCommand(0x01);
	initDelayTimer2();
	LCD_Send4Bit(0x00,olcd74hc);
	msDelay(20);
	resetBit(olcd74hc.lcdRSBitNumb_0to7,&outByte);
	tranfer74HC595(&outByte,1,olcd74hc.o74hc595);
	usDelay(10);
	LCD_Send4Bit(0x03,olcd74hc);
	LCD_Enable(olcd74hc);
	msDelay(5);
	LCD_Enable(olcd74hc);
	usDelay(100);
	LCD_Enable(olcd74hc);
	LCD_Send4Bit(0x02,olcd74hc);
	LCD_Enable(olcd74hc);
	LCD_SendCommand(0x28,olcd74hc);
	LCD_SendCommand(0x0c,olcd74hc);
	LCD_SendCommand(0x06,olcd74hc);
	LCD_SendCommand(0x01,olcd74hc);
	
}

void LCD_Gotoxy(unsigned char x, unsigned char y,lcd74hc_TYPE olcd74hc){
//        unsigned char address;
//        if(!y)address=(0x80+x);
//        else address=(0xc0+x);
//        delay_us(1000);
//        LCD_SendCommand(address);
//        delay_us(50);
	unsigned char address;
	if(!y)
	{
		address = 0x80+1;
	}
	else
	{
		address = 0xc0+x;
	}
	usDelay(1000);
	LCD_SendCommand(address,olcd74hc);
	usDelay(50);
}

void LCD_PutChar(unsigned char Data,lcd74hc_TYPE olcd74hc){
//        LCD_RS=1;
//        LCD_SendCommand(Data);
//        LCD_RS=0 ;
	setBit(olcd74hc.lcdRSBitNumb_0to7,&outByte);
	tranfer74HC595(&outByte,1,olcd74hc.o74hc595);
	LCD_SendCommand(Data,olcd74hc);
	resetBit(olcd74hc.lcdRSBitNumb_0to7,&outByte);
	tranfer74HC595(&outByte,1,olcd74hc.o74hc595);
}

void LCD_PutString(char *s,lcd74hc_TYPE olcd74hc){
//        while (*s){
//                LCD_PutChar(*s);
//                s++;
//        }
	while(*s)
	{
		LCD_PutChar(*s,olcd74hc);
		s++;
	}
}




#endif