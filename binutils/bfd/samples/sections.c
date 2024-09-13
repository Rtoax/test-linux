#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>

#define BFD_ERR	bfd_errmsg(bfd_get_error())

int main(int argc, char *argv[])
{
	int ret;
	bfd *abfd;
	char **matching;
	asection *asect;
	char *filepath = argv[0];

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
