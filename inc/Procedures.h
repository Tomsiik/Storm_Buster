/*
 * Procedures.h
 *
 *  Created on: 31. 3. 2018
 *      Author: Tomsik
 */

#ifndef PROCEDURES_H_
#define PROCEDURES_H_

uint32_t ADC_CALIB_REF_Read(void);
uint32_t ADC_read(void);
void ADC_StartConversion(void);
void ADC_Read_Voltage(float *sens1,float *sens2);


#endif /* PROCEDURES_H_ */
