#include "DHT.h"
	
void DHT11_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef timer;
    
    timer.TIM_Prescaler = (SystemCoreClock / 1000000) - 1; 
    timer.TIM_Period = 0xFFFF;
    timer.TIM_ClockDivision = 0;
    timer.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM2, &timer);
    TIM_Cmd(TIM2, ENABLE);
}


void DHT11_delay_us(int time){
    TIM_SetCounter(TIM2, 0);
    while(TIM_GetCounter(TIM2) < time);
}

void DHT11_delay(int time){
    TIM_SetCounter(TIM2, 0);
    while(TIM_GetCounter(TIM2) < (time * 1000));
}


void DHT11_SetOutput(void){
	GPIO_InitTypeDef gpio;
	
	gpio.GPIO_Pin = DHT11_PIN;
	gpio.GPIO_Mode = GPIO_Mode_Out_OD;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT11_GPIO,&gpio);
}

void DHT11_SetInput(void){
	GPIO_InitTypeDef gpio;
	
	gpio.GPIO_Pin = DHT11_PIN;
	gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DHT11_GPIO,&gpio);
}

void DHT11_Start(void){
	DHT11_SetOutput();
  GPIO_ResetBits(DHT11_GPIO, DHT11_PIN);
  DHT11_delay(20);   // keo LOW it nhat 18ms
 
  GPIO_SetBits(DHT11_GPIO, DHT11_PIN);
  DHT11_delay_us(30);
 
    DHT11_SetInput();
}

uint8_t DHT11_CheckResponse(void){
		uint8_t response = 0;
    uint32_t timeout;
 
    DHT11_delay_us(40);
 
    if(!GPIO_ReadInputDataBit(DHT11_GPIO, DHT11_PIN)){
        DHT11_delay_us(80);
 
        if(GPIO_ReadInputDataBit(DHT11_GPIO, DHT11_PIN)){
            response = 1;
        }
    }
 
    // tranh timeout
    timeout = 100000;
    while(GPIO_ReadInputDataBit(DHT11_GPIO, DHT11_PIN)){
        if(--timeout == 0) return 0;
    }
 
    return response;
}
uint8_t DHT11_ReadByte(void){
	  uint8_t i, data = 0;
    uint32_t timeout;
 
    for(i = 0; i < 8; i++){
        // FIX 3: Timeout cho vong while cho LOW -> HIGH
        timeout = 100000;
        while(!GPIO_ReadInputDataBit(DHT11_GPIO, DHT11_PIN)){
            if(--timeout == 0) return 0;
        }
 
        DHT11_delay_us(40);
 
        if(GPIO_ReadInputDataBit(DHT11_GPIO, DHT11_PIN)){
            data |= (1 << (7 - i));
        }
 
        // FIX 4: Timeout cho vong while cho HIGH -> LOW
        timeout = 100000;
        while(GPIO_ReadInputDataBit(DHT11_GPIO, DHT11_PIN)){
            if(--timeout == 0) return 0;
        }
    }
    return data;
}
uint8_t DHT11_ReadData(uint8_t *temp, uint8_t *hum){
	  uint8_t hum_dec, temp_dec, checksum;
 
    DHT11_Start();
    if(DHT11_CheckResponse()){
        *hum     = DHT11_ReadByte();
        hum_dec  = DHT11_ReadByte();
        *temp    = DHT11_ReadByte();
        temp_dec = DHT11_ReadByte();
        checksum = DHT11_ReadByte();
 
        // FIX 6: Kiem tra checksum
        if(checksum == (uint8_t)(*hum + hum_dec + *temp + temp_dec)){
            return 1; // doc thanh cong
        }
    }
		return 0; // loi
}