/* TIMER_COUNTER_16PWM 코드
기능)
Fast PWM 모드, 64분주, non-inverting 모드 => 레지스터 설정해줘야 함
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1 << DDRB5); // 0010 0000 (OC1A를 출력으로 잡은 것)
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
	TCCR1C = 0; // 어짜피 TCCR1C를 사용안하기 때문에 해당 코드는 생략가능
	
	ICR1 = 2499; // TOP 값 (TOP값을 바꾸면 주파수가 변경됨)
	//OCR1A = 1250; // 약 PWM 50% 해준것 (OC1A를 출력으로 잡았으니 A로 입력을 해줌)
	
	while (1)
	{
		for(uint16_t i=0; i<2500; i++)
		{
			OCR1A = i;
			_delay_ms(2);
		}
	}
}
