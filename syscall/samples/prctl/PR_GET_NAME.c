#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/prctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


int get_name(char *buffer)
{
	int ret;
	ret = prctl(PR_GET_NAME, buffer, 0, 0, 0);
	if (ret) {
		perror("prctl buffer");
		return ret;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int ret;
	const char *const setname = "rongtao";
	char buffer[64];

	ret = prctl(PR_SET_NAME, setname, 0, 0, 0);
	if (ret < 0 && ! (errno == EINVAL)) {
		perror("prctl PR_SET_NAME");
	}
	printf("set: %s\n", setname);

	/* Bad address */
	get_name(NULL);
	{
		int pagesize = getpagesize();
		char *s = mmap(NULL, pagesize, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		/* no enough space, so Bad address */
		get_name(s + getpagesize() - 4);
		munmap(s, pagesize);
	}

	get_name(buffer);
	if (ret) {
		perror("prctl buffer");
		return ret;
	}
	if (strcmp(setname, buffer)) {
		fprintf(stderr, "prctl fail to PR_GET_NAME.\n");
		return 1;
	}
	printf("get: %s\n", buffer);
	{
		/**
		 * PR_SET_NAME = /proc/PID/comm
		 */
		char proc[64];
		snprintf(proc, sizeof(proc), "/proc/%d/comm", getpid());
		FILE *fp = fopen(proc, "r");
		fread(buffer, sizeof(buffer), 1, fp);
		printf("proc: %s\n", buffer);
		fclose(fp);
	}

	return 0;
}
