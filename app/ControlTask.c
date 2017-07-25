#include "main.h"
/*
��ͷ����������ת��ʱ  �ڸ���������
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
	pitch_position_out=PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										exp_pitch,				//����ֵ���趨ֵ��
										Pitch,			//����ֵ����
										&PitchP_arg, //PID�����ṹ��
										&PitchP_val,	//PID���ݽṹ��
										8		//integration limit�������޷�
										 );
	motor1_out=PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										pitch_position_out,				//����ֵ���趨ֵ��
										-mpu6050.Gyro_deg.y,			//����ֵ����
										&PitchS_arg, //PID�����ṹ��
										&PitchS_val,	//PID���ݽṹ��
										30			//integration limit�������޷�
										 );
		
	roll_position_out=PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										exp_roll,				//����ֵ���趨ֵ��
										Roll,			//����ֵ����
										&PitchP_arg, //PID�����ṹ��
										&RollP_val,	//PID���ݽṹ��
										8			//integration limit�������޷�
										 );
	motor2_out=PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										roll_position_out,				//����ֵ���趨ֵ��
										-mpu6050.Gyro_deg.x,			//����ֵ����
										&PitchS_arg, //PID�����ṹ��
										&RollS_val,	//PID���ݽṹ��
										30			//integration limit�������޷�
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
 	IMUupdate(0.5f *inner_loop_time,mpu6050.Gyro_deg.x, mpu6050.Gyro_deg.y, mpu6050.Gyro_deg.z, //����IMU
						mpu6050.Acc.x, mpu6050.Acc.y, mpu6050.Acc.z,&Roll,&Pitch,&Yaw);
}

static void Task_5ms(void)
{	
	float inner_loop_time = GetInnerLoop(Task_5ms_Time)/1000000.0f;
	ControlAngle(inner_loop_time);
}

static void Task_10ms(void)
{
	ANO_AK8975_Read();										//��ȡ������
}


static void Task_20ms(void)
{
}

static void Task_50ms(void)
{
	if (NS==Stop)
	LED_Duty();
}

void ControlLoop(void)																//ControlLoop�н����������Ϊ1ms��2ms��5ms��10ms��20ms����
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


