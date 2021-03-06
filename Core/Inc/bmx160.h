/*
 * bmx160.h
 *
 *  Created on: 2021-04-07
 *      Author: wuliZhao_ch
 */
#ifndef BMX160_H_
#define BMX160_H_

#include "main.h"
#include "system.h"
#include "i2c.h"

//#define IIC_HANDLE              hi2c1

//#define BMX160_TIMEOUT          1000

#define BMX160_WRITE_ADDRESS    0XD0
#define BMX160_READ_ADDRESS     0XD1

/* Chip Only Read Register  */
#define BMX160_CHIPID           0x00
#define BMX160_ERR_REG          0X02
#define BMX160_PMU_STATUS       0X03

#define BMX160_DATA0            0X04
#define BMX160_DATA1            0X05
#define BMX160_DATA2            0X06
#define BMX160_DATA3            0X07
#define BMX160_DATA4            0X08
#define BMX160_DATA5            0X09
#define BMX160_DATA6            0X0A
#define BMX160_DATA7            0X0B
#define BMX160_DATA8            0X0C
#define BMX160_DATA9            0X0D
#define BMX160_DATA10           0X0E
#define BMX160_DATA11           0X0F
#define BMX160_DATA12           0X10
#define BMX160_DATA13           0X11
#define BMX160_DATA14           0X12
#define BMX160_DATA15           0X13
#define BMX160_DATA16           0X14
#define BMX160_DATA17           0X15
#define BMX160_DATA18           0X16
#define BMX160_DATA19           0X17

#define BMX160_SENSORTIME0      0X18
#define BMX160_SENSORTIME1      0X19
#define BMX160_SENSORTIME2      0X1A

#define BMX160_STATUS           0X1B

#define BMX160_INT_STATUS0      0X1C
#define BMX160_INT_STATUS1      0X1D
#define BMX160_INT_STATUS2      0X1E
#define BMX160_INT_STATUS3      0X1F

#define BMX160_TEMPERATURE0     0X20
#define BMX160_TEMPERATURE1     0X21

#define BMX160_FIFO_LENGTH0     0X22
#define BMX160_FIFO_LENGTH1     0X23
#define BMX160_FIFO_DATA        0X24

/* Chip Only Read/Write Register  */






#endif
