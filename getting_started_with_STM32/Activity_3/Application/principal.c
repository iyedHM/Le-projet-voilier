#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyADC.h"
#include "MyTimer2.h"

// Global variable to store ADC measurement
int measure;

int main(void) {
    // GPIO configuration: Set GPIOA Pin 1 as Analog input
    MyGPIO_Struct_TypeDef GPIOA_Analog_Pin1_Config;
    MyGPIO_Struct_TypeDef *GPIOA_Analog_Pin1 = &GPIOA_Analog_Pin1_Config; // Pointer to GPIO configuration structure

    GPIOA_Analog_Pin1->GPIO = GPIOA;             // Set GPIO port to GPIOA
    GPIOA_Analog_Pin1->GPIO_Pin = 0;             // Set GPIO pin to 1 (PA1)
    GPIOA_Analog_Pin1->GPIO_Conf = In_Analog;    // Set pin configuration to Analog input
    
    // Initialize GPIOA Pin 1 as Analog
    MyGPIO_Init(GPIOA_Analog_Pin1);

    // Start ADC configuration
	  MyADC_Base_Init(ADC1, CONTINUOUS, 0);  // Initialize ADC1 in continuous mode for channel 0
    
        

    // Calibrate ADC1
    //while (ADC1->CR2 & ADC_CR2_RSTCAL)	;
   
    // Main loop
    while (1) {   // Trigger conversion with software start (SWSTART)

        measure = ADC_read();          // Read ADC value and store it in 'measure'

        // Add any processing logic for 'measure' if needed
    
    }
}
// this code has a problem any affectation to ADC1->CR2 end uo trigerring the Conversion so look into that weird thing 