#include "sfr62p.h"
#include <ctype.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include "LCD.h"


/***********************************************************************/
/*                                                                     */
/*  DATE        :Mon, Mar 23, 2009                                     */
/*																	   */
/*  DESCRIPTION :      All the defines for the projects are kept here. */
/* 	  																   */
/*																	   */
/*  CPU GROUP   :62P                                                   */
/*                                                                     */
/*  Copyright (c) 2009 by BNS Solutions, Inc.						   */
/*  All rights reserved.											   */
/*                                                                     */
/***********************************************************************/


// These two defines are used to help keep track of which version of code we are running.
//  Major is incremented when a new feature or function is added.
//  Minor is incremented when there is a bug fix or attempted fix.

#define MAJOR_REV		1
#define MINOR_REV		1

// Shorthand stuff... 

#define BIT0			0x01
#define BIT1			0x02
#define BIT2			0x04
#define BIT3			0x08
#define BIT4			0x10
#define BIT5			0x20
#define BIT6			0x40
#define BIT7			0x80

#define ulong   unsigned long
#define uint	unsigned int
#define uchar 	unsigned char

#define TRUE	1
#define FALSE	0

#define PASSED  TRUE
#define FAILED  FALSE

#define YES		TRUE
#define NO		FALSE

#define ON		TRUE
#define OFF		FALSE

#define HIGH 1
#define LOW 0

#define ENABLE_IRQ   	{_asm(" FSET I");}
#define DISABLE_IRQ		{_asm(" FCLR I");}

// Defines used to configure the Timer 
// This stuff sets up the timer to run a 1ms tick.


//#define f1_CLK_SPEED	(6000000L)
#define f1_CLK_SPEED	(24000000L)
#define MS_PER_TICK		1

#define TWO_FIFTY_MS			(250)		// ticks in 250 MS
#define ONE_HUNDRED_MS			(100)		// ticks in one hundred MS
#define ONE_SECOND				(10)		// one hundred MS ticks in a second


// Serial Port Defines
#define TX0_PRIORITY_LEVEL                      3
#define RX0_PRIORITY_LEVEL                      2

#define ENABLE_TX0_INTERRUPTS		           s0tic = TX0_PRIORITY_LEVEL;
#define DISABLE_TX0_INTERRUPTS		           s0tic = 0;
#define ENABLE_RX0_INTERRUPTS                  s0ric = RX0_PRIORITY_LEVEL;
#define DISABLE_RX0_INTERRUPTS                 s0ric = 0;

#define TX0_INTERRUPTS_ENABLED                 (s0tic != 0)
#define RX0_INTERRUPTS_ENABLED                 (s0ric != 0)

#define BAUD_RATE  115200

/* Switches */
#define	S1 				p8_3 
#define S2 				p8_1 
#define S3 				p8_2 
#define S1_DDR			pd8_3
#define S2_DDR			pd8_1
#define S3_DDR			pd8_2

/* LEDs */
#define	LED0			p8_0
#define	LED1			p7_4
#define	LED2			p7_2

#define	LED0_DDR 		pd8_0		// LED port direction register
#define	LED1_DDR 		pd7_4
#define	LED2_DDR 		pd7_2


#define LED_ON      	0
#define LED_OFF     	1

// Use these macros for switch inputs. 
#define ENABLE_SWITCHES {S1_DDR = 0; S2_DDR = 0; S3_DDR = 0;}

// Use these macros to control the LEDs.  
#define LED(led, state) ((led) = !state)
#define ENABLE_LEDS {LED0 = LED_OFF; LED1 = LED_OFF; LED2 = LED_OFF; LED0_DDR = 1; LED1_DDR = 1; LED2_DDR = 1; }
