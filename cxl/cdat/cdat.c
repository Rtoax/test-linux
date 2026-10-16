// SPDX-License-Identifier: GPL-3.0
// Copyright (C) 2026 Rong Tao. All rights reserved.
/**
 * CXL CDAT (Coherent Device Attribute Table) Structure
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "cdat.h"

static const char *cdat_type_name(enum cdat_type t)
{
	switch (t) {
#define C(t)                \
	case CDAT_TYPE_##t: \
		return "" #t
		C(DSMAS);
		C(DSLBIS);
		C(DSMSCIS);
		C(DSIS);
		C(DSEMTS);
		C(SSLBIS);
	default:
		return "Unknown type";
	}
}

static int probe_type(FILE *fp)
{
	uint8_t type;
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

void print_cdat_sub_hdr(const CDATSubHeader *h, int namewidth)
{
	printf("\033[1;3;7m%*s : %#02x [%s]\033[m\n", namewidth,
	       "Structure Type", h->type, cdat_type_name(h->type));
	printf("%*s : %#02x\n", namewidth, "Reserved", h->reserved);
	printf("%*s : %#04x              <- %dd, size of structure\n",
	       namewidth, "Length", h->length, h->length);
}

void print_cdat_dsmas(const CDATDsmas *d)
{
	int width = sizeof("   DSMADHandle");
	/* Format: https://docs.kernel.org/driver-api/cxl/platform/cdat.html */
	print_cdat_sub_hdr(&d->header, width);
	printf("%*s : %#02x\n", width, "DSMADHandle", d->DSMADhandle);
	printf("%*s : %#02x\n", width, "Flags", d->flags);
	printf("%*s : %#04x\n", width, "Reserved", d->reserved);
	printf("%*s : %#016lx  <- %ldGiB base\n", width, "DPA Base",
	       d->DPA_base, d->DPA_base / 1024 / 1024 / 1024);
	printf("%*s : %#016lx  <- %ldGiB size\n", width, "DPA Length",
	       d->DPA_length, d->DPA_length / 1024 / 1024 / 1024);
}

void print_cdat_dslbis(const CDATDslbis *d)
{
	int width = sizeof("          Handle");

	/* Format: https://docs.kernel.org/driver-api/cxl/platform/cdat.html */
	print_cdat_sub_hdr(&d->header, width);
	printf("%*s : %04x                   <- DSMAS handle\n", width,
	       "Handle", d->handle);
	printf("%*s : %02x                     <- Matches flag field for HMAT SLLBIS\n",
	       width, "Flags", d->flags);
	printf("%*s : %02x                     <- Latency\n", width,
	       "Data Type", d->data_type);
	printf("%*s : %016lx       <- Entry Base Unit field in HMAT SSLBIS\n",
	       width, "Entry Basee Unit", d->entry_base_unit);
	printf("%*s : %04x%04x%04x           <- First byte used here, CXL LTC\n",
	       width, "Entry", d->entry[0], d->entry[1], d->entry[2]);
	printf("%*s : %04x\n", width, "Entry", d->reserved2);
}

void print_cdat_dsemts(const CDATDsemts *d)
{
	int width = sizeof("          Handle");

	/* Format: https://docs.kernel.org/driver-api/cxl/platform/cdat.html */
	print_cdat_sub_hdr(&d->header, width);
	printf("%*s : %04x              <- DSMAS handle\n", width, "Handle",
	       d->DSMAS_handle);
	printf("%*s : %02x\n", width, "EFI Memory Type",
	       d->EFI_memory_type_attr);
	printf("%*s : %#016lx  <- %ldGiB offset\n", width, "DPA Offset",
	       d->DPA_offset, d->DPA_offset / 1024 / 1024 / 1024);
	printf("%*s : %#016lx  <- %ldGiB size\n", width, "DPA Length",
	       d->DPA_length, d->DPA_length / 1024 / 1024 / 1024);
}

void print_cdat_sslbe(const CDATSslbe *s, int namewidth)
{
	printf("%*s : %04x                         <- First port, 0100h represents an upstream port\n",
	       namewidth, "Port X ID", s->port_x_id);
	printf("%*s : %04x                         <- Second port, downstream port 0\n",
	       namewidth, "Port Y ID", s->port_y_id);
	printf("%*s : %04x                         <- Port latency\n",
	       namewidth, "Latency", s->latency_bandwidth);
}

void print_cdat_sslbis(const CDATSslbis *d)
{
	int width = sizeof("      Data Type");

	/* Format: https://docs.kernel.org/driver-api/cxl/platform/cdat.html */
	print_cdat_sub_hdr(&d->sslbis_header.header, width);

	printf("%*s : %02x                           <- Latency\n", width,
	       "Data Type", d->sslbis_header.data_type);
	printf("%*s : %02x%02x%02x\n", width, "Reserved",
	       d->sslbis_header.reserved[0], d->sslbis_header.reserved[1],
	       d->sslbis_header.reserved[2]);
	printf("%*s : %016lx         <- Matches Entry Base Unit in HMAT SSLBIS\n",
	       width, "Entry Base Unit", d->sslbis_header.entry_base_unit);

	int nr_sslbe = (d->sslbis_header.header.length - sizeof(CDATSslbis)) /
		       sizeof(CDATSslbe);
	for (int i = 0; i < nr_sslbe; i++) {
		printf("%*s\n", width, "SSLB Entry");
		print_cdat_sslbe(&d->sslbe[i], width);
	}
}

int main(int argc, char *argv[])
{
	FILE *fp;
	char *file;
	struct cdat_tab_hdr hdr;
	struct stat st;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s [cdat file path]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	file = argv[1];

	fp = fopen(file, "r");
	if (!fp) {
		fprintf(stderr, "fopen(%s) failed, %m.\n", file);
		return -errno;
	}

	stat(file, &st);
	printf("File size %ld\n", st.st_size);

	fread(&hdr, sizeof(hdr), 1, fp);
	printf("HDR: len %d, revision %u, chksum %u, seq %x\n", hdr.length,
	       hdr.revision, hdr.checksum, hdr.sequence);

	while (!feof(fp)) {
		int type = probe_type(fp);
		if (type == -1)
			break;
		switch (type) {
		case CDAT_TYPE_DSMAS: {
			CDATDsmas dsmas;
			fread(&dsmas, sizeof(dsmas), 1, fp);
			print_cdat_dsmas(&dsmas);
			break;
		}
		case CDAT_TYPE_DSLBIS: {
			CDATDslbis dslbis;
			fread(&dslbis, sizeof(dslbis), 1, fp);
			print_cdat_dslbis(&dslbis);
			break;
		}
		case CDAT_TYPE_DSEMTS: {
			CDATDsemts s;
			fread(&s, sizeof(s), 1, fp);
			print_cdat_dsemts(&s);
			break;
		}
		case CDAT_TYPE_SSLBIS: {
			CDATSslbis s;
			fread(&s, sizeof(s), 1, fp);
			print_cdat_sslbis(&s);
			break;
		}
		case CDAT_TYPE_DSMSCIS:
		case CDAT_TYPE_DSIS:
		default:
			fprintf(stderr,
				"\033[31mNot support parse %s(%d) yet\033[m\n",
				cdat_type_name(type), type);
			goto done;
			break;
		}
	}

done:
	fclose(fp);
	return 0;
}
