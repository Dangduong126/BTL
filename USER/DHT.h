/*
  ******************************************************************************
  * @file		DHT.h                                         
  * @author	Duong Xuan Dang
	* @brief   This file provides the necessary functions to program sensor DHT11
  * @date		10/06/2026                                                         
  ******************************************************************************
*/
	
#ifndef __DHT_H__
#define __DHT_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

#define DHT11_PIN GPIO_Pin_12
#define DHT11_GPIO GPIOA

void DHT11_Init(void);
void DHT11_SetOutput(void);
void DHT11_SetInput(void);
void DHT11_Start(void);
uint8_t DHT11_CheckResponse(void);
uint8_t DHT11_ReadByte(void);
uint8_t DHT11_ReadData(uint8_t *temp, uint8_t *hum);

void DHT11_delay(int time);
void DHT11_delay_us(int time);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/