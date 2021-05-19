/*
 * myiic.c
 *
 *  Created on: 2020-05-03
 *      Author: wuliZhao_ch
 *       brief: MYIIC Drive
 */
#include "myiic.h"



/**
  * @brief IIC initializes the function
  * @retval none
  */
void MY_I2C_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(BMX160_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);
}

/**
  * @brief  IIC starts the signal function
  * @retval none
  */
void I2C_Start(void)
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
  * @brief  IIC stop the signal function
  * @retval none
  */
void I2C_Stop(void)
{
    SDA_OUT();
    I2C_SCL_RESET;
    HAL_Delay_us(1);
    I2C_SDA_RESET;
    HAL_Delay_us(4);
    I2C_SCL_SET;
    HAL_Delay_us(1);
    I2C_SDA_SET;
    HAL_Delay_us(4);
}

/**
  * @brief   IIC Wait Ack Signal Function
  * @retval  1->Failed to receive reply
             0->Receive reply successful
  */
uint8_t I2C_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN();
    I2C_SDA_SET;
    HAL_Delay_us(1);
    I2C_SCL_SET;
    HAL_Delay_us(1);
    while (READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250) {
            I2C_Stop();
            return 1;
        }
    }
    I2C_SCL_RESET;
    HAL_Delay_us(2);

    return 0;
}

/**
  * @brief  IIC Ack Signal Function
  * @retval none
  */
void I2C_Ack(void)
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
  * @brief  IIC NAck Signal Function
  * @retval none
  */
void I2C_NAck(void)
{
    I2C_SCL_RESET;
    SDA_OUT();
    I2C_SDA_SET;
    HAL_Delay_us(2);
    I2C_SCL_SET;
    HAL_Delay_us(2);
    I2C_SCL_RESET;
}

