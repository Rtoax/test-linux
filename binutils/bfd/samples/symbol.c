#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <getopt.h>

#define BFD_ERR	bfd_errmsg(bfd_get_error())

static unsigned long text_vma = 0;

void usage(const char *prog)
{
	fprintf(stderr, "\n"
		"-f, --file     specify file to bfd, default: %s\n"
		"-t, --text-vma specify text vma address, format: 0x0xxxx\n"
		"-h, --help     print this info\n",
		prog
	);
}

int main(int argc, char *argv[])
{
	int ret, i;
	bfd *abfd;
	char **matching;
	asection *asect;
	asymbol **symbol_table, **dynamic_symbol_table;
	long storage_needed, dynamic_storage_needed;
	long number_of_symbols, number_of_dynamic_symbols;
	char *filepath;

	struct option options[] = {
		{"file", required_argument, 0, 'f'},
		{"text-vma", required_argument, 0, 't'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};

	filepath = argv[0];

	while (1) {
		int option_index = 0;
		int c = getopt_long(argc, argv, "f:t:h", options, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 'f':
			filepath = optarg;
			printf("Set file name %s\n", filepath);
			break;
		case 't':
			if (optarg[0] != '0' || optarg[1] != 'x') {
				fprintf(stderr, "Wrong format, start with '0x'\n");
				exit(1);
			}
			text_vma = strtoull(optarg, NULL, 16);
			break;
		case 'h':
			usage(argv[0]);
			exit(0);
			break;
		case '?':
			usage(argv[0]);
			fprintf(stderr, "Unknown option or requires an argument.\n");
			exit(1);
			break;
		default:
			abort();
		}
	}

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
		fprintf(stderr, "format_matches\n");
		goto close;
	}

	printf("ELF %s\n", filepath);

	if (text_vma)
		printf("Text VMA 0x%lx\n", text_vma);

	/**
	 * If abfd is target process, we should set vma address, it's useful
	 * for PIE process.
	 */
	for (asect = abfd->sections; asect != NULL; asect = asect->next) {
		flagword flags = bfd_section_flags(asect);
		if ((flags & SEC_CODE) && text_vma)
			/**
			 * FIXME: set vma, but symbol value not changed
			 */
			bfd_set_section_vma(asect, text_vma);
	}

	storage_needed = bfd_get_symtab_upper_bound(abfd);
	symbol_table = (asymbol **)malloc(storage_needed);
	number_of_symbols = bfd_canonicalize_symtab(abfd, symbol_table);

	/**
	 * FIXME: why symbols == dynamic symbols?
	 */
	dynamic_storage_needed = bfd_get_dynamic_symtab_upper_bound(abfd);
	dynamic_symbol_table = (asymbol **)malloc(dynamic_storage_needed);
	number_of_dynamic_symbols = bfd_canonicalize_dynamic_symtab(abfd, dynamic_symbol_table);

	printf("Scanning %ld symbols\n", number_of_symbols);
	printf("Scanning %ld dynamic symbols\n", number_of_dynamic_symbols);

#ifdef TEST_bfd_print_symbol_vandf
	for (i = 0; i < number_of_symbols; i++) {
		bfd_print_symbol_vandf(abfd, stdout, symbol_table[i]);
		fprintf(stdout, "\n");
	}
#endif

	printf("%-8s %-16s %-4s %-8s %-16s %-16s %-16s %-8s\n", "IDX", "VALUE",
		"TYPE", "LOCAL", "VMA", "LMA", "SECTION", "SYM");
	for (i = 0; i < number_of_symbols; i++) {
		asymbol *sym = symbol_table[i];
		const char *name, *version_string = NULL;
		bool hidden = false;
		symbol_info symbolinfo;

		if (sym->section == NULL)
			continue;

		asect = bfd_asymbol_section(sym);

		if ((sym->flags & (BSF_SECTION_SYM | BSF_SYNTHETIC)) == 0)
			version_string = bfd_get_symbol_version_string(abfd,
							sym, true, &hidden);

		if (bfd_is_und_section(asect))
			hidden = true;

		/**
		 * symbolinfo.name = bfd_asymbol_name(sym);
		 */
		bfd_symbol_info(sym, &symbolinfo);

		/**
		 * type: see nm(1)
		 */
		printf("%-8d %-16lx %-4c %-8s %-16lx %-16lx %-16s %s <%s>\n",
			i,
			symbolinfo.value,
			symbolinfo.type,
			bfd_is_local_label(abfd, sym) ? "YES" : "-",
			bfd_section_vma(asect),
			bfd_section_lma(asect),
			bfd_section_name(asect),
			symbolinfo.name,
			version_string ?: "-");
	}

	free(symbol_table);
close:
	bfd_close(abfd);
	return 0;
}
