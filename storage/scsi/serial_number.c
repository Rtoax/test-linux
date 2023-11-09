#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <scsi/sg.h> /* glibc-headers */


int main(void)
{
	const char devicefile[] = "/dev/sda";
	const char* file_name = NULL;
	int sg_fd;
	unsigned char reply_buffer[96];
	unsigned char sense_buffer[32];
	sg_io_hdr_t io_hdr;
	unsigned char inquiry[6] = {0x12, 0x01, 0x80, 0x00, sizeof(reply_buffer), 0x00};
	int i;

	/* Open device file */
	file_name = devicefile;
	printf("\nGet Type & SN from device file: %s\n\n", file_name);
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
		fprintf(stderr, "Cannot send INQUIRY command!\n\n");
		exit(1);
	}

	if ((io_hdr.info & SG_INFO_OK_MASK) != SG_INFO_OK) {
		fprintf(stderr, "INQUIRY command failed!\n");
		if (io_hdr.sb_len_wr > 0) {
			printf("Sense data: ");
			for (i = 0; i < io_hdr.sb_len_wr; i++)
				printf("0x%02X ", sense_buffer[i]);
			printf("\n");
		}
		exit(1);
	}

	/* Extract SN */
	if (reply_buffer[1] != 0x80) {
		fprintf(stderr, "Unit serial number page invalid!\n\n");
		exit(1);
	}
	printf("Device type: 0x%02X\n", reply_buffer[1] & 0x1F);
	printf("Serial number: ");
	for (i = 4; i < reply_buffer[3] + 4; i++)
		printf("%c", reply_buffer[i]);
	printf("\n\n");
	exit(0);
}
