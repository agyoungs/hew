#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

void uart_putc_direct(char c){
	while((u0c1&(1<<1)) == 0x00){};
	u0tb = c;
}

void uart_init(void){
	u0brg = (unsigned char)(((f1_CLK_SPEED/16)/BAUD_RATE)-1);	// set UART0 bit rate generator
  	ucon = 0x00; 		// UART transmit/receive control register 2
  	u0c0 = 0x10; 		// UART0 transmit/receive control register 1
  	u0c1 = 0x00; 		// UART0 transmit/receive control register 1
  	u0mr = 0x05;		// UART0 transmit/receive mode register, not reversed
  	u0tb = u0rb;		// clear UART0 receive buffer by reading
  	u0tb = 0;			// clear UART0 transmit buffer
	/*
	u1brg = (unsigned char)(((f1_CLK_SPEED/16)/BAUD_RATE)-1);	// set UART0 bit rate generator
  	ucon = 0x00; 		// UART transmit/receive control register 2
  	u1c0 = 0x10; 		// UART0 transmit/receive control register 1
  	u1c1 = 0x00; 		// UART0 transmit/receive control register 1
  	u1mr = 0x05;		// UART0 transmit/receive mode register, not reversed
  	u1tb = u0rb;		// clear UART0 receive buffer by reading
  	u1tb = 0;			// clear UART0 transmit buffer
	*/
    DISABLE_IRQ			// disable irqs before setting irq registers
	s0ric = 0x04;		// Enable UART0 receive interrupt, priority level 4
	//s1ric = 0x04;
	ENABLE_IRQ			// Enable all interrupts
  	u0c1 = 0x05; 		// UART0 transmit/receive control register 1
}


void uart_puts(_far char* s){
	_far char* str = s;
	while(*str){
		uart_putc_direct(*str);
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

void itoa(int integer, char *string)
{
if (0 > integer) {
++integer;
*string++ = '-';
*sput_ip1(-integer, string) = '\0';
} else {
*sput_i(integer, string) = '\0';
}
}

char *sput_i(int integer, char *string)
{
if (integer / 10 != 0) {
string = sput_i(integer / 10, string);
}
*string++ = (char)('0' + integer % 10);
return string;
}

char *sput_ip1(int integer, char *string)
{
int digit;

digit = (integer % 10 + 1) % 10;
if (integer / 10 != 0) {
string = (digit == 0 ? sput_ip1 : sput_i)(integer / 10, string);
*string++ = (char)('0' + digit);
} else {
if (digit == 0) {
*string++ = '1';
}
*string++ = (char)('0' + digit);
}
return string;
}


/*
void uart_buf_init(void){
	rx_buf_s.read_index = 0;
	rx_buf_s.write_index = 0;
	tx_buf_s.read_index = 0;
	tx_buf_s.write_index = 0;
}

void begin_tx(void){
	if(tx_buf_s.write_index != tx_buf_s.read_index){
		u0tb = tx_buf_s.buf[tx_buf_s.read_index];
		tx_buf_s.read_index++;
	}
}

void read_from_rx_buf(_far char* s){
	_far char* str = s;
	while(rx_buf_s.read_index != rx_buf_s.write_index){
		rx_buf_s.buf[rx_buf_s.read_index] = *str;
		str++;
		rx_buf_s.read_index++;
	}
}

void write_to_tx_buf(_far char* s){
	_far char* str = s;
	if(!(u0c1&(1<<1))){
		while(*str){
			tx_buf_s.buf[tx_buf_s.write_index] = *str;
			str++;
			tx_buf_s.write_index++;
		}
	}
}
*/