#include 'usart.h'
#include 'gpio.h'

#define F_CPU 180000000UL

void usart_init(USART_TypeDef *usart, uint32_t baudrate,
		GPIO_TypeDef *TX, uint8_t tx_pin,
		GPIO_TypeDef *RX, uint8_t rx_pin,
		 USART_OVERSAMPLING oversampling_mode){
	if (usart == USART1){
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	}
	else if (usart == USART2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	}
	else if (usart == USART3){
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	}
	else if (usart == UART4){
		RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
	}
	else if (usart == UART5){
		RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
	}
	else{
		RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
	}
	usart_set_TX(usart, TX,tx_pin);
	usart_set_RX(usart, RX,rx_pin);
	usart_oversampling(usart, oversampling_mode);
	usart_baud_rate(usart, baudrate);
	usart -> CR1 |= (0x1 << 2);
	usart -> CR1 |= (0x1 << 3);
	usart -> CR1 |= (0x1 << 13);
}

void usart_oversampling(USART_TypeDef *usart, USART_OVERSAMPLING oversampling_mode){
	usart->CR1 &= ~(1 << 15);
	usart->CR1 |= (oversampling_mode << 15);
}

void usart_baud_rate(USART_TypeDef *usart, uint32_t baudrate){
	uint32_t over8 = usart->CR1;
	over8 = over8>>15;
	over8 &= 0x1;
	uint32_t pclk;

	if (usart == USART1 || usart == USART6)
	    pclk = APB2_CLOCK;
	else
	    pclk = APB1_CLOCK;
	float usartdiv = (float)pclk/(8.0f*(2-over8)*baudrate);
	usart -> BRR = (0x0);
	usart -> BRR |= ((uint32_t)usartdiv << 4);
	float fraction = usartdiv - (uint32_t)usartdiv;
	if (over8 == 1){
		fraction = fraction * 8.0f + 0.5f;
	}
	else{
		fraction = fraction * 16.0f + 0.5f;
	}
	usart -> BRR |= ((uint16_t)fraction);
}

void usart_set_TX(USART_TypeDef *usart, GPIO_TypeDef *TX, uint8_t tx_pin){
	GPIO_mode_def txrx_modes = GPIO_ALTERNATE_FUNCTION;
	GPIO_output_type tx_push_pull = GPIO_PUSH_PULL;
	gpio_set_mode(TX, tx_pin, txrx_modes);
	gpio_output_type(TX, tx_pin, tx_push_pull);
}

void usart_set_RX(USART_TypeDef *usart, GPIO_TypeDef *RX, uint8_t rx_pin){
	GPIO_mode_def txrx_modes = GPIO_ALTERNATE_FUNCTION;
	GPIO_pupd rx_no_pupd = GPIO_NO_PUPD;
	gpio_set_mode(RX, rx_pin, txrx_modes);
	gpio_input_type(RX,rx_pin, rx_no_pupd);
}


