#include "MPU6050.h"
#include <stdio.h>

void MPU6050_Init(void)
{
	uint8_t Data;

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG,1, &Data, 1, 1000); // check device ID WHO_AM_I

	if (Data == 0x68)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
		Data = 0x00;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
		Data = 0x00;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);
        printf("MPU6050 is online...\n");
	}
    else
    {
        printf("Could not connect to MPU6050...\n");
    }
}

void MPU6050_Read_Acc(MPU6050_t* acc)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H register
	HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

    // raw acceleration data
	u_int16_t accX_Raw = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	u_int16_t accY_Raw = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	u_int16_t accZ_Raw = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

    // convert the raw data to actual acceleration
	acc->accData[0] = accX_Raw/2048.0;
	acc->accData[1] = accY_Raw/2048.0;
	acc->accData[2] = accZ_Raw/2048.0;
}

void MPU6050_Read_Temp(MPU6050_t* data) {
    uint8_t buffer[2];
    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, TEMP_OUT_H_REG, 1, buffer, 2, 1000);

    int16_t tempRaw = (buffer[0] << 8) | buffer[1];
    data->temp = (float)(tempRaw / 340.0 + 36.53); // Convert raw value to Celsius
}