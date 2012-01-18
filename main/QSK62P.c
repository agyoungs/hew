#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

void main(void){
	long count = 0;
	int i = 0;
	int nyan = 0;
	MCUInit();
	lcd_init("SNYANYAN");
	InitUART();
	while(1){
		count = 100000;
		while(--count != 0){
			for(i = 0; i < 20; i++){
				_asm("nop");
			}
		}
		if(nyan == 0){
			lcd_puts(LCD_LINE1, "~NYANYAN");
			lcd_puts(LCD_LINE2, "NYANYAN~");
			nyan = 1;
		}
		else{
			lcd_puts(LCD_LINE1, "NYANYAN~");
			lcd_puts(LCD_LINE2, "~NYANYAN");
			nyan = 0;
		}
	}
}


