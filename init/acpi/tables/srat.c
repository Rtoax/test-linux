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
#include <stdlib.h>

#define SRAT_TAB "/sys/firmware/acpi/tables/SRAT"

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

typedef struct {
	uint8_t Type; /* must be 2 */
	uint8_t Length;
	uint8_t reserved[2];
	uint8_t ProximityDomain[4];
	uint8_t X2APIC_ID;
	uint32_t Flags;
	uint32_t ClockDomain;
	uint8_t reserved1[4];
} __attribute__((packed)) ProcessorLocalX2APICAffinity;

typedef struct {
	uint8_t Type; /* must be 3 */
	uint8_t Length;
	uint8_t ProximityDomain[4];
	uint32_t ACPI_Processor_ID;
	uint32_t Flags;
	uint32_t ClockDomain;
} __attribute__((packed)) GICCAffinity;

typedef struct {
	uint8_t Type; /* must be 4 */
	uint8_t Length;
	uint8_t ProximityDomain[4];
	uint8_t reserved[2];
	uint32_t ITS_ID;
} __attribute__((packed)) ArchitectureSpecificAffinity;

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
	printf("\033[1;3;7mProcessor Local APIC/SAPIC Affinity Structure\033[m\n");
	printf("[lapic] %u %u.%u.%u.%u id %u flags %x EID %u clk %x\n",
	       a->Length, a->ProximityDomain[0], a->ProximityDomain2[0],
	       a->ProximityDomain2[1], a->ProximityDomain2[2], a->APIC_ID,
	       a->Flags, a->Local_SAPIC_EID, a->ClockDomain);
}

void display_memory_affinity(MemoryAffinity *a)
{
	printf("\033[1;3;7mMemory Affinity\033[m\n");
	printf("[memory] %u %u.%u.%u.%u addr %x~%x len %x~%x, flags %x\n",
	       a->Length, a->ProximityDomain[0], a->ProximityDomain[1],
	       a->ProximityDomain[2], a->ProximityDomain[3], a->BaseAddressLow,
	       a->BaseAddressHigh, a->LengthLow, a->LengthHigh, a->Flags);
}

void display_processor_local_X2APIC_affinity(ProcessorLocalX2APICAffinity *a)
{
	printf("\033[1;3;7mProcessor Local x2APIC Affinity Structure\033[m\n");
	printf("[lx2apic] %u %u.%u.%u.%u id %u flags %x clk %x\n", a->Length,
	       a->ProximityDomain[0], a->ProximityDomain[1],
	       a->ProximityDomain[2], a->ProximityDomain[3], a->X2APIC_ID,
	       a->Flags, a->ClockDomain);
}

void display_GICC_affinity(GICCAffinity *a)
{
	printf("\033[1;3;7mGICC Affinity\033[m\n");
	printf("[GICC] %u %u.%u.%u.%u id %u flags %x clk %x\n", a->Length,
	       a->ProximityDomain[0], a->ProximityDomain[1],
	       a->ProximityDomain[2], a->ProximityDomain[3],
	       a->ACPI_Processor_ID, a->Flags, a->ClockDomain);
}

void display_arch_specific_affinity(ArchitectureSpecificAffinity *a)
{
	printf("\033[1;3;7mArchitecture Specific Affinity\033[m\n");
	printf("[arch] %u %u.%u.%u.%u ITS %d\n", a->Length,
	       a->ProximityDomain[0], a->ProximityDomain[1],
	       a->ProximityDomain[2], a->ProximityDomain[3], a->ITS_ID);
}

int main(void)
{
	int err = 0;
	SRAT_HEADER hdr;

	printf("Parsing %s\n", SRAT_TAB);
	FILE *fp = fopen(SRAT_TAB, "rb");
	if (!fp) {
		fprintf(stderr, "open %s failed, %m\n", SRAT_TAB);
		exit(EXIT_FAILURE);
	}

	if (fread(&hdr, 1, sizeof(hdr), fp) != sizeof(hdr)) {
		fprintf(stderr, "Failed to read ACPI header, %m\n");
		fclose(fp);
		exit(EXIT_FAILURE);
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
		case 2: {
			ProcessorLocalX2APICAffinity aff;
			fread(&aff, 1, sizeof(aff), fp);
			display_processor_local_X2APIC_affinity(&aff);
			break;
		}
		case 3: {
			GICCAffinity aff;
			fread(&aff, 1, sizeof(aff), fp);
			display_GICC_affinity(&aff);
			break;
		}
		case 4: {
			ArchitectureSpecificAffinity aff;
			fread(&aff, 1, sizeof(aff), fp);
			display_arch_specific_affinity(&aff);
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
