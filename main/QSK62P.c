#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"
#include <string.h>


typedef unsigned char uint_8;


/*GLOBE-LULZ*/
volatile unsigned long ticks;
volatile unsigned short adc_reg;
volatile struct adc_t adc_s;
struct lcd_fb fb0, fb1;
struct uart_buf rx_buf_s, tx_buf_s;
struct lcd_fb* current_fb;

void main(void){
	uint_8 state = 0;
	uint_8 past_state = 0;
	long delay = 200000;
	cpu_init();
	gpio_init();
	lcd_init();
	uart_init();
	timer_init();
	adc_init();
	current_fb = (struct lcd_fb*)(fb_init());
	while(1){
		if(!p8_3){
			state = 1;
		}
		if(!p8_1){
			state = 2;
		}
		if(!p8_2){
			state = 3;
		}
		if(p8_1 && p8_2 && p8_3){
			state = 0;
		}
		if(!(state == past_state)){
			switch(state){
				case 0:
					off_all();
					break;
				case 1:
					while(--delay);
					delay = 200000;
					forward_right();
					forward_left();
					while(--delay);
					delay = 200000;
					off_all();
					break;
				case 2:
					p8 |= 0x01;
					p7 |= 0x14;
					p7 &= ~0x10;
					break;
				case 3:
					p8 |= 0x01;
					p7 |= 0x14;
					p7 &= ~0x04;
					break;
				default:
					break;
			}
			past_state = state;
		}
			
	}
}