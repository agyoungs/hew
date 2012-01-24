#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"
#include <string.h>

/*GLOBE-LULZ*/
volatile unsigned long ticks;
volatile unsigned short adc_reg;
struct lcd_fb fb0, fb1;
struct uart_buf rx_buf_s, tx_buf_s;
struct lcd_fb* current_fb;

void main(void){
	int nyan = 0;
	char adc_val[4] = {0,0,0,0};
	cpu_init();
	gpio_init();
	lcd_init("SNYANYAN");
	uart_init();
	timer_init();
	adc_init();
	current_fb = (struct lcd_fb*)(fb_init());
	while(1){
		if((ticks%50000) < 20){
			uart_puts("Stuff: ");
			itoa(adc_reg, adc_val);
			uart_putsn(adc_val, 4);
			uart_putc_direct('\n');
			adst = 1;
		}
	}
}