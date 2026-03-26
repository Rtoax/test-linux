#include <stdio.h>
#include <sys/reboot.h>
#include <unistd.h>

int main(void)
{
	int err, op = RB_AUTOBOOT;

#ifdef POWEROFF
	op = RB_POWER_OFF;
#elif defined(KEXEC)
	/* work with CONFIG_KEXEC=y */
	op = RB_KEXEC;
#endif

	err = geteuid();
	if (err) {
		fprintf(stderr, "Need root permission.\n");
		return -err;
	}

	sync();

	err = reboot(op);
	if (err) {
		fprintf(stderr, "reboot: %m.\n");
		return -err;
	}

	return 0;
}
