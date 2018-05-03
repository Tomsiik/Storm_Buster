
#include "main.h"

extern uint32_t calib_val;

float voltage;
uint8_t consumption;
float temp;
uint8_t addr_ofset=1,pokusna0=100,pokusna1=57,pokusna2=99,pokusna3=51,pokusna4=154;

uint8_t *eeprom_data[]={&addr_ofset,&pokusna0,&pokusna1,&pokusna2,&pokusna3,&pokusna4};
uint8_t eeprom_data_r[5];

uint8_t data[]={0x01,55};
uint8_t data_read;

uint8_t as3935_reg;
int main(void) {
	SystemClock_Config();
	SPI2_Init();
	USART1_Init();
	USART2_Init();
	I2C2_Init();
	GPIO_Init();
	TIM6_Init();
	ADC_Init();
	//TL_mDelay(100);
	IRQ_Init(); //nutno inicializovat po všech periferiích

	calib_val = ADC_CALIB_REF_Read();
	GPIOC->ODR = 0;

	EEPROM_Write(eeprom_data);
	EEPROM_Read(eeprom_data_r,5);
	//EEPROM_Read(eeprom_data_r);
	//AS3935_REG_Write(0x01,0b00110010);
	while (1) {
		TL_USART_putByte(USART2,'A');
		TL_mDelay(100);
		LL_GPIO_SetOutputPin(GPIOA, _3V3_EN	);
		LL_GPIO_SetOutputPin(GPIOA, _5V_EN	);
		//LL_GPIO_SetOutputPin(GPIOC,ULED1);
		//GPIOC->ODR |= ULED2;
		//ADC_VC_Read(&voltage,&consumption);
		//Temperature_Config(0x00);
		//Temperature_Read_float(&temp);
		//TL_TIM6_Delay(50000);
		//GPIOC->ODR = 0;
		//ADC_VC_Read(&voltage,&consumption);
		//as3935_reg=AS3935_REG_Read(0x01);
		//AS3935_REG_Write(0x01,0x32);
		//as3935_reg=AS3935_REG_Read(0x01);
		//TL_TIM6_Delay(50000);

	}
}

































