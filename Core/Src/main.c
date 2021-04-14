#include "includes.h"

uint32_t main_loop = 0;

ChipIDTypeDef SystemChipID;



/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    HAL_Init();

    SystemClock_Config();

    HAL_Delay_init();


    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
//    MX_I2C1_Init();
    BMX160_I2C_Init();
    BMX160_Config_Init();

    BMX160_GetTemperature();

    GET_ChipID(&SystemChipID);
    printf("System ChipID is: %lx%lx%lx\r\n", SystemChipID.Chip_ID_H,SystemChipID.Chip_ID_M, SystemChipID.Chip_ID_L);
    HAL_Delay(1000);




    while (1)
    {
//        BMX160_Read_MultiByte(BMX160_DEVICE_ADDR, BMX160_TEMPERATURE0, Temperature_buffer, 2);
//        printf("Temp[0] = 0x%x,Temp[1] = 0x%x,      Temp[1]+Temp[0] = 0x%x\r\n",
//                Temperature_buffer[0], Temperature_buffer[1],
//                (Temperature_buffer[1] << 8) | Temperature_buffer[0]);
//        printf("Temperature is: %.3f\r\n", 23.00+(float)((Temperature_buffer[1] << 8) | Temperature_buffer[0])/512);

//        printf("System main_loop is: %ld\r\n", main_loop);
//        main_loop++;
        HAL_GPIO_TogglePin(SYSTEM_RUN_LED_GPIO_Port, SYSTEM_RUN_LED_Pin);
        HAL_Delay_us(2000000);
    }

}

