#include "main.h"

int main(){
	All_Init();
	while(1){
		if (appTosave)											//主循环中判断是否要保存各种参数
		{
			appTosave=0;
			AppParamSave();										//将保存参数的函数放在main函数中
		}																		//因为擦写flash时，所有中断函数都不会执行
		Delay_ms(50);
	}
}


