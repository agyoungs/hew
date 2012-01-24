#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

void lcd_init(char far StartupString1[] ){
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
	lcd_puts(LCD_LINE1, LOGO);
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


void BNSPutch(uint where, char c){
//  Notes:          Well, don't pass it an index that isn't defined, because you'll mess up memory...
    uchar result;
    switch( where ) {
    case LCD_FILE_NUM:
		if(c == '\t'){													// inserting a \t in the string to be printed will cause the display to home and clear
		  	LCD_write(CTRL_WR, (unsigned char)(LCD_HOME_L1) );
		}
		else if(c == '\n'){												// inserting a \n will cause it to go to the start of the second line
		  	LCD_write(CTRL_WR, (unsigned char)(LCD_HOME_L2) );
		}
		else{
			LCD_write(DATA_WR,c);
		}
        break;
   case SERIAL_FILE_NUM:
		while(ti_u0c1 == 0); 			//  puts it in the UART 0 transmit buffer 
		u0tb = c;			
        break;
    default:
		*(char *)where = c;
        break;
    }
}

/*
unsigned char BNSPrintf(uint where, char * f, ...){
    char        c;
    va_list     ap;
    unsigned char   sign;
    unsigned char   prec = 255;
    unsigned long    i;
    unsigned char   retval;
    unsigned long   frac;
    unsigned long   over;
    unsigned char   digs;
    signed char width;                        
    uchar LeadingZero = ' ';
    uchar FirstCharOfPrecisionDetected;
    retval = 0;
    va_start(ap, f);
    while( c = *f++ ) {
        if( c != '%' ) {
            pputch(c);
        } else {
            prec = 255;
            width = 0;
            sign = 0;
            LeadingZero = ' '; 
            FirstCharOfPrecisionDetected = FALSE;
            loop:
            switch( c = *f++ ) {
            case 0:
                return retval;
            case '*':
                width = va_arg(ap, int);
                goto loop;
            case 'l':
                sign |= 0x80;
                goto loop;
            case 'd':
                sign++;
                goto decimal;
            case 'x':
            case 'X':
                prec += 8;
            case 'o':
                prec -= 2;
            case 'u':
                decimal:
                {
                    unsigned long    j;

                    if( sign & 0x80 ){
                        i = va_arg(ap, unsigned long);
					}
                    else{
                        i = va_arg(ap, int);
					}
                    if( sign & 1 ) {
                        if( (long)i < 0 ) {
                            i = -i;
                            width--;
                        } else
                            sign = 0;
                    } else {
                        if( !(sign & 0x80) ){
                            i = (unsigned short)i;
						}
                        sign = 0;
                    }
                    prec -= 255-10;
         putint:
                    c = (unsigned long)i % prec;
                    *(unsigned long *)&i /= prec;
                    j = 1;
                    while( j <= i ) {
                        j *= prec;
                        width--;
                    }

                    while( --width > 0 ){
                        pputch(LeadingZero);
					}

                    if( sign & 1 ){
                        pputch('-');
					}
                    while( j /= prec ) {
                        width = (i/j)%prec;
                        if( width > 9 ){
                            width += 'A'-'0'-10;
						}
                        pputch(width+'0');
                    }
                    if( c > 9 ){
                        c += 'A'-'0'-10;
					}
					pputch(c+'0');
				
                    if( sign & 2 ) {			// are we doing a floating point?
                        pputch('.');			// yup, put out the decimal point.
                        i = frac;
						LeadingZero = '0';		// at this point, it's actually a trailing zero.
                        sign = 4;
                        width = digs;
                        prec = 10;
                        goto putint;                                           // I know - ick!  but it's this or the 8K version
                    }
                }
                break;
            case 'f':
                {
                    double  flt;
                    flt = va_arg(ap, double);
                    if( prec > 6 ) {
                        prec = 6;
                    }
                    digs = prec;
                    sign = 0;
                    if( flt < 0 ) {
                        sign = 1;
                        flt = -flt;
                    }
                    if( digs == 0 ) {
                        i = (unsigned long)(flt+0.5);
                        prec = 10;
                        goto putint;                                           // put as integer - no dot 
                    }
                    width -= digs+1;
                    i = (unsigned long)flt;
                    flt -= (double)i;
                    sign |= 2;
                    over = 1;
                    do {
                        flt *= 10.0;
                        over *= 10;
                    }
                    while( --prec );
                    flt += 0.5;
                    frac = (unsigned long)flt;
                    if( frac >= over ) {
                        frac -= over;
                        i++;
                    }
                    prec = 10;
                    goto putint;
                }
            case 'c':
                while( width > 1 ) {
                    pputch(' ');
                    width--;
                }
                c = va_arg(ap, int);
                pputch(c);
                continue;
            case 's':
                {
                    const char *    x;
                    x = va_arg(ap, const char *);
                    c = 0;
                    while( x[c] ){
                        c++;
					}
                    if( c < prec ){
                        prec = c;
					}
                    while( width > prec ) {
                        pputch(' ');
                        width--;
                    }
                    while( prec-- ) {
                        c = *x++;
                        pputch(c);
                    }
                    continue;
                }
            case '.':
                if( *f == '*' ) {
                    prec = va_arg(ap, int);
                    f++;
                } else {
                    prec = *f++ - '0';
                    c = *f;
                    if( c >= '0' && c <= '9' ) {
                        prec = prec*10 + c - '0';
                        f++;
                    }
                }
                goto loop;
            default:
                if( c >= '0' && c <= '9' ) {
                    if( FirstCharOfPrecisionDetected == FALSE ) {
                        if( c == '0' ) {
                            LeadingZero = '0';
                        }
                        FirstCharOfPrecisionDetected = TRUE;
                    }
                    width = width * 10 + c - '0';
                    goto loop;
                }
                pputch(c);
                continue;

            }

        }
    }
	if(where > GREATEST_FILE_NUMBER){			// must be a pointer so this must be an sprintf...
		*(char *)where = 0;								// null terminate it
	}
    return retval;
}
*/