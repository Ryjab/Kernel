#include "initserial.h"


void enable_trei(u16 COM1)
{
	//ier
	u8 res = 0x02;
	outb(COM1+1, res);
}

void four_things(u16 COM1)
{
	//fcr	
	u8 res = 0xc7;
	outb(COM1+2, res);
}

void eight_noparity(u16 COM1)
{
	//lcr
	u8 res = 0x03;
	outb(COM1+3, res);
	//dlab = 0
}

void initserial()
{
	u16 COM1 = 0x3f8;
	
	eight_noparity(COM1);
	four_things(COM1);
	enable_trei(COM1);
	
	outb(COM1+3,0x83);
	//dlab = 1
	outb(COM1, 0x03);
	outb(COM1+1, 0x00);
	outb(COM1+3, 0x03);
	//dlab = 0
}



