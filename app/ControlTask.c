#include "main.h"

static void Task_2ms(void)
{

}

static void Task_5ms(void)
{

}

static void Task_10ms(void)
{

}

static void Task_20ms(void)
{
	
	
}

static void Task_50ms(void)
{
	
}

void ControlTask(void)
{
	static u32 MS_TIME=0;
	MS_TIME++;
	DataTransferTask(MS_TIME);
	if(MS_TIME%2==0)Task_2ms();
	if(MS_TIME%5==0)Task_5ms();
	if(MS_TIME%10==0)Task_10ms();
	if(MS_TIME%20==0)Task_20ms();
	if(MS_TIME%50==0)Task_50ms();
}
