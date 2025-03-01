/*
 * FND_4.c
 *
 * Created: 2025-02-20 오후 2:08:46
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FND_SELECT_DDR   DDRB  // B번 포트에 0, 1, 2, 3번 핀에 꽂음
#define FND_SELECT_PORT  PORTB

#define FND_DATA_DDR     DDRC  // C번 포트에 0,1,2,3,4,5,6번 핀에 꽂음
#define FND_DATA_PORT    PORTC


void fndDisplay(uint16_t data)
{
	// static으로 선언했기 때문에 프로그램이 실행될 때만 한번 0으로 초기화 되고
	// fndDisplay 함수가 끝나도 어떤 값을 기다릴 꺼임
	static uint8_t position = 0; // digit를 선택하는 포지션 (4 FND니깐 0 ~ 3번째 자리를 선택하도록)
	uint8_t fndData[10] = // 0 ~ 9까지 출력하도록 배열에 저장
	{ 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67 };
	
	switch(position)
	{
		case 0: // 첫번째 자리의 FND를 표시하기 위해서 0번핀 LOW / 1, 2, 3번핀 HIGH
		FND_SELECT_PORT &= ~(1 << 0);	// digit 1번 LED ON
		FND_SELECT_PORT |= (1<<1) | (1<<2) | (1<<3); // digit 2, 3, 4번 LED OFF
		FND_DATA_PORT = fndData[data/1000]; // 천의 자리를 구하기 위해 1000으로 나눔
		break;
		
		case 1: // 두번째 자리의 FND를 표시하기 위해서 1번핀 LOW / 0, 2, 3번핀 HIGH
		FND_SELECT_PORT &= ~(1 << 1);	// digit 2번 LED ON
		FND_SELECT_PORT |= (1<<0) | (1<<2) | (1<<3); // digit 1, 3, 4번 LED OFF
		FND_DATA_PORT = fndData[data/100%10]; // 백의 자리 구하기
		break;
		
		case 2: // 세번째 자리의 FND를 표시하기 위해서 2번핀 LOW / 0, 1, 3번핀 HIGH
		FND_SELECT_PORT &= ~(1 << 2);	// digit 3번 LED ON
		FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<3); // digit 1, 2, 4번 LED OFF
		FND_DATA_PORT = fndData[data/10%10]; // 십의 자리 구하기
		break;
		
		case 3: // 네번째 자리의 FND를 표시하기 위해서 3번핀 LOW / 0, 1, 2번핀 HIGH
		FND_SELECT_PORT &= ~(1 << 3);	// digit 4번 LED ON
		FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<2); // digit 1, 2, 3번 LED OFF
		FND_DATA_PORT = fndData[data%10]; // 일의 자리 구하기
		break;
	}
	position++;				 // 다음 자릿수로 이동하기 위해 ++ 해줌
	position = position % 4; // 4자리 출력 후엔 다시 첫번째로 가라
}

int main(void)
{
	// 4 FND는 캐소드 방식이라 select핀에는 Low(0V)를 주고 data핀에는 High(5V)를 줘야 켜짐
	
	FND_SELECT_DDR = 0xff; // select 레지스터 출력으로 설정
	FND_DATA_DDR = 0xff;   // data 레지스터 출력으로 설정
		
	FND_SELECT_PORT = 0x00;
	
	uint16_t count = 0;
	uint32_t timeTick = 0;
	uint32_t prevTime = 0;

    while (1) 
    {
		fndDisplay(count); // 현재 count값을 출력
		if(timeTick - prevTime > 100) // 100ms가 지날 때마다 count값 1씩 증가
		{
			prevTime = timeTick;
			count++;
		}
				
		_delay_ms(1);	// 1ms 지연
		timeTick++;		// 약 1ms마다 timeTick 1씩 증가
    }
}

