#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

/***********************************************************************/
/*                                                                     */
/*  DATE        :Mon, Mar 23, 2009                                     */
/*																	   */
/*  DESCRIPTION :  This file contains all the interrupt routines for   */
/* 	  				the peripherals.  								   */
/*																	   */
/*  CPU GROUP   :62P                                                   */
/*                                                                     */
/*  Copyright (c) 2009 by BNS Solutions, Inc.						   */
/*  All rights reserved.											   */
/*                                                                     */
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



void A2DInterrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void UART0TransmitInterrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void DMA0Interrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void UART0ReceiveInterrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void TimerA1Interrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void TimerA2Interrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void TimerB0Interrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void KeyBoardInterrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void WakeUpInterrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void RTCInterrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}

void WatchDogInterrupt(void)
//-----------------------------------------------------------------------------------------------------
//  Purpose:	Unused in this program
//  
//
//  Rev:    1.0     Initial Release
//  
//  Notes:          None    
//-----------------------------------------------------------------------------------------------------
{
}