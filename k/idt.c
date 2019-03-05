#include "idt.h"
#include <k/types.h>
#include "io.h"
#include "kbqueue.h"
#include "pit.h"

struct idte idt[256];
struct idt_r idtr;

//cached mask for irq
char k = 0xff;

void enable_interrupt(int irq)
{
	char i = (0x01 << irq);
	k ^= i;
	outb(0x21, k);
}

void disable_interrupt(int irq)
{
	char i = (0x01 << irq);
	k &= i;
	outb(0x21, k);
}

void init_pic()
{
	//icw1 - initialisation master
	outb(0x20, 0x11);
	// initialisation slave 	
    outb(0xA0, 0x11);
    //on map les interruptions sur 32 pour le pic master
    outb(0x21, 0x20);
    //on map les interruptions sur 38 pour le pic slave
    outb(0xA1, 0x28);
    //on determine l'entre/sortie du master sur l'irq2
    outb(0x21, 0x04);
    //on determine l'entre/sortie du slave sur irq2
    outb(0xA1, 0x02);

    //icw4 - master
    outb(0x21, 0x01);
 	//icw4 - slave
    outb(0xA1, 0x01);
 	
 	//masque toutes les interruptions
 	outb(0x21, 0xff); // 0xfc to enable pit and keyboard
	outb(0xA1, 0xff);
}

void (*asmfuncisr[32])(void) = {
	__asm_isr0,
	__asm_isr1,
	__asm_isr2,
	__asm_isr3,
	__asm_isr4,
	__asm_isr5,
	__asm_isr6,
	__asm_isr7,
	__asm_isr8,
	__asm_isr9,
	__asm_isr10,
	__asm_isr11,
	__asm_isr12,
	__asm_isr13,
	__asm_isr14,
	__asm_isr15,
	__asm_isr16,
	__asm_isr17,
	__asm_isr18,
	__asm_isr19,
	__asm_isr20,
	__asm_isr21,
	__asm_isr22,
	__asm_isr23,
	__asm_isr24,
	__asm_isr25,
	__asm_isr26,
	__asm_isr27,
	__asm_isr28,
	__asm_isr29,
	__asm_isr30,
	__asm_isr31
};

void (*asmfuncirq[2])(void) = {
	__asm_irq32,
	__asm_irq33
	__asm_irq46
	__asm_irq47
};

void idt_set(u16 segsel, u32 offset, u8 mbity, struct idte* midt)
{
	midt->off1 = (offset & 0xffff);
	midt->tss = segsel;
	midt->n0 = 0x0;
	midt->bity = mbity;
	midt->off2 = (offset >> 16) & 0xffff;
}


void idt_init()
{
	idtr.base = (u32) idt;
	idtr.limit = sizeof(idt) - 1;
	for (int i = 0; i < 32; i++)
	{
		idt_set(0x08, (u32) asmfuncisr[i], INTBITYP, &idt[i]);
	}
	init_pic();	
	//irq0 - PIT
	idt_set(0x08, (u32) asmfuncirq[0], INTBITYP, &idt[32]);
	//init tic with 100hrz
	timer_init(100);
	enable_interrupt(0);
	
	//irq1 - keyboard
	idt_set(0x08, (u32) asmfuncirq[1], INTBITYP, &idt[33]);
	enable_interrupt(1);

	idt_set(0x08, (u32) asmfuncirq[14], INTBITYP, &idt[46]);
	enable_interrupt(14);

	idt_set(0x08, (u32) asmfuncirq[15], INTBITYP, &idt[47]);
	enable_interrupt(15);
	
	asm volatile("lidt %0\n"
			 :/* no output */
			 : "m" (idtr)
			 : "memory");
	//ACTIVE LES INTERRUPTIONS
	sti;
}
