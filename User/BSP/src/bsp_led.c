#include "bsp_led.h"

void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(LED_RED_GPIO_CLK|LED_GREEN_GPIO_CLK|LED_BLUE_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED_RED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(LED_RED_GPIO_PORT , &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED_BLUE_GPIO_PIN;
    GPIO_Init(LED_BLUE_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED_GREEN_GPIO_PIN;
    GPIO_Init(LED_GREEN_GPIO_PORT, &GPIO_InitStructure);
    LED_RGBOFF;
}