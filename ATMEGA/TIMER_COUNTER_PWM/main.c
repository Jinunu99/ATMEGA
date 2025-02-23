/*
 * TIMER_COUNTER_PWM.c
 *
 * Created: 02-22 (토) 오후 10:09:20
 * Author : jw
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << DDRB4); // OC0을 사용할꺼라 PB4핀을 사용해야함
	
	// 레지스터 초기화
	TCCR0 |= (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS02) | (1 << CS01);
	// OCR0 = 127; // PWM 출력을 50%를 예상하고 세팅함
	
    while (1)
    {
		for(uint8_t i=0; i<256; i++)
		{
			OCR0 = i;
			_delay_ms(10);
		}
    }
}

