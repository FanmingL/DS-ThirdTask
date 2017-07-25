#ifndef _GPIO_H_
#define _GPIO_H_
void GPIO_Configuration(void);

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

#define MOTOR1_Positive() GPIO_SetBits(GPIOC,GPIO_Pin_12);\
													GPIO_ResetBits(GPIOE,GPIO_Pin_14);
#define MOTOR1_Negtive() GPIO_ResetBits(GPIOC,GPIO_Pin_12);\
													GPIO_SetBits(GPIOE,GPIO_Pin_14);
#define MOTOR2_Positive() GPIO_SetBits(GPIOD,GPIO_Pin_2);\
													GPIO_ResetBits(GPIOE,GPIO_Pin_13);
#define MOTOR2_Negtive() GPIO_ResetBits(GPIOD,GPIO_Pin_2);\
													GPIO_SetBits(GPIOE,GPIO_Pin_13);
#define MOTOR3_Positive() GPIO_SetBits(GPIOA,GPIO_Pin_0);\
													GPIO_ResetBits(GPIOE,GPIO_Pin_11);
#define MOTOR3_Negtive() GPIO_ResetBits(GPIOA,GPIO_Pin_0);\
													GPIO_SetBits(GPIOE,GPIO_Pin_11);													
#define MOTOR4_Positive() GPIO_SetBits(GPIOA,GPIO_Pin_1);\
													GPIO_ResetBits(GPIOE,GPIO_Pin_9);
#define MOTOR4_Negtive() GPIO_ResetBits(GPIOA,GPIO_Pin_1);\
													GPIO_SetBits(GPIOE,GPIO_Pin_9);

#define All_Positive() MOTOR1_Positive();\
												MOTOR2_Positive();\
												MOTOR3_Positive();\
												MOTOR4_Positive();

#endif

