#include "mq2.h"

void ADC_MQ_Init(void){
	GPIO_InitTypeDef gpio;
	ADC_InitTypeDef adc;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1,ENABLE);
	
	gpio.GPIO_Pin = MQ_Pin;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIO_MQ,&gpio);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	adc.ADC_Mode = ADC_Mode_Independent;
	adc.ADC_ScanConvMode = DISABLE;
	adc.ADC_ContinuousConvMode = DISABLE;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_NbrOfChannel = 1;
	
	ADC_Init(ADC_MQ,&adc);
	
	ADC_Cmd(ADC_MQ, ENABLE);
	
	//Hieu chinh
	ADC_ResetCalibration(ADC_MQ);
	while(ADC_GetResetCalibrationStatus(ADC_MQ));
	ADC_StartCalibration(ADC_MQ);
	while(ADC_GetCalibrationStatus(ADC_MQ));
}

uint8_t MQ_Read(void ){
	 ADC_RegularChannelConfig(ADC_MQ,ADC_MQ_Channel,1,ADC_SampleTime_55Cycles5);

    ADC_SoftwareStartConvCmd(ADC_MQ, ENABLE);

    while (ADC_GetFlagStatus(ADC_MQ, ADC_FLAG_EOC) == RESET);

    return ADC_GetConversionValue(ADC_MQ);
}