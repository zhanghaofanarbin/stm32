#ifndef __BSP_EEPROM_H
#define __BSP_EEPROM_H

#include "stm32f4xx.h"

#define EEPROM_DEV_ADDR  0xA0
#define EEPROM_PAGE_SIZE 8
#define EEPROM_SIZE      256 // 8*256 = 2K Byte

uint8_t EEPROM_CheckOK(void);
void EEPROM_Erase(void);
uint8_t EEPROM_Test(void);

uint8_t ReadByte(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t WriteByte(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);

#endif