#include "main.h"
#include "math.h"
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
#define HEIGHT 73.727f
u32 SystemTimeMs=0;
float exp_pitch=0.0f,exp_roll=0.0f;					//-8.3,-12.4
float pitch_position_out=0,pitch_speed_out=0,
			roll_position_out=0,roll_speed_out=0,
			motor1_out=0,motor2_out=0,motor3_out=0,motor4_out=0;
float RotateAngleNow=0,AngleWithGradianteNow=0,RotateAngleNowTest=0;
//��һ��

static void All_PID_Cal(float T)
{
		pitch_position_out=-PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										exp_pitch,				//����ֵ���趨ֵ��
										Pitch,			//����ֵ����
										&PitchP_arg, //PID�����ṹ��
										&PitchP_val,	//PID���ݽṹ��
										20		//integration limit�������޷�
										 );
		motor1_out=PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										pitch_position_out,				//����ֵ���趨ֵ��
										mpu6050.Gyro_deg.y,			//����ֵ����
										&PitchS_arg, //PID�����ṹ��
										&PitchS_val,	//PID���ݽṹ��
										10			//integration limit�������޷�
										 );
		
		roll_position_out=PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										exp_roll,				//����ֵ���趨ֵ��
										Roll,			//����ֵ����
										&PitchP_arg, //PID�����ṹ��
										&RollP_val,	//PID���ݽṹ��
										20			//integration limit�������޷�
										 );
		motor2_out=PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										roll_position_out,				//����ֵ���趨ֵ��
										mpu6050.Gyro_deg.x,			//����ֵ����
										&PitchS_arg, //PID�����ṹ��
										&RollS_val,	//PID���ݽṹ��
										10			//integration limit�������޷�
										 );
		SetAllPWM((short)motor1_out,(short)motor2_out,-(short)motor1_out,-(short)motor2_out);
}

static void exp_angle_update(float RotateAngle, float Exp_AngleWithGradiant)
{
	float q0,q1,q2,q3,norm;
	RotateAngle=(-RotateAngle+MY_PPPIII_HALF);
				q0 = my_cos(Exp_AngleWithGradiant/2.0f),
				q1 = my_sin(Exp_AngleWithGradiant/2.0f)*cos(RotateAngle),
				q2 = my_sin(Exp_AngleWithGradiant/2.0f)*sin(RotateAngle),
				q3 = 0;
	 norm = my_sqrt(q0*q0+q1*q1+q2*q2+q3*q3);
	q0=q0/norm;
	q1=q1/norm;
	q2=q2/norm;
	q3=q3/norm;
	exp_roll = fast_atan2(2*(q0*q1 + q2*q3),1 - 2*(q1*q1 + q2*q2)) *57.3f;
	exp_pitch = -asin(2*(q1*q3 - q0*q2)) *57.3f;
}

#define TASK1_ANGLEWITHGRIADIANTE 17.0f
static void Task1_Motion(float T, u32 Sys_Time_Ms)
{
	static int mode =0;
	if (mode==0)
		{
				exp_angle_update(-174.0f*RAD_PER_DEG,LIMIT(AngleWithGradianteNow+2.0f*RAD_PER_DEG,-TASK1_ANGLEWITHGRIADIANTE*RAD_PER_DEG,TASK1_ANGLEWITHGRIADIANTE*RAD_PER_DEG));
				if (AngleWithGradianteNow>=TASK1_ANGLEWITHGRIADIANTE*RAD_PER_DEG)mode=1-mode;
		}
		else	
		{
			exp_angle_update(-174.0f*RAD_PER_DEG,LIMIT(AngleWithGradianteNow-2.0f*RAD_PER_DEG,-TASK1_ANGLEWITHGRIADIANTE*RAD_PER_DEG,TASK1_ANGLEWITHGRIADIANTE*RAD_PER_DEG));
			if (AngleWithGradianteNow<=-TASK1_ANGLEWITHGRIADIANTE*RAD_PER_DEG)mode=1-mode;
		}
				All_PID_Cal(T);
}
//�ڶ������һ������ͬ�Ĵ���
#define TASK2_ANGLEWITHGRIADIANTE 13.0f
static void Task2_Motion(float T, u32 Sys_Time_Ms)
{
		static int mode =0;
		if (mode==0)
		{
				exp_angle_update(-174.0f*RAD_PER_DEG,LIMIT(AngleWithGradianteNow+2.0f*RAD_PER_DEG,-TASK2_ANGLEWITHGRIADIANTE*RAD_PER_DEG,TASK2_ANGLEWITHGRIADIANTE*RAD_PER_DEG));
				if (AngleWithGradianteNow>=TASK2_ANGLEWITHGRIADIANTE*RAD_PER_DEG)mode=1-mode;
		}
		else	
		{
			exp_angle_update(-174.0f*RAD_PER_DEG,LIMIT(AngleWithGradianteNow-2.0f*RAD_PER_DEG,-TASK2_ANGLEWITHGRIADIANTE*RAD_PER_DEG,TASK2_ANGLEWITHGRIADIANTE*RAD_PER_DEG));
			if (AngleWithGradianteNow<=-TASK2_ANGLEWITHGRIADIANTE*RAD_PER_DEG)mode=1-mode;
		}
		All_PID_Cal(T);
}
//������
static void Task3_Motion(float T, u32 Sys_Time_Ms)
{
	static int mode =0;
	if (mode==0)
		{
				exp_angle_update(ExpAngleFromUsart*RAD_PER_DEG,LIMIT(AngleWithGradianteNow+2.0f*RAD_PER_DEG,-AngleWithGradiantFromUsart*RAD_PER_DEG,AngleWithGradiantFromUsart*RAD_PER_DEG));
				if (AngleWithGradianteNow>=AngleWithGradiantFromUsart*ANGLE_TO_RADIAN)mode=1-mode;
		}
		else	
		{
			exp_angle_update(ExpAngleFromUsart*RAD_PER_DEG,LIMIT(AngleWithGradianteNow-2.0f*RAD_PER_DEG,-AngleWithGradiantFromUsart*RAD_PER_DEG,AngleWithGradiantFromUsart*RAD_PER_DEG));
			if (AngleWithGradianteNow<=-AngleWithGradiantFromUsart*ANGLE_TO_RADIAN)mode=1-mode;
		}
		All_PID_Cal(T);
}
//������
static void Task4_Motion(float T, u32 Sys_Time_Ms)
{
//	exp_pitch=0.0f,exp_roll=0.0f;
//	pitch_position_out=-PID_calculate( T,            //���ڣ���λ���룩
//										0,				//ǰ��ֵ
//										exp_pitch,				//����ֵ���趨ֵ��
//										Pitch,			//����ֵ����
//										&PitchP_arg, //PID�����ṹ��
//										&PitchP_val,	//PID���ݽṹ��
//										20		//integration limit�������޷�
//										 );
		motor1_out=PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										0,				//����ֵ���趨ֵ��
										mpu6050.Gyro_deg.y,			//����ֵ����
										&PitchS_arg, //PID�����ṹ��
										&PitchS_val,	//PID���ݽṹ��
										10			//integration limit�������޷�
										 );
		
//		roll_position_out=PID_calculate( T,            //���ڣ���λ���룩
//										0,				//ǰ��ֵ
//										exp_roll,				//����ֵ���趨ֵ��
//										Roll,			//����ֵ����
//										&PitchP_arg, //PID�����ṹ��
//										&RollP_val,	//PID���ݽṹ��
//										20			//integration limit�������޷�
//										 );
		motor2_out=PID_calculate( T,            //���ڣ���λ���룩
										0,				//ǰ��ֵ
										0,				//����ֵ���趨ֵ��
										mpu6050.Gyro_deg.x,			//����ֵ����
										&PitchS_arg, //PID�����ṹ��
										&RollS_val,	//PID���ݽṹ��
										10			//integration limit�������޷�
										 );
		SetAllPWM((short)motor1_out,(short)motor2_out,-(short)motor1_out,-(short)motor2_out);
}


#define EXP_ROTATEANGLE (9.25f*RAD_PER_DEG)
//������
static void Task5_Motion(float T, u32 Sys_Time_Ms)
{
	exp_angle_update(RotateAngleNow+0.5f*RAD_PER_DEG,EXP_ROTATEANGLE);
	All_PID_Cal(T);
}
//������
static void Task6_Motion(float T, u32 Sys_Time_Ms)
{
	exp_angle_update(RotateAngleNow+0.5f*RAD_PER_DEG,EXP_ROTATEANGLE);
	All_PID_Cal(T);
}
//���Ե��ת���Լ�ת������
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
	static float RotateAngleLast=0.0f,Temp=0.0f;
	MPU6050_Read();
	MPU6050_Data_Prepare( inner_loop_time );
 	IMUupdate(0.5f *inner_loop_time,mpu6050.Gyro_deg.x, mpu6050.Gyro_deg.y, mpu6050.Gyro_deg.z, //����IMU
						mpu6050.Acc.x, mpu6050.Acc.y, mpu6050.Acc.z,&Roll,&Pitch,&Yaw);

	AngleWithGradianteNow	=	asin(my_sqrt(ref_q[1]*ref_q[1]+ref_q[2]*ref_q[2]))*2;
	if (NS==Task5||NS==Task6){
	RotateAngleNow			=	(fast_atan2(ref_q[2],ref_q[1]))+Temp;
	if ((RotateAngleLast-RotateAngleNow)>330.0f*RAD_PER_DEG){
		RotateAngleNow+=360.0f*RAD_PER_DEG;
		Temp+=360.0f*RAD_PER_DEG;
	}else if ((RotateAngleLast-RotateAngleNow)<-330.0f*RAD_PER_DEG)
	{
		RotateAngleNow-=360.0f*RAD_PER_DEG;
		Temp-=360.0f*RAD_PER_DEG;
	}
	RotateAngleLast=RotateAngleNow;
}else
	{
		RotateAngleNow	=	(fast_atan2(ref_q[2],ref_q[1]));
		if (RotateAngleNow<0){
			RotateAngleNow+=MY_PPPIII;
			AngleWithGradianteNow=-AngleWithGradianteNow;
		}
		RotateAngleNowTest	=	-(atan(Pitch/Roll))+MY_PPPIII_HALF;
	}
//}
//	else
//	{	
//		RotateAngleNow	=	(atan(Pitch/Roll));

//	
//	}
}

	

static void Task_5ms(void)
{	
	float inner_loop_time = GetInnerLoop(Task_5ms_Time)/1000000.0f;
	ControlAngle(inner_loop_time,SystemTimeMs);
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
	SystemTimeMs++;
	if (SystemTimeMs%2==0)Task_2ms();
	if (SystemTimeMs%5==0)Task_5ms();
	if (SystemTimeMs%10==0)Task_10ms();
	if (SystemTimeMs%20==0)Task_20ms();
	if (SystemTimeMs%50==0)Task_50ms();
	DataTransferTask(SystemTimeMs);
}


