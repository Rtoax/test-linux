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
	/**
	 * Signature ("EFI PART", 45h 46h 49h 20h 50h 41h 52h 54h or
	 * 0x5452415020494645ULL[a] on little-endian machines)
	 */
	uint64_t signature;
	/**
	 * Revision number of header - 1.0 (00h 00h 01h 00h) for UEFI 2.10
	 */
	uint32_t revision_number;
	/**
	 * Header size in little endian (in bytes, usually 5Ch 00h 00h 00h or
	 * 92 bytes)
	 */
	uint32_t size;
	/**
	 * CRC32 of header (offset +0 to +0x5B) in little endian, with this
	 * field zeroed during calculation
	 */
	uint32_t hdr_crc32;
	/* Reserved; must be zero */
	uint32_t reserved1;
	/* Current LBA (location of this header copy) */
	uint64_t current_lba;
	/* Backup LBA (location of the other header copy) */
	uint64_t backup_lba;
	/* First usable LBA for partitions (primary partition table last LBA + 1) */
	uint64_t first_usable_lba;
	/* Last usable LBA (secondary partition table first LBA − 1) */
	uint64_t last_usable_lba;
	/* Disk GUID in little endian */
	uint8_t guid[16];
	/* Starting LBA of array of partition entries (usually 2 for compatibility) */
	uint64_t start_lba;
	/* Number of partition entries in array */
	uint32_t nr_partition_entries;
	/* Size of a single partition entry (usually 80h or 128) */
	uint32_t sz_partition_entry;
	/* CRC32 of partition entries array in little endian */
	uint32_t part_entries_crc32;
	/**
	 * Reserved; must be zeroes for the rest of the block (420 bytes for a
	 * sector size of 512 bytes; but can be more with larger sector sizes)
	 */
	uint8_t reserved2[];
} __attribute__((packed));

/**
 * GUID partition entry format
 */
struct gpt_partition_entry {
	/* little endian */
	uint8_t  partition_type_guid[16];
	/* little endian */
	uint8_t  unique_partition_guid[16];
	/* little endian */
	uint64_t first_lba;
	/* inclusive, usually odd */
	uint64_t last_lba;
/**
 * Platform required (required by the computer to function properly, OEM
 * partition for example, disk partitioning utilities must preserve the
 * partition as is)
 */
#define GPT_PART_ATTR_BIT_PLATFORM_REQ	0
/**
 * EFI firmware should ignore the content of the partition and not try to
 * read from it.
 */
#define GPT_PART_ATTR_BIT_EFI_FW	1
/**
 * Legacy BIOS bootable (equivalent to active flag (typically bit 7 set)
 * at offset +0h in partition entries of the MBR partition table)
 */
#define GPT_PART_ATTR_BIT_LEGACY_BIOS	2
/* Reserved for future use, bits 3-47 */
#define GPT_PART_ATTR_BITMASK_RSVD	0x00fffffffffffff8UL
/**
 * Defined and used by the individual partition type, bits 48–63
 */
#define GPT_PART_ATTR_BITMASK_PART_TYPE	0xff00000000000000UL
#define GPT_PART_ATTR_BIT_PART_RO	60
/* Shadow copy (of another partition) */
#define GPT_PART_ATTR_BIT_PART_SHADOW_COPY	61
#define GPT_PART_ATTR_BIT_PART_HIDDEN	62
/* No drive letter (i.e. do not automount) */
#define GPT_PART_ATTR_BIT_PART_NO_DRIVE_LETTER	63
	/* Attribute flags (e.g. bit 60 denotes read-only) */
	uint64_t attr_flags;
	/* Partition name (36 UTF-16LE code units) */
	uint8_t name[72];
} __attribute__((packed));

