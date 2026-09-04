#include "adc.h"
#include "gpio.h"

void adc_init(ADC_TypeDef* adc,GPIO_TypeDef *port, uint8_t pin, ADC_Channel channel){

	gpio_enable_clock(port);

	gpio_set_mode(port, pin, GPIO_ANALOG);

	gpio_set_pupd(port, pin, GPIO_NO_PUPD);

	if (adc == ADC1){
		RCC->APB2ENR |= (1 << RCC_APB2ENR_ADC1EN_Pos);
	}
	else if (adc == ADC2){
		RCC->APB2ENR |= (1 << RCC_APB2ENR_ADC2EN_Pos);
	}
	else if (adc == ADC3){
		RCC->APB2ENR |= (1 << RCC_APB2ENR_ADC3EN_Pos);
	}

	adc -> CR2 &= ~(1 <<ADC_CR2_ADON_Pos);

	adc_set_resolution(adc, ADC_RESOLUTION_12BIT);

	adc->CR2 &= ~(1 << ADC_CR2_CONT_Pos);

	adc->CR2 &= ~(1 << ADC_CR2_ALIGN_Pos);

	adc_set_channel(adc, channel);

	adc_set_sample_time(adc, channel, ADC_SAMPLE_15_CYCLES);

	adc -> CR2 |= (1 << ADC_CR2_ADON_Pos);
}

void adc_set_resolution(ADC_TypeDef *adc, ADC_Resolution resolution){

	adc->CR1 &= ~(1 << ADC_CR1_RES_Pos);

	adc->CR1 &= ~(1 << (ADC_CR1_RES_Pos + 1));

    switch (resolution){
        case ADC_RESOLUTION_12BIT:

            break;

        case ADC_RESOLUTION_10BIT:

            adc->CR1 |= (1 << ADC_CR1_RES_Pos);

            break;

        case ADC_RESOLUTION_8BIT:

            adc->CR1 |= (1 << (ADC_CR1_RES_Pos + 1));

            break;

        case ADC_RESOLUTION_6BIT:

            adc->CR1 |= (1 << ADC_CR1_RES_Pos);

            adc->CR1 |= (1 << (ADC_CR1_RES_Pos + 1));

            break;
    }
}

void adc_set_channel(ADC_TypeDef *adc, ADC_Channel channel){

    adc->SQR3 &= ~(1 << ADC_SQR3_SQ1_Pos);
    adc->SQR3 &= ~(1 << (ADC_SQR3_SQ1_Pos + 1));
    adc->SQR3 &= ~(1 << (ADC_SQR3_SQ1_Pos + 2));
    adc->SQR3 &= ~(1 << (ADC_SQR3_SQ1_Pos + 3));
    adc->SQR3 &= ~(1 << (ADC_SQR3_SQ1_Pos + 4));

    adc->SQR3 |= ((uint32_t)channel << ADC_SQR3_SQ1_Pos);

    adc->SQR1 &= ~(1 << ADC_SQR1_L_Pos);
    adc->SQR1 &= ~(1 << (ADC_SQR1_L_Pos + 1));
    adc->SQR1 &= ~(1 << (ADC_SQR1_L_Pos + 2));
    adc->SQR1 &= ~(1 << (ADC_SQR1_L_Pos + 3));
}

void adc_set_sample_time(ADC_TypeDef *adc, ADC_Channel channel, ADC_SampleTime sample_time){

	uint32_t shift;

    if (channel <= ADC_CHANNEL_9){
    	shift = ADC_SMPR2_SMP0_Pos + (channel * 3);

        adc->SMPR2 &= ~(1 << shift);
        adc->SMPR2 &= ~(1 << (shift + 1));
        adc->SMPR2 &= ~(1 << (shift + 2));

        adc->SMPR2 |= ((uint32_t)sample_time << shift);
    }
    else {
        shift = ADC_SMPR1_SMP10_Pos + ((channel - 10) * 3);

        adc->SMPR1 &= ~(1 << shift);
        adc->SMPR1 &= ~(1 << (shift + 1));
        adc->SMPR1 &= ~(1 << (shift + 2));

        adc->SMPR1 |= ((uint32_t)sample_time << shift);
    }
}

void adc_start(ADC_TypeDef *adc){
    adc->CR2 |= (1 << ADC_CR2_SWSTART_Pos);
}

uint16_t adc_read(ADC_TypeDef *adc){
    while (!(adc->SR & (1 << ADC_SR_EOC_Pos))){
        // Wait for conversion to finish
    }

    return (uint16_t)adc->DR;
}

uint16_t adc_read_channel(ADC_TypeDef *adc, ADC_Channel channel){
    adc_set_channel(adc, channel);
    adc_start(adc);
    return adc_read(adc);
}

void adc_enable_dma(ADC_TypeDef *adc){

    adc->CR2 &= ~(3 << ADC_CR2_DMA_Pos);
    adc->CR2 |= (1 << ADC_CR2_DMA_Pos);

    adc->CR2 |= (1 << ADC_CR2_DDS_Pos);
}

void adc_enable_continuous(ADC_TypeDef *adc){
    adc->CR2 |= (1 << ADC_CR2_CONT_Pos);
}

void adc_disable_continuous(ADC_TypeDef *adc){
    adc->CR2 &= ~(1 << ADC_CR2_CONT_Pos);
}
