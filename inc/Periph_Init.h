/*
 * WD_Periph.h
 *
 *  Created on: 14. 10. 2017
 *      Author: Tomsik
 */

#include "stm32l433xx.h"
#include "stm32l4xx.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_i2c.h"
#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_adc.h"


#ifndef PERIPH_INIT_H_
#define PERIPH_INIT_H_

void SystemClock_Config(void);
void GPIO_Init(void);
void SPI2_Init(void);
void USART1_Init(void);
void USART2_Init(void);
void I2C2_Init(void);
void ADC_Init(void);



/*Pinout definition*/

//GPIOA
#define USBPWREN 	GPIO_PIN_0
#define USART2_TX	GPIO_PIN_2
#define USART2_RX	GPIO_PIN_3
#define SENS1		GPIO_PIN_4
#define SENS2		GPIO_PIN_5
#define _3V3_EN		GPIO_PIN_6
#define _5V_EN		GPIO_PIN_7
#define MCO			GPIO_PIN_8
#define USART1_TX	GPIO_PIN_9
#define USART1_RX	GPIO_PIN_10

//GPIOB
#define ALERT		GPIO_PIN_1
#define WP			GPIO_PIN_2
#define U4			GPIO_PIN_5
#define U3			GPIO_PIN_6
#define U2			GPIO_PIN_7
#define U1			GPIO_PIN_8
#define U0			GPIO_PIN_9
#define I2C2_SCL	GPIO_PIN_10
#define I2C2_SDA	GPIO_PIN_11
#define LGHTNG_CS	GPIO_PIN_12
#define SPI2_SCK	GPIO_PIN_13
#define SPI2_MISO	GPIO_PIN_14
#define SPI2_MOSI	GPIO_PIN_15

//GPIOC
#define ULED1		GPIO_PIN_4
#define ULED2		GPIO_PIN_5
#define LGHTNG_IRQ	GPIO_PIN_6
#define U7			GPIO_PIN_10
#define U6			GPIO_PIN_11
#define U5			GPIO_PIN_12

//System & Hardware
#define ShuntR	16


#endif /* PERIPH_INIT_H_ */

