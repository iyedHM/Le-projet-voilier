#include "MyTimer2.h"

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer , unsigned short periode ) {
	//Calcule PSC*
	int PSC;
	PSC = ((periode*72e3)/(65536)) ;
	//Calcule ARR
	unsigned int ARR;
	ARR = ((periode*72e3)/(PSC+1));
	//Enable 
	if (Timer->Timer == TIM1) RCC->APB2ENR |=(0x1<<11);  
	else if (Timer->Timer == TIM2) RCC->APB1ENR |=0x1;
		else if (Timer->Timer == TIM3) RCC->APB1ENR |=(0x1<<1);
			else if (Timer->Timer == TIM4) RCC->APB1ENR |=(0x1<<2);
	//load ARR
	Timer->Timer->ARR=ARR;
	// load PSC
	Timer->Timer->PSC = PSC;
}
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio ){
	// DMA
	if(Timer==TIM1){
	Timer->DIER=(0x01);
	NVIC->ISER[0]= (0x01<<25);
	NVIC->IPR[25]=(0x30);
	}
	else if(Timer==TIM2){
	Timer->DIER=(0x01);
	NVIC->ISER[0]= (0x01<<28);
	NVIC->IPR[28]=(0x30);
	}
	else if(Timer==TIM3){
	Timer->DIER=(0x01);
	NVIC->ISER[0]= (0x01<<29);
	NVIC->IPR[29]=(0x30);
	}
	else if(Timer==TIM4){
	Timer->DIER=(0x01);
	NVIC->ISER[0]= (0x01<<30);
	NVIC->IPR[30]=(0x30);
	}

}