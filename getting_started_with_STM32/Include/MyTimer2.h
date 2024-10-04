#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"
typedef struct
{
TIM_TypeDef * Timer ; // TIM1 à TIM4
unsigned short ARR ;
unsigned short PSC ;
} MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brie f
* @param -> Paramè t r e sous forme d ’ une s t r u c t u r e ( son a d re s se ) con ten an t l e s
i n f o rm a ti o n s de base
* @Note -> F onc ti on à l a n c e r s y s t ématiquement avan t d ’ a l l e r pl u s en dé t a i l dans l e s
con f pl u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ,unsigned short periode ) ; // Periode is un ms
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio ) ;
#define MyTimer_Base_Start(Timer) (Timer->CR1 |= 0x1)
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &= ~(0x1))
#endif


