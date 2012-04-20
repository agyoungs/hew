#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#define DOS 2
#define NONE 1
#define DOWN 0
#define SONG_MIN 0
#define SONG_MAX 45
#define UBERDELAY 1000

struct res_menunode{
	_far char* value;
	_far char* color;
};

struct res_menunode res_menu[] =  { {"    0   ", "  Black "},
									{"    1   ", "  Brown "},
									{"    2   ", "   Red  "},
									{"    3   ", " Orange "},
									{"    4   ", " Yellow "},
									{"    5   ", "  Green "},
									{"    6   ", "  Blue  "},
									{"    7   ", " Violet "},
									{"    8   ", "  Gray  "},
									{"    9   ", "  White "}
};
									
_far char* shape_menu[] = {
					" Circle ",
					" Square ",
					"Triangle",
					" Octagon",
					"Pentagon",
					" Hexagon",
					"  Cube  ",
					"  Oval  ",
					" Sphere ",
					"Cylinder"
};

_far char* song[] = {
					"We're   ",
					"the     ",
					"Red     ",
					"and     ",
					"White   ",
					"from    ",
					"State   ",
					"And     ",
					"we      ",
					"know    ",
					"we      ",
					"are     ",
					"the     ",
					"best.   ",
					"A       ",
					"hand    ",
					"behind  ",
					"our     ",
					"back,   ",
					"We      ",
					"can     ",
					"take    ",
					"on      ",
					"all     ",
					"the     ",
					"rest.   ",
					"Come    ",
					"over    ",
					"the     ",
					"hill,   ",
					"Carolina",
					"Devils  ",
					"and     ",
					"Deacs   ",
					"stand   ",
					"in      ",
					"line.   ",
					"The     ",
					"Red     ",
					"and     ",
					"White   ",
					"from    ",
					"N.C.    ",
					"State.  ",
					"Go      ",
					"State!  "
};

void res_menu_f(void){
	int index = ad0/RES_SCALE;
	lcd_puts(LCD_LINE1, res_menu[index].value);
	lcd_puts(LCD_LINE2, res_menu[index].color);
}

void shape_menu_f(void){
	int index = ad0/SHAPE_SCALE;
	lcd_puts(LCD_LINE1, shape_menu[index]);
	if(index == SHAPE_MENU_END)
		lcd_puts(LCD_LINE2, "   END  ");
	else
		lcd_puts(LCD_LINE2, shape_menu[++index]);
}


void song_menu_f(void){
	static int song_index;
	int dir = ad0/SONG_SCALE;
	if(dir < NONE)
		song_index--;
	if(dir > NONE)
		song_index++;
	if(song_index < SONG_MIN)
		song_index = SONG_MIN;
	if(song_index > SONG_MAX)
		song_index = SONG_MAX;
	lcd_puts(LCD_LINE1, song[song_index]);
	if(song_index % DOS)
		lcd_puts(LCD_LINE2, "   RED  ");
	else
		lcd_puts(LCD_LINE2, "  WHITE ");
	DisplayDelay(UBERDELAY);
}