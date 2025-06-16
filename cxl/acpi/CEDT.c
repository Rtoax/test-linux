/**
 * CXL Early Discovery Table (CEDT)
 */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define FILE_CEDT	"/sys/firmware/acpi/tables/CEDT"

/**
 * CXL 2.0 Specification, Section 9.14.1
 */
struct cedt_hdr {
	uint32_t signature; /* CEDT */
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

int main(void)
{
	if (access(FILE_CEDT, F_OK)) {
		fprintf(stderr, "%s is not exist.\n", FILE_CEDT);
		return -1;
	}
	return 0;
}
