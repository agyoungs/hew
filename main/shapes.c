#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#define SQUARE_SIDE_DELAY 500000
#define QUARTER_TURN_DELAY 150000
#define SQUARE_IDLE_DELAY 800000
#define THREE_CIRCLES_DELAY 5600000
#define FE_LINE_DELAY 350000
#define FE_TURN_DELAY 1300000
#define FE_LEFT 200000
#define PWM_FW	1
#define PWM_RV	0
#define HALF_SPEED .5
#define Q_SPEED 	.25
#define INFLOOP 	1

void find_lines(void){
	long delay = SQUARE_IDLE_DELAY;
	right_pwm_state = PWM_FW;
	left_pwm_state = PWM_FW;
	both_throttle(HALF_SPEED);
	while(INFLOOP){
		if((ad2 > thresh)||(ad3 > thresh))
			break;
	}
	right_pwm_state = PWM_RV;
	left_pwm_state = PWM_RV;
	while(--delay);
	while(INFLOOP){
		if((ad2 > thresh)||(ad3 > thresh))
			break;
	}
	right_pwm_state = PWM_FW;
	left_pwm_state = PWM_FW;
	delay = SQUARE_IDLE_DELAY;
	while(--delay);
	while(INFLOOP){
		if((ad2 > thresh)||(ad3 > thresh))
			break;
	}
	min_throttle();
}