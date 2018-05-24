
#include "main.h"

extern uint32_t calib_val;
extern uint8_t bufferUSART1[30];

float voltage;
uint8_t consumption;
float temp;
uint8_t addr_ofset=1,pokusna0=100,pokusna1=57,pokusna2=99,pokusna3=51,pokusna4=154;
uint8_t *eeprom_data[]={&addr_ofset,&pokusna0,&pokusna1,&pokusna2,&pokusna3,&pokusna4};
uint8_t eeprom_data_r[5];
uint8_t data[]={0x01,55};
uint8_t data_read;
uint8_t as3935_reg;
uint8_t i;



int main(void) {
	SystemClock_Config();
	TIM6_Init();
	SPI2_Init();
	USART1_Init();
	USART2_Init();
	I2C2_Init();
	GPIO_Init();
	LL_GPIO_SetOutputPin(GPIOA, _3V3_EN	);
	LL_GPIO_SetOutputPin(GPIOA, _5V_EN	);
	//ADC_Init();
	TL_TIM6_Delay(10);
	IRQ_Init(); //nutno inicializovat po všech periferiích

	//calib_val = ADC_CALIB_REF_Read();
	//GPIOC->ODR = 0;

	//EEPROM_Write(eeprom_data);
	//EEPROM_Read(eeprom_data_r,5);
	//EEPROM_Read(eeprom_data_r);
	//AS3935_REG_Write(0x01,0b00110010);

	while (1) {
		TL_USART_printf(USART1,"va0.val=15");
		TL_USART_putByte(USART1,255);
		TL_USART_putByte(USART1,255);
		TL_USART_putByte(USART1,255);
		TL_mDelay(500);
		TL_USART_printf(USART1,"va0.val=128");
		TL_USART_putByte(USART1,255);
		TL_USART_putByte(USART1,255);
		TL_USART_putByte(USART1,255);
		TL_mDelay(500);


	}
}

































