#include <bfd.h>
#include <stdio.h>


int main(void)
{
	bfd *abfd;
	const struct bfd_build_id *build_id;

	bfd_init();

	abfd = bfd_openr("/bin/ls", NULL);

	printf("get_filename: %s\n", bfd_get_filename(abfd));
	printf("get_size: %ld\n", bfd_get_size(abfd));

	if (abfd->build_id != NULL) {
		build_id = abfd->build_id;
		printf("BuildID size %ld\n", build_id->size);
	}

	bfd_close(abfd);
	return 0;
}
