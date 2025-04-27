#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>

#include "bfd_helpers.h"

int main(int argc, char *argv[])
{
	int ret, i;
	bfd *abfd;
	char **matching;
	const struct bfd_build_id *build_id;

	tl_bfd_init();

	abfd = bfd_openr(argv[0], NULL);

	/**
	 * NOTE: This function will make the section/build_id relate function
	 * return non-zero/NULL value.
	 */
	if (!bfd_check_format_matches(abfd, bfd_object, &matching)) {
		fprintf(stderr, "format_matches");
		goto close;
	}

	if (!(bfd_get_file_flags(abfd) & HAS_SYMS)) {
		fprintf(stderr, "No syms in %s\n", bfd_get_filename(abfd));
	}

#if 0 /* segvfault */
	for (i = 0; matching[i]; i++)
		printf("matching[%d] = %s\n", i, matching[i]);
#endif

	printf("get_filename: %s\n", bfd_get_filename(abfd));
	printf("get_size: %ld\n", bfd_get_size(abfd));
	printf("count_sections: %d\n", bfd_count_sections(abfd));
	printf("get_symcount: %d\n", bfd_get_symcount(abfd));
	printf("get_dynamic_symcount: %d\n", bfd_get_dynamic_symcount(abfd));

	if (abfd->build_id != NULL) {
		char buf[128];
		build_id = abfd->build_id;
		printf("BuildID %s\n", tl_bfd_strbid(build_id, buf, 128));
		printf("BuildID ");
			tl_bfd_print_build_id(build_id);
			printf("\n");
	}

close:
	bfd_close(abfd);
	return 0;
}
