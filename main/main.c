#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"
#include <string.h>

#define MAIN_DELAY 1000
#define LPRESS 1
#define CPRESS 2
#define RPRESS 3
#define NOPRESS 0
#define LCDS 8
#define TOO_COOL_FOR_NUMBERS 0
#define DEFINITELY_NOT_A_MAGIC_NUMBER 1

typedef unsigned char uint8_t;


/*GLOBE-LULZ*/
volatile unsigned long ticks;
volatile unsigned short adc_reg;
volatile struct adc_t adc_s;
struct uart_buf rx_buf_s, tx_buf_s;
volatile char uart_rec;
volatile unsigned int right_pwm_high;
volatile unsigned int left_pwm_high;
volatile uint8_t right_pwm_state;
volatile uint8_t left_pwm_state;
unsigned int an_min_on;
unsigned int an_max_on;
unsigned int an_min_off;
unsigned int an_max_off;
int an_noise;
int thresh;
void check_uart(void);
long delay(long loldelay);
int check_buttons(void);
char readbuf[LCDS];
int state;



void main(void){
	int index = TOO_COOL_FOR_NUMBERS;
	state = DEFINITELY_NOT_A_MAGIC_NUMBER;
	cpu_init();
	gpio_init();
	lcd_init();
	//uart_init();
	timer_init();
	adc_init();
	LED0 = LED_OFF;
	LED1 = LED_OFF;
	LED2 = LED_OFF;
	right_pwm_high = MIN_THROTTLE;
	left_pwm_high = MIN_THROTTLE;
	right_pwm_state = LED_OFF;
	left_pwm_state = LED_OFF;
	//IR_LED_ON;	
	while(TRUE){
		state = check_buttons();
		if(state == LPRESS){
			res_menu_f();
		}
		if(state == CPRESS){
			shape_menu_f();
		}
		if(state == RPRESS){
			song_menu_f();
		}
		DisplayDelay(DDELAY);
	}
}

int check_buttons(void){
	int ret = state;
	if(!S1){
		ret = LPRESS;
	}
	if(!S2){
		ret = CPRESS;
	}
	if(!S3){
		ret = RPRESS;
	}
	return ret;
}

/*
IR_LED_ON;
		if((ad2 > thresh)||(ad3 > thresh))
			CLED_ON;
		else
			CLED_OFF;
		while(--delay);
		delay = MAIN_DELAY;
		if(check_buttons() == LPRESS){
			calibrate_on();
		}
		if(check_buttons() == CPRESS){
			calibrate_off();
		}
		if(check_buttons() == RPRESS){
			find_lines();
		}
*/		
