#include "lcd.h"

void LCD_Data(uint8_t data)		// 8bit mode
{	// 어떤 data든 LCD에 보낼 것임
	// 데이터 핀에 8bit data를 출력
	LCD_DATA_PORT = data;
}

void LCD_Data4Bit(uint8_t data) // 4bit mode
{
	// LCD_DATA_PORT에선 상위비트 4개를 0으로 만들어서 data의 상위 4비트를 보낼것임
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | (data & 0xf0); // 상위 4bit 추출
	LCD_EnablePin();	// LCD 동작 신호 전송 (트리거를 때려줘야 실제로 실행됨)
	
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | ((data & 0x0f) << 4); // 하위 4bit 추출해서 상위 4bit로 밀어줌
	LCD_EnablePin();
}

void LCD_WritePin()
{	// write하기 위해서는 0으로 세팅해야함
	// RW핀을 low로 설정해서 쓰기모드 진입
	LCD_RW_PORT &= ~(1 << LCD_RW);
}

void LCD_EnablePin() // 동작에 대한 트리거
{	// active high에서 low로 갈때
	LCD_E_PORT &= ~(1 << LCD_E); // 일단 로우로 설정한 것
	LCD_E_PORT |= (1 << LCD_E);  // E핀 액티브 high (실제 동작은 여기임)
	LCD_E_PORT &= ~(1 << LCD_E); // 다시 low로 내림
	_delay_us(1600);	// 시간이 모자라면 동작 안함 (1600us 이상)
}

// 명령어 모드
void LCD_WriteCommand(uint8_t commandData)
{	// RS핀에 0을 쓰면 명령어 레지스터, 1을 쓰면 데이터 레지스터를 핸들링함
	LCD_RS_PORT &= ~(1 << LCD_RS);  // RS핀을 low로 설정해서 명령어 모드로 진입
	LCD_WritePin();					// 데이터 쓰기 모드로 진입
	LCD_Data4Bit(commandData);		// 명령어를 데이터핀에 출력
}

// write 모드
void LCD_WriteData(uint8_t charData)
{
	LCD_RS_PORT |= (1 << LCD_RS);	// RS핀을 high로 설정해서 데이터 모드로 진입
	LCD_WritePin();
	LCD_Data4Bit(charData);			// 해당 함수 안에는 LCD_EnablePin()을 포함하고 있음
}

void LCD_GotoXY(uint8_t row, uint8_t col)
{
	col %= 16; // col이 16개 있기 때문에 col을 0~15로 제한
	row %= 2;  // row는 2개 있기 때문에 row를 0~1로 제한
	uint8_t address = (0x40 * row) + col; // 주소 계산 (2-Line Display에서 값을 가져오는 방식)
	uint8_t command = 0x80 + address;     // 주소 설정 (DD-RAM 주소 설정 방법)
	LCD_WriteCommand(command); // 어디에 쓸지 커서가 설정됨
}

void LCD_WriteString(char *string)
{
	for(uint8_t i=0; string[i]; i++)
	{
		LCD_WriteData(string[i]);
	}
}

// 커서 위치 잡은 곳에서 쓰라는 함수
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string)
{
	LCD_GotoXY(row, col);	 // 커서 위치 잡음
	LCD_WriteString(string); // 씀
}

void LCD_Init()
{
	// 출력으로 잡겠다
	LCD_DATA_DDR = 0xff;
	LCD_RS_DDR |= (1 << LCD_RS);
	LCD_RW_DDR |= (1 << LCD_RW);
	LCD_E_DDR |= (1 << LCD_E);
	
	// 8bit 인터페이스에서 동작하라는 대로 해야함 (datasheet)
	_delay_ms(20);
	LCD_WriteCommand(0x03);
	_delay_ms(5);
	LCD_WriteCommand(0x03);
	_delay_ms(5);
	LCD_WriteCommand(0x03);
	LCD_WriteCommand(0x02);
	
	LCD_WriteCommand(COMMAND_4BIT_MODE); // 0x28
	
	LCD_WriteCommand(COMMAND_DISPLAY_OFF);
	LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
	LCD_WriteCommand(COMMAND_DISPLAY_ON); // datasheet엔 on을 빼먹어서 켜줘야함
	LCD_WriteCommand(COMMAND_ENTRY_MODE);
}