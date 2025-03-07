#ifndef UART0_H_
#define UART0_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>


void UART0_Init(); // 레지스터 세팅 부분
void UART0_Transmit(char data); // 문자 하나 송신
unsigned char UART0_Receive(void);


#endif /* UART0_H_ */