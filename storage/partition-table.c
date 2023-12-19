#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>


struct gpt_hdr {
	uint64_t signature;
	uint32_t revision_number;
	uint32_t size;
	uint32_t crc32;
	uint32_t reserved1;
	uint64_t current_lba;
	uint64_t backup_lba;
	uint64_t first_usable_lba;
	uint64_t last_usable_lba;
	uint8_t  guid[16];
	/* more */
} __attribute__((packed));

char *try_disks[] = {
	"/dev/nvme0n1",
	"/dev/vdb",
	NULL
};

int main(void)
{
	char *path;
	int i, fd = -1;
	unsigned char *mbr;
	unsigned char *primary_gpt_hdr;
	struct gpt_hdr *hdr;

	for (i = 0; try_disks[i]; i++) {
		path = try_disks[i];
		fd = open(path, O_RDONLY);
		if (fd == -1 && errno == ENOENT) {
			printf("open(%s) %s\n", path, strerror(errno));
			continue;
		} else if (fd == -1 && errno == EPERM) {
			printf("open(%s) %s\n", path, strerror(errno));
			return 1;
		}
	}

	if (fd == -1) {
		printf("open(%s) %s\n", path, strerror(errno));
		return 1;
	}

	/* MBR: 512 bytes */
	mbr = malloc(512);
	primary_gpt_hdr = malloc(0x5c);

	read(fd, mbr, 512);
	read(fd, primary_gpt_hdr, 0x5c);

	hdr = (struct gpt_hdr *)primary_gpt_hdr;

	/**
	 * "EFI PART" = 45h 46h 49h 20h 50h 41h 52h 54h
	 *            = 0x5452415020494645ULL
	 */
	if (hdr->signature == 0x5452415020494645ULL)
		printf("Partition Table: GPT\n");
	/**
	 * 00h 00h 01h 00h
	 */
	if (hdr->revision_number == 0x00010000U)
		printf("Revision 1.0 for UEFI 2.0\n");

	printf("Header Size: %d bytes\n", hdr->size);
	printf("Header CRC32: %#08x\n", hdr->crc32);

	printf("GUID: ");
	for (i = 0; i < sizeof(hdr->guid); i++) {
		unsigned char ch = hdr->guid[i];
		printf("%02x", ch);
	} printf("\n");


	close(fd);
	return 0;
}
