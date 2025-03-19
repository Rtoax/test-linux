#pragma once
/**
 * refs:
 * - https://en.wikipedia.org/wiki/GUID_Partition_Table
 * - https://en.wikipedia.org/wiki/Master_boot_record
 */
#include <stdint.h>

/**
 * Structure of a classical generic MBR
 *
 * Address	Description			Size(bytes)
 * 0x0000 (0)	Bootstrap code area		446
 * 0x01BE (446)	Partition entry No.1		16
 * 0x01CE (462)	Partition entry No.2		16
 * 0x01DE (478)	Partition entry No.3		16
 * 0x01EE (494)	Partition entry No.4		16
 * 0x01FE (510)	0x55	Boot signature[0]	2
 * 0x01FF (511)	0xAA	Boot signature[1]	2
 *
 * ref: https://en.wikipedia.org/wiki/Master_boot_record
 */
struct classical_generic_mbr {
	uint8_t bootstrap_code_area[446];
	/**
	 * Partition table (for primary partitions)
	 */
	uint8_t part_entry1[16];
	uint8_t part_entry2[16];
	uint8_t part_entry3[16];
	uint8_t part_entry4[16];
	/* 0x55, 0xAA */
	uint8_t boot_signature[2];
} __attribute__((packed));

/**
 * Structure of a modern standard MBR
 */
struct modern_standard_mbr {
	uint8_t bootstrap_code_area[218];
	struct {
		uint8_t zero[2];
		uint8_t orig_phy_drv;
		uint8_t secs;
		uint8_t mins;
		uint8_t hours;
	} timestamp;
	uint8_t bootstrap_code_area2[216]; /* 216 or 222 */
	/**
	 * Disk signature
	 * optional; UEFI, Linux, Windows NT family and other OSes
	 */
	struct {
		uint32_t signature;
		/* 0x0000 (0x5A5A if copy-protected) */
		uint16_t copy_protected;
	} disk_signature;

	/**
	 * Partition table (for primary partitions)
	 */
	uint8_t part_entry1[16];
	uint8_t part_entry2[16];
	uint8_t part_entry3[16];
	uint8_t part_entry4[16];

	/* 0x55, 0xAA */
	uint8_t boot_signature[2];
} __attribute__((packed));

/**
 * Structure of AAP MBR
 */
struct aap_mbr {
	uint8_t bootstrap_code_area[428];
	/* 0x78, 0x56 */
	uint8_t aap_signature[2];
	uint8_t aap_phy_drv;
	/* CHS (start) address of AAP partition/image file or VBR/EBR */
	uint8_t chs_addr[3];
	uint8_t reserved1;
	uint8_t reserved2[3];
	union {
		uint32_t start_lba;
		uint32_t vbr_ebr;
		uint32_t relative_sectors;
		uint32_t aap_partition;
	};
	uint32_t reserved3;
	uint8_t part_entry1[16];
	uint8_t part_entry2[16];
	uint8_t part_entry3[16];
	uint8_t part_entry4[16];
	/* 0x55, 0xAA */
	uint8_t boot_signature[2];
} __attribute__((packed));

/**
 * TODO: More MBR type, see https://en.wikipedia.org/wiki/Master_boot_record
 */

struct chs_addr {
	uint8_t head;
	union {
		struct {
			uint8_t cylinder_9_8:2;
			uint8_t sector:6;
		};
		uint8_t cylinder_sector;
	};
	uint8_t cylinder_7_0;
};

struct mbr_entry {
	union {
		uint8_t status;
		uint8_t phy_drv;
	};
	union {
		uint8_t first_chs_addr[3];
		struct chs_addr first_chs_addr_struct;
	};
	uint8_t partition_type;
	union {
		uint8_t last_chs_addr[3];
		struct chs_addr last_chs_addr_struct;
	};
	uint32_t first_abs_sector;
	uint32_t nr_sectors;
} __attribute__((packed));


