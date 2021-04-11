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
    I2C_SDA(1);
    I2C_SCL(1);
    HAL_Delay_us(4);
    I2C_SDA(0);
    HAL_Delay_us(4);
    I2C_SCL(0);
}

/**
  * @brief  The BMX160 stop the signal function
  * @retval none
  */
void BMX160_I2C_Stop(void)
{
    SDA_OUT();
    I2C_SDA(0);
    I2C_SCL(0);
    HAL_Delay_us(4);
    I2C_SDA(1);
    HAL_Delay_us(4);
    I2C_SCL(1);
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
    I2C_SDA(1);HAL_Delay_us(1);
    I2C_SCL(1);HAL_Delay_us(1);
    while (READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250) {
            BMX160_I2C_Stop();
            return 1;
        }
    }
    I2C_SCL(0);
    return 0;
}

/**
  * @brief  The BMX160 Ack Signal Function
  * @retval none
  */
void BMX160_I2C_Ack(void)
{
    I2C_SCL(0);
    SDA_OUT();
    I2C_SDA(0);
    HAL_Delay_us(2);
    I2C_SCL(1);
    HAL_Delay_us(2);
    I2C_SCL(0);
}

/**
  * @brief  The BMX160 NAck Signal Function
  * @retval none
  */
void BMX160_I2C_NAck(void)
{
    I2C_SCL(0);
    SDA_OUT();
    I2C_SDA(1);
    HAL_Delay_us(2);
    I2C_SCL(1);
    HAL_Delay_us(2);
    I2C_SCL(0);
}
