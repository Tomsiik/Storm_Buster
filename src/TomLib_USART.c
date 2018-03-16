/*
 * TomLib_USART.c
 *
 *  Created on: 9. 11. 2017
 *      Author: Tomsik
 */


#include "TomLib_USART.h"
#include "string.h"


void TL_USART_putByte(char charr){
	while(LL_USART_IsActiveFlag_TXE(USART2)==0){}
	LL_USART_TransmitData8(USART2,charr);
}

void TL_USART_printf(char charr[]){
	for(int i=0;i<strlen(charr);i++){
		TL_USART_putByte(charr[i]);
	}

}

USART_result TL_USART_AVALAIBLE(){
	if (LL_USART_IsActiveFlag_RXNE(USART2)==1){
		return TRUE;
	}
	else{
		return FALSE;
	}

}

uint8_t TL_USART_ReadByte(){
	return LL_USART_ReceiveData8(USART2);

}
