#ifndef MYPWM_H
#define MYPWM_H
#include "stm32f10x.h"
typedef struct
{
TIM_TypeDef * Timer ; // TIM1 � TIM4
unsigned short ARR ;
unsigned short PSC ;
unsigned short CCR ;
} MyTimer_Struct_TypeDef ;
/*
*****************************************************************************************
* @brief
* @param -> Param� t r e sous forme d � une s t r u c t u r e ( son a d re s se ) con ten an t l e s
i n f o rm a ti o n s de base
* @Note -> F onc ti on � l a n c e r s y s t �matiquement avan t d � a l l e r pl u s en d� t a i l dans l e s
con f pl u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer , unsigned short periode,unsigned short duty_cycle ) ; // Periode is un ms
void MyTimer_ActiveIT ( TIM_TypeDef * Timer , char Prio ,void (*IT_function)(void)) ;
#define MyTimer_Base_Start(Timer) (Timer->CR1 |= 0x1)
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &= ~(0x1))
//PWM PART
/***
	* @brief
	* @param . . . .
	* @Note Activele channel sp�cifi� suTimerr le timer sp�cifi�
	* la gestion de la configuration I /On�est pas faite dans cette fonction
	* ni le r�glage de la p�riode de la PWM (ARR, PSC)
*/
void MyTimer_PWM( MyTimer_Struct_TypeDef * Timer , char Channel ) ;
#endif


