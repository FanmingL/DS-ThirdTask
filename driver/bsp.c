#include "main.h"


void BSP_Init(void)	
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM2_Configuration();
	TIM6_Configuration();
	LED_Configuration();
	TIM6_Start();
}


