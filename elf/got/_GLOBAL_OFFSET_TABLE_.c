#include <stdio.h>

#define Addr	unsigned long

/**
 * _GLOBAL_OFFSET_TABLE_
 *
 * - define in libc.so.6;
 * - GOT[plt] in .got.plt section;
 */
extern const Addr _GLOBAL_OFFSET_TABLE_[];

Addr elf_machine_dynamic(void)
{
	return _GLOBAL_OFFSET_TABLE_[0];
}

Addr addr_link_map(void)
{
	return _GLOBAL_OFFSET_TABLE_[1];
}

/**
 * (gdb) disassemble /s _GLOBAL_OFFSET_TABLE_[2],+0x16
 */
Addr addr_dl_runtime_resolve(void)
{
	return _GLOBAL_OFFSET_TABLE_[2];
}

int main(void)
{
	printf("size of Addr = %ld\n", sizeof(Addr));

	printf("_GLOBAL_OFFSET_TABLE_ addr = 0x%lx\n", _GLOBAL_OFFSET_TABLE_);
/**
 * FIXME: Why segfault here??
 */
#if !defined(M32)
	printf("link_map = 0x%lx\n", addr_link_map());
	printf("elf_machine_dynamic = 0x%lx\n", elf_machine_dynamic());
	printf("addr_dl_runtime_resolve = 0x%lx\n", addr_dl_runtime_resolve());
#endif
	/**
	 * More @plt
	 */
	/* fwrite@plt */
	fprintf(stderr, "Hello\n");
	dprintf(1, "Hello\n");
	puts("Hello");
	return 0;
}

