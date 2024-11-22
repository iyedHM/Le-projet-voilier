#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MyPWM.h"
 
 void (*IT_function)(void);
 void LED_switch (void);
int main ( void )

{
	//configuration de GPIOB_10 comme sortie
	MyGPIO_Struct_TypeDef  insMGPIO_B10;
	MyGPIO_Struct_TypeDef * MGPIO_B10=&insMGPIO_B10 ; 
	MGPIO_B10->GPIO=GPIOB;
	MGPIO_B10->GPIO_Pin=0;
	MGPIO_B10->GPIO_Conf=AltOut_Ppull;
	
	//configuration de GPIOA_10 comme entree
	MyGPIO_Struct_TypeDef  insMGPIO_A10;
	MyGPIO_Struct_TypeDef * MGPIO_A10=&insMGPIO_A10 ; 
	MGPIO_A10->GPIO=GPIOA;
	MGPIO_A10->GPIO_Pin=7;
	MGPIO_A10->GPIO_Conf=AltOut_Ppull;
	
	
	MyGPIO_Init(MGPIO_B10);
	MyGPIO_Init(MGPIO_A10);
	
	//configuration timer 
	MyTimer_Struct_TypeDef insMTimer_2;
	MyTimer_Struct_TypeDef * MTimer_2=&insMTimer_2 ; 
	MTimer_2->Timer=TIM3;
	
	//Call_back
	IT_function=LED_switch;
	MyTimer_Base_Init ( MTimer_2 , 500,25);
	MyTimer_PWM( MTimer_2 , 2 );
	
	
	
	

	while (1)
	{
		MyTimer_Base_Start(MTimer_2->Timer);//Enabl timer 
		
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
