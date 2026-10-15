// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
/**
 * ACPI SRAT: System Resource Affinity Table
 *
 *
 * Refs:
 * - ACPI Specification, Release 6.5
 *   5.2.16 System Resource Affinity Table (SRAT)
 */
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
	char Signature[4]; /* "SRAT" */
	uint32_t Length;
	uint8_t Revision;
	uint8_t Checksum;
	char OEMID[6];
	char OEMTableID[8];
	uint32_t OEMRevision;
	uint32_t CreatorID;
	uint32_t CreatorRevision;
	uint32_t reserved1;
	uint64_t reserved2;
} __attribute__((packed)) SRAT_HEADER;

typedef struct {
	uint8_t Type; /* must be 0 */
	uint8_t Length;
	uint8_t ProximityDomain[1];
	uint8_t APIC_ID;
	uint32_t Flags;
	uint8_t Local_SAPIC_EID;
	uint8_t ProximityDomain2[3];
	uint32_t ClockDomain;
} __attribute__((packed)) ProcessorLocalAPICAffinity;

typedef struct {
	uint8_t Type; /* must be 1 */
	uint8_t Length;
	uint8_t ProximityDomain[4];
	uint8_t reserved[2];
	uint32_t BaseAddressLow;
	uint32_t BaseAddressHigh;
	uint32_t LengthLow;
	uint32_t LengthHigh;
	uint32_t reserved1;
	uint32_t Flags;
	uint64_t reserved2;
} __attribute__((packed)) MemoryAffinity;

static int probe_type(FILE *fp)
{
	int8_t type;
	fpos_t old_pos;

	if (feof(fp))
		return -1;

	fgetpos(fp, &old_pos);
	fread(&type, 1, 1, fp);
	if (feof(fp)) {
		fsetpos(fp, &old_pos);
		return -1;
	}
	fsetpos(fp, &old_pos);
	return type;
}

void display_processor_local_APIC_affinity(ProcessorLocalAPICAffinity *a)
{
	printf("\033[1;3;7mProcessorLocalAPICAffinity\033[m\n");
	printf("[lapic] %u %u.%u.%u.%u id %u flags %x EID %u clk %x\n",
	       a->Length, a->ProximityDomain[0], a->ProximityDomain2[0],
	       a->ProximityDomain2[0], a->ProximityDomain2[2], a->APIC_ID,
	       a->Flags, a->Local_SAPIC_EID, a->ClockDomain);
}

void display_memory_affinity(MemoryAffinity *a)
{
	printf("\033[1;3;7mMemoryAffinity\033[m\n");
	printf("[memory] %u %u.%u.%u.%u addr %x~%x len %x~%x, flags %x\n",
	       a->Length, a->ProximityDomain[0], a->ProximityDomain[1],
	       a->ProximityDomain[2], a->ProximityDomain[3], a->BaseAddressLow,
	       a->BaseAddressHigh, a->LengthLow, a->LengthHigh, a->Flags);
}

int main(void)
{
	int err = 0;
	SRAT_HEADER hdr;

	FILE *fp = fopen("/sys/firmware/acpi/tables/SRAT", "rb");
	if (!fp) {
		perror("fopen SRAT");
		return 1;
	}

	if (fread(&hdr, 1, sizeof(hdr), fp) != sizeof(hdr)) {
		fprintf(stderr, "Failed to read ACPI header, %m\n");
		fclose(fp);
		return 1;
	}

	if (memcmp(hdr.Signature, "SRAT", 4) != 0) {
		fprintf(stderr, "Not a SRAT table, %m\n");
		fclose(fp);
		return 1;
	}

	printf("SRAT Header  : %ld\n", sizeof(SRAT_HEADER));
	printf("SRAT Sign    : %c%c%c%c\n", hdr.Signature[0], hdr.Signature[1],
	       hdr.Signature[2], hdr.Signature[3]);
	printf("SRAT Length  : %d\n", hdr.Length);

	while (1) {
		int8_t type = probe_type(fp);
		if (type == -1)
			break;
		switch (type) {
		case 0: {
			ProcessorLocalAPICAffinity aff;
			fread(&aff, 1, sizeof(aff), fp);
			display_processor_local_APIC_affinity(&aff);
			break;
		}
		case 1: {
			MemoryAffinity aff;
			fread(&aff, 1, sizeof(aff), fp);
			display_memory_affinity(&aff);
			break;
		}
		default:
			fprintf(stderr, "Unknown type %u\n", type);
			err = -ENOENT;
			goto done;
		}
	}

done:
	fclose(fp);

	return err;
}
