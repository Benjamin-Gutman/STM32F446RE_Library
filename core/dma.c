#include "dma.h"
#include <stdint.h>



void dma_init(DMA_TypeDef* dma, uint8_t stream){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

	if (dma == DMA1){
		RCC->AHB1ENR |= (1<<RCC_AHB1ENR_DMA1EN_Pos);
	}

	else if (dma == DMA2){
		RCC->AHB1ENR |= (1<<RCC_AHB1ENR_DMA2EN_Pos);
	}

	dma_stream -> CR &= ~(1<<DMA_SxCR_EN_Pos);

	while (dma_stream->CR & DMA_SxCR_EN)
	{
	}

}

static DMA_Stream_TypeDef* dma_get_stream(DMA_TypeDef* dma, uint8_t stream){
    switch (stream)
    {
        case 0:
            return dma == DMA1 ? DMA1_Stream0 : DMA2_Stream0;

        case 1:
            return dma == DMA1 ? DMA1_Stream1 : DMA2_Stream1;

        case 2:
            return dma == DMA1 ? DMA1_Stream2 : DMA2_Stream2;

        case 3:
            return dma == DMA1 ? DMA1_Stream3 : DMA2_Stream3;

        case 4:
            return dma == DMA1 ? DMA1_Stream4 : DMA2_Stream4;

        case 5:
            return dma == DMA1 ? DMA1_Stream5 : DMA2_Stream5;

        case 6:
            return dma == DMA1 ? DMA1_Stream6 : DMA2_Stream6;

        case 7:
            return dma == DMA1 ? DMA1_Stream7 : DMA2_Stream7;
    }
}

void dma_set_channel(DMA_TypeDef* dma, uint8_t stream, DMA_Channel channel){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

	dma_stream->CR &= ~DMA_SxCR_CHSEL;
	dma_stream -> CR |= (channel << DMA_SxCR_CHSEL_Pos);

}

void dma_set_address(DMA_TypeDef* dma, uint8_t stream, uint32_t peripheral_address, uint32_t memory_address){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

	dma_stream -> PAR = peripheral_address;
	dma_stream -> M0AR = memory_address;


}

void dma_set_transfer_length(DMA_TypeDef* dma, uint8_t stream, uint16_t length){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);


	dma_stream->NDTR = length;
}

void dma_set_direction(DMA_TypeDef* dma, uint8_t stream, DMA_Direction direction){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

	dma_stream -> CR &= ~(3<< DMA_SxCR_DIR_Pos);

	dma_stream -> CR |= (direction<<DMA_SxCR_DIR_Pos);

}

void dma_set_data_size(DMA_TypeDef* dma, uint8_t stream, DMA_DataSize peripheral_size, DMA_DataSize memory_size){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

	dma_stream -> CR &= ~(3<< DMA_SxCR_MSIZE_Pos);
	dma_stream -> CR |= (memory_size<< DMA_SxCR_MSIZE_Pos);

	dma_stream -> CR &= ~(3<< DMA_SxCR_PSIZE_Pos);
	dma_stream -> CR |= (peripheral_size<< DMA_SxCR_PSIZE_Pos);

}

void dma_enable_memory_increment(DMA_TypeDef* dma, uint8_t stream){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

	dma_stream -> CR |= (1<<DMA_SxCR_MINC_Pos);

}

void dma_enable_peripheral_increment(DMA_TypeDef* dma, uint8_t stream){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

	dma_stream -> CR |= (1<<DMA_SxCR_PINC_Pos);

}

void dma_enable_circular_mode(DMA_TypeDef* dma, uint8_t stream){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

	dma_stream -> CR |= (1<<DMA_SxCR_CIRC_Pos);

}

void dma_set_priority(DMA_TypeDef* dma, uint8_t stream, DMA_Priority priority){

	DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

	dma_stream -> CR &= ~(3<<DMA_SxCR_PL_Pos);
	dma_stream -> CR |= (priority<<DMA_SxCR_PL_Pos);

}


void dma_enable(DMA_TypeDef* dma, uint8_t stream)
{
    DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

    dma_stream->CR |= (1<<DMA_SxCR_EN_Pos);
}

void dma_disable(DMA_TypeDef* dma, uint8_t stream)
{
    DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

    if (dma_stream == 0)
        return;

    dma_stream->CR &= ~(1<<DMA_SxCR_EN_Pos);

    while (dma_stream->CR & DMA_SxCR_EN)
    {
    }
}

uint8_t dma_is_enabled(DMA_TypeDef* dma, uint8_t stream)
{
    DMA_Stream_TypeDef* dma_stream = dma_get_stream(dma, stream);

    return (dma_stream->CR & DMA_SxCR_EN) ? 1 : 0;
}










