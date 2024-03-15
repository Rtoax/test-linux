#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>

#define STACK_SIZE (1024 * 1024)

static char stack[STACK_SIZE];

int setip(char *name, char *addr, char *netmask)
{
	struct ifreq ifr;
	int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);

	strncpy(ifr.ifr_name, name, IFNAMSIZ);

	ifr.ifr_addr.sa_family = AF_INET;
	inet_pton(AF_INET, addr, ifr.ifr_addr.sa_data + 2);
	ioctl(fd, SIOCSIFADDR, &ifr);

	inet_pton(AF_INET, netmask, ifr.ifr_addr.sa_data + 2);
	ioctl(fd, SIOCSIFNETMASK, &ifr);

	/* get flags */
	ioctl(fd, SIOCGIFFLAGS, &ifr);
	strncpy(ifr.ifr_name, name, IFNAMSIZ);
	ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);
	/* set flags */
	ioctl(fd, SIOCSIFFLAGS, &ifr);

	return 0;
}

int child(void *arg)
{
	int ret;
	sleep(1);
	sethostname("myhost", 6);

	/* TODO: switch root to rootfs/initramfs */
	ret = chroot("/");
	if (ret) {
		perror("chroot");
		return 0;
	}
	chdir("/");
	mount("proc", "/proc", "proc", MS_PRIVATE, NULL);

	setip("veth1", "10.0.0.15", "255.0.0.0");
	execlp("/bin/sh", "/bin/sh", NULL);

	return 1;
}

int main(void)
{
	int ret;
	char buf[255];
	int flags = CLONE_NEWNET | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID |
		    CLONE_NEWNS | SIGCHLD;
	pid_t pid = clone(child, stack + STACK_SIZE, flags, NULL);
	if (pid == -1) {
		perror("clone");
		return -1;
	}

	sprintf(buf,
		"sudo ip link add name veth0 type veth peer name veth1 netns %d",
		pid);
	system(buf);
	setip("veth0", "10.0.0.13", "255.0.0.0");

	ret = waitpid(pid, NULL, 0);
	if (ret) {
		perror("waitpid");
		return 0;
	}
	return 0;
}
