#include "main.h"
/*
				USART4   Tx    PA0				Motor3
				USART4   Rx    PA1				Motor4
				WAVE     Tx    PC12				Motor1
				WAVE     Rx		 PD2				Motor2
				MOTOR1         PE14				Motor1
				MOTOR2         PE13				Motor2
				MOTOR3         PE11				Motor3
				MOTOR4         PE9				Motor4
*/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef gpio;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	//////
	gpio.GPIO_Mode = GPIO_Mode_OUT; 
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	/////
	gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOA,&gpio);
	GPIO_ResetBits(GPIOA,gpio.GPIO_Pin);
	////
	gpio.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOC,&gpio);
	GPIO_ResetBits(GPIOC,gpio.GPIO_Pin);
	////
	gpio.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD,&gpio);
	GPIO_ResetBits(GPIOD,gpio.GPIO_Pin);
	//////
	gpio.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_Init(GPIOE,&gpio);
	GPIO_ResetBits(GPIOE,gpio.GPIO_Pin);
	
	All_Positive();
}

void SetAllPWM(short motor1_pwm,short motor2_pwm,short motor3_pwm,short motor4_pwm)
{
	motor1_pwm=LIMIT(motor1_pwm,-1000,1000);
	motor2_pwm=LIMIT(motor2_pwm,-1000,1000);
	motor3_pwm=LIMIT(motor3_pwm,-1000,1000);
	motor4_pwm=LIMIT(motor4_pwm,-1000,1000);
	if (motor1_pwm<0)
	{ 
			MOTOR1_Negtive();
			motor1_pwm=-motor1_pwm;
	}
	else
	{
			MOTOR1_Positive();
	}
	if (motor2_pwm<0)
	{ 
			MOTOR2_Negtive();
			motor2_pwm=-motor2_pwm;
	}
	else
	{
			MOTOR2_Positive();
	}
	if (motor3_pwm<0)
	{ 
			MOTOR3_Negtive();
			motor3_pwm=-motor3_pwm;
	}
	else
	{
			MOTOR3_Positive();
	}
	if (motor4_pwm<0)
	{ 
			MOTOR4_Negtive();
			motor4_pwm=-motor4_pwm;
	}
	else
	{
			MOTOR4_Positive();
	}
	motor1_out=motor1_pwm;
	motor2_out=motor2_pwm;
	motor3_out=motor3_pwm;
	motor4_out=motor4_pwm;
	SetPWMOut(motor1_pwm,motor2_pwm,motor3_pwm,motor4_pwm);

}
