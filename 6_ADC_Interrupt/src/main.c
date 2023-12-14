#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "adc.h"

ADC_HandleTypeDef hadc1;
uint32_t sensorValue;

int main()
{
    HAL_Init();
    uart_init();
    adc_pa0_interrupt_init();

    // start adc in interrupt mode
    HAL_ADC_Start_IT(&hadc1);
    
    while(1)
    {
      printf("ADC value: %ld\n", sensorValue);
      HAL_Delay(1000);
        
    }
}
 
void SysTick_Handler(void)
{
  HAL_IncTick();
}

// callback function for adc interrupt this function is called when adc conversion is complete
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance == ADC1)
  {
    // ADC conversion is complete, read the value here
    sensorValue = HAL_ADC_GetValue(hadc);
    HAL_ADC_Start_IT(&hadc1);
  }
}




