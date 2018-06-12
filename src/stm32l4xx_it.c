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
#include "stm32l4xx_ll_tim.h"
#include "Procedures.h"



__IO uint32_t TimmingDelay;
uint8_t bufferUSART1[30];
uint8_t count;
uint8_t RXHMIPacket_ready;

void SysTick_Handler(void)
{	 if(TimmingDelay !=0)
	{
		TimmingDelay --;

	}
}

void EXTI9_5_IRQHandler(void){
	if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_6)){
		//AS3935_REG_Read(0x03);
		//LL_GPIO_TogglePin(GPIOC,ULED1);
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

		TIM7_Start(5);
		bufferUSART1[count]=LL_USART_ReceiveData8(USART1);
		count++;
		//RXHMIPacket_ready=0;

		}
}


void TIM7_IRQHandler(){
	if(LL_TIM_IsActiveFlag_UPDATE(TIM7)){
		TIM7_Stop();
		if (bufferUSART1[count-1]==0xFF && bufferUSART1[count-2]==0xFF && bufferUSART1[count-3]==0xFF){
			RXHMIPacket_ready=1;
		}
		LL_USART_ReceiveData8(USART1);
		LL_TIM_ClearFlag_UPDATE(TIM7);
		count=0;
	}
}


#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif

