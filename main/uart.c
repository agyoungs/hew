#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#define UXC0 0x10
#define UXC1 0x00
#define UXMR 0x05
#define UCON 0x00
#define TX_PENDING 0
#define TX_EMPTY (1<<1)

void read_from_rx_buf(char* str){
	int temp = ++rx_buf_s.index;
	rx_buf_s.index = UART_END;
	while(rx_buf_s.index != temp){
		*str = rx_buf_s.buf[rx_buf_s.index];
		str++;
		rx_buf_s.index++;
	}
	rx_buf_s.index = UART_END;
}

void uart_putc_direct(char c){
	u2tb = c;
	while(ti_u2c1 == TX_PENDING){};
}

void dbg_putc_direct(char c){
	while((u0c1&TX_EMPTY) == TX_PENDING){};
	u0tb = c;
}

void uart_puts(_far char* str){
	while(*str){
		uart_putc_direct(*str);
		str++;
	}
}
void dbg_puts(_far char* s){
	_far char* str = s;
	while(*str){
		dbg_putc_direct(*str);
		str++;
	}
}

void uart_putsn(_far char* s, int n){
	_far char* str = s;
	while(n){
		uart_putc_direct(*str);
		str++;
		n--;
	}
}
/*
void uart_init(void){
	u0brg = (unsigned char)(((f1_CLK_SPEED/16)/BAUD)-1);	// set UART0 bit rate generator
  	ucon = 0x00; 		// UART transmit/receive control register 2
  	u0c0 = 0x10; 		// UART0 transmit/receive control register 1
  	u0c1 = 0x00; 		// UART0 transmit/receive control register 1
  	u0mr = 0x05;		// UART0 transmit/receive mode register, not reversed
  	u0tb = u0rb;		// clear UART0char)0x55 receive buffer by reading
  	u0tb = 0;			// clear UART0 transmit buffer

	u2brg = (unsigned char)(((f1_CLK_SPEED/16)/BAUD)-1);	// set UART0 bit rate generator
  	u2c0 = 0x10; 		// UART0 transmit/receive control register 1
  	u2c1 = 0x00; 		// UART0 transmit/receive control register 1
  	u2mr = 0x05;		// UART0 transmit/receive mode register, not reversed
  	u2tb = u2rb;		// clear UART0 receive buffer by reading
  	u2tb = 0;			// clear UART0 transmit buffer

    DISABLE_IRQ			// disable irqs before setting irq registers
	s0ric = 0x04;		// Enable UART0 receive interrupt, priority level 4
	s2ric = 0x04;
	ENABLE_IRQ			// Enable all interrupts
  	u0c1 = 0x05; 		// UART0 transmit/receive control register 1
	u2c1 = 0x05;
}
*/