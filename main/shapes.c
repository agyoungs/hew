#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#define SQUARE_SIDE_DELAY 500000
#define QUARTER_TURN_DELAY 130000
#define SQUARE_IDLE_DELAY 400000
#define THREE_CIRCLES_DELAY 5000000

void circle(void){
	long delay = THREE_CIRCLES_DELAY;
	lcd_puts(LCD_LINE2, "CIRCLEZ!");
	right_pwm_high = PWM_FRAME_LEN/2;
	left_pwm_high = PWM_FRAME_LEN/4;
	right_pwm_state = 1;
	left_pwm_state = 1;
	while(S2 && --delay){
		_asm("nop");
	}
	min_throttle();
	lcd_puts(LCD_LINE2, "CHILLING");
}

void square(void){
	long delay;
	int i = 0;
	lcd_puts(LCD_LINE2, "SQUAHURR");
	right_pwm_state = 1;
	left_pwm_state = 1;
	for(i = 0; i < 7; i++){
		both_throttle(.5);
		delay = SQUARE_SIDE_DELAY;
		while(S3 && --delay){
			_asm("nop");
		}

		min_throttle();
		delay = SQUARE_IDLE_DELAY;
		while(S3 && --delay){
			_asm("nop");
		}

		left_pwm_state = 0;
		both_throttle(.5);
		delay = QUARTER_TURN_DELAY;
		while(S3 && --delay){
			_asm("nop");
		}
		left_pwm_state = 1;
		
		min_throttle();
		delay = SQUARE_IDLE_DELAY;
		while(S3 && --delay){
			_asm("nop");
		}
	}
	both_throttle(.5);
	delay = SQUARE_SIDE_DELAY;
		while(S3 && --delay){
			_asm("nop");
	}
	min_throttle();
	lcd_puts(LCD_LINE2, "CHILLING");
}