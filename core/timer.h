#ifndef TIMER_H
#define TIMER_H

#include "../Drivers/CMSIS/Device/ST/STM32F4XX/Include/stm32f446xx.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
    TIMER_COUNT_UP,
    TIMER_COUNT_DOWN,
    TIMER_CENTER_ALIGNED_1,
    TIMER_CENTER_ALIGNED_2,
    TIMER_CENTER_ALIGNED_3
} TimerCounterMode;

void timer_init(TIM_TypeDef* timer, uint16_t prescaler, uint16_t period);
//void advanced_timer_init(TIM_TypeDef* timer);
//void basic_timer_init();
//void general_timer_init();

void set_timer_prescaler(TIM_TypeDef* timer, uint16_t prescaler);
void set_timer_auto_reload(TIM_TypeDef* timer, uint16_t reload_value);
void set_timer_counter(TIM_TypeDef* timer, uint16_t value);
uint16_t get_timer_counter(TIM_TypeDef* timer);

void start_timer(TIM_TypeDef* timer);
void stop_timer(TIM_TypeDef* timer);

void timer_enable_clock(TIM_TypeDef* timer);

void set_timer_mode(TimerCounterMode);
void set_repitition_count();
int32_t read_repitition_count();






#ifdef __cplusplus
}
#endif

#endif
