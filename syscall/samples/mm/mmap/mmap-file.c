#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/stat.h>

#define MAP_FILENAME	"/etc/os-release"
#define MAP_FILENAME_OUT	"os-release"

int fdin, fdout;
char *pin, *pout;
size_t size;

void cleanup(void)
{
	munmap(pin, size);
	munmap(pout, size);
	close(fdin);
	close(fdout);
}

void sig_handler(int signo)
{
	psignal(signo, "Catch");
	cleanup();
	exit(0);
}

int main(void)
{
	int i, ret;
	struct stat st;
	pid_t child;

	signal(SIGINT, sig_handler);

	fdin = open(MAP_FILENAME, O_RDONLY);
	if (fdin == -1) {
		perror("open\n");
		exit(1);
	}
	/* remove the exist one */
	ret = access(MAP_FILENAME_OUT, F_OK);
	if (!ret)
		unlink(MAP_FILENAME_OUT);

	fdout = open(MAP_FILENAME_OUT, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1) {
		perror("open\n");
		exit(1);
	}

	ret = stat(MAP_FILENAME, &st);
	if (ret == -1) {
		perror("stat");
		exit(1);
	}
	size = st.st_size;

	ftruncate(fdout, size);

	/**
	 * mmap(2): MAP_PRIVATE
	 *
	 * Create a private copy-on-write mapping. Updates to the mapping are
	 * not visible to other processes mapping the same file, and are not
	 * carried through to the underlying file. It is unspecified whether
	 * changes made to the file after the mmap() call are visible in the
	 * mapped region.
	 */
	pin = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fdin, 0);
	if (pin == MAP_FAILED) {
		perror("mmap\n");
		exit(1);
	}
	printf("mmap %p\n", pin);

#ifdef MREMAP
	pin = mremap(pin, size, size, MREMAP_MAYMOVE);
	if (pin == MAP_FAILED) {
		perror("mremap\n");
		exit(1);
	}
	printf("mremap %p\n", pin);
#endif

	/* Can't write in child if MAP_PRIVATE */
	pout = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_SHARED, fdout, 0);
	if (pout == MAP_FAILED) {
		perror("mmap\n");
		exit(1);
	}

	child = fork();

	if (child == 0) {
		for (i = 0; i < size; i++) {
			char ch = *(pin + i);
			putchar(ch);
			pout[i] = ch;
		}
		msync(pout, size, MS_SYNC);
		exit(0);
	}

	wait(NULL);

	cleanup();

	return 0;
}
