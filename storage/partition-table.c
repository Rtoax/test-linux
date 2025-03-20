/**
 * Read and parse block information
 *
 * table:
 * - MBR: master boot record
 * - gpt: GUID partition table
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
#include <iconv.h>

#include "mbr.h"
#include "gpt.h"

enum part_table_type {
	PTAB_TYPE_UNKNOWN,
	PTAB_TYPE_MBR_CLASSIC,
	PTAB_TYPE_MBR_AAP,
	PTAB_TYPE_GPT,
};

static int verbose = 0;

/**
 * https://en.wikipedia.org/wiki/Partition_type
 */
const char *mbr_partition_type_str(uint8_t type)
{
	static char hex[3];
	sprintf(hex, "%02x", type);
	switch (type) {
#define T(v, s)	case v: return s;
	T(0x0c, "W95 FAT32 (LBA)")
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

void print_guid(uint8_t guid[16], size_t size)
{
	int i;
	for (i = 0; i < size; i++) {
		unsigned char ch = guid[i];
		printf("%02X", ch);
		if (i == 3 || i == 5 || i == 7 || i == 9)
			printf("-");
	}
}

void print_mixed_endian_guid(uint8_t i_guid[16])
{
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
	print_guid(guid, sizeof(guid));
}

const char* utf16le_to_utf8(char *inbuff, size_t inbytes, char *outbuff,
			    size_t outbytes)
{
	int err;
	iconv_t icv;
	char *in, *out;

	icv = iconv_open("UTF-8", "UTF-16LE");
	if (icv == (iconv_t)-1) {
		perror("iconv_open");
		return NULL;
	}

	in = inbuff;
	out = outbuff;

	err = iconv(icv, &in, &inbytes, &out, &outbytes);
	if (err) {
		perror("iconv");
		iconv_close(icv);
		return NULL;
	}
	*out = '\0';
#ifdef DEBUG
	printf("out %s\n", outbuff);
#endif
	iconv_close(icv);
	return outbuff;
}

void parse_gpt(int blkfd, struct classical_generic_mbr *protective_mbr,
	       struct gpt_hdr *hdr)
{
	int i;
	size_t size;
	struct gpt_partition_entry *part_entries = NULL;

	printf("Signature: 0x%-16lx '%s'\n", hdr->signature, (char *)&hdr->signature);
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

	if (hdr->reserved1 != 0)
		fprintf(stderr, "ERROR: reserved must be zero.\n");

	size = sizeof(struct gpt_partition_entry) * hdr->nr_partition_entries;
	part_entries = malloc(size);
	read(blkfd, part_entries, size);

	printf("\033[7m%-6s %-16s %-16s %-16s %-36s",
		"ENTRY", "FIRST_LBA", "LAST_LBA", "ATTR_FLAGS", "NAME");
	if (verbose)
		printf(" %-36s %-36s", "Partition_type_GUID", "Unique_partition_GUID");
	printf("\033[m\n");

	for (i = 0; i < hdr->nr_partition_entries; i++) {
		struct gpt_partition_entry *e = &part_entries[i];
		char utf8buf[sizeof(e->utf16le_name) / 2 + 1];

		if (e->first_lba == 0 || e->last_lba == 0)
			continue;

		printf("%-6d %#016lx %#016lx %#016lx %-36s",
			i, e->first_lba, e->last_lba, e->attr_flags,
			utf16le_to_utf8(e->utf16le_name, sizeof(e->utf16le_name),
					utf8buf, sizeof(utf8buf)));

		if (verbose) {
			printf(" ");
			print_guid(e->partition_type_guid, sizeof(e->partition_type_guid));
			printf(" ");
			print_guid(e->unique_partition_guid, sizeof(e->unique_partition_guid));
		}
		printf("\n");
		/**
		 * TODO: print entries
		 */
	}
	free(part_entries);
}

void parse_mbr_classic(struct classical_generic_mbr *cg_mbr)
{
	int i;
	struct mbr_entry *me[4];

	printf("MBR Signature: %x %x\n", cg_mbr->boot_signature[0], cg_mbr->boot_signature[1]);

	me[0] = (void *)cg_mbr->part_entry1;
	me[1] = (void *)cg_mbr->part_entry2;
	me[2] = (void *)cg_mbr->part_entry3;
	me[3] = (void *)cg_mbr->part_entry4;

	printf("\033[7m%-8s %-16s %-16s %-32s\033[m\n",
		"ENTRY", "ABS_SECTOR", "NR_SECTOR", "TYPE");
	for (i = 0; i < 4; i++) {
		struct mbr_entry *e = me[i];
		if (e->nr_sectors <= 0)
			continue;
		printf("%-8d %-16d %-16d %-32s\n", i + 1, e->first_abs_sector,
			e->nr_sectors, mbr_partition_type_str(e->partition_type));
	}
}

void usage(char *prog)
{
	printf("%s\n", prog);
	printf("\n");
	printf(" -b, --blk [BLK|FILE]  specify lock or file to check, for example: /dev/vda\n");
	printf(" -h, --help            show this information.\n");
	printf(" -v, --verbose         show verbose information.\n");
	printf("\n");
}


int main(int argc, char *argv[])
{
	char *path = NULL;
	int err, i, fd = -1;
	unsigned char *mbr;
	unsigned char *primary_gpt_hdr;
	struct stat statbuf;
	struct classical_generic_mbr *cg_mbr;
	struct modern_standard_mbr *ms_mbr;
	struct aap_mbr *aap_mbr;
	struct gpt_hdr *gpt_hdr;
	struct mbr_entry *mbr_entry;
	enum part_table_type tab_type = PTAB_TYPE_UNKNOWN;

	struct option options[] = {
		{"blk",     required_argument, 0, 'b'},
		{"help",    no_argument,       0, 'h'},
		{"verbose", no_argument,       0, 'v'},
		{0, 0, 0, 0}
	};

	while (1) {
		int option_index = 0;
		int c = getopt_long(argc, argv, "b:hv", options, &option_index);
		if (c == -1)
			break;
		switch (c) {
		case 'b':
			path = strdup(optarg);
			break;
		case 'h':
			usage(argv[0]);
			return 0;
		case 'v':
			verbose = 1;
			break;
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

	if (!S_ISREG(statbuf.st_mode) && !S_ISBLK(statbuf.st_mode)) {
		fprintf(stderr, "%s is neithor block device nor regular file.\n", path);
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

#ifdef DEBUG
	printf("size of struct mbr_entry %d\n", sizeof(struct mbr_entry));
#endif

	printf("Disk: %s\n", path);

	/* MBR: 512 bytes */
	mbr = malloc(512);
	read(fd, mbr, 512);

	cg_mbr = (void *)mbr;
	ms_mbr = (void *)mbr;
	aap_mbr = (void *)mbr;

	/* GPT */
	primary_gpt_hdr = malloc(sizeof(struct gpt_hdr));
	read(fd, primary_gpt_hdr, sizeof(struct gpt_hdr));
	gpt_hdr = (struct gpt_hdr *)primary_gpt_hdr;

	if (cg_mbr->boot_signature[0] == 0x55 && cg_mbr->boot_signature[1] == 0xAA) {
		tab_type = PTAB_TYPE_MBR_CLASSIC;
	}

	if (aap_mbr->boot_signature[0] == 0x55 && aap_mbr->boot_signature[1] == 0xAA &&
	    aap_mbr->aap_signature[0] == 0x78 && aap_mbr->aap_signature[1] == 0x56) {
		tab_type = PTAB_TYPE_MBR_AAP;
	}

	/**
	 * Protective MBR (LBA 0)
	 *
	 * For limited backward compatibility, the space of the legacy Master
	 * Boot Record (MBR) is still reserved in the GPT specification, but
	 * it is now used in a way that prevents MBR-based disk utilities from
	 * misrecognizing and possibly overwriting GPT disks. This is referred
	 * to as a protective MBR.
	 *
	 * A single partition of type "EEh", encompassing the entire GPT drive
	 * (where "entire" actually means as much of the drive as can be
	 * represented in an MBR), is indicated and identifies it as GPT.
	 *
	 * https://en.wikipedia.org/wiki/GUID_Partition_Table
	 */
	mbr_entry = (void *)cg_mbr->part_entry1;
	if (mbr_entry->partition_type == MBR_PT_GPT_PROTECTIVE_MBR) {
		tab_type = PTAB_TYPE_GPT;
	}

	/**
	 * "EFI PART" = 45h 46h 49h 20h 50h 41h 52h 54h
	 *            = 0x5452415020494645ULL
	 */
	if (gpt_hdr->signature == MAGIC_EFI_PART) {
		printf("Partition Table: GPT\n");
		tab_type = PTAB_TYPE_GPT;
	} else {
		printf("No GPT found in %s.\n", path);
	}

	switch (tab_type) {
	case PTAB_TYPE_GPT:
		parse_gpt(fd, cg_mbr, gpt_hdr);
		break;
	case PTAB_TYPE_MBR_CLASSIC:
		parse_mbr_classic(cg_mbr);
		break;
	case PTAB_TYPE_MBR_AAP:
		printf("Not support AAP MBR yet in %s.\n", path);
		break;
	default:
		printf("No MBR and GPT found in %s.\n", path);
		goto all_done;
	}

all_done:
	close(fd);
	free(primary_gpt_hdr);
	free(mbr);
	return 0;
}
