//ALL FUNCTIONS RELATED TO IR LINE DETECTION AND ADC USE GO HERE
//Michael Yenik 23-3-2012

#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#define ADCON2_RS0 0x00
#define ADCON1_RS0 0x29
#define ADCON0_RS0 0x18
#define START_SWEEPIN 1
#define ADIC_RS0 0x00
#define ADC_MAX 1024
#define ADC_MIN 0
#define CAL_ITERATIONS	5000
#define CAL_DELAY		1000
#define AVG_CONST 2


//Initializes ADC to repeat sweep mode 0 to read an0-an3//
void adc_init(void){
	adcon0 = ADCON0_RS0;
	adcon1 = ADCON1_RS0;
	adcon2 = ADCON2_RS0;
	DISABLE_IRQ
	adic = ADIC_RS0;
	ENABLE_IRQ
	adst = START_SWEEPIN;
}

//Calibrates with IR LED on
void calibrate_on(void){
	unsigned long i = CAL_ITERATIONS;
	unsigned long delay = CAL_DELAY;
	an_min_on = ADC_MAX;
	an_max_on = ADC_MIN;
	IR_LED_ON;
	while(i--){
		if(ad2 > an_max_on)
			an_max_on = ad2;
		if(ad3 > an_max_on)
			an_max_on = ad3;

		if(ad2 < an_min_on)
			an_min_on = ad2;
		if(ad3 < an_min_on)
			an_min_on = ad3;
		while(delay--){};
		delay = CAL_DELAY;
		LED1 ^= LED_OFF;
	}
	CLED_OFF;
	thresh = (an_max_on + an_min_on)/AVG_CONST;
}

//Calibrates with IR LED off
void calibrate_off(void){
	unsigned long i = CAL_ITERATIONS;
	unsigned long delay = CAL_DELAY;
	an_min_off = ADC_MAX;
	an_max_off = ADC_MIN;
	IR_LED_OFF;
	while(i--){
		if(ad2 > an_max_off)
			an_max_off = ad2;
		if(ad3 > an_max_off)
			an_max_off = ad3;

		if(ad2 < an_min_off)
			an_min_off = ad2;
		if(ad3 < an_min_off)
			an_min_off = ad3;
		
		while(delay--){};
		delay = CAL_DELAY;
		LED1 ^= LED_OFF;
	}
	IR_LED_ON;
	CLED_OFF;
	an_noise = (an_max_off + an_min_off)/AVG_CONST;
}			