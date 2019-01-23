#ifndef IO_H_
#define IO_H_

#include <k/types.h>
/* desactive les interruptions */
#define cli asm("cli"::)

/* reactive les interruptions */
#define sti asm("sti"::)

static inline void outb(u16 port, u8 val)
{
	asm volatile ("outb %0, %1" : /* No output */ : "a"(val), "d"(port));
}

static inline u8 inb(u16 port)
{
	u8 res;

	asm volatile ("inb %1, %0" : "=&a"(res) : "d"(port));

	return res;
}

static inline void outw(u16 port, u16 val)
{
	asm volatile ("outw %0, %1" : /* No output */ : "a"(val), "d"(port));
}

static inline u16 inw(u16 port)
{
	u16 res;

	asm volatile ("inw %1, %0" : "=&a"(res) : "d"(port));

	return res;
}

/* ecrit un octet sur un port et marque une temporisation  */
static inline void outbp(u16 port, u8 value)
{
        asm volatile ("outb %%al, %%dx; jmp 1f; 1:" :: "d" (port), "a" (value));
}

#endif				/* !IO_H_ */
