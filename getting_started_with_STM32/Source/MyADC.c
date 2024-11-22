#include "MyADC.h"

// Initialize the ADC base configuration
void MyADC_Base_Init(ADC_TypeDef *MyADC, char mode, uint8_t channel) {
    // Enable clock for the selected ADC
    if (MyADC == ADC1) {
        RCC->APB2ENR |= (0x1 << 9);  // Enable clock for ADC1
    } else if (MyADC == ADC2) {
        RCC->APB2ENR |= (0x1 << 10); // Enable clock for ADC2
    } else if (MyADC == ADC3) {
        RCC->APB2ENR |= (0x1 << 15); // Enable clock for ADC3
    }
    // Set ADC prescaler
    RCC->CFGR &= ~(0x3 << 14);   // Clear prescaler bits
    RCC->CFGR |= (0x2 << 14);    // Set ADC prescaler to 6
    RCC->CFGR &= ~(0x7 << 11);   // Clear APB2 prescaler

    // Set mode (Continuous or Single)
    if (mode == CONTINUOUS) {
        MyADC->CR2 |= CONTINUOUS;   // Enable continuous mode
    } else if (mode == SINGLE) {
        MyADC->CR2 &= ~(SINGLE << 1);  // Enable single conversion mode
    }
		
		
		
		Calibration(ADC1);
		MyADC_Base_Start(ADC1);
   	while (ADC1->CR2 & ADC_CR2_CAL);  // Wait for calibration to complete
		
		                   // Enable ADC1
		
    // Set sampling time for the selected channel(fot this code 28.5 cycles)
    if (channel < 10) {
        MyADC->SMPR2 |= (3 << (channel * 3));  // Set sampling time for channels 0-9
    } else {
        MyADC->SMPR2 |= (3 << ((channel - 10) * 3));  // Set sampling time for channels 10-17
    }

    // Configure sequence
    MyADC->SQR1 &= ~(0xF << 20);  // 1 conversion in the regular sequence
    MyADC->SQR3 &= ~(0x1F);       // Clear sequence register (set to channel 0 by default)

    // External event selection and start conversion
    MyADC->CR2 |= (0x7 << 17);    // Select SWSTART as external event
   MyADC->CR2 |= (0x1 << 22);    // external trigger 
		
}


// Calibrate the ADC
void Calibration(ADC_TypeDef *MyADC) {
    MyADC->CR2 |= (1 << 2);   // Start calibration
}

// Read ADC value
int ADC_read(void) {
		ADC1->CR2 |= ADC_CR2_SWSTART;
    // Return the data register value after conversion completes
    return ADC1->DR;
}
