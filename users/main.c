#include "main.h"

int main(){
	All_Init();
	while(1){
		if (appTosave)											//��ѭ�����ж��Ƿ�Ҫ������ֲ���
		{
			appTosave=0;
			AppParamSave();										//����������ĺ�������main������
		}																		//��Ϊ��дflashʱ�������жϺ���������ִ��
		Delay_ms(50);
	}
}


