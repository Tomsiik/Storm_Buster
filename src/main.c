
#include "main.h"

__IO uint32_t calib_val;

float voltage1,voltage2;


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
		GPIOC->ODR |= ULED2;
		TL_mDelay(50);
		GPIOC->ODR = 0;
		TL_mDelay(500);

		ADC_Read_Voltage(&voltage1,&voltage2);


	}
}

