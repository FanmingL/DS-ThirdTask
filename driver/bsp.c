#include "main.h"

void All_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);    
	LED_Configuration();																//LED初始化
	TIM2_Configuration();																//定时器初始化
	TIM6_Configuration();																//TIM6初始化
	Usart2_Init(115200);																//串口2初始化
	PWM_Configuration();																//PWM初始化
	GPIO_Configuration();																//GPIO初始化
	Para_ResetToFactorySetup();													//从flash读取保存的参数
	PID_Para_Init();																		//PID初始化
	I2c_Soft_Init();																		//iic初始化
	Delay_ms(100);																			//mpu6050初始化之前必要延时
	MPU6050_Init(20); 																	//mpu6050初始化，低通频率20Hz
	Delay_ms(100);																			//磁力计初始化前的延时
	ak8975_ok = !(ANO_AK8975_Run());										//磁力计初始化
	InnerLoopInit();																		//内环周期初始化
	TIM6_Start();																				//ControlLoop开始
	
}



