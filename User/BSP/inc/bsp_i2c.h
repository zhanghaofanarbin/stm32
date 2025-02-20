#ifndef __BSP_I2C_H
#define __BSP_I2C_H

#include "stm32f4xx.h"

#define EEPROM_I2C_WR 0 /* 写控制bit */
#define EEPROM_I2C_RD 1 /* 读控制bit */

/* 定义I2C总线连接的GPIO端口, 用户只需要修改下面4行代码即可任意改变SCL和SDA的引脚 */
#define EEPROM_I2C_GPIO_PORT GPIOB                /* GPIO端口 */
#define EEPROM_I2C_GPIO_CLK  RCC_AHB1Periph_GPIOB /* GPIO端口时钟 */
#define EEPROM_I2C_SCL_PIN   GPIO_Pin_8           /* 连接到SCL时钟线的GPIO */
#define EEPROM_I2C_SDA_PIN   GPIO_Pin_9           /* 连接到SDA数据线的GPIO */

#if 1 
    #define EEPROM_I2C_SCL_1()  GPIO_SetBits(EEPROM_I2C_GPIO_PORT, EEPROM_I2C_SCL_PIN)
    #define EEPROM_I2C_SDA_1()  GPIO_SetBits(EEPROM_I2C_GPIO_PORT, EEPROM_I2C_SDA_PIN)
    #define EEPROM_I2C_SCL_0()  GPIO_ResetBits(EEPROM_I2C_GPIO_PORT, EEPROM_I2C_SCL_PIN)
    #define EEPROM_I2C_SDA_0()  GPIO_ResetBits(EEPROM_I2C_GPIO_PORT, EEPROM_I2C_SDA_PIN)

    #define EEPROM_I2C_SDA_READ()   GPIO_ReadInputDataBit(EEPROM_I2C_GPIO_PORT, EEPROM_I2C_SDA_PIN)
#else

#endif

void I2C_Config(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(uint8_t u8sendByte);
uint8_t I2C_ReadByte(void);
uint8_t I2C_WaitACK(void);
void I2C_ACK(void);
void I2C_NACK(void);
uint8_t I2C_CheckDevice(uint8_t address);



#endif
