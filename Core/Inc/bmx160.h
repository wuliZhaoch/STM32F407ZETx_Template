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
#include "delay.h"
#include "usart.h"
//#include "i2c.h"

#define BMX160_SDA_PIN      GPIO_PIN_9
#define BMX160_SCL_PIN      GPIO_PIN_8
#define BMX160_GPIO_Port    GPIOB

#define I2C_SDA_SET         HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SDA_PIN, GPIO_PIN_SET)
#define I2C_SDA_RESET       HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SDA_PIN, GPIO_PIN_RESET)
#define I2C_SCL_SET         HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SCL_PIN, GPIO_PIN_SET)
#define I2C_SCL_RESET       HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SCL_PIN, GPIO_PIN_RESET)

//#define I2C_SDA(n)  (n?HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SDA_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SDA_PIN, GPIO_PIN_RESET))
//#define I2C_SCL(n)  (n?HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SCL_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SCL_PIN, GPIO_PIN_RESET))
#define READ_SDA        HAL_GPIO_ReadPin(BMX160_GPIO_Port, BMX160_SDA_PIN)

#define SDA_IN()        {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}   // Input Mode
#define SDA_OUT()       {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;}   // Output Mode

//#define IIC_HANDLE              hi2c1

#define BMX160_TIMEOUT          1000

#define ACC_DATA_LEN            6
#define GRY_DATA_LEN            6
#define MAG_DATA_LEN            8

/*
 * SDO -> GND   Device Address 0x68 (The lowest read/write bit is not included)
 * SDO -> VDDIO Device Address 0x69 (The lowest read/write bit is not included)
 *  */
#define BMX160_DEVICE_ADDR      0X68    //  BMX160 Device Address

#define BMX160_WRITE_ADDRESS    ((BMX160_DEVICE_ADDR << 1) | 0)    //  ((0X68 << 1) | 0)   Write Address
#define BMX160_READ_ADDRESS     ((BMX160_DEVICE_ADDR << 1) | 1)    //  ((0x68 << 1) | 1)   Read Address

#define BMX160_CHIPID_RET_VALUE 0XD8

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
#define BMX160_ACC_CONF         0X40
#define BMX160_ACC_RANGE        0X41

#define BMX160_GYR_CONF         0X42
#define BMX160_GYR_RANGE        0X43
#define BMX160_MAG_CONF         0X44

#define BMX160_FIFO_DOWNS       0X45
#define BMX160_FIFO_CONFIG0     0X46
#define BMX160_FIFO_CONFIG1     0X47

#define BMX160_MAG_IF0          0X4C
#define BMX160_MAG_IF1          0X4D
#define BMX160_MAG_IF2          0X4E
#define BMX160_MAG_IF3          0X4F

#define BMX160_INT_EN0          0X50
#define BMX160_INT_EN1          0X51
#define BMX160_INT_EN2          0X52

#define BMX160_INT_OUT_CTRL     0X53
#define BMX160_INT_LATCH        0X54

#define BMX160_INT_MAP0         0X55
#define BMX160_INT_MAP1         0X56
#define BMX160_INT_MAP2         0X57

#define BMX160_INT_DATA0        0X58
#define BMX160_INT_DATA1        0X59

#define BMX160_INT_LOWHIGH0     0X5A
#define BMX160_INT_LOWHIGH1     0X5B
#define BMX160_INT_LOWHIGH2     0X5C
#define BMX160_INT_LOWHIGH3     0X5D
#define BMX160_INT_LOWHIGH4     0X5E

#define BMX160_INT_MOTION0      0X5F
#define BMX160_INT_MOTION1      0X60
#define BMX160_INT_MOTION2      0X61
#define BMX160_INT_MOTION3      0X62

#define BMX160_INT_TAP0         0X63
#define BMX160_INT_TAP1         0X64

#define BMX160_INT_ORIENT0      0X65
#define BMX160_INT_ORIENT1      0X66

#define BMX160_INT_FLAT0        0X67
#define BMX160_INT_FLAT1        0X68

#define BMX160_FOC_CONF         0X69
#define BMX160_CONF             0X6A
#define BMX160_IF_CONF          0X6B
#define BMX160_PMU_TRIGGER      0X6C
#define BMX160_SELF_TEST        0X6D

#define BMX160_NV_CONF          0X70

#define BMX160_OFFSET0          0X71
#define BMX160_OFFSET1          0X72
#define BMX160_OFFSET2          0X73
#define BMX160_OFFSET3          0X74
#define BMX160_OFFSET4          0X75
#define BMX160_OFFSET5          0X76
#define BMX160_OFFSET6          0X77

#define BMX160_STEP_CNT0        0X78
#define BMX160_STEP_CNT1        0X79

#define BMX160_STEP_CONF0       0X7A
#define BMX160_STEP_CONF1       0X7B

#define BMX160_CMD              0X7E

/** Soft reset command */
#define BMX160_SOFTRESET_CMD            0xB6    //  BMX160 Reset

/** Power mode settings */
/* Accel power mode */
#define BMX160_ACCEL_SUSPEND_MODE       0x10    //  Accelerometer Suspend Mode
#define BMX160_ACCEL_NORMAL_MODE        0x11    //  Accelerometer Normal Mode
#define BMX160_ACCEL_LOWPOWER_MODE      0x12    //  Accelerometer LowPower Mode

/* Gyro power mode */
#define BMX160_GYRO_SUSPEND_MODE        0x14    //  Gyroscope Suspend Mode
#define BMX160_GYRO_NORMAL_MODE         0x15    //  Gyroscope Normal Mode
#define BMX160_GYRO_FASTSTARTUP_MODE    0x17    //  Gyroscope FastStartUP Mode

/* Magn power mode */
#define BMX160_MAGN_SUSPEND_MODE        0x18    //  Magnetometer Suspend Mode
#define BMX160_MAGN_NORMAL_MODE         0x19    //  Magnetometer Normal Mode
#define BMX160_MAGN_LOWPOWER_MODE       0x1A    //  Magnetometer LowPower Mode




void BMX160_I2C_Init(void);             // I2C Initialize
void BMX160_I2C_Start(void);            // I2C Start Signal
void BMX160_I2C_Stop(void);             // I2C Stop Signal

uint8_t BMX160_I2C_Wait_Ack(void);      // I2C Wait Ack
void BMX160_I2C_Ack(void);              // I2C Ack
void BMX160_I2C_NAck(void);             // I2C NAck

void BMX160_I2C_WriteByte(uint8_t cmd);     // I2C Write Byte
uint8_t BMX160_I2C_ReadByte(uint8_t ack);   // I2C Read Byte

uint8_t BMX160_Write_Byte(uint8_t reg, uint8_t data);   // BMX160 Write one Byte
uint8_t BMX160_Read_Byte(uint8_t reg);                  // BMX160 Read one Byte

uint8_t BMX160_Write_MultiByte(uint8_t DeviceAddr, uint8_t reg, uint8 *rev_buffer, uint16_t Size);  // BMX160 Write Multi Byte
uint8_t BMX160_Read_MultiByte(uint8_t DeviceAddr, uint8_t reg, uint8 *rev_buffer, uint16_t Size);   // BMX160 Write Multi Byte

void BMX160_Config_Init(void);          // The BMX160 configuration is initialized
uint16_t BMX160_GetTemperature(void);   // Get BMX160 temperature
int16_t BMX160_Data_Conversion(uint16_t SensorData);   // Acceleration Data Conversion
void BMX160_GetAccelerometer(uint8 *rev_buffer);    // Get BMX160 Accelerometer Value
void BMX160_GetGyroscope(uint8 *rev_buffer);        // Get BMX160 Gyroscope Value
void BMX160_GetMagnetometer(uint8 *rev_buffer);     // Get BMX160 Magnetometer Value

#endif
