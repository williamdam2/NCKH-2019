/**************************************************************************//**
 * @file     _HAL_GPIO
 * @brief    GPIO Peripheral Access Layer for STM32F10x
 * @version  V1.2
 * @date     2019
 * @author   Dam Quang Dat UTC 
 ******************************************************************************/


 #ifndef _HAL_GPIO_H
#define _HAL_GPIO_H

#include "stm32f10x.h"

#define PORTA GPIOA
#define PORTB GPIOB
#define PORTC GPIOC
#define PORTD GPIOD
#define PORTE GPIOE
#define PORTF GPIOF
#define PORTG GPIOG

#define HIGH (uint32_t)1
#define LOW  (uint32_t)0

//PIN MODE
#define OUTPUT_MODE  ((uint32_t)0x00)
#define INPUT_MODE   ((uint32_t)0x01)

// INPUT TYPE

#define INPUT_ANALOG   ((uint32_t)0x00)
#define INPUT_FLOATING ((uint32_t)0x01)  // defualt at reset
#define INPUT_PU_PD   ((uint32_t)0x02)//input pullup or pulldown

// output type

#define OUTPUT_GEN_PURPOSE   ((uint32_t)0x00) //
#define OUTPUT_OD   ((uint32_t)0x01) //
#define OUTPUT_ALT_FUNCTION   ((uint32_t)0x02) //
#define OUTPUT_ALT_FUNCTION_OD   ((uint32_t)0x03) //

// Enable clock 
#define GPIO_CLOCK_ENABLE_ALT_FUNC   (RCC->APB2ENR |= (1<<0))
#define GPIO_CLOCK_ENABLE_PORTA   (RCC->APB2ENR |= (1<<2))
#define GPIO_CLOCK_ENABLE_PORTB   (RCC->APB2ENR |= (1<<3))
#define GPIO_CLOCK_ENABLE_PORTC   (RCC->APB2ENR |= (1<<4))
#define GPIO_CLOCK_ENABLE_PORTD  (RCC->APB2ENR |= (1<<5))
//#define GPIO_CLOCK_ENABLE_PORTE (RCC->APB2ENR |= (1<<6))

// PIN speed 
#define SPEED_2MHZ ((uint32_t)0x02)
#define SPEED_10MHZ ((uint32_t)0x01)
#define SPEED_50MHZ ((uint32_t)0x03)


// HIGH bit position for CRH register CNFYG and MODE
#define CNF_POS_BIT1 (PINPOS[pinNumber]+2)
#define CNF_POS_BIT2 (PINPOS[pinNumber]+3)

// Configuration Struction
typedef struct 
{
	GPIO_TypeDef *portname;

	uint32_t pin;
	uint32_t mode;
	uint32_t mode_type;
	uint32_t pull;
	uint32_t speed;
	uint32_t alt_func;
}GPIO_TYPE;

typedef enum 
{
	RISING_EGDE,
	FALLING_EGDE,
	RISING_FALLING_EGDE
}egdeSelection;


 //Function prototypes
//*******************************************
// GPIO CONFIGURATION

static void config_pin(GPIO_TypeDef *port_name , uint32_t pinNumber ,uint32_t pinMode );

static void config_pin_speed(GPIO_TypeDef *port_name , uint32_t pinNumber , uint32_t pinSpeed , uint32_t mode);

//*********************************************
// PIN Function protocol

//gpio
void gpio_write(GPIO_TypeDef *port_name , uint32_t pinNumber , uint32_t state);

void gpio_toggle(GPIO_TypeDef *port_name , uint32_t pinNumber);

void gpio_init(GPIO_TYPE gpio_type);

void gpio_write_gpioObject(GPIO_TYPE gpioObject , uint32_t state);

void gpio_toggle_gpioObject(GPIO_TYPE gpioObject );

char gpio_read(GPIO_TypeDef *port_name , uint32_t pinNumber );

//gpio interrupt 

void config_gpio_interrupt(GPIO_TypeDef *port_name , uint32_t pinNumber , egdeSelection egde);
void enable_gpio_interrupt(uint32_t pinNumber , IRQn_Type irqNumber);
void clear_gpio_interrupt(uint32_t pinNumber);

void config_gpioObject_interrupt(GPIO_TYPE gpioObject , egdeSelection egde);
void enable_gpioObject_interrupt(GPIO_TYPE gpioObject , IRQn_Type irqNumber);
void clear_gpioObject_interrupt(GPIO_TYPE gpioObject);
#endif
