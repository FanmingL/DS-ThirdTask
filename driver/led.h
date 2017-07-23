#ifndef _LED_H_
#define _LED_H_
void LED_Configuration(void);
#define LED_TASK() GPIO_ToggleBits(GPIOB,GPIO_Pin_0)
#endif
