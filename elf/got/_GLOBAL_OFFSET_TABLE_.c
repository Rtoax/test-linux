#include <stdio.h>
#include <libelf.h>
#include <gelf.h>

#define Addr	unsigned long

/**
 * _GLOBAL_OFFSET_TABLE_ is in libc.so.6.
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
#if defined(M32)
Addr addr_dl_runtime_resolve(void)
#else
Addr addr_dl_runtime_resolve_xsavec(void)
#endif
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
	printf("addr_dl_runtime_resolve = 0x%lx\n", addr_dl_runtime_resolve_xsavec());
#endif
	return 0;
}

