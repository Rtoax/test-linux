#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define BFD_ERR	bfd_errmsg(bfd_get_error())

void usage(const char *prog)
{
	fprintf(stderr, "\n"
		"-f, --file     specify file to bfd, default: %s\n"
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
		{"text-vma", required_argument, 0, 't'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};

	filepath = argv[0];

	while (1) {
		int option_index = 0;
		int c = getopt_long(argc, argv, "f:h", options, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 'f':
			filepath = optarg;
			printf("Set file name %s\n", filepath);
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

	ret = bfd_init();
	if (ret != BFD_INIT_MAGIC) {
		fprintf(stderr, "bfd_init failed.\n");
		exit(1);
	}

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

	printf("Print %s sections.\n", filepath);
	printf("%-32s %-8s %-8s %-16s %-16s\n", "SECTION", "SIZE", "ALIGN",
		"VMA", "ALLOC/DATA/TEXT");
	for (asect = abfd->sections; asect != NULL; asect = asect->next) {
		flagword flags = bfd_section_flags(asect);
		bfd_vma align = (bfd_vma) 1UL << bfd_section_alignment(asect);
		// bfd_set_section_vma(asect, 0xffff);
		printf("%-32s %-8lx %-8lx %-16lx %c%c%c\n",
			bfd_section_name(asect),
			bfd_section_size(asect),
			align,
			bfd_section_vma(asect),
			flags & SEC_ALLOC ? 'a' : '-',
			flags & SEC_DATA ? 'd' : '-',
			flags & SEC_CODE ? 't' : '-');
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
