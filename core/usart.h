#ifndef USART_H
#define USART_H

#include "../Drivers/CMSIS/Device/ST/STM32F4XX/Include/stm32f446xx.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	NO_CHANGE,
	CHANGE_DETECTED
} USART_CTS_Flag;

typedef enum{
	NO_DETECTED_BREAK,
	BREAK_DETECTED
} USART_LIN_BREAK_DETECTION_FLAG;

typedef enum{
	NOT_TRANSFERRED,
	TRANSFERRED
}USART_DATA_REGISTER_STATUS;

typedef enum{
	TRANSMISSION_INCOMPLETE,
	TRANSMISSION_COMPLETED
}USART_TRANSMISSION_STATUS;

typedef enum{
	NOT_RECEIVED,
	RECEIVED
}USART_READ_REGISTER_STATUS;

typedef enum{
	NO_IDLE,
	IDLING
}USART_IDLE_LINE_DETECTION;

typedef enum{
	NO_OVERRUN,
	OVERRUN
}USART_OVERRUN_DETECTION;

typedef enum{
	NO_NOISE,
	NOISE_DETECTED
}USART_NOISE_DETECTION;

typedef enum{
	NO_FRAMING_ERROR,
	FRAMING_ERROR
}USART_FE_DETECTION;

typedef enum{
	NO_PE,
	PARITY_ERROR
} USART_PARITY_DETECTION;

typedef enum{
	NoOver,
	Over8
}USART_OVERSAMPLING;



void usart_init(USART_TypeDef *usart, uint32_t baudrate, GPIO_TypeDef *TX, uint8_t tx_pin, GPIO_TypeDef *RX, uint8_t rx_pin,  USART_OVERSAMPLING oversampling_mode);

void usart_baud_rate(USART_TypeDef *usart, uint32_t baudrate);
void usart_set_TX(USART_TypeDef *usart, GPIO_TypeDef *TX, uint8_t tx_pin);
void usart_set_RX(USART_TypeDef *usart, GPIO_TypeDef *RX, uint8_t rx_pin);
void usart_oversampling(USART_TypeDef *usart, USART_OVERSAMPLING oversampling_mode);



char usart_read_char(USART_TypeDef *usart);
void usart_read_string(USART_TypeDef *usart, char* buffer, uint32_t buffer_length);

void usart_transmit_char(USART_TypeDef *usart, char c);
void usart_transmit_string(USART_TypeDef *usart, char *str);

void usart_enable(USART_TypeDef *usart);
void usart_disable(USART_TypeDef *usart);


#ifdef __cplusplus
}
#endif

#endif
