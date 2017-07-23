#include "main.h"
u16 KEY1_PRESS_FLAG,KEY3_PRESS_FLAG,KEY2_PRESS_FLAG=0;
void EXTI9_5_IRQHandler(void)
{		 
	if(EXTI_GetITStatus(EXTI_Line9)){
				KEY2_PRESS_FLAG=!(KEY2);
		EXTI_ClearITPendingBit(EXTI_Line9);}
		if(EXTI_GetITStatus(EXTI_Line7)){
				KEY3_PRESS_FLAG=!(KEY3);
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}

void EXTI15_10_IRQHandler(void)
{		 
	if(EXTI_GetITStatus(EXTI_Line10)){
				KEY1_PRESS_FLAG=!(KEY1);
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}









