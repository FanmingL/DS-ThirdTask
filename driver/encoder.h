#ifndef _ENCODER_H_
#define _ENCODER_H_

#define PWMToDegree 0.9230769f					//390Ïß
#define ANGLE_TO_RADIAN 0.01745329f
void Encoder_Configuration(void);
typedef struct 
{
	float speed;
	float degree;
	int circle_cnt;
	float T;
	float encoder_temp;
}_encoder_st;
#define Encoder_InitVal {\
													0.0f,\
													0.0f,\
													0,\
													0.0f,\
													0.0f}
extern _encoder_st motor_encoder;
void Encoder_Start(void);
void Refresh_Encoder(void);
#endif
