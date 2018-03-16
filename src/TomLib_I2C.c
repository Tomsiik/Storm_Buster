/*************************************************************************************************
 * TomLib_I2C.c
 *
 *  Created on: 12. 12. 2017
 *      Author: Tomsik
 *************************************************************************************************
 *************************************************************************************************/
/************************************I2C knihovna*************************************************
 * poskytuje funkce pro ovládání zvolené I2C periferie
 *
 *************************************************************************************************/




#include "TomLib_I2c.h"


void TL_I2C_SetSlaveAddress(I2C_TypeDef *I2C,uint8_t address){
	LL_I2C_SetSlaveAddr(I2C,address);
}

void TL_I2C_Start(I2C_TypeDef *I2C){
	LL_I2C_GenerateStartCondition(I2C);
}

void TL_I2C_Stop(I2C_TypeDef *I2C){
	LL_I2C_GenerateStopCondition(I2C);
}


void TL_I2C_InitConfig(I2C_TypeDef *I2C){
	LL_I2C_SetMasterAddressingMode(I2C, LL_I2C_ADDRESSING_MODE_7BIT);
	LL_I2C_EnableAutoEndMode(I2C);
}



void TL_I2C_WriteByte(I2C_TypeDef *I2C,uint8_t data){
	while(LL_I2C_IsActiveFlag_TXE(I2C)==0){}
	LL_I2C_TransmitData8(I2C,data);

}

uint8_t TL_I2C_ReadByte(I2C_TypeDef *I2C){
	while(LL_I2C_IsActiveFlag_RXNE(I2C)==0){}
	return LL_I2C_ReceiveData8(I2C);

}

void TL_I2C_SendData(I2C_TypeDef *I2C,uint8_t addr,uint8_t data[],uint8_t size){
	LL_I2C_SetTransferRequest(I2C, LL_I2C_REQUEST_WRITE);
	TL_I2C_SetSlaveAddress(I2C,addr);
	LL_I2C_SetTransferSize(I2C,size);
	TL_I2C_Start(I2C);
	for(uint8_t count=0;count<size;count++){
		while(LL_I2C_IsActiveFlag_TXIS(I2C)==0){}
		TL_I2C_WriteByte(I2C,data[count]);
	}
	LL_I2C_ClearFlag_STOP(I2C);
	while(LL_I2C_IsActiveFlag_BUSY(I2C)==1){}
}

void TL_I2C_ReadData(I2C_TypeDef *I2C,uint8_t addr,uint8_t data[],uint8_t size){
	LL_I2C_SetTransferRequest(I2C, LL_I2C_REQUEST_READ);
	TL_I2C_SetSlaveAddress(I2C,addr);
	LL_I2C_SetTransferSize(I2C,size);
	TL_I2C_Start(I2C);
	for(uint8_t count=0;count<size;count++){

		data[count]=TL_I2C_ReadByte(I2C);
	}
	LL_I2C_ClearFlag_STOP(I2C);
	while(LL_I2C_IsActiveFlag_BUSY(I2C)==1){}
}


/*Vyšle jeden byte na zvolenou adresu
 * parametr addr je tøeba vložit v osmibitovém formátu s pøiloženým bitem W
 */
void TL_I2C_SendOneByte(I2C_TypeDef *I2C,uint8_t addr,uint8_t data){
	LL_I2C_SetTransferRequest(I2C, LL_I2C_REQUEST_WRITE);
	TL_I2C_SetSlaveAddress(I2C,addr);
	LL_I2C_SetTransferSize(I2C,1);
	TL_I2C_Start(I2C);
	while(LL_I2C_IsActiveFlag_TXIS(I2C)==0){}
	TL_I2C_WriteByte(I2C,data);
	LL_I2C_ClearFlag_STOP(I2C);
	while(LL_I2C_IsActiveFlag_BUSY(I2C)==1){}

}

uint8_t TL_I2C_ReadOneByte(I2C_TypeDef *I2C,uint8_t addr){
	LL_I2C_SetTransferRequest(I2C, LL_I2C_REQUEST_READ);
	TL_I2C_SetSlaveAddress(I2C,addr);
	LL_I2C_SetTransferSize(I2C,1);
	TL_I2C_Start(I2C);
	return TL_I2C_ReadByte(I2C);
	LL_I2C_ClearFlag_STOP(I2C);
	while(LL_I2C_IsActiveFlag_BUSY(I2C)==1){}
}
