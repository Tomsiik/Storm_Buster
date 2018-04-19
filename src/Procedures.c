/*
 * Procedure.c
 *
 *  Created on: 31. 3. 2018
 *      Author: Tomsik
 */

#include "Periph_Init.h"
#include "Procedures.h"
#include "main.h"
#include "TomLib_I2C.h"


uint32_t calib_val;

uint32_t ADC_CALIB_REF_Read() {
	return *VREFINT_CAL_ADDR;
}

uint32_t ADC_Read() {
	GPIOB->ODR |= LL_GPIO_PIN_13;

	while (LL_ADC_IsActiveFlag_EOC(ADC1) == RESET) {
	}
	return READ_REG(ADC1->DR);
}

void ADC_StartConversion() {
	while (LL_ADC_IsActiveFlag_ADRDY(ADC1) == RESET)
		;
	LL_ADC_REG_StartConversion(ADC1);
}

/* Mereni vstupniho nap�t� USB, a odb�r z 3V3 v�tve (core voltage)
 *
 */
void ADC_VC_Read(float *sens, uint8_t *consumption) {

	uint32_t vrefin_data = 0;
	uint32_t rawdata1 = 0;
	uint32_t rawdata2 = 0;
	float voltage1 = 0;
	float voltage2 = 0;
	float voltage_diff = 0;

	for (int y = 0; y <= 10; y++) {	//p�e�ten� analogov�ch vstup� a reference 10 kr�t

		ADC_StartConversion();
		vrefin_data += ADC_Read();
		rawdata1 += ADC_Read();
		rawdata2 += ADC_Read();
		LL_ADC_ClearFlag_EOS(ADC1);

	}
	rawdata1 = rawdata1 / 10;		//proveden� aritmetick�ho pr�m�ru
	rawdata2 = rawdata2 / 10;
	vrefin_data = vrefin_data / 10;

	voltage1 = (3.0 * calib_val * rawdata1 / ((float) vrefin_data * 4095));	//v�po�et dat na nap�t�
	voltage1 *= 4;
	voltage2 = (3.0 * calib_val * rawdata2 / ((float) vrefin_data * 4095));
	voltage2 *= 4;

	*sens = voltage2;

	voltage_diff = voltage2 - voltage1;	//rozd�lov� nap�t� na vstupech - nap�t� na shunt rezistoru
	*consumption = (uint8_t) ((voltage_diff / ShuntR) * 1000); //v�po�et proudu do nap�jen� j�dra

}

/*Temperature*/
void Temperature_Config(uint8_t config) {
	uint8_t data[2] = { config, TEMP_CONF_REG };
	TL_I2C_SendData(I2C2, Temp_Addr, data, 2);
}

void Temperature_Read_int(uint16_t *temp) {
	uint8_t data[2];
	TL_I2C_SendOneByte(I2C2, Temp_Addr, TEMP_TEMP_REG);
	TL_I2C_ReadData(I2C2, Temp_Addr, data, 2);
	*temp=(((uint16_t)data[0]<<4) | (data[1]>>4))*0.0625;
}
void Temperature_Read_float(float *temp) {
	uint8_t data[2];
	TL_I2C_SendOneByte(I2C2, Temp_Addr, TEMP_TEMP_REG);
	TL_I2C_ReadData(I2C2, Temp_Addr, data, 2);
	*temp=(((uint16_t)data[0]<<4) | (data[1]>>4))*0.0625;
}


/*EEPROM*/
void EEPROM_Write(uint8_t *data[]){
	LL_GPIO_ResetOutputPin(GPIOB,WP);
	TL_I2C_SendData(I2C2,EEPROM_Addr,*data,6);
	LL_GPIO_SetOutputPin(GPIOB,WP);

}


void EEPROM_Read(uint8_t *data,uint8_t size){
		LL_GPIO_SetOutputPin(GPIOB,WP);
		LL_I2C_DisableAutoEndMode(I2C2);
		LL_I2C_SetTransferRequest(I2C2, LL_I2C_REQUEST_WRITE);
		TL_I2C_SetSlaveAddress(I2C2, EEPROM_Addr);
		LL_I2C_SetTransferSize(I2C2, 1);
		TL_I2C_Start(I2C2);
		TL_I2C_WriteByte(I2C2, 0x01);
		LL_I2C_ClearFlag_STOP(I2C2);
		while(LL_I2C_IsActiveFlag_TC(I2C2)==0){}
		LL_I2C_DisableAutoEndMode(I2C2);
		LL_I2C_SetTransferRequest(I2C2, LL_I2C_REQUEST_READ);
		LL_I2C_SetTransferSize(I2C2,size);
		TL_I2C_Start(I2C2);
		for(uint8_t y=0;y<size;y++){
		data[y]=TL_I2C_ReadByte(I2C2);
		}
		TL_I2C_Stop(I2C2);
		LL_I2C_ClearFlag_STOP(I2C2);
		//while(LL_I2C_IsActiveFlag_TC(I2C2)==1){}
}
