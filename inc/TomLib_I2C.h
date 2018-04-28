/*
 * TomLib_I2C.h
 *
 *  Created on: 12. 12. 2017
 *      Author: Tomsik
 */

#ifndef TOMLIB_I2C_H_
#define TOMLIB_I2C_H_



#include "stm32l4xx.h"


typedef enum{
	I2C_OK=0,
	I2C_NOK=1
}I2C_result;

void TL_I2C_SetSlaveAddress(I2C_TypeDef *I2C,uint8_t address);
void TL_I2C_Start(I2C_TypeDef *I2C);
void TL_I2C_Stop(I2C_TypeDef *I2C);
void TL_I2C_InitConfig(I2C_TypeDef *I2C);
void TL_I2C_WriteByte(I2C_TypeDef *I2C,uint8_t data);
uint8_t TL_I2C_ReadByte(I2C_TypeDef *I2C);
I2C_result TL_I2C_SendData(I2C_TypeDef *I2C,uint8_t addr,uint8_t data[],uint8_t size);
I2C_result TL_I2C_ReadData(I2C_TypeDef *I2C,uint8_t addr,uint8_t data[],uint8_t size);
I2C_result TL_I2C_SendOneByte(I2C_TypeDef *I2C,uint8_t addr,uint8_t data);
uint8_t TL_I2C_ReadOneByte(I2C_TypeDef *I2C,uint8_t addr);




#endif /* TOMLIB_I2C_H_ */
