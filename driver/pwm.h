#ifndef _PWM_H_
#define _PWM_H_

void PWM_Configuration(void);
void SetAllPWM(short motor1_pwm,short motor2_pwm,short motor3_pwm,short motor4_pwm);
#define SetPWMOut(CH1,CH2,CH3,CH4) \
											TIM3->CCR1=CH1;\
											TIM3->CCR2=CH2;\
											TIM3->CCR3=CH3;\
											TIM3->CCR4=CH4;

#endif
