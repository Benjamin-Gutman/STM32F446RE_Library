#ifndef ADC_H
#define ADC_H

#include "../Drivers/CMSIS/Device/ST/STM32F4XX/Include/stm32f446xx.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    ADC_RESOLUTION_12BIT,
    ADC_RESOLUTION_10BIT,
    ADC_RESOLUTION_8BIT,
    ADC_RESOLUTION_6BIT

} ADC_Resolution;

typedef enum
{
    ADC_CHANNEL_0 = 0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12,
    ADC_CHANNEL_13,
    ADC_CHANNEL_14,
    ADC_CHANNEL_15,
    ADC_CHANNEL_16,
    ADC_CHANNEL_17,
    ADC_CHANNEL_18

} ADC_Channel;

typedef enum
{
    ADC_SAMPLE_3_CYCLES,
    ADC_SAMPLE_15_CYCLES,
    ADC_SAMPLE_28_CYCLES,
    ADC_SAMPLE_56_CYCLES,
    ADC_SAMPLE_84_CYCLES,
    ADC_SAMPLE_112_CYCLES,
    ADC_SAMPLE_144_CYCLES,
    ADC_SAMPLE_480_CYCLES

} ADC_SampleTime;


void adc_init(ADC_TypeDef* adc,GPIO_TypeDef *port, uint8_t pin, ADC_Channel channel);

void adc_set_resolution(ADC_TypeDef *adc, ADC_Resolution resolution);

void adc_set_channel(ADC_TypeDef *adc, ADC_Channel channel);

void adc_set_sample_time(ADC_TypeDef *adc, ADC_Channel channel, ADC_SampleTime sample_time);

void adc_start(ADC_TypeDef *adc);

uint16_t adc_read(ADC_TypeDef *adc);

uint16_t adc_read_channel(ADC_TypeDef *adc, ADC_Channel channel);

void adc_enable_dma(ADC_TypeDef *adc);

void adc_enable_continuous(ADC_TypeDef *adc);

void adc_disable_continuous(ADC_TypeDef *adc);




#ifdef __cplusplus
}
#endif

#endif
