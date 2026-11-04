#include "mq2.h"

#define RL                10000.0f     // dien tro tai module
#define VCC               5.0f
#define CLEAN_AIR_RATIO   9.83f        // Rs/R0 trong khong khi sach (datasheet)

static float R0 = 0;                   // 0 = chua hieu chuan

/* ---------- Khoi tao ---------- */
void MQ2_Init(void)
{
    GPIO_InitTypeDef g;
    ADC_InitTypeDef  a;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);            // 72 MHz / 6 = 12 MHz (<= 14 MHz)

    g.GPIO_Pin   = GPIO_Pin_7;                   // PA7 = ngo vao analog
    g.GPIO_Mode  = GPIO_Mode_AIN;
    g.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &g);

    a.ADC_Mode               = ADC_Mode_Independent;
    a.ADC_ScanConvMode       = DISABLE;
    a.ADC_ContinuousConvMode = DISABLE;          // moi lan goi doc 1 mau
    a.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
    a.ADC_DataAlign          = ADC_DataAlign_Right;
    a.ADC_NbrOfChannel       = 1;
    ADC_Init(ADC1, &a);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_71Cycles5);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);                  // hieu chuan ADC
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}


/* ---------- Doc ADC ---------- */
uint16_t MQ2_ReadRaw(void)                       // 1 mau, 0..4095
{
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}
uint16_t MQ2_Read(void)                          // trung binh 10 mau
{
    uint32_t sum = 0;
    uint8_t i;
    for (i = 0; i < 10; i++) sum += MQ2_ReadRaw();
    return (uint16_t)(sum / 10);
}

/* Dien ap that tai dau AO (V), da bu cau chia ap 10k/10k (he so 2) */
static float get_voltage(void)
{
    return MQ2_Read() * 3.3f / 4095.0f * 2.0f;
}
uint16_t MQ2_ReadMilliVolt(void)
{
    return (uint16_t)(get_voltage() * 1000.0f);
}

/* ---------- Dien tro cam bien Rs ---------- */
static float get_Rs(void)
{
    float v = get_voltage();
    if (v <= 0.01f || v >= VCC) return 0;
    return RL * (VCC - v) / v;
}

/* ---------- Hieu chuan R0 (goi khi dang o khong khi sach) ---------- */
void MQ2_Calibrate(void)
{
    float sum = 0;
    uint8_t i;

    for(i = 0; i < 10; i++)
    {
        sum += get_Rs();
        Sys_Delay_ms(100);
    }

    R0 = (sum / 10.0f) / CLEAN_AIR_RATIO;
}
uint8_t MQ2_IsCalibrated(void)
{
    return (R0 > 0) ? 1 : 0;
}

/* ---------- Doc ppm (tra ve 0 neu chua hieu chuan) ---------- */
uint16_t MQ2_ReadPPM(void)
{
    float rs = get_Rs();
    float ppm;

    if (R0 <= 0 || rs <= 0) return 0;
    ppm = 574.25f * powf(rs / R0, -2.222f);
    if (ppm > 65535.0f) ppm = 65535.0f;
    return (uint16_t)ppm;
}