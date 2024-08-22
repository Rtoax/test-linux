#include <bfd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	bfd *abfd;
	symbol_info info;
	asymbol symbol;

	bfd_init();

	abfd = bfd_openr(argv[0], NULL);

	bfd_symbol_info(&symbol, &info);

	bfd_close(abfd);

	return 0;
}
