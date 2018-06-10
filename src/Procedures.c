/*
 * Procedure.c
 *
 *  Created on: 31. 3. 2018
 *      Author: Tomsik
 */


#include "Procedures.h"
#include "stm32l4xx.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_i2c.h"
#include "stm32l4xx_ll_tim.h"
#include "Periph_Init.h"
#include "TomLib_I2C.h"
#include "TomLib_SPI.h"
#include "TomLib_USART.h"

uint32_t calib_val;
uint8_t bufferUSART1[30];

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

/* Mereni vstupniho napìtí USB, a odbìr z 3V3 vìtve (core voltage)
 *
 */
void ADC_VC_Read(float *sens, uint8_t *consumption) {

	uint32_t vrefin_data = 0;
	uint32_t rawdata1 = 0;
	uint32_t rawdata2 = 0;
	float voltage1 = 0;
	float voltage2 = 0;
	float voltage_diff = 0;

	for (int y = 0; y <= 10; y++) {	//pøeètení analogových vstupù a reference 10 krát

		ADC_StartConversion();
		vrefin_data += ADC_Read();
		rawdata1 += ADC_Read();
		rawdata2 += ADC_Read();
		LL_ADC_ClearFlag_EOS(ADC1);

	}
	rawdata1 = rawdata1 / 10;		//provedení aritmetického prùmìru
	rawdata2 = rawdata2 / 10;
	vrefin_data = vrefin_data / 10;

	voltage1 = (3.0 * calib_val * rawdata1 / ((float) vrefin_data * 4095));	//výpoèet dat na napìtí
	voltage1 *= 4;
	voltage2 = (3.0 * calib_val * rawdata2 / ((float) vrefin_data * 4095));
	voltage2 *= 4;

	*sens = voltage2;

	voltage_diff = voltage2 - voltage1;	//rozdílové napìtí na vstupech - napìtí na shunt rezistoru
	*consumption = (uint8_t) ((voltage_diff / ShuntR) * 1000); //výpoèet proudu do napájení jádra

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


/*LIGHTNING*/
uint8_t AS3935_REG_Read(uint8_t reg){
	uint8_t dummy = 0x00;
	uint8_t r_data;
	TL_SPI_Reset_CSN(LGHTNG_CS);
	TL_SPI_Transmit_Byte(SPI2,R_REG(reg));
	r_data=TL_SPI_ReceiveTransmit_Byte(SPI2,dummy);
	TL_SPI_Set_CSN(LGHTNG_CS);
	return r_data;
}

void AS3935_REG_Write(uint8_t reg,uint8_t data){
	TL_SPI_Reset_CSN(LGHTNG_CS);
	TL_SPI_Transmit_Byte(SPI2,W_REG(reg));
	TL_SPI_Transmit_Byte(SPI2,data);
	TL_SPI_Set_CSN(LGHTNG_CS);
}

void AS3935_REG_SetDef(){
	TL_SPI_Reset_CSN(LGHTNG_CS);
	TL_SPI_Transmit_Byte(SPI2,W_REG(0x3C));
	TL_SPI_Transmit_Byte(SPI2,0x96);
	TL_SPI_Set_CSN(LGHTNG_CS);
}


void TIM7_Start(uint32_t auto_reload){
	//LL_TIM_SetAutoReload(TIM7, time);
	LL_TIM_DisableCounter(TIM7);
	LL_TIM_SetCounter(TIM7, 0);
	LL_TIM_SetAutoReload(TIM7,auto_reload);
	LL_TIM_ClearFlag_UPDATE(TIM7);
	LL_TIM_EnableCounter(TIM7);
}
void TIM7_Stop(){
	//LL_TIM_SetAutoReload(TIM7, time);
	LL_TIM_SetCounter(TIM7, 0);
	LL_TIM_ClearFlag_UPDATE(TIM7);
	LL_TIM_DisableCounter(TIM7);
}

uint32_t TIM7_Read(){
	return LL_TIM_GetCounter(TIM7);

}

void USART1_Buffer_Clear(){
	for(uint8_t i=0;i<30;i++){
		bufferUSART1[i]=0;

	}
}

void HMI_Send(char *charr){
	TL_USART_printf(USART1,charr);
	TL_USART_putByte(USART1,255);
	TL_USART_putByte(USART1,255);
	TL_USART_putByte(USART1,255);
}
