#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
	int fd = mkfifo("mkfifo.tmp", 1);
	if (fd == -1)
		return -errno;
	return 0;
}
