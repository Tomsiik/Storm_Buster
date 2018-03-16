/*
 * TomLib_NRF24L01.c#
 *
 *  Created on: 14. 10. 2017
 *      Author: Tomsik
 */

/* NRF24L01 knihovna
 * poskytuje funkce ke komunikaci a konfiguraci bezdr�tov�ho NRF24L01 modulu.
 * k t�to knihovn� se p�ipojuj� i hlavi�kov� soubory knihoven TomLib_SPI.h a TomLib_SYS.h
 * v hlavi�kov�m souboru TomLib_NRF24L01.h je nutn� specifikovat definici pro vyu��vanou SPI
 * a specifikovat pin CE a CSN
 */

#include"TomLib_SPI.h"
#include"TomLib_NRF24L01.h"
#include "TomLib_SYS.h"

/*	Obsluha CE
 *
 */
void TL_NRF24_CE_Set() {
	LL_GPIO_SetOutputPin(GPIOB, NRF24_CE);
}


/*Obsluha CE
 *
 */
void TL_NRF24_CE_Reset() {
	LL_GPIO_ResetOutputPin(GPIOB, NRF24_CE);
}



/*	Nastaveni TX adresy
 *
 * 	je pot�eba vlo�it pole o 5ti uint8_t hodnot
 * 	napriklad uint8_t txaddr[5]={0xE7,0xE7,0xE7,0xE7,0xE7,};
 */
void TL_NRF24_TXADDR_Set(uint8_t *txaddr, uint8_t count) {

	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,W_REGISTER(TXADDR_REG)); //zapis prvn�ho bytu (command nebo register) plus vy��t�n� status registru
	TL_SPI_Transmit_Multi(NRF24_SPI,txaddr, count);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/*	�ten� TX adresy
 *
 * 	return: field[5] uint8_t
 */
void TL_NRF24_TXADDR_Read(uint8_t *txaddr) {

	uint8_t dummy[5] = { 0, 0, 0, 0, 0 };
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,R_REGISTER(TXADDR_REG));
	TL_SPI_ReceiveTransmit_Multi(NRF24_SPI,dummy, txaddr, sizeof(dummy));
	TL_SPI_Set_CSN(NRF24_CSN);
}


/*	Nastaveni RX adresy pipu
 * 	pipe	PIPE0
 * 			PIPE1
 * 			PIPE2
 * 			PIPE3
 * 			PIPE4
 * 			PIPE5
 *	PIPE0 a PIPE1 je 32 bitovy!
 *	PIPE2 az PIPE5 je 8 bitovy!
 *	je pot�eba vlo�it pole o 5ti uint8_t hodnot
 * 	napriklad uint8_t rxaddr[5]={0xE7,0xE7,0xE7,0xE7,0xE7,};
 */
void TL_NRF24_RXADDR_Set(Pipe pipe, uint8_t *rxaddr, uint8_t count) {

	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,W_REGISTER(pipe));
	TL_SPI_Transmit_Multi(NRF24_SPI,rxaddr, count);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/*	�ten� RX adresy zvolen�ho pipu
 *  pipe	PIPE0
 * 			PIPE1
 * 			PIPE2
 * 			PIPE3
 * 			PIPE4
 * 			PIPE5
 *	PIPE0 a PIPE1 je 32 bitovy!
 *	PIPE2 az PIPE5 je 8 bitovy!
 *	return: 5 byt� pro PIPE0 a PIPE1
 *	return: 1 byte pro PIPE2 az PIPE5
 */
void TL_NRF24_RXADDR_Read(Pipe pipe, uint8_t *rxaddr, uint8_t count) {

	uint8_t dummy[5] = { 0, 0, 0, 0, 0 };
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,R_REGISTER(pipe));
	TL_SPI_ReceiveTransmit_Multi(NRF24_SPI,dummy, rxaddr, count);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/* 	�ten� Status registru
 *
 * 	aktualizuje glob�ln� prom�nnou Status_Reg
 * 	return: uint8_t
 */
uint8_t TL_NRF24_STATUS_Read() {

	uint8_t status;
	TL_SPI_Reset_CSN(NRF24_CSN);
	status = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,STATUS_REG);
	TL_SPI_Set_CSN(NRF24_CSN);
	Status_Reg=status;
	return status;
}


/* 	Nastaven� Config registru
 *
 * 	do parametru se vkl�d� p��mo n�zev bitu kter� chceme povolit
 * 	nap��klad CONFIG_PRIMRX	| CONFIG_PWRUP | CONFIG_ENCRC
 */
void TL_NRF24_CONFIG_Set(uint8_t config) {

	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,W_REGISTER(CONFIG_REG));
	TL_SPI_Transmit_Byte(NRF24_SPI,config);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/* 	�ten� Config registru
 *
 * 	return: uint8_t
 */
uint8_t TL_NRF24_CONFIG_Read() {

	uint8_t config = 0;
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,R_REGISTER(CONFIG_REG));
	config = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,0x00);
	TL_SPI_Set_CSN(NRF24_CSN);
	return config;
}


/*	Vyma�e RX payload
 *
 */
void TL_NRF24_FLUSH_RX() {
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,FLUSH_RX_COM);
	TL_SPI_Set_CSN(NRF24_CSN);
}

/*	Vyma�e RX payload
 *
 */
void TL_NRF24_FLUSH_TX() {
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,FLUSH_TX_COM);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/*	Nastaven� kan�lu
 *
 */
void TL_NRF24_CHANNEL_Set(uint8_t channel) {

	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,W_REGISTER(RFCH_REG));
	TL_SPI_Transmit_Byte(NRF24_SPI,channel);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/*	Nastaven� d�lky zvolen�ho rx pipu
 * 	5:0 bit
 * 	lze nastavit 1 a� 32
 * 	1=1 byte d�lka
 * 	.
 *	.
 * 	32=32 byte d�lka
 */
void TL_NRF24_RX_PAYLOAD_LENGHT_Set(Pipe_lenght pipe_lenght, uint8_t lenght) {

	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,W_REGISTER(pipe_lenght));
	TL_SPI_Transmit_Byte(NRF24_SPI,lenght);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/*	Z�pis do tx payloadu
 *
 */
void TL_NRF24_TX_PAYLOAD_Write(uint8_t *payload, uint8_t count) {
	TL_NRF24_CE_Reset();
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,W_TX_PAYLOAD_COM);
	TL_SPI_Transmit_Multi(NRF24_SPI,payload, count);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/*	Z�pis registru
 *
 */
void TL_NRF24_REGISTER_Write(uint8_t reg, uint8_t data) {
	TL_NRF24_CE_Reset();
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,W_REGISTER(reg));
	TL_SPI_Transmit_Byte(NRF24_SPI,data);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/*	�ten� registru
 *
 * 	return: uint8_t
 */
uint8_t TL_NRF24_REGISTER_Read(uint8_t reg) {

	uint8_t data = 0;
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,R_REGISTER(reg));
	data = TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,0x00);
	TL_SPI_Set_CSN(NRF24_CSN);
	return data;
}


/*	Zap�e data do payloadu a ode�le je
 *
 */
void TL_NRF24_PAYLOAD_Send(uint8_t *payload, uint8_t count){
	TL_NRF24_CE_Reset();
	TL_NRF24_FLUSH_TX();
	TL_NRF24_TX_PAYLOAD_Write(payload, count);
	TL_NRF24_CONFIG_Set(CONFIG_PWRUP | CONFIG_ENCRC | CONFIG_MASKRXDR);
	TL_NRF24_CE_Set();
	TL_uDelay(50);
	TL_NRF24_CE_Reset();
}


/*	Z�sk� flag ze status registru
 *
 *	return: FLAG_DISABLE nebo FLAG ENABLE
 */
Flag_result TL_NRF24_GET_STATUS_FLAG(uint8_t flag) {
	if ((Status_Reg & flag) == flag) {
		return FLAG_ENABLE;
	} else {
		return FLAG_DISABLE;
	}
}


/*	�te fifostatus flag
 *
 *	return: FLAG_DISABLE nebo FLAG ENABLE
 */
Flag_result TL_NRF24_GET_FIFOSTATUS_FLAG(uint8_t flag) {

	if ((FifoStatus_Reg & flag) == flag) {
		return FLAG_ENABLE;
	} else {
		return FLAG_DISABLE;
	}
}


/*	�te fifostatus registr
 *
 * 	return: uint8_t
 */
uint8_t TL_NRF24_FIFOSTATUS_Read() {

	uint8_t fifostatus;
	TL_SPI_Reset_CSN(NRF24_CSN);
	TL_SPI_Transmit_Byte(NRF24_SPI,R_REGISTER(FIFOSTATUS_REG));
	fifostatus=TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,0x00);
	TL_SPI_Set_CSN(NRF24_CSN);
	FifoStatus_Reg=fifostatus;
	return fifostatus;
}


/*	Z�sk� flag o dostupn�ch datech v RX fifu
 *
 */
Flag_result TL_NRF24_AVAILABLE_RXFIFO() {
	TL_NRF24_STATUS_Read();
	if (TL_NRF24_GET_STATUS_FLAG(STATUS_RXDR) == FLAG_ENABLE) {
		TL_NRF24_FIFOSTATUS_Read();
		if (TL_NRF24_GET_FIFOSTATUS_FLAG(FIFOSTATUS_RXEMPTY) == FLAG_DISABLE) {
			return FLAG_ENABLE;
		} else {
			return FLAG_DISABLE;
		}
	} else {
		return FLAG_DISABLE;
	}
}


/*	�te RX payload
 *
 * 	ma�e flag o p�ijat�ch datech ve status registru
 * 	ma�e rx payload po �ten�
 * 	return: field uint8_t
 */
void TL_NRF24_RX_PAYLOAD_Read(uint8_t *data,uint8_t *count){
	uint8_t dummy_p[255];
	for(int i=0;i<255;i++){
		dummy_p[i]=0x00;
	}

	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg=TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,R_RX_PAYLOAD_COM);
	TL_SPI_ReceiveTransmit_Multi(NRF24_SPI,dummy_p,data,count);
	TL_SPI_Set_CSN(NRF24_CSN);
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg=TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,W_REGISTER(STATUS_REG));
	TL_SPI_Transmit_Byte(NRF24_SPI,Status_Reg|STATUS_RXDR);
	TL_SPI_Set_CSN(NRF24_CSN);
	TL_SPI_Reset_CSN(NRF24_CSN);
	Status_Reg=TL_SPI_ReceiveTransmit_Byte(NRF24_SPI,FLUSH_RX_COM);
	TL_SPI_Set_CSN(NRF24_CSN);
}


/*	Nastavuje NRF24 do Tx modu
 *
 */
void TL_NRF24_TX_MODE_Set(){
	TL_NRF24_CONFIG_Set(CONFIG_PWRUP|CONFIG_ENCRC);
}


/*	Nastavuje NRF24 do Rx modu
 *
 */
void TL_NRF24_RX_MODE_Set(){
	TL_NRF24_CONFIG_Set(CONFIG_PRIMRX|CONFIG_PWRUP|CONFIG_ENCRC);
	TL_mDelay(2);
	TL_NRF24_CE_Set();
}
