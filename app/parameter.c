#include "main.h"
#include "string.h"
_PID_arg_st Chassis_arg;
_PID_arg_st PitchS_arg;
_PID_arg_st PitchP_arg;

_PID_val_st Chassis_left_val;
_PID_val_st Chassis_right_val;
_PID_val_st PitchS_val;
_PID_val_st PitchP_val;

#define PositionPitch_P 14.0f
#define PositionPitch_I 0.0f
#define PositionPitch_D 0.0f
#define SpeedPitch_P 0.7f
#define SpeedPitch_I 0.0f
#define SpeedPitch_D 0.0f
#define Chassis_P 1.5f
#define Chassis_I 30.0f
#define Chassis_D 0.0f
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
 appTosave=1;	
}

void Para_ResetToFactorySetup(void)
{
	Chassis_arg.kp=Chassis_P;
	Chassis_arg.ki=Chassis_I;
	Chassis_arg.kd=Chassis_D;
	Chassis_arg.inc_hz=20.0f;
	Chassis_arg.k_inc_d_norm=0.0;
	Chassis_arg.k_pre_d=0.0f;
	Chassis_arg.k_ff=0.0f;
	
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
	
}

u8 pid_saved_flag=0;
uint8_t AppParamSave(void)
{
	uint8_t retval=1;
	
	pid_un.save_to_flash.pid_st[0]=PitchP_arg;
	pid_un.save_to_flash.pid_st[1]=PitchS_arg;
	pid_un.save_to_flash.pid_st[2]=Chassis_arg;
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
	Chassis_arg=pid_un.save_to_flash.pid_st[2];
	sensor_setup=pid_un.save_to_flash.sensor_setup;
		
	memcpy(&mpu6050.Acc_Offset,&sensor_setup.Offset.Accel,sizeof(xyz_f_t));
	memcpy(&mpu6050.Gyro_Offset,&sensor_setup.Offset.Gyro,sizeof(xyz_f_t));
	memcpy(&ak8975.Mag_Offset,&sensor_setup.Offset.Mag,sizeof(xyz_f_t));
	//memcpy(&mpu6050.vec_3d_cali,&sensor_setup.Offset.vec_3d_cali,sizeof(xyz_f_t));
	
	mpu6050.Acc_Temprea_Offset = sensor_setup.Offset.Acc_Temperature;
	mpu6050.Gyro_Temprea_Offset = sensor_setup.Offset.Gyro_Temperature;
  

	}
}
