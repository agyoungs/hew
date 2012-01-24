#include "extern.h"

struct adc_t{
    unsigned short val[16];
    unsigned char index;
};

struct lcd_fb{
	char line1[8];
	char line2[8];
};

struct uart_buf{
	char buf[64];
	char buf_i;
};

void lcd_write_fb(struct lcd_fb* fb);
void A2DInit(void);
void lcd_init(char far StartupString1[] );
void lcd_puts(unsigned char position, _far const char * string);
void LCD_write(unsigned char data_or_ctrl, unsigned char value);
void DisplayDelay(unsigned long int units);
void BNSPutch(uint where, char c);
unsigned char BNSPrintf(uint where, char far * f, ...);
