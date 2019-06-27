#include "idt.h"
#include "io.h"
#include "keyboard.h"
#include "kbqueue.h"
#include "gettick.h"

unsigned long ticks = 0;

void divide_0()
{
	printf("interruption : divide by 0\n");
}
void debug()
{
	printf("interruption : debug\n");
}
void nmi()
{
	printf("interruption : nmi\n");
}
void breakpoint()
{
	printf("interruption : breakpoint\n");
}

void pit()
{
	ticks++;
	//printf("timer\n");
}

unsigned long gettick(void)
{
	return ticks;
}

void keyboard()
{
	unsigned char scancode;
	scancode = inb(0x60);
	unsigned char tmp = scancode;
	tmp = tmp >> 7;
	if (tmp == 0x00)
	{
		//printf("lettre appuyée %c \n", (kbdus[scancode]));
		if (!putkey(kbdus[scancode]))
			printf("%s\n", "buffer full");
	}
}



void D_primaire(){

}

void D_secondaire()
{
	
}

void general_handler(struct regs* r)
{
	if (r->int_no < 32)
	{
		switch (r->int_no){
			case 0 :
				divide_0();
				break;		
			case 1 :
				debug();
				break;		
			case 2 :
				nmi();
				break;
			case 3 :
				breakpoint();
				break;				
			default :
				printf("error, interruption : %d\n", r->int_no);
		}
	}
	else
	{
		switch(r->int_no)
		{
			case 32:
				pit();
				break;
			case 33:
				keyboard();
				break;
			case 46 :
				D_primaire();
				outbp(0xA0, 0x20);
				break;
			case 47 :
				D_secondaire();
				outbp(0xA0, 0x20);
				break;
			default :
				printf("error, interruption : %%d\n", r->int_no);
		}
		outbp(0x20, 0x20);
	}
}

