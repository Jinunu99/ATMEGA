/*
 * FND.c
 *
 * Created: 2025-02-20 오전 11:36:19
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint8_t FND_Number[] =
	{
		// 7세그먼트의 0 ~ 9까지 제어값을 배열에 저장
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
	};
	
	uint16_t count = 0;
	
	DDRA = 0xff; // 출력으로 설정
	
	while(1)
	{
		PORTA = FND_Number[count];
		count = (count + 1) % 10;
		_delay_ms(500);
	}
}
