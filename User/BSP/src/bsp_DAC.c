#include "bsp_DAC.h"

const uint16_t Sine12bit[32] = {
	2048	, 2460	, 2856	, 3218	, 3532	, 3786	, 3969	, 4072	,
	4093	, 4031	, 3887	, 3668	, 3382	, 3042	,	2661	, 2255	, 
	1841	, 1435	, 1054	, 714		, 428		, 209		, 65		, 3			,
	24		, 127		, 310		, 564		, 878		, 1240	, 1636	, 2048

};

uint32_t DualSine12bit[32];

static void DAC_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitStructure;

    RCC_AHB1PeriphClockCmd(DAC_CH1_GPIO_CLK | DAC_CH2_GPIO_CLK, ENABLE);

    RCC_APB1PeriphClockCmd(DAC_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = DAC_CH1_GPIO_PIN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(DAC_CHI_GPIO_PORT, & GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = DAC_CH2_GPIO_PIN;
    GPIO_Init(DAC_CH2_GPIO_PORT, &GPIO_InitStructure);

    /* 配置DAC 通道1*/
    DAC_InitStructure.DAC_Trigger = DAC_TRIGGER;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_Init(DAC_CH1_CHANNEL, &DAC_InitStructure);

    /*配置DAC 通道2*/
    DAC_Init(DAC_CH2_CHANNEL, &DAC_InitStructure);
    DAC_Cmd(DAC_Channel_1, ENABLE);
    DAC_Cmd(DAC_Channel_2, ENABLE);

    DAC_DMACmd(DAC_Channel_1, ENABLE);

}

static void DAC_DMA_Config(void)
{

}

/* 配置TIM
*/
static void DAC_TIM_Config(void)
{
    //TIM_TimeBaseInitTypeDef TIM_TimeVBaseStructure;
    //TIM_TimeVBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
}

void DAC_Mode_Init(void)
{
    uint32_t Idx = 0;
    DAC_Config();
    DAC_TIM_Config();
    for(Idx = 0; Idx < 32; Idx++)
    {
        //DualSine12bit[Idx] = (Sine12bit[Idx] << 16) + (Sine12bit[idx]);
    }

    DAC_DMA_Config();
}