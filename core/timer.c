#include "timer.h"

void timer_init(TIM_TypeDef* timer, uint16_t prescaler, uint16_t period){

	timer -> PSC = prescaler;

	timer -> ARR = period;

	timer -> CNT = 0;

}


void set_timer_prescaler(TIM_TypeDef* timer, uint16_t prescaler){
	timer -> PSC = prescaler;
}

void set_timer_auto_reload(TIM_TypeDef* timer, uint16_t reload_value){
	timer -> ARR = reload_value;
}

void set_timer_counter(TIM_TypeDef* timer, uint16_t value){
	timer -> CNT = value;
}

uint16_t get_timer_counter(TIM_TypeDef* timer){
	return timer->CNT;
}

void start_timer(TIM_TypeDef* timer){
	timer -> CR1 |= (1<<TIM_CR1_CEN_Pos);
}

void stop_timer(TIM_TypeDef* timer){
	timer -> CR1 &= ~(1<<TIM_CR1_CEN_Pos);
}

void timer_enable_clock(TIM_TypeDef* timer)
{
    if (timer == TIM1) {
        RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM1EN_Pos);
    }
    else if (timer == TIM2) {
        RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM2EN_Pos);
    }
    else if (timer == TIM3) {
        RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM3EN_Pos);
    }
    else if (timer == TIM4) {
        RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM4EN_Pos);
    }
    else if (timer == TIM5) {
        RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM5EN_Pos);
    }
    else if (timer == TIM6) {
        RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM6EN_Pos);
    }
    else if (timer == TIM7) {
        RCC->APB1ENR |= (1 << RCC_APB1ENR_TIM7EN_Pos);
    }
    else if (timer == TIM8) {
        RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM8EN_Pos);
    }
    else if (timer == TIM9) {
        RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM9EN_Pos);
    }
    else if (timer == TIM10) {
        RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM10EN_Pos);
    }
    else if (timer == TIM11) {
        RCC->APB2ENR |= (1 << RCC_APB2ENR_TIM11EN_Pos);
    }
}
