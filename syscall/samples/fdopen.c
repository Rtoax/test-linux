#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int main(void)
{
	int fd = open("a.txt", O_CREAT | O_CLOEXEC | O_RDWR, 0644);
	assert(fd > 2);

	FILE *fp = fdopen(fd, "a");

	fprintf(fp, "Hello world.\n");

	fclose(fp);
	perror("fclose");

	/* Double close: Bad file descriptor */
	close(fd);
	if (errno != EBADF)
		fprintf(stderr, "ERROR: close() should return EBADF here.\n");
	perror("close");
}
