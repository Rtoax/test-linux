#pragma once

#define FILE_CEDT "/sys/firmware/acpi/tables/CEDT"

#define CEDT_STRUCTURE_TYPE_CHBS 0
/* CXL 3.0 added */
#define CEDT_STRUCTURE_TYPE_CFMWS 1
#define CEDT_STRUCTURE_TYPE_CXIMS 2
#define CEDT_STRUCTURE_TYPE_RDPAS 3

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
