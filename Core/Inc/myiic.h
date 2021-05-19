/*
 * myiic.h
 *
 *  Created on: 2021-05-03
 *      Author: wuliZhao_ch
 */
#ifndef MYIIC_H_
#define MYIIC_H_
#include "main.h"
#include "system.h"
#include "delay.h"

#define BMX160_SDA_PIN      GPIO_PIN_9
#define BMX160_SCL_PIN      GPIO_PIN_8
#define BMX160_GPIO_Port    GPIOB

#define I2C_SDA_SET         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET)
#define I2C_SDA_RESET       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET)
#define I2C_SCL_SET         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET)
#define I2C_SCL_RESET       HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)

//#define I2C_SDA(n)  (n?HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SDA_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SDA_PIN, GPIO_PIN_RESET))
//#define I2C_SCL(n)  (n?HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SCL_PIN, GPIO_PIN_SET):HAL_GPIO_WritePin(BMX160_GPIO_Port, BMX160_SCL_PIN, GPIO_PIN_RESET))
#define READ_SDA        HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9)

#define SDA_IN()        {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}   // Input Mode
#define SDA_OUT()       {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;}   // Output Mode


void MY_I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
uint8_t I2C_Wait_Ack(void);
void I2C_Ack(void);
void I2C_NAck(void);


#endif


