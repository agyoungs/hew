#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

void gpio_init(void){
	p8 &= ~0x01;
	pd8 |= 0x01;
	p7 &= ~0x10;
	pd7 |= 0x10;
	pd10 &= ~0x01;
}

struct lcd_fb* fb_init(void){
	int i;
	fb0.next_fb = &fb1;
	fb1.next_fb = &fb0;
	write_to_fb("INITNYANFB  ZERO",&fb0);
	write_to_fb("INITNYANFB   ONE",&fb1);
	return &fb0;
}

void timer_init(void){
   	/* turn off interrupts before modifying Interrupt Priority Level */
	DISABLE_IRQ	        
   	tb0mr = 0x00;
    tb0ic = 0x03;
	//ta0
	ENABLE_IRQ
	tb0 = 240;
   	tb0s = 1;
}

void adc_init(void){
	/* AN0 input, one shot mode, soft trigger, fAD/2 */
	adcon0 = 0x80;
	adcon1 = 0x28;
	adcon2 = 0x01;
	_asm ("fclr i");
	/* Enable the ADC interrupt */
	adic = 0x01;
	/* globally enable interrupts */
    _asm ("fset i");
 	/* Start a conversion here */
    adst = 1;
}

void cpu_init(void){
	unsigned int count = 40000;
	/* configure clock for divide by 1 mode */
	prc0 =1;					/* enable access to clock registers */
	cm1 = 0x20;					/* set CM16,CM17 divide ratio to 1, 
									main clock on in high drive no PLL*/
	cm06 = 0;					/* set divide ratio to 1 */
    /* configure and switch main clock to PLL at 24MHz - uncomment this section
		out if PLL operation is desired								*/
	prc1 = 1;					/* allow writing to processor mode register */
	pm20 = 1;					/* set SFR access to 2 wait which is required for
   									operation greater than 16 MHz */
	prc1 = 0;					/* protect processor mode register */
	plc0= 0x92;					// enable PLL (2X) and turn on
	while(count > 0) count--;   /* wait for PLL to stabilize (20mS maximum, 240,000 cycles @12Mhz)
                                   this decrement with no optimization is 12 cycles each */
    cm11 = 1;                   /* switch to PLL */
    prc0 = 0;   				/* protect clock control register */
	prc1 = 1;
	pm10 = 1;		// enable data flash area
	prc1 = 0;
}