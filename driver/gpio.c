#include "main.h"
/*
				USART4   Tx    PA0
				USART4   Rx    PA1
				WAVE     Tx    PC12
				WAVE     Rx		 PD2
				MOTOR1         PE14
				MOTOR2         PE13
				MOTOR3         PE11
				MOTOR4         PE9
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

}
