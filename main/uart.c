#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

void uart_putc_direct(char c){
	while((u0c1&(1<<1)) == 0x00){};
	u0tb = c;
}

void uart_puts_direct(_far unsigned char* s){
	char* str = s;
	while(*str){
		uart_putc_direct(*str);
		str++;
	}
}