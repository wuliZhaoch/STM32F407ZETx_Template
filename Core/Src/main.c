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

#define PERIODOC_SAMPLING_NUMBER    350
#define SAMPLE_NUMBER               (PERIODOC_SAMPLING_NUMBER*4)

uint32_t ADC_DMABuffer[SAMPLE_NUMBER] = {0};
uint8_t ADC_Conv_Flag;

uint16_t channel3_buffer[PERIODOC_SAMPLING_NUMBER] = {0};
uint16_t channel6_buffer[PERIODOC_SAMPLING_NUMBER] = {0};
uint16_t channel12_buffer[PERIODOC_SAMPLING_NUMBER] = {0};
uint16_t channel13_buffer[PERIODOC_SAMPLING_NUMBER] = {0};

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

    if (hadc == &hadc1)
    {
        HAL_ADC_Stop_DMA(&hadc1);
        for (uint16_t i = 0; i < PERIODOC_SAMPLING_NUMBER; i++)
        {
            channel3_buffer[i] = ADC_DMABuffer[i*4];
            channel6_buffer[i] = ADC_DMABuffer[i*4+1];
            channel12_buffer[i] = ADC_DMABuffer[i*4+2];
            channel12_buffer[i] = ADC_DMABuffer[i*4+3];
        }
//        for (uint16_t i = 0; i < PERIODOC_SAMPLING_NUMBER; i++)
//        {
//            printf("%d\r\n", channel3_buffer[i]);
//        }
//        printf("\r\n");
        for (uint16_t i = 0; i < PERIODOC_SAMPLING_NUMBER; i++)
        {
            printf("%d\r\n", channel6_buffer[i]);
        }
        printf("\r\n");
    }
}

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim2)
    {
        HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_DMABuffer, SAMPLE_NUMBER);
        HAL_GPIO_TogglePin(SYSTEM_RUN_LED_GPIO_Port, SYSTEM_RUN_LED_Pin);
    }
}

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
    MX_ADC1_Init();
    MX_TIM2_Init();

    System_GetChipID();     // Get Chip ID

    BMX160_Config_Init();
    BMX160_GetTemperature();

    SHT30_Init();


    while (1)
    {

        /* The sensor measures 10 times per second,Turn on Periodic Mode */
//        SHT30_Read_Temperature_Humidity(SHT30_PERIODIC_MODE_READ, SHT30_BUFF);
//        SHT30_Data_Conversion(SHT30_BUFF, &sht30_temperature, &sht30_humidity);
//        printf("SHT30 Temperature is:  %f \r\n", sht30_temperature);
//        printf("SHT30 Humidity is:  %f \r\n", sht30_humidity);
//        BMX160_GetAccelerometer(Acc_Buffer);
//        BMX160_GetGyroscope(Gyr_Buffer);
//        BMX160_GetMagnetometer(Mag_Buffer);
//        printf("System main_loop is: %ld\r\n", main_loop);
//        main_loop++;
//        HAL_GPIO_TogglePin(SYSTEM_RUN_LED_GPIO_Port, SYSTEM_RUN_LED_Pin);
//        HAL_Delay_ms(1000);
    }

}

