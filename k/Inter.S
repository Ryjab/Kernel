.macro IRQ_NOERROR nb
.globl __asm_irq\nb
	__asm_irq\nb:
		pushl $0
		pushl $\nb
		jmp __asm_common_irq

.endm

.macro IRQ_ERROR nb
.globl __asm_irq\nb
	__asm_irq\nb:
		pushl $\nb
		jmp __asm_common_irq
.endm

.extern general_handler
__asm_common_irq:
	pusha
 	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl %esp
	call general_handler
	add $4, %esp
	pop %gs
	pop %fs
	pop %es
	pop %ds
	movb $0x20, %al
	outb %al, $0x20
	popa
	add $8, %esp 
	iret

IRQ_NOERROR 32
IRQ_NOERROR 33

