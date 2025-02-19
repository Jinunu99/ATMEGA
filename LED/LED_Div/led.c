/*
 * led.c
 *
 * Created: 2025-02-19 오전 9:55:02
 *  Author: USER
 */ 
#include "led.h"

void ledInit()
{
	LED_DDR = 0xff; // 출력으로 설정
}

void GPIO_Output(uint8_t data)
{
	LED_PORT = data;
}

void ledLeftShift(uint8_t *data)
{
	// 오른쪽으로 8번 밀어서 clear 시키고 data가 가리키는 주소의 값을 왼쪽으로 한 번 shift
	*data = (*data >> 8) | (*data << 1);
	GPIO_Output(*data);
}

void ledRightShift(uint8_t *data)
{
	*data = (*data << 8) | (*data >> 1);
	GPIO_Output(*data);
}