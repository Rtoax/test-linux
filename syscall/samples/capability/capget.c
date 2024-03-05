#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/capability.h>


int main(void)
{
	int ret;
	char buf[1024];

	cap_user_header_t hdrp = (cap_user_header_t)&buf[0];
	cap_user_data_t datap = (cap_user_data_t)&buf[100];

	ret = capget(hdrp, NULL);
	if (ret < 0) {
		fprintf(stderr, "capget error: %s", strerror(errno));
	}

	hdrp->pid = getpid();

	capget(hdrp, datap);

	printf("%x,%d: %x,%x,%x\n",
		hdrp->version, hdrp->pid,
		datap->effective, datap->permitted, datap->inheritable);

	return 0;
}
