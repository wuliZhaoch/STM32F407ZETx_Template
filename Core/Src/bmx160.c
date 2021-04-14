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
         cmd <<= 1;
         HAL_Delay_us(2);
         I2C_SCL_SET;

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
        I2C_SCL_SET;
        Receive_Data <<= 1;
        if(READ_SDA) {
            Receive_Data++;
        }
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
  * @brief  The BMX160 Write Byte
  * @retval none
  */
uint8_t BMX160_Write_Byte(uint8_t reg, uint8_t data)
{
    BMX160_I2C_Start();
    BMX160_I2C_WriteByte(BMX160_WRITE_ADDRESS);
    if (BMX160_I2C_Wait_Ack()) {
        BMX160_I2C_Stop();
        return 1;
    }
    BMX160_I2C_WriteByte(reg);
    BMX160_I2C_Wait_Ack();
    BMX160_I2C_WriteByte(data);
    if (BMX160_I2C_Wait_Ack()) {
        BMX160_I2C_Stop();
        return 1;
    }
    BMX160_I2C_Stop();
    return 0;
}

/**
  * @brief  The BMX160 Read Byte
  * @retval Read data
  */
uint8_t BMX160_Read_Byte(uint8_t reg)
{
    uint8_t temp = 0;
    BMX160_I2C_Start();
    BMX160_I2C_WriteByte(BMX160_WRITE_ADDRESS);
    BMX160_I2C_Wait_Ack();
    BMX160_I2C_WriteByte(reg);
    BMX160_I2C_Wait_Ack();

    BMX160_I2C_Start();
    BMX160_I2C_WriteByte(BMX160_READ_ADDRESS);
    BMX160_I2C_Wait_Ack();

    temp = BMX160_I2C_ReadByte(0);
    BMX160_I2C_Stop();
    return temp;
}

/**
  * @brief  The BMX160 Write MultiByte
  * @retval 0 -> Succees
  *         1 -> Fail
  */
uint8_t BMX160_Write_MultiByte(uint8_t DeviceAddr, uint8_t reg, uint8 *rev_buffer, uint16_t Size)
{
    uint8_t i = 0;
    BMX160_I2C_Start();
    BMX160_I2C_WriteByte((DeviceAddr<<1) | 0);
    if (BMX160_I2C_Wait_Ack())
    {
        BMX160_I2C_Stop();
        return 1;
    }
    BMX160_I2C_WriteByte(reg);
    BMX160_I2C_Wait_Ack();
    for (i = 0; i < Size; i++)
    {
        BMX160_I2C_WriteByte(rev_buffer[i]);
        if (BMX160_I2C_Wait_Ack())
        {
            BMX160_I2C_Stop();
            return 1;
        }
    }
    BMX160_I2C_Stop();
    return 0;
}

/**
  * @brief  The BMX160 Read MultiByte
  * @retval 0 -> Succees
  *         1 -> Fail
  */
uint8_t BMX160_Read_MultiByte(uint8_t DeviceAddr, uint8_t reg, uint8 *rev_buffer, uint16_t Size)
{
    BMX160_I2C_Start();
    BMX160_I2C_WriteByte((DeviceAddr<<1) | 0);
    if (BMX160_I2C_Wait_Ack())
    {
        BMX160_I2C_Stop();
        return 1;
    }
    BMX160_I2C_WriteByte(reg);
    BMX160_I2C_Wait_Ack();

    BMX160_I2C_Start();
    BMX160_I2C_WriteByte((DeviceAddr<<1) | 1);
    BMX160_I2C_Wait_Ack();
    while (Size)
    {
        if (Size == 1) {
            *rev_buffer = BMX160_I2C_ReadByte(0);
        } else {
            *rev_buffer = BMX160_I2C_ReadByte(1);
        }
        Size--;
        rev_buffer++;
    }
    BMX160_I2C_Stop();
    return 0;

}

/**
  * @brief  The BMX160 Configuration is Initialized
  * @retval None
  */
void BMX160_Config_Init(void)
{
    uint8_t pmu_status = 0;
    uint8_t temp = 0;
    uint8_t BMX160_Chip_ID = 0;

    BMX160_Write_Byte(BMX160_CMD, BMX160_SOFTRESET_CMD);    //  Accelerometer Normal Mode
    HAL_Delay(500);

    /* Accelerometer Config */
    temp = 0x26;    BMX160_Write_Byte(BMX160_ACC_CONF, temp);
    temp = 0x0C;    BMX160_Write_Byte(BMX160_ACC_RANGE, temp);

    /* Gyroscope Config */
    temp = 0x26;    BMX160_Write_Byte(BMX160_GYR_CONF, temp);
    temp = 0x03;    BMX160_Write_Byte(BMX160_GYR_RANGE, temp);

    BMX160_Write_Byte(BMX160_CMD, BMX160_ACCEL_NORMAL_MODE);    //  Accelerometer Normal Mode
    HAL_Delay(500);

    BMX160_Write_Byte(BMX160_CMD, BMX160_GYRO_NORMAL_MODE);     //  Gyroscope Normal Mode
    HAL_Delay(500);

    BMX160_Write_Byte(BMX160_CMD, BMX160_MAGN_NORMAL_MODE);     //  Magnetometer Normal Mode
    HAL_Delay(500);

    pmu_status = BMX160_Read_Byte(BMX160_PMU_STATUS);   // Read PMU Status
    if (pmu_status == 0x15)
    {
        printf("BMX160 Sensor In Normal Mode!\r\n");
    }

    BMX160_Chip_ID = BMX160_Read_Byte(BMX160_CHIPID);
    if (BMX160_Chip_ID == BMX160_CHIPID_RET_VALUE) {
        printf("BMX160 ChipID is: 0x%x\r\n", BMX160_Chip_ID);
    } else {
        printf("BMX160 ChipID Read Fail\r\n");
    }

}

/**
  * @brief  Get BMX160 temperature
  * @retval None
  */
uint16_t BMX160_GetTemperature(void)
{
    uint8_t Temperature_buffer[2] = {0};
    uint16_t ret;
    Temperature_buffer[0] = BMX160_Read_Byte(BMX160_TEMPERATURE0);
    Temperature_buffer[1] = BMX160_Read_Byte(BMX160_TEMPERATURE1);
    ret = (Temperature_buffer[1] << 8) | Temperature_buffer[0];
    printf("Temperature is: 0x%x --> %.3f\r\n", ret, ((float)ret / 512.0) + 23.0);

    return ret;
}


