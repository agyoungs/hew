#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#define B0 0x01
#define B4 0x10
#define B3 0x03
#define ALL_ON 0xff

void gpio_init(void){
	p8 &= ~ALL_ON;
	pd8 = B0;
	p7 &= ~(B4|B3);
	pd7 = ~(B4|B3);
	pd10 &= ~B0;
	p3 &= ~ALL_ON;
	pd3 = ALL_OUTPUTS;
	IR_PORT |= IR_LED;
	
}