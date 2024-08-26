#include <bfd.h>
#include <stdio.h>


int main(void)
{
	bfd *templ, *abfd;

	bfd_init();

	templ = bfd_openr("/bin/bash", NULL);

	/* TODO: Apply to ulpatch */
	abfd = bfd_elf_bfd_from_remote_memory(templ, 0, 0, NULL, NULL);

	bfd_close(templ);
	bfd_close(abfd);
	return 0;
}
