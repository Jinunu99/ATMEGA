
#ifndef UART0_H_
#define UART0_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

void UART0_Init();
uint8_t UART0_getFlag();
void UART0_clearRxFlag();
void UART0_setReadyRxFlag();
uint8_t *UART0_readRxBuff(); // 함수 포인터는 함수에 대한 주소값을 나중에 넘겨줄꺼임
void UART0_Transmit(unsigned char data);
unsigned char UART0_Receive();
void UART0_print(char *str);
uint8_t UART0_avail();
void UART0_ISR_Process();
void UART0_execute();


#endif /* UART0_H_ */