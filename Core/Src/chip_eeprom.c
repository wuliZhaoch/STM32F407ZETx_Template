/*
 * chip_eeprom.c
 *
 *  Created on: 2020-04-06
 *      Author: wuliZhao_ch
 *       brief: Source file of chip_eeprom.c
 *   attention: Use for in-chip EEPROM.
 */
#include "chip_eeprom.h"




void chip_eeprom_readByte(uint16_t Address, uint8_t *read_buffer, uint8_t length)
{
    uint8_t *waddr;
    waddr = (uint8_t *)(EEPROM_BASE_START_ADDRESS + Address);
    while (length--) {
        *read_buffer++ = *waddr++;
    }
}

void chip_eeprom_writeByte(uint16_t Address, uint8_t *write_data, uint8_t length)
{
    uint32_t waddr;
    waddr = EEPROM_BASE_START_ADDRESS + Address;

//    HAL_FLASHEx_DATAEEPROM_Unlock();
    HAL_FLASH_Unlock();

    HAL_Delay(200);
    for (uint8_t i = 0; i < length; i++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, waddr + i, write_data[i]);
    }
//    HAL_FLASHEx_DATAEEPROM_Lock();
    HAL_FLASH_Lock();

}
