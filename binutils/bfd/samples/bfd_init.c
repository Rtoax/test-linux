#include <bfd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	bfd *abfd;
	const struct bfd_build_id *build_id;

	bfd_init();

	abfd = bfd_openr(argv[0], NULL);

	printf("get_filename: %s\n", bfd_get_filename(abfd));
	printf("get_size: %ld\n", bfd_get_size(abfd));
	printf("count_sections: %d\n", bfd_count_sections(abfd));
	printf("get_symcount: %d\n", bfd_get_symcount(abfd));
	printf("get_dynamic_symcount: %d\n", bfd_get_dynamic_symcount(abfd));

	if (abfd->build_id != NULL) {
		build_id = abfd->build_id;
		printf("BuildID size %ld\n", build_id->size);
	}

	bfd_close(abfd);
	return 0;
}
