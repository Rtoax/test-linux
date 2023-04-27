#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/kvm.h>
#include <stdio.h>


int open_dev_kvm(void)
{
	int kvm = open("/dev/kvm", O_RDWR | O_CLOEXEC);
	if (kvm <= 0) {
		fprintf(stderr, "open /dev/kvm %d\n", kvm);
		exit(1);
	}
	int ret = ioctl(kvm, KVM_GET_API_VERSION, NULL);
	if (ret != KVM_API_VERSION) {
		fprintf(stderr, "KVM_GET_API_VERSION expoected 12 but got %d.", ret);
		exit(1);
	}

	return kvm;
}

