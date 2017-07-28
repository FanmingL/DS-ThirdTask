#include "main.h"
#include "math.h"
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
u32 SystemTimeMs=0;
float exp_pitch=0.0f,exp_roll=0.0f;					//-8.3,-12.4
float pitch_position_out=0,pitch_speed_out=0,
			roll_position_out=0,roll_speed_out=0,
			motor1_out=0,motor2_out=0,motor3_out=0,motor4_out=0;
//第一题

static void All_PID_Cal(float T)
{
		pitch_position_out=-PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										exp_pitch,				//期望值（设定值）
										Pitch,			//反馈值（）
										&PitchP_arg, //PID参数结构体
										&PitchP_val,	//PID数据结构体
										20		//integration limit，积分限幅
										 );
		motor1_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										pitch_position_out,				//期望值（设定值）
										mpu6050.Gyro_deg.y,			//反馈值（）
										&PitchS_arg, //PID参数结构体
										&PitchS_val,	//PID数据结构体
										10			//integration limit，积分限幅
										 );
		
		roll_position_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										exp_roll,				//期望值（设定值）
										Roll,			//反馈值（）
										&PitchP_arg, //PID参数结构体
										&RollP_val,	//PID数据结构体
										20			//integration limit，积分限幅
										 );
		motor2_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										roll_position_out,				//期望值（设定值）
										mpu6050.Gyro_deg.x,			//反馈值（）
										&PitchS_arg, //PID参数结构体
										&RollS_val,	//PID数据结构体
										10			//integration limit，积分限幅
										 );
		SetAllPWM((short)motor1_out,(short)motor2_out,-(short)motor1_out,-(short)motor2_out);
}

static void Task1_Motion(float T, u32 Sys_Time_Ms)
{
	static int mode =0;
	if (mode==0)
		{
				exp_pitch=LIMIT(Pitch+3.0f,-15.0f,15.0f);
				if (Pitch>=14.5f&&my_abs(mpu6050.Gyro_deg.y)<=100)
				{
					mode=1-mode;
				}
		}
		else	
		{
			exp_pitch=LIMIT(Pitch-3.0f,-15.0f,15.0f);
			if (Pitch<=-14.5f&&my_abs(mpu6050.Gyro_deg.y)<=100)
			{
				mode=1-mode;
			}	
		}
		All_PID_Cal(T);
	
}
//第二题与第一题用相同的代码
static void Task2_Motion(float T, u32 Sys_Time_Ms)
{
	Task1_Motion(T,Sys_Time_Ms);
}
//第三题
static void Task3_Motion(float T, u32 Sys_Time_Ms)
{

}
//第四题
static void Task4_Motion(float T, u32 Sys_Time_Ms)
{
	exp_pitch=0.0f,exp_roll=0.0f;
	pitch_position_out=-PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										exp_pitch,				//期望值（设定值）
										Pitch,			//反馈值（）
										&PitchP_arg, //PID参数结构体
										&PitchP_val,	//PID数据结构体
										20		//integration limit，积分限幅
										 );
		motor1_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										0,				//期望值（设定值）
										mpu6050.Gyro_deg.y,			//反馈值（）
										&PitchS_arg, //PID参数结构体
										&PitchS_val,	//PID数据结构体
										10			//integration limit，积分限幅
										 );
		
		roll_position_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										exp_roll,				//期望值（设定值）
										Roll,			//反馈值（）
										&PitchP_arg, //PID参数结构体
										&RollP_val,	//PID数据结构体
										20			//integration limit，积分限幅
										 );
		motor2_out=PID_calculate( T,            //周期（单位：秒）
										0,				//前馈值
										0,				//期望值（设定值）
										mpu6050.Gyro_deg.x,			//反馈值（）
										&PitchS_arg, //PID参数结构体
										&RollS_val,	//PID数据结构体
										10			//integration limit，积分限幅
										 );
		SetAllPWM((short)motor1_out,(short)motor2_out,-(short)motor1_out,-(short)motor2_out);
}

#define EXP_ROTATEANGLE 10.5f/180.0f*3.1415926f
static void exp_angle_update(float RotateAngle)
{
	float q0 = my_cos(EXP_ROTATEANGLE/2.0f),
				q1 = my_sin(EXP_ROTATEANGLE/2.0f)*my_sin(RotateAngle),
				q2 = my_sin(EXP_ROTATEANGLE/2.0f)*my_cos(RotateAngle),
				q3 = 0;
	float norm = my_sqrt(q0*q0+q1*q1+q2*q2+q3*q3);
	q0=q0/norm;
	q1=q1/norm;
	q2=q2/norm;
	q3=q3/norm;
	exp_roll = fast_atan2(2*(q0*q1 + q2*q3),1 - 2*(q1*q1 + q2*q2)) *57.3f;
	exp_pitch = asin(2*(q1*q3 - q0*q2)) *57.3f;
}
//第五题
static void Task5_Motion(float T, u32 Sys_Time_Ms)
{
	float RotateAngleNow=fast_atan2(ref_q[1],ref_q[2]);
	exp_angle_update(RotateAngleNow+0.5f/180.0f*3.1415926f);
	All_PID_Cal(T);
	
}
//第六题
static void Task6_Motion(float T, u32 Sys_Time_Ms)
{

}
//测试电机转速以及转动方向
static void Test_Motion(float T, u32 Sys_Time_Ms)
{
		SetAllPWM(-500,-500,-500,-500);
}

static void Stop_Task(float T, u32 Sys_Time_Ms)
{
		SetAllPWM(0,0,0,0);
		PitchP_val.err_i=0;
		PitchS_val.err_i=0;
		RollP_val.err_i=0;
		RollS_val.err_i=0;
		Motor1_val.err_i=0;
		Motor2_val.err_i=0;
		Motor3_val.err_i=0;
		Motor4_val.err_i=0;

}

static void ControlAngle(float T,u32 Sys_Time_Ms)
{
	if (NS==Task1)
	{
		Task1_Motion(T,Sys_Time_Ms);
	}
	else if (NS==Task2)
	{
		Task2_Motion(T,Sys_Time_Ms);
	}
	else if (NS==Task3)
	{
		Task3_Motion(T,Sys_Time_Ms);
	}
	else if (NS==Task4)
	{
		Task4_Motion(T,Sys_Time_Ms);
	}
	else if (NS==Task5)
	{
		Task5_Motion(T,Sys_Time_Ms);
	}
	else if (NS==Task6) 
	{
		Task6_Motion(T,Sys_Time_Ms);
	}
	else if (NS==Stop)
	{
		Stop_Task(T,Sys_Time_Ms);
	}
	else if (NS==Test)
	{
		Test_Motion(T,Sys_Time_Ms);	
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
	ControlAngle(inner_loop_time,SystemTimeMs);
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
	SystemTimeMs++;
	if (SystemTimeMs%2==0)Task_2ms();
	if (SystemTimeMs%5==0)Task_5ms();
	if (SystemTimeMs%10==0)Task_10ms();
	if (SystemTimeMs%20==0)Task_20ms();
	if (SystemTimeMs%50==0)Task_50ms();
	DataTransferTask(SystemTimeMs);
}


