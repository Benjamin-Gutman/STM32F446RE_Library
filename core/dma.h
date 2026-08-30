#ifndef DMA_H
#define DMA_H

#include "stm32f446xx.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
	DMA_PERIPHERY_TO_MEMORY,
	DMA_MEMORY_TO_PERIPHERY,
	DMA_MEMORY_TO_MEMORY
} DMA_Direction;

typedef enum {
	DMA_DATA_8BIT,
	DMA_DATA_16BIT,
	DMA_DATA_32BIT
} DMA_DataSize;

typedef enum {
	DMA_PRIORITY_LOW,
	DMA_PRIORITY_MEDIUM,
	DMA_PRIORITY_HIGH,
	DMA_PRIORITY_VERY_HIGH
} DMA_Priority;

typedef enum {
	DMA_SINGLE,
	DMA_INCREMENTAL_BURST
} DMA_Burst;

void dma_init(DMA_TypeDef* dma, uint8_t stream);

void dma_set_channel(DMA_TypeDef* dma, uint8_t stream, uint8_t channel);

void dma_set_address(DMA_TypeDef* dma, uint8_t stream, uint32_t peripheral_address, uint32_t memory_address);

void dma_set_transfer_length(DMA_TypeDef* dma, uint8_t stream, uint16_t length);

void dma_set_direction(DMA_TypeDef* dma, uint8_t stream, DMA_Direction direction);

void dma_set_data_size(DMA_TypeDef* dma, uint8_t stream, DMA_DataSize peripheral_size, DMA_DataSize size);

void dma_enable_memory_increment(DMA_TypeDef* dma, uint8_t stream);

void dma_enable_peripheral_increment(DMA_TypeDef* dma, uint8_t stream);

void dma_enable_circular_mode(DMA_TypeDef* dma, uint8_t stream);

void dma_set_priority(DMA_TypeDef* dma, uint8_t stream, DMA_Priority priority);


void dma_enable(DMA_TypeDef* dma, uint8_t stream);

void dma_disable(DMA_TypeDef* dma, uint8_t stream);

uint8_t dma_is_enabled(DMA_TypeDef* dma, uint8_t stream);


#ifdef __cplusplus
}

#endif

#endif
