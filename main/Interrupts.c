#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#pragma INTERRUPT A2DInterrupt
#pragma INTERRUPT UART0TransmitInterrupt
#pragma INTERRUPT UART0ReceiveInterrupt
#pragma INTERRUPT TimerA1Interrupt
#pragma INTERRUPT TimerA2Interrupt
#pragma INTERRUPT TimerB0Interrupt
#pragma INTERRUPT KeyBoardInterrupt
#pragma INTERRUPT DMA0Interrupt
#pragma INTERRUPT WakeUpInterrupt
#pragma INTERRUPT tb1_int
#pragma INTERRUPT WatchDogInterrupt
void tb1_int(void){}

void A2DInterrupt(void){
}

void UART0TransmitInterrupt(void){	
}

void DMA0Interrupt(void){
}

void UART0ReceiveInterrupt(void){
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
