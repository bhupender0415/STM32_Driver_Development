#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "gpio.h"
#include "timer.h"

TIM_HandleTypeDef htim2;

int main()
{
  HAL_Init();
  uart_init();
  PA5_init();
  TIM2_Init();

  HAL_TIM_Base_Start_IT(&htim2);

  while(1)
  {


  }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
} 


/* TIM2 interrupt handler */
void TIM2_IRQHandler(void) 
{
  HAL_TIM_IRQHandler(&htim2);
}

/* Callback function for TIM2 interrupt */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) 
{
  if (htim->Instance == TIM2) {
    HAL_GPIO_TogglePin(GPIOA,  GPIO_PIN_5);
  }
}

