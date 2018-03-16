/*
 * TomLib_SPI.c
 *
 *  Created on: 14. 10. 2017
 *      Author: Tomsik
 */

#include"TomLib_SPI.h"
#include"stm32l4xx_ll_gpio.h"


void TL_SPI_Set_CSN(uint32_t Pin){
	//while(LL_SPI_IsActiveFlag_BSY(TL_SPI)==1){}
	LL_GPIO_SetOutputPin(GPIOB,Pin);
}

void TL_SPI_Reset_CSN(uint32_t Pin){
	//while(LL_SPI_IsActiveFlag_BSY(TL_SPI)==1){}
	LL_GPIO_ResetOutputPin(GPIOB,Pin);
}


void TL_SPI_Transmit_Byte(SPI_TypeDef *SPI,uint8_t dataIn){
	while(LL_SPI_IsActiveFlag_TXE(SPI)==0){}
	LL_SPI_TransmitData8(SPI,dataIn);

	while(LL_SPI_IsActiveFlag_BSY(SPI)==1){}
	LL_SPI_ReceiveData8(SPI);
}


void TL_SPI_Transmit_Multi(SPI_TypeDef *SPI,uint8_t dataIn[],uint32_t size){

	for(uint8_t count=0; count<size; count++){
		while(LL_SPI_IsActiveFlag_TXE(SPI)==0){}
		LL_SPI_TransmitData8(SPI,dataIn[count]);
		while(LL_SPI_IsActiveFlag_BSY(SPI)==1){}
		LL_SPI_ReceiveData8(SPI);
	}


}

uint8_t TL_SPI_ReceiveTransmit_Byte(SPI_TypeDef *SPI,uint8_t dataIn){
	while(LL_SPI_IsActiveFlag_TXE(SPI)==0){}
	LL_SPI_TransmitData8(SPI,dataIn);
	while(LL_SPI_IsActiveFlag_RXNE(SPI)==0){}
	while(LL_SPI_IsActiveFlag_BSY(SPI)==1){}
	return LL_SPI_ReceiveData8(SPI);
}

void TL_SPI_ReceiveTransmit_Multi(SPI_TypeDef *SPI,uint8_t dataIn[],uint8_t dataOut[],uint16_t size){
	uint16_t count=0;
	for(count=0;count<size;count++){
		while(LL_SPI_IsActiveFlag_TXE(SPI)==0){}
		LL_SPI_TransmitData8(SPI,dataIn[count]);

		while(LL_SPI_IsActiveFlag_RXNE(SPI)==0){}
		dataOut[count]=LL_SPI_ReceiveData8(SPI);
		while(LL_SPI_IsActiveFlag_BSY(SPI)==1){}


	}
}

