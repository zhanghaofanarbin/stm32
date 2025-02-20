#include "bsp_i2c.h"

static void I2C_Delay(void)
{
    uint8_t i;
    for(i = 0; i < 40; i++);
}

void I2C_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruc;

    RCC_AHB1PeriphClockCmd(EEPROM_I2C_GPIO_CLK, ENABLE);

    GPIO_InitStruc.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruc.GPIO_OType = GPIO_OType_OD;      // 开漏
    GPIO_InitStruc.GPIO_Pin = EEPROM_I2C_SCL_PIN | EEPROM_I2C_SDA_PIN;
    GPIO_InitStruc.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruc.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(EEPROM_I2C_GPIO_PORT, &GPIO_InitStruc);

    I2C_Stop();
}

void I2C_Start(void)
{
    EEPROM_I2C_SDA_1();
    EEPROM_I2C_SCL_1();
    I2C_Delay();
    EEPROM_I2C_SDA_0();
    I2C_Delay();
    EEPROM_I2C_SCL_0();
    
}

void I2C_Stop(void)
{
    // SCL 高电平 SDA 0->1
    EEPROM_I2C_SDA_0();
    EEPROM_I2C_SCL_1();
    I2C_Delay();
    EEPROM_I2C_SDA_1();
}

void I2C_SendByte(uint8_t u8sendByte)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        if(u8sendByte & 0x80) // 
        {
            EEPROM_I2C_SDA_1();
        }
        else
        {
            EEPROM_I2C_SDA_0();
        }
        I2C_Delay();
        EEPROM_I2C_SCL_1();
        I2C_Delay();
        EEPROM_I2C_SCL_0();
        if(i == 7)
        {
            EEPROM_I2C_SDA_1(); // 释放总线
        }
        u8sendByte <<= 1;
        I2C_Delay();
    }
}

uint8_t I2C_ReadByte(void)
{
    uint8_t i;
    uint8_t value;
    value = 0;

    for(i = 0; i < 8; i++)
    {
        value <<= 1;
        EEPROM_I2C_SCL_1();         // 数据有效
        I2C_Delay();
        if(EEPROM_I2C_SDA_READ())   // 每次读最低位
        {
            value++;        
        }
        EEPROM_I2C_SCL_0();         // 无效
        I2C_Delay();
    }
    return value;
}

/// @brief 
/// @param  
/// @return  返回1 非应答 返回0 应答
uint8_t I2C_WaitACK(void)
{
    uint8_t res;
    EEPROM_I2C_SDA_1();
    I2C_Delay();
    EEPROM_I2C_SCL_1();
    I2C_Delay();
    if(EEPROM_I2C_SDA_READ())   // 高电平 非应答信号， 低电平 应答信号
    {
        res = 1;
    }
    else
    {
        res = 0;
    }
    EEPROM_I2C_SCL_0();   
    I2C_Delay();
    return res;
}

void I2C_ACK(void)
{
    EEPROM_I2C_SDA_0();	/* CPU驱动SDA = 0 */
	I2C_Delay();
	EEPROM_I2C_SCL_1();	/* CPU产生1个时钟 */
	I2C_Delay();
	EEPROM_I2C_SCL_0();
	I2C_Delay();
	EEPROM_I2C_SDA_1();	/* CPU释放SDA总线 */
}

void I2C_NACK(void)
{
    EEPROM_I2C_SDA_1(); // 释放控制权
    I2C_Delay();
    EEPROM_I2C_SCL_1();
    I2C_Delay();
    EEPROM_I2C_SCL_0();
    I2C_Delay();
}

/// @brief 配置GPIO模拟I2C
/// @param address EEPROM 地址
/// @return 1 NACK 0 ACK
uint8_t I2C_CheckDevice(uint8_t address)
{
    uint8_t res;

    I2C_Config();

    I2C_Start();

    I2C_SendByte(address | EEPROM_I2C_WR);

    res = I2C_WaitACK();
    I2C_Stop();
    return res;
}
