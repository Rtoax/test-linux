#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>

#define BFD_ERR	bfd_errmsg(bfd_get_error())

int main(int argc, char *argv[])
{
	int ret;
	bfd *abfd;
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

	for (asect = abfd->sections; asect != NULL; asect = asect->next) {
		printf("%lx\n", bfd_section_vma(asect));
	}

	asect = bfd_get_section_by_name(abfd, ".plt");
	if (!asect) {
		fprintf(stderr, "Not found .plt section, %s.\n", BFD_ERR);
	}
	asect = bfd_get_section_by_name(abfd, ".text");
	if (!asect) {
		fprintf(stderr, "Not found .text section.\n");
	}

	bfd_close(abfd);

	return 0;
}
