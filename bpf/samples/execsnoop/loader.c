#include <stdio.h>
#include <signal.h>
#include "bpf_load.h"
#include "trace_helpers.h"


void sig_handler(int sig)
{
	read_trace_pipe_stop();
}

int main(int argc, char **argv)
{
	signal(SIGINT, sig_handler);

	if (load_bpf_file("bpf_program.bpf.o") != 0) {
		printf("The kernel didn't load the BPF program\n");
		return -1;
	}

	read_trace_pipe();

	return 0;
}
