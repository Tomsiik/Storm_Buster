/*
 * TomLib_USART.h
 *
 *  Created on: 9. 11. 2017
 *      Author: Tomsik
 */

#ifndef TOMLIB_USART_H_
#define TOMLIB_USART_H_

#include "stm32l4xx_ll_usart.h"

typedef enum {
	TRUE = 0x01,
	FALSE = 0x00
} USART_result;

void TL_USART_putByte(USART_TypeDef *USARTx,char charr);
void TL_USART_printf(USART_TypeDef *USARTx,char charr[]);
void TL_USART_putBuffer(USART_TypeDef *USARTx,uint8_t data[],uint8_t size);
USART_result TL_USART_Available(USART_TypeDef *USARTx);
uint8_t TL_USART_ReadByte(USART_TypeDef *USARTx);




#endif /* TOMLIB_USART_H_ */
