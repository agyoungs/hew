#include "extern.h"

struct lcd_fb{
	char lines[16];
	struct lcd_fb* next_fb;
};

struct uart_buf{
	char buf[64];
	char* rp;
	char* wp;
	char buf_i;
};

void write_to_fb_pos(_far char* s, int pos, struct lcd_fb* fb);
void write_to_fb(_far char* s, struct lcd_fb* fb);
void lcd_write_fb(struct lcd_fb* fb);
void A2DInit(void);
void lcd_init(char far StartupString1[] );
void lcd_puts(unsigned char position, _far const char * string);
void LCD_write(unsigned char data_or_ctrl, unsigned char value);
void DisplayDelay(unsigned long int units);
void BNSPutch(uint where, char c);
unsigned char BNSPrintf(uint where, char far * f, ...);
void itoa(int, char *);
char *sput_i(int, char *);
char *sput_ip1(int, char *);
void uart_putsn(_far char* s, int n);
void uart_putc_direct(char c);
