#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

/***********************************************************************/
/*  DESCRIPTION :  This file contains all the interrupt routines for   */
/* 	  				the peripherals.  								   */
/*																	   */
/*  Copyright (c) 2009 by BNS Solutions, Inc.						   */
/***********************************************************************/

#pragma INTERRUPT A2DInterrupt
#pragma INTERRUPT UART0TransmitInterrupt
#pragma INTERRUPT UART0ReceiveInterrupt
#pragma INTERRUPT TimerA1Interrupt
#pragma INTERRUPT TimerA2Interrupt
#pragma INTERRUPT TimerB0Interrupt
#pragma INTERRUPT KeyBoardInterrupt
#pragma INTERRUPT DMA0Interrupt
#pragma INTERRUPT WakeUpInterrupt
#pragma INTERRUPT RTCInterrupt
#pragma INTERRUPT WatchDogInterrupt

void A2DInterrupt(void){
	adc_reg = ad0;
}

void UART0TransmitInterrupt(void){
	if(tx_buf_s.buf_i != 0){
		u0tb = tx_buf_s.buf[buf_i];
		buf_i--;
	}
}

void DMA0Interrupt(void){
}

void UART0ReceiveInterrupt(void){
	rx_buf_s.buf[buf_i++] = u0rb;
}

void TimerA1Interrupt(void){
}

void TimerA2Interrupt(void){
}

void TimerB0Interrupt(void){
	p8 ^= 0x01;
	ticks++;
}

void KeyBoardInterrupt(void){
}

void WakeUpInterrupt(void){
}

void RTCInterrupt(void){
}

void WatchDogInterrupt(void){
}