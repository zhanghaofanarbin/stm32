#ifndef __BSP_DAC_H
#define __BSP_DAC_H


#include "stm32f4xx.h"

#define DAC_DHR12RD_ADDRESS         (uint32_t)(DAC_BASE + 0x20)

#define DAC_CLK                     RCC_APB1Periph_DAC
#define DAC_TIM                     TIM2
#define DAC_TIM_CLK                 RCC_APB1Periph_TIM2
#define DAC_TRIGGER                 DAC_Trigger_T2_TRGO

#define DAC_DMA_CLK                 RCC_AHB1Periph_DMA1
#define DAC_CHANNEL                 DMA_Channel_7
#define DAC_DMA_STREAM              DMA1_Stream5

#define DAC_CH1_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define DAC_CHI_GPIO_PORT           GPIOA
#define DAC_CH1_GPIO_PIN            GPIO_Pin_4
#define DAC_CH1_CHANNEL             DAC_Channel_1

#define DAC_CH2_GPIO_CLK            RCC_AHB1Periph_GPIOA
#define DAC_CH2_GPIO_PORT           GPIOA
#define DAC_CH2_GPIO_PIN            GPIO_Pin_5
#define DAC_CH2_CHANNEL             DAC_Channel_2

/*
DAC初始化函数
*/
void DAC_Mode_init(void);

#endif