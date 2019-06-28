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


/* Link the drive with the reg to manipulate it */
void select_drive(u16 bus, u8 slave)
{
}
/* Check with memcmp the correct structure of the drive */
bool is_atapi_drive(u16 bus, u8 slave)
{
	return 0;
}
/** Main function:
 * For each drive found, check if it is one and save it to the reg
 **/
void discover_atapi_drive()
{
}

/* send the SCSI packet to the dive */
int send_packet(struct SCSI_packet *pkt, u16 drive, u16 size)
{
}

/* Read the datas for the drive of lba size */
void *read_block(size_t lba)
{
}
