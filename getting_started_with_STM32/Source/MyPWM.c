#include "MyPWM.h"

void (*LED_swtich)(void);
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer , unsigned short periode,unsigned short duty_cycle ) {
	//Calcule PSC
	int PSC;
	PSC = ((periode*72e3)/(65536)) ;
	//Calcule ARR
	unsigned int ARR;
	ARR = ((periode*72e3)/(PSC+1));
	//Enable 
	if (Timer->Timer == TIM1) {RCC->APB2ENR |=(0x1<<11);  
		Timer->Timer->BDTR|=(0x1<<15);// the extra step to do to timer0
	}
	else if (Timer->Timer == TIM2) RCC->APB1ENR |=0x1;
		else if (Timer->Timer == TIM3) RCC->APB1ENR |=(0x1<<1);
			else if (Timer->Timer == TIM4) RCC->APB1ENR |=(0x1<<2);
	//load ARR
	Timer->Timer->ARR=ARR;
	// load PSC
	Timer->Timer->PSC = PSC;
	Timer->CCR= duty_cycle*(ARR+1)/100;
}
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio ,void (*IT_function)(void)){
	// DMA
	if(Timer==TIM1){
	Timer->DIER=(0x01);
	NVIC->ISER[0]= (0x01<<25);
	NVIC->IP[25]=(0x30);
	}
	else if(Timer==TIM2){
	Timer->DIER=(0x01);
	NVIC->ISER[0]= (0x01<<28);
	NVIC->IP[28]=(0x30);
	}
	else if(Timer==TIM3){
	Timer->DIER=(0x01);
	NVIC->ISER[0]= (0x01<<29);
	NVIC->IP[29]=(0x30);
	}
	else if(Timer==TIM4){
	Timer->DIER=(0x01);
	NVIC->ISER[0]= (0x01<<30);
	NVIC->IP[30]=(0x30);
	}
	LED_swtich=IT_function;

}
//Handlers interruptions
void TIM2_IRQHandler(void) {
	
	TIM2->SR&=~(0x01);
	LED_swtich();
	
}
void TIM3_IRQHandler(void) {
	TIM3->SR&=~(0x01);
	LED_swtich();
	
}
void TIM1_UP_IRQHandler(void) {
	TIM1->SR&=~(0x01);
  LED_swtich();
	
}
void TIM4_IRQHandler(void) {
	TIM4->SR&=~(0x01);
	LED_swtich();
	
}
void MyTimer_PWM( MyTimer_Struct_TypeDef * Timer , char Channel ) {
	if ( Channel==1 ){
Timer->Timer->CCR1=Timer->CCR;
		
}else if(Channel==2){
Timer->Timer->CCR2=Timer->CCR;
} 
else if(Channel==3){
Timer->Timer->CCR3=Timer->CCR;
} 
else if(Channel==4){
Timer->Timer->CCR4=Timer->CCR;
}
		
	// configuration channel 
	Timer->Timer->CCER|=(0x1)<<((Channel-1)*4);
	//in case you want polarity(you want the PWM upside down)
	// Timer->CCER|=(0x2)<<(Channel-1)*4);
	
	//PWM configuration 
	if ( Channel==1 || Channel==2){
	//OC1PE :Output compare 2 preload enable
	Timer->Timer->CCMR1|=(0x1)<<((Channel-1)*8+3); 
	//OCM1 :Output compare 1 mode
	Timer->Timer->CCMR1&=~((0x7)<<((Channel-1)*8+4));//reset to 0
	Timer->Timer->CCMR1|=(0x6)<<((Channel-1)*8+4); 
	
	}else 
	if (Channel==3 || Channel==4){
	//OC1PE :Output compare 2 preload enable
	Timer->Timer->CCMR2|=(0x1)<<((Channel-3)*8+3); 
	//OCM1 :Output compare 1 mode
	Timer->Timer->CCMR2&=~((0x7)<<((Channel-3)*8+4));//reset to 0
	Timer->Timer->CCMR2|=(0x6)<<((Channel-3)*8+4); 
	}
	//I want to use P110
	
	
	
}


