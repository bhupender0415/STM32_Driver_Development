#include "uart.h"
#include <stdio.h>

/**
 * @brief Redirects the standard output stream to UART.
 * 
 * This function is called by the standard library's printf function to redirect the output to UART.
 * 
 * @param file The file descriptor (not used).
 * @param ptr Pointer to the data to be transmitted.
 * @param len Length of the data to be transmitted.
 * @return int The number of bytes transmitted.
 */
int _write(int file, char *ptr, int len)
{
    // Redirect stdout to UART
    HAL_UART_Transmit(&huart2, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}

/**
 * @brief Initializes the standard output stream.
 * 
 * This function initializes the standard output stream (stdout) to be unbuffered.
 * It is called before using printf to ensure that the output is immediately transmitted via UART.
 */
void stdout_init(void)
{
    // Initialize standard output stream
    setvbuf(stdout, NULL, _IONBF, 0);
}

/**
 * @brief Initializes the UART peripheral.
 * 
 * This function initializes the UART peripheral (USART2) on GPIO pins PA2 (TX) and PA3 (RX).
 * It configures the GPIO pins as alternate function mode and sets the UART parameters.
 */
void uart_init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    

    __HAL_RCC_GPIOA_CLK_ENABLE();   // enable usart pin clock connected to gpio port A
    __HAL_RCC_USART2_CLK_ENABLE();  // enable clock for usart2
    
    // configure gpio module as AF
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);   

    // configure usart module
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);
}