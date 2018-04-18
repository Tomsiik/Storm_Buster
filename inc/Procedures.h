/*
 * Procedures.h
 *
 *  Created on: 31. 3. 2018
 *      Author: Tomsik
 */

#ifndef PROCEDURES_H_
#define PROCEDURES_H_

//ADC
uint32_t ADC_CALIB_REF_Read(void);
uint32_t ADC_Read(void);
void ADC_StartConversion(void);
void ADC_VC_Read(float *sens2,uint8_t *consumption);

//Temperature

void Temperature_Config(uint8_t config);
void Temperature_Read(uint16_t *temp);

//EEPROM
void EEPROM_Write(uint8_t *data[]);

void EEPROM_Read(uint8_t data[]);

//LIGHTNING

//UART_HMI

//UART_USB




#endif /* PROCEDURES_H_ */
