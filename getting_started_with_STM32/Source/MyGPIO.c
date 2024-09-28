#include "MyGPIO.h"

void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) {
	GPIOA->CRL &= ~(0xF<<4) ;
	GPIOA->CRL |= (0x2<<4) ;
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
 
		GPIO->ODR ^= (0x1<<GPIO_Pin) ;
		
}