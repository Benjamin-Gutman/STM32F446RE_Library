#include "dma.h"
#include <stdint.h>



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


uint8_t dma_transfer_complete(DMA_TypeDef* dma, uint8_t stream){

	switch (stream){
		case 0:
			return (dma->LISR & DMA_LISR_TCIF0) ? 1 : 0;

		case 1:
			return (dma->LISR & DMA_LISR_TCIF1) ? 1 : 0;

		case 2:
			return (dma->LISR & DMA_LISR_TCIF2) ? 1 : 0;

		case 3:
			return (dma->LISR & DMA_LISR_TCIF3) ? 1 : 0;

		case 4:
	        return (dma->HISR & DMA_HISR_TCIF4) ? 1 : 0;

		case 5:
	        return (dma->HISR & DMA_HISR_TCIF5) ? 1 : 0;

		case 6:
	        return (dma->HISR & DMA_HISR_TCIF6) ? 1 : 0;

	    case 7:
	        return (dma->HISR & DMA_HISR_TCIF7) ? 1 : 0;
	}

	return 0;
}

uint8_t dma_half_transfer(DMA_TypeDef* dma, uint8_t stream){

	switch (stream){
		case 0:
			return (dma->LISR & DMA_LISR_HTIF0) ? 1 : 0;

		case 1:
			return (dma->LISR & DMA_LISR_HTIF1) ? 1 : 0;

		case 2:
			return (dma->LISR & DMA_LISR_HTIF2) ? 1 : 0;

		case 3:
			return (dma->LISR & DMA_LISR_HTIF3) ? 1 : 0;

		case 4:
	        return (dma->HISR & DMA_HISR_HTIF4) ? 1 : 0;

		case 5:
	        return (dma->HISR & DMA_HISR_HTIF5) ? 1 : 0;

		case 6:
	        return (dma->HISR & DMA_HISR_HTIF6) ? 1 : 0;

	    case 7:
	        return (dma->HISR & DMA_HISR_HTIF7) ? 1 : 0;
	}

	return 0;

}

uint8_t dma_transfer_error(DMA_TypeDef* dma, uint8_t stream){

	switch (stream){
		case 0:
			return (dma->LISR & DMA_LISR_TEIF0) ? 1 : 0;

		case 1:
			return (dma->LISR & DMA_LISR_TEIF1) ? 1 : 0;

		case 2:
			return (dma->LISR & DMA_LISR_TEIF2) ? 1 : 0;

		case 3:
			return (dma->LISR & DMA_LISR_TEIF3) ? 1 : 0;

		case 4:
	        return (dma->HISR & DMA_HISR_TEIF4) ? 1 : 0;

		case 5:
	        return (dma->HISR & DMA_HISR_TEIF5) ? 1 : 0;

		case 6:
	        return (dma->HISR & DMA_HISR_TEIF6) ? 1 : 0;

	    case 7:
	        return (dma->HISR & DMA_HISR_TEIF7) ? 1 : 0;
	}

	return 0;

}

void dma_clear_transfer_complete(DMA_TypeDef* dma, uint8_t stream){

	switch (stream){

		case 0:
			dma->LIFCR = DMA_LIFCR_CTCIF0;
	        break;

		case 1:
			dma->LIFCR = DMA_LIFCR_CTCIF1;
	        break;

		case 2:
			dma->LIFCR = DMA_LIFCR_CTCIF2;
	        break;

		case 3:
			dma->LIFCR = DMA_LIFCR_CTCIF3;
	        break;

		case 4:
			dma->HIFCR = DMA_HIFCR_CTCIF4;
	        break;

		case 5:
			dma->HIFCR = DMA_HIFCR_CTCIF5;
	        break;

		case 6:
			dma->HIFCR = DMA_HIFCR_CTCIF6;
	        break;

		case 7:
			dma->HIFCR = DMA_HIFCR_CTCIF7;
	        break;
	}

}

void dma_clear_half_transfer(DMA_TypeDef* dma, uint8_t stream){

	switch (stream){

		case 0:
			dma->LIFCR = DMA_LIFCR_CHTIF0;
	        break;

		case 1:
			dma->LIFCR = DMA_LIFCR_CHTIF1;
	        break;

		case 2:
			dma->LIFCR = DMA_LIFCR_CHTIF2;
	        break;

		case 3:
			dma->LIFCR = DMA_LIFCR_CHTIF3;
	        break;

		case 4:
			dma->HIFCR = DMA_HIFCR_CHTIF4;
	        break;

		case 5:
			dma->HIFCR = DMA_HIFCR_CHTIF5;
	        break;

		case 6:
			dma->HIFCR = DMA_HIFCR_CHTIF6;
	        break;

		case 7:
			dma->HIFCR = DMA_HIFCR_CHTIF7;
	        break;
	}

}

void dma_clear_transfer_error(DMA_TypeDef* dma, uint8_t stream){

	switch (stream){

		case 0:
			dma->LIFCR = DMA_LIFCR_CTEIF0;
	        break;

		case 1:
			dma->LIFCR = DMA_LIFCR_CTEIF1;
	        break;

		case 2:
			dma->LIFCR = DMA_LIFCR_CTEIF2;
	        break;

		case 3:
			dma->LIFCR = DMA_LIFCR_CTEIF3;
	        break;

		case 4:
			dma->HIFCR = DMA_HIFCR_CTEIF4;
	        break;

		case 5:
			dma->HIFCR = DMA_HIFCR_CTEIF5;
	        break;

		case 6:
			dma->HIFCR = DMA_HIFCR_CTEIF6;
	        break;

		case 7:
			dma->HIFCR = DMA_HIFCR_CTEIF7;
	        break;
	}


}




