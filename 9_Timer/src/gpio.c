#include "gpio.h"

void PA5_init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();   // enabled clock
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);
}
