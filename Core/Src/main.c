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

//#define PERIODOC_SAMPLING_NUMBER    350
#define PERIODOC_SAMPLING_NUMBER    200
#define SAMPLE_NUMBER               (PERIODOC_SAMPLING_NUMBER*4)

uint32_t ADC_DMABuffer[4] = {0};
uint8_t ADC_Conv_Flag;

uint16_t Sample_num = 0;
uint16_t maxPos;
uint16_t minPos;
uint16_t channel6_buffer_max;
uint16_t channel6_buffer_min;

//uint16_t channel3_buffer[PERIODOC_SAMPLING_NUMBER] = {0};
//uint16_t channel6_buffer[PERIODOC_SAMPLING_NUMBER] = {0};
//uint16_t channel12_buffer[PERIODOC_SAMPLING_NUMBER] = {0};
//uint16_t channel13_buffer[PERIODOC_SAMPLING_NUMBER] = {0};

uint16_t channel3_buffer[PERIODOC_SAMPLING_NUMBER] = {0};
uint16_t channel6_buffer[PERIODOC_SAMPLING_NUMBER] = {0};
uint16_t channel12_buffer[PERIODOC_SAMPLING_NUMBER] = {0};
uint16_t channel13_buffer[PERIODOC_SAMPLING_NUMBER] = {0};

/* Find MIN Value */
uint16_t FindMax_Value(uint16_t a[], uint16_t n, uint16_t *pMaxPos)
{

    int i, max;
    max = a[0];
    *pMaxPos = 0;

    for (i = 1; i < n; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
            *pMaxPos = i;
        }
    }
    return max;
}

/* Find MAX Value */
uint16_t FindMin_Value(uint16_t a[], uint16_t n, uint16_t *pMaxPos)
{

    int i, max;
    max = a[0];
    *pMaxPos = 0;

    for (i = 1; i < n; i++)
    {
        if (a[i] < max)
        {
            max = a[i];
            *pMaxPos = i;
        }
    }
    return max;
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

    if (hadc == &hadc1)
    {
        HAL_ADC_Stop_DMA(&hadc1);
        channel6_buffer[Sample_num] = ADC_DMABuffer[1];
        Sample_num++;
        if (Sample_num == PERIODOC_SAMPLING_NUMBER)
        {
           HAL_TIM_Base_Stop_IT(&htim2);
           Sample_num = 0;
           ADC_Conv_Flag = 1;
           for (uint16_t i = 0; i < PERIODOC_SAMPLING_NUMBER; i++)
           {
               printf("%d\r\n", channel6_buffer[i]);
           }
           printf("\r\n");
           channel6_buffer_max = FindMax_Value(channel6_buffer, PERIODOC_SAMPLING_NUMBER, &maxPos);
           channel6_buffer_min = FindMin_Value(channel6_buffer, PERIODOC_SAMPLING_NUMBER, &minPos);
           printf("channel6_buffer max value is %d\r\n", channel6_buffer_max);
           printf("channel6_buffer min value is %d\r\n", channel6_buffer_min);
           printf("channel6_buffer max value Pos is %d\r\n", maxPos);
           printf("channel6_buffer min value Pos is %d\r\n", minPos);
           printf("\r\n");
        }
//        HAL_ADC_Stop_DMA(&hadc1);
//        for (uint16_t i = 0; i < PERIODOC_SAMPLING_NUMBER; i++)
//        {
//            channel3_buffer[i] = ADC_DMABuffer[i*4];
//            channel6_buffer[i] = ADC_DMABuffer[i*4+1];
//            channel12_buffer[i] = ADC_DMABuffer[i*4+2];
//            channel13_buffer[i] = ADC_DMABuffer[i*4+3];
//        }
//        for (uint16_t i = 0; i < PERIODOC_SAMPLING_NUMBER; i++)
//        {
//            printf("%d\r\n", channel3_buffer[i]);
//        }
//        printf("\r\n");
//        for (uint16_t i = 0; i < PERIODOC_SAMPLING_NUMBER; i++)
//        {
//            printf("%d\r\n", channel6_buffer[i]);
//        }
//        printf("\r\n");
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
        HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_DMABuffer, 4);
//        HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_DMABuffer, SAMPLE_NUMBER);
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

        if (ADC_Conv_Flag == 1)
        {
            ADC_Conv_Flag = 0;
            if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK)
            {
                Error_Handler();
            }
        }
        HAL_Delay(1000);
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

