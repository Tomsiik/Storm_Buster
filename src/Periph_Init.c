#include "stm32l4xx.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_i2c.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_tim.h"
#include "Periph_Init.h"
#include "TomLib_SYS.h"


void SystemClock_Config(void) {
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

	LL_RCC_HSE_Enable();
	LL_RCC_HSE_EnableBypass();

	while (LL_RCC_HSE_IsReady() != 1) {}

	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_1, 16,LL_RCC_PLLR_DIV_4);
	LL_RCC_PLL_EnableDomain_SYS();
	LL_RCC_PLL_Enable();

	while (LL_RCC_PLL_IsReady() != 1) {}
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {}
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_RCC_SetI2CClockSource(LL_RCC_I2C2_CLKSOURCE_PCLK1);

	LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_SYSCLK, LL_RCC_MCO1_DIV_1);

	SystemCoreClockUpdate();

	LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
	SysTick_Config(SystemCoreClock / 100000);
	NVIC_SetPriority(SysTick_IRQn,3);
	LL_SYSTICK_DisableIT();
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_SYSCLK);


}


void GPIO_Init(void)
{ 	/*Povolen� hodin do GPIO periferi�*/
	WRITE_REG(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN) ;


	/*USBPWREN Init*/
	LL_GPIO_SetPinMode(GPIOA,USBPWREN,LL_GPIO_MODE_INPUT);

	/*USART2 GPIO Init*/
	LL_GPIO_SetPinMode(GPIOA,USART2_TX,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(GPIOA,USART2_RX,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOA,USART2_TX,LL_GPIO_SPEED_FREQ_MEDIUM);
	LL_GPIO_SetPinSpeed(GPIOA,USART2_RX,LL_GPIO_SPEED_FREQ_MEDIUM);
	LL_GPIO_SetAFPin_0_7(GPIOA,USART2_TX,LL_GPIO_AF_7);
	LL_GPIO_SetAFPin_0_7(GPIOA,USART2_RX,LL_GPIO_AF_7);

	/*Analog SENS GPIO Init*/
	LL_GPIO_SetPinMode(GPIOA,SENS1,LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOA,SENS2,LL_GPIO_MODE_ANALOG);

	/*Power EN GPIO Init*/
	LL_GPIO_SetPinMode(GPIOA,_5V_EN,LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA,_3V3_EN,LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(GPIOA,_5V_EN,LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinSpeed(GPIOA,_3V3_EN,LL_GPIO_SPEED_FREQ_LOW);

	/*MCO Init*/
	LL_GPIO_SetPinMode(GPIOA,MCO,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOA,MCO,LL_GPIO_SPEED_FREQ_VERY_HIGH);
	LL_GPIO_SetAFPin_8_15(GPIOA,MCO,LL_GPIO_AF_0);

	/*USART1 GPIO Init*/
	LL_GPIO_SetPinMode(GPIOA,USART1_TX,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(GPIOA,USART1_RX,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOA,USART1_TX,LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinSpeed(GPIOA,USART1_RX,LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinPull(GPIOA,USART1_RX,LL_GPIO_PULL_UP);
	LL_GPIO_SetAFPin_8_15(GPIOA,USART1_TX,LL_GPIO_AF_7);
	LL_GPIO_SetAFPin_8_15(GPIOA,USART1_RX,LL_GPIO_AF_7);

	/*ALERT Init*/
	LL_GPIO_SetPinMode(GPIOB,ALERT,LL_GPIO_MODE_INPUT);

	/*WP Init*/
	LL_GPIO_SetPinMode(GPIOB,WP,LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOB,WP,LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinSpeed(GPIOB,WP,LL_GPIO_SPEED_FREQ_MEDIUM);
	LL_GPIO_SetOutputPin(GPIOB,WP);

	/*I2C2 GPIO Init*/
	LL_GPIO_SetPinMode(GPIOB,I2C2_SCL,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(GPIOB,I2C2_SDA,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB,I2C2_SCL,LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinSpeed(GPIOB,I2C2_SDA,LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB,I2C2_SCL,LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetPinOutputType(GPIOB,I2C2_SDA,LL_GPIO_OUTPUT_OPENDRAIN);
	LL_GPIO_SetAFPin_8_15(GPIOB,I2C2_SCL,LL_GPIO_AF_4);
	LL_GPIO_SetAFPin_8_15(GPIOB,I2C2_SDA,LL_GPIO_AF_4);

	/*LGHTNG_CS Init*/
	LL_GPIO_SetPinMode(GPIOB,LGHTNG_CS,LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(GPIOB,LGHTNG_CS,LL_GPIO_SPEED_FREQ_MEDIUM);
	LL_GPIO_SetOutputPin(GPIOB,LGHTNG_CS);

	/*SPI2 GPIO Init*/
	LL_GPIO_SetPinMode(GPIOB,SPI2_SCK,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(GPIOB,SPI2_MISO,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinMode(GPIOB,SPI2_MOSI,LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB,SPI2_SCK,LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinSpeed(GPIOB,SPI2_MISO,LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinSpeed(GPIOB,SPI2_MOSI,LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetAFPin_8_15(GPIOB,SPI2_SCK,LL_GPIO_AF_5);
	LL_GPIO_SetAFPin_8_15(GPIOB,SPI2_MISO,LL_GPIO_AF_5);
	LL_GPIO_SetAFPin_8_15(GPIOB,SPI2_MOSI,LL_GPIO_AF_5);

	/*ULED1 */
	LL_GPIO_SetPinMode(GPIOC,ULED1,LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(GPIOC,ULED1,LL_GPIO_SPEED_FREQ_LOW);

	/*ULED2 */
	LL_GPIO_SetPinMode(GPIOC,ULED2,LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(GPIOC,ULED2,LL_GPIO_SPEED_FREQ_LOW);

	/*LGHTNG_IRQ*/
	LL_GPIO_SetPinMode(GPIOC,LGHTNG_IRQ,LL_GPIO_MODE_INPUT);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);



}

void SPI2_Init(void)
{
  LL_SPI_InitTypeDef SPI_InitStruct;
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV64;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 7;
  LL_SPI_SetRxFIFOThreshold(SPI2,LL_SPI_RX_FIFO_TH_QUARTER);
  LL_SPI_Init(SPI2, &SPI_InitStruct);
  LL_SPI_Enable(SPI2);
  NVIC_SetPriority(EXTI9_5_IRQn,2);
  NVIC_EnableIRQ(EXTI9_5_IRQn);

}

void USART1_Init(void){

	LL_USART_InitTypeDef USART1_InitStruct;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

	USART1_InitStruct.BaudRate=9600;
	USART1_InitStruct.DataWidth=LL_USART_DATAWIDTH_8B;
	USART1_InitStruct.HardwareFlowControl=LL_USART_HWCONTROL_NONE;
	USART1_InitStruct.OverSampling=LL_USART_OVERSAMPLING_16;
	USART1_InitStruct.Parity=LL_USART_PARITY_NONE;
	USART1_InitStruct.StopBits=LL_USART_STOPBITS_1;
	USART1_InitStruct.TransferDirection=LL_USART_DIRECTION_TX_RX;
	LL_USART_DisableOverrunDetect(USART1);
	LL_USART_DisableSCLKOutput(USART1);
	LL_USART_Init(USART1,&USART1_InitStruct);
	LL_USART_Enable(USART1);

}

void USART2_Init(void){

	LL_USART_InitTypeDef USART2_InitStruct;
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

	USART2_InitStruct.BaudRate=115200;
	USART2_InitStruct.DataWidth=LL_USART_DATAWIDTH_8B;
	USART2_InitStruct.HardwareFlowControl=LL_USART_HWCONTROL_NONE;
	USART2_InitStruct.OverSampling=LL_USART_OVERSAMPLING_8;
	USART2_InitStruct.Parity=LL_USART_PARITY_NONE;
	USART2_InitStruct.StopBits=LL_USART_STOPBITS_1;
	USART2_InitStruct.TransferDirection=LL_USART_DIRECTION_TX_RX;
	LL_USART_DisableSCLKOutput(USART2);
	LL_USART_Init(USART2,&USART2_InitStruct);
	LL_USART_Enable(USART2);

}

void I2C2_Init(void){
	LL_I2C_InitTypeDef I2C_InitStruct;
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
	LL_I2C_Disable(I2C2);
	I2C_InitStruct.AnalogFilter=LL_I2C_ANALOGFILTER_ENABLE;
	I2C_InitStruct.DigitalFilter=0x00;
	I2C_InitStruct.OwnAddrSize=LL_I2C_OWNADDRESS1_7BIT;
	I2C_InitStruct.OwnAddress1=0x02;
	I2C_InitStruct.PeripheralMode=LL_I2C_MODE_I2C;
	I2C_InitStruct.Timing=0x00B07CB4;
	I2C_InitStruct.TypeAcknowledge=LL_I2C_NACK;
	LL_I2C_Init(I2C2,&I2C_InitStruct);
	LL_I2C_Enable(I2C2);

}

void ADC_Init(void){
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	LL_GPIO_SetPinMode(GPIOC,LL_GPIO_PIN_0,LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinPull(GPIOC,LL_GPIO_PIN_0,LL_GPIO_PULL_NO);

	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC);
	//ADC_COMMON je base adresa registr� kter� je spole�n� pro v�echny prvky ADC p�evodn�ku
	//zde se definuje prescaler a clock

	LL_ADC_DisableDeepPowerDown(ADC1);
	ADC1->CR|=ADC_CR_ADVREGEN ;
	TL_TIM6_Delay(10);
	LL_ADC_StartCalibration(ADC1,LL_ADC_SINGLE_ENDED);
	while(READ_BIT(ADC1->CR,ADC_CR_ADCAL));


	ADC1_COMMON->CCR=ADC_CCR_PRESC_0;
	LL_ADC_SetDataAlignment(ADC1,LL_ADC_DATA_ALIGN_RIGHT);
	LL_ADC_SetResolution(ADC1,LL_ADC_RESOLUTION_12B);
	LL_ADC_REG_SetContinuousMode(ADC1,LL_ADC_REG_CONV_SINGLE);
	LL_ADC_REG_SetTrigSource(ADC1,LL_ADC_REG_TRIG_SW_START);
	LL_ADC_REG_SetSequencerLength(ADC1,LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS);
	LL_ADC_REG_SetDMATransfer(ADC1,LL_ADC_REG_DMA_TRANSFER_NONE);

	//vrefin
	LL_ADC_SetCommonPathInternalCh(ADC1_COMMON,LL_ADC_PATH_INTERNAL_VREFINT);
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_0);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_0, LL_ADC_SAMPLINGTIME_247CYCLES_5);

	//set channel pin
	LL_ADC_SetChannelSingleDiff(ADC1,LL_ADC_CHANNEL_9,LL_ADC_SINGLE_ENDED);
	LL_ADC_REG_SetSequencerRanks(ADC1,LL_ADC_REG_RANK_2,LL_ADC_CHANNEL_9);
	LL_ADC_SetChannelSamplingTime(ADC1,LL_ADC_CHANNEL_9,LL_ADC_SAMPLINGTIME_640CYCLES_5);

	LL_ADC_SetChannelSingleDiff(ADC1,LL_ADC_CHANNEL_10,LL_ADC_SINGLE_ENDED);
	LL_ADC_REG_SetSequencerRanks(ADC1,LL_ADC_REG_RANK_3,LL_ADC_CHANNEL_10);
	LL_ADC_SetChannelSamplingTime(ADC1,LL_ADC_CHANNEL_10,LL_ADC_SAMPLINGTIME_640CYCLES_5);


	LL_ADC_ClearFlag_ADRDY(ADC1);
	LL_ADC_Enable(ADC1);
	while(LL_ADC_IsActiveFlag_ADRDY(ADC1)==RESET);


}

void IRQ_Init(void){
	/*GPIO IRQ (AS3935)*/
	LL_EXTI_InitTypeDef EXTI_IRQ;
	EXTI_IRQ.Line_0_31=LL_EXTI_LINE_6;
	EXTI_IRQ.Mode=LL_EXTI_MODE_IT;
	EXTI_IRQ.Trigger=LL_EXTI_TRIGGER_RISING;
	EXTI_IRQ.LineCommand=ENABLE;
	LL_EXTI_Init(&EXTI_IRQ);

	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC,LL_SYSCFG_EXTI_LINE6);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_SetPriority(EXTI9_5_IRQn,1);

	/*USART1 IRQ*/
	NVIC_SetPriority(USART1_IRQn,0);
	LL_USART_EnableIT_RXNE(USART1);
	NVIC_EnableIRQ(USART1_IRQn);


	/*USART2 IRQ*/
	NVIC_SetPriority(USART2_IRQn,4);
	NVIC_EnableIRQ(USART2_IRQn);
	LL_USART_EnableIT_RXNE(USART2);

	NVIC_SetPriority(TIM7_IRQn,2);
	NVIC_EnableIRQ(TIM7_IRQn);
	LL_TIM_EnableIT_UPDATE(TIM7);

}

void TIM7_Init(){
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
	LL_TIM_InitTypeDef TIM7_Init;
	TIM7_Init.Autoreload=0xFFFFFFFFU;
	TIM7_Init.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	TIM7_Init.CounterMode=LL_TIM_COUNTERDIRECTION_UP;
	TIM7_Init.Prescaler=31999;
	TIM7_Init.RepetitionCounter=0;
	LL_TIM_Init(TIM7,&TIM7_Init);
	LL_TIM_ClearFlag_UPDATE(TIM7);

}

