extern volatile unsigned long ticks;
extern volatile unsigned short adc_reg;

extern struct uart_buf rx_buf_s, tx_buf_s;
extern struct lcd_fb fb0, fb1;
extern struct lcd_fb* current_fb;