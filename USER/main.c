#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "uart_lib.h"
#include "delay.h"
#include "DHT.h"
#include "mq2.h"
#include "led.h"


uint8_t hum = 0;
uint8_t temp = 0;
uint8_t gas = 0;
char TX_string[100];

extern volatile uint32_t g_mililis;

void UART_LED_Control(void){
	static char cmd[10];
	static uint8_t index = 0;
	char c;
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) != RESET){
		c = (char)USART_ReceiveData(USART1);
		
		if(c == '\n'){
			cmd[index] = '\0';
			if(strcmp(cmd,"LED_ON") == 0){
				GPIO_ResetBits(LED_GPIO,LED_PIN);
			}
			else if(strcmp(cmd,"LED_OFF") == 0){
				GPIO_SetBits(LED_GPIO,LED_PIN);
			}
			index = 0;
		}
		else if(c != '\r' && index < sizeof(cmd) - 1){
			cmd[index++] = c;
		}
		else if(index >= sizeof(cmd) - 1){
			index = 0;
		}
	}
}

int main(){
	DHT11_Init();
	Sys_Init();
	ADC_MQ_Init();
	UART1_lib_Config(9600);
	UART1_lib_send_string("STM32 System Start...\n");
	
	uint32_t lastSensorTime = g_mililis;
	
	while(1){
		UART_LED_Control();
		int v = MQ_Read();
		gas = v*3.3/4095;
		
		if(g_mililis - lastSensorTime >= 1000){
			lastSensorTime = g_mililis;
			
			int v = MQ_Read();
			gas = v*3.3/4095;
			
			if((DHT11_ReadData(&temp, &hum)) == 1){
				sprintf(TX_string,"T:%d,H:%d,G:%d\n",temp,hum,gas);
				UART1_lib_send_string(TX_string);
			} else {
				UART1_lib_send_string("Loi: Khong doc duoc cam bien!\n");
			}
		}
	}
}
