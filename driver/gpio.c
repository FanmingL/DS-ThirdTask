#include "main.h"
/*----PB0-A1----PB1-A2--PC12-B1--PD2-B2--*/
/*A-left-----------------------------B-right*/
/*--------------PE13-ENABLE-------------*/
/*D5---PB5*/
/*D6---PB14*/
/*D7--PB3*/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef gpio;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	/*---PB0---PB1-*/
	gpio.GPIO_Mode = GPIO_Mode_OUT; 
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_6|GPIO_Pin_7;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&gpio);
	gpio.GPIO_Pin=GPIO_Pin_2;
	GPIO_Init(GPIOA,&gpio);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
//	/*-----PD12----*/
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//	gpio.GPIO_Pin = GPIO_Pin_12;
//	GPIO_Init(GPIOC,&gpio);
//	/*-------PC2-----*/
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//	gpio.GPIO_Pin = GPIO_Pin_2;
//	GPIO_Init(GPIOD,&gpio);
//	/*------PE13---------*/
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//	gpio.GPIO_Pin = GPIO_Pin_13;
//	/
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
//	gpio.GPIO_Pin = GPIO_Pin_13;
	
//	GPIO_Init(GPIOE,&gpio);
//	LEFT_UP();
//	RIGHT_UP();
}
