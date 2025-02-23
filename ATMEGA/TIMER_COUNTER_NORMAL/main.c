/*
 * TIMER_COUNTER_NORMAL.c
 *
 * Created: 02-22 (토) 오후 8:38:51
 * Author : jw
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
	DDRG |= (1 << 0); // PORTG0번을 출력으로 설정 (여기에 주파수 생성)
	PORTG &= ~(1 << 0); // LOW로 출발
	
	// 레지스터 세팅
	// (1 << CS02) | (1 << CS00) - 128 분주비로 설정하겠다는 의미
	TCCR0 |= (1 << CS02) | (1 << CS00); // TCCR0 = 0x05와 같은 의미
	
	TCNT0 = 6; // 6부터 카운트 시켜주기 위해
	
    while (1)
    {
		while((TIFR & 0x01) == 0) // normal 모드에서는 오버플로우 되었을때 TOV0 flag가 1이된다
		
		PORTG = ~PORTG; // 토글
		TCNT0 = 6;      // count의 시작값 초기화
		TIFR = 0x01;    // clear (해당 flag에 1을 써주면 clear됨)
		
	}
}

