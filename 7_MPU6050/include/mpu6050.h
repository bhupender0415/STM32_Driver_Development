/*
*
* STM32 MPU6050 I2C driver
* Author: Bhupender Singh
*
*/

#ifndef MPU6050_H
#define MPU6050_H

/* STM32 essential libraries includes  */
#include "stm32f4xx_hal.h"

I2C_HandleTypeDef hi2c1;

/* Register addresses */
#define MPU6050_ADDR              0xD0
#define SMPLRT_DIV_REG            0x19
#define GYRO_CONFIG_REG           0x1B
#define ACCEL_CONFIG_REG          0x1C
#define ACCEL_XOUT_H_REG          0x3B
#define TEMP_OUT_H_REG            0x41
#define GYRO_XOUT_H_REG           0x43
#define PWR_MGMT_1_REG            0x6B
#define WHO_AM_I_REG              0x75


/* device init struct  */
typedef struct {
    I2C_HandleTypeDef* i2cHandle;
    float accData[3]; // accelerometer is in meters per second
    float gyroData[3]; // gyro values in deg
    float temperature;
} MPU6050_t;

// Initialization function
void MPU6050_Init (void);

#endif // end MPU6050_H
