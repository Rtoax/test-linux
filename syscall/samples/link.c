#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "syscall_helpers.h"


int main(void)
{
	int ret;

	create_file("rong.out", 'a', 0);

	/* Make hard link (same inode) */
	ret = link("rong.out", "rong2.out");
	printf("link ret: %d\n", ret);

	unlink("rong.out");
	unlink("rong2.out");

	return 0;
}
