#include "QSKDefines.h"
#include "proto.h"
#include "extern.h"

#define FW_RIGHT	0x01
#define FW_LEFT		0x04
#define RV_RIGHT	0x02
#define RV_LEFT		0x08
#define ALL			0x0f
#define LEFT		0x0c
#define RIGHT		0x03

void forward_left(void){
	p3 &= ~LEFT;
	p3 |= FW_LEFT;
}

void reverse_left(void){
	p3 &= ~LEFT;
	p3 |= RV_LEFT;
}

void reverse_right(void){
	p3 &= ~RIGHT;
	p3 |= FW_RIGHT;
}

void forward_right(void){
	p3 &= ~RIGHT;
	p3 |= RV_RIGHT;
}

void off_right(void){
	p3 &= ~RIGHT;
}

void off_left(void){
	p3 &= ~LEFT;
}

void off_all(void){
	p3 &= ~ALL;
}