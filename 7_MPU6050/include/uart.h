/**
 * @file uart.h
 * @brief Header file for UART communication module.
 */

#ifndef __UART_H
#define __UART_H

#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart2; /**< UART handle for UART2 peripheral. */

void uart_init();
int _write(int file, char *ptr, int len);
void stdout_init(void);

#endif // __UART_H
