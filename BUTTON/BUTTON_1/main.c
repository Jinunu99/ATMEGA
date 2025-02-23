/*
 * BUTTON_1.c
 *
 * Created: 2025-02-20 오전 9:12:11
 * Author : USER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD = 0xff; // 출력으로 지정
	DDRG = 0x00; // 입력으로 지정
	
	uint8_t ledData = 0x01; // 0000 0001
	uint8_t buttonData;
	int flag = 0;
	
	PORTD = 0x00; // led 꺼진 상태로 초기화

    while (1) 
    {
		buttonData = PING;
		if((buttonData & (1 << 4)) == 0) // 4번 버튼을 누르면 (여기서 0은 버튼을 눌렀다는 의미)
		{
			PORTD = ledData; //현재 0x01
			ledData = (ledData >> 7) | (ledData << 1);
			_delay_ms(300);
		}
		if((buttonData & (1 << 3)) == 0) // 3번 버튼을 누르면
		{
			PORTD = ledData;
			ledData = (ledData >> 1) | (ledData << 7);
			_delay_ms(300);
		}
		if(flag == 0)
		{
			if((buttonData & (1 << 2)) == 0) // 2번 버튼을 누르면
				flag = 1;
			else
				flag = 0;
		}
		if(flag == 1) // 2번 버튼이 눌러지면 flag가 1로 바껴서 led가 3번 깜빡거림
		{
			for(uint8_t i=0; i<3; i++)
			{
				PORTD = 0xff; // led 전부 키겠다
				_delay_ms(500);
				PORTD = 0x00;
				_delay_ms(500);
			}
			flag = 0;
		}
    }
}

