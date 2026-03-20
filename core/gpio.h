#ifndef GPIO_H
#define GPIO_H

#include "stm32f446xx.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_HIGH 1
#define GPIO_LOW 0

typedef enum{
	GPIO_INPUT,
	GPIO_OUTPUT,
	GPIO_ALTERNATE_FUNCTION,
	GPIO_ANALOG
}GPIO_mode_def;

typedef enum{
	GPIO_SLOW_SPEED,
	GPIO_MEDIUM_SPEED,
	GPIO_FAST_SPEED,
	GPIO_HIGH_SPEED,
}GPIO_SPEED;

typedef enum{
	GPIO_NO_PUPD,
	GPIO_PULL_UP,
	GPIO_PULL_DOWN,
	GPIO_RESERVED
}GPIO_pupd;

typedef enum{
	GPIO_UNLOCK,
	GPIO_LOCK
}GPIO_lock;

typedef enum{
	GPIO_AF0,
	GPIO_AF1,
	GPIO_AF2,
	GPIO_AF3,
	GPIO_AF4,
	GPIO_AF5,
	GPIO_AF6,
	GPIO_AF7,
	GPIO_AF8,
	GPIO_AF9,
	GPIO_AF10,
	GPIO_AF11,
	GPIO_AF12,
	GPIO_AF13,
	GPIO_AF14,
	GPIO_AF15
}GPIO_alternate_mode;

typedef enum{
	GPIO_PUSH_PULL,
	GPIO_OPEN_DRAIN
}GPIO_output_type;

void gpio_toggle(GPIO_TypeDef *port, uint8_t pin);
void gpio_write(GPIO_TypeDef *port, uint8_t pin, uint8_t value);
uint8_t gpio_read(GPIO_TypeDef *port, uint8_t pin);
void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, GPIO_mode_def mode);
void gpio_set_speed(GPIO_TypeDef *port, uint8_t pin, GPIO_speed speed);
void gpio_set_pupd(GPIO_TypeDef *port, uint8_t pin,GPIO_pupd pupd_type);
uint32_t gpio_read_port(GPIO_TypeDef *port);
void gpio_lock_mode(GPIO_TypeDef *port, uint8_t pin,GPIO_lock mode);
void gpio_alternate_function(GPIO_TypeDef *port, uint8_t pin, GPIO_alternate_mode mode);
void gpio_output_type(GPIO_TypeDef *port, uint8_t pin, GPIO_output_type output);
void gpio_set_port(GPIO_TypeDef *port, uint32_t value);



#ifdef __cplusplus
}
#endif

#endif
