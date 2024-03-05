#include <stdio.h>
#include <unistd.h>
#include <sys/capability.h>


int main(void)
{
	char buf[1024];

	cap_user_header_t hdrp = (cap_user_header_t)&buf[0];
	cap_user_data_t datap = (cap_user_data_t)&buf[100];

	hdrp->pid = getpid();
	hdrp->version = _LINUX_CAPABILITY_VERSION_1;

	capget(hdrp, datap);

	printf("%x,%d: %x,%x,%x\n",
		hdrp->version, hdrp->pid,
		datap->effective, datap->permitted, datap->inheritable);

	return 0;
}
