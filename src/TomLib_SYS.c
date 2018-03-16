/*
 * 		TomLib_SYS.c
 *
 *  	Created on: 21. 10. 2017
 *      Author: Tomsik
 */
/* Systémová knihovna
 * poskytuje delay funkce
 */

#include "TomLib_SYS.h"

#include "main.h"

extern __IO uint32_t TimmingDelay;

/* Systick Delay v microsekundách
 * range min 10 us
 */
void TL_uDelay(__IO uint32_t time) {
	LL_SYSTICK_EnableIT();
	time = time / 10;
	TimmingDelay = time;
	while (TimmingDelay != 0);
	LL_SYSTICK_DisableIT();
}

/* Systick Delay v milisekundách
 * range min 1 ms
 */
void TL_mDelay(__IO uint32_t time) {
	LL_SYSTICK_EnableIT();
	time = time * 100;
	TimmingDelay = time;
	while (TimmingDelay != 0);
	LL_SYSTICK_DisableIT();
}

void TIM6_Init(void) {

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
	LL_TIM_StructInit(TIM6);
//LL_TIM_SetClockSource(TIM6,)
	LL_TIM_SetPrescaler(TIM6, 31);

}
void TL_TIM6_Delay(uint32_t time) {
	LL_TIM_SetAutoReload(TIM6, time);
	LL_TIM_SetCounter(TIM6, 0);

	LL_TIM_ClearFlag_UPDATE(TIM6);
	LL_TIM_EnableCounter(TIM6);

	while (!LL_TIM_IsActiveFlag_UPDATE(TIM6)) {
	}
	LL_TIM_DisableCounter(TIM6);

}

