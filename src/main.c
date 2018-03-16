

#include "main.h"
#include "Periph_Init.h"



int main(void) {
	SystemClock_Config();
	SPI2_Init();
	USART2_Init();
	I2C2_Init();
	while (1) {


	}
}




