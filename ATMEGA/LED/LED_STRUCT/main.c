/*
 * LED_STRUCT.c
 *
 * Created: 2025-02-19 오전 10:14:40
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

int main(void)
{
    LED led;
	led.port = &PORTD; // PORTD의 주소값을 구조체에 있는 포인터 멤버에 대입
	led.pin = 0;
	ledInit(&led);
	
    while (1)
    {
		for(uint8_t i=0; i<8; i++)
		{
			led.pin = i;
			ledSet(&led);
			ledOn(&led);
			_delay_ms(300);
			ledOff(&led);
			_delay_ms(300);
		}
    }
}

