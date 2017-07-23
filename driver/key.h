#ifndef __KEY_H
#define __KEY_H
//KEY define
void key_init(void);
#define KEY2 (GPIOA->IDR&GPIO_Pin_9)
#define KEY1 (GPIOA->IDR&GPIO_Pin_10)
#define KEY3 (GPIOA->IDR&GPIO_Pin_7)
#endif
