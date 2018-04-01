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

void ADC_Read_Voltage(float *sens1,float *sens2){

	uint32_t vrefin_data=0;
	uint32_t rawdata1=0;
	uint32_t rawdata2=0;
	float voltage1=0;
	float voltage2=0;
	float voltage_diff=0;

	for (int y = 0; y <= 20; y++) {

		ADC_StartConversion();
		vrefin_data +=ADC_read();
		rawdata1 +=ADC_read();
		rawdata2+=ADC_read();
		LL_ADC_ClearFlag_EOS(ADC1);
		TL_mDelay(10);
	}
	rawdata1 = rawdata1 / 20;
	rawdata2 = rawdata2 / 20;
	vrefin_data = vrefin_data / 20;

	voltage1 = (3.0 * calib_val * rawdata1 / ((float) vrefin_data * 4095));
	voltage1 *= 4;
	voltage2 = (3.0 * calib_val * rawdata2 / ((float) vrefin_data * 4095));
	voltage2 *= 4;

	*sens1=voltage1;
	*sens2=voltage2;

	voltage_diff=voltage2-voltage1;

}


