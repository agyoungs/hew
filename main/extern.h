extern volatile unsigned long ticks;
extern volatile unsigned short adc_reg;

struct lcd_fb{
	char line1[8];
	char line2[8];
};