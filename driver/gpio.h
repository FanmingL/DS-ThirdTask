#ifndef _GPIO_H_
#define _GPIO_H_
void GPIO_Configuration(void);
#define UP() \
									GPIO_ResetBits(GPIOB,GPIO_Pin_6);\
									GPIO_SetBits(GPIOB,GPIO_Pin_7);
#define DOWN() \
									GPIO_SetBits(GPIOB,GPIO_Pin_6);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_7);
#define STOP() \
									GPIO_ResetBits(GPIOB,GPIO_Pin_6);\
									GPIO_ResetBits(GPIOB,GPIO_Pin_7);

#define MotorEnable() GPIO_SetBits(GPIOA,GPIO_Pin_2);
#define MotorDisable() GPIO_ResetBits(GPIOA,GPIO_Pin_2);
#endif

