#include "includes.h"

uint32_t main_loop = 0;

float sht30_temperature = 0;
float sht30_humidity = 0;

uint8_t Acc_Buffer[ACC_DATA_LEN] = {0};
uint8_t Gyr_Buffer[GRY_DATA_LEN] = {0};
uint8_t Mag_Buffer[MAG_DATA_LEN] = {0};

uint8_t SHT30_BUFF[6] = {0};
uint8_t SHT30_Status_buff[3] = {0};
uint16_t SHT30_Status = 0;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    HAL_Init();

    SystemClock_Config();   // System Clock Config

    HAL_Delay_init();       // System Delay Init

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
//    MX_I2C1_Init();
    MY_I2C_Init();

    System_GetChipID();     // Get Chip ID

    BMX160_Config_Init();
    BMX160_GetTemperature();

    SHT30_Init();





    while (1)
    {
        /* The sensor measures 10 times per second,Turn on Periodic Mode */
        SHT30_Read_Temperature_Humidity(SHT30_PERIODIC_MODE_READ, SHT30_BUFF);
        SHT30_Data_Conversion(SHT30_BUFF, &sht30_temperature, &sht30_humidity);
        printf("SHT30 Temperature is:  %f \r\n", sht30_temperature);
        printf("SHT30 Humidity is:  %f \r\n", sht30_humidity);
//        BMX160_GetAccelerometer(Acc_Buffer);
//        BMX160_GetGyroscope(Gyr_Buffer);
//        BMX160_GetMagnetometer(Mag_Buffer);
//        printf("System main_loop is: %ld\r\n", main_loop);
//        main_loop++;
        HAL_GPIO_TogglePin(SYSTEM_RUN_LED_GPIO_Port, SYSTEM_RUN_LED_Pin);
        HAL_Delay_ms(1000);
    }

}

