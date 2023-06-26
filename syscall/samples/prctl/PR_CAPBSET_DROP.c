#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/prctl.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int ret;
	int cap;

	for (cap = 0; cap < 2; cap++) {
		ret = prctl(PR_CAPBSET_DROP, cap, 0, 0, 0);
		if (ret < 0 && ! (errno == EINVAL)) {
			perror("prctl drop bounding:");
		}
	}

	return 0;
}
