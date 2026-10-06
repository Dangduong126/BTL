#include "delay.h"

volatile uint32_t g_ms_Time = 0;
volatile uint32_t g_mililis = 0;

void Sys_Init(void){
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
}


void Sys_Delay_ms(uint32_t msTime){
	g_ms_Time = msTime;
	while(g_ms_Time>0);
	
}
void Sys_Delay_s(uint32_t sTime){
 while(sTime--){
	Sys_Delay_ms(1000);
 }
}
uint32_t Sys_mililis(void){
	return g_mililis;
}

void SysTick_Handler(void){
	if(g_ms_Time > 0){
		g_ms_Time --;
	}
	g_mililis ++;
}