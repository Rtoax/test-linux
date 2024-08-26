#include <bfd.h>
#include <stdio.h>


int main(void)
{
	bfd *abfd;

	bfd_init();
	abfd = bfd_openr("/bin/ls", NULL);

	if (bfd_get_flavour(abfd) == bfd_target_elf_flavour) {
		printf("bfd_target_elf_flavour\n");
	}

	bfd_close(abfd);

	return 0;
}
