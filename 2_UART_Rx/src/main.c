#include<string.h>
#include "stm32f4xx_hal.h"


#define LED_PIN                    GPIO_PIN_5
#define LED_GPIO_PORT              GPIOA

/*
PA2 -> TX
PA3 -> RX

*/

UART_HandleTypeDef huart2;
void uart_init(void);
uint8_t ToUpper(uint8_t data);

char *user_data = "The application is running\r\n";

int main(void)
{
	HAL_Init();
	uart_init();

	uint16_t len_of_data = strlen(user_data);
	HAL_UART_Transmit(&huart2,(uint8_t*)user_data,len_of_data,HAL_MAX_DELAY);

	uint8_t rcvd_data;
	uint8_t data_buffer[100];
	uint32_t count=0;

	while(1)
	{
		HAL_UART_Receive(&huart2,&rcvd_data,1,HAL_MAX_DELAY);
		if(rcvd_data == '\r')
		{
			break;
		}
		else
		{
			data_buffer[count++]= ToUpper(rcvd_data);
		}
	}

	data_buffer[count++]= '\r\n';
	HAL_UART_Transmit(&huart2,data_buffer,count,HAL_MAX_DELAY);

	while(1);


	return 0;
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
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);

}

uint8_t ToUpper(uint8_t data)
{
	if( data >= 'a' && data <= 'z')
	{
		data = data - ( 'a'- 'A');
	}

	return data;

}






