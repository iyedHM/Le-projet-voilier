#include "MYTIM2.h"

//Configurer le TMR2
void TMR2_init(){
	// enables Timer2
	RCC->APB1ENR |=0x1;
	//load ARR
	TIM2->ARR=0xFF9B;
	// load PSC
	TIM2->PSC = 549;
	//Enable 
	TIM2->CR1 |= 0x1;
	
	
	
	
	
	
}