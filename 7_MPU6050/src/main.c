#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "MPU6050.h"
#include "uart.h"
#include <stdio.h>

float Ax, Ay, Az, temperature;
MPU6050_t pData;

int main()
{
    HAL_Init();
    uart_init();
    I2C1_Init();    // initialize the I2C1
    MPU6050_Init(); // initialize the MPU6050

    while(1)
    {
      MPU6050_Read_Acc(&pData);
      MPU6050_Read_Temp(&pData);
      Ax = pData.accData[0];
      Ay = pData.accData[1];
      Az = pData.accData[2];
      temperature = pData.temp;
      printf("Acc X: %d, Acc Y: %d, Acc Z: %d, Temperature %d\n", (u_int16_t)Ax, (u_int16_t)Ay, (u_int16_t)Az, (u_int16_t)temperature);    //*float values are not priting
      HAL_Delay(100);   
    }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
} 