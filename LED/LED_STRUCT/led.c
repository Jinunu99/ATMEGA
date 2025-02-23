/*
 * led.c
 *
 * Created: 2025-02-19 오전 10:16:09
 *  Author: USER
 */ 
#include "led.h"

void ledInit(LED *led) // 습관적으로 초기화 함수를 만들자
{
	/*
	data sheet 보면 $12 - PORTD, $11 - DDRD, $10 - PIND 주소를 가짐
	PORT와 DDR의 초기값은 0000 0000임
	
	PORT 주소에서 -1을 하면 DDR로 이동할 수 있음
	*/
	// 포트에 해당되는 핀을 출력으로 설정
	// DDRx = DDRx | (1<<0); 와 동일 의미 (led.pin = 0이라 가정)
	// DDRx의 0000 0001 이 출력으로 설정 됨
	*(led->port -1) |= (1 << led->pin);
}

// led 출력핀 설정
void ledSet(LED *led)
{
	*(led->port -1) |= (1 << led->pin);
}

void ledOn(LED *led)
{
	*(led->port) |= (1 << led->pin);
}

void ledOff(LED *led)
{
	// 내가 원하는 위치에 0을 넣고 싶을 때 : & ~(1 << led->pin)
	// *(led->port) = *(led->port) & ~(1 << led->pin)
	// ~(1 << 0)이라 하면 ~(0000 0001) -> 1111 1110이 됨 그럼 원하는 위치에 0을 넣을 수 있게됨
	*(led->port) &= ~(1 << led->pin);
}