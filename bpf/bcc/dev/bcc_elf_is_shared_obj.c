#include <stdio.h>
#include <bcc/bcc_elf.h>

int main(int argc, char *argv[])
{
	char *path = (argc <= 1) ? argv[0] : argv[1];

	printf("bcc_elf_is_exe: %d\n", bcc_elf_is_exe(path));
	printf("bcc_elf_is_shared_obj: %d\n", bcc_elf_is_shared_obj(path));

	return 0;
}
