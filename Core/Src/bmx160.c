/*
 * bmx160.c
 *
 *  Created on: 2020-04-07
 *      Author: wuliZhao_ch
 *       brief: BMX160 Drive
 */
#include "bmx160.h"





/**
  * @brief  Function Write a Byte to BMX160
  * @param  Addr: Start Write Address
  * @param  Data: Data Content Write
  * @param  Time_out: Timeout duration
  * @retval HAL status
  */
uint8_t BMX160_ByteWrite(uint16_t Addr, uint8_t* data, uint32_t Time_out)
{
    return HAL_I2C_Mem_Write(&IIC_HANDLE, BMX160_WRITE_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, data, 1, Time_out);
}

/**
  * @brief  Function Write MultiByte to BMX160
  * @param  Addr: Start Write Address
  * @param  Data: Data Content Write
  * @param  size: Write data len
  * @param  Time_out: Timeout duration
  * @retval HAL status
  */
uint8_t BMX160_MultiByteWrite(uint16_t Addr, uint8_t* data, uint16_t size, uint32_t Time_out)
{
    return HAL_I2C_Mem_Write(&IIC_HANDLE, BMX160_WRITE_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, data, size, Time_out);
}

/**
  * @brief  Function Read a Byte to BMX160
  * @param  Addr: Start Reading the Starting Address
  * @param  read_buff: Data Content Read
  * @param  Time_out: Timeout duration
  * @retval HAL status
  */
uint8_t BMX160_ByteRead(uint16_t Addr, uint8_t* read_buff, uint32_t Time_out)
{
    return HAL_I2C_Mem_Read(&IIC_HANDLE, BMX160_READ_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, read_buff, 1, Time_out);
}

/**
  * @brief  Function Read MultiByte to BMX160
  * @param  Addr: Start Reading the Starting Address
  * @param  read_buff: Data Content Read
  * @param  Size: Amount of data to be sent
  * @param  Time_out: Timeout duration
  * @retval HAL status
  */
uint8_t BMX160_MultiByteRead(uint16_t Addr, uint8_t* read_buff, uint16_t size, uint32_t Time_out)
{
    return HAL_I2C_Mem_Read(&IIC_HANDLE, BMX160_READ_ADDRESS, Addr, I2C_MEMADD_SIZE_8BIT, read_buff, size, Time_out);
}
