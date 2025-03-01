#include "uart0.h"

void UART0_Init()
{
	// 통신속도 세팅 : UBRR = 207 (9600bps와 2배 속도 사용)로 설정
	UBRR0H = 0;
	UBRR0L = 0xCF; // UBRR0L = 207과 동일
	
	// 2배속, 8비트, 패리티x, 스톱비트 1개 세팅해야 함
	UCSR0A |= (1 << U2X0);
	// UCSR0C = 0x06; // 초기값이 설정값과 같음 따라서 생략가능
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // 송, 수신 가능
	UCSR0B |= (1 << RXCIE0); // RX 인터럽트 enable => 수신될 때마다 인터럽트 걸림
	// UCSR0B |= (1 << TXCIE0); // TX 인터럽트 enable
}

void UART0_Transmit(char data)
{
	// UDRE0는 송신버퍼가 비어있는지 확인하는것으로
	// 송신버퍼가 비어있으면 1, 아니면 0임
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char UART0_Receive(void)
{
	// RXC0는 수신버퍼에 읽지 않은 데이터가 있으면 1로 세팅되어있음
	// RXC0 자리에 1로 되어있으면 아직 수신완료가 아닌것임
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}