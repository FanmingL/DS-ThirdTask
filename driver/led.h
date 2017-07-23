#ifndef _LED_H_
#define _LED_H_
#define LED_ON() 	GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define LED_OFF() 	GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define LED_TOGGLE() GPIO_ToggleBits(GPIOB,GPIO_Pin_0)
void LED_Configuration(void);

#endif
