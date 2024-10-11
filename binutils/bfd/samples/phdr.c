#include <elf.h>
#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define BFD_ERR	bfd_errmsg(bfd_get_error())

int main(int argc, char *argv[])
{
	int ret, i;
	bfd *abfd;
	char **matching;
	long phdrs_size;
	char *filepath;
	Elf64_Phdr *phdrs, **segments;


	filepath = argv[0];

	bfd_init();

	abfd = bfd_openr(filepath, NULL);
	if (!abfd) {
		fprintf(stderr, "Open %s failed, %s.\n", filepath, BFD_ERR);
		exit(1);
	}

	if (!bfd_check_format_matches(abfd, bfd_object, &matching)) {
		fprintf(stderr, "format_matches");
		goto close;
	}

/**
 * FIXME: BFD not export phdr relate APIs
 */
#if 0
	phdrs_size = bfd_get_elf_phdr_upper_bound(abfd);

	phdrs = (Elf64_Phdr *)alloca(phdrs_size);
	num_phdrs = bfd_get_elf_phdrs(abfd, phdrs);
#endif

close:
	bfd_close(abfd);
	return 0;
}
