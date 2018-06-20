#include "main.h"
#include "Periph_Init.h"
#include "Procedures.h"
#include "TomLib_SYS.h"
#include "TomLib_I2C.h"
#include "TomLib_SPI.h"
#include "TomLib_USART.h"
#include "stm32l433xx.h"
#include "stm32l4xx.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_usart.h"







int main(void) {
	SystemClock_Config();
	TIM6_Init();
	GPIO_Init();
	LL_GPIO_SetOutputPin(GPIOA, _3V3_EN);
	LL_GPIO_SetOutputPin(GPIOA, _5V_EN);
	TL_mDelay(250);	//displej po probuzení dává najevo že žije po cca 220 ms odesílá data, takže se èeká - jinak by se spustil IRQ
	SPI2_Init();
	TIM7_Init();
	USART1_Init();
	USART2_Init();
	I2C2_Init();

	ADC_Init();
	calib_val = ADC_CALIB_REF_Read();
	IRQ_Init(); //nutno inicializovat po všech periferiích

	//GPIOC->ODR = 0;

	EEPROM_Write(eeprom_data);
	EEPROM_Read(eeprom_data_r, 5);
	//EEPROM_Read(eeprom_data_r);
	//AS3935_REG_Write(0x01,0b00110010);
	ADC_VC_Read(&voltage, &consumption);

	HMI_Send("bkcmd=1");
	TL_mDelay(100);
	AS3935_REG_Read(0x03);
	while (1) {
		ADC_VC_Read(&voltage, &consumption);
		if (RXHMIPacket_ready) {
			StateAutomat();
			//TL_mDelay(100);
			TL_mDelay(500);
		}
	}
}






void StateAutomat() {
	switch (bufferUSART1[0]) {

	case 0xA1:

		AS3935_REG_Write(0x00, bufferUSART1[1]);
		AS3935_REG_Write(0x01, bufferUSART1[2]);
		AS3935_REG_Write(0x02, bufferUSART1[3]);
		AS3935_REG_Write(0x03, bufferUSART1[4]);
		AS3935_REG_Write(0x08, bufferUSART1[5]);

		Reg_lghtng[0] = AS3935_REG_Read(0x00);
		Reg_lghtng[1] = AS3935_REG_Read(0x01);
		Reg_lghtng[2] = AS3935_REG_Read(0x02);
		Reg_lghtng[3] = AS3935_REG_Read(0x03);
		Reg_lghtng[4] = AS3935_REG_Read(0x08);

		RXHMIPacket_ready = 0;
		USART1_Buffer_Clear();
		break;

	case 0xA2:

		Reg_lghtng[0] = AS3935_REG_Read(0x00);
		Reg_lghtng[1] = AS3935_REG_Read(0x01);
		Reg_lghtng[2] = AS3935_REG_Read(0x02);
		Reg_lghtng[3] = AS3935_REG_Read(0x03);
		Reg_lghtng[4] = AS3935_REG_Read(0x08);

		sprintf(string, "config_0_p.reg0.val=%d", Reg_lghtng[0]);
		HMI_Send(string);
		HMI_Send("config_0_p.n1.bco=64520");

		sprintf(string, "config_1_p.reg1.val=%d", Reg_lghtng[1]);
		HMI_Send(string);
		HMI_Send("config_1_p.n1.bco=64520");

		sprintf(string, "config_2_p.reg2.val=%d", Reg_lghtng[2]);
		HMI_Send(string);
		HMI_Send("config_2_p.n1.bco=64520");

		sprintf(string, "config_3_p.reg3.val=%d", Reg_lghtng[3]);
		HMI_Send(string);
		HMI_Send("config_3_p.n1.bco=64520");

		sprintf(string, "config_4_p.reg8.val=%d", Reg_lghtng[4]);
		HMI_Send(string);
		HMI_Send("config_4_p.n1.bco=64520");

		RXHMIPacket_ready = 0;
		USART1_Buffer_Clear();
		break;

	}

}
