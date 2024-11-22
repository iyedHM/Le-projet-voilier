#include "stm32f10x.h"

#include "UART.h"

#include "MyTimer2.h"

#include "MyGPIO.h"
// Global variable to store ADC measurement
int measure;

int main(void) {
	MyTimer_Base_Start(TIM2);
		//enable  
	MyTimer_Struct_TypeDef insMTimer;
	MyTimer_Struct_TypeDef * MTimer=&insMTimer ; 
	MTimer->Timer=TIM2;
	
	MyTimer_Base_Init(MTimer, 1) ;
	//PREP
	TIM2->SMCR|=(TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0);
	TIM2->CCER|=TIM_CCER_CC1E;
	TIM2->CCER|=TIM_CCER_CC2E;
	//mapping 
	TIM2->CCMR1|=TIM_CCMR1_CC1S_1;
	TIM2->CCMR1|=TIM_CCMR1_CC2S_1;

	//GPIO mapping 
		MyGPIO_Struct_TypeDef GPIOA_CH1_ALT_Pin0_Config;
	MyGPIO_Struct_TypeDef *GPIOA_CH1_ALT_Pin0 = &GPIOA_CH1_ALT_Pin0_Config; // Pointer to GPIO configuration structure

	GPIOA_CH1_ALT_Pin0->GPIO = GPIOA;             // Set GPIO port to GPIOA
	GPIOA_CH1_ALT_Pin0->GPIO_Pin = 0;             // Set GPIO pin to 2 (PA2)
	GPIOA_CH1_ALT_Pin0->GPIO_Conf = In_PullDown;    // Set pin configuration to Analog input
	MyGPIO_Init(GPIOA_CH1_ALT_Pin0);
	
	MyGPIO_Struct_TypeDef GPIOA_CH2_ALT_Pin1_Config;
	MyGPIO_Struct_TypeDef *GPIOA_CH2_ALT_Pin1 = &GPIOA_CH2_ALT_Pin1_Config; // Pointer to GPIO configuration structure

	GPIOA_CH2_ALT_Pin1->GPIO = GPIOA;             // Set GPIO port to GPIOA
	GPIOA_CH2_ALT_Pin1->GPIO_Pin = 1;             // Set GPIO pin to 2 (PA2)
	GPIOA_CH2_ALT_Pin1->GPIO_Conf = In_PullDown;    // Set pin configuration to Analog input
	MyGPIO_Init(GPIOA_CH2_ALT_Pin1);
	// For this part i thought it would more efficient to use externall interruption for this because i don't see how i'l gonna catch my a 360 electrical periode and instead of using capture for a timer 
	// that i may need i choose to configure AFIO and find the appropriate way to configure the EXIT register to catch the rising edges 
	//polarity
    MTimer->Timer->CCMR1 &= ~TIM_CCMR1_IC1F;
    MTimer->Timer->CCER &= ~TIM_CCER_CC1P ;
    MTimer->Timer->CCMR1 &= ~TIM_CCMR1_IC2F;
    MTimer->Timer->CCER &= ~TIM_CCER_CC2P ;
		MTimer->Timer->CNT &= 0;
		

	
	
    while (1) { 
			if (( MTimer->Timer->CR1 & TIM_CR1_DIR) == 0) {
    
} else {
  
}
			

    }
}
