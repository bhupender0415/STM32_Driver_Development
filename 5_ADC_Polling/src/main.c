#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "adc.h"

ADC_HandleTypeDef hadc1;
u_int32_t sensorValue;

int main()
{
    HAL_Init();
    uart_init();
    adc_pa0_single_conv_init();
    
    while(1)
    {
        // 1. start ADC
        HAL_ADC_Start(&hadc1);

        // 2. Poll for conversion
        HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

        // 3. get convrsion
        sensorValue = pa0_adc_read();

        // 4. print to serial monitor
        printf("ADC value: %lu\n", sensorValue);
        HAL_Delay(500);
        
    }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}



