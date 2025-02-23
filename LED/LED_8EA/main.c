/*
 * LED_8EA.c
 *
 * Created: 2025-02-18 오후 2:03:35
 * Author : USER
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// LED 8ea shift
/*
int main(void)
{
	DDRD = 0xff; // Port D를 출력으로 설정
    while (1)
    {
		for(uint8_t i=0; i<8; i++) // unsigned int인데 방이 8비트 단위이다
		{
			PORTD = (0x80 >> i); // 0x01 = 0b00000001
			// 0x01 << 1 => 0b00000010이 됨
			
			_delay_ms(100);
		}		
    }
}
*/

// LED 4개 좌우 양끝에서 안쪽으로 이동
/*
#define LED_DDR DDRD    // LED를 위한 포트 방향 레지스터
#define LED_PORT PORTD  // LED를 켜고 끄기 위한 포트 레지스터
int main()
{
	LED_DDR = 0xff;
	while(1)
	{
		for(uint8_t i=0; i<3; i++)
		{
			LED_PORT = ((0x80 >> i) | (0x01 << i));
			_delay_ms(500);
		}
		for(uint8_t i=0; i<3; i++)
		{
			LED_PORT = ((0x08 >> i) | (0x10 << i));
			_delay_ms(500);
		}
	}
}
*/
/*
int main()
{
	DDRD = 0xff;
	
	unsigned char L = 0x01;
	unsigned char R = 0x80;
	
	while(1)
	{
		PORTD = L | R;
		L <<= 1;
		if(L == 0)
		{
			L = 0x02;
		}
		R >>= 1;
		if(R == 0)
		{
			R = 0x40;
		}
		_delay_ms(300);
	}
	
}
*/

// 함수 및 포인터 이용

#include "led.h"

int main()
{
	ledInit();
	uint8_t ledData = 0x81; // 0b10000001

	while(1)
	{
		for(uint8_t i=0; i<8; i++)
		{
			ledShift(i, &ledData);
			GPIO_Output(ledData);
			_delay_ms(200);
		}
	}
}
