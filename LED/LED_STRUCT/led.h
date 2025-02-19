/*
 * led.h
 *
 * Created: 2025-02-19 오전 10:16:00
 *  Author: USER
 */ 


#ifndef LED_H_
#define LED_H_

#include <stdint.h>

typedef struct  
{
	// volatile - 메모리 쪽은 컴파일 할 때 최적화 하지말고 정확하게 행하고 넘어가라는 의미
	// 메모리 쪽에 공간확보할 때 volatile 타입을 붙힘
	volatile uint8_t *port; // LED가 연결될 포트 (port의 주소를 가리키고 있는 포인터)
	uint8_t pin;			// LED가 연결될 핀 번호
}LED;

void ledInit(LED *led); // 내가 만든 데이터형의 포인터를 넘겨줌
void ledSet(LED *led);
void ledOn(LED *led);
void ledOff(LED *led);

#endif /* LED_H_ */