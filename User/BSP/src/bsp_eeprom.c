#include "bsp_eeprom.h"
#include "bsp_i2c.h"
#include "bsp_usart.h"


uint8_t EEPROM_CheckOK(void)
{
    if(I2C_CheckDevice(EEPROM_DEV_ADDR) == 0)
    {
        return 1;
    }
    else
    {
        I2C_Stop();
        return 0;
    }
}

void EEPROM_Erase(void)
{
    uint8_t buf[EEPROM_SIZE];
    for(int i = 0 ; i < EEPROM_SIZE; i++)
    {
        buf[i] = 0xFF;
    }
    if(WriteByte(buf, 0, EEPROM_SIZE) == 0)
    {
        printf("擦除失败!\r\n");
    }
    else
    {
        printf("擦除成功!\r\n");
    }

}

static void EEPROM_Delay(__IO uint32_t ncount)
{
    for(; ncount != 0; ncount--);
}

uint8_t EEPROM_Test(void)
{
    uint8_t write_buf[EEPROM_SIZE];
    uint8_t read_buf[EEPROM_SIZE];
    uint16_t i;
    if(EEPROM_CheckOK() == 0)
    {
        printf("设备连接失败\r\n");
        return 0;
    }
    for(int i = 0; i < EEPROM_SIZE; i++)
    {
        write_buf[i] = i;
    }
    if(WriteByte(write_buf, 0, EEPROM_SIZE) == 0)
    {
        printf("写EEPROM错误");        
    }
    else
    {
        printf("写成功");
    }
    EEPROM_Delay(0xFFFFF);
    if(ReadByte(read_buf,0, EEPROM_SIZE) == 0)
    {
        printf("读EEPROM错误");        
        return 0;
    }
    else
    {
        printf("读成功");
    }
    for(i = 0; i < EEPROM_SIZE; i++)
    {
        if(read_buf[i] != write_buf[i])
        {
            printf("0x%02X", read_buf[i]);
            printf("读写不一致");
            return 0;
        }
        printf("0x%02X", read_buf[i]);
        if(i & 15 == 15)
            printf("\r\n");
    }
    printf(" 读写测试成功");
    return 1;
}

uint8_t ReadByte(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize)
{
    //  1. 向EEPROM发送地址
    I2C_Start();

    I2C_SendByte(EEPROM_DEV_ADDR| EEPROM_I2C_WR);   //写

    if(I2C_WaitACK() != 0)
    {
        goto cmd_fail;
    }
    I2C_SendByte((uint8_t)_usAddress);
    if(I2C_WaitACK() != 0)
    {
        goto cmd_fail;
    }

    // 2. 
    I2C_Start();

    I2C_SendByte(EEPROM_DEV_ADDR| EEPROM_I2C_RD);   // 读

    if(I2C_WaitACK() != 0)
    {
        goto cmd_fail;
    }
    for(int i = 0; i < _usSize; i++)
    {
        _pReadBuf[i] = I2C_ReadByte();
        if( i != _usSize - 1)
        {
            I2C_ACK();
        }
        else
        {
            I2C_NACK();
        }
    }
    I2C_Stop();
    return 1;
    
    cmd_fail:
        I2C_Stop();
        return 0;
}



uint8_t WriteByte(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize)
{
    uint16_t i, m;
    uint16_t usAddr;
    usAddr = _usAddress;
    for(int i = 0; i < _usSize; i++)
    {
        // 页面首地址或 第一个字节 发送 启动信号和地址
        if(i == 0 || (usAddr & EEPROM_PAGE_SIZE - 1) == 0)
        {
            I2C_Stop();
            
            for(m = 0; m < 1000; m++)
            {
                I2C_Start(); // 启动                                
                I2C_SendByte(EEPROM_DEV_ADDR | EEPROM_I2C_WR);  // 发送设备地址 写
                if(I2C_WaitACK() == 0)
                {
                    break;
                }
            }
            if(m == 1000)
            {
                goto cmd_fail;
            }
            I2C_SendByte((uint8_t)usAddr);      // 发送字节地址
            if(I2C_WaitACK() != 0)              // 等待ack
            {
                goto cmd_fail;
            }
        }
        I2C_SendByte((uint8_t)_pWriteBuf[i]);  // 写入数据
        if(I2C_WaitACK() != 0)
        {
            goto cmd_fail;
        }
        usAddr++;
    }
    
    cmd_fail:
        I2C_Stop();
        return 0;
}


