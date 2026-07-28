// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2025-2026 Rong Tao
/**
 * CXL Early Discovery Table (CEDT)
 * ACPI0017 CXL Root Object
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h>
#include "cedt.h"
#include "chbs.h"
#include "cfmws.h"

void display_cedt_hdr(struct cedt_hdr *hdr)
{
	if (hdr->signature[0] != 'C' || hdr->signature[1] != 'E' ||
	    hdr->signature[2] != 'D' || hdr->signature[3] != 'T') {
		fprintf(stderr, "Header is not CEDT.\n");
		return;
	}

	printf("CEDT length %d\n", hdr->length);
	printf("Signature: %c%c%c%c\n", hdr->signature[0], hdr->signature[1],
	       hdr->signature[2], hdr->signature[3]);
	printf("Revision 0x%x\n", hdr->revision);
	printf("Checksum 0x%x\n", hdr->checksum);
	printf("OEM ID '%c%c%c%c%c%c'(raw:%02x%02x%02x%02x%02x%02x)\n",
	       hdr->oem_id[0], hdr->oem_id[1], hdr->oem_id[2], hdr->oem_id[3],
	       hdr->oem_id[4], hdr->oem_id[5], hdr->oem_id[0], hdr->oem_id[1],
	       hdr->oem_id[2], hdr->oem_id[3], hdr->oem_id[4], hdr->oem_id[5]);
	printf("OEM Table ID '%c%c%c%c%c%c%c%c'(raw:%02x%02x%02x%02x%02x%02x%02x%02x)\n",
	       hdr->oem_table_id[0], hdr->oem_table_id[1], hdr->oem_table_id[2],
	       hdr->oem_table_id[3], hdr->oem_table_id[4], hdr->oem_table_id[5],
	       hdr->oem_table_id[6], hdr->oem_table_id[7], hdr->oem_table_id[0],
	       hdr->oem_table_id[1], hdr->oem_table_id[2], hdr->oem_table_id[3],
	       hdr->oem_table_id[4], hdr->oem_table_id[5], hdr->oem_table_id[6],
	       hdr->oem_table_id[7]);
	printf("OEM Revision 0x%x\n", hdr->oem_revision);
	printf("Creator ID 0x%x\n", hdr->creator_id);
	printf("Creator Revision 0x%x\n", hdr->creator_revision);
	printf("CEDT structure size %ld\n", hdr->length - sizeof(*hdr));
	printf("struct cedt header size %ld\n", sizeof(struct cedt_hdr));
	printf("struct chbs size %ld\n", sizeof(struct chbs));
	printf("struct cfmws size %ld\n", sizeof(struct cfmws));
}

static int probe_structure_type(FILE *fp)
{
	uint8_t type;
	fpos_t old_pos;

	fgetpos(fp, &old_pos);
	fread(&type, 1, 1, fp);
	if (feof(fp))
		return -1;
	fsetpos(fp, &old_pos);
	return type;
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

	while (1) {
		int type = probe_structure_type(fp);
		if (type == -1)
			break;
		switch (type) {
		case CEDT_STRUCTURE_TYPE_CHBS: {
			struct chbs chbs;
			fread(&chbs, sizeof(chbs), 1, fp);
			display_chbs(&chbs);
			break;
		}
		case CEDT_STRUCTURE_TYPE_CFMWS: {
			struct cfmws tmp, *cfmws;
			fpos_t old_pos;
			fgetpos(fp, &old_pos);
			fread(&tmp, sizeof(struct cfmws), 1, fp);
			cfmws = malloc(tmp.record_length);
			fsetpos(fp, &old_pos);
			fread(cfmws, tmp.record_length, 1, fp);
			display_cfmws(cfmws);
			free(cfmws);
			break;
		}
		default:
			fprintf(stderr, "Unknown CEDT structure type %d\n",
				type);
			goto done;
		}
	}

done:
	fclose(fp);
	return 0;
}
