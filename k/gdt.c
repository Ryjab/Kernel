#include "gdt.h"

void gdt_init();

void gdt_prettyprint()
{
	for(int i = 0; i < 5; ++i)
	{
		printf("****************************************\n");
		if (i == 0)
			printf ("Null\n");
		else if (i == 1)
			printf ("Kernel code\n");
		else if (i == 2)
			printf("Kernel data\n");
		else if (i == 3)
			printf("User code\n");
		else
			printf("User data\n");		
		printf("\t\t\t\tlimit = %d\n \
			\tbase = %d\n \
			\tbbase = %d\n \
			\ttype = %d\n \
			\ts = %d\n \
			\tdpl = %d\n \
			\tp = %d\n \
			\tllimit = %d\n \
			\tavl = %d\n \
			\tl = %d\n \
			\tdb = %d\n \
			\tg = %d\n \
			\tlbase = %d\n" \
			, gdt[i].limit, gdt[i].base, gdt[i].bbase \
			, gdt[i].type, gdt[i].s, gdt[i].dpl \
			, gdt[i].p, gdt[i].llimit, gdt[i].avl \
			, gdt[i].l, gdt[i].db, gdt[i].g \
			, gdt[i].lbase); 	
		
		printf("****************************************\n");		
	}
}

void gdt_all()
{
	gdt_init();
	struct gdt_r_e gdtr;
	gdtr.base = gdt;
	gdtr.limit = sizeof(gdt) - 1;
	memcpy((char *) gdtr.base, (char *) gdt, gdtr.limit);
	asm volatile("lgdt %0\n"
			: /* no	 output*/
			: "m" (gdtr)
			: "memory");
	//cr0 - PE to 1 
	asm volatile("movl $0x1, %eax\n\t"
		     "movl %eax, %cr0\n\t");

	//ds,fs,gs,ss -> KD		
	asm volatile("movw $0x10, %ax\n\t"
		     "movw %ax, %ds\n\t"
		     "movw %ax, %fs\n\t"
		     "movw %ax, %gs\n\t"
		     "movw %ax, %ss\n\t");
	// cs -> KC
	asm volatile ("ljmp $0x08, $yolo \n\t yolo: \n\t");
}



void gdt_init()
{
// 0 - Null
	gdt[0].limit = 0x0000;
	gdt[0].base = 0x0000;
	gdt[0].bbase = 0x00;
	gdt[0].type = 0x0;
	gdt[0].s = 0x0;
	gdt[0].dpl = 0x0;
	gdt[0].p = 0x0;
	gdt[0].llimit = 0x0;
	gdt[0].avl = 0x0;
	gdt[0].l = 0x0;
	gdt[0].db = 0x0;
	gdt[0].g = 0x0;
	gdt[0].lbase = 0x00;

// 1 - Kernel Code
	gdt[1].limit = 0xffff;
	gdt[1].base = 0x0000;
	gdt[1].bbase = 0x00;
	gdt[1].type = 0xa;
	gdt[1].s = 0x1;
	gdt[1].dpl = 0x0;
	gdt[1].p = 0x1;
	gdt[1].llimit = 0xf;
	gdt[1].avl = 0x0;
	gdt[1].l = 0x0;
	gdt[1].db = 0x1;
	gdt[1].g = 0x1;
	gdt[1].lbase = 0x00;

// 2 - Kernel data

	gdt[2].limit = 0xffff;
	gdt[2].base = 0x0000;
	gdt[2].bbase = 0x00;
	gdt[2].type = 0x2;
	gdt[2].s = 0x1;
	gdt[2].dpl = 0x0;
	gdt[2].p = 0x1;
	gdt[2].llimit = 0xf;
	gdt[2].avl = 0x0;
	gdt[2].l = 0x0;
	gdt[2].db = 0x1;
	gdt[2].g = 0x1;
	gdt[2].lbase = 0x00;

// 3 - user code

	gdt[3].limit = 0xffff;
	gdt[3].base = 0x0000;
	gdt[3].bbase = 0x00;
	gdt[3].type = 0xa;
	gdt[3].s = 0x1;
	gdt[3].dpl = 0x3;
	gdt[3].p = 0x1;
	gdt[3].llimit = 0xf;
	gdt[3].avl = 0x1;
	gdt[3].l = 0x0;
	gdt[3].db = 0x1;
	gdt[3].g = 0x1;
	gdt[3].lbase = 0x00;

// 4 - user data

	gdt[4].limit = 0xffff;
	gdt[4].base = 0x0000;
	gdt[4].bbase = 0x00;
	gdt[4].type = 0x2;
	gdt[4].s = 0x1;
	gdt[4].dpl = 0x3;
	gdt[4].p = 0x0;
	gdt[4].llimit = 0xf;
	gdt[4].avl = 0x1;
	gdt[4].l = 0x0;
	gdt[4].db = 0x1;
	gdt[4].g = 0x1;
	gdt[4].lbase = 0x00;
}

