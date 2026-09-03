#include "usart.h"
#include "gpio.h"

#define F_CPU 180000000UL
#define APB1_CLOCK 16000000UL
#define APB2_CLOCK 90000000UL

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
	usart -> CR1 |= (0x1 << USART_CR1_RE_Pos);
	usart -> CR1 |= (0x1 << USART_CR1_TE_Pos);
	usart_enable(usart);
}

void usart_oversampling(USART_TypeDef *usart, USART_OVERSAMPLING oversampling_mode){
	usart->CR1 &= ~(1 << 15);
	usart->CR1 |= (oversampling_mode << 15);
}

void usart_baud_rate(USART_TypeDef *usart, uint32_t baudrate)
{
    uint32_t pclk;

    if (usart == USART1 || usart == USART6)
        pclk = APB2_CLOCK;
    else
        pclk = APB1_CLOCK;

    if ((usart->CR1 & USART_CR1_OVER8) == 0)
    {
        // 16x oversampling
        usart->BRR = (pclk + (baudrate / 2)) / baudrate;
    }
    else
    {
        // 8x oversampling
        uint32_t usartdiv = (2 * pclk + (baudrate / 2)) / baudrate;

        usart->BRR = (usartdiv & 0xFFF0)
                   | ((usartdiv & 0x000F) >> 1);
    }
}

void usart_set_TX(USART_TypeDef *usart, GPIO_TypeDef *TX, uint8_t tx_pin)
{
    gpio_enable_clock(TX);

    GPIO_mode_def txrx_modes = GPIO_ALTERNATE_FUNCTION;
    GPIO_output_type tx_push_pull = GPIO_PUSH_PULL;

    gpio_set_mode(TX, tx_pin, txrx_modes);
    gpio_output_type(TX, tx_pin, tx_push_pull);
    gpio_alternate_function(TX, tx_pin, GPIO_AF7);
}

void usart_set_RX(USART_TypeDef *usart, GPIO_TypeDef *RX, uint8_t rx_pin)
{
    gpio_enable_clock(RX);

    GPIO_mode_def txrx_modes = GPIO_ALTERNATE_FUNCTION;
    GPIO_pupd rx_no_pupd = GPIO_NO_PUPD;

    gpio_set_mode(RX, rx_pin, txrx_modes);
    gpio_set_pupd(RX, rx_pin, rx_no_pupd);
    gpio_alternate_function(RX, rx_pin, GPIO_AF7);
}

char usart_read_char(USART_TypeDef *usart){
	while (!((usart -> SR) & (1<<USART_SR_RXNE_Pos)));

	return (char)usart -> DR;
}

void usart_read_string(USART_TypeDef *usart, char* buffer, uint32_t buffer_length){
	for (int i = 0; i <buffer_length-1; i++){
		char c = usart_read_char(usart);
		buffer[i] = c;
		if ((c == '\n')){
			buffer[i+1] = '\0';
			break;
		}
		if (c=='\0'){
			break;
		}
	}
}
void usart_transmit_char(USART_TypeDef *usart, char c){
	while (!((usart->SR) & (1<<USART_SR_TXE_Pos)));

	usart->DR =(uint8_t)c;
}


void usart_transmit_string(USART_TypeDef *usart, char *str){
	int i =1;
	while (str[i-1] != '\0'){
		i++;
	}
	for (int j = 0; j<i;j++){
		usart_transmit_char(usart,str[j]);
	}
}

void usart_enable(USART_TypeDef *usart)
{
    usart->CR1 |= (1<<USART_CR1_UE_Pos);
}

void usart_disable(USART_TypeDef *usart)
{
    usart->CR1 &= ~(1<<USART_CR1_UE_Pos);
}





















