#include "stm32f10x.h"

#include "UART.h"



// Global variable to store ADC measurement
int measure;

int main(void) {
	MyUART_Base_Init(USART2);
	char D;
	/*
	char T[]="Hamrouni iyed";
for(unsigned int i=0;i<sizeof(T);i++){
UART_TRANSMIT(USART2,T[i]);
}
*/
	
	
    while (1) { 
			D=UART_READ(USART2);
	UART_TRANSMIT(USART2,D);
			
    }
}
// this code has a problem any affectation to ADC1->CR2 end uo trigerring the Conversion so look into that weird thing 