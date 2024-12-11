#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <syscall.h>
#include <fcntl.h>

/* Get the RSS information in an OS-specific way.
 *
 * ---------------------------------------
 * *** Resident Set Size 实际使用物理内存（包括共享内存占用的内存）
 *
 * WARNING: the function hpmalloc_get_rss() is not designed to be fast
 * and may not be called in the busy loops where Redis tries to release
 * memory expiring or swapping out objects.
 *
 * For this kind of "fast RSS reporting" usages use instead the
 * function RedisEstimateRSS() that is a much faster (and less precise)
 * version of the function. */
size_t hpmalloc_get_rss(pid_t pid)
{
	int page = sysconf(_SC_PAGESIZE);
	size_t rss;
	char buf[4096];
	char filename[256];
	int fd, count;
	char *p, *x;

	snprintf(filename,256,"/proc/%d/stat", pid);
	if ((fd = open(filename,O_RDONLY)) == -1)
		return 0;

	if (read(fd,buf,4096) <= 0) {
		close(fd);
		return 0;
	}
	close(fd);

	p = buf;

	/* RSS is the 24th field in /proc/<pid>/stat */
	count = 23;
	while (p && count--) {
		p = strchr(p, ' ');
		if (p)
			p++;
	}

	if (!p)
		return 0;

	x = strchr(p, ' ');
	if (!x)
		return 0;

	*x = '\0';

	rss = strtoll(p,NULL,10);
	rss *= page;

	return rss;
}

int main(void)
{
	printf("%ld\n", hpmalloc_get_rss(getpid()));
	return 0;
}

