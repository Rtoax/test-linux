#include <bfd.h>
#include <stdio.h>


int main(void)
{
	bfd *abfd;

	bfd_init();
	abfd = bfd_openr("/bin/ls", NULL);
	printf("%ld\n", bfd_get_start_address(abfd));
	bfd_close(abfd);

	return 0;
}
