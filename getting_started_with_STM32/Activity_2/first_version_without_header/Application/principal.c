#include "stm32f10x.h"
#include "MyGPIO.h"
#include "MYTIM2.h"

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
	
	TMR2_init();
	
	int k;
	while (1)
	{
		k=(TIM2->SR) & 0x1;
		if (k==1){
		 MyGPIO_Toggle(MGPIO_C8->GPIO,MGPIO_C8->GPIO_Pin) ;
			TIM2->SR &= ~(0x1);
		}
	}
}
