#ifndef _LED_H_
#define _LED_H_
void LED_Configuration(void);
#define LED_Duty() GPIO_ToggleBits(GPIOA,GPIO_Pin_5)
#endif
