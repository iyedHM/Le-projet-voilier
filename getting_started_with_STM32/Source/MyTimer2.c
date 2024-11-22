#include "MyTimer2.h"
#include "MyGPIO.h"

// Pointer to hold the function to switch LED
void (*LED_switch)(void);

// Initialize the basic timer
void MyTimer_Base_Init(MyTimer_Struct_TypeDef *Timer, unsigned short period) {
    // Calculate Prescaler (PSC)
    int PSC = (int)((period * 72e3) / 65536);  // PSC ensures the timer's counter works within 16 bits
    // Calculate Auto-Reload Register (ARR)
    unsigned int ARR = (unsigned int)((period * 72e3) / (PSC + 1));  // ARR sets the timer period

    // Enable clock for the selected timer
    if (Timer->Timer == TIM1) {
        RCC->APB2ENR |= (0x1 << 11);  // Enable clock for TIM1
    } else if (Timer->Timer == TIM2) {
        RCC->APB1ENR |= 0x1;  // Enable clock for TIM2
    } else if (Timer->Timer == TIM3) {
        RCC->APB1ENR |= (0x1 << 1);  // Enable clock for TIM3
    } else if (Timer->Timer == TIM4) {
        RCC->APB1ENR |= (0x1 << 2);  // Enable clock for TIM4
    }

    // Load the calculated ARR and PSC values into the timer
    Timer->Timer->ARR = ARR;  // Set the timer period
    Timer->Timer->PSC = PSC;  // Set the prescaler value
}

// Activate the timer interrupt (IT)
void MyTimer_ActiveIT(TIM_TypeDef *Timer, char Prio, void (*IT_function)(void)) {
    // Enable the interrupt for the selected timer
    if (Timer == TIM1) {
        Timer->DIER |= 0x01;  // Enable update interrupt for TIM1
        NVIC->ISER[0] |= (0x1 << 25);  // Enable TIM1 interrupt in NVIC
        NVIC->IPR[25] = (Prio << 4);  // Set priority for TIM1
    } else if (Timer == TIM2) {
        Timer->DIER |= 0x01;  // Enable update interrupt for TIM2
        NVIC->ISER[0] |= (0x1 << 28);  // Enable TIM2 interrupt in NVIC
        NVIC->IPR[28] = (Prio << 4);  // Set priority for TIM2
    } else if (Timer == TIM3) {
        Timer->DIER |= 0x01;  // Enable update interrupt for TIM3
        NVIC->ISER[0] |= (0x1 << 29);  // Enable TIM3 interrupt in NVIC
        NVIC->IPR[29] = (Prio << 4);  // Set priority for TIM3
    } else if (Timer == TIM4) {
        Timer->DIER |= 0x01;  // Enable update interrupt for TIM4
        NVIC->ISER[0] |= (0x1 << 30);  // Enable TIM4 interrupt in NVIC
        NVIC->IPR[30] = (Prio << 4);  // Set priority for TIM4
    }

    // Assign the interrupt service routine (ISR) function
    LED_switch = IT_function;
}

// TIM2 interrupt handler
void TIM2_IRQHandler(void) {
    TIM2->SR &= ~(0x01);  // Clear the update interrupt flag
    LED_switch();         // Call the assigned interrupt function (e.g., toggle LED)
}

// TIM3 interrupt handler
void TIM3_IRQHandler(void) {
    TIM3->SR &= ~(0x01);  // Clear the update interrupt flag
    LED_switch();         // Call the assigned interrupt function
}

// TIM1 update interrupt handler
void TIM1_UP_IRQHandler(void) {
    TIM1->SR &= ~(0x01);  // Clear the update interrupt flag
    LED_switch();         // Call the assigned interrupt function
}

// TIM4 interrupt handler
void TIM4_IRQHandler(void) {
    TIM4->SR &= ~(0x01);  // Clear the update interrupt flag
    LED_switch();         // Call the assigned interrupt function
}

void Encoder(MyTimer_Struct_TypeDef *MTimer){
MyTimer_Base_Start(TIM2);
		//enable  

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

}
