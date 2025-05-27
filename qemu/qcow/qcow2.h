/**
 * see qemu/block/qcow2.h
 */
#pragma once
#include <stdint.h>
#include <sys/types.h>

#define QEMU_PACKED __attribute__((packed))
#define QCOW_MAGIC (('Q' << 24) | ('F' << 16) | ('I' << 8) | 0xfb)

/* Incompatible feature bits */
enum {
	QCOW2_INCOMPAT_DIRTY_BITNR	= 0,
	QCOW2_INCOMPAT_CORRUPT_BITNR	= 1,
	QCOW2_INCOMPAT_DATA_FILE_BITNR	= 2,
	QCOW2_INCOMPAT_COMPRESSION_BITNR= 3,
	QCOW2_INCOMPAT_EXTL2_BITNR	= 4,
	QCOW2_INCOMPAT_DIRTY		= 1 << QCOW2_INCOMPAT_DIRTY_BITNR,
	QCOW2_INCOMPAT_CORRUPT		= 1 << QCOW2_INCOMPAT_CORRUPT_BITNR,
	QCOW2_INCOMPAT_DATA_FILE	= 1 << QCOW2_INCOMPAT_DATA_FILE_BITNR,
	QCOW2_INCOMPAT_COMPRESSION	= 1 << QCOW2_INCOMPAT_COMPRESSION_BITNR,
	QCOW2_INCOMPAT_EXTL2		= 1 << QCOW2_INCOMPAT_EXTL2_BITNR,

	QCOW2_INCOMPAT_MASK	= QCOW2_INCOMPAT_DIRTY
				| QCOW2_INCOMPAT_CORRUPT
				| QCOW2_INCOMPAT_DATA_FILE
				| QCOW2_INCOMPAT_COMPRESSION
				| QCOW2_INCOMPAT_EXTL2,
};

typedef struct QCowHeader {
	uint32_t magic;
	uint32_t version;
	uint64_t backing_file_offset;
	uint32_t backing_file_size;
	uint32_t cluster_bits;
	uint64_t size; /* in bytes */
	uint32_t crypt_method;
	uint32_t l1_size; /* XXX: save number of clusters instead ? */
	uint64_t l1_table_offset;
	uint64_t refcount_table_offset;
	uint32_t refcount_table_clusters;
	uint32_t nb_snapshots;
	uint64_t snapshots_offset;

	/* The following fields are only valid for version >= 3 */
	uint64_t incompatible_features;
	uint64_t compatible_features;
	uint64_t autoclear_features;

	uint32_t refcount_order;
	uint32_t header_length;

	/* Additional fields */
	uint8_t compression_type;

	/* header must be a multiple of 8 */
	uint8_t padding[7];
} QEMU_PACKED QCowHeader;
