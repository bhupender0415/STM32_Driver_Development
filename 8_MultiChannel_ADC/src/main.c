#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "adc.h"


ADC_HandleTypeDef hadc1;
uint32_t adc_value[6] = {0};
uint16_t ind = 0;

int main()
{
  HAL_Init();
  uart_init();
  ADC_init();
  HAL_ADC_Start_IT(&hadc1);

  while(1)
  {
    printf("ADC value: %ld %ld %ld %ld %ld %ld\n", adc_value[0], adc_value[1], adc_value[2], adc_value[3], adc_value[4], adc_value[5]);
    HAL_Delay(2000);


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
    adc_value[ind] = HAL_ADC_GetValue(hadc);
    ind++;
    if(ind == 6)
    {
      ind = 0;
    }
    HAL_ADC_Start_IT(&hadc1);   // start ADC interrupt
  }
}