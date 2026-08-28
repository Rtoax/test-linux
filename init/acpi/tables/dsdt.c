/**
 * ACPI DSDT: Differentiated System Description Table
 *
 * Usage:
 * - CXL ACPI0016
 *
 * Refs:
 * - ACPI Specification, Release 6.5
 *   5.2.11.1 Differentiated System Description Table (DSDT)
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DSDT "/sys/firmware/acpi/tables/DSDT"

typedef struct {
	char Signature[4]; // "DSDT"
	uint32_t Length;
	uint8_t Revision;
	uint8_t Checksum;
	uint8_t OEMID[6];
	uint8_t OEMTabID[8];
	uint32_t OEMRevision;
	uint32_t CreatorID;
	uint32_t CreatorRevision;
	/* n bytes of AML code */
	uint8_t DefinitionBlock[];
} ACPI_DSDT;

int main(void)
{
	ACPI_DSDT dsdt;

	FILE *fp = fopen(DSDT, "rb");
	if (!fp) {
		perror("fopen " DSDT);
		return 1;
	}

	if (fread(&dsdt, 1, sizeof(dsdt), fp) != sizeof(dsdt)) {
		fprintf(stderr, "Failed to read ACPI header, %m\n");
		fclose(fp);
		return 1;
	}

	if (memcmp(dsdt.Signature, "DSDT", 4) != 0) {
		fprintf(stderr, "Not a DSDT table, %m\n");
		fclose(fp);
		return 1;
	}

	printf("DSDT Sign      : %c%c%c%c\n", dsdt.Signature[0],
	       dsdt.Signature[1], dsdt.Signature[2], dsdt.Signature[3]);
	printf("DSDT Length    : %d\n", dsdt.Length);
	printf("DSDT Revision  : %d\n", dsdt.Revision);
	printf("DSDT Checksum  : %d\n", dsdt.Checksum);
	printf("DSDT OEMID     : %c%c%c%c%c%c\n", dsdt.OEMID[0], dsdt.OEMID[1],
	       dsdt.OEMID[2], dsdt.OEMID[3], dsdt.OEMID[4], dsdt.OEMID[5]);
	printf("DSDT OEMTabID  : %c%c%c%c%c%c%c%c\n", dsdt.OEMTabID[0],
	       dsdt.OEMTabID[1], dsdt.OEMTabID[2], dsdt.OEMTabID[3],
	       dsdt.OEMTabID[4], dsdt.OEMTabID[5], dsdt.OEMTabID[6],
	       dsdt.OEMTabID[7]);
	printf("DSDT OEM Revision  : %d\n", dsdt.OEMRevision);
	printf("DSDT Creator ID : %d (0x%x)\n", dsdt.CreatorID, dsdt.CreatorID);
	printf("DSDT Creator Revision  : %d\n", dsdt.CreatorRevision);

	/**
	 * TODO: Parse DefinitionBlock[] AML
	 */

	fclose(fp);

	return 0;
}
