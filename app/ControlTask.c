#include "main.h"


static void Task_2ms(void)
{
	float inner_loop_time = GetInnerLoop(Task_2ms_Time)/1000000.0f;
	MPU6050_Read();
	MPU6050_Data_Prepare( inner_loop_time );
 	IMUupdate(0.5f *inner_loop_time,mpu6050.Gyro_deg.x, mpu6050.Gyro_deg.y, mpu6050.Gyro_deg.z, //更新IMU
						mpu6050.Acc.x, mpu6050.Acc.y, mpu6050.Acc.z,&Roll,&Pitch,&Yaw);
}

static void Task_5ms(void)
{	

}

static void Task_10ms(void)
{
	ANO_AK8975_Read();										//读取磁力计
}


static void Task_20ms(void)
{
	
}

static void Task_50ms(void)
{
	if (NS==Stop)
	LED_Duty();
}

void ControlLoop(void)																//ControlLoop中将各种任务分为1ms、2ms、5ms、10ms、20ms任务
{
	static u32 SystemTimeMs=0;
	SystemTimeMs++;
	if (SystemTimeMs%2==0)Task_2ms();
	if (SystemTimeMs%5==0)Task_5ms();
	if (SystemTimeMs%10==0)Task_10ms();
	if (SystemTimeMs%20==0)Task_20ms();
	if (SystemTimeMs%50==0)Task_50ms();
	DataTransferTask(SystemTimeMs);
}


