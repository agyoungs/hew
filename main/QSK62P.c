#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"


/*GLOBE-LULZ*/
volatile unsigned long ticks;
volatile unsigned short adc_reg;


void main(void){
	int nyan = 0;
	lcd_fb_t fb0;
	cpu_init();
	gpio_init();
	lcd_init("SNYANYAN");
	uart_init();
	timer_init();
	adc_init();
	fb0.line1[5] = 0x41;
	fb0.line2[5] = 0x42;
	while(1){
		if(ticks%250000 < 20){
			lcd_write_fb(&fb0);
			/*
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
			*/
		}
		
	}
}


