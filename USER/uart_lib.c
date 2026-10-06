#include "uart_lib.h"


void UART1_lib_Config(int baurate){
	
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
	
	//config TX
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Pin = GPIO_Pin_9;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);
	//config RX
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Pin = GPIO_Pin_10;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);
	
	uart.USART_BaudRate = baurate;
	uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uart.USART_Parity = USART_Parity_No;
	uart.USART_StopBits = USART_StopBits_1;
	uart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&uart);
	USART_Cmd(USART1,ENABLE);
	
}

void UART1_lib_send_char(char c){
	USART_SendData(USART1,c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void UART1_lib_send_string(char* str){
	while(*str != '\0'){
	UART1_lib_send_char(*str++);
	}
}

char UART1_lib_receive_char(void)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData(USART1);
}

void UART1_lib_delay(int time){
	for(int i = 0;i<time;i++){
		for(int j = 0;j<0x2AFF;j++);
	}
}