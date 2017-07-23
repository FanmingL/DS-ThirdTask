#include "main.h"

int x=0,y=0;							//X_MAX=240,Y_MAX=320
void EXTI0_IRQHandler(void)
{		 
	LCD_Clear(BLACK);
	x=0;y=0;
	EXTI_ClearITPendingBit(EXTI_Line0);//清除LINE2上的中断标志位 
}






