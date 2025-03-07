/* LCD_4bit.c 코드

*/
#include "lcd.h"
#include <avr/io.h>


int main(void)
{
	LCD_Init();
	LCD_GotoXY(0, 0);
	LCD_WriteString("Hello LCD PR");
	LCD_GotoXY(1, 0);
	LCD_WriteString("Hello AVR");
	
	while (1)
	{
		
	}
}

