#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer2.h"
 
MyGPIO_Struct_TypeDef  insMGPIO_C8;
MyGPIO_Struct_TypeDef * MGPIO_C8=&insMGPIO_C8 ; 
int main ( void )
{
	//configuration de GPIOC_8 comme sortie

	MGPIO_C8->GPIO=GPIOC;
	MGPIO_C8->GPIO_Pin=8;
	MGPIO_C8->GPIO_Conf=Out_Ppull;
	
	//configuration de GPIOC_9 comme entree
	MyGPIO_Struct_TypeDef  insMGPIO_C9;
	MyGPIO_Struct_TypeDef * MGPIO_C9=&insMGPIO_C9 ; 
	MGPIO_C9->GPIO=GPIOC;
	MGPIO_C9->GPIO_Pin=9;
	MGPIO_C9->GPIO_Conf=In_PullDown;
	
	
	MyGPIO_Init(MGPIO_C8);
	MyGPIO_Init(MGPIO_C9);
	
	//configuration timer 
	MyTimer_Struct_TypeDef insMTimer_2;
	MyTimer_Struct_TypeDef * MTimer_2=&insMTimer_2 ; 
	MTimer_2->Timer=TIM1;
	
	MyTimer_Base_Init ( MTimer_2 , 500);
	MyTimer_ActiveIT(TIM1,3);
	
	
	

	while (1)
	{
		MyTimer_Base_Start(MTimer_2->Timer);
		
	}

}
void TIM2_IRQHandler(void) {
	TIM2->SR&=~(0x01);
	MyGPIO_Toggle(MGPIO_C8->GPIO,MGPIO_C8->GPIO_Pin) ;
	
}
void TIM3_IRQHandler(void) {
	TIM3->SR&=~(0x01);
	MyGPIO_Toggle(MGPIO_C8->GPIO,MGPIO_C8->GPIO_Pin) ;
	
}
void TIM1_UP_IRQHandler(void) {
	TIM1->SR&=~(0x01);
	MyGPIO_Toggle(MGPIO_C8->GPIO,MGPIO_C8->GPIO_Pin) ;
	
}
void TIM4_IRQHandler(void) {
	TIM4->SR&=~(0x01);
	MyGPIO_Toggle(MGPIO_C8->GPIO,MGPIO_C8->GPIO_Pin) ;
	
}
