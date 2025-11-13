#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bcc/bcc_syms.h>


int pid;
unsigned long addr;
int verbose = 0;

void parse_args(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++) {
		if (!strncmp(argv[i], "pid=", 4)) {
			pid = atoi(argv[i] + 4);
			if (pid < 1) {
				fprintf(stderr, "ERROR: bad pid %s\n", argv[i]);
				exit(1);
			}
		} else if (!strncmp(argv[i], "addr=", 5)) {
			char *s = argv[i] + 5;
			if (s[0] != '0' && s[1] != 'x') {
				fprintf(stderr, "ERROR: addr must start with 0x\n");
				exit(1);
			}
			addr = strtoul(s, NULL, 16);
			if (addr <= 0) {
				fprintf(stderr, "ERROR: bad addr %s\n", argv[i]);
				exit(1);
			}
		} else if (!strcmp(argv[i], "verbose")) {
			verbose = 1;
		} else {
			fprintf(stderr, "ERROR: unknown %s\n", argv[i]);
			exit(1);
		}
	}
}

void foo(void)
{
}

void bar(void)
{
}

void test_addr(void *psyms, unsigned long addr)
{
	struct bcc_symbol sym;

	bcc_symcache_resolve_no_demangle(psyms, addr, &sym);
	printf("name: %s\n", sym.name);

	bcc_symcache_resolve(psyms, addr, &sym);
	printf("name: %s\n", sym.name);
}

int main(int argc, char *argv[])
{
	void *psyms;
	/**
	 * see bpftrace src/usyms.cpp
	 */
	struct bcc_symbol_option symopts = {
		.use_debug_file = 1,
		.check_debug_file_crc = 1,
		.lazy_symbolize = 0,
		.use_symbol_type = BCC_SYM_ALL_TYPES,
	};

	pid = getpid();

	fprintf(stderr, "%s [pid=<PID>] [addr=<ADDR>] [verbose]\n", argv[0]);
	parse_args(argc - 1, argv + 1);

	psyms = bcc_symcache_new(pid, &symopts);
	if (!psyms) {
		fprintf(stderr, "bcc_symcache_new failed.\n");
		return -1;
	}

	if (pid == getpid()) {
		test_addr(psyms, (unsigned long)foo);
		test_addr(psyms, (unsigned long)bar);
		test_addr(psyms, (unsigned long)main);
	} else {
		test_addr(psyms, addr);
	}

	bcc_free_symcache(psyms, pid);
	return 0;
}
