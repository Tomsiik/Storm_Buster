
#include "main.h"

extern uint32_t calib_val;

float voltage;
uint8_t consumption;
uint16_t temp;
uint8_t addr_ofset=1,pokusna0=15,pokusna1=55;

uint8_t *eeprom_data[]={&addr_ofset,&pokusna0,&pokusna1};

uint8_t data[]={12,15,16};


int main(void) {
	SystemClock_Config();
	SPI2_Init();
	USART2_Init();
	I2C2_Init();
	GPIO_Init();
	TIM6_Init();
	ADC_Init();

	calib_val = ADC_CALIB_REF_Read();

	GPIOC->ODR = 0;
	TL_mDelay(2000);




	EEPROM_Write(eeprom_data);


	while (1) {
		LL_GPIO_SetOutputPin(GPIOA, _3V3_EN	);
		LL_GPIO_SetOutputPin(GPIOA, _5V_EN	);
		GPIOC->ODR |= ULED2;
		ADC_VC_Read(&voltage,&consumption);
		Temperature_Config(0x00);
		Temperature_Read(&temp);


		GPIOC->ODR = 0;
		ADC_VC_Read(&voltage,&consumption);




	}
}

