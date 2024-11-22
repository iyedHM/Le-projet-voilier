#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"
typedef struct
{
TIM_TypeDef * Timer ; // TIM1 à TIM4
unsigned short ARR ;
unsigned short PSC ;
} MyTimer_Struct_TypeDef ;

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ,unsigned short periode ) ; // Periode is un ms
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio ,void (*IT_function)(void)) ;
void Encoder(MyTimer_Struct_TypeDef *MTimer);
#define MyTimer_Base_Start(Timer) (Timer->CR1 |= 0x1)
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &= ~(0x1))
#endif


