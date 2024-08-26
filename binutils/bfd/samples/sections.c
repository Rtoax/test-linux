#include <bfd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	bfd *abfd;
	asection *asect;
	char *filepath = argv[0];

	bfd_init();
	abfd = bfd_openr(filepath, NULL);

	for (asect = abfd->sections; asect != NULL; asect = asect->next) {
		printf("%lx\n", bfd_section_vma(asect));
	}

	asect = bfd_get_section_by_name(abfd, ".plt");
	if (!asect) {
		fprintf(stderr, "Not found .plt section.\n");
	}

	bfd_close(abfd);

	return 0;
}
