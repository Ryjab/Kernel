.macro ISR_NOERROR nb
.globl __asm_isr\nb
	__asm_isr\nb:
		pushl $0
		pushl $\nb
		jmp __asm_common_isr

.endm

.macro ISR_ERROR nb
.globl __asm_isr\nb
	__asm_isr\nb:
		pushl $\nb
		jmp __asm_common_isr
.endm

.extern general_handler
__asm_common_isr:
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
	popa
	add $8, %esp 
	iret


//isr
ISR_NOERROR 0
ISR_NOERROR 1
ISR_NOERROR 2
ISR_NOERROR 3
ISR_NOERROR 4
ISR_NOERROR 5
ISR_NOERROR 6
ISR_NOERROR 7
ISR_ERROR 8
ISR_NOERROR 9
ISR_ERROR 10
ISR_ERROR 11
ISR_ERROR 12
ISR_ERROR 13
ISR_ERROR 14
ISR_NOERROR 15
ISR_NOERROR 16
ISR_ERROR 17
ISR_NOERROR 18
ISR_NOERROR 19
ISR_NOERROR 20
ISR_NOERROR 21
ISR_NOERROR 22
ISR_NOERROR 23
ISR_NOERROR 24
ISR_NOERROR 25
ISR_NOERROR 26
ISR_NOERROR 27
ISR_NOERROR 28
ISR_NOERROR 29
ISR_NOERROR 30
ISR_NOERROR 31

