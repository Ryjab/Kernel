#include "atapi.h"
#include "io.h"


void atapi_init()
{
	outb(PRIMARY_DCR, SRST);
	outb(PRIMARY_DCR, INTERRUPT_DISABLE);
	outb(SECONDARY_DCR, SRST);
	outb(SECONDARY_DCR, INTERRUPT_DISABLE);
}
