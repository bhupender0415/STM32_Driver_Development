#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "stm32f4xx_hal.h"

void interrupt_init(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif /* INTERRUPT_H */
