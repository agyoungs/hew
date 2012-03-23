#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#define TICK_LEN 24000
#define TICKMR_CONFIG 0x00
#define TICKIC_CONFIG 0x07
#define MOTBMR_CONFIG 0x00
#define MOTBIC_CONFIG 0x05
#define MOTA_CONFIG 0x02
void timer_init(void){
   	/* turn off interrupts before modifying Interrupt Priority Level */
	DISABLE_IRQ	        
   	tb0mr = TICKMR_CONFIG;
    tb0ic = TICKIC_CONFIG;
	tb1mr = MOTBMR_CONFIG;
    tb1ic = MOTBIC_CONFIG;

	ta0mr = MOTA_CONFIG;
	ta0ic = MOTA_CONFIG;
	ta1mr = MOTA_CONFIG;
	ta1ic = MOTA_CONFIG;
	ENABLE_IRQ

	tb0 = TICK_LEN;
	tb0s = START;
	tb1 = PWM_FRAME_LEN;
	tb1s = START;
}