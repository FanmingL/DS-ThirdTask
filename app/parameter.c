#include "main.h"
#include "string.h"
_PID_arg_st Motor_arg;
_PID_arg_st PitchS_arg;
_PID_arg_st PitchP_arg;
_PID_arg_st RollS_arg;
_PID_arg_st RollP_arg;

_PID_val_st Motor1_val;
_PID_val_st	Motor2_val;
_PID_val_st Motor3_val;
_PID_val_st	Motor4_val;

_PID_val_st PitchS_val;
_PID_val_st PitchP_val;
_PID_val_st RollS_val;
_PID_val_st RollP_val;


#define PositionPitch_P 0.0f
#define PositionPitch_I 0.0f
#define PositionPitch_D 0.0f

#define SpeedPitch_P 0.0f
#define SpeedPitch_I 0.0f
#define SpeedPitch_D 0.0f

#define PositionRoll_P 0.0f
#define PositionRoll_I 0.0f
#define PositionRoll_D 0.0f

#define SpeedRoll_P 0.0f
#define SpeedRoll_I 0.0f
#define SpeedRoll_D 0.0f

#define Motor_P 0.0f
#define Motor_I 0.0f
#define Motor_D 0.0f
union _Pid_un_ pid_un;


void Param_SaveAccelOffset(xyz_f_t *offset)
{
 memcpy(&mpu6050.Acc_Offset,offset,sizeof(xyz_f_t));
 memcpy(&sensor_setup.Offset.Accel, offset,sizeof(xyz_f_t));
	
 sensor_setup.Offset.Acc_Temperature = mpu6050.Acc_Temprea_Offset ;
}

void Param_SaveGyroOffset(xyz_f_t *offset)
{
 memcpy(&mpu6050.Gyro_Offset,offset,sizeof(xyz_f_t));
 memcpy(&sensor_setup.Offset.Gyro, offset,sizeof(xyz_f_t));
	
 sensor_setup.Offset.Gyro_Temperature = mpu6050.Gyro_Temprea_Offset ;
}

void Param_SaveMagOffset(xyz_f_t *offset)
{
 memcpy(&ak8975.Mag_Offset,offset,sizeof(xyz_f_t));
 memcpy(&sensor_setup.Offset.Mag, offset,sizeof(xyz_f_t));
}

void Para_ResetToFactorySetup(void)
{
	Motor_arg.kp=Motor_P;
	Motor_arg.ki=Motor_I;
	Motor_arg.kd=Motor_D;
	Motor_arg.inc_hz=20.0f;
	Motor_arg.k_inc_d_norm=0.0;
	Motor_arg.k_pre_d=0.0f;
	Motor_arg.k_ff=0.0f;
	
	PitchS_arg.kp=SpeedPitch_P;
	PitchS_arg.ki=SpeedPitch_I;
	PitchS_arg.kd=SpeedPitch_D;
	PitchS_arg.inc_hz=20.0f;
	PitchS_arg.k_inc_d_norm=0.0f;
	PitchS_arg.k_pre_d=0.0f;
	PitchS_arg.k_ff=0.0f;
	
	PitchP_arg.kp=PositionPitch_P;
	PitchP_arg.ki=PositionPitch_I;
	PitchP_arg.kd=PositionPitch_D;
	PitchP_arg.inc_hz=20.0f;
	PitchP_arg.k_inc_d_norm=0.0f;
	PitchP_arg.k_pre_d=0.0f;
	PitchP_arg.k_ff=0.0f;
	
	RollS_arg.kp=SpeedRoll_P;
	RollS_arg.ki=SpeedRoll_I;
	RollS_arg.kd=SpeedRoll_D;
	RollS_arg.inc_hz=20.0f;
	RollS_arg.k_inc_d_norm=0.0f;
	RollS_arg.k_pre_d=0.0f;
	RollS_arg.k_ff=0.0f;
	
	RollP_arg.kp=PositionRoll_P;
	RollP_arg.ki=PositionRoll_I;
	RollP_arg.kd=PositionRoll_D;
	RollP_arg.inc_hz=20.0f;
	RollP_arg.k_inc_d_norm=0.0f;
	RollP_arg.k_pre_d=0.0f;
	RollP_arg.k_ff=0.0f;
	
}

u8 pid_saved_flag=0;
uint8_t AppParamSave(void)
{
	uint8_t retval=1;
	
	pid_un.save_to_flash.pid_st[0]=PitchP_arg;
	pid_un.save_to_flash.pid_st[1]=PitchS_arg;
	pid_un.save_to_flash.pid_st[2]=RollP_arg;
	pid_un.save_to_flash.pid_st[3]=RollS_arg;
	pid_un.save_to_flash.pid_st[4]=Motor_arg;
	pid_un.save_to_flash.pid_saved_flag=1;
	pid_un.save_to_flash.sensor_setup=sensor_setup;
	BSP_FLASH_Write(PARAM_SAVED_START_ADDRESS, pid_un.pid_array, sizeof(saveToFlash_st));
	PID_Para_Init();
//	pid_saved_flag=1;
//	BSP_FLASH_Write(PARAM_SAVED_FLAG_ADDRESS, &pid_saved_flag, 1);
   return retval;
}

void PID_Para_Init(void)
{
	//BSP_FLASH_Read(PARAM_SAVED_FLAG_ADDRESS,&pid_saved_flag,1);
	BSP_FLASH_Read(PARAM_SAVED_START_ADDRESS, pid_un.pid_array, sizeof(saveToFlash_st));
	if (pid_un.save_to_flash.pid_saved_flag==1){

	
	PitchP_arg=pid_un.save_to_flash.pid_st[0];
	PitchS_arg=pid_un.save_to_flash.pid_st[1];
	RollP_arg=pid_un.save_to_flash.pid_st[2];
	RollS_arg=pid_un.save_to_flash.pid_st[3];
	Motor_arg=pid_un.save_to_flash.pid_st[4];
		
	sensor_setup=pid_un.save_to_flash.sensor_setup;
		
	memcpy(&mpu6050.Acc_Offset,&sensor_setup.Offset.Accel,sizeof(xyz_f_t));
	memcpy(&mpu6050.Gyro_Offset,&sensor_setup.Offset.Gyro,sizeof(xyz_f_t));
	memcpy(&ak8975.Mag_Offset,&sensor_setup.Offset.Mag,sizeof(xyz_f_t));
	//memcpy(&mpu6050.vec_3d_cali,&sensor_setup.Offset.vec_3d_cali,sizeof(xyz_f_t));
	
	mpu6050.Acc_Temprea_Offset = sensor_setup.Offset.Acc_Temperature;
	mpu6050.Gyro_Temprea_Offset = sensor_setup.Offset.Gyro_Temperature;
  

	}
}
