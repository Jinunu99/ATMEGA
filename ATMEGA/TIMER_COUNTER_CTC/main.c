/*
 * TIMER_COUNTER_CTC.c
 *
 * Created: 02-22 (토) 오후 8:05:14
 * Author : jw
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1 << 4); // OC0번 핀 => PB4 (출력으로 설정)
	
	// 레지스터 세팅 (TCCT0 레지스터를 세팅해줘야 함)
	// (1 << WGM01) - CTC 모드로 설정
	// (1 << COM00) - compare match가 발생하면 OC0핀 토글 시키기 위해
	// (1 << CS02) - 분주비를 설정하기 위해 (prescale factor를 64로 설정하기 위함)
	TCCR0 |= (1<<COM00) | (1<<WGM01) | (1<<CS02); //TCCR0 = 0x1C; 와 동일 세팅
	
	OCR0 = 124; // CTC모드에선 count max값을 지정해줌 (그러면 TCNT0는 0~124까지 count함)
	
	
	while (1)
	{
		// 인터럽트가 걸리면 TIFR의 0000 0010이 됨
		// 해당자리는 TCNT0 = OCR0가 되면 비교일치가 발생하여 OCF0 flag가 1로 바뀜
		// compare match가 되어 OCF0 flag가 1인지 확인하기 위해 TIFR & 0x02를 통해 확인
		while((TIFR & 0x02) == 0) // 인터럽트가 걸릴때까지 계속 무한 반복
		
		TIFR = 0x02; // OCF0를 소프트웨어적으로 초기화시킴 (일반적인 메모리 쓰기와 다름)
		OCR0 = 124;
	}
}

