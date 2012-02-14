#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#pragma inline(min_throttle)
#pragma inline(both_throttle)

void min_throttle(void){
	right_pwm_high = MIN_THROTTLE;
	left_pwm_high = MIN_THROTTLE;
}

void both_throttle(float throttle){
	unsigned int val = (unsigned int)((float)(PWM_FRAME_LEN)*throttle);
	right_pwm_high = val;
	left_pwm_high = val;
}