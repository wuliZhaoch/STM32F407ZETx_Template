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

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();

    GET_ChipID(&SystemChipID);
    printf("System chipID is: %lx%lx%lx\r\n", SystemChipID.Chip_ID_H,
            SystemChipID.Chip_ID_M, SystemChipID.Chip_ID_L);

    while (1) {
        printf("System main_loop is: %ld\r\n", main_loop);
        main_loop++;
        HAL_Delay(1000);
    }

}

