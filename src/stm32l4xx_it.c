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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */


__IO uint32_t TimmingDelay;

void SysTick_Handler(void)
{	 if(TimmingDelay !=0)
	{
		TimmingDelay --;
	}
}

void EXTI9_5_IRQHandler(void){
	if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_6)){

		GPIOC->ODR |= ULED2;
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
	}
}

#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif

