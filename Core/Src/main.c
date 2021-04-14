#include "includes.h"

uint32_t main_loop = 0;





/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    HAL_Init();

    SystemClock_Config();   // System Clock Config

    HAL_Delay_init();       // System Delay Init

    System_GetChipID();     // Get Chip ID


    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
//    MX_I2C1_Init();
    BMX160_I2C_Init();

    BMX160_Config_Init();
    BMX160_GetTemperature();




    while (1)
    {

//        printf("System main_loop is: %ld\r\n", main_loop);
//        main_loop++;
        HAL_GPIO_TogglePin(SYSTEM_RUN_LED_GPIO_Port, SYSTEM_RUN_LED_Pin);
        HAL_Delay_us(2000000);
    }

}

