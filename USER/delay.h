/*
  ******************************************************************************
  * @file		delay.h                                         
  * @author	Duong Xuan Dang                                                      
  * @date		11/25/2025                                                         
  ******************************************************************************
*/
	
#ifndef __DELAY_H__
#define __DELAY_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

void Sys_Init(void);
void Sys_Delay_ms(uint32_t msTime);
void Sys_Delay_s(uint32_t sTime);
uint32_t Sys_mililis(void);
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/