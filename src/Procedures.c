/*
 * Procedure.c
 *
 *  Created on: 31. 3. 2018
 *      Author: Tomsik
 */

#include "Periph_Init.h"


 uint32_t calib_val;


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

void ADC_Read_VC(float *sens2,float *consumption){

	uint32_t vrefin_data=0;
	uint32_t rawdata1=0;
	uint32_t rawdata2=0;
	float voltage1=0;
	float voltage2=0;
	float voltage_diff=0;

	for (int y = 0; y <= 10; y++) {		//pøeètení analogových vstupù a reference 10 krát

		ADC_StartConversion();
		vrefin_data +=ADC_read();
		rawdata1 +=ADC_read();
		rawdata2+=ADC_read();
		LL_ADC_ClearFlag_EOS(ADC1);

	}
	rawdata1 = rawdata1 / 10;		//provedení aritmetického prùmìru
	rawdata2 = rawdata2 / 10;
	vrefin_data = vrefin_data / 10;

	voltage1 = (3.0 * calib_val * rawdata1 / ((float) vrefin_data * 4095));	//výpoèet dat na napìtí
	voltage1 *= 4;
	voltage2 = (3.0 * calib_val * rawdata2 / ((float) vrefin_data * 4095));
	voltage2 *= 4;


	*sens2=voltage2;

	voltage_diff=voltage2-voltage1;		//rozdílové napìtí na vstupech - napìtí na shunt rezistoru
	*consumption=(float)(voltage_diff/ShuntR); //výpoèet proudu do napájení jádra

}


