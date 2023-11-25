#include "stm32f4xx_hal.h"

#define BTN_PIN                    GPIO_PIN_13
#define BTN_GPIO_PORT              GPIOC
#define LED_PIN                    GPIO_PIN_5
#define LED_GPIO_PORT              GPIOA


void gpio_pc13_interrupt_init(void);

int main()
{
    HAL_Init();
    gpio_pc13_interrupt_init();
    
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
void gpio_pc13_interrupt_init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // enable clock connected to gpio port A and C
    __HAL_RCC_GPIOC_CLK_ENABLE();               
    __HAL_RCC_GPIOA_CLK_ENABLE();               
    
    // configuring BTN as interrupt
    GPIO_InitStruct.Pin = BTN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (BTN_GPIO_PORT, &GPIO_InitStruct);


    // configuring output LED
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init (LED_GPIO_PORT, &GPIO_InitStruct);  

    // configuring EXTI
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}


/**
 * @brief Callback function for GPIO EXTI interrupt.
 * @param GPIO_Pin: The pin number that triggered the interrupt.
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
}


/**
    * @brief  EXTI line 15 to 10 interrupt handler.
    *         This function is called when an interrupt event occurs on the EXTI line 15 to 10.
    * @param  None
    * @retval None
    */
void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(BTN_PIN);
}

