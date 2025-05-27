#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <byteswap.h>

#include "qcow2_helpers.h"

int qcowhdr_check_magic(QCowHeader *hdr)
{
	if (bswap_32(hdr->magic) != QCOW_MAGIC) {
		fprintf(stderr, "qcow2 bad magic %x\n", bswap_32(hdr->magic));
		return -EINVAL;
	}
	return 0;
}

void display_qcowhdr(QCowHeader *hdr)
{
	if (qcowhdr_check_magic(hdr))
		return;
	printf("version %d\n", bswap_32(hdr->version));
	printf("virtual size %ld GiB (%ld bytes)\n",
		bswap_64(hdr->size) / 1024 / 1024 / 1024, bswap_64(hdr->size));
	/* TODO: display more */
}
