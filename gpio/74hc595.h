/**************************************************************************//**
 * @file     74HC595 
 * @brief    work with 75hc595 ic
 * @version  V1.1
 * @date     2020
 * @author   Dam Quang Dat UTC 
 ******************************************************************************/
#ifndef _74HC595_H
#define _74HC595_H

#include "_HAL_GPIO.h"

typedef struct
{
	GPIO_TYPE DSPin;
	GPIO_TYPE SHPin;
	GPIO_TYPE STPin;
}struct74HC595_TYPE;


struct74HC595_TYPE init74HC595Object(GPIO_TypeDef* portNameDS,uint16_t pinNumberDS,GPIO_TypeDef* portNameSH,uint16_t pinNumberSH,GPIO_TypeDef* portNameST,uint16_t pinNumberST);
void tranfer74HC595(unsigned char *buffer , unsigned char l,struct74HC595_TYPE o74HC595);




struct74HC595_TYPE init74HC595Object(GPIO_TypeDef* portNameDS,uint16_t pinNumberDS,GPIO_TypeDef* portNameSH,uint16_t pinNumberSH,GPIO_TypeDef* portNameST,uint16_t pinNumberST)
{
	struct74HC595_TYPE o74HC595;
	
	GPIO_TYPE dsPin;
	dsPin.mode = OUTPUT_MODE;
	dsPin.mode_type = OUTPUT_GEN_PURPOSE;
	dsPin.speed = SPEED_50MHZ;
	dsPin.pin=pinNumberDS;
	dsPin.portname = portNameDS;
	gpio_init(dsPin);
	gpio_write_gpioObject(dsPin,0);
	
	GPIO_TYPE stPin;
	stPin.mode = OUTPUT_MODE;
	stPin.mode_type = OUTPUT_GEN_PURPOSE;
	stPin.speed = SPEED_50MHZ;
	stPin.pin=pinNumberST;
	stPin.portname = portNameST;
	gpio_init(stPin);
	gpio_write_gpioObject(stPin,1);
	
	GPIO_TYPE shPin;
	shPin.mode = OUTPUT_MODE;
	shPin.mode_type = OUTPUT_GEN_PURPOSE;
	shPin.speed = SPEED_50MHZ;
	shPin.pin=pinNumberSH;
	shPin.portname = portNameSH;
	gpio_init(shPin);
	gpio_write_gpioObject(shPin,1);
	
	o74HC595.DSPin = dsPin;
	o74HC595.SHPin = shPin;
	o74HC595.STPin = stPin;
	
	return o74HC595;
	
}

void tranfer74HC595(unsigned char *buffer , unsigned char l,struct74HC595_TYPE o74HC595)
{
	unsigned char temp;
	_Bool k =0;
	for(int j=0;j<l;j++)
	{
		temp = (*(buffer+l-j-1));// truyen  byte cao nhat truoc
		for(int i=0;i<8;i++)
		{
			k = temp & (0x80>>i);
			gpio_write_gpioObject(o74HC595.DSPin,k);
			gpio_toggle_gpioObject(o74HC595.SHPin);
			gpio_toggle_gpioObject(o74HC595.SHPin);
		}
		}
	// chot du lieu
		
		gpio_toggle_gpioObject(o74HC595.STPin);
		gpio_toggle_gpioObject(o74HC595.STPin);
	}



#endif