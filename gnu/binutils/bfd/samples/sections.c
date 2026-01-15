#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "bfd_helpers.h"

#define BFD_ERR	bfd_errmsg(bfd_get_error())

static unsigned long vma_addr = 0;

void usage(const char *prog)
{
	fprintf(stderr, "\n"
		"-f, --file     specify file to bfd, default: %s\n"
		"-v, --vma      specify vma address, format: 0x0xxxx\n"
		"-h, --help     print this info\n",
		prog
	);
}

int main(int argc, char *argv[])
{
	int ret;
	bfd *abfd;
	char **matching;
	asection *asect;
	char *filepath;

	struct option options[] = {
		{"file", required_argument, 0, 'f'},
		{"vma", required_argument, 0, 'v'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};

	filepath = argv[0];

	while (1) {
		int option_index = 0;
		int c = getopt_long(argc, argv, "f:v:h", options, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 'f':
			filepath = optarg;
			printf("Set file name %s\n", filepath);
			break;
		case 'v':
			if (optarg[0] != '0' || optarg[1] != 'x') {
				fprintf(stderr, "Wrong format, start with '0x'\n");
				exit(1);
			}
			vma_addr = strtoull(optarg, NULL, 16);
			break;
		case 'h':
			usage(argv[0]);
			exit(0);
			break;
		case '?':
			usage(argv[0]);
			fprintf(stderr, "Unknown option or requires an argument.\n");
			exit(1);
			break;
		default:
			abort();
		}
	}

	bfd_init();

	abfd = bfd_openr(filepath, NULL);
	if (!abfd) {
		fprintf(stderr, "Open %s failed, %s.\n", filepath, BFD_ERR);
		exit(1);
	}

	/**
	 * NOTE: This function will make the section relate function return
	 * non-zero/NULL value.
	 */
	if (!bfd_check_format_matches(abfd, bfd_object, &matching)) {
		fprintf(stderr, "format_matches");
		goto close;
	}

	if (vma_addr)
		printf("VMA 0x%lx\n", vma_addr);

	printf("Print %s sections.\n", filepath);
	printf("%-32s %-16s %-8s %-8s %-16s %-16s %-16s\n", "SECTION", "ADDR",
		"SIZE",	"ALIGN", "VMA", "LMA", "ALLOC/DATA/TEXT/UDF/COM");

	for (asect = abfd->sections; asect != NULL; asect = asect->next) {
		flagword flags = tl_bfd_section_flags(asect);
		bfd_vma align;
		unsigned long addr;

#if defined(BFD_HAS_BFD_SECTION_ALIGNMENT)
		align = (bfd_vma) 1UL << bfd_section_alignment(asect);
#elif defined(BFD_HAS_BFD_SECTION_ALIGNMENT2)
		align = (bfd_vma) 1UL << bfd_section_alignment(abfd, asect);
#else
# error "bfd_section_alignment fatal."
#endif
#if defined(BFD_HAS_BFD_SECTION_VMA)
		addr = bfd_section_vma(asect);
#elif defined(BFD_HAS_BFD_SECTION_VMA2)
		addr = bfd_section_vma(abfd, asect);
#else
# error "bfd_section_vma fatal."
#endif

		if (vma_addr)
			addr += vma_addr;

		printf("%-32s %-16lx %-8lx %-8lx %-16lx %-16lx %c%c%c%c%c\n",
			tl_bfd_section_name(asect),
			addr,
#if defined(BFD_HAS_BFD_SECTION_SIZE)
			bfd_section_size(asect),
#elif defined(BFD_HAS_BFD_SECTION_SIZE2)
			bfd_section_size(abfd, asect),
#else
# error "bfd_section_size fatal."
#endif
			align,
#if defined(BFD_HAS_BFD_SECTION_VMA)
			bfd_section_vma(asect),
#elif defined(BFD_HAS_BFD_SECTION_VMA2)
			bfd_section_vma(abfd, asect),
#else
# error "bfd_section_vma fatal."
#endif
#if defined(BFD_HAS_BFD_SECTION_LMA)
			bfd_section_lma(asect),
#elif defined(BFD_HAS_BFD_SECTION_LMA2)
			bfd_section_lma(abfd, asect),
#else
# error "bfd_section_lma fatal."
#endif
			flags & SEC_ALLOC ? 'a' : '-',
			flags & SEC_DATA ? 'd' : '-',
			flags & SEC_CODE ? 't' : '-',
			bfd_is_und_section(asect) ? 'u' : '-',
			bfd_is_com_section(asect) ? 'C' : '-');
	}

	asect = bfd_get_section_by_name(abfd, ".plt");
	if (!asect) {
		fprintf(stderr, "Not found .plt section, %s.\n", BFD_ERR);
	}
	asect = bfd_get_section_by_name(abfd, ".text");
	if (!asect) {
		fprintf(stderr, "Not found .text section.\n");
	}

close:
	bfd_close(abfd);
	return 0;
}
