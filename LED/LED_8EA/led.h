/*
 * led.h
 *
 * Created: 2025-02-18 오후 4:00:25
 *  Author: USER
 */ 


#ifndef LED_H_
#define LED_H_

#include <avr/io.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

void ledInit();
void GPIO_Output(uint8_t data);
void ledShift(uint8_t i, uint8_t *data);


#endif /* LED_H_ */