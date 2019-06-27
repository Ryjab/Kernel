#include "write.h"

 
int check_error(u16 COM1)
{
	u8 res = inb(COM1+2);
	u8 res2 = res;
	u8 res3 = inb(COM1+5);
	res = res & 0x0f;
	res2 = res2 & 0xf0;

	/*
	*	res = 0x06 -> interupt lsr
	*		res3 = lsr.
	*		if res3 possède bit 1 sur 7/4/3/2/1 -> error !
	*
	*	res2 = 0xc0 -> FIFO enable and usable.
	*/

	if (res == 0x06)	
	{
		res3 = res3 & 0x80;
		if (res3 != 0x00)
			return 1;		
	}
	if (res2 == 0xc0)
		return 0;
	else
		return 1;
}

int write(const char *buf, size_t count)
{
	u16 COM1 = 0x3f8;
	size_t i = 0;
	
	for (; i < count; i++)
	{
		outb(COM1, buf[i]);
		if (check_error(COM1))
			return -1;
	}

	return i+2;
}
