#include <bfd.h>
#include <stdio.h>


int main(void)
{
	bfd *abfd;

	bfd_init();

	abfd = bfd_openr("/bin/ls", NULL);

	/**
	 * TODO: bfd_elf_bfd_from_remote_memory()
	 */

	bfd_close(abfd);
	return 0;
}
