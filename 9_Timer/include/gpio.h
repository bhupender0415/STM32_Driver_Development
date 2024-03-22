#ifndef GPIO_H
#define GPIO_H
#include "stm32f4xx_hal.h"

void PA5_init(void);

#endif // GPIO_H
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
#include "gpio.h"

void PA5_init(void) {
  // Enable GPIOA clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // Configure PA5 as output
  GPIOA->MODER |= GPIO_MODER_MODE5_0;

  // Enable Timer 2 clock
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

  // Configure Timer 2
  TIM2->PSC = 0; // Set prescaler to 1
  TIM2->ARR = 1000; // Set auto-reload value
  TIM2->CR1 |= TIM_CR1_ARPE; // Enable auto-reload preload
  TIM2->CR1 |= TIM_CR1_CEN; // Enable Timer 2

  while (1) {
    if (TIM2->CNT >= 500) {
      GPIOA->ODR ^= GPIO_ODR_OD5; // Toggle PA5
      TIM2->CNT = 0; // Reset Timer 2 counter
    }
  }
}
