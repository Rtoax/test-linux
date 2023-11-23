#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>


#define SHM_FILE	"wurstverschwendung"

int main(void)
{
	struct stat st;
	void *p;
	int fd, shm_fd, rc;
	pid_t pid;

	shm_fd = shm_open(SHM_FILE, O_RDWR | O_CREAT, 0777);
	if (shm_fd == -1) {
		perror("shm_open");
		exit(1);
	}

	rc = stat("/bin/ls", &st);
	if (rc == -1) {
		perror("stat");
		exit(1);
	}

	rc = ftruncate(shm_fd, st.st_size);
	if (rc == -1) {
		perror("ftruncate");
		exit(1);
	}

	p = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,
		shm_fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	fd = open("/bin/ls", O_RDONLY, 0);
	if (fd == -1) {
		perror("openls");
		exit(1);
	}

	rc = read(fd, p, st.st_size);
	if (rc == -1) {
		perror("read");
		exit(1);
	}
	if (rc != st.st_size) {
		fputs("Strange situation!\n", stderr);
		exit(1);
	}

	munmap(p, st.st_size);
	close(shm_fd);

	shm_fd = shm_open(SHM_FILE, O_RDONLY, 0);

	pid = fork();
	if (pid == 0) {
		static char *args[] = {
			"hic et nunc",
			"-l",
			"/dev/shm",
			NULL
		};
		extern char **environ;
		fexecve(shm_fd, args, environ);
		perror("fexecve");
	}
	wait(NULL);

	close(shm_fd);
	shm_unlink(SHM_FILE);
	perror("shm_unlink");
	return 0;
}
