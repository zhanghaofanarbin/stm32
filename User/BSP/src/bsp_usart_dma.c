#include "bsp_usart_dma.h"

uint8_t SendBuffer[8];

void Debug_DMA_USART_Config(void){
    
    DMA_InitTypeDef DMA_InitStrc;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

    DMA_DeInit(DMA_USART1_STREAM);
    while(DMA_GetCmdStatus(DMA_USART1_STREAM)!= DISABLE)
    {}

    DMA_InitStrc.DMA_Channel = DMA_USART1_CHANNEL;
    DMA_InitStrc.DMA_PeripheralBaseAddr =  DMA_USART1_BASEADDR;     // 串口地址
    DMA_InitStrc.DMA_Memory0BaseAddr = (u32)SendBuffer;    
    DMA_InitStrc.DMA_DIR = DMA_DIR_MemoryToPeripheral;  // 内存->外设
    
    DMA_InitStrc.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStrc.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;

    DMA_InitStrc.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStrc.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_InitStrc.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStrc.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 地址不递增
    DMA_InitStrc.DMA_Mode = DMA_Mode_Normal;
    
    DMA_InitStrc.DMA_BufferSize = BUFFERSIZE;
    DMA_InitStrc.DMA_Priority = DMA_Priority_High;
    DMA_InitStrc.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  // 8位
    DMA_InitStrc.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  //8 bit

    DMA_Init(DMA_USART1_STREAM, &DMA_InitStrc);

    DMA_Cmd(DMA_USART1_STREAM, ENABLE);
    while(DMA_GetCmdStatus(DMA_USART1_STREAM) != ENABLE)
    {}
}

void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruc;
    USART_InitTypeDef USART_InitStruc;

    RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK | DEBUG_USART_TX_GPIO_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);

    GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT,DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);
    GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT,DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);

    GPIO_InitStruc.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruc.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruc.GPIO_Pin = DEBUG_USART_RX_PIN;
    GPIO_InitStruc.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruc.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruc);

    GPIO_InitStruc.GPIO_Mode = GPIO_Mode_AF; // 感觉没用
    GPIO_InitStruc.GPIO_Pin = DEBUG_USART_TX_PIN;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruc);

    

    USART_InitStruc.USART_BaudRate = DEBUG_USART_BAUDRATE;
    USART_InitStruc.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruc.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruc.USART_Parity = USART_Parity_No ;        // 奇偶校验
    USART_InitStruc.USART_StopBits = USART_StopBits_1;                      // 停止位数量 1
    USART_InitStruc.USART_WordLength = USART_WordLength_8b;                    // 数据帧字长 8

    USART_Init(DEBUG_USART, &USART_InitStruc);

    //NVIC_Configuration();
    //USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);     // 
    USART_Cmd(DEBUG_USART, ENABLE);
}
