#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyTimer2.h"
 
 void (*IT_function)(void);
 void LED_switch (void);
int main ( void )
{
	//configuration de GPIOC_8 comme sortie
	MyGPIO_Struct_TypeDef  insMGPIO_C8;
	MyGPIO_Struct_TypeDef * MGPIO_C8=&insMGPIO_C8 ; 
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
	
	//Call_back
	IT_function=LED_switch;
	MyTimer_Base_Init ( MTimer_2 , 500);
	MyTimer_ActiveIT(TIM1,3,IT_function);
	
	
	
	

	while (1)
	{
		MyTimer_Base_Start(MTimer_2->Timer);
		
	}

}
void LED_switch (void){
	//configuration de GPIOC_8 comme sortie
	MyGPIO_Struct_TypeDef  insMGPIO_C8;
	MyGPIO_Struct_TypeDef * MGPIO_C8=&insMGPIO_C8 ; 
	MGPIO_C8->GPIO=GPIOC;
	MGPIO_C8->GPIO_Pin=8;
	MGPIO_C8->GPIO_Conf=Out_Ppull;
	MyGPIO_Toggle(MGPIO_C8->GPIO,MGPIO_C8->GPIO_Pin) ;
}
