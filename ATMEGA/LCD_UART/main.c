/* LCD_UART.c

*/
#include "lcd.h"
#include "uart0.h"

// 출력 스트림 설정
// NULL까지 받은 문자열을 UART0_Transmit를 통해서 출력을 내보내겠다는 의미
FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);

char rxBuff[16] = {0}; // 우리가 만든 수신 버퍼
uint8_t rxFlag = 0;		// 수신이 완료되면 flag 설정하기 위함

ISR(USART0_RX_vect) // 인터럽트가 걸릴때마다 호출되는 함수임
{
	static uint8_t rxHead = 0; // 수신된 데이터의 인덱스
	uint8_t rxData = UDR0;     // 수신된 데이터!
	
	if(rxData == '\n' || rxData == '\r') // 수신된 마지막 데이터가 개행이나 라인피드이면
	{
		rxBuff[rxHead] = '\0'; // 문자열의 마지막에 NULL 추가
		rxHead = 0;			   // 인덱스 초기화
		rxFlag = 1;			   // 문자열을 전부 받았다는 flag를 설정
	}
	else // 개행이나 라인피드가 아니면 계속 할거야
	{
		rxBuff[rxHead] = rxData;  // 이번에 들어온 문자를 배열에 저장
		rxHead++;				  // 다음 문자를 위해 인덱스를 1 증가
	}
}


int main(void)
{
	LCD_Init();
	UART0_Init();     // UART 초기화
	uint8_t rxData;   // 수신된 데이터
	stdout = &OUTPUT; // 출력 스트림을 지정
	
	sei(); // 글로벌 인터럽트 허용
	
	while (1)
	{
		if(rxFlag == 1)		// rxFlag가 1이 되면 문자열이 다 들어왔다는 의미
		{
			rxFlag = 0;     // 문자열 flag 초기화
			LCD_WriteCommand(0x01);
			LCD_WriteStringXY(0, 0, rxBuff);
			_delay_ms(200);
			printf(rxBuff); // 수신된 문자열 출력
			// 출력 스트림에 설정한 대로 출력됨
		}
	}
}

