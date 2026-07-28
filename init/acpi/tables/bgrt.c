/**
 * ACPI BGRT: Boot Graphics Resource Table
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
	char Signature[4]; // "BGRT"
	uint32_t Length;
	uint8_t Revision;
	uint8_t Checksum;
	char OEMID[6];
	char OEMTableID[8];
	uint32_t OEMRevision;
	uint32_t CreatorID;
	uint32_t CreatorRevision;
} ACPI_TABLE_HEADER;

typedef struct {
	uint16_t Version;
	uint8_t Status; // 0=disable, 1=enable
	uint8_t ImageType; // 0=BMP
	uint64_t ImageAddress;
	uint32_t ImageOffsetX;
	uint32_t ImageOffsetY;
} ACPI_BGRT;

int main(void)
{
	ACPI_TABLE_HEADER hdr;
	ACPI_BGRT bgrt;

	FILE *fp = fopen("/sys/firmware/acpi/tables/BGRT", "rb");
	if (!fp) {
		perror("fopen BGRT");
		return 1;
	}

	if (fread(&hdr, 1, sizeof(hdr), fp) != sizeof(hdr)) {
		fprintf(stderr, "Failed to read ACPI header, %m\n");
		fclose(fp);
		return 1;
	}

	if (memcmp(hdr.Signature, "BGRT", 4) != 0) {
		fprintf(stderr, "Not a BGRT table, %m\n");
		fclose(fp);
		return 1;
	}

	if (fread(&bgrt, 1, sizeof(bgrt), fp) != sizeof(bgrt)) {
		fprintf(stderr, "Failed to read BGRT body, %m\n");
		fclose(fp);
		return 1;
	}
	fclose(fp);

	printf("BGRT Version : %u\n", bgrt.Version);
	printf("Status	     : %u (%s)\n", bgrt.Status,
	       bgrt.Status ? "valid" : "invalid");
	printf("Image Type   : %u (0 = BMP)\n", bgrt.ImageType);
	printf("Image Physical Address : 0x%llx\n",
	       (unsigned long long)bgrt.ImageAddress);
	printf("Display Offset : X=%u, Y=%u\n", bgrt.ImageOffsetX,
	       bgrt.ImageOffsetY);

	return 0;
}
