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
//  File        : i2c.c 
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
//  25/01/2005    1.0   TMA    Creation
//  26/07/2005   1.01 Thanks to M. Louvel    
// ---------------------------------------------------------------------------
//              R E M A R K S
// Tested on device : M16C26 & M16C62P on UART2
// Used Peripherals : UARTi
// Used Interrupts : UARTiRX / UARTiTX / BUS_COLLISION_UARTi
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// Include declaration
// ---------------------------------------------------------------------------
#include "i2c.h"
// ---------------------------------------------------------------------------
// Global variables declaration
// ---------------------------------------------------------------------------
struct stI2CAddress
{
  unsigned char rw:1;
  unsigned char address:7;
};
typedef union
{
  unsigned char byte;
  struct stI2CAddress bit;
}tI2CAddress;
 
static tI2CAddress slaveAddress;
static unsigned short readIndex;
static unsigned short totalReadLength;
static unsigned char *ptrReadData;
static unsigned short writeIndex;
static unsigned short writeLength;
static unsigned char *ptrWriteData;
static I2CStatus currentStatus;

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
void I2C_init()
{
  UiMR    = 0x0A;   // I²C mode mode ext. clock (slave mode)
  UiBRG   = I2C_400_KB_SPEED; // 100KBPS (this depends on used Xin/CPU clock)
  UiC0    = 0xB0;   // MSB first,Tx at raising edge of CK, f1,Nch,CTS disable
  UiSMR   = 0x01;   // I²Cbus mode,Arbitration lost flag Update per bit
                    // Bus collision detect at raising edge of CK
  UiSMR2  = 0x11;   // ACK/NACK interrupt,disable SDA/SCL,UART init
  UiSMR3  = 0x62;   // SDA delay = 3 to 4-cycle of BRG count source
  UiSMR4  = 0x30;   // NACK data output(SDA=SCL="H")
  UiC1    = 0x15;   // Transfer/Receive enable
#ifdef  DMA1_USED
  DMA1IC  = INT_DISABLE;  // Disable DMA1 Interrupt
  DM1SL   = DMA1_ACK_TRIG_SOURCE;
#endif
  STA_STP_IC  = STA_STP_IPL;  // Start condition interrupt enable
  ACK_IC      = INT_DISABLE;  // ACK int. disable
  NACK_IC     = INT_DISABLE;  // NACK int. enable
  currentStatus.byte = I2C_FREE_NO_ERROR;
}
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
tBoolean I2C_MasterWrite(unsigned char address, unsigned char * ptrData, unsigned short length)
{
  if(currentStatus.bit.busy==TRUE)
    return FALSE;
  currentStatus.byte =I2C_BUSY_NO_ERROR;
#ifdef  DMA1_USED
  // DMA Configuration
  DAR1    = (long)&UiTB;    // Destination
  TCR1    = length-1;       // Size (minus one due to DMA specification)
  SAR1    = (long)ptrData;  // Source
  DM1CON  = 0x19;           // Memory to fixed destination single transfert
  DMA1IC  = DMA1_IPL;       // Enable DMA1 Interrupt
#else
  writeLength     = length;       // Size (minus one due to DMA specification)
  ptrWriteData    = ptrData;  // Source
  writeIndex      = 0;
#endif
  slaveAddress.bit.address = address;
  slaveAddress.bit.rw = 0;     // Write mode
  UiSMR   = 0x01;   // All bit clear without bit0
  UiSMR4  = 0x70;   // SCL output STOP enable (SCLHI=1)
  UiMR    = 0x00;   // Disable UART function
  UiMR    = 0x02;   // Enable IIC mode, internal clock
  UiC1    = 0x10;   // Transmit/Receive disable
  UiSMR2  = 0x02;   // UART init. disable,Clock sync. enable
  UiSMR4  = 0x71;   // Start condition generate (STSPSEL=0/STAREQ=1)
  UiSMR4  = 0x09;   // STSP output enable (STSPSEL=1/STAREQ=1)
  return TRUE;
}
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
tBoolean I2C_MasterRead(unsigned char address, unsigned char *ptrData, unsigned short length)
{
  if(currentStatus.bit.busy==TRUE)
    return FALSE;
  if(length==0)
    return TRUE;
  currentStatus.byte =I2C_BUSY_NO_ERROR;
  ptrReadData = ptrData;
  readIndex = 0;
  totalReadLength = length;
  slaveAddress.bit.address = address;
  slaveAddress.bit.rw=1;//Read mode
  UiSMR   = 0x01;   // All bit clear without bit0
  UiSMR4  = 0x70;   // SCL output STOP enable (SCLHI=1)
  UiMR    = 0x00;   // Disable UART function
  UiMR    = 0x02;   // Enable IIC mode, internal clock
  UiC1    = 0x10;   // Transmit/Receive disable
  UiSMR2  = 0x02;   // UART init. disable,Clock sync. enable
  UiSMR4  = 0x71;   // Start condition generate (STSPSEL=0/STAREQ=1)
  UiSMR4  = 0x09;   // STSP output enable (STSPSEL=1/STAREQ=1)
  return TRUE;
}
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
void I2C_setSpeed(unsigned char baudRate)
{
    UiBRG = baudRate;
}
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
#ifdef DMA1_USED
#pragma vector = DMA1
_INTERRUPT  void DMA_interrupt(void){
  if(slaveAddress.bit.rw==0)//Write mode ?
  {
    //Last data send, with ack ?
    ACK_IC = RX_ACK_IPL;    // ACK int. enable
    DMA1IC = INT_DISABLE;   //Disable DMA1 Interrupt
  }
}
#endif
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
#pragma vector=UARTi_RX
_INTERRUPT  void I2C_ACK(void)
{
  if(slaveAddress.bit.rw==1)  //Read mode ?
    {
    if(readIndex!=0)      //Address in receive register if readIndex==0
      {
      ptrReadData[readIndex-1] = (unsigned char)UiRB;
      }
    readIndex++;
    //Continue transmission with FF (keep bus high)
    if(readIndex==totalReadLength)//is next data last byte ?
      UiTB = 0x01FF;    // send NACK
    else
      UiTB = 0x00FF;    // send ACK
    }
  else
    {
      if(writeIndex != writeLength) //Sent all bytes ?
        {
        UiTB = ptrWriteData[writeIndex];
        writeIndex++;
        }
      else
        {
        //Continue transmission with FF (keep bus high)
        if(writeIndex==writeLength)//is next data last byte ?
        //This portion is generated ONLY on last data Transmit
        UiSMR4 = 0x74;    // SCL=SDA="H"
        UiSMR4 = 0x0C;    // Stop condition (STSPSEL=1/STPREQ=1)
        }
    }
}
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
#pragma vector=UARTi_TX
_INTERRUPT  void I2C_NACK(void)
{
currentStatus.bit.nack = TRUE;
  UiSMR4 = 0x74;    // SCL=SDA="H"
  UiSMR4 = 0x0C;    // Stop condition (STSPSEL=1/STPREQ=1)
  ACK_IC = INT_DISABLE;  // ACK int. disable
#ifdef  DMA1_USED
  DM1CON = 0;           // DMA1 disable (stop data transmission)
  DMA1IC = INT_DISABLE; //Disable DMA1 Interrupt
#endif
  if(slaveAddress.bit.rw==1)//Read mode ?
    {
    if(readIndex!=totalReadLength)
      // Received NACK before end of reception.
      currentStatus.bit.error = I2C_UNCOMPLETE_READ;
    else
      {
      // Get last byte in receive buffer
      ptrReadData[readIndex-1] = (unsigned char)UiRB;
      }
    }
  else
    {
    // Illegal condition
    currentStatus.bit.error = I2C_UNCOMPLETE_WRITE;
    }
}
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
#pragma vector=UiBUS    // COLLISION UART
_INTERRUPT  void I2C_StartStopDetection(void)
{
  unsigned short temp = 0;
  if(BusBusyFlag == 1)
    { // Start condition interrupt
    UiC1 = 0x10;    // Transfer/Receive enable
    UiC1 = 0x15;    // Transfer/Receive enable
    UiMR = 0x02;
    UiSMR4 = 0x00;  // STSPSEL=0
    temp = slaveAddress.byte; // Slave address set
    temp |= 0x0100; // NACK data set
    UiTB = temp;    // Start 1st byte transfer
    UiRB = 0;       // Arbitration lost flag clear
    NACK_IC = TX_NACK_IPL;   // NACK interrupt
#ifdef DMA1_USED
    if(slaveAddress.bit.rw==1)//Read mode ?
      ACK_IC  = RX_ACK_IPL;    // ACK interrupt
#else
    ACK_IC  = RX_ACK_IPL;    // ACK interrupt
#endif
    }
  else
    { // Stop condition interrupt
    UiMR = 0x00;  // port set(Purpose:TXFUL,TBFUL flag must be cleared when
  // slave receive)
    UiMR    = 0x02;    // modified july 2005, thanks to M. Louvel
//    UiMR    = 0x0a;    // ext. clock sel => previous option
    UiSMR2  = 0x10;    //
    UiSMR4  = 0x30;    // ACK data output"H"
    UiC1    = 0x15;    // transfer/receive enable
    ACK_IC  = INT_DISABLE;
    NACK_IC = INT_DISABLE;
    if(currentStatus.bit.busy==TRUE)
      {
      currentStatus.bit.busy=FALSE;
      }
    }
}
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
I2CStatus I2C_getStatus()
{
  return currentStatus;
}*/