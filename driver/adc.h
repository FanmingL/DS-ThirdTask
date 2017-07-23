#ifndef _ADC_H_
#define _ADC_H_
#define ADC_POSITION_LOWEST 3439
#define ADC_MAX 4096.0f
#define PI 3.141592653f
typedef struct 
{
	float speed;
	float degree;
	float degree_old;
	float sin;
}pendulum_st;
void  Adc_Init(void);
void Refresh_Angle(void);
extern pendulum_st PAngle;
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);
#endif
