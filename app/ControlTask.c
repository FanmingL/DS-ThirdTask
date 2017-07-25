#include "main.h"
/*
箭头方向是正向转动时  摆杆受力方向
									roll>0
	
										2
										|
										v
pitch<0 	1	->								<-3			pitch>0
										^
										|
										4
										
									roll<0


*/

float exp_pitch=0,exp_roll=0;
float pitch_position_out=0,pitch_speed_out=0,
			roll_position_out=0,roll_speed_out=0,
			motor1_out=0,motor2_out=0,motor3_out=0,motor4_out=0;
static void ControlAngle(float T)
{
	if (NS==Task1){
	pitch_position_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										exp_pitch,				//期望值（设定值）
										Pitch,			//反馈值（）
										&PitchP_arg, //PID参数结构体
										&PitchP_val,	//PID数据结构体
										8		//integration limit，积分限幅
										 );
	motor1_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										pitch_position_out,				//期望值（设定值）
										-mpu6050.Gyro_deg.y,			//反馈值（）
										&PitchS_arg, //PID参数结构体
										&PitchS_val,	//PID数据结构体
										30			//integration limit，积分限幅
										 );
		
	roll_position_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										exp_roll,				//期望值（设定值）
										Roll,			//反馈值（）
										&PitchP_arg, //PID参数结构体
										&RollP_val,	//PID数据结构体
										8			//integration limit，积分限幅
										 );
	motor2_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										roll_position_out,				//期望值（设定值）
										-mpu6050.Gyro_deg.x,			//反馈值（）
										&PitchS_arg, //PID参数结构体
										&RollS_val,	//PID数据结构体
										30			//integration limit，积分限幅
										 );
	SetAllPWM((short)motor1_out,(short)motor2_out,-(short)motor1_out,-(short)motor2_out);
	}
	else if (NS==Task2)
	{
	
	}
	else if (NS==Task3)
	{
	
	
	}
	else if (NS==Task4)
	{
	
	}
	else if (NS==Task5)
	{
	
	
	}
	else if (NS==Task6) 
	{
	
	}
	else if (NS==Stop)
	{
	SetAllPWM(0,0,0,0);
	}
}


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
	float inner_loop_time = GetInnerLoop(Task_5ms_Time)/1000000.0f;
	ControlAngle(inner_loop_time);
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


