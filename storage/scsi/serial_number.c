#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <scsi/sg.h> /* glibc-headers */
#include <scsi/scsi.h>


#define SCSI_VPD_UNIT_SERIAL_NUMBER     0x80

int main(void)
{
	const char devicefile[] = "/dev/sda";
	const char* file_name = NULL;
	int sg_fd;
	unsigned char reply_buffer[96];
	unsigned char sense_buffer[32];
	sg_io_hdr_t io_hdr;

	/**
	 * INQUIRY Command
	 * +=====-========-========-========-========-========-========-========-========+
	 * |  Bit|   7    |   6    |   5    |   4    |   3    |   2    |   1    |   0    |
	 * |Byte |        |        |        |        |        |        |        |        |
	 * |=====+=======================================================================|
	 * | 0   |                           Operation Code (12h)                        |
	 * |-----+-----------------------------------------------------------------------|
	 * | 1   | Logical Unit Number      |                  Reserved         |  EVPD  |
	 * |-----+-----------------------------------------------------------------------|
	 * | 2   |                           Page Code                                   |
	 * |-----+-----------------------------------------------------------------------|
	 * | 3   |                           Reserved                                    |
	 * |-----+-----------------------------------------------------------------------|
	 * | 4   |                           Allocation Length                           |
	 * |-----+-----------------------------------------------------------------------|
	 * | 5   |                           Control                                     |
	 * +=============================================================================+
	 */
	unsigned char inquiry[6] = {
		INQUIRY, /* 0x12 */
		0x01, /* enable EVPD (VPD: Vital Product Data) */
		SCSI_VPD_UNIT_SERIAL_NUMBER,
		0x00, /* Reserved */
		sizeof(reply_buffer), /* Allocation Length */
		0x00, /* Control */
	};
	int i;

	/* Open device file */
	file_name = devicefile;
	printf("Get Type & SN from device file: %s\n", file_name);
	if ((sg_fd = open(file_name, O_RDWR)) < 0) {
		fprintf(stderr, "Cannot open devicefile! %s\n\n", strerror(errno));
		exit(1);
	}

	/* Send INQUIRY command */
	memset(&io_hdr, 0, sizeof(sg_io_hdr_t));
	io_hdr.interface_id = 'S';
	io_hdr.dxfer_direction = SG_DXFER_FROM_DEV;
	io_hdr.mx_sb_len = sizeof(sense_buffer);
	io_hdr.sbp = sense_buffer;
	io_hdr.dxfer_len = sizeof(reply_buffer);
	io_hdr.dxferp = reply_buffer;
	io_hdr.cmd_len = sizeof(inquiry);
	io_hdr.cmdp = inquiry;
	io_hdr.timeout = 1000; /* Miliseconds */

	if (ioctl(sg_fd, SG_IO, &io_hdr) < 0) {
		fprintf(stderr, "Cannot send INQUIRY command! %s\n", strerror(errno));
		exit(1);
	}

	if ((io_hdr.info & SG_INFO_OK_MASK) != SG_INFO_OK) {
		fprintf(stderr, "INQUIRY command failed! %s\n", strerror(errno));
		if (io_hdr.sb_len_wr > 0) {
			printf("Sense data: ");
			for (i = 0; i < io_hdr.sb_len_wr; i++)
				printf("0x%02X ", sense_buffer[i]);
			printf("\n");
		}
		exit(1);
	}

	/* Extract SN */
	if (reply_buffer[1] != SCSI_VPD_UNIT_SERIAL_NUMBER) {
		fprintf(stderr, "Unit serial number page invalid!\n\n");
		exit(1);
	}

	printf("Device type: 0x%02X\n", reply_buffer[1] & 0x1F);
	printf("Serial number: ");
	for (i = 4; i < reply_buffer[3] + 4; i++)
		printf("%c", reply_buffer[i]);
	printf("\n");
	exit(0);
}
