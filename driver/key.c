#include "main.h"

void key_init(void){
	GPIO_InitTypeDef GI;		//申明初始化变量
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);		
	GI.GPIO_Mode=GPIO_Mode_IN;
	GI.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_7;
	GI.GPIO_PuPd=GPIO_PuPd_UP;
	GI.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GI);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource9);//PA8对中断线8
	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger =   EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	////////////////////////////////////////////////////////////////////////////////
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource10);//PA8对中断线8
	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger =   EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	/////////////////////////////////////////////////////////////////////////////
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource7);//PA8对中断线8
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger =   EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
}
