/**
 * Read and parse block information
 *
 * refs:
 * - https://en.wikipedia.org/wiki/GUID_Partition_Table
 * - https://en.wikipedia.org/wiki/Master_boot_record
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdint.h>
#include <getopt.h>
#include <byteswap.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * LBA: logical block addressing
 */

enum part_table_type {
	TYPE_UNKNOWN,
	TYPE_MBR,
	TYPE_GPT,
};

struct classical_generic_mbr {
	uint8_t bootstrap_code_area[446];
	uint8_t part_entry1[16];
	uint8_t part_entry2[16];
	uint8_t part_entry3[16];
	uint8_t part_entry4[16];
	/* 0x55, 0xAA */
	uint8_t boot_signature[2];
} __attribute__((packed));

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
	 * optional; UEFI, Linux, Windows NT family and other OSes
	 */
	struct {
		uint32_t signature;
		/* 0x0000 (0x5A5A if copy-protected) */
		uint16_t copy_protected;
	} disk_signature;

	uint8_t part_entry1[16];
	uint8_t part_entry2[16];
	uint8_t part_entry3[16];
	uint8_t part_entry4[16];
	/* 0x55, 0xAA */
	uint8_t boot_signature[2];
} __attribute__((packed));

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

/**
 * https://en.wikipedia.org/wiki/Partition_type
 */
const char *mbr_partition_type_str(uint8_t type)
{
	static char hex[3];
	sprintf(hex, "%02x", type);
	switch (type) {
#define T(v, s)	case v: return s;
	T(0x43, "Linux File system(old)")
	T(0x83, "Linux File system")
	T(0x85, "Linux extended")
	T(0x86, "Linux RAID")
	T(0x88, "Linux plaintext")
	T(0x8e, "Linux LVM")
	T(0xee, "EFI Blocker(GPT protective MBR)")
#undef T
	default: return hex;
	}
}

void print_mixed_endian_guid(uint8_t i_guid[16])
{
	int i;
	uint8_t guid[16];

	memcpy(guid, i_guid, sizeof(guid));

	/**
	 * fdisk -l:  C9516251-2856-4737-B86D-06225B05B911
	 * hdr->guid: 516251c9 5628 3747 b86d 06225b05b911
	 *            ^^^^^^^^^^^^^^^^^^
	 *                big endian     ^^^^^^^^^^^^^^^^^
	 *                                 little endian
	 */
	uint32_t *guid_hi_32 = (uint32_t *)&guid[0];
	uint16_t *guid_hi_16 = (uint16_t *)&guid[4];
	uint16_t *guid_mid_16 = (uint16_t *)&guid[6];
	*guid_hi_32 = bswap_32(*guid_hi_32);
	*guid_hi_16 = bswap_16(*guid_hi_16);
	*guid_mid_16 = bswap_16(*guid_mid_16);
	for (i = 0; i < sizeof(guid); i++) {
		unsigned char ch = guid[i];
		printf("%02X", ch);
		if (i == 3 || i == 5 || i == 7 || i == 9)
			printf("-");
	}
}

void usage(char *prog)
{
	printf("%s\n", prog);
	printf("\n");
	printf(" -d, --disk   specify disk to check, for example: /dev/vda\n");
	printf("\n");
	printf(" -h, --help   show this information.\n");
	printf("\n");
}


int main(int argc, char *argv[])
{
	char *path = NULL;
	size_t size;
	int err, i, fd = -1;
	unsigned char *mbr;
	unsigned char *primary_gpt_hdr;
	struct stat statbuf;
	struct classical_generic_mbr *cg_mbr;
	struct modern_standard_mbr *ms_mbr;
	struct aap_mbr *aap_mbr;
	struct gpt_hdr *hdr;
	struct gpt_partition_entry *part_entries = NULL;
	enum part_table_type tab_type = TYPE_UNKNOWN;

	struct option options[] = {
		{"disk",    required_argument, 0, 'd'},
		{"help",    no_argument,       0, 'h'},
		{0, 0, 0, 0}
	};

	while (1) {
		int option_index = 0;
		int c = getopt_long(argc, argv, "d:h", options, &option_index);
		if (c == -1)
			break;
		switch (c) {
		case 'd':
			path = strdup(optarg);
			break;
		case 'h':
			usage(argv[0]);
			return 0;
		case '?':
			fprintf(stderr, "Unknown option or requires an argument.\n");
			exit(1);
			break;
		default:
			abort();
		}
	}

	if (!path) {
		usage(argv[0]);
		fprintf(stderr, "No disk input(-d).\n");
		exit(1);
	}

	err = stat(path, &statbuf);
	if (err) {
		fprintf(stderr, "can't stat %s.\n", path);
		exit(1);
	}

	if (!S_ISBLK(statbuf.st_mode)) {
		fprintf(stderr, "%s is not a block device.\n", path);
		exit(1);
	}

	/* Open with read only permission, never O_WR */
	fd = open(path, O_RDONLY);
	if (fd == -1) {
		printf("open(%s) %s\n", path, strerror(errno));
		exit(1);
	}

	if (fd == -1) {
		printf("open(%s) %s\n", path, strerror(errno));
		return 1;
	}

	/* MBR: 512 bytes */
	mbr = malloc(512);
	primary_gpt_hdr = malloc(0x5c);

	read(fd, mbr, 512);
	read(fd, primary_gpt_hdr, 0x5c);

	cg_mbr = (void *)mbr;
	ms_mbr = (void *)mbr;
	aap_mbr = (void *)mbr;

	hdr = (struct gpt_hdr *)primary_gpt_hdr;

	if (cg_mbr->boot_signature[0] == 0x55 && cg_mbr->boot_signature[1] == 0xAA) {
		tab_type = TYPE_MBR;
	}

	printf("Disk: %s\n", path);

	/**
	 * "EFI PART" = 45h 46h 49h 20h 50h 41h 52h 54h
	 *            = 0x5452415020494645ULL
	 */
	if (hdr->signature == 0x5452415020494645ULL) {
		printf("Partition Table: GPT\n");
		tab_type = TYPE_GPT;
	} else {
		printf("No GPT found in %s.\n", path);
		goto parse_mbr;
	}

	printf("Signature: 0x%-16lx\n", hdr->signature);
	/**
	 * 00h 00h 01h 00h
	 */
	if (hdr->revision_number == 0x00010000U)
		printf("Revision 1.0 for UEFI 2.0\n");

	printf("Header Size: %d bytes\n", hdr->size);
	printf("Header CRC32: %#08x\n", hdr->hdr_crc32);

	printf("GUID: ");
	print_mixed_endian_guid(hdr->guid);
	printf("\n");

	printf("Starting LBA: %ld\n", hdr->start_lba);
	printf("Number of partition entries: %d\n", hdr->nr_partition_entries);
	printf("Size of partition entry: %d\n", hdr->sz_partition_entry);
	printf("Partition entries CRC32: %#08x\n", hdr->part_entries_crc32);

	size = sizeof(struct gpt_partition_entry) * hdr->nr_partition_entries;
	part_entries = malloc(size);
	read(fd, part_entries, size);
	printf("%-8s %-16s %-16s %-16s\n", "ENTRY", "FIRST_LBA", "LAST_LBA", "ATTR_FLAGS");
	for (i = 0; i < hdr->nr_partition_entries; i++) {
		struct gpt_partition_entry *e = &part_entries[i];
		if (e->first_lba == 0 || e->last_lba == 0)
			continue;

		printf("%-8d %16lx %16lx %16lx\n", i, e->first_lba, e->last_lba, e->attr_flags);
		/**
		 * TODO: print entries
		 */
	}

parse_mbr:
	/**
	 * MBR maybe
	 */
	if (tab_type != TYPE_MBR && tab_type != TYPE_GPT) {
		printf("No MBR found in %s.\n", path);
		goto all_done;
	}
	printf("MBR Signature: %x %x\n", cg_mbr->boot_signature[0], cg_mbr->boot_signature[1]);

	struct mbr_entry *me[4];
	me[0] = (void *)cg_mbr->part_entry1;
	me[1] = (void *)cg_mbr->part_entry2;
	me[2] = (void *)cg_mbr->part_entry3;
	me[3] = (void *)cg_mbr->part_entry4;

	printf("%-8s %-16s %-16s %-8s\n", "ENTRY", "ABS_SECTOR", "NR_SECTOR", "TYPE");
	for (i = 0; i < 4; i++) {
		struct mbr_entry *e = me[i];
		if (e->nr_sectors <= 0)
			continue;
		printf("%-8d %-16d %-16d %-16s\n", i + 1, e->first_abs_sector,
			e->nr_sectors, mbr_partition_type_str(e->partition_type));
	}

all_done:
	close(fd);
	free(primary_gpt_hdr);
	free(mbr);
	if (part_entries)
		free(part_entries);
	return 0;
}
