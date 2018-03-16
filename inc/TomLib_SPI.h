/*
 * TomLib_SPI.h
 *
 *  Created on: 14. 10. 2017
 *      Author: Tomsik
 */

#ifndef TOMLIB_SPI_H_
#define TOMLIB_SPI_H_
//#include "main.h"
#include "stm32l4xx_ll_spi.h"




void TL_SPI_Set_CSN(uint32_t Pin);
void TL_SPI_Reset_CSN(uint32_t Pin);
void TL_SPI_Transmit_Byte(SPI_TypeDef *SPI,uint8_t dataIn);
void TL_SPI_Transmit_Multi(SPI_TypeDef *SPI,uint8_t dataIn[],uint32_t size);
uint8_t TL_SPI_ReceiveTransmit_Byte(SPI_TypeDef *SPI,uint8_t dataIn);
void TL_SPI_ReceiveTransmit_Multi(SPI_TypeDef *SPI,uint8_t dataIn[],uint8_t dataOut[],uint16_t size);




#endif /* TOMLIB_SPI_H_ */
