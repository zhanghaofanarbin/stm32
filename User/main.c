/**
 ******************************************************************************
 * @file    main.c
 * @author  fire
 * @version V1.0
 * @date    2015-xx-xx
 * @brief   ��1.8.0�汾�⽨�Ĺ���ģ��
 ******************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:Ұ��  STM32 F407 ������
 * ��̳    :http://www.firebbs.cn
 * �Ա�    :https://fire-stm32.taobao.com
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
 * @brief  ������
 * @param  ��
 * @retval ��
 */
int main(void)
{
    /* ��������main����֮ǰ�������ļ���statup_stm32f4xx.s�Ѿ�����
     * SystemInit()������ϵͳʱ�ӳ�ʼ����168MHZ
     * SystemInit()��system_stm32f4xx.c�ж���
     * ����û����޸�ϵͳʱ�ӣ������б�д�����޸�
     */
    /* add your code here ^_^. */

    // Debug_USART_Config();
    // Usart_SendString(DEBUG_USART, "����\n");
    // printf("ʵ��2\n");

    LED_GPIO_Config();
    //LED_PURPLE;
    //Delay(0xFFFFFF);
    DMA_Config();
    while (DMA_GetFlagStatus(DMA_STREAM, DMA_FLAG_TCIF) == DISABLE) {
        // FLAG��ΪSetʱ����whileѭ��
    }
    uint8_t res;
    // for (int i = 0; i < BUFFER_SIZE; i++) {
    //   printf("dst_buffer[%d] = 0x%08X\n", i, dst_buffer[i]);
    // }
    res = BufferCmp(src_buffer, dst_buffer, BUFFER_SIZE);
    if(res == 0)
    {
        LED_GREEN;  // ���к궨�� ��Ҫ������
    }
    else
    {
        LED_RED;
    }
    while (1) {
    }
}

/*********************************************END OF FILE**********************/
