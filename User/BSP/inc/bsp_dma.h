#ifndef __BSP_DMA_H
#define __BSP_DMA_H

#include "stm32f4xx.h"

#define BUFFER_SIZE         32
#define DMA_STREAM          DMA2_Stream0
#define DMA_CHANNEL         DMA_Channel_0
#define DMA_STREAM_CLK      RCC_AHB1Periph_DMA2
#define DMA_FLAG_TCIF       DMA_FLAG_TCIF0
#define TIMEOUT_MAX         10000


extern const uint32_t src_buffer[BUFFER_SIZE]; 

extern uint32_t dst_buffer[BUFFER_SIZE];

void DMA_Config(void);
uint8_t BufferCmp(const uint32_t* pbuffer, uint32_t* pbuffer1, uint16_t BufferLength);

#endif