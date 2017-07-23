#ifndef _PARAMETER_H_
#define _PARAMETER_H_
#include "stm32f4xx.h"



#define PID_ST_SIZE 28u

extern sensor_setup_t sensor_setup;
typedef struct {

_PID_arg_st pid_st[3];
sensor_setup_t sensor_setup;
u8 pid_saved_flag;
}saveToFlash_st;

union _Pid_un_
{
	saveToFlash_st save_to_flash;
	uint8_t pid_array[sizeof(saveToFlash_st)];
};
extern union _Pid_un_ pid_un;
extern _PID_arg_st Chassis_arg;
extern _PID_arg_st PitchS_arg;
extern _PID_arg_st PitchP_arg;
extern _PID_arg_st Theta_arg;

extern _PID_val_st Chassis_left_val;
extern _PID_val_st Chassis_right_val;
extern _PID_val_st PitchS_val;
extern _PID_val_st PitchP_val;
extern _PID_val_st Theta_val;

void Para_ResetToFactorySetup(void);
void Param_SaveAccelOffset(xyz_f_t *offset);
void Param_SaveGyroOffset(xyz_f_t *offset);
void Param_SaveMagOffset(xyz_f_t *offset);
uint8_t AppParamSave(void);
extern u8 pid_saved_flag;
void PID_Para_Init(void);
#define PARAM_SAVED_START_ADDRESS ADDR_FLASH_SECTOR_10
#define PARAM_SAVED_FLAG_ADDRESS ADDR_FLASH_SECTOR_11
#endif

