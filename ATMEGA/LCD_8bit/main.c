/* LCD_8bit.c

*/ 
#include "lcd.h"
#include <stdio.h>

int main(void)
{
    LCD_Init();
	//LCD_GotoXY(0, 0);
	//LCD_WriteString("Hello LCD");
	//LCD_GotoXY(1, 0);
	//LCD_WriteString("Hello AVR");
	
	char buff[30];
	uint8_t count = 0;
    while (1) 
    {
		/*
		LCD_GotoXY(0, 0);
		LCD_WriteCommand(0x01); // 화면 clear
		LCD_WriteString("HI HI");
		_delay_ms(1000);
		
		LCD_GotoXY(0, 0);
		LCD_WriteCommand(0x01);
		LCD_WriteString("Hello AVR");
		_delay_ms(1000);
		*/
		
		
		// 문자열을 버퍼에 담아 출력하는 방식
		sprintf(buff, "count : %3d", count++); // 문자열을 buff에 담아서 출력함
		LCD_WriteStringXY(1, 0, buff);
		_delay_ms(200);
    }
}

