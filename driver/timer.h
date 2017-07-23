#ifndef TIMER_H_
#define TIMER_H_


void TIM2_Configuration(void);
#define Get_Time_Micros() (TIM2->CNT)
uint32_t GetInnerLoop(int loop);
void TIM6_Start(void);
void delay_ms(u32 ms);
void delay_us(u32 us);
void TIM6_Configuration(void);
#define INERLOOPLENGTH 7

#define MOTOR_TIME 0
#define PAngle_TIME 1
#define MS_2MS_TIME 2
#define MS_5MS_TIME 3
#define MS_10MS_TIME 4
#define MS_20MS_TIME 5
#define MS_50MS_TIME 6

#endif
