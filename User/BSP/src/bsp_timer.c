#include "bsp_timer.h"

void TIMx_Configuration(void)
{

} 

static void TIMx_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_initStructure;
    DMA_InitTypeDef DMA_initStructure;

    RCC_AHB1PeriphClockCmd(ADVANCE_OCPWM_GPIO_CLK, ENABLE);
    // 引脚复用
    GPIO_PinAFConfig(ADVANCE_OCPWM_PORT, ADVANCE_OCPWM_PINSOUCE, ADVANCE_OCPWM_AF);

    GPIO_initStructure.GPIO_Pin = ADVANCE_OCPWM_PIN;
    GPIO_initStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_initStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_initStructure.GPIO_PuPd =GPIO_PuPd_NOPULL;
    GPIO_initStructure.GPIO_Speed = GPIO_Speed_100MHz;

    RCC_AHB1PeriphClockCmd(TIM_DMA_CLK, ENABLE);

    DMA_DeInit(TIM_DMA_STREAM);
    while (DMA_GetCmdStatus(TIM_DMA_STREAM) != DISABLE)  
    {
        DMA_initStructure.DMA_Channel = TIM_DMA_CHANNEL;
        DMA_initStructure.DMA_PeripheralBaseAddr = (uint32_t)(TIM_DMA_ADDRESS);
        //DMA_initStructure.DMA_Memory0BaseAddr = (uint32_t)aSRC_Buffer;
        
    }
}