#include <bcc/bcc_syms.h>

int main(void)
{
	int pid = 1;
	void *psyms;
	struct bcc_symbol_option symopts = {
		.use_debug_file = 1,
		.check_debug_file_crc = 1,
		.lazy_symbolize = 0,
		.use_symbol_type = BCC_SYM_ALL_TYPES,
	};

	psyms = bcc_symcache_new(pid, &symopts);

	/* TODO: How to list all symbols in memory? */

	bcc_free_symcache(psyms, pid);

	return 0;
}
