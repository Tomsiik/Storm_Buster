/*
 * Procedures.h
 *
 *  Created on: 31. 3. 2018
 *      Author: Tomsik
 */

#ifndef PROCEDURES_H_
#define PROCEDURES_H_

#include "stm32l4xx.h"

typedef enum {
	true = 0x01,
	false = 0x00
} result;



//ADC
uint32_t ADC_CALIB_REF_Read(void);
uint32_t ADC_Read(void);
void ADC_StartConversion(void);
void ADC_VC_Read(float *sens,uint8_t *consumption);

//Temperature

void Temperature_Config(uint8_t config);
void Temperature_Read_int(uint16_t *temp);
void Temperature_Read_float(float *temp);

//EEPROM
result EEPROM_Write(uint8_t *data[]);
result EEPROM_Read(uint8_t *data, uint8_t size);

//LIGHTNING
uint8_t AS3935_REG_Read(uint8_t reg);
void AS3935_REG_Write(uint8_t reg,uint8_t data);
void AS3935_REG_SetDef();

//TIM-timeout
void TIM7_Start(uint32_t auto_reload);
void TIM7_Stop();
uint32_t TIM7_Read();


//UART_HMI
void USART1_Buffer_Clear();
void HMI_Send(char *charr);
//UART_USB




#endif /* PROCEDURES_H_ */
