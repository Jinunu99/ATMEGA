#include "uart0.h"

uint8_t rxBuff[100];
uint8_t rxFlag;

// UART를 사용하기 위해 세팅해주는 함수
void UART0_Init()
{
	// 통신속도 세팅 : UBRR = 207 (9600bps와 2배 속도 사용)로 설정
	UBRR0H = 0;
	UBRR0L = 0xCF; // UBRR0L = 207과 동일
	
	// 2배속, 8비트, 패리티x, 스톱비트 1개 세팅해야 함
	UCSR0A |= (1 << U2X0);
	// UCSR0C = 0x06; // 초기값이 설정값과 같음 따라서 생략가능
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // 송, 수신 가능
	UCSR0B |= (1 << RXCIE0); // RX 인터럽트 enable
	// UCSR0B |= (1 << TXCIE0); // TX 인터럽트 enable
	
	sei();
}

uint8_t UART0_getFlag()
{
	return rxFlag;
}

void UART0_clearRxFlag()
{
	rxFlag = 0;
}

void UART0_setReadyRxFlag()
{
	rxFlag = 1;
}

uint8_t *UART0_readRxBuff()
{
	// 이때까지 수신된 데이터가 저장된 rxBuff 배열의 주소를 반환
	return rxBuff;
}

void UART0_Transmit(unsigned char data)
{
	// UDRE0는 송신버퍼가 비어있는지 확인하는것으로
	// 송신버퍼가 비어있으면 1, 아니면 0임
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char UART0_Receive()
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

// 출력 스트림을 안쓰고 문자열 출력하는 방법
void UART0_print(char *str)
{
	// 배열을 받아서 배열의 크기만큼 반복문을 돌려라
	for(int i=0; str[i]; i++)
	{
		// 이때까지 받은 문자열을 송신
		UART0_Transmit(str[i]);
	}
	UART0_Transmit('\n');
}

uint8_t UART0_avail() // 쓸 수 있냐 없냐
{
	if(!(UCSR0A & (1 << RXC0)))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

// 데이터가 수신되었을때 인터럽트가 발생하면 하게 될 동작
void UART0_ISR_Process()
{
	uint8_t rxData = UDR0; //UDR0에 저장된 데이터를 읽어와서
	static uint8_t rxHead = 0;
	if(rxData == '\n') // 개행문자가 들어오면
	{
		rxBuff[rxHead] = rxData;
		rxHead++;
		rxBuff[rxHead] = '\0'; // 문자열의 끝이라고 저장해줌
		rxHead = 0;
		UART0_setReadyRxFlag(); // 문자열이 모두 수신되었다고 flag세움
	}
	else
	{
		rxBuff[rxHead] = rxData;
		rxHead++;
	}
}

// main문에서 해당 함수가 while()문으로 계속 실행됨
void UART0_execute()
{
	// Flag의 상태를 가져오는데 (Flag가 1이면 개행을 만나 모든 문자열이 들어왔다는 것을 의미)
	if(UART0_getFlag())
	{
		UART0_clearRxFlag(); // Flag를 0으로 clear
		uint8_t *rxString = UART0_readRxBuff(); // 이때까지 수신된 데이터(배열)의 주소를 받아옴
		
		UART0_print(rxString);
		// printf(rxString); // printf를 사용하고 싶으면 출력 스트림을 사용해야함
	}
	_delay_ms(300);
}