#ifndef _CONTROL_TASK_H_
#define _CONTROL_TASK_H_

void ControlLoop(void);
extern float	motor1_out,motor2_out,motor3_out,motor4_out;
extern float exp_pitch,exp_roll,RotateAngleNow,AngleWithGradianteNow,RotateAngleNowTest;
#endif

