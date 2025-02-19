/*
 * led.c
 *
 * Created: 2025-02-18 오후 4:01:08
 *  Author: USER
 */ 
#include "led.h"


void ledInit()
{
	LED_DDR = 0xff;
}

void GPIO_Output(uint8_t data)
{
	LED_PORT = data;
}

void ledShift(uint8_t i, uint8_t *data)
{
	*data = (1 << i) | (1 << (7-i));
}