#include "main.h"

void All_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);    
	LED_Configuration();																//LED��ʼ��
	TIM2_Configuration();																//��ʱ����ʼ��
	TIM6_Configuration();																//TIM6��ʼ��
	Usart2_Init(115200);																//����2��ʼ��
	PWM_Configuration();																//PWM��ʼ��
	GPIO_Configuration();																//GPIO��ʼ��
	Para_ResetToFactorySetup();													//��flash��ȡ����Ĳ���
	PID_Para_Init();																		//PID��ʼ��
	I2c_Soft_Init();																		//iic��ʼ��
	Delay_ms(100);																			//mpu6050��ʼ��֮ǰ��Ҫ��ʱ
	MPU6050_Init(20); 																	//mpu6050��ʼ������ͨƵ��20Hz
	Delay_ms(100);																			//�����Ƴ�ʼ��ǰ����ʱ
	ak8975_ok = !(ANO_AK8975_Run());										//�����Ƴ�ʼ��
	InnerLoopInit();																		//�ڻ����ڳ�ʼ��
	TIM6_Start();																				//ControlLoop��ʼ
	
}



