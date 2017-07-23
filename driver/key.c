#include "main.h"

void key_init(){
	GPIO_InitTypeDef GI;		//������ʼ������
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);		//ʹ�ܶ˿�Fʱ��
	GI.GPIO_Mode=GPIO_Mode_IN;
	GI.GPIO_Pin=GPIO_Pin_0;
	GI.GPIO_PuPd=GPIO_PuPd_UP;
	GI.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GI);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);//PA8���ж���8
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger =   EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
}
