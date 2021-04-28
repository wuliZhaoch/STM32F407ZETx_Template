/*
 * sht30.c
 *
 *  Created on: 2020-04-28
 *      Author: wuliZhao_ch
 *       brief: SHT30 Drive
 */
#include "sht30.h"




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
uint8_t SHT30_WriteByte(uint16_t reg)
{
    I2C_Start();

    SHT30_I2C_WriteByte(SHT30_WRITE_ADDRESS);
    if (I2C_Wait_Ack()) {
        I2C_Stop();
        return 1;
    }
    SHT30_I2C_WriteByte((reg >> 8) & 0xFF);
    I2C_Wait_Ack();
    SHT30_I2C_WriteByte(reg & 0XFF);
    if (I2C_Wait_Ack()) {
        I2C_Stop();
        return 1;
    }
    I2C_Stop();
    return 0;
}

