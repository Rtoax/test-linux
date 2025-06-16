/**
 * CXL Early Discovery Table (CEDT)
 */
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>

#define FILE_CEDT	"/sys/firmware/acpi/tables/CEDT"

/**
 * CXL 2.0 Specification, Section 9.14.1
 */
struct cedt_hdr {
	uint8_t signature[4]; /* CEDT */
	uint32_t length;
	uint16_t revision;
	uint8_t checksum;
	uint8_t oem_id[6];
	uint8_t oem_table_id[8];
	uint32_t oem_revision;
	uint32_t creator_id;
	uint32_t creator_revision;
	uint8_t cedt_structure[];
};

void display_cedt_hdr(struct cedt_hdr *hdr)
{
	if (hdr->signature[0] != 'C' || hdr->signature[1] != 'E' ||
	    hdr->signature[2] != 'D' || hdr->signature[3] != 'T') {
		fprintf(stderr, "Header is not CEDT.\n");
		return;
	}
	printf("CEDT length %d\n", hdr->length);
	printf("Revision 0x%x\n", hdr->revision);
	printf("Checksum 0x%x\n", hdr->checksum);
	printf("OEM ID %02x%02x%02x%02x%02x%02x\n",
		hdr->oem_id[0], hdr->oem_id[1],
		hdr->oem_id[2], hdr->oem_id[3],
		hdr->oem_id[4], hdr->oem_id[5]);
	printf("OEM Table ID %02x%02x%02x%02x%02x%02x%02x%02x\n",
		hdr->oem_table_id[0], hdr->oem_table_id[1],
		hdr->oem_table_id[2], hdr->oem_table_id[3],
		hdr->oem_table_id[4], hdr->oem_table_id[5],
		hdr->oem_table_id[6], hdr->oem_table_id[7]);
	printf("OEM revision 0x%x\n", hdr->oem_revision);
	printf("Creator ID 0x%x\n", hdr->creator_id);
	printf("Creator revision 0x%x\n", hdr->creator_revision);
	printf("CEDT structure size %d\n", hdr->length - sizeof(*hdr));
}

int main(void)
{
	FILE *fp;
	struct cedt_hdr hdr;

	fp = fopen(FILE_CEDT, "r");
	if (!fp) {
		fprintf(stderr, "fopen(%s) failed, %m.\n", FILE_CEDT);
		return -errno;
	}

	fread(&hdr, sizeof(hdr), 1, fp);
	display_cedt_hdr(&hdr);

	fclose(fp);
	return 0;
}
