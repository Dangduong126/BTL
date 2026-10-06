#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"
#include "stdio.h"
#include "string.h"
#include "uart_lib.h"
#include "delay.h"
#include "DHT.h"
#include "mq2.h"

uint8_t hum = 0;
uint8_t temp = 0;
uint8_t gas = 0;
char TX_string[100];

int main(){
	DHT11_Init();
	Sys_Init();
	ADC_MQ_Init();
	UART1_lib_Config(9600);
	UART1_lib_send_string("STM32 System Start...\n");
	while(1){
		int v = MQ_Read();
		gas = v*3.3/4095;
		if((DHT11_ReadData(&temp, &hum)) == 1){
			sprintf(TX_string,"T:%d,H:%d,G:%d\n",temp,hum,gas);
			UART1_lib_send_string(TX_string);
		} else {
			UART1_lib_send_string("Loi: Khong doc duoc DHT11\n");
		}
		Sys_Delay_s(1);
	}
}
