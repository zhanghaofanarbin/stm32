#include "bsp_rcc.h"

void HSI_SetSysClk()
{
   

}
void HSE_SetSysClk()
{
    __IO uint32_t HSEStartUpStatus;
    RCC_HSEConfig(RCC_HSE_ON);

    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if(HSEStartUpStatus == SUCCESS)
    {
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    }

}