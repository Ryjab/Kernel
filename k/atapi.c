#include "atapi.h"
#include "io.h"


void atapi_init()
{
	outb(PRIMARY_DCR, SRST);
	outb(PRIMARY_DCR, INTERRUPT_DISABLE);
	outb(SECONDARY_DCR, SRST);
	outb(SECONDARY_DCR, INTERRUPT_DISABLE);
}

/* Check for the availability of the register(Bit 7: BSY */
void busy_wait(u16 drive)
{
}
/* wait for the 4*inb or approx 400 ns */
void wait_device_selection(u16 drive)
{
}
/* Wait until Busy Bit is cleared and DRQ is set */
void wait_packet_request(u16 drive)
{
}


/* */
void select_drive(u16 bus, u8 slave)
{
}
/* */
bool is_atapi_drive(u16 bus, u8 slave)
{
	return 0;
}
/* */
void discover_atapi_drive()
{
}

/* */
int send_packet(struct SCSI_packet *pkt, u16 drive, u16 size)
{
}

/* */
void *read_block(size_t lba)
{
}
