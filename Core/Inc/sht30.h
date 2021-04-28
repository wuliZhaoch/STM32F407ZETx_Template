/*
 * sht30.h
 *
 *  Created on: 2021-04-07
 *      Author: wuliZhao_ch
 */
#ifndef SHT30_H_
#define SHT30_H_
#include "main.h"
#include "system.h"
#include "bmx160.h"

/* Address Pin Connect to GND */
#define SHT30_DEVICE_ADDR           0X44    // SHT30 Device Address

#define SHT30_WRITE_ADDRESS         ((SHT30_DEVICE_ADDR << 1) | 0)  // SHT30 Device Write Address ((0x44<<1)|0) = 0x88
#define SHT30_READ_ADDRESS          ((SHT30_DEVICE_ADDR << 1) | 1)  // SHT30 Device Read Address ((0x44<<1)|1) = 0x89


typedef enum {
    /* Soft Reset Command */
    SHT30_SOFT_RESET_CMD        = 0X30A2,

    /* Measurement Commands for Single Shot Data Acquisition Mode */
    SHT30_HIGH_ENABLED_CMD      = 0X2C06,
    SHT30_MEDIUM_ENABLED_CMD    = 0X2C0D,
    SHT30_LOW_ENABLED_CMD       = 0X2C10,

    SHT30_HIGH_DISABLED_CMD     = 0X2400,
    SHT30_MEDIUM_DISABLED_CMD   = 0X240B,
    SHT30_LOW_DISABLED_CMD      = 0X2416,

    /* Measurement Commands for Periodic Data Acquisition Mode */
    SHT30_HIGH_0_5_CMD          = 0X2032,
    SHT30_MEDIUM_0_5_CMD        = 0X2024,
    SHT30_LOW_0_5_CMD           = 0X202F,

    SHT30_HIGH_1_CMD            = 0X2130,
    SHT30_MEDIUM_1_CMD          = 0X2126,
    SHT30_LOW_1_CMD             = 0X212D,

    SHT30_HIGH_2_CMD            = 0X2236,
    SHT30_MEDIUM_2_CMD          = 0X2220,
    SHT30_LOW_2_CMD             = 0X222B,

    SHT30_HIGH_4_CMD            = 0X2334,
    SHT30_MEDIUM_4_CMD          = 0X2322,
    SHT30_LOW_4_CMD             = 0X2329,

    SHT30_HIGH_10_CMD           = 0X2737,
    SHT30_MEDIUM_10_CMD         = 0X2721,
    SHT30_LOW_10_CMD            = 0X272A,

    /* Readout of Measurement Results for Periodic Mode */
    SHT30_PERIODIC_MODE_READ    = 0XE000,

    /* ART(accelerated response time) Command */
    SHT30_ART_CMD               = 0X2B32,

    /* Break command / Stop Periodic Data Acquisition Mode */
    SHT30_BREAK_CMD             = 0X3093,

    /* Reset through General Call */
    SHT30_GENERAL_CALL_CMD      = 0X0006,

    /* Heater */
    SHT30_HEATER_ENABLED_CMD    = 0X306D,
    SHT30_HEATER_DISABLED_CMD   = 0X3066,

    /* Status Register */
    SHT30_STATUS_READOUT        = 0XF32D,

    /* Clear Status Register */
    SHT30_CLEAR_STATUS_REG_CMD  = 0X3041,

}SHT30_CmdTypeDef;


#endif
