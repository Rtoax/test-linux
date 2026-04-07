// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
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

	printf("backing_file_offset: 0x%lx\n", bswap_64(hdr->backing_file_offset));
	printf("backing_file_size: 0x%x\n", bswap_32(hdr->backing_file_size));

	printf("cluster_bits: 0x%x\n", bswap_32(hdr->cluster_bits));

	printf("crypt_method: 0x%x\n", bswap_32(hdr->crypt_method));

	printf("l1_size: %d\n", bswap_32(hdr->l1_size));
	printf("l1_table_offset: 0x%lx\n", bswap_64(hdr->l1_table_offset));

	printf("refcount_table_offset: 0x%lx\n", bswap_64(hdr->refcount_table_offset));
	printf("refcount_table_clusters: %d\n", bswap_32(hdr->refcount_table_clusters));

	printf("nb_snapshots: %d\n", bswap_32(hdr->nb_snapshots));
	printf("snapshots_offset: 0x%lx\n", bswap_64(hdr->snapshots_offset));

	printf("incompatible_features: 0x%lx\n", bswap_64(hdr->incompatible_features));
	printf("compatible_features: 0x%lx\n", bswap_64(hdr->compatible_features));

	printf("autoclear_features: 0x%lx\n", bswap_64(hdr->autoclear_features));

	printf("refcount_order: %d\n", bswap_32(hdr->refcount_order));
	printf("header_length: %d\n", bswap_32(hdr->header_length));

	printf("compression_type: %d\n", hdr->compression_type);
}
