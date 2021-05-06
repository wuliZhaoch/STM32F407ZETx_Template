/*
 * sht30.c
 *
 *  Created on: 2020-04-28
 *      Author: wuliZhao_ch
 *       brief: SHT30 Drive
 */
#include "sht30.h"

uint8_t CheckCrc8(uint8_t* const message)
{
    uint8_t  remainder;        // remainder
    uint8_t  i = 0, j = 0;

    /* 初始化 */
    remainder = CRC8_INITIALIZATION;

    for(j = 0; j < 2; j++)
    {
        remainder ^= message[j];

        /* 从最高位开始依次计算  */
        for (i = 0; i < 8; i++)
        {
            if (remainder & 0x80)
            {
                remainder = (remainder << 1)^CRC8_POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }

    /* 返回计算的CRC码 */
    return remainder;
}


/**
  * @brief  The SHT30 I2C Write Byte
  * @retval none
  */
void SHT30_I2C_WriteByte(uint8_t cmd)
{
     uint8_t i = 0;
     SDA_OUT();
     I2C_SCL_RESET;
     for (i= 0; i < 8; i++) {
         if ((cmd&0x80) >> 7)
         {
             I2C_SDA_SET;
         } else {
             I2C_SDA_RESET;
         }
         cmd <<= 1;
         HAL_Delay_us(2);
         I2C_SCL_SET;

         HAL_Delay_us(2);
         I2C_SCL_RESET;
         HAL_Delay_us(2);
    }
}

/**
  * @brief  The SHT30 I2C Read Byte
  * @retval Read data
  */
uint8_t SHT30_I2C_ReadByte(uint8_t ack)
{
    uint8_t i = 0;
    uint8_t Receive_Data = 0;
    SDA_IN();
    for (i = 0; i < 8; i++)
    {
        I2C_SCL_RESET;
        HAL_Delay_us(2);
        I2C_SCL_SET;
        Receive_Data <<= 1;
        if(READ_SDA) {
            Receive_Data++;
        }
        HAL_Delay_us(1);
    }
    if (!ack){
        I2C_NAck();
    } else {
        I2C_Ack();
    }
    return Receive_Data;
}

/**
  * @brief  The SHT30 Write Byte
  * @retval none
  */
void SHT30_Write_Byte(uint8_t Device_Write_addr, uint16_t reg)
{
    SHT30_I2C_WriteByte(Device_Write_addr);
    if (I2C_Wait_Ack()) {
        I2C_Stop();
    }
    SHT30_I2C_WriteByte(reg >> 8);
    if (I2C_Wait_Ack()) {
        I2C_Stop();
    }
    SHT30_I2C_WriteByte(reg);
    if (I2C_Wait_Ack()) {
        I2C_Stop();
    }
}

/**
  * @brief  The SHT30 Write Commend
  * @retval none
  */
void SHT30_Write_Commend(uint16_t reg)
{
    I2C_Start();
    SHT30_Write_Byte(SHT30_WRITE_ADDRESS, reg);
    I2C_Stop();
}

/**
  * @brief  The SHT30 Read Byte
  * @retval Read data
  */
void SHT30_Read_Byte(uint8_t Device_Read_addr, uint16_t reg, uint8_t *buff)
{
    I2C_Start();
    SHT30_I2C_WriteByte(SHT30_WRITE_ADDRESS);
    if (I2C_Wait_Ack()) {
        I2C_Stop();
    }
    SHT30_I2C_WriteByte(reg >> 8);
    if (I2C_Wait_Ack()) {
        I2C_Stop();
    }
    SHT30_I2C_WriteByte(reg);
    if (I2C_Wait_Ack()) {
        I2C_Stop();
    }

    HAL_Delay_us(10);

    I2C_Start();
    SHT30_I2C_WriteByte(Device_Read_addr);
    if (I2C_Wait_Ack()) {
        I2C_Stop();
    }

    buff[0] = SHT30_I2C_ReadByte(1);
    buff[1] = SHT30_I2C_ReadByte(1);
    buff[2] = SHT30_I2C_ReadByte(1);
    buff[3] = SHT30_I2C_ReadByte(1);
    buff[4] = SHT30_I2C_ReadByte(1);
    buff[5] = SHT30_I2C_ReadByte(0);
    I2C_Stop();
}

/**
  * @brief  The SHT30 Read Data
  * @retval none
  */
uint8_t SHT30_Read_Temperature_Humidity(uint16_t reg, uint8_t *buff)
{
    SHT30_Read_Byte(SHT30_READ_ADDRESS, reg, buff);
    if (CheckCrc8(buff) != buff[2] && CheckCrc8(&buff[3]) != buff[5])
    {
        return HAL_ERROR;
    }
    return HAL_OK;
}

/**
  * @brief  The SHT30 Data Conversion
  * @retval none
  */
void SHT30_Data_Conversion(uint8_t* const dat, float* temperature, float* humidity)
{
    uint16_t recv_temperature = 0;
    uint16_t recv_humidity = 0;

    recv_temperature = (uint16_t)(dat[0] << 8 | dat[1]);
    *temperature = -45 + 175 * ((float)recv_temperature / 65535);

    recv_humidity = (uint16_t)(dat[3] << 8 | dat[4]);
    *humidity = 100 * ((float)recv_humidity / 65535);
}
/**
  * @brief  The SHT30 Init
  * @retval none
  */
void SHT30_Init(void)
{
    /* SoftWare Reset */
    SHT30_Write_Commend(SHT30_SOFT_RESET_CMD);
    HAL_Delay_ms(10);
    SHT30_Write_Commend(SHT30_HIGH_10_CMD);
    HAL_Delay_ms(10);
}


