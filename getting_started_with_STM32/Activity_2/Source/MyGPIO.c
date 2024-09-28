#include "MyGPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
	//initialisation des clocks
	if(GPIOStructPtr->GPIO==GPIOA){
		RCC->APB2ENR |= (0x01 << 2);
	}
	if(GPIOStructPtr->GPIO==GPIOC){
		RCC->APB2ENR |= (0x01 << 4);
	}
	if(GPIOStructPtr->GPIO==GPIOB){
		RCC->APB2ENR |= (0x01 << 3);
	}
	//Initialisation du PIN
	if(GPIOStructPtr->GPIO_Pin<8){
		GPIOStructPtr->GPIO->CRL &= ~(0xF<<(GPIOStructPtr->GPIO_Pin*4));
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Conf<<(GPIOStructPtr->GPIO_Pin*4));
	}
	else{
		GPIOStructPtr->GPIO->CRH &= ~(0xF<<((GPIOStructPtr->GPIO_Pin-8)*4));
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Conf<<((GPIOStructPtr->GPIO_Pin-8)*4));
	}
}


int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	return (GPIO->IDR>>GPIO_Pin) & (0x1) ;
} // re nv oie 0 ou a u t re chose d i f f e r e n t de 0

void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	GPIO->ODR |=(0x1<<GPIO_Pin);
}
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) {
	
	GPIO->ODR &=~(0x1<<GPIO_Pin);
	
}

//Eteindre allumer LED
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ){
	if (MyGPIO_Read(GPIO,GPIO_Pin) == 1){ 
		 GPIOC->ODR &= ~(0x1<<8);
		}else{
			GPIOC->ODR |= (0x1<<8)			;
		}
}

//Configurer le TMR2
void TMR2_init(){
	RCC->APB1ENR |=0x1;
	//load ARR
	TIM2->ARR=0xFF9B;
	// load PSC
	TIM2->PSC = 549;
	//Enable 
	TIM2->CR1 |= 0x1;
	
	
	
	
	
	
}