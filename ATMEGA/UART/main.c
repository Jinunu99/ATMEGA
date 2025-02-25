/*
 * UART.c
 *
 * Created: 2025-02-25 오후 2:00:47
 *  Author: jw
 */ 

#include "uart0.h"

// PE0 (RXD0), PE1(TXD0), PD2(RXD1), PD3(TXD1) - 해당 핀을 사용해서 UART 통신해야함
// ComPortMaster 앱을 다운받아서 시리얼통신 프로그램


int main(void)
{
	UART0_Init();
	
	DDRD = 0xff;  // LED 포트를 출력으로 설정
	PORTD = 0x00; // LED OFF 상태로 출발
	
	char data;
	
	
	while (1)
	{
		data = UART0_Receive();
		UART0_Transmit(data);
		
		if(data == 'a')
		{
			PORTD = 0xff;
		}
		else if(data == 'b')
		{
			PORTD = 0x00;
		}
		else if(data == 'c')
		{
			for(uint8_t i=0; i<8; i++)
			{
				PORTD |= (1 << i);
				_delay_ms(200);
			}
			PORTD = 0x00;
		}
	}
}
