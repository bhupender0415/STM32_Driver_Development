#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "MPU6050.h"


int main()
{
    HAL_Init();
    I2C1_Init();    // initialize the I2C1
    MPU6050_Init(); // initialize the MPU6050

    while(1)
    {
        
    }
}

void SysTick_Handler(void)
{
  HAL_IncTick();
} 