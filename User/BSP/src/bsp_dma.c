#include "bsp_dma.h"
#include "bsp_led.h"
uint32_t const src_buffer[BUFFER_SIZE] = {
    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80
};
uint32_t dst_buffer[BUFFER_SIZE] = {1};

void DMA_Config(void)
{
    RCC_AHB1PeriphClockCmd(DMA_STREAM_CLK, ENABLE);

    DMA_DeInit(DMA_STREAM); // 复位

    while (DMA_GetCmdStatus(DMA_STREAM) != DISABLE) {}

    DMA_InitTypeDef DMA_Struc;
    __IO uint32_t    Timeout = TIMEOUT_MAX;

    DMA_Struc.DMA_Channel            = DMA_CHANNEL;
    DMA_Struc.DMA_Memory0BaseAddr    = (uint32_t)dst_buffer;
    DMA_Struc.DMA_PeripheralBaseAddr = (uint32_t)src_buffer;         
    DMA_Struc.DMA_BufferSize         = (uint32_t)BUFFER_SIZE;
    DMA_Struc.DMA_DIR                = DMA_DIR_MemoryToMemory;

    DMA_Struc.DMA_FIFOMode           = DMA_FIFOMode_Disable;    
    DMA_Struc.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;

    DMA_Struc.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
    DMA_Struc.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word; // 数据大小
    DMA_Struc.DMA_MemoryInc          = DMA_MemoryInc_Enable;    // 数据递增

    DMA_Struc.DMA_Mode               = DMA_Mode_Normal;         // 一次传输模式
    
    DMA_Struc.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single; //
    DMA_Struc.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_Struc.DMA_PeripheralInc      = DMA_PeripheralInc_Enable;
    DMA_Struc.DMA_Priority           = DMA_Priority_High; // 优先级

    DMA_Init(DMA_STREAM, &DMA_Struc);

    DMA_ClearFlag(DMA_STREAM, DMA_FLAG_TCIF);

    DMA_Cmd(DMA_STREAM, ENABLE);

    /* 检测DMA数据流是否有效并带有超时检测功能 */
  Timeout = TIMEOUT_MAX;
  while ((DMA_GetCmdStatus(DMA_STREAM) != ENABLE) && (Timeout-- > 0))
  {
  }
   
  /* 判断是否超时 */
  if (Timeout == 0)
  {
    /* 超时就让程序运行下面循环：RGB彩色灯闪烁 */
    while (1)
    {      
      LED_RED;
      Delay(0xFFFFFF);
      LED_RGBOFF;
      Delay(0xFFFFFF);
    }
  } 
}

uint8_t BufferCmp(const uint32_t* pbuffer, uint32_t* pbuffer1, uint16_t BufferLength)
{
    while(BufferLength--)
    {
        if(*pbuffer != *pbuffer1)
            return 0;
        pbuffer++;
        pbuffer1++;
    }
    return 1;
}