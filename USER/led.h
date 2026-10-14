#ifndef LED_H
#define LED_H

#include "stm32f10x.h"                  // Device header

#define LED_GPIO GPIOA
#define LED_PIN GPIO_Pin_5

void Led_Config(void );

void Led_On(void);

void Led_Off(void);

#endif