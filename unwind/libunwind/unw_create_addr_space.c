#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <libunwind.h>
#include <libunwind-ptrace.h>

int main(void)
{
	unw_addr_space_t addr_space = unw_create_addr_space(&_UPT_accessors, __BYTE_ORDER__);
	if (!addr_space) {
		fprintf(stderr, "create unw addr space failed %s\n", strerror(errno));
		return -1;
	}
	return 0;
}
