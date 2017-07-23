#include "main.h"


void TIM2_Configuration(void)	
{
    TIM_TimeBaseInitTypeDef tim;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    tim.TIM_Period = 0xFFFFFFFF;
    tim.TIM_Prescaler = 84 - 1;	 //1M ��ʱ��  
    tim.TIM_ClockDivision = TIM_CKD_DIV1;	
    tim.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_ARRPreloadConfig(TIM2, ENABLE);	
    TIM_TimeBaseInit(TIM2, &tim);
    TIM_Cmd(TIM2,ENABLE);	
}
void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
		{
			  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		}
}

void delay_us(uint32_t us)										//��TIM2�ļ���ֵ��������ȷ��ʱ
{
    uint32_t now = Get_Time_Micros();
    while (Get_Time_Micros() - now < us);
}

void delay_ms(uint32_t ms)
{
    while (ms--)
        delay_us(1000);
}


uint32_t GetInnerLoop(int loop)								//���ڻ�þ�ȷ�ĺ������õ�����
{
	static uint32_t Time[2][INERLOOPLENGTH]={0};//Time[0] is the last time, Time[1] is the new time;
	Time[0][loop] = Time[1][loop];
	Time[1][loop] = Get_Time_Micros();
	return Time[1][loop]-Time[0][loop];
}

void InnerLoopInit(void)
{
	int i=0;
	for (i=0;i<INERLOOPLENGTH;i++)
	{
		GetInnerLoop(i);
	}
}	
void TIM6_Configuration(void)							
{
    TIM_TimeBaseInitTypeDef  tim;
    NVIC_InitTypeDef         nvic;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
    
    nvic.NVIC_IRQChannel = TIM6_DAC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    tim.TIM_Prescaler = 84-1;        //84M internal clock
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_Period = 1000 - 1;  //1ms,1000Hz
    TIM_TimeBaseInit(TIM6,&tim);
}

void TIM6_Start(void)
{
    TIM_Cmd(TIM6, ENABLE);	 
    TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);	
}
void TIM6_DAC_IRQHandler(void)									//TIM6�Ļص�����1ms����һ�Σ����ھ�ȷ����ControlLoop
{
	 if (TIM_GetITStatus(TIM6,TIM_IT_Update)!= RESET) 
	  {
			TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
			TIM_ClearFlag(TIM6, TIM_FLAG_Update);
			ControlTask();
    }

}
