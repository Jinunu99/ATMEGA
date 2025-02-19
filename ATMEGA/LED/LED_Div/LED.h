/*
 * LED.h
 *
 * Created: 2025-02-19 오전 9:54:45
 *  Author: USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#ifndef LED_H_
#define LED_H_

// LED 이동 함수로 구현
#define LED_DDR DDRD
#define LED_PORT PORTD

// 함수의 원형 선언
void ledInit();
void GPIO_Output(uint8_t data);
void ledLeftShift(uint8_t *data);
void ledRightShift(uint8_t *data);



#endif /* LED_H_ */