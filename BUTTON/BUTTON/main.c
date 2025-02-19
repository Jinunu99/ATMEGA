/*
 * BUTTON.c
 *
 * Created: 2025-02-19 오후 3:06:48
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
// 변경 확인 차 쓴 주석
// DDRG 4번에 연결된 스위치로 모든 LED 켜기
/*
int main(void)
{
    DDRD = 0xff; // 출력으로 설정
	
	DDRG &= ~(1<<4); // PORTG의 4번핀을 입력설정 (01111)
	//PORTG |= (1<<4); // PORTG의 4번핀을 풀업저항 설정 (만약 회로로 풀업저항을 구성하면 해당 코드 필요없음)
	// (풀업은 항상 1이라서 4번핀 풀업저항 설정하면 10000이 됨)
	// 풀업 - 스위치 안누르면 1(5V)이고 스위치 누르면 0(0V)가 된다
    while (1)
    {
		if(PING & (1<<4)) // 4번핀에 연결된 스위치를 누르지 않으면 (PING - 10000)
		{
			PORTD = 0x00; // LED OFF
		}
		else // 스위치를 누르면 (PING - 00000)
		{
			PORTD = 0xff; // LED ON
		}
    }
}
*/

// 3개의 스위치로 LED 조작하기
int main(void)
{
	DDRD = 0xff;
	
	// ~(11100) -> 00011 (2, 3, 4번 핀을 입력으로 설정)
	DDRG &= ~((1 << 4) | (1 << 3) | (1 << 2));
	
	while(1)
	{
		// 풀업저항이기 때문에 스위치를 안누르면 PING - 11100
		if(!(PING & (1 << 4))) // 4번 스위치 누르면 (PING - 01100) & 10000
			PORTD = 0x01;
			
		if(!(PING & (1 << 3))) // 3번 스위치 누르면 (PING - 10100)
			PORTD = 0x02;
			
		if(!(PING & (1 << 2))) // 2번 스위치 누르면 (PING - 11000)
			PORTD = 0x04;
	}
}