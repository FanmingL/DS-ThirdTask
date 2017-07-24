#include "main.h"
/*-----PA5----LED----*/
void LED_Configuration(void)
{
	GPIO_InitTypeDef gpio;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_OUT; 
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = GPIO_Pin_5;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

