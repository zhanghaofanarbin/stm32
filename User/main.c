/**
 ******************************************************************************
 * @file    main.c
 * @author  fire
 * @version V1.0
 * @date    2015-xx-xx
 * @brief   用1.8.0版本库建的工程模板
 ******************************************************************************
 * @attention
 *
 * 实验平台:野火  STM32 F407 开发板
 * 论坛    :http://www.firebbs.cn
 * 淘宝    :https://fire-stm32.taobao.com
 *
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include "bsp_usart.h"
#include "bsp_dma.h"
#include "bsp_led.h"
#include "stdio.h"
void Delay(__IO uint32_t nCount);
void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

/**
 * @brief  主函数
 * @param  无
 * @retval 无
 */
int main(void)
{
    /* 程序来到main函数之前，启动文件：statup_stm32f4xx.s已经调用
     * SystemInit()函数把系统时钟初始化成168MHZ
     * SystemInit()在system_stm32f4xx.c中定义
     * 如果用户想修改系统时钟，可自行编写程序修改
     */
    /* add your code here ^_^. */

    // Debug_USART_Config();
    // Usart_SendString(DEBUG_USART, "测试\n");
    // printf("实验2\n");

    LED_GPIO_Config();
    //LED_PURPLE;
    //Delay(0xFFFFFF);
    DMA_Config();
    while (DMA_GetFlagStatus(DMA_STREAM, DMA_FLAG_TCIF) == DISABLE) {
        // FLAG变为Set时跳出while循环
    }
    uint8_t res;
    // for (int i = 0; i < BUFFER_SIZE; i++) {
    //   printf("dst_buffer[%d] = 0x%08X\n", i, dst_buffer[i]);
    // }
    res = BufferCmp(src_buffer, dst_buffer, BUFFER_SIZE);
    if(res == 0)
    {
        LED_GREEN;  // 多行宏定义 需要加括号
    }
    else
    {
        LED_RED;
    }
    while (1) {
    }
}

/*********************************************END OF FILE**********************/
