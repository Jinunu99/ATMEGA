/*
 * uart0.c
 *
 * Created: 02-25 (화) 오후 5:31:38
 *  Author: jw
 */ 

#include "uart0.h"


void UART0_Init()
{
	// datasheet를 보면 UBRR = 207이면 2배속 9600bps를 의미함
	UBRR0H = 0;
	UBRR0L = 207; // 2배속 9600bps 설정한 것임
	UCSR0A |= (1 << U2X0); // 2배속 speed를 사용할꺼다라는 설정
	
	// (1 << RXEM0) - 수신가능 , (1 << TXEN0) - 송신가능
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	// UCSR0C에는 비동기, 8비트, 패리티비트 없음, 스톱비트 1개를 설정한 것
	// UCSR0C |= (1 << UCSZ01) | (1 << USCZ00); -> 어짜피 초기값이 8it 사용이라 해당 코드 생략가능
}

void UART0_Transmit(char data)
{
	while(!(UCSR0A & (1 << UDRE0))); // 비어있는지? -> UDRE0는 송신버퍼가 비어있는지 확인하는 부분
	UDR0 = data; // UART에 대한 데이터 레지스터에 data를 넣어라
}

unsigned char UART0_Receive(void)
{
	while(!(UCSR0A & (1 << RXC0))); // 데이터 수신대기
	return UDR0;
}