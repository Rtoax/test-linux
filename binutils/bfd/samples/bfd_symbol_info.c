#include <bfd.h>
#include <stdio.h>


int main(void)
{
	bfd *abfd;
	symbol_info info;
	asymbol symbol;

	bfd_init();

	abfd = bfd_openr("./bfd_symbol_info", NULL);

	bfd_symbol_info(&symbol, &info);

	bfd_close(abfd);

	return 0;
}
