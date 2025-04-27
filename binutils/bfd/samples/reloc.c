#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <getopt.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#include "bfd_helpers.h"

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
	int ret, i;
	bfd *abfd;
	char **matching;
	asection *asect;
	char *filepath;
	char default_file_buffer[PATH_MAX];

	struct option options[] = {
		{"file", required_argument, 0, 'f'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};

	snprintf(default_file_buffer, PATH_MAX, "%s.o", argv[0]);
	filepath = default_file_buffer;

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
			usage(default_file_buffer);
			exit(0);
			break;
		case '?':
			usage(default_file_buffer);
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

	if (!bfd_check_format_matches(abfd, bfd_object, &matching)) {
		fprintf(stderr, "format_matches\n");
		goto close;
	}

	printf("ELF %s\n", filepath);

	for (asect = abfd->sections; asect != NULL; asect = asect->next) {
		arelent **p, **pend;
		arelent **relpp;
		asymbol **asympp;
		long relsize, relcount;

		relsize = bfd_get_reloc_upper_bound(abfd, asect);
		if (relsize < 0) {
			fprintf(stderr, "Could not read relocs\n");
			continue;
		}
		if (relsize == 0)
			continue;

		fprintf(stderr, "section %s relsize %ld\n",
			tl_bfd_section_name(asect), relsize);

		relpp = (arelent **)malloc(relsize);

		asympp = bfd_get_outsymbols(abfd);

		relcount = bfd_canonicalize_reloc(abfd, asect, relpp, asympp);
		if (relcount < 0) {
			fprintf(stderr, "Could not read relocs\n");
			free(relpp);
			continue;
		}

		p = relpp;
		pend = p + relcount;

		for (; p < pend && *p != NULL; p++) {
			arelent *q = *p;

			if (q->sym_ptr_ptr != NULL &&
			    *q->sym_ptr_ptr != NULL) {
				printf("rel %s, addr %lx, addend %lx\n",
					bfd_asymbol_name(*q->sym_ptr_ptr),
					q->address,
					q->addend);
			}
		}
		free(relpp);
	}

close:
	bfd_close(abfd);
	return 0;
}
