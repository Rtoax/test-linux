#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <syscall.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>

#include <linux/unistd.h>
#if defined __i386__ || defined __x86_64__
#include <asm/ldt.h>
#endif

int sys_get_thread_area(struct user_desc *u_info)
{
	int ret = syscall(__NR_get_thread_area, u_info);
	return ret >= 0 ? ret : -errno;
}

int main(void)
{
	int ret;
	struct user_desc u_info;

	memset(&u_info, 0, sizeof(u_info));

	u_info.entry_number = 1;

	ret = sys_get_thread_area(&u_info);
	if (ret != 0) {
		fprintf(stderr, "get_thread_area failed: %s\n",
			strerror(errno));
		exit(1);
	}

	printf("base_addr: %x\n", u_info.base_addr);
	printf("limit: %x\n", u_info.limit);

	return 0;
}
