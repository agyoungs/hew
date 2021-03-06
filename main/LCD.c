#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

void lcd_init(void){
	int i;
	// initial port directions
	prc2=1;							// unprotect as Port 9 is used
	PORT_DDR = PORT_DDR_VALUE; 
	EN_PIN = HIGH;
	EN_PIN_DDR = HIGH;				// set port that controls EN as output
	RS_PIN = HIGH;
	RS_PIN_DDR = HIGH;				// set port that controls RS as output
	EN_PIN = LOW;
	LCD_write(CTRL_WR,0x33);
	DisplayDelay(20);
	LCD_write(CTRL_WR,0x32);
	DisplayDelay(20);
	LCD_write(CTRL_WR,FUNCTION_SET);	/* reset sequence */
	LCD_write(CTRL_WR,FUNCTION_SET);
	LCD_write(CTRL_WR,LCD_CURSOR_OFF);
	LCD_write(CTRL_WR,LCD_CLEAR);
	LCD_write(CTRL_WR,LCD_HOME_L1);
	lcd_puts(LCD_LINE2, "        ");
	lcd_puts(LCD_LINE1, "FABULOUS");
}
/*
struct lcd_fb* fb_init(void){
	int i;
	fb0.next_fb = &fb1;
	fb1.next_fb = &fb0;
	write_to_fb("INITNYANFB  ZERO",&fb0);
	write_to_fb("INITNYANFB   ONE",&fb1);
	return &fb0;
}

void write_to_fb(_far char* s, struct lcd_fb* fb){
	int i = 0;
	while(i < 16){
		fb->lines[i] = s[i];
		i++;
	}
}

void write_to_fb_pos(_far char* s, int pos, struct lcd_fb* fb){
	int i = pos;
	while(i < 16){
		fb->lines[i] = s[i];
		i++;
	}		
}

void lcd_write_fb(struct lcd_fb* fb){
	int i;
	LCD_write(CTRL_WR, (unsigned char)(LCD_HOME_L1));
	for(i = 0; i < 8; i++){
		LCD_write(DATA_WR, fb->lines[i]);
	}
	LCD_write(CTRL_WR, (unsigned char)(LCD_HOME_L2));
	for(i = 0; i < 8; i++){
		LCD_write(DATA_WR, fb->lines[i+8]);
	}
	current_fb = current_fb->next_fb;
}
*/
void lcd_puts(unsigned char position, _far const char * string){
	static unsigned char next_pos = 0xFF;
	/* Set line position if needed. We don't want to if we don't need 
	   to because LCD control operations take longer than LCD data
	   operations. */
	if( next_pos != position){
		if(position < LCD_LINE2){
			/* Display on Line 1 */
		  	LCD_write(CTRL_WR, (unsigned char)(LCD_HOME_L1 + position) );
		}
		else{
			/* Display on Line 2 */
		  	LCD_write(CTRL_WR, (unsigned char)(LCD_HOME_L2 + position - LCD_LINE2) );
		}
		next_pos = position;		// set position index to known value
	}
	do{
		LCD_write(DATA_WR,*string++);
		next_pos++;				// increment position index
	}
	while(*string);
}

void LCD_write(unsigned char data_or_ctrl, unsigned char value){
    RS_PIN = data_or_ctrl;     			// RS SELECT (HIGH=DATA, LOW=CTRL
	/* Write upper nibble first */
	DATA_PORT &= 0xF0;					// Clear lower part of port
	DATA_PORT |= (value & 0xF0)>>4;		// OR in upper nibble
    EN_PIN = HIGH;          			// EN enable chip (HIGH)
	DisplayDelay(0);					// We only need a very little delay
    EN_PIN = LOW;          				// Latch data by dropping EN
	DisplayDelay(0);					// We only need a very little delay
	if(data_or_ctrl == CTRL_WR)
		DisplayDelay(1);				// extra delay needed for control writes
	/* Write lower nibble second */
	DATA_PORT &= 0xF0;					// Clear lower part of port
	DATA_PORT |= (value & 0x0F) ;		// write to port
    EN_PIN = HIGH;
	DisplayDelay(0);					// We only need a very little delay
    EN_PIN = LOW;          				// Latch data by dropping EN
	DisplayDelay(1);					// needed to put delay in between writes.
	if(data_or_ctrl == CTRL_WR)
		DisplayDelay(40);				// extra delay needed for control writes
}

void DisplayDelay(unsigned long int units){
	unsigned long int counter = units * 0x100;
	while(counter--){
		_asm ("NOP");
		_asm ("NOP");
		_asm ("NOP");
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

void cpu_init(void){
	unsigned int count = 40000;
	/* configure clock for divide by 1 mode */
	prc0 =1;					/* enable access to clock registers */
	cm1 = 0x20;					/* set CM16,CM17 divide ratio to 1, 
									main clock on in high drive no PLL*/
	cm06 = 0;					/* set divide ratio to 1 */
    /* configure and switch main clock to PLL at 24MHz - uncomment this section
		out if PLL operation is desired								*/
	prc1 = 1;					/* allow writing to processor mode register */
	pm20 = 1;					/* set SFR access to 2 wait which is required for
   									operation greater than 16 MHz */
	prc1 = 0;					/* protect processor mode register */
	plc0= 0x92;					// enable PLL (2X) and turn on
	while(count > 0) count--;   /* wait for PLL to stabilize (20mS maximum, 240,000 cycles @12Mhz)
                                   this decrement with no optimization is 12 cycles each */
    cm11 = 1;                   /* switch to PLL */
    prc0 = 0;   				/* protect clock control register */
	prc1 = 1;
	pm10 = 1;		// enable data flash area
	prc1 = 0;
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
