/*
 * sht30.h
 *
 *  Created on: 2021-04-07
 *      Author: wuliZhao_ch
 */

#ifndef SHT30_H_
#define SHT30_H_
#include "system.h"
#include "main.h"
#include "bmx160.h"
//#include "delay.h"

/* Address Pin Connect to GND */
#define SHT30_DEVICE_ADDR           0X44    // SHT30 Device Address

#define SHT30_WRITE_ADDRESS         (SHT30_DEVICE_ADDR << 1) | 0  // SHT30 Device Write Address ((0x44<<1)|0) = 0x88
#define SHT30_READ_ADDRESS          (SHT30_DEVICE_ADDR << 1) | 1  // SHT30 Device Read Address ((0x44<<1)|1) = 0x89

/* Soft Reset Command */
#define SHT30_SOFT_RESET_CMD        0x30A2
/* Measurement Commands for Single Shot Data Acquisition Mode */
#define SHT30_HIGH_ENABLED_CMD      0x2C06
#define SHT30_MEDIUM_ENABLED_CMD    0x2C0D
#define SHT30_LOW_ENABLED_CMD       0x2C10

#define SHT30_HIGH_DISABLED_CMD     0x2400
#define SHT30_MEDIUM_DISABLED_CMD   0x240B
#define SHT30_LOW_DISABLED_CMD      0x2416

/* Measurement Commands for Periodic Data Acquisition Mode */
#define SHT30_HIGH_0_5_CMD          0x2032
#define SHT30_MEDIUM_0_5_CMD        0x2024
#define SHT30_LOW_0_5_CMD           0x202F

#define SHT30_HIGH_1_CMD            0x2130
#define SHT30_MEDIUM_1_CMD          0x2126
#define SHT30_LOW_1_CMD             0x212D

#define SHT30_HIGH_2_CMD            0x2236
#define SHT30_MEDIUM_2_CMD          0x2220
#define SHT30_LOW_2_CMD             0x222B

#define SHT30_HIGH_4_CMD            0x2334
#define SHT30_MEDIUM_4_CMD          0x2322
#define SHT30_LOW_4_CMD             0x2329

#define SHT30_HIGH_10_CMD           0x2737
#define SHT30_MEDIUM_10_CMD         0x2721
#define SHT30_LOW_10_CMD            0x272A

/* Readout of Measurement Results for Periodic Mode */
#define SHT30_PERIODIC_MODE_READ    0xE000

/* ART(accelerated response time) Command */
#define SHT30_ART_CMD               0x2B32

/* Break command / Stop Periodic Data Acquisition Mode */
#define SHT30_BREAK_CMD             0x3093

/* Reset through General Call */
#define SHT30_GENERAL_CALL_CMD      0x0006

/* Heater */
#define SHT30_HEATER_ENABLED_CMD    0x306D
#define SHT30_HEATER_DISABLED_CMD   0x3066

/* Status Register */
#define SHT30_STATUS_READOUT        0xF32D

/* Clear Status Register */
#define SHT30_CLEAR_STATUS_REG_CMD  0x3041



void SHT30_I2C_WriteByte(uint8_t cmd);
uint8_t SHT30_I2C_ReadByte(uint8_t ack);

void SHT30_Write_Byte(uint8_t Address, uint16_t reg);
void SHT30_Read_Byte(uint8_t Address, uint16_t reg, uint8_t *buff);

#endif
