#include "stm32f4xx_hal.h"
#include <stdio.h>

/*
PA2 -> TX
PA3 -> RX

*/

UART_HandleTypeDef huart2;
void uart_init(void);

// Retargetting printf with uart

// not working
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 100);
    return ch;
}


int main()
{
    HAL_Init();
    uart_init();
    while(1)
    {
        printf("This is Printed using printf\r\n"); //not working
        HAL_Delay(1000);
    }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

void uart_init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // configure gpio module as AF

    __HAL_RCC_GPIOA_CLK_ENABLE();   // enable usart pin clock connected to gpio port A
    __HAL_RCC_USART2_CLK_ENABLE();  // enable clock for usart2
    
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);   

    // configure usart module
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);

}