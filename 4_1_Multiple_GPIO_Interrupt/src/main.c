#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "uart.h"


void interrupt_init(void);

int main()
{
    HAL_Init();
    uart_init();
    interrupt_init();
    printf("Program started\n");
    
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



/**
 * @brief Initializes the GPIO interrupt for PC13 button and configures the output LED.
 * 
 * This function enables the clock for GPIO ports A and C, configures the button pin as an interrupt
 * with rising edge trigger, and configures the LED pin as an output. It also sets the priority and enables
 * the EXTI interrupt for PC13 button.
 */
void interrupt_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // enable clock connected to gpio port A and c
    __HAL_RCC_GPIOC_CLK_ENABLE();               
    __HAL_RCC_GPIOA_CLK_ENABLE();               
    
    // configuring PA0 as interrupt
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);

    // configuring PA1 as interrupt
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);

    // congifuring PC13 as interrupt
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (GPIOC, &GPIO_InitStruct);

    // configuring EXTI for PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn , 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn );

    // configuring EXTI for PA1
    HAL_NVIC_SetPriority(EXTI1_IRQn , 0, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn );
}


/**
 * @brief Callback function for GPIO EXTI interrupt.
 * @param GPIO_Pin: The pin number that triggered the interrupt.
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_0)
    {
        printf("Interrupt happen through PA0\n");
    }
    else if(GPIO_Pin == GPIO_PIN_1)
    {
        printf("Interrupt happen through PA1\n");
    }
}


// IRQ handler for EXTI line 0
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

// IRQ handler for EXTI line 1
void EXTI1_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

