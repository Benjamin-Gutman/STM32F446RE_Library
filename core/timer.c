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

