/*
 * main.h
 *
 *  Created on: 11. 10. 2017
 *      Author: Tomsik
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stdio.h"





/*Definitions and declarations */
extern uint32_t calib_val;
extern uint8_t bufferUSART1[30];
extern uint8_t RXHMIPacket_ready;

float voltage;
uint8_t consumption;
float temp;
uint8_t addr_ofset = 1, pokusna0 = 100, pokusna1 = 57, pokusna2 = 99, pokusna3 =
		51, pokusna4 = 154;
uint8_t *eeprom_data[] = { &addr_ofset, &pokusna0, &pokusna1, &pokusna2,
		&pokusna3, &pokusna4 };
uint8_t eeprom_data_r[5];
uint8_t as3935_reg;
uint8_t i;
uint8_t a;















int main(void);
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)


#endif /* MAIN_H_ */
