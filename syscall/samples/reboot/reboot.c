/**
 * linux: int reboot(int magic, int magic2, int op, void *arg);
 * glibc: int reboot(int op);
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/reboot.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int err, op = RB_AUTOBOOT;

#ifdef POWEROFF
	op = RB_POWER_OFF;
#elif defined(KEXEC)
	/* work with CONFIG_KEXEC=y */
	op = RB_KEXEC;
#elif defined(CAD)
	/**
	 * see also /proc/sys/kernel/ctrl-alt-del
	 * or: $ sudo bpftrace -e 'begin { printf("%d\n", *kaddr("C_A_D")) }'
	 */
	fprintf(stderr, "%s [cad=<0|1>]\n", argv[0]);
	op = RB_DISABLE_CAD;

	for (int i = 1; i < argc; i++) {
		char *cad = argv[i];
		if (!strncmp(cad, "cad=", 4)) {
			op = atoi(cad + 4) == 0 ? RB_DISABLE_CAD :
						  RB_ENABLE_CAD;
		}
	}
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
