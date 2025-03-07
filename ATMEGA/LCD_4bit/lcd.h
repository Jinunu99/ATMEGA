
#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#define LCD_DATA_DDR   DDRF  // 데이터 핀은 F에서 사용
#define LCD_DATA_PORT  PORTF
#define LCD_RS_DDR	   DDRE  //
#define LCD_RW_DDR     DDRE
#define LCD_E_DDR	   DDRE
#define LCD_RS_PORT    PORTE
#define LCD_RW_PORT    PORTE
#define LCD_E_PORT     PORTE
#define LCD_RS		   5
#define LCD_RW		   6
#define LCD_E		   7

// 명령어를 미리 정의함
#define COMMAND_DISPLAY_CLEAR	0x01
#define COMMAND_DISPLAY_ON		0x0C
#define COMMAND_DISPLAY_OFF		0x08
#define COMMAND_ENTRY_MODE		0x06
#define COMMAND_8BIT_MODE		0x38

#define COMMAND_4BIT_MODE		0x28 // 해당 코드는 4bit씩 출력할 것임


void LCD_Data(uint8_t data);		// 8bit에서 사용하는 코드
void LCD_Data4Bit(uint8_t data);	// 4bit
void LCD_WritePin();
void LCD_EnablePin();
void LCD_WriteCommand(uint8_t commandData);
void LCD_WriteData(uint8_t charData);
void LCD_GotoXY(uint8_t row, uint8_t col);
void LCD_WriteString(char *string);
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string);
void LCD_Init();


#endif /* LCD_H_ */