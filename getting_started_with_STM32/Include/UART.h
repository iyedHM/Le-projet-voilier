#ifndef MYUART_H
#define MYUART_H

#include "stm32f10x.h"

// ADC operation modes
#define CONTINUOUS 0x2  // Continuous conversion mode
#define SINGLE     0x1  // Single conversion mode

// Function prototypes
void MyUART_Base_Init(USART_TypeDef *MyUART);  // Initialize ADC with mode and channel
void Pin_config(USART_TypeDef *MyUART ) ;                               // Perform ADC calibration
void UART_TRANSMIT(USART_TypeDef *MyUART,char T);  
int UART_READ(USART_TypeDef *MyUART);// Read ADC value

// Macros for ADC control
#define MyADC_Base_Start(MyADC) (MyADC->CR2 |= 0x1)   // Start ADC by setting ADON bit to 1
#define MyADC_Base_Stop(MyADC)  (MyADC->CR2 &= ~0x1)  // Stop ADC by clearing ADON bit

#endif  // MYADC_H



