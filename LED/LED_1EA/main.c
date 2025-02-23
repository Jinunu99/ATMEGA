/*
 * LED_1EA.c
 *
 * Created: 2025-02-18 오전 11:20:24
 * Author : USER
 */ 
// build - compile & 파일 생성
// tool -> device programming
#define F_CPU 16000000UL // 16MHz, cpu가 뛰는 속도를 정의 
#include <avr/io.h>
#include <util/delay.h> // delay.h - 어떤 일을 하다가 지연시키고 싶을 때 헤더를 부름

int main(void)
{
	DDRD = 0xFF; // D Port 전체를 출력으로 잡겠다, 0b11111111
	
    while (1) // 실제 동작은 여기서 시켜야 함 
    {
		PORTD = 0xff;   // 0b11111111 (출력이 나감)
		_delay_ms(500); // 0.5초 동안 켜져 있게 함
		PORTD = 0x00;   // 0b00000000 (출력을 안내보냄), LED 꺼라
		_delay_ms(500);
    }
}

