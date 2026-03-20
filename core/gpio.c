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

void gpio_lock_mode(GPIO_TypeDef *port, uint8_t pin,GPIO_lock mode){
	uint32_t temp = (1U << pin);
	port->LCKR |= temp;
	port->LCKR |= (1U << 16);
	port->LCKR &= ~(1U << 16);
	port->LCKR |= (1U << 16);
	temp = port->LCKR;
	(void)temp; // avoid unused warning
}

void gpio_alternate_function(GPIO_TypeDef *port, uint8_t pin, GPIO_alternate_mode mode){
	if ((port -> MODER >> (2*pin) & 0x3) !=0x2){
		return;
	}
	if (pin <8)
		port -> AFR[0] &= ~(0xF<<(4*pin));
		port -> AFR[0] |= (mode<<(4*pin));
	else{
		port -> AFR[1] &= ~(0xF<<(4*(pin-8)));
		port -> AFR[1] |= (mode<<(4*(pin-8)));
	}
}

void gpio_output_type(GPIO_TypeDef *port, uint8_t pin, GPIO_output_type output){
	port->OTYPER &= ~(1 << pin);
	port->OTYPER |= (output << pin);
}


void gpio_set_port(GPIO_TypeDef *port, uint32_t value){
	port -> MODER = value;
}















