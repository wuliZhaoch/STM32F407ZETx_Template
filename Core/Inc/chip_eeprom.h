/*
 * chip_eeprom.h
 *
 *  Created on: 2020-04-06
 *      Author: wuliZhao_ch
 *       brief: Source file of chip_eeprom.h
 *   attention: Use for in-chip EEPROM.
 */

#ifndef CHIP_EEPROM_H_
#define CHIP_EEPROM_H_
#include "main.h"
#include "system.h"


#define EEPROM_BASE_START_ADDRESS       0x08080000
#define EEPROM_BASE_ENDADDRESS          0x080807FF
#define EEPROM_TYPE_SIZE                0x7FF       // 2KBytes

#define PEKEY1      0x89ABCDEF
#define PEKEY2      0x02030405


void chip_eeprom_readByte(uint16_t Address, uint8_t *read_buffer, uint8_t length);
void chip_eeprom_writeByte(uint16_t Address, uint8_t *write_data, uint8_t length);

#endif
