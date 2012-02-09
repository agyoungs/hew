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
volatile int mot_wait;
int mot_pticks;
volatile char uart_rec;

void check_uart(void);

void main(void){
	uint_8 state = 0;
	uint_8 past_state = 0;
	long delay = 2000000;
	char lulzbuf[] = {0,0};
	cpu_init();
	gpio_init();
	lcd_init();
	uart_init();
	timer_init();
	adc_init();
	current_fb = (struct lcd_fb*)(fb_init());
	while(1){
		check_uart();//check_buttons();
	}
}

void check_uart(void){
	if(uart_rec == 'w'){
		forward_left();
		forward_right();
	}
	if(uart_rec == 's'){
		reverse_left();
		reverse_right();
	}
	if(uart_rec == 'a'){
		forward_right();
		reverse_left();
	}
	if(uart_rec == 'd'){
		reverse_right();
		forward_left();
	}
	if(uart_rec == 'c'){
		off_all();
	}
}
/*
uint8_t check_buttons(void){
	uint8_t ret;
	if(!p8_3){
		ret = 1;
	}
	if(!p8_1){
		ret = 2;
	}
	if(!p8_2){
		ret = 3;
	}
	if(p8_1 && p8_2 && p8_3){
		ret = 0;
	}
}

int check_state(uint8_t st, uint8_t pst){
	switch(st){
		case 0:
			off_all();
			break;
		case 1:
			while(--delay);
			delay = 2000000;
			forward_right();
			forward_left();
			while(--delay);
			delay = 2000000;
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
	return 0;
}*/		