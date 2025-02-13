#include "bsp_key.h"


void Key_GPIO_Init() {

    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(KEY1_CLK|KEY2_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(KEY1_GPIO_POET, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
    GPIO_Init(KEY2_GPIO_POET, &GPIO_InitStructure);
}

uint8_t Key_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
    {
        while(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON);
        return KEY_ON;
    }
    else
        return KEY_OFF;
}