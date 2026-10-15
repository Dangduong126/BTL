#include "led.h"

void Led_Config(void ){
	GPIO_InitTypeDef led;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	led.GPIO_Pin = LED_PIN;
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	led.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED_GPIO,&led);
	
	GPIO_SetBits(LED_GPIO,LED_PIN);
}

void Led_On(void){
	GPIO_ResetBits(LED_GPIO,LED_PIN); // led on
}

void Led_Off(void){
	GPIO_SetBits(LED_GPIO,LED_PIN);
}