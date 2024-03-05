#include <stdio.h>
#include <sys/capability.h>


int main(void)
{
	char buf[1024];

	cap_user_header_t hdrp = (cap_user_header_t)&buf[0];
	cap_user_data_t datap = (cap_user_data_t)&buf[100];

	capget(hdrp, datap);

	printf("%x,%d: %d,%d,%d\n",
		hdrp->version, hdrp->pid,
		datap->effective, datap->permitted, datap->inheritable);

	return 0;
}
