#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"


int main()
{
  HAL_Init();
  uart_init();
 

  while(1)
  {


  }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
} 

