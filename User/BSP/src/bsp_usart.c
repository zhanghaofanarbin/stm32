#include "bsp_usart.h"


static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStruc;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);         // 嵌套向量中断控制器 组选择
    NVIC_InitStruc.NVIC_IRQChannel = DEBUG_USART_IRQ;
    NVIC_InitStruc.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruc.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruc.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruc);
}

void Debug_USART_Config(void) 
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

    NVIC_Configuration();

    USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);     // 
    USART_Cmd(DEBUG_USART, ENABLE);
}
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
    USART_SendData(pUSARTx, ch);
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);       // 等待发送完

}
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
    unsigned int k = 0;
    do
    {
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    }while(*(str+k) != '\0');

    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
    {}      // 等待发送完
}

void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
    uint8_t half_h, half_l;
    half_h = (ch&0XFF00)>>8;
    half_l = ch&0XFF;

    USART_SendData(pUSARTx, half_h);
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);       // 等待发送完

    USART_SendData(pUSARTx, half_l);
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);       // 等待发送完
}

int fputc(int ch, FILE* f)
{
    USART_SendData(DEBUG_USART, (uint8_t)ch);
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);	
    return (ch);
}
int fgetc(FILE* f)
{
    while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(DEBUG_USART);
}