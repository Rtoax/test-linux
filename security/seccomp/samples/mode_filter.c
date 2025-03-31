/**
 * Seccomp bpf demo
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/prctl.h>
#include <linux/seccomp.h>
#include <linux/filter.h>
#include <linux/unistd.h>

#ifdef CONFIG_NO_SECCOMP
void configure_seccomp(void) {}
#else
void configure_seccomp(void)
{
	struct sock_filter filter[] = {
		BPF_STMT(BPF_LD | BPF_W | BPF_ABS, (offsetof(struct seccomp_data, nr))),
		BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_write, 0, 1),
		BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
#if defined(__aarch64__) || defined(__riscv) || defined(__loongarch64)
		BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_openat, 0, 3),
#else
		BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, __NR_open, 0, 3),
#endif
		BPF_STMT(BPF_LD | BPF_W | BPF_ABS, (offsetof(struct seccomp_data, args[1]))),
		BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, O_RDONLY, 0, 1),
		BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
		BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL)
	};
	struct sock_fprog prog = {
		.len = (unsigned short)(sizeof(filter) / sizeof(filter[0])),
		.filter = filter,
	};

	printf("Configuring seccomp\n");
	prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
}
#endif

int main(int argc, char *argv[])
{
	int infd, outfd;
	ssize_t read_bytes;
	char buffer[1024];
	char *from = "/etc/os-release";
	char *to = "./os-release";

	printf("Ducplicating file '%s' to '%s'\n", from, to);

	configure_seccomp();

	printf("Opening '%s' for reading\n", from);
	infd = open(from, O_RDONLY);
	if (infd <= 0) {
		fprintf(stderr, "Opening '%s' failed, %m\n", from);
		exit(1);
	}

	printf("Opening '%s' for writing\n", to);
	outfd = open(to, O_WRONLY | O_CREAT, 0644);
	if (outfd <= 0) {
		fprintf(stderr, "Opening '%s' failed, %m\n", to);
		exit(1);
	}

	while ((read_bytes = read(infd, &buffer, 1024)) > 0)
		write(outfd, &buffer, (ssize_t)read_bytes);

	close(infd);
	close(outfd);
	return 0;
}

