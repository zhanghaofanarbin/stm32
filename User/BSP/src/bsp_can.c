#include "bsp_can.h"

static void CAN_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(CAN_TX_GPIO_CLK| CAN_RX_GPIO_CLK);

    GPIO_PinAFConfig(CAN_TX_GPIO_PORT, CAN_TX_SOURCE,CAN_AF_PORT);
    GPIO_PinAFConfig(CAN_RX_GPIO_PORT, CAN_RX_SOURCE,CAN_AF_PORT);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = CAN_TX_PIN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CAN_TX_GPIO_PORT, &GPIO_InitStructure);

    /* configure CAN RX Pins */ 

    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    // GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
     // GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN;
    GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStructure);
}


static void CAN_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = CAN_RX_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void CAN_Mode_Config(void)
{
    CAN_InitTypeDef CAN_InitStructure;
    RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

    CAN_DeInit(CANx);
    CAN_StructInit(&CAN_InitStructure);

    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = ENABLE;
    CAN_InitStructure.CAN_AWUM = ENABLE;
    CAN_InitStructure.CAN_NART = DISABLE;  
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;
    CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;

    CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;


    CAN_InitStructure.CAN_Prescaler = 6;
    CAN_INit(CANx, &CAN_InitStructure);
}



static void CAN_Filter_Config(void)
{
    CAN_FilterInitTypeDef CAN_InitFilterStructure;
    

    CAN_InitFilterStructure.CAN_FilterNumber = 14;
    CAN_InitFilterStructure.CAN_FilterMode = CAN_FilterMode_IdMask; //掩码模式
    CAN_InitFilterStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    
    
    CAN_InitFilterStructure.CAN_FilterIdHigh = ((((u32)0x1314<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF0000)>>16; //高16位
    CAN_InitFilterStructure.CAN_FilterIdLow = (((u32)0x1314<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;            //低16位
    CAN_InitFilterStructure.CAN_FilterMaskIdHigh = 0xFFFF;
    CAN_InitFilterStructure.CAN_FilterMaskIdLow = 0xFFFF;
    CAN_InitFilterStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;        // 筛选器关联FIFO0
    CAN_FilterInit(&CAN_InitFilterStructure);
    
    CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);    // 使能CAN中断

}
void CAN_Config(void)
{
    CAN_GPIO_Config();
    CAN_NVIV_Config();
    CAN_Mode_Config();
    CAN_Filter_Config();
}
void CAN_SetMsg(CanTxMsg *TxMessage)
{
    uint8_t Counter = 0;
    TxMessage->ExtId = 0x1314;
    TxMessage->IDE = CAN_ID_EXT;
    TxMessage->RTR = CAN_RTR_DATA;
    TxMessage->DLC = 8;

    for(Counter = 0; Counter < 8; Counter++) {
        TxMessage->Data[Counter] = Counter;
    }
}
void Init_RxMes(CanRxMsg *RxMessage) 
{
    uint8_t counter = 0;
    RxMessage->ExtId = 0x00;
    RxMessage->StdId = 0x00;
    RxMessage->IDE = CAN_ID_STD;
    RxMessage->FMI = 0;
    RxMessage->DLC =0;
    for(counter = 0; counter < 8; counter++)
    {
        RxMessage->Data[counter] = 0;
    }
}