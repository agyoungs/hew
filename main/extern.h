extern volatile unsigned int right_pwm_high;
extern volatile unsigned int left_pwm_high;
extern volatile unsigned char right_pwm_state;
extern volatile unsigned char left_pwm_state;
extern volatile unsigned long ticks;
extern volatile unsigned short adc_reg;
extern volatile char uart_rec;

extern unsigned int an_min_on;
extern unsigned int an_max_on;
extern unsigned int an_min_off;
extern unsigned int an_max_off;
extern int an_noise;
extern int thresh;

extern struct uart_buf rx_buf_s, tx_buf_s;
extern volatile struct adc_t adc_s;
extern struct lcd_fb fb0, fb1;
extern struct lcd_fb* current_fb;
