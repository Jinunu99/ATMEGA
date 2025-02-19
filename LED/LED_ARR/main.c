/*
 * LED_ARR.c
 *
 * Created: 2025-02-19 오전 9:07:24
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t ledArr[]=
{
	0x00,
	0x80, // 10000000
	0xC0, // 11000000
	0xE0, // 11100000
	0xF0, // 11110000
	0xF8, // 11111000
	0xFC, // 11111100
	0xFE, // 11111110
	0xFF, // 11111111
	0x7F, // 01111111
	0x3F, // 00111111
	0x1F, // 00011111
	0x0F, // 00001111
	0x07, // 00000111
	0x03, // 00000011
	0x01  // 00000001
};

int main(void)
{
	DDRD = 0xff;
	while(1)
	{
		for(uint8_t i=0; i<16; i++)
		{
			// 11111111 00000000 인데 i만큼 오른쪽 shift
			PORTD = 0xff00 >> i;
			_delay_ms(400);
		}
	}
	
	/*
    DDRD = 0xff;
	
	// 배열의 갯수 세는 방법
	uint8_t arrSize = sizeof(ledArr)/sizeof(ledArr[0]);
	
    while (1) 
    {
		for(uint8_t i=0; i<arrSize; i++)
		{
			PORTD = ledArr[i];
			_delay_ms(200);
		}
    }
	*/
}

