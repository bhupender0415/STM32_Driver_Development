#include "stm32f4xx_hal.h"

 
#define LED_PIN                    GPIO_PIN_5
#define LED_GPIO_PORT              GPIOA
#define BTN_PIN                    GPIO_PIN_13
#define BTN_GPIO_PORT              GPIOC


/*
    LED -> output -> PA5 -> PORT A -> AHB1
    BTN -> input -> PC13 -> PORT C -> AHB1
*/

void pc13_btn_init(void);
void pa5_led_init(void);

uint8_t btnState;
int main(){

    HAL_Init();
    pa5_led_init();
    pc13_btn_init();

    while(1){
     btnState = HAL_GPIO_ReadPin (BTN_GPIO_PORT, BTN_PIN);
     HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, btnState);
    }
}

void pc13_btn_init(void){
    __HAL_RCC_GPIOC_CLK_ENABLE();   // enabled clock
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = BTN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (BTN_GPIO_PORT, &GPIO_InitStruct);
}

void pa5_led_init(void){
    __HAL_RCC_GPIOA_CLK_ENABLE();   // enabled clock
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init (LED_GPIO_PORT, &GPIO_InitStruct);
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}