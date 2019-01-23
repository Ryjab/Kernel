#ifndef GDT_H
#define GDT_h


void gdt_all();
void gdt_prettyprint();

//64 bit ok
struct gdt_e {
	unsigned short limit : 16;
	unsigned short base : 16;
	unsigned char bbase : 8;
	unsigned char type : 4;
	unsigned char s : 1;
	unsigned char dpl : 2;
	unsigned char p : 1;
	unsigned char llimit : 4;
	unsigned char avl : 1;
	unsigned char l : 1;
	unsigned char db : 1;
	unsigned char g : 1;
	unsigned char lbase : 8;
	
}__attribute__((packed));


struct gdt_r_e{
	unsigned short limit;
	unsigned int base;
			
}__attribute__((packed));

struct gdt_e gdt[5];


#endif
