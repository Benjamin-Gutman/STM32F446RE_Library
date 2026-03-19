#include 'gpio.h'


void gpio_toggle(GPIO_TypeDef *port, uint8_t pin){
	if (port->ODR & (1<<pin)){
		port->BSRR = (1<<(pin+16));
	}
	else{
		port -> BSRR = (1<<pin);
	}
}

void gpio_write(GPIO_TypeDef *port, uint8_t pin, uint8_t value){
	if (value){
		port->BSRR = (1<<pin);
	}
	else{
		port->BSRR = (1<<(pin+16));
	}
}

uint8_t gpio_read(GPIO_TypeDef *port, uint8_t pin){
	uint8_t value = ((port->IDR) & (1<<pin)) >> pin;
	return value;
}

void gpio_set_mode(GPIO_TypeDef *port, uint8_t pin, GPIO_mode_def mode){
	port->MODER &= ~(0x3 << (2*pin));
	port->MODER |= (mode<<(2*pin));
}

void gpio_set_speed(GPIO_TypeDef *port, uint8_t pin, GPIO_speed speed){
	port->OSPEEDR &= ~(0x3 << (2*pin));
	port->OSPEEDR |= (speed << (2*pin));
}

void gpio_set_pupd(GPIO_TypeDef *port, uint8_t pin,GPIO_pupd pupd_type){
	port->PUPDR &= ~(0x3 << (2*pin));
	port->PUPDR |= (pupd_type << (2*pin));
}

uint32_t gpio_read_port(GPIO_TypeDef *port){
	uint32_t value = port->IDR;
	return value;
}

