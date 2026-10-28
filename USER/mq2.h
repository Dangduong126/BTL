	
#ifndef __MQ2_H__
#define __MQ2_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

#define ADC_MQ ADC1
#define GPIO_MQ GPIOA
#define MQ_Pin GPIO_Pin_7
#define ADC_MQ_Channel ADC_Channel_7

void ADC_MQ_Init(void );
uint8_t MQ_Read(void );
#ifdef __cplusplus
}
#endif

#endif
