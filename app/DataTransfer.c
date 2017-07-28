#include "main.h"
u8 data_to_send[50];

#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
u8 send_pid1=0,send_pid2=0,send_pid3=0,send_check=0;
u8 checkdata_to_send,checksum_to_send;
u8 appTosave=0;


//各种用于数据传输的函数
//发送pitch，roll，yaw三个角度到上位机
void ANO_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, s32 alt, u8 fly_model, u8 armed)
{
	u8 _cnt=0;
	vs16 _temp;
	vs32 _temp2 = alt;
	u8 sum = 0;
	u8 i;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x01;
	data_to_send[_cnt++]=0;
	
	_temp = (int)(angle_rol*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_pit*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = (int)(angle_yaw*100);
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[_cnt++]=BYTE3(_temp2);
	data_to_send[_cnt++]=BYTE2(_temp2);
	data_to_send[_cnt++]=BYTE1(_temp2);
	data_to_send[_cnt++]=BYTE0(_temp2);
	
	data_to_send[_cnt++] = fly_model;
	
	data_to_send[_cnt++] = armed;
	
	data_to_send[3] = _cnt-4;
	

	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	
	Usart2_Send(data_to_send, _cnt);
}
//发送加速度、角速度、磁力计等传感器的原始数据
void ANO_DT_Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z)
{
	u8 _cnt=0;
	vs16 _temp;
		u8 sum = 0;
	u8 i;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x02;
	data_to_send[_cnt++]=0;
	
	_temp = a_x;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_y;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = a_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = g_x;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_y;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = g_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	_temp = m_x;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_y;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = m_z;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
/////////////////////////////////////////
	_temp = 0;	
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);	
	
	data_to_send[3] = _cnt-4;
	

	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++] = sum;
	
	Usart2_Send(data_to_send, _cnt);
}
//1ms调用一次数据传输任务
void DataTransferTask(u32 sys_time)
{
	if (sys_time%10==0){
	ANO_DT_Send_Status(Roll,Pitch,RotateAngleNow*57.3f,0,0,0);
//	ANO_DT_Send_Status(exp_roll,exp_pitch,0,0,0,0);
	}
	else if((sys_time+1)%10==0){
	ANO_DT_Send_Senser(mpu6050.Acc.x,mpu6050.Acc.y,mpu6050.Acc.z,mpu6050.Gyro.x,
												mpu6050.Gyro.y,mpu6050.Gyro.z,
												ak8975.Mag_Val.x,ak8975.Mag_Val.y,ak8975.Mag_Val.z);//mpu6050.Acc.x,mpu6050.Acc.y,mpu6050.Acc.z,mpu6050.Gyro.x
	
	}
	else if((sys_time+2)%10==0)
	{
		if (send_pid1){ANO_DT_Send_PID(1,PitchP_arg.kp,PitchP_arg.ki,PitchP_arg.kd,
																			PitchS_arg.kp,PitchS_arg.ki,PitchS_arg.kd,
																			RollP_arg.kp,RollP_arg.ki,RollP_arg.kd);
		send_pid1=0;}
		else if(send_pid2){
		ANO_DT_Send_PID(2,RollS_arg.kp,RollS_arg.ki,RollS_arg.kd,
																			Motor_arg.kp,Motor_arg.ki,Motor_arg.kd,
																			0,0,0);
		send_pid2=0;
		}
	}else if ((sys_time+5)%10==0){
		ANO_DT_Send_MotoPWM((short)my_abs(motor1_out),(short)my_abs(motor2_out),(short)my_abs(motor1_out),(short)my_abs(motor2_out),0,0,0,0);
	}
	else {
		if (send_check){
		send_check = 0;
				ANO_DT_Send_Check(checkdata_to_send,checksum_to_send);
		}
	
	}


}
//串口1数据解析
void Usart1_DataPrepare(u8 com_data)
{

}
//串口2数据解析
void Usart2_DataPrepare(u8 data)
{
	static u8 RxBuffer[50];
	static u8 _data_len = 0,_data_cnt = 0;
	static u8 state = 0;
	
	if(state==0&&data==0xAA)						//判断帧头
	{
		state=1;
		RxBuffer[0]=data;
	}
	else if(state==1&&data==0xAF)			//帧头
	{
		state=2;
		RxBuffer[1]=data;
	}
	else if(state==2&&data<0XF1)			//帧类型
	{
		state=3;
		RxBuffer[2]=data;
	}
	else if(state==3&&data<50)				//帧长
	{
		state = 4;
		RxBuffer[3]=data;
		_data_len = data;
		_data_cnt = 0;
	}
	else if(state==4&&_data_len>0)		//数据帧
	{
		_data_len--;
		RxBuffer[4+_data_cnt++]=data;
		if(_data_len==0)
			state = 5;
	}
	else if(state==5)								//校验帧
	{
		state = 0;
		RxBuffer[4+_data_cnt]=data;
		Data_Receive_Anl(RxBuffer,_data_cnt+5);
		
	}
	else
		state = 0;

}
float AngleWithGradiantFromUsart=0.0f,ExpAngleFromUsart=0.0f;
enum PendulumMode NS=Stop;										//NS用于切换模式，Stop为停止模式，Task1到Task6分别为题1至题2
void Data_Receive_Anl(u8 *data_buf,u8 num)
{
	u8 sum = 0;
	u8 i;
	for(i=0;i<(num-1);i++)														//求和校验
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		return;						//校验不成功则return
	if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))		return;	//帧头校验不成功则return
	if(*(data_buf+2)==0X01)														//分析帧类型
	{
		if(*(data_buf+4)==0X01)
		{
			mpu6050.Acc_CALIBRATE = 1;
		}
		else if(*(data_buf+4)==0X02)
			mpu6050.Gyro_CALIBRATE = 1;
		else if(*(data_buf+4)==0X03)
		{
			mpu6050.Acc_CALIBRATE = 1;		
			mpu6050.Gyro_CALIBRATE = 1;	
		}
		else if(*(data_buf+4)==0X04)
		{
			Mag_CALIBRATED = 1;		

		}
		else if (*(data_buf+4)==0X05)
		{
			appTosave=1;
		}
		else if((*(data_buf+4)>=0X021)&&(*(data_buf+4)<=0X26))
		{
		}
		else if(*(data_buf+4)==0X20)
		{
		}
	}
	if(*(data_buf+2)==0X22){
			NS=(enum PendulumMode)(*(data_buf+4));
		}
			if(*(data_buf+2)==0X21){
			NS=Stop;
		}
if(*(data_buf+2)==0X02)
	{
		if(*(data_buf+4)==0X01)
		{
			send_pid1 = 1;
			send_pid2 = 1;
		}
		if(*(data_buf+4)==0XA1)	
		{
			Para_ResetToFactorySetup();
		}
	}
		if(*(data_buf+2)==0X10)								//PID1
    {
        PitchP_arg.kp  = 0.01*( (vs16)(*(data_buf+4)<<8)|*(data_buf+5) );
        PitchP_arg.ki  = 0.01*( (vs16)(*(data_buf+6)<<8)|*(data_buf+7) );
        PitchP_arg.kd  = 0.01*( (vs16)(*(data_buf+8)<<8)|*(data_buf+9) );
        PitchS_arg.kp = 0.01*( (vs16)(*(data_buf+10)<<8)|*(data_buf+11) );
        PitchS_arg.ki = 0.01*( (vs16)(*(data_buf+12)<<8)|*(data_buf+13) );
        PitchS_arg.kd = 0.01*( (vs16)(*(data_buf+14)<<8)|*(data_buf+15) );
        RollP_arg.kp 	= 0.01*( (vs16)(*(data_buf+16)<<8)|*(data_buf+17) );
        RollP_arg.ki 	= 0.01*( (vs16)(*(data_buf+18)<<8)|*(data_buf+19) );
        RollP_arg.kd 	= 0.01*( (vs16)(*(data_buf+20)<<8)|*(data_buf+21) );
				if(send_check == 0)
				{
					send_check = 1;
					checkdata_to_send = *(data_buf+2);
					checksum_to_send = sum;
				}
    }
		 if(*(data_buf+2)==0X11)								//PID2
    {
        RollS_arg.kp  = 0.01*( (vs16)(*(data_buf+4)<<8)|*(data_buf+5) );
        RollS_arg.ki  = 0.01*( (vs16)(*(data_buf+6)<<8)|*(data_buf+7) );
        RollS_arg.kd  = 0.01*( (vs16)(*(data_buf+8)<<8)|*(data_buf+9) );
        Motor_arg.kp = 0.01*( (vs16)(*(data_buf+10)<<8)|*(data_buf+11) );
        Motor_arg.ki = 0.01*( (vs16)(*(data_buf+12)<<8)|*(data_buf+13) );
        Motor_arg.kd = 0.01*( (vs16)(*(data_buf+14)<<8)|*(data_buf+15) );
						if(send_check == 0)
				{
					send_check = 1;
					checkdata_to_send = *(data_buf+2);
					checksum_to_send = sum;
				}
    }
	
    	if(*(data_buf+2)==0X03)
	{

		ExpAngleFromUsart = ((vs16)(*(data_buf+8)<<8)|*(data_buf+9))/100.0f ;
		AngleWithGradiantFromUsart = ((vs16)(*(data_buf+10)<<8)|*(data_buf+11))/100.0f ;
		
	}
    if(*(data_buf+2)==0X12)								//PID3
    {	
       	if(send_check == 0)
				{
					send_check = 1;
					checkdata_to_send = *(data_buf+2);
					checksum_to_send = sum;
				}
    }
	if(*(data_buf+2)==0X13)								//PID4
	{
		   				if(send_check == 0)
				{
					send_check = 1;
					checkdata_to_send = *(data_buf+2);
					checksum_to_send = sum;
				}
	}
	if(*(data_buf+2)==0X14)								//PID5
	{
						if(send_check == 0)
				{
					send_check = 1;
					checkdata_to_send = *(data_buf+2);
					checksum_to_send = sum;
				}
	}
	if(*(data_buf+2)==0X15)								//PID6
	{
						if(send_check == 0)
				{
					send_check = 1;
					checkdata_to_send = *(data_buf+2);
					checksum_to_send = sum;
				}
	}
		
			if(*(data_buf+2)==0X03)
	{
		GPIO_ToggleBits(GPIOA,GPIO_Pin_5);
	}
}
void ANO_DT_Send_Check(u8 head, u8 check_sum)
{
		u8 sum = 0;
	u8 i;
	data_to_send[0]=0xAA;
	data_to_send[1]=0xAA;
	data_to_send[2]=0xEF;
	data_to_send[3]=2;
	data_to_send[4]=head;
	data_to_send[5]=check_sum;
	
	

	for(i=0;i<6;i++)
		sum += data_to_send[i];
	data_to_send[6]=sum;

	Usart2_Send(data_to_send, 7);
}
//发送PID
void ANO_DT_Send_PID(u8 group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d)
{
	u8 _cnt=0;
	vs16 _temp;
	u8 sum = 0;
	u8 i;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x10+group-1;
	data_to_send[_cnt++]=0;
	
	
	_temp = p1_p * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p1_i  * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p1_d  * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p2_p  * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p2_i  * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p2_d * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p3_p  * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p3_i  * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	_temp = p3_d * 100;
	data_to_send[_cnt++]=BYTE1(_temp);
	data_to_send[_cnt++]=BYTE0(_temp);
	
	data_to_send[3] = _cnt-4;
	
	
	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;

	Usart2_Send(data_to_send, _cnt);
}

void ANO_DT_Send_MotoPWM(u16 m_1,u16 m_2,u16 m_3,u16 m_4,u16 m_5,u16 m_6,u16 m_7,u16 m_8)
{
	u8 _cnt=0;
	u8 sum = 0 ;
	u8 i;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0xAA;
	data_to_send[_cnt++]=0x06;
	data_to_send[_cnt++]=0;
	
	data_to_send[_cnt++]=BYTE1(m_1);
	data_to_send[_cnt++]=BYTE0(m_1);
	data_to_send[_cnt++]=BYTE1(m_2);
	data_to_send[_cnt++]=BYTE0(m_2);
	data_to_send[_cnt++]=BYTE1(m_3);
	data_to_send[_cnt++]=BYTE0(m_3);
	data_to_send[_cnt++]=BYTE1(m_4);
	data_to_send[_cnt++]=BYTE0(m_4);
	data_to_send[_cnt++]=BYTE1(m_5);
	data_to_send[_cnt++]=BYTE0(m_5);
	data_to_send[_cnt++]=BYTE1(m_6);
	data_to_send[_cnt++]=BYTE0(m_6);
	data_to_send[_cnt++]=BYTE1(m_7);
	data_to_send[_cnt++]=BYTE0(m_7);
	data_to_send[_cnt++]=BYTE1(m_8);
	data_to_send[_cnt++]=BYTE0(m_8);
	
	data_to_send[3] = _cnt-4;

	for(i=0;i<_cnt;i++)
		sum += data_to_send[i];
	
	data_to_send[_cnt++]=sum;
	
	Usart2_Send(data_to_send, _cnt);
}

