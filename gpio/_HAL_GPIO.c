/**************************************************************************//**
 * @file     _HAL_GPIO
 * @brief    GPIO Peripheral Access Layer for STM32F10x
 * @version  V1.2
 * @date     2019
 * @author   Dam Quang Dat UTC 
 ******************************************************************************/

#include "_HAL_GPIO.h"
#include "stdint.h"


/*  every pin in the high and low */
//  position of the first bit of 4 bit CONTROL HIGH REGISTERS
uint32_t PINPOS[16] = {
	(0x00),
	(0x04),
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C),
	(0x00), //pin 8
	(0x04), //pin 9
	(0x08),
	(0x0C),
	(0x10),
	(0x14),
	(0x18),
	(0x1C),
};

static void config_pin(GPIO_TypeDef *port_name , uint32_t pinNumber ,uint32_t modeType )
{
   if(pinNumber>=8)  // CONTROL HIGH REGISTERS
   {
   	   switch(modeType)
	   {
	       // OUTPUT & INPUT MODE
		   case OUTPUT_GEN_PURPOSE | INPUT_ANALOG :
			 {
		      port_name->CRH &=~(  (1<<CNF_POS_BIT1) | (1<<CNF_POS_BIT2));
		    break;
			 }

			case OUTPUT_OD |  INPUT_FLOATING :
			{
			  port_name->CRH &=~((1<<CNF_POS_BIT2));
			  port_name->CRH |=((1<<CNF_POS_BIT1));
			break;
			}

			case OUTPUT_ALT_FUNCTION |INPUT_PU_PD:
			{
			  port_name->CRH |=OUTPUT_ALT_FUNCTION<<(CNF_POS_BIT1);
			break;
			}
			
			case OUTPUT_ALT_FUNCTION_OD:
			{
			  port_name ->CRH |=OUTPUT_ALT_FUNCTION_OD<<(CNF_POS_BIT1);
			break;
			}


	   }// end switch
   }
   else
   {
      switch(modeType)
	   {
      case OUTPUT_GEN_PURPOSE | INPUT_ANALOG :
			{
		      port_name->CRL &=~(  (1<<CNF_POS_BIT1) | (1<<CNF_POS_BIT2));
		    break;
			}

			case OUTPUT_OD :
			{
			  port_name->CRL &=~((1<<CNF_POS_BIT2));
			  port_name->CRL |=((1<<CNF_POS_BIT1));
			break;
			}

			case OUTPUT_ALT_FUNCTION |INPUT_PU_PD:
			{
			  port_name->CRL |=OUTPUT_ALT_FUNCTION<<(CNF_POS_BIT1);
			break;
			}
			
			case OUTPUT_ALT_FUNCTION_OD:
			{
			  port_name ->CRL |=OUTPUT_ALT_FUNCTION_OD<<(CNF_POS_BIT1);
			break;
			}

		}
   }

}


static void config_pin_speed(GPIO_TypeDef *port_name , uint32_t pinNumber , uint32_t pinSpeed , uint32_t mode)
{
	if(pinNumber>=8)
	{
		if(mode == INPUT_MODE)  // set CONTROL HIGH REGISTERS  
		{
			port_name -> CRH &=~(1<<(PINPOS[pinNumber] )| 1<<(PINPOS[pinNumber]));

		}
		else
		{
			port_name -> CRH |= (pinSpeed<<(PINPOS[pinNumber]));
		}

	}
	else 
	{
		if(mode == INPUT_MODE)  // set CONTROL LOW REGISTERS  
		{
			port_name -> CRL &=~(1<<(PINPOS[pinNumber]) | 1<<(PINPOS[pinNumber]));

		}
		else
		{
			port_name -> CRL |= (pinSpeed<<(PINPOS[pinNumber]));
		}
	}
}

// GPIO FUNCTION
void gpio_write(GPIO_TypeDef *port_name , uint32_t pinNumber , uint32_t state)
{
    if(state)
	{
	    port_name->BSRR = (1<<pinNumber); // set is HIGH
	}
	else
	{
	    port_name->BSRR = (1<<(pinNumber+16)); // RESET THE PIN
	}
}

void gpio_toggle(GPIO_TypeDef *port_name , uint32_t pinNumber)
{
	port_name->ODR ^=(1<<pinNumber); 
}

void gpio_write_gpioObject(GPIO_TYPE gpioObject , uint32_t state)
{
	 if(state)
	{
	    gpioObject.portname->BSRR = (1<<gpioObject.pin); // set is HIGH
	}
	else
	{
	    gpioObject.portname->BSRR = (1<<(gpioObject.pin + 16)); // RESET THE PIN
	}
}
void gpio_toggle_gpioObject(GPIO_TYPE gpioObject )
{
	gpioObject.portname ->ODR ^=(1<<gpioObject.pin); 
}

void gpio_init(GPIO_TYPE gpio_type)
{
	if(gpio_type.portname == PORTA|gpio_type.portname == GPIOA )
	{
		GPIO_CLOCK_ENABLE_PORTA;
	}
	if(gpio_type.portname == PORTB|gpio_type.portname == GPIOB )
	{
		GPIO_CLOCK_ENABLE_PORTB;
	}
	if(gpio_type.portname == PORTC|gpio_type.portname == GPIOC )
	{
		GPIO_CLOCK_ENABLE_PORTC;
	}
	if(gpio_type.portname == PORTD|gpio_type.portname == GPIOD )
	{
		GPIO_CLOCK_ENABLE_PORTD;
	}
	config_pin(gpio_type.portname,gpio_type.pin,gpio_type.mode_type);
	config_pin_speed(gpio_type.portname,gpio_type.pin,gpio_type.speed,gpio_type.mode);
	
}

char gpio_read(GPIO_TypeDef *port_name , uint32_t pinNumber )
{
	char state = (port_name->IDR)&(1<<pinNumber);
	if(state==0)
	{
		return 0 ;
	}
	else if(state != 0 )
	{
		return 1;
	}
}
//***********************************
// gpio Interrupt Funtion

void config_gpio_interrupt(GPIO_TypeDef *port_name , uint32_t pinNumber , egdeSelection egde)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	if(port_name == PORTA | port_name == GPIOA)
	{
		switch(pinNumber)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PA;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PA;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PA;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PA;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PA;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PA;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PA;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PA ;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PA;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PA;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PA;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PA;
				break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PA;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PA;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PA;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PA;
			}						
		} // end of PORTA switch	
	} 
	//END OF PORTA IF
	
	if(port_name == PORTB | port_name == GPIOB)
	{
		
		switch(pinNumber)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PB;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PB;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PB;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PB;
				break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PB;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PB;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PB;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PB ;
				break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PB;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PB;
				break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PB;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PB;
				break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PB;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PB;
				break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PB;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PB;
				break;
			}						
		} // end of PORTB switch	
	}
	
	//END OF PORTB IF
	
	if(port_name == PORTC | port_name == GPIOC)
	{
		switch(pinNumber)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PC;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PC;
				break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PC;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PC;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PC;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PC;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PC;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PC ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PC;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PC;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PC;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PC;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PC;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PC;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PC;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PC;break;
			}						
		} // end of PORTC switch	
	}
	
	//END OF PORTC IF
	
	if(port_name == PORTD| port_name == GPIOD)
	{
		switch(pinNumber)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PD;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PD;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PD;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PD;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PD;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PD;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PD;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PD ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PD;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PD;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PD;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PD;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PD;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PD;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PD;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PD;break;
			}						
		} // end of PORTD switch	
	}
	
	//END OF PORTD IF
	
	if(port_name == PORTE | port_name == GPIOE)
	{
		switch(pinNumber)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PE;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PE;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PE;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PE;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PE;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PE;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PE;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PE ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PE;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PE;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PE;break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PE;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PE;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PE;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PE;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PE;break;
			}						
		} // end of PORTE switch	
	}
	
	//END OF PORTE IF
	
	if(port_name == PORTF | port_name == GPIOF)
	{
		switch(pinNumber)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PF;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PF;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PF;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PF;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PF;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PF;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PF;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PF ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PF;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PF;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PF;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PF;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PF;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PF;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PF;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PF;break;
			}						
		} // end of PORTE switch	
	}
	
	//END OF PORTF IF
	
	if(port_name == PORTG | port_name == GPIOG)
	{
		switch(pinNumber)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PG;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PG;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PG;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PG;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PG;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PG;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PG;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PG ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PG;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PG;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PG;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PG;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PG;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PG;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PG;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PG;break;
			}						
		} // end of PORTG switch	
   }
	
	// END OF PORTG IF
	 
	 //CONFIGURATION EGDE OF INTERRUPT TRIGGER
	 if(egde==RISING_EGDE)
	 {
		 EXTI->RTSR |= 1<<pinNumber;
	 }
	 if(egde==FALLING_EGDE)
	 {
		 EXTI->FTSR |= 1<<pinNumber;
	 }
	 if(egde==RISING_FALLING_EGDE)
	 {
		 EXTI->RTSR |= 1<<pinNumber;
		 EXTI->FTSR |= 1<<pinNumber;
	 }
	 //END OF EGDE CONFIGURATION
	 
}

/// END OF INTERRUPT CONFIG

void enable_gpio_interrupt(uint32_t pinNumber , IRQn_Type irqNumber)
{
	// set the INTERRUPT MASK REGISTER 
	EXTI->IMR |=1<<pinNumber ;
	// ENABLE NVIC line in ARM core
	NVIC_EnableIRQ(irqNumber);
}

void clear_gpio_interrupt(uint32_t pinNumber)
{
	// clear by set the bit in PENDING REGISTER 
	EXTI->PR |= 1<<pinNumber;
}

void config_gpioObject_interrupt(GPIO_TYPE gpioObject , egdeSelection egde)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	if(gpioObject.portname == PORTA | gpioObject.portname == GPIOA)
	{
		switch(gpioObject.pin)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PA;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PA;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PA;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PA;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PA;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PA;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PA;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PA ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PA;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PA;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PA;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PA;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PA;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PA;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PA;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PA;break;
			}						
		} // end of PORTA switch	
	} 
	//END OF PORTA IF
	
	if(gpioObject.portname == PORTB | gpioObject.portname == GPIOB)
	{
		
		switch(gpioObject.pin)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PB;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PB;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PB;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PB;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PB;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PB;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PB;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PB ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PB;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PB;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PB;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PB;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PB;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PB;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PB;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PB;break;
			}						
		} // end of PORTB switch	
	}
	
	//END OF PORTB IF
	
	if(gpioObject.portname == PORTC | gpioObject.portname == GPIOC)
	{
		switch(gpioObject.pin)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PC;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PC;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PC;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PC;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PC;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PC;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PC;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PC ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PC;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PC;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PC;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PC;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PC;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PC;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PC;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PC;break;
			}						
		} // end of PORTC switch	
	}
	
	//END OF PORTC IF
	
	if(gpioObject.portname == PORTD| gpioObject.portname == GPIOD)
	{
		switch(gpioObject.pin)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PD;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PD;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PD;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PD;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PD;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PD;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PD;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PD ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PD;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PD;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PD;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PD;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PD;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PD;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PD;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PD;break;
			}						
		} // end of PORTD switch	
	}
	
	//END OF PORTD IF
	
	if(gpioObject.portname == PORTE | gpioObject.portname== GPIOE)
	{
		switch(gpioObject.pin)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PE;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PE;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PE;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PE;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PE;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PE;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PE;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PE ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PE;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PE;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PE;break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PE;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PE;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PE;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PE;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PE;break;
			}						
		} // end of PORTE switch	
	}
	
	//END OF PORTE IF
	
	if(gpioObject.portname == PORTF | gpioObject.portname == GPIOF)
	{
		switch(gpioObject.pin)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PF;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PF;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PF;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PF;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PF;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PF;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PF;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PF ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PF;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PF;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PF;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PF;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PF;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PF;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PF;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PF;break;
			}						
		} // end of PORTE switch	
	}
	
	//END OF PORTF IF
	
	if(gpioObject.portname == PORTG | gpioObject.portname == GPIOG)
	{
		switch(gpioObject.pin)
		{
			case 0 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PG;
				break;
			}
			case 1:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PG;break;
			}
			case 2 :
			{
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PG;
				break;
			}
			case 3:
			{
				 AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PG;break;
			}
			case 4 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PG;
				break;
			}
			case 5:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PG;
				break;
			}
			case 6 :
			{
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PG;
				break;
			}
			case 7:
			{
				 AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PG ;break;
			}
			case 8 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PG;
				break;
			}
			case 9:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PG;break;
			}
			case 10 :
			{
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PG;
				break;
			}
			case 11:
			{
				 AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PG;break;
			}
			case 12 :
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PG;
				break;
			}
			case 13:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PG;break;
			}
			case 14:
			{
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PG;
				break;
			}
			case 15:
			{
				 AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PG;break;
			}						
		} // end of PORTG switch	
   }
	
	// END OF PORTG IF
	 
	 //CONFIGURATION EGDE OF INTERRUPT TRIGGER
	 if(egde==RISING_EGDE)
	 {
		 EXTI->RTSR |= 1<<gpioObject.pin;
	 }
	 if(egde==FALLING_EGDE)
	 {
		 EXTI->FTSR |= 1<<gpioObject.pin;
	 }
	 if(egde==RISING_FALLING_EGDE)
	 {
		 EXTI->RTSR |= 1<<gpioObject.pin;
		 EXTI->FTSR |= 1<<gpioObject.pin;
	 }
	 //END OF EGDE CONFIGURATION
	 
}

void enable_gpioObject_interrupt(GPIO_TYPE gpioObject , IRQn_Type irqNumber)
{
	
	// set the INTERRUPT MASK REGISTER 
	EXTI->IMR |=1<<gpioObject.pin ;
	// ENABLE NVIC line in ARM core
	NVIC_EnableIRQ(irqNumber);
}

void clear_gpioObject_interrupt(GPIO_TYPE gpioObject)
{
	// clear by set the bit in PENDING REGISTER 
	EXTI->PR |= 1<<gpioObject.pin;
}