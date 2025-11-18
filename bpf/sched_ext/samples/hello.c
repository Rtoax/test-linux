#include <stdio.h>
#include <signal.h>
#include "hello.skel.h"

sig_atomic_t stop = 0;

void sig_handler(int sig)
{
	stop = 1;
}

static int libbpf_print_fn(enum libbpf_print_level level, const char *format,
			   va_list args)
{
	if (level == LIBBPF_DEBUG)
		return 0;
	return vfprintf(stderr, format, args);
}

int main(void)
{
	int err;
	struct hello_bpf *skel;

	libbpf_set_print(libbpf_print_fn);
	signal(SIGINT, sig_handler);

	skel = hello_bpf__open();
	if (!skel) {
		fprintf(stderr, "ERROR: open skel failed.\n");
		exit(1);
	}

	err = hello_bpf__load(skel);
	if (err) {
		fprintf(stderr, "ERROR: load skel failed.\n");
		exit(1);
	}

	err = hello_bpf__attach(skel);
	if (err) {
		fprintf(stderr, "ERROR: attach skel failed.\n");
		exit(1);
	}

	printf("Sched ext running...\n");

	while (!stop) {
		sleep(1);
	}

	printf("Bye...\n");

	hello_bpf__detach(skel);
	hello_bpf__destroy(skel);
	return 0;
}
