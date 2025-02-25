/*
 * uart0.h
 *
 * Created: 02-25 (화) 오후 5:31:47
 *  Author: jw
 */ 


#ifndef UART0_H_
#define UART0_H_

#include "def.h"


void UART0_Init(); // 레지스터 세팅 부분
void UART0_Transmit(char data); // 문자 하나 송신
unsigned char UART0_Receive(void);



#endif /* UART0_H_ */