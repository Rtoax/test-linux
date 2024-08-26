#include <bfd.h>
#include <stdio.h>


int main(void)
{
	bfd *abfd;
	asection *asect;

	bfd_init();
	abfd = bfd_openr("/bin/ls", NULL);

	for (asect = abfd->sections; asect != NULL; asect = asect->next) {
		printf("%lx\n", bfd_section_vma(asect));
	}

	bfd_close(abfd);

	return 0;
}
