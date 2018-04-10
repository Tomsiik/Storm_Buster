
#include "main.h"

extern uint32_t calib_val;

float voltage;
uint8_t consumption;
uint16_t temp;
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
	while (1) {
		LL_GPIO_SetOutputPin(GPIOA, _3V3_EN	);
		LL_GPIO_SetOutputPin(GPIOA, _5V_EN	);
		GPIOC->ODR |= ULED2;
		ADC_VC_Read(&voltage,&consumption);
		GPIOC->ODR = 0;
		ADC_VC_Read(&voltage,&consumption);
		Temperature_Config(0x00);
		Temperature_Read(&temp);


	}
}

