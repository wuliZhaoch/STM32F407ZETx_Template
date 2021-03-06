#include "includes.h"

uint32_t main_loop = 0;

ChipIDTypeDef SystemChipID;
uint8_t bmx160_chipid = 0;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

    HAL_Init();

    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
    MX_I2C1_Init();

    GET_ChipID(&SystemChipID);
    printf("System chipID is: %lx%lx%lx\r\n", SystemChipID.Chip_ID_H,
            SystemChipID.Chip_ID_M, SystemChipID.Chip_ID_L);

    HAL_Delay(100);
    BMX160_ByteRead(BMX160_CHIPID, &bmx160_chipid, BMX160_TIMEOUT);
    printf("BMX160 ChipID is: 0x%x\r\n", bmx160_chipid);

    while (1) {

        printf("System main_loop is: %ld\r\n", main_loop);
        main_loop++;
        HAL_GPIO_TogglePin(SYSTEM_RUN_LED_GPIO_Port, SYSTEM_RUN_LED_Pin);
        HAL_Delay(1000);
    }

}

