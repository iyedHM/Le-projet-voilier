#include "UART.h"
#include "MyGPIO.h"
// Initialize the UART base configuration
void MyUART_Base_Init(USART_TypeDef *MyUART){  // Initialize ADC with mode and channel
//Clock enable
	if (MyUART==USART1){
	RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
 }
	else if (MyUART==USART2){
	RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
	}else if(MyUART==USART3){
	RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
	}
	MyUART->CR1|=USART_CR1_UE; //Enable
//MyUART->CR1|=USART_CR1_M; //if we want 9 bits transmission
MyUART->CR2|=USART_CR2_STOP_1; // change the stop bit to 2 stopbits
//Clock
if (MyUART==USART1){
RCC->CFGR&=~RCC_CFGR_PPRE2_DIV1 ; // PLCK2 divided by 1(72Mhz)
MyUART->BRR|=(468<<4)+12; // 9600 baudrate
}else{
RCC->CFGR&=~RCC_CFGR_PPRE1_DIV1; //PLCK1 divided by 1(32MHz)
MyUART->BRR|=(234<<4)+12; // 9600 baudrate
}
//Clock parity 
if (!(MyUART==UART4 || MyUART==UART5)){
MyUART->CR1|=USART_CR1_PCE;
}
//Enable Transmission
MyUART->CR1|=USART_CR1_TE;
//Enable Receive
MyUART->CR1|=USART_CR1_RE;
Pin_config(MyUART);


}

//transmission
//TX configuration 
void Pin_config(USART_TypeDef *MyUART){
	if (MyUART == USART2){
	  MyGPIO_Struct_TypeDef GPIOA_OUT_ALT_Pin2_Config;
    MyGPIO_Struct_TypeDef *GPIOA_OUT_ALT_Pin2 = &GPIOA_OUT_ALT_Pin2_Config; // Pointer to GPIO configuration structure

    GPIOA_OUT_ALT_Pin2->GPIO = GPIOA;             // Set GPIO port to GPIOA
    GPIOA_OUT_ALT_Pin2->GPIO_Pin = 2;             // Set GPIO pin to 2 (PA2)
    GPIOA_OUT_ALT_Pin2->GPIO_Conf = Out_Ppull;    // Set pin configuration to Analog input
		MyGPIO_Init(GPIOA_OUT_ALT_Pin2);
		
		MyGPIO_Struct_TypeDef GPIOA_IN_ALT_Pin3_Config;
    MyGPIO_Struct_TypeDef *GPIOA_IN_ALT_Pin3 = &GPIOA_IN_ALT_Pin3_Config; // Pointer to GPIO configuration structure

    GPIOA_IN_ALT_Pin3->GPIO = GPIOA;             // Set GPIO port to GPIOA
    GPIOA_IN_ALT_Pin3->GPIO_Pin = 3;             // Set GPIO pin to 2 (PA2)
    GPIOA_IN_ALT_Pin3->GPIO_Conf = In_PullDown;    // Set pin configuration to Analog input
		MyGPIO_Init(GPIOA_IN_ALT_Pin3);
		
	}


}
void UART_TRANSMIT(USART_TypeDef *MyUART,char  T){

	MyUART->DR=(int)T;
	while(((MyUART->SR >> 7) & 0x1) ==0);
}
int UART_READ(USART_TypeDef *MyUART){

	while(((MyUART->SR >> 5) & 0x1) ==0);
	return(MyUART->DR);
	
}

	