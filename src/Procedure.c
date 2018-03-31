/*
 * Procedure.c
 *
 *  Created on: 31. 3. 2018
 *      Author: Tomsik
 */
#include "main.h"
#include "Periph_Init.h"


extern __IO uint32_t calib_val;


uint32_t ADC_CALIB_REF_Read(){
	return *VREFINT_CAL_ADDR;
}

uint32_t ADC_read(){
	GPIOB->ODR|=LL_GPIO_PIN_13;

	while(LL_ADC_IsActiveFlag_EOC(ADC1)==RESET){}
	return READ_REG(ADC1->DR);
}

void ADC_StartConversion(){
	while(LL_ADC_IsActiveFlag_ADRDY(ADC1)==RESET);
	LL_ADC_REG_StartConversion(ADC1);
}

void ADC_Read_Voltage(float sens1,float *sens2){

	uint32_t vrefin_data;
	uint32_t rawdata;
	float voltage;

	rawdata = 0;
	vrefin_data = 0;
	TL_TIM6_Delay(1000000);

	for (int y = 0; y <= 20; y++) {

		ADC_StartConversion();
		vrefin_data += ADC_read();
		rawdata += ADC_read();
		LL_ADC_ClearFlag_EOS(ADC1);
		TL_mDelay(10);
	}
	rawdata = rawdata / 20;
	vrefin_data = vrefin_data / 20;

	voltage = (3.0 * calib_val * rawdata / ((float) vrefin_data * 4095));
	voltage *= 4;

	sens1=voltage;
}




