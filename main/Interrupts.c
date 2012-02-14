#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#pragma INTERRUPT A2DInterrupt
#pragma INTERRUPT UART0TransmitInterrupt
#pragma INTERRUPT UART0ReceiveInterrupt
#pragma INTERRUPT TimerA2Interrupt
#pragma INTERRUPT TimerB0Interrupt
#pragma INTERRUPT KeyBoardInterrupt
#pragma INTERRUPT DMA0Interrupt
#pragma INTERRUPT WakeUpInterrupt
#pragma INTERRUPT tb1_int
#pragma INTERRUPT ta0_int
#pragma INTERRUPT ta1_int
#pragma INTERRUPT WatchDogInterrupt

void ta0_int(void){
	off_right();
}

void ta1_int(void){
	off_left();
}

void tb1_int(void){
	ta0s = 0;
	ta1s = 0;

	ta0 = right_pwm_high;
	ta1 = left_pwm_high;
	if(right_pwm_state){
		forward_right();
	}
	else{
		reverse_right();
	}
	if(left_pwm_state){
		forward_left();
	}
	else{
		reverse_left();
	}
	
	ta0s = 1;
	ta1s = 1;
	ta0os = 1;
	ta1os = 1;
}

void A2DInterrupt(void){
}

void UART0TransmitInterrupt(void){	
}

void DMA0Interrupt(void){
}

void UART0ReceiveInterrupt(void){
	uart_rec = u0rb;
}

void TimerA1Interrupt(void){
}

void TimerA2Interrupt(void){
}

void TimerB0Interrupt(void){
	ticks++;
}

void KeyBoardInterrupt(void){
}

void WakeUpInterrupt(void){
}

void WatchDogInterrupt(void){
}
