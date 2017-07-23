#ifndef _USART_H_
#define _USART_H_
void Usart1_Init(u32 br_num);
void Usart1_Send(unsigned char *DataToSend ,u8 data_num);
void Usart2_Init(u32 br_num);
void Usart2_Send(unsigned char *DataToSend ,u8 data_num);
void Usart2_Send_DMA(unsigned char *DataToSend ,u8 data_num);
#endif

