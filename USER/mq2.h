#ifndef MQ2_H
#define MQ2_H

#include "stm32f10x.h"
#include <math.h>
#include "delay.h"

void     MQ2_Init(void);               // cau hinh PA7 và ADC1, goi 1 lan
void     MQ2_DelayMs(uint32_t ms);     // cho ms mili-giây (SysTick, chan chuong trình)

uint16_t MQ2_ReadRaw(void);            // 1 mau ADC, 0..4095
uint16_t MQ2_Read(void);               // ADC trung bình 10 mau
uint16_t MQ2_ReadMilliVolt(void);      // dien áp that tai AO (mV)

void     MQ2_Calibrate(void);          // do R0, goi khi cam bien nong và o không khí sach
uint8_t  MQ2_IsCalibrated(void);       // 1 = da hieu chuan
uint16_t MQ2_ReadPPM(void);            // nong do gas (ppm), 0 neu chua hieu chuan

#endif