#pragma once
/**
 * gpt: GUID partition table
 * LBA: logical block addressing
 *
 * refs:
 * - https://en.wikipedia.org/wiki/GUID_Partition_Table
 * - https://en.wikipedia.org/wiki/Master_boot_record
 */
#include <stdint.h>

struct gpt_hdr {
	uint64_t signature;
	uint32_t revision_number;
	uint32_t size;
	uint32_t hdr_crc32;
	uint32_t reserved1;
	uint64_t current_lba;
	uint64_t backup_lba;
	uint64_t first_usable_lba;
	uint64_t last_usable_lba;
	uint8_t  guid[16];
	/* Starting LBA of array of partition entries (usually 2 for compatibility) */
	uint64_t start_lba;
	uint32_t nr_partition_entries;
	/* Size of a single partition entry (usually 80h or 128) */
	uint32_t sz_partition_entry;
	uint32_t part_entries_crc32;
	uint8_t reserved[];
} __attribute__((packed));

struct gpt_partition_entry {
	uint8_t  partition_type_guid[16];
	uint8_t  unique_partition_guid[16];
	uint64_t first_lba;
	uint64_t last_lba;
	uint64_t attr_flags;
	uint8_t name[72];
} __attribute__((packed));

