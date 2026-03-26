#include <stdio.h>
#include <sys/reboot.h>
#include <unistd.h>

int main(void)
{
	int err;

	err = geteuid();
	if (err) {
		fprintf(stderr, "Need root permission.\n");
		return -err;
	}

	sync();

	err = reboot(RB_POWER_OFF);
	if (err) {
		fprintf(stderr, "reboot: %m.\n");
		return -err;
	}

	return 0;
}
