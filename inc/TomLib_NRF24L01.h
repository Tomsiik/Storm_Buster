/*
 * TomLib_NRF24L01.h
 *
 *  Created on: 14. 10. 2017
 *      Author: Tomsik
 * CE,CSN must be defined
 * SPI must be defined
 */



#ifndef TOMLIB_NRF24L01_H_
#define TOMLIB_NRF24L01_H_





#include "stm32l4xx.h"
#include "stm32l4xx_ll_gpio.h"

#define NRF24_CSN LL_GPIO_PIN_7	//bank B
#define NRF24_CE LL_GPIO_PIN_8 	//bank B
#define NRF24_SPI SPI1


/*NRF24 globální promìnné
 *
 *je v ní uložen Status registr a Fifostatus
 *Status_Reg se aktualizuje s každým first bytem nebo pøímým vyètením
 *FifoStatus_Reg se aktualizuje pouze vlastním pøíkazem
 */
__IO uint8_t Status_Reg;
__IO uint8_t FifoStatus_Reg;

///**************NRF24L01 registers' addresses *****************////
///************************************************************////
#define CONFIG_REG					0x00
#define ENAA_REG					0x01
#define ENRXADDR_REG 				0x02
#define SETUPAW_REG 				0x03
#define SETUPRETR_REG 				0x04
#define RFCH_REG					0x05
#define RFSETUP_REG 				0x06
#define STATUS_REG 					0x07
#define OBSERVETX_REG 				0x08
#define RPD_REG 					0x09
#define RXADDRP0_REG 				0x0A
#define RXADDRP1_REG 				0x0B
#define RXADDRP2_REG 				0x0C
#define RXADDRP3_REG 				0x0D
#define RXADDRP4_REG 				0x0E
#define RXADDRP5_REG 				0x0F
#define TXADDR_REG 					0x10
#define RXPWP0_REG 					0x11
#define RXPWP1_REG 					0x12
#define RXPWP2_REG 					0x13
#define	RXPWP3_REG 					0x14
#define RXPWP4_REG 					0x15
#define RXPWP5_REG 					0x16
#define FIFOSTATUS_REG				0x17
#define DYNPD_REG	 				0x1C
#define FEATURE_REG 				0x1D

///**************NRF24L01 registers' reset values *****************////
///************************************************************////

#define STATUS_REG_RES				0x0E
#define CONFIG_REG_RES				0x08
#define ENRXADDR_REG_RES			0x03
#define SETUPAW_REG_RES				0x03
#define SETURETR_REG_RES			0x03
#define RFCH_REG_RES				0x02
#define RFSETUP_REG_RES				0x0E
#define OBSERVETX_REG_RES			0x00
#define RPD_REG_RES					0x00
#define RXADDRP0_REG_RES			{0xE7,0xE7,0xE7,0xE7,0xE7}
#define RXADDRP1_REG_RES			{0xC2,0xC2,0xC2,0xC2,0xC2}
#define RXADDRP2_REG_RES			0xC3
#define RXADDRP3_REG_RES			0xC4
#define RXADDRP4_REG_RES			0xC5
#define RXADDRP5_REG_RES			0xC6
#define TXADDR_REG_RES				{0xE7,0xE7,0xE7,0xE7,0xE7}
#define RXPWP0_REG_RES				0x00
#define RXPWP1_REG_RES				0x00
#define RXPWP2_REG_RES				0x00
#define RXPWP3_REG_RES				0x00
#define RXPWP4_REG_RES				0x00
#define RXPWP5_REG_RES				0x00
#define FIFO_STATUS_REG				0x11
#define DYNPD_REG_RES				0x00
#define FEATURE_REG_RES				0x00


////*************NRF24L01 Commands****************////
////*********************************************////

#define R_REGISTER(reg)			(0x00 | reg)
#define W_REGISTER(reg)			(0x20 | reg)
#define R_RX_PAYLOAD_COM			0x61
#define W_TX_PAYLOAD_COM			0xA0
#define FLUSH_TX_COM				0xE1
#define FLUSH_RX_COM				0xE2
#define W_ACK_PAYLOAD				0xA8
#define W_TX_PAYLOADNOACK_COM		0xB0
#define NOP_COM						0xFF

////***********NRF24L01 bits of registers***********////
////***********************************************////

//CONFIG register
#define CONFIG_PRIMRX				0x01
#define	CONFIG_PWRUP				0x02
#define CONFIG_CRCO					0x04
#define CONFIG_ENCRC				0x08
#define CONFIG_MASKMAXRT			0x10
#define CONFIG_MASKTXDS				0x20
#define CONFIG_MASKRXDR				0x40

//EN_RXADDR register
#define ENRXADDR_ERXP0				0x01
#define ENRXADDR_ERXP1				0x02
#define ENRXADDR_ERXP2				0x04
#define ENRXADDR_ERXP3				0x08
#define ENRXADDR_ERXP4				0x10
#define ENRXADDR_ERXP5				0x20

//RF_SETUP register
#define RFSETUP_PWR_18dB			0x00
#define RFSETUP_PWR_12dB			0x02
#define RFSETUP_PWR_6dB				0x04
#define RFSETUP_PWR_0dB				0x06

#define RFSETUP_DR_250kbps			0x08
#define RFSETUP_DR_1Mbps			0x00
#define RFSETUP_DR_2Mbps			0x20

#define RFSETUP_PLLLOCK				0x10
#define RFSETUP_CONTWAVE 			0x80

//STATUS register
#define STATUS_TXFULL				0x01
#define STATUS_RXPNO_PIPE0			0x00
#define STATUS_RXPNO_PIPE1		 	0x02
#define STATUS_RXPNO_PIPE2			0x03
#define STATUS_RXPNO_PIPE3			0x04
#define STATUS_RXPNO_PIPE4			0x05
#define STATUS_RXPNO_PIPE5	 		0x06
#define STATUS_RXPNO_NOTUSED 	 	0x0C
#define STATUS_RXPNO_FIFOEMPTY		0x0E

#define STATUS_MAXRT				0x10
#define STATUS_TXDS					0x20
#define STATUS_RXDR					0x40

//FIFO_STATUS register
#define FIFOSTATUS_RXEMPTY			0x01
#define FIFOSTATUS_RXFULL			0x02
#define FIFOSTATUS_TXEMPTY			0x04
#define FIFOSTATUS_TXFULL			0x08
#define FIFOSTATUS_TX_REUSE			0x10

//DYNPD register
#define DYNPD_DPL_P0 				0x01
#define DYNPD_DPL_P1 				0x02
#define DYNPD_DPL_P2 				0x04
#define DYNPD_DPL_P3 				0x08
#define DYNPD_DPL_P4 				0x10
#define DYNPD_DPL_P5 				0x20

//SETUP_RETR register
#define SETUP_RETR_ARD_250uS		0x00
#define SETUP_RETR_ARD_500uS		0x10
#define SETUP_RETR_ARD_750uS		0x20
#define SETUP_RETR_ARD_1000uS		0x30
#define SETUP_RETR_ARD_1250uS		0x40
#define SETUP_RETR_ARD_1500uS		0x50
#define SETUP_RETR_ARD_1750uS		0x60
#define SETUP_RETR_ARD_2000uS		0x70
#define SETUP_RETR_ARD_2250uS		0x80
#define SETUP_RETR_ARD_2500uS		0x90
#define SETUP_RETR_ARD_2750uS		0xA0
#define SETUP_RETR_ARD_3000uS		0xB0
#define SETUP_RETR_ARD_3250uS		0xC0
#define SETUP_RETR_ARD_3500uS		0xD0
#define SETUP_RETR_ARD_3750uS		0xE0
#define SETUP_RETR_ARD_4000uS		0xF0

#define SETUP_RETR_ARC_REDIS		0x01
#define SETUP_RETR_ARC_RE1			0x02
#define SETUP_RETR_ARC_RE2			0x03
#define SETUP_RETR_ARC_RE3			0x04
#define SETUP_RETR_ARC_RE4			0x05
#define SETUP_RETR_ARC_RE5			0x06
#define SETUP_RETR_ARC_RE6			0x07
#define SETUP_RETR_ARC_RE7			0x08
#define SETUP_RETR_ARC_RE8			0x09
#define SETUP_RETR_ARC_RE10			0x0A
#define SETUP_RETR_ARC_RE11			0x0B
#define SETUP_RETR_ARC_RE12			0x0C
#define SETUP_RETR_ARC_RE13			0x0D
#define SETUP_RETR_ARC_RE14			0x0E
#define SETUP_RETR_ARC_RE15			0x0f


//RX_ADDR pipes register//
typedef enum {
	PIPE0 = 0x0A,	//5bytes data
	PIPE1 = 0x0B,	//5bytes data
	PIPE2 = 0x0C,	//1byte data
	PIPE3 = 0x0D,	//1byte data
	PIPE4 = 0x0E,	//1byte data
	PIPE5 = 0x0F	//1byte data
} Pipe;

typedef enum {
	PIPE0_lenght = RXPWP0_REG,	//5bytes data
	PIPE1_lenght = RXPWP1_REG,	//5bytes data
	PIPE2_lenght = RXPWP2_REG,	//1byte data
	PIPE3_lenght = RXPWP3_REG,	//1byte data
	PIPE4_lenght = RXPWP4_REG,	//1byte data
	PIPE5_lenght = RXPWP5_REG	//1byte data
} Pipe_lenght;

typedef enum {
	FLAG_ENABLE = 0x01,
	FLAG_DISABLE = 0x00
} Flag_result;




void TL_NRF24_CE_Set();
void TL_NRF24_CE_Reset();
void TL_NRF24_TXADDR_Set(uint8_t *txaddr, uint8_t count);
void TL_NRF24_TXADDR_Read(uint8_t *txaddr);
void TL_NRF24_RXADDR_Set(Pipe pipe, uint8_t *rxaddr, uint8_t count);
void TL_NRF24_RXADDR_Read(Pipe pipe, uint8_t *rxaddr, uint8_t count);
uint8_t TL_NRF24_STATUS_Read();
void TL_NRF24_CONFIG_Set(uint8_t config);
uint8_t TL_NRF24_CONFIG_Read();
void TL_NRF24_FLUSH_RX();
void TL_NRF24_FLUSH_TX();
void TL_NRF24_CHANNEL_Set(uint8_t channel);
void TL_NRF24_RX_PAYLOAD_LENGHT_Set(Pipe_lenght pipe_lenght, uint8_t lenght);
void TL_NRF24_TX_PAYLOAD_Write(uint8_t *payload, uint8_t count);
void TL_NRF24_REGISTER_Write(uint8_t reg, uint8_t data);
uint8_t TL_NRF24_REGISTER_Read(uint8_t reg);
void TL_NRF24_PAYLOAD_Send(uint8_t *payload, uint8_t count);
Flag_result TL_NRF24_GET_STATUS_FLAG(uint8_t flag);
Flag_result TL_NRF24_GET_FIFOSTATUS_FLAG(uint8_t flag);
uint8_t TL_NRF24_FIFOSTATUS_Read();
Flag_result TL_NRF24_AVAILABLE_RXFIFO();
void TL_NRF24_RX_PAYLOAD_Read(uint8_t * data,uint8_t *count);
void TL_NRF24_TX_MODE_Set();
void TL_NRF24_RX_MODE_Set();


#endif /* TOMLIB_NRF24L01_H_ */
