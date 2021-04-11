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
// YANSHI 4US
    I2C_SDA(0);
// YANSHI 4US
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
// YANSHI 4US
    I2C_SDA(1);
// YANSHI 4US
    I2C_SCL(1);
}
