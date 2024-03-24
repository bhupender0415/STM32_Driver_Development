#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "it.h"


int main()
{
    HAL_Init();
    uart_init();
    interrupt_init();
    printf("Program Started\n");
    
    while(1)
    {
        
    }
}


/**
    * @brief  SysTick Handler.
    *         This function is called when the SysTick interrupt occurs.
    * @param  None
    * @retval None
    */
void SysTick_Handler(void)
{
    HAL_IncTick();
}