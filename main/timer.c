#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

void timer_init(void){
   	/* turn off interrupts before modifying Interrupt Priority Level */
	DISABLE_IRQ	        
   	tb0mr = 0x00;
    tb0ic = 0x07;
	tb1mr = 0x00;
    tb1ic = 0x05;

	ta0mr = 0x02;
	ta0ic = 0x02;
	ta1mr = 0x02;
	ta1ic = 0x02;
	ENABLE_IRQ

	tb0 = 24000;
	tb0s = 1;
	tb1 = PWM_FRAME_LEN;
	tb1s = 1;
}