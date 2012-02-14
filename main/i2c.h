/*
// ---------------------------------------------------------------------------
//  DISCLAIMER:                                                         
//  We (RENESAS TECHNOLOGY EUROPE) do not warrant that the Software is
//  free from claims by a third party of copyright, patent, trademark,
//  trade secret or any other intellectual property infringement.
//
//  Under no circumstances are we liable for any of the following:
//
//  1. third-party claims against you for losses or damages;
//  2. loss of, or damage to, your records or data; or
//  3. economic consequential damages (including lost profits or
//     savings) or incidental damages, even if we are informed of
//     their possibility.
//
//  We do not warrant uninterrupted or error free operation of the
//  Software. We have no obligation to provide service, defect
//  correction, or any maintenance for the Software. We have no
//  obligation to supply any Software updates or enhancements to you
//  even if such are or later become available.
//
//  IF YOU DOWNLOAD OR USE THIS SOFTWARE YOU AGREE TO THESE TERMS.
//
//  THERE ARE NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
//  PARTICULAR PURPOSE.
// ---------------------------------------------------------------------------
//  Copyright (c) 2005 RENESAS TECHNOLOGY EUROPE   All rights reserved.
// ---------------------------------------------------------------------------
//              S O U R C E   F O R M A T
// ---------------------------------------------------------------------------
// tab width 4 (tab at 4 8 12 ...)     
// ---------------------------------------------------------------------------
//  Project Name: I2C   
//  File        : i2c.h 
//  Description : access i2c external device     
// ---------------------------------------------------------------------------
//  Supported   : IAR M16C C/EC++ Compiler V2.12A/W32
//  Compiler             
// ---------------------------------------------------------------------------
//              R E V I S I O N
// ---------------------------------------------------------------------------
//  Supported Compiler : IAR
// ---------------------------------------------------------------------------
//               R E V I S I O N   H I S T O R Y   
// ---------------------------------------------------------------------------
//  Date          Ver  Author  Description   
// ---------------------------------------------------------------------------
//  25/01/2005    1.0  TMA    Creation    
// ---------------------------------------------------------------------------
//              R E M A R K S
// Tested on device : M16C26 & M16C62P on UART2
// Used Peripherals : UARTi
// Used Interrupts : UARTiRX / UARTiTX / BUS_COLLISION_UARTi
// ---------------------------------------------------------------------------
#ifndef I2C_H
#define I2C_H

//#include "cpu.h"
// ---------------------------------------------------------------------------
// Defines declaration
// ---------------------------------------------------------------------------
#define BIT0  0x01
#define BIT1  0x02
#define BIT2  0x04
#define BIT3  0x08
#define BIT4  0x10
#define BIT5  0x20
#define BIT6  0x40
#define BIT7  0x80
#define BIT8  0x0100
#define BIT9  0x0200
#define BIT10  0x0400
#define BIT11  0x0800
#define BIT12  0x1000
#define BIT13  0x2000
#define BIT14  0x4000
#define BIT15  0x8000
#define FALSE 0
#define TRUE  1
// ---------------------------------------------------------------------------
// Types Defines
// ---------------------------------------------------------------------------
// Defines boolean type
typedef unsigned char tBoolean;
struct stI2CStatus
{
  unsigned char error:6;
  unsigned char nack:1;   // ACK/NACK Flag
  unsigned char busy:1;
};
//I2C bus errors "error" field defines
#define I2C_OK                0
#define I2C_UNCOMPLETE_WRITE  1
#define I2C_UNCOMPLETE_READ   2
typedef union
{
  unsigned char byte;
  struct stI2CStatus bit;
}I2CStatus;
#define I2C_FREE_NO_ERROR     0x00
#define I2C_BUSY_NO_ERROR     0x80
// ---------------------------------------------------------------------------
// I2C Bus speed seetings (based on 24MHZ CPU clock with f2SIO clock)
// I2C_CK = fj/2(n+1)
// ---------------------------------------------------------------------------
// I2C bus at 100 Kbit/s
#define I2C_50_KB_SPEED 119
// I2C bus at 200 Kbit/s
#define I2C_100_KB_SPEED 59
// I2C bus at 300 Kbit/s
#define I2C_150_KB_SPEED 39
// I2C bus at 200 Kbit/s
#define I2C_200_KB_SPEED 29
// I2C bus at 300 Kbit/s
#define I2C_300_KB_SPEED 19
// I2C bus at 400 Kbit/s
#define I2C_400_KB_SPEED 14
// ---------------------------------------------------------------------------
// Interrupt priority defines
// ---------------------------------------------------------------------------
#define INT_DISABLE 0   // Transmit/NACK interrupt level
#define RX_ACK_IPL  1   // Receive/ACK interrupt level
#define TX_NACK_IPL 1   // Transmit/NACK interrupt level
#define STA_STP_IPL 1   // Transmit/NACK interrupt level
#define DMA1_IPL    6   // Transmit/NACK interrupt level
// ---------------------------------------------------------------------------
// Initialise I²C line
// Data is sent by DMA1 triggered by ACK reception
// ---------------------------------------------------------------------------
// Input Parameters :     None
// ---------------------------------------------------------------------------
// Returned Parameters :  None
// ---------------------------------------------------------------------------
// Modified globales:     None
// ---------------------------------------------------------------------------
void I2C_init(void);
// ---------------------------------------------------------------------------
// Send Data on I²C line
// Data is sent by DMA1 triggered by ACK reception
// ---------------------------------------------------------------------------
// Input Parameters :
// 1- Slave address
// 2- Pointer to transmit buffer
// 3- Number of data to transmit
// ---------------------------------------------------------------------------
// Returned Parameters :
// TRUE or FALSE if data can be transmited
// ---------------------------------------------------------------------------
// Modified globales:   None
// ---------------------------------------------------------------------------
tBoolean I2C_MasterWrite(unsigned char , unsigned char * , unsigned short);
// ---------------------------------------------------------------------------
// Read Data on I²C line
// Data is received by DMA1 triggered by ACK reception
// ---------------------------------------------------------------------------
// Input Parameters :
// 1- Slave address
// 2- Pointer to receive buffer
// 3- Number of data to receive
// ---------------------------------------------------------------------------
// Returned Parameters :
// TRUE or FALSE if data can be read
// ---------------------------------------------------------------------------
// Modified globales:   None
// ---------------------------------------------------------------------------
tBoolean I2C_MasterRead(unsigned char , unsigned char * , unsigned short );
// ---------------------------------------------------------------------------
// Adjust bus speed of I²C line
// Uses defines : I2C_75_KB_SPEED ==> I2C_400_KB_SPEED
// ---------------------------------------------------------------------------
// Input Parameters :
// 1- Baud rate
// ---------------------------------------------------------------------------
// Returned Parameters :
// TRUE or FALSE if data can be transmited
// ---------------------------------------------------------------------------
// Modified globales: None
// ---------------------------------------------------------------------------
void I2C_setSpeed(unsigned char);
// ---------------------------------------------------------------------------
// DMA1 Interrupt
// Uses defines :
// ---------------------------------------------------------------------------
// Input Parameters :     None
// ---------------------------------------------------------------------------
// Returned Parameters :  None
// ---------------------------------------------------------------------------
// Modified globales:     None
// ---------------------------------------------------------------------------
_INTERRUPT  void DMA_interrupt(void);
// ---------------------------------------------------------------------------
// UARTi ACK interrupt
// Uses defines :
// ---------------------------------------------------------------------------
// Input Parameters :     None
// ---------------------------------------------------------------------------
// Returned Parameters :  None
// ---------------------------------------------------------------------------
// Modified globales:
// currentStatus
// ---------------------------------------------------------------------------
_INTERRUPT  void I2C_ACK(void);
// ---------------------------------------------------------------------------
// UARTi NACK interrupt
// Uses defines :
// ---------------------------------------------------------------------------
// Input Parameters :     None
// ---------------------------------------------------------------------------
// Returned Parameters :  None
// ---------------------------------------------------------------------------
// Modified globales:
// currentStatus
// ---------------------------------------------------------------------------
_INTERRUPT  void I2C_NACK(void);
// ---------------------------------------------------------------------------
// UARTi Start / Stop Interrupt
// Uses defines :
// ---------------------------------------------------------------------------
// Input Parameters :    None
// ---------------------------------------------------------------------------
// Returned Parameters : None
// ---------------------------------------------------------------------------
// Modified globales:
// currentStatus
// ---------------------------------------------------------------------------
_INTERRUPT void I2C_StartStopDetection(void);

// ---------------------------------------------------------------------------
// Get I²C line status
// Uses defines
// ---------------------------------------------------------------------------
// Input Parameters : None
// ---------------------------------------------------------------------------
// Returned : I²C status
// ---------------------------------------------------------------------------
// Modified globales: None
// ---------------------------------------------------------------------------
I2CStatus I2C_getStatus(void);
#endif
*/