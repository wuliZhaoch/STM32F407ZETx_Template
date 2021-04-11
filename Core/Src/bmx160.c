/*
 * bmx160.c
 *
 *  Created on: 2020-04-07
 *      Author: wuliZhao_ch
 *       brief: BMX160 Drive
 */
#include "bmx160.h"


/**
  * @brief BMX160 initializes the function
  * @retval none
  */
void BMX160_I2C_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = BMX160_SDA_PIN | BMX160_SCL_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(BMX160_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SDA_PIN | BMX160_SCL_PIN, GPIO_PIN_SET);
}


/**
  * @brief  The BMX160 starts the signal function
  * @retval none
  */
void BMX160_I2C_Start(void)
{
    SDA_OUT();
    I2C_SDA_SET;
    I2C_SCL_SET;
    HAL_Delay_us(4);
    I2C_SDA_RESET;
    HAL_Delay_us(4);
    I2C_SCL_RESET;
}

/**
  * @brief  The BMX160 stop the signal function
  * @retval none
  */
void BMX160_I2C_Stop(void)
{
    SDA_OUT();
    I2C_SCL_RESET;
    I2C_SDA_RESET;

    HAL_Delay_us(4);

    I2C_SCL_SET;
    I2C_SDA_SET;
    HAL_Delay_us(4);
}

/**
  * @brief  The BMX160 Wait Ack Signal Function
  * @retval  1->Failed to receive reply
             0->Receive reply successful
  */
uint8_t BMX160_I2C_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN();
    I2C_SDA_SET;HAL_Delay_us(1);
    I2C_SCL_SET;HAL_Delay_us(1);
    while (READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250) {
            BMX160_I2C_Stop();
            return 1;
        }
    }
    I2C_SCL_RESET;
    return 0;
}

/**
  * @brief  The BMX160 Ack Signal Function
  * @retval none
  */
void BMX160_I2C_Ack(void)
{
    I2C_SCL_RESET;
    SDA_OUT();
    I2C_SDA_RESET;
    HAL_Delay_us(2);
    I2C_SCL_SET;
    HAL_Delay_us(2);
    I2C_SCL_RESET;
}

/**
  * @brief  The BMX160 NAck Signal Function
  * @retval none
  */
void BMX160_I2C_NAck(void)
{
    I2C_SCL_RESET;
    SDA_OUT();
    I2C_SDA_SET;
    HAL_Delay_us(2);
    I2C_SCL_SET;
    HAL_Delay_us(2);
    I2C_SCL_RESET;
}

/**
  * @brief  The BMX160 I2C Write Byte
  * @retval none
  */
void BMX160_I2C_WriteByte(uint8_t cmd)
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
         HAL_Delay_us(2);
         I2C_SCL_SET;
//         I2C_SDA((cmd&0x80) >> 7);
         cmd <<= 1;
//         HAL_Delay_us(2);
//         I2C_SCL(1);
         HAL_Delay_us(2);
         I2C_SCL_RESET;
         HAL_Delay_us(2);
    }
}

/**
  * @brief  The BMX160 I2C Read Byte
  * @retval Read data
  */
uint8_t BMX160_I2C_ReadByte(uint8_t ack)
{
    uint8_t i = 0;
    uint8_t Receive_Data = 0;
    for (i = 0; i < 8; i++)
    {
        I2C_SCL_RESET;
        HAL_Delay_us(2);

        Receive_Data <<= 1;
        if(READ_SDA) {
            Receive_Data++;
        }
        I2C_SCL_SET;
        HAL_Delay_us(1);
    }
    if (!ack){
        BMX160_I2C_NAck();
    } else {
        BMX160_I2C_Ack();
    }
    return Receive_Data;
}

/**
  * @brief  The BMX160 I2C Write Byte
  * @retval none
  */
void BMX160_Write_Byte(uint8_t Address)
{
    BMX160_I2C_Start();
//    BMX160_I2C_WriteByte();
}

/**
  * @brief  The BMX160 I2C Read Byte
  * @retval Read data
  */
uint8_t BMX160_Read_Byte(uint16_t Address)
{
    uint8_t temp = 0;
    BMX160_I2C_Start();
    BMX160_I2C_WriteByte((0x68<<1)|0);
//    BMX160_I2C_Wait_Ack();
    BMX160_I2C_WriteByte(Address);
//    BMX160_I2C_Wait_Ack();
    BMX160_I2C_Start();
    BMX160_I2C_WriteByte((0x68<<1)|1);
//    BMX160_I2C_Wait_Ack();

    temp = BMX160_I2C_ReadByte(0);
    BMX160_I2C_Stop();
    return temp;
}
