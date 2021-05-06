#include "includes.h"

uint32_t main_loop = 0;



uint8_t Acc_Buffer[ACC_DATA_LEN] = {0};
uint8_t Gyr_Buffer[GRY_DATA_LEN] = {0};
uint8_t Mag_Buffer[MAG_DATA_LEN] = {0};

uint8_t SHT30_BUFF[6] = {0};

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



    SHT30_Write_Byte(SHT30_SOFT_RESET_CMD);
    while (1)
    {
        SHT30_Write_Byte(SHT30_HIGH_2_CMD);
        HAL_Delay_ms(20);
        SHT30_Read_Byte(SHT30_PERIODIC_MODE_READ, SHT30_BUFF);
        for (uint8_t i = 0;i < 6; i++)
        {
            printf("SHT30_BUFF[%d] is: 0x%x\r\n", i, SHT30_BUFF[i]);
        }
        printf("\r\n");
//        SHT30_Write_Byte(SHT30_HIGH_2_CMD);
//        SHT30_Write_Byte(SHT30_HIGH_2_CMD);
//        BMX160_GetAccelerometer(Acc_Buffer);
//        BMX160_GetGyroscope(Gyr_Buffer);
//        BMX160_GetMagnetometer(Mag_Buffer);
//        printf("System main_loop is: %ld\r\n", main_loop);
//        main_loop++;
        HAL_GPIO_TogglePin(SYSTEM_RUN_LED_GPIO_Port, SYSTEM_RUN_LED_Pin);
        HAL_Delay_ms(1000);
    }

}

