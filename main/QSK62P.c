#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"


/*GLOBE-LULZ*/
volatile unsigned long ticks;
volatile unsigned short adc_reg;
struct lcd_fb fb0;
extern struct uart_buf rx_buf_s, tx_buf_s;


void main(void){
	int nyan = 0;
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


