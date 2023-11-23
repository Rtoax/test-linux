#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/prctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


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

	ret = prctl(PR_GET_NAME, buffer, 0, 0, 0);
	if (strcmp(setname, buffer)) {
		fprintf(stderr, "prctl fail to PR_GET_NAME.\n");
		return 1;
	}
	printf("get: %s\n", buffer);

	return 0;
}
