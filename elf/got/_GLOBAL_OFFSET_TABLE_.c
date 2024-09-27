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

/**
 * (gdb) disassemble /s _GLOBAL_OFFSET_TABLE_[2],+0x16
 */
Addr _dl_runtime_resolve(void)
{
	return _GLOBAL_OFFSET_TABLE_[2];
}

int main(void)
{
	printf("size of Addr = %ld\n", sizeof(Addr));

	printf("_GLOBAL_OFFSET_TABLE_ = 0x%lx\n", _GLOBAL_OFFSET_TABLE_);
#if !defined(M32)
	printf("elf_machine_dynamic = 0x%lx\n", elf_machine_dynamic());
	printf("_dl_runtime_resolve = 0x%lx\n", _dl_runtime_resolve());
#endif
	return 0;
}

