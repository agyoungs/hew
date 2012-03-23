#include "extern.h"

struct adc_t{
    unsigned short val[16];
    unsigned char index;
};

struct lcd_fb{
	char lines[16];
	struct lcd_fb* next_fb;
};

struct uart_buf{
	char buf[64];
	int read_index;
	int write_index;
};

struct task_t{
	unsigned long last_ticks;
};

void calibrate_on(void);
void calibrate_off(void);
void update_adc(void);
void back_n_forward(void);
void both_throttle(float throttle);
void min_throttle(void);
void circle(void);
void write_to_fb_pos(_far char* s, int pos, struct lcd_fb* fb);
void write_to_fb(_far char* s, struct lcd_fb* fb);
void lcd_write_fb(struct lcd_fb* fb);
void adc_init(void);
void lcd_init(void);
void lcd_puts(unsigned char position, _far const char * string);
void LCD_write(unsigned char data_or_ctrl, unsigned char value);
void DisplayDelay(unsigned long int units);
void itoa(int, char *);
char *sput_i(int, char *);
char *sput_ip1(int, char *);
void uart_putsn(_far char* s, int n);
void uart_putc_direct(char c);
void forward_left(void);
void reverse_left(void);
void forward_right(void);
void reverse_right(void);
void off_right(void);
void off_left(void);
void off_all(void);