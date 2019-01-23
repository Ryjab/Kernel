#include "io.h"

void timer_init(int hz)
	{
	    unsigned int divisor = 1193182 / hz; 	    
	    unsigned short command = 0b00110110;
	    outb(0x43, command);
	    outb(0x40, divisor & 0xFF);    
	    outb(0x40, divisor >> 8);
	}