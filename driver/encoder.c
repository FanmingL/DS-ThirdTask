#include "main.h"
_encoder_st motor_encoder=Encoder_InitVal;
/*-----MOTOR----TIM3*/
void Encoder_Configuration(void)
{
		GPIO_InitTypeDef gpio;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
		gpio.GPIO_Mode = GPIO_Mode_AF;
		gpio.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOA,&gpio);
	

		GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
    TIM_Cmd(TIM3,ENABLE);	
}



void Encoder_Start(void)
{
    TIM3->CNT = 0x00;
		
}
void Refresh_Encoder(void)
{
	int TIM_TIM3;
	
	TIM_TIM3 = (short)TIM3 -> CNT; TIM3->CNT=0;
	
	motor_encoder.T=((GetInnerLoop(MOTOR_TIME))/1000000.0f);
	
	motor_encoder.encoder_temp = TIM_TIM3*PWMToDegree;
	
	motor_encoder.speed=ANGLE_TO_RADIAN*TIM_TIM3*PWMToDegree/motor_encoder.T;
	
	motor_encoder.degree += motor_encoder.encoder_temp;
	
	if (motor_encoder.degree>360){motor_encoder.degree-=360;motor_encoder.circle_cnt++;}
	else if(motor_encoder.degree<0){motor_encoder.degree+=360;motor_encoder.circle_cnt--;}
	
}
