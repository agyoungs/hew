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
#pragma INTERRUPT uart2_rx_int
#define STOP 0

void uart2_rx_int(void){
	if(u2rb == 'N'){
		rx_buf_s.index = UART_END;
	}
	if(rx_buf_s.index > UART_BSIZE){
		rx_buf_s.index = UART_END;
	}
	rx_buf_s.buf[rx_buf_s.index] = u2rb;
	rx_buf_s.index++;
}

void ta0_int(void){
	off_right();
}

void ta1_int(void){
	off_left();
}

void tb1_int(void){
	ta0s = STOP;
	ta1s = STOP;
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
	ta0s = START;
	ta1s = START;
	ta0os = START;
	ta1os = START;
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
	if((ad2 > thresh)||(ad3 > thresh))
		CLED_ON;
	else
		CLED_OFF;
}

void KeyBoardInterrupt(void){
}

void WakeUpInterrupt(void){
}

void WatchDogInterrupt(void){
}
