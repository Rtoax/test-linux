#include <stdio.h>
#include <unistd.h>
#include <bcc/bcc_syms.h>

void foo(void)
{
}

void bar(void)
{
}

int main(int argc, char *argv[])
{
	int pid;
	void *psyms;
	struct bcc_symbol sym;
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

	psyms = bcc_symcache_new(pid, &symopts);
	if (!psyms) {
		fprintf(stderr, "bcc_symcache_new failed.\n");
		return -1;
	}

	bcc_symcache_resolve_no_demangle(psyms, (unsigned long)main, &sym);
	printf("name: %s\n", sym.name);

	bcc_symcache_resolve(psyms, (unsigned long)foo, &sym);
	printf("name: %s\n", sym.name);

	/* TODO: How to list all symbols in memory? */

	bcc_free_symcache(psyms, pid);

	return 0;
}
