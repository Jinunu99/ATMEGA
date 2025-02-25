/*
4번 버튼 누르면 led 왼쪽으로 한칸이동
3번 버튼 누르면 오른쪽으로 한칸이동
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD = 0xff; // D 레지스터를 출력으로 지정
	DDRG = 0x00; // G 레지스터를 입력으로 지정
	
	uint8_t ledData = 0x01; // 0000 0001
	uint8_t buttonData;
	int flag = 0;
	
	PORTD = 0x00; // led 꺼진 상태로 초기화

    while (1) 
    {
		buttonData = PING;
		if((buttonData & (1 << 4)) == 0) // 4번 버튼을 누르면 (여기서 0은 버튼을 눌렀다는 의미)
		{
			ledData = (ledData >> 7) | (ledData << 1);
			PORTD = ledData;
			_delay_ms(300); // 채터링 현상을 완화하기 위해 지연을 통해 디바운스 구현
		}
		if((buttonData & (1 << 3)) == 0) // 3번 버튼을 누르면
		{
			ledData = (ledData >> 1) | (ledData << 7);
			PORTD = ledData;
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

