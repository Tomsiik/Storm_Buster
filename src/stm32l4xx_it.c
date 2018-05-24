/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32l4xx_it.h"
#include"Periph_Init.h"
#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_gpio.h"




__IO uint32_t TimmingDelay;
uint8_t bufferUSART1[];

void SysTick_Handler(void)
{	 if(TimmingDelay !=0)
	{	//GPIOC->ODR = 0;
		TimmingDelay --;
		GPIOC->ODR = LL_GPIO_PIN_2;
	}
}

void EXTI9_5_IRQHandler(void){
	if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_6)){
		AS3935_REG_Read(0x03);

		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
	}
}

void USART2_IRQHandler(){
	if(LL_USART_IsActiveFlag_RXNE(USART2)){


		LL_USART_ReceiveData8(USART2);
	}
}

void USART1_IRQHandler(){
	if(LL_USART_IsActiveFlag_RXNE(USART1)){
		uint8_t count;
		bufferUSART1[count]=LL_USART_ReceiveData8(USART1);
		count++;

	}

}


#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif

