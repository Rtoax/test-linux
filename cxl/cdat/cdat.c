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
		switch (type) {
		case CDAT_TYPE_DSMAS: {
			CDATDsmas dsmas;
			fread(&dsmas, sizeof(dsmas), 1, fp);
			printf("%s: len %d\n",
			       cdat_type_name(dsmas.header.type),
			       dsmas.header.length);
			break;
		}
		case CDAT_TYPE_DSLBIS:
		case CDAT_TYPE_DSMSCIS:
		case CDAT_TYPE_DSIS:
		case CDAT_TYPE_DSEMTS:
		case CDAT_TYPE_SSLBIS:
		default:
			fprintf(stderr, "Not support parse %s yet\n",
				cdat_type_name(type));
			goto done;
			break;
		}
	}

done:
	fclose(fp);
	return 0;
}
