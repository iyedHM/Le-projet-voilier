#ifndef MYADC_H
#define MYADC_H

#include "stm32f10x.h"

// ADC operation modes
#define CONTINUOUS 0x2  // Continuous conversion mode
#define SINGLE     0x1  // Single conversion mode

// Function prototypes
void MyADC_Base_Init(ADC_TypeDef *MyADC, char mode, uint8_t channel);  // Initialize ADC with mode and channel
void Calibration(ADC_TypeDef *MyADC);                                  // Perform ADC calibration
int ADC_read(void);                                                    // Read ADC value

// Macros for ADC control
#define MyADC_Base_Start(MyADC) (MyADC->CR2 |= 0x1)   // Start ADC by setting ADON bit to 1
#define MyADC_Base_Stop(MyADC)  (MyADC->CR2 &= ~0x1)  // Stop ADC by clearing ADON bit

#endif  // MYADC_H



