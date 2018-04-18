
#include "main.h"

extern uint32_t calib_val;

float voltage;
uint8_t consumption;
uint16_t temp;
uint8_t addr_ofset=1,pokusna0=100,pokusna1=57,pokusna2=99,pokusna3=51,pokusna4=154;

uint8_t *eeprom_data[]={&addr_ofset,&pokusna0,&pokusna1,&pokusna2,&pokusna3,&pokusna4};
uint8_t eeprom_data_r[6];

uint8_t data[]={0x01,55};
uint8_t data_read;


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
	TL_TIM6_Delay(100);
	READ(eeprom_data_r,6);
	//EEPROM_Read(eeprom_data_r);

	while (1) {
		LL_GPIO_SetOutputPin(GPIOA, _3V3_EN	);
		LL_GPIO_SetOutputPin(GPIOA, _5V_EN	);
		GPIOC->ODR |= ULED2;
		ADC_VC_Read(&voltage,&consumption);
		//Temperature_Config(0x00);
		//Temperature_Read(&temp);


		GPIOC->ODR = 0;
		ADC_VC_Read(&voltage,&consumption);



	}
}


void READ(uint8_t *data,uint8_t size){
		LL_GPIO_SetOutputPin(GPIOB,WP);
		LL_I2C_DisableAutoEndMode(I2C2);
		LL_I2C_SetTransferRequest(I2C2, LL_I2C_REQUEST_WRITE);
		TL_I2C_SetSlaveAddress(I2C2, EEPROM_Addr);
		LL_I2C_SetTransferSize(I2C2, 1);
		TL_I2C_Start(I2C2);
		TL_I2C_WriteByte(I2C2, 0x01);
		LL_I2C_ClearFlag_STOP(I2C2);
		while(LL_I2C_IsActiveFlag_TC(I2C2)==0){}
		while(LL_I2C_IsActiveFlag_BUSY(I2C2)==0){}
		LL_I2C_DisableAutoEndMode(I2C2);
		LL_I2C_SetTransferRequest(I2C2, LL_I2C_REQUEST_READ);
		LL_I2C_SetTransferSize(I2C2,size);
		TL_I2C_Start(I2C2);
		for(uint8_t y=0;y<size;y++){
		data[y]=TL_I2C_ReadByte(I2C2);
		}
		TL_I2C_Stop(I2C2);
		//while(LL_I2C_IsActiveFlag_TC(I2C2)==1){}
}






























