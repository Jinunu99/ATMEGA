/*
 * led.c
 *
 * Created: 2025-02-19 오전 9:55:02
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

void ledLeftShift(uint8_t *data)
{ // 0000 0000 | 0000 0010
	// 오른쪽으로 7번 밀어서 clear 시키고 0000 000ㅁ인 것을 왼쪽으로 한 번 shift
	// 결과 => 0000 00ㅁ0 (ㅁ은 0 or 1임)
	*data = (*data >> 7) | (*data << 1);
	GPIO_Output(*data);
}

void ledRightShift(uint8_t *data)
{ //
	*data = (*data << 7) | (*data >> 1);
	GPIO_Output(*data);
}