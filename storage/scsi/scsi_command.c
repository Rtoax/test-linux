/* Example program to demonstrate the generic SCSI interface */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <scsi/sg.h> /* glibc-headers */

#define DEVICE "/dev/sda"
#define SCSI_OFF sizeof(struct sg_header)

static unsigned char cmd[SCSI_OFF + 18]; /* SCSI command buffer */
int fd; /* SCSI device/file descriptor */

/**
 * process a complete scsi cmd. Use the generic scsi interface.
 *
 * @cmd_len: command length
 * @in_size: input data size
 * @i_buff: input buffer
 * @out_size: output data size
 * @o_buff: output buffer
 */
static int handle_scsi_cmd(unsigned cmd_len, unsigned in_size,
			   unsigned char *i_buff, unsigned out_size,
			   unsigned char *o_buff)
{
	int status = 0;
	struct sg_header *sg_hd;

	/* safety checks */
	if (!cmd_len)
		return -1;
	if (!i_buff)
		return -1;

#ifdef SG_BIG_BUFF
	if (SCSI_OFF + cmd_len + in_size > SG_BIG_BUFF)
		return -1;
	if (SCSI_OFF + out_size > SG_BIG_BUFF)
		return -1;
#else
	if (SCSI_OFF + cmd_len + in_size > 4096)
		return -1;
	if (SCSI_OFF + out_size > 4096)
		return -1;
#endif

	if (!o_buff)
		out_size = 0;

	/* generic scsi device header construction */
	sg_hd = (struct sg_header *) i_buff;
	sg_hd->reply_len = SCSI_OFF + out_size;
	sg_hd->twelve_byte = cmd_len == 12;
	sg_hd->result = 0;

	/* send command */
	status = write(fd, i_buff, SCSI_OFF + cmd_len + in_size);
	if (status < 0 || status != SCSI_OFF + cmd_len + in_size || sg_hd->result) {
		/* some error happened */
		fprintf(stderr, "write(generic) result = 0x%x cmd = 0x%x\n",
			sg_hd->result, i_buff[SCSI_OFF]);
		perror("");
		return status;
	}

	/* buffer pointer check */
	if (!o_buff)
		o_buff = i_buff;

	/* retrieve result */
	status = read(fd, o_buff, SCSI_OFF + out_size);
	if (status < 0 || status != SCSI_OFF + out_size || sg_hd->result) {
		/* some error happened */
		fprintf(stderr, "read(generic) result = 0x%x cmd = 0x%x\n",
			sg_hd->result, o_buff[SCSI_OFF] );
		fprintf(stderr, "read(generic) sense "
			"%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x\n",
			sg_hd->sense_buffer[0], sg_hd->sense_buffer[1],
			sg_hd->sense_buffer[2], sg_hd->sense_buffer[3],
			sg_hd->sense_buffer[4], sg_hd->sense_buffer[5],
			sg_hd->sense_buffer[6], sg_hd->sense_buffer[7],
			sg_hd->sense_buffer[8], sg_hd->sense_buffer[9],
			sg_hd->sense_buffer[10],sg_hd->sense_buffer[11],
			sg_hd->sense_buffer[12],sg_hd->sense_buffer[13],
			sg_hd->sense_buffer[14],sg_hd->sense_buffer[15]);
		if (status < 0)
			perror("");
	}

	/* Look if we got what we expected to get */
	if (status == SCSI_OFF + out_size)
		status = 0;

	return status;
}

/* Offset in reply data to vendor name */
#define INQUIRY_CMD 0x12
#define INQUIRY_CMDLEN 6
#define INQUIRY_REPLY_LEN 96
#define INQUIRY_VENDOR 8

/* request vendor brand and model */
static unsigned char *Inquiry(void)
{
	static unsigned char Inqbuffer[SCSI_OFF + INQUIRY_REPLY_LEN];
	unsigned char cmdblk[INQUIRY_CMDLEN] = {
		INQUIRY_CMD,  /* command */
		0,  /* lun/reserved */
		0,  /* page code */
		0,  /* reserved */
		INQUIRY_REPLY_LEN,  /* allocation length */
		0 };/* reserved/flag/link */

	memcpy(cmd + SCSI_OFF, cmdblk, sizeof(cmdblk));

	/*
	 * +------------------+
	 * | struct sg_header | <- cmd
	 * +------------------+
	 * | copy of cmdblk   | <- cmd + SCSI_OFF
	 * +------------------+
	 */

	if (handle_scsi_cmd(sizeof(cmdblk), 0, cmd, sizeof(Inqbuffer) - SCSI_OFF, Inqbuffer)) {
		fprintf(stderr, "Inquiry failed\n");
		exit(2);
	}
	return (Inqbuffer + SCSI_OFF);
}

#define TESTUNITREADY_CMD 0
#define TESTUNITREADY_CMDLEN 6

#define ADD_SENSECODE 12
#define ADD_SC_QUALIFIER 13
#define NO_MEDIA_SC 0x3a
#define NO_MEDIA_SCQ 0x00

int TestForMedium(void)
{
	/* request READY status */
	static unsigned char cmdblk[TESTUNITREADY_CMDLEN] = {
		TESTUNITREADY_CMD, /* command */
		0, /* lun/reserved */
		0, /* reserved */
		0, /* reserved */
		0, /* reserved */
		0};/* reserved */

	memcpy(cmd + SCSI_OFF, cmdblk, sizeof(cmdblk));

	/*
	 * +------------------+
	 * | struct sg_header | <- cmd
	 * +------------------+
	 * | copy of cmdblk   | <- cmd + SCSI_OFF
	 * +------------------+
	 */

	if (handle_scsi_cmd(sizeof(cmdblk), 0, cmd, 0, NULL)) {
		fprintf(stderr, "Test unit ready failed\n");
		exit(2);
	}

	return *(((struct sg_header*)cmd)->sense_buffer +ADD_SENSECODE) != NO_MEDIA_SC ||
	 *(((struct sg_header*)cmd)->sense_buffer +ADD_SC_QUALIFIER) != NO_MEDIA_SCQ;
}

int main(void)
{
	fd = open(DEVICE, O_RDWR);
	if (fd < 0) {
		fprintf( stderr, "Need read/write permissions for "DEVICE".\n" );
		exit(1);
	}

	/* print some fields of the Inquiry result */
	printf("%s\n", Inquiry() + INQUIRY_VENDOR);

	/* look if medium is loaded */
	if (!TestForMedium()) {
		printf("device is unloaded\n");
	} else {
		printf("device is loaded\n");
	}

	return 0;
}
