#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>


int main(void)
{
	char *path;
	int fd;
	unsigned char *mbr;
	unsigned char *primary_gpt_hdr;
	void *hdr;

	path = "/dev/nvme0n1";

	fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	/* MBR: 512 bytes */
	mbr = malloc(512);
	primary_gpt_hdr = malloc(0x5c);

	read(fd, mbr, 512);
	read(fd, primary_gpt_hdr, 0x5c);

	hdr = primary_gpt_hdr;
	uint64_t signature = *(uint64_t *)hdr;
	hdr += sizeof(signature);
	uint32_t revision_number = *(uint32_t *)(hdr);
	hdr += sizeof(revision_number);
	uint32_t hdr_size = *(uint32_t *)hdr;
	hdr += sizeof(hdr_size);
	uint32_t hdr_crc32 = *(uint32_t *)hdr;
	hdr += sizeof(hdr_crc32);
	hdr += 4; /* Reserved */

	/* TODO: More */

	/**
	 * "EFI PART" = 45h 46h 49h 20h 50h 41h 52h 54h
	 *            = 0x5452415020494645ULL
	 */
	if (signature == 0x5452415020494645ULL)
		printf("Partition Table: GPT\n");
	/**
	 * 00h 00h 01h 00h
	 */
	if (revision_number == 0x00010000U)
		printf("Revision 1.0 for UEFI 2.0\n");

	printf("Header Size: %d bytes\n", hdr_size);
	printf("Header CRC32: %#08x\n", hdr_crc32);

	close(fd);
	return 0;
}
