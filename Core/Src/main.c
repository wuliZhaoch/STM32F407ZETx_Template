#include "includes.h"

uint32_t main_loop = 0;

ChipIDTypeDef SystemChipID;
uint8_t BMX160_Chip_ID = 0;

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


    GET_ChipID(&SystemChipID);
    printf("System chipID is: %lx%lx%lx\r\n", SystemChipID.Chip_ID_H,SystemChipID.Chip_ID_M, SystemChipID.Chip_ID_L);
    HAL_Delay(1000);

    BMX160_Chip_ID = BMX160_Read_Byte(BMX160_CHIPID);
    if (BMX160_Chip_ID == BMX160_CHIPID_RET_VALUE)
    {
        printf("BMX160 ChipID is: 0x%x\r\n", BMX160_Chip_ID);
    } else {
        printf("BMX160 ChipID Read Fail\r\n");
    }


    while (1) {

        printf("System main_loop is: %ld\r\n", main_loop);
        main_loop++;
        HAL_GPIO_TogglePin(SYSTEM_RUN_LED_GPIO_Port, SYSTEM_RUN_LED_Pin);
        HAL_Delay_us(1000000);
    }

}

