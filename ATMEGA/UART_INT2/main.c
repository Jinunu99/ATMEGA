/*
 * UART_INT2.c
 *
 * Created: 2025-02-25 오후 3:31:35
 * Author : USER
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "uart0.h"

// printf를 사용할때 쓰는 출력 스트림 함수
//FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);

// 수신된 데이터가 들어올때마다 인터럽트가 발생됨
ISR(USART0_RX_vect)
{
	UART0_ISR_Process();
}


int main(void)
{
    UART0_Init();
	// stdout = &OUTPUT; // printf를 사용할꺼면 써야되는 코드
	
    while (1) 
    {
		UART0_execute();
    }
}

