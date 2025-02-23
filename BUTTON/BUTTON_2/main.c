/*
 * BUTTON_2.c
 *
 * Created: 2025-02-20 오전 9:32:32
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR			DDRD
#define LED_PORT		PORTD
#define BUTTON_DDR		DDRG
#define BUTTON_PIN		PING
#define BUTTON_ON		4
#define BUTTON_OFF		3
#define BUTTON_Toggle	2

enum{PUSHED, RELEASED}; // eum은 0부터 시작해서 1씩 증가하도록 정의 {0, 1, 2...}
enum{NO_ACT, ACT_PUSH, ACT_RELEASE};

typedef struct
{
	volatile uint8_t *ddr;
	volatile uint8_t *pin;
	uint8_t btnPin;
	uint8_t prevState;
}BUTTON;

void buttonInit(BUTTON *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum)
{
	button->ddr = ddr;
	button->pin = pin;
	button->btnPin = pinNum;
	button->prevState = RELEASED; //초기화 상태로 아무것도 안누른 상태
	*button->ddr &= ~(1 << button->btnPin); // 버튼 핀이 누른 자리를 입력 상태로 만듬
}

uint8_t buttonGetState(BUTTON *button)
{
	uint8_t curState = *button->pin & (1 << button->btnPin); // 버튼의 상태를 읽어옴 (PING & 10000) 11100 -> 01100
	
	if((curState == PUSHED) && (button->prevState == RELEASED)) // 버튼이 안눌러진 상태에서 처음으로 누르면
	{
		_delay_ms(50); // 디바운스 코드
		button->prevState = PUSHED; // 버튼을 눌렀으니 누른 상태로 변환
		return ACT_PUSH; // 버튼을 눌렀다고 반환
	}
	else if((curState != PUSHED) && (button->prevState == PUSHED)) // 버튼이 눌러진 상태에서 손을 떼면
	{
		_delay_ms(50);
		button->prevState = RELEASED;
		return ACT_RELEASE;
	}
}

int main(void)
{
    LED_DDR = 0xff;
	
	BUTTON btnOn;
	BUTTON btnOff;
	BUTTON btnToggle;
	
	buttonInit(&btnOn, &BUTTON_DDR, &BUTTON_PIN, BUTTON_ON);
	buttonInit(&btnOff, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);
	buttonInit(&btnToggle, &BUTTON_DDR, &BUTTON_PIN, BUTTON_Toggle);
	
    while (1) 
    {
		if(buttonGetState(&btnOn) == ACT_RELEASE)
		{
			LED_PORT = 0xff;
		}
		if(buttonGetState(&btnOff) == ACT_RELEASE)
		{
			LED_PORT = 0x00;
		}
		if(buttonGetState(&btnToggle) == ACT_RELEASE)
		{
			LED_PORT ^= 0xff;
		}
    }
}

