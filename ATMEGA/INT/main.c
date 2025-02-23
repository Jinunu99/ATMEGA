/*
 * INT.c
 *
 * Created: 2025-02-20 오후 4:59:24
 * Author : USER
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint8_t test = 0; // 인터럽트에 사용되는 변수는 volatile로 선언

ISR(INT4_vect)
{
	PORTD ^= 0xff; // 꺼져있으면 켜지고 켜져있으면 꺼지게 함
}

int main(void)
{
	
	// SERG 레지스터의 I비트를 세팅하는 것은 글로벌 인터럽트를 세팅하는 것 (나는 이제 인터럽트를 사용하겠다고 열어준 것)
	sei(); //SERG 레지스터의 I비트를 셋 합니다.
	// cli(); //SERG 레지스터의 I비트를 클리어 합니다. (글로벌 인터럽트 불가하게 할때 사용)
	// SREG |=(1<<7); // I비트까지 밀어서 1로 셋 => sei(); 와 동일한 의미
	
	// EIMSK를 설정하는 부분인데 (INT0, INT1, INT7 중에 어떤 핀을 사용할꺼냐?)
	EIMSK |= (1<<INT4); // INT4번의 인터럽트를 허용 (단, 글로벌 인터럽트 허용상태로 세팅을 마쳤어야 함)
	
	// 어떤 형태여야 인터럽트를 실행 할꺼냐?
	//EICRB |= (1<<ISC41); // INT4번의 하강엣지 이용
	//EICRB |= (1<<ISC41) | (1<<ISC40); // INT4번의 상승엣지 이용
	EICRB |= (1<<ISC40); // INT4번의 상승엣지나 하강엣지 중 어떤것이든 이용 (00 00 00 10)
	
	
	DDRE &= ~(1<<4); // E포트의 4번핀을 입력으로 설정
	
	DDRD = 0xff;   // LED바 출력 설정
	
	while(1)
	{
		
	}
}