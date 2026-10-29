#ifndef UART_LIB_H__
#define UART_LIB_H__

#include "stm32f10x.h"

void UART1_lib_Config(int baurate);
void UART1_lib_send_char(char c);
void UART1_lib_send_string(char* str);
void UART1_lib_delay(int time);
char UART1_lib_receive_char(void);

#endif