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
	uint8_t revision;
	uint8_t checksum;
	uint8_t oem_id[6];
	uint8_t oem_table_id[8];
	uint32_t oem_revision;
	uint32_t creator_id;
	uint32_t creator_revision;
	uint8_t cedt_structure[];
} __attribute__((packed));

/**
 * CXL 2.0 Specification, Section 9.14.1.2
 * CXL Host Bridge Structure (CHBS)
 */
struct chbs {
	uint8_t type;
	uint8_t reserved;
	uint16_t record_length;
	uint32_t uid;
	/**
	 * 00h: CXL 1.1 Specification compliant Host Bridge
	 * 01h: CXL 2.0 Specification compliant Host Bridge
	 */
	uint32_t cxl_version;
	uint32_t reserved2;
	/**
	 * If Version = 0, this represents the base address of
	 * CXL 1.1 Downstream Port RCRB.
	 *
	 * If version =1, this represents the base address of
	 * the CXL 2.0 CHBCR.
	 */
	uint64_t base;
	uint64_t length;
} __attribute__((packed));

void display_chbs(struct chbs *chbs)
{
	printf("CHBS type %2d, len %4d, uid %4x, CXL version %2x, base %lx len %lx\n",
		chbs->type, chbs->record_length, chbs->uid,
		chbs->cxl_version, chbs->base, chbs->length);
}

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
	printf("struct cedt_hdr size %d\n", sizeof(struct cedt_hdr));
	printf("struct chbs size %d\n", sizeof(struct chbs));
}

int main(void)
{
	FILE *fp;
	struct cedt_hdr hdr;
	struct chbs chbs;

	fp = fopen(FILE_CEDT, "r");
	if (!fp) {
		fprintf(stderr, "fopen(%s) failed, %m.\n", FILE_CEDT);
		return -errno;
	}

	fread(&hdr, sizeof(hdr), 1, fp);
	display_cedt_hdr(&hdr);

	/* TODO: only handle one CHBS */
	if (hdr.length > sizeof(hdr) + sizeof(chbs)) {
		fread(&chbs, sizeof(chbs), 1, fp);
		display_chbs(&chbs);
	}

	fclose(fp);
	return 0;
}
