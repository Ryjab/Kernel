#ifndef IDT_H
#define IDT_H


#define INTBITYP 0x8E //privilegié
#define INTBITYNP 0xEE // non privilégié

#include "io.h"
void idt_init();

struct idte
{
	unsigned short off1 : 16;
	unsigned short tss : 16;
	unsigned char n0 :8; // toujours 0
	unsigned char bity : 8; //contient dpl + p + autre flag
	unsigned short off2 : 16;
}__attribute__((packed));


struct idt_r
{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

struct regs
{
	unsigned gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;   	/* pushed by 'pusha' */
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;   		/* pushed by the processor automatically */
}__attribute__((packed));


extern struct idte idt[256];
extern struct idt_r idtr;


extern void __asm_isr0();
extern void __asm_isr1();
extern void __asm_isr2();
extern void __asm_isr3();
extern void __asm_isr4();
extern void __asm_isr5();
extern void __asm_isr6();
extern void __asm_isr7();
extern void __asm_isr8();
extern void __asm_isr9();
extern void __asm_isr10();
extern void __asm_isr11();
extern void __asm_isr12();
extern void __asm_isr13();
extern void __asm_isr14();
extern void __asm_isr15();
extern void __asm_isr16();
extern void __asm_isr17();
extern void __asm_isr18();
extern void __asm_isr19();
extern void __asm_isr20();
extern void __asm_isr21();
extern void __asm_isr22();
extern void __asm_isr23();
extern void __asm_isr24();
extern void __asm_isr25();
extern void __asm_isr26();
extern void __asm_isr27();
extern void __asm_isr28();
extern void __asm_isr29();
extern void __asm_isr30();
extern void __asm_isr31();


extern void __asm_irq32();
extern void __asm_irq33();
extern void __asm_irq46();
extern void __asm_irq47();


#endif
