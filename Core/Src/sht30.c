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
void SHT30_Write_Byte(uint8_t Address, uint16_t reg)
{
    I2C_Start();
    SHT30_I2C_WriteByte(Address);
    I2C_Wait_Ack();
    SHT30_I2C_WriteByte((reg >> 8)&0xFF);
    I2C_Wait_Ack();
    SHT30_I2C_WriteByte(reg&0xFF);
    I2C_Wait_Ack();
    I2C_Stop();

}

/**
  * @brief  The SHT30 Read Byte
  * @retval Read data
  */
void SHT30_Read_Byte(uint8_t Address, uint16_t reg, uint8_t *buff)
{
    uint8_t reg_MSB = 0;
    uint8_t reg_LSB = 0;
    reg_MSB = (reg >> 8)&0xFF;
    reg_LSB = reg&0xFF;

    I2C_Start();
    SHT30_I2C_WriteByte(Address);
    I2C_Wait_Ack();
    SHT30_I2C_WriteByte(reg_MSB);
    I2C_Wait_Ack();
    SHT30_I2C_WriteByte(reg_LSB);
    I2C_Wait_Ack();

    I2C_Start();
    SHT30_I2C_WriteByte(Address + 1);
    I2C_Wait_Ack();

    buff[0] = SHT30_I2C_ReadByte(1);
    buff[1] = SHT30_I2C_ReadByte(1);
    buff[2] = SHT30_I2C_ReadByte(1);
    buff[3] = SHT30_I2C_ReadByte(1);
    buff[4] = SHT30_I2C_ReadByte(1);
    buff[5] = SHT30_I2C_ReadByte(0);

    I2C_Stop();
}

