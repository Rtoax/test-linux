#include <stdio.h>
#include <libelf.h>
#include <gelf.h>

/**
 * $ nm /lib64/libc.so.6 | grep _GLOBAL_OFFSET_TABLE_
 * 00000000001f9bc0 d _GLOBAL_OFFSET_TABLE_
 */
extern GElf_Addr _GLOBAL_OFFSET_TABLE_[];

int main(void)
{
	printf("%p\n", _GLOBAL_OFFSET_TABLE_[0]);
	return 0;
}

