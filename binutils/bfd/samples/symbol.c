#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define BFD_ERR	bfd_errmsg(bfd_get_error())

int main(int argc, char *argv[])
{
	int ret, i;
	bfd *abfd;
	char **matching;
	asection *asect;
	asymbol **symbol_table;
	long storage_needed;
	long number_of_symbols;
	symbol_info symbolinfo;
	char *filepath;

	filepath = argv[0];

	ret = bfd_init();
	if (ret != BFD_INIT_MAGIC) {
		fprintf(stderr, "bfd_init failed.\n");
		exit(1);
	}

	abfd = bfd_openr(filepath, NULL);
	if (!abfd) {
		fprintf(stderr, "Open %s failed, %s.\n", filepath, BFD_ERR);
		exit(1);
	}

	if (!bfd_check_format_matches(abfd, bfd_object, &matching)) {
		fprintf(stderr, "format_matches");
		goto close;
	}

	/**
	 * If abfd is target process, we should set vma address, it's useful
	 * for PIE process.
	 */
	for (asect = abfd->sections; asect != NULL; asect = asect->next) {
		/**
		 * FIXME: section belongs to a VMA.
		 */
		//bfd_set_section_vma(asect, 0x0);
	}

	storage_needed = bfd_get_symtab_upper_bound(abfd);

	symbol_table = (asymbol **)malloc(storage_needed);
	number_of_symbols = bfd_canonicalize_symtab(abfd, symbol_table);

	printf("Scanning %ld symbols\n", number_of_symbols);

	for (i = 0; i < number_of_symbols; i++) {
		bfd_print_symbol_vandf(abfd, stdout, symbol_table[i]);
		fprintf(stdout, "\n");
	}

	printf("%-16s %-4s %-8s %-16s %-8s\n", "VALUE", "TYPE", "LOCAL", "VMA",
		"SYM");
	for (i = 0; i < number_of_symbols; i++) {
		if (symbol_table[i]->section == NULL)
			continue;

		asect = symbol_table[i]->section;

		bfd_symbol_info(symbol_table[i], &symbolinfo);

		/**
		 * type: see nm(1)
		 */
		printf("%-16lx %-4c %-8s %-16lx %s\n",
			symbolinfo.value,
			symbolinfo.type,
			bfd_is_local_label(abfd, symbol_table[i]) ? "YES" : "-",
			bfd_section_vma(asect),
			symbolinfo.name);
	}

	free(symbol_table);
close:
	bfd_close(abfd);
	return 0;
}
