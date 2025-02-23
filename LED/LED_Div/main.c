/*
 * LED_Div.c
 *
 * Created: 2025-02-19 오전 9:32:06
 * Author : USER
 */ 
#include "led.h"

int main(void)
{
    ledInit();
	uint8_t ledData = 0x01; // 0000 0001
	
    while (1) 
    {
		for(uint8_t i=0; i<7; i++)
		{
			ledLeftShift(&ledData);
			_delay_ms(200);
		}
		for(uint8_t i=0; i<7; i++)
		{
			ledRightShift(&ledData);
			_delay_ms(200);
		}
    }
}