#include <bfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <getopt.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>

#include "proc_helpers.h"
#include "bfd_helpers.h"

#define BFD_ERR	bfd_errmsg(bfd_get_error())

static unsigned long base_vma = 0;
static bool test_libc = 0;

#include "data.c"

int main(int argc, char *argv[]);

void usage(const char *prog)
{
	fprintf(stderr, "\n"
		"-f, --file     specify file to bfd, default: %s\n"
		"-b, --base     specify base vma address, format: 0x0xxxx\n"
		"-c, --libc     test libc.so\n"
		"-h, --help     print this info\n",
		prog
	);
}

void handle_sym(const char *prefix, asymbol *sym, bool firstline)
{
	int i;
	bfd *abfd;
	const char *name, *version_string = NULL;
	bool hidden = false;
	symbol_info symbolinfo;
	asection *asect;

	abfd = sym->the_bfd;

	(void)abfd;

	if (sym->section == NULL)
		return;

#if defined(TEST_SYMBOL_VALUE)
	if (!base_vma)
		base_vma = proc_maps_exec_base_addr(NULL);
#else
	if (firstline)
		printf("%-4s %-16s %-4s %-8s %-16s %-16s %-16s %-8s\n", "PFX",
			"VALUE", "TYPE", "LOCAL", "VMA", "LMA", "SECTION",
			"SYM");
#endif

#if defined(BFD_HAS_BFD_ASYMBOL_SECTION)
	asect = bfd_asymbol_section(sym);
#else
	asect = sym->section;
#endif

	if ((sym->flags & (BSF_SECTION_SYM | BSF_SYNTHETIC)) == 0)
#if defined(BFD_HAS_BFD_GET_SYMBOL_VERSION_STRING)
		version_string = bfd_get_symbol_version_string(abfd,
						sym, true,
						(bfd_boolean *)&hidden);
#else
	{
		version_string = "";
		(void)hidden;
		fprintf(stderr, "WARNING: Not define bfd_get_symbol_version_string().\n");
	}
#endif

	if (bfd_is_und_section(asect))
		hidden = true;

	/**
	 * symbolinfo.name = bfd_asymbol_name(sym);
	 */
	bfd_symbol_info(sym, &symbolinfo);

/**
 * Q: Could we use BFD to resolve all symbols?
 */
#if defined(TEST_SYMBOL_VALUE)
	(void)version_string;

	char buff[512];
	bool synthetic = false;

	if (!strcmp(tl_bfd_section_name(asect), ".plt"))
		synthetic = true;

# define TEST_SYM(s)	\
	if (!strcmp(#s, symbolinfo.name) || \
	    (synthetic && !strcmp(#s, tl_bfd_pure_name(sym, buff, sizeof(buff))))) {	\
		unsigned long v1 = (unsigned long)&s;	\
		unsigned long v2 = symbolinfo.value + base_vma;	\
		printf("%s: " #s ": %lx %lx %s in %s\n", prefix, v1, v2,	\
			v1 == v2 ? "\033[32mOK\033[m" : "\033[31mNot OK\033[m",	\
			tl_bfd_section_name(asect));	\
	}

	/**
	 * Self
	 */
	TEST_SYM(bss_count);
	TEST_SYM(static_bss_count);
	TEST_SYM(data_count);
	TEST_SYM(static_data_count);
	TEST_SYM(rodata_count);
	TEST_SYM(static_rodata_count);
	TEST_SYM(main);
	TEST_SYM(usage);
	TEST_SYM(static_func);

	/**
	 * libc.so
	 */
	TEST_SYM(printf);
	TEST_SYM(puts);
	TEST_SYM(pthread_create);
	TEST_SYM(errno);
	TEST_SYM(stderr);
# undef TEST_SYM
#else
	/**
	 * type: see nm(1)
	 */
	printf("%-4s %-16lx %-4c %-8s %-16lx %-16lx %-16s %s <%s>\n",
		prefix,
		symbolinfo.value,
		symbolinfo.type,
		bfd_is_local_label(abfd, sym) ? "YES" : "-",
#if defined(BFD_HAS_BFD_SECTION_VMA)
		bfd_section_vma(asect),
#elif defined(BFD_HAS_BFD_SECTION_VMA2)
		bfd_section_vma(abfd, asect),
#endif
#if defined(BFD_HAS_BFD_SECTION_LMA)
		bfd_section_lma(asect),
#elif defined(BFD_HAS_BFD_SECTION_LMA2)
		bfd_section_lma(abfd, asect),
#else
		asect->lma,
#endif
		tl_bfd_section_name(asect),
		symbolinfo.name,
		version_string ?: "-");
#endif
}

int main(int argc, char *argv[])
{
	int ret, i;
	bfd *abfd;
	char **matching;
	asection *asect;
	asymbol **symbol_table, **dynamic_symbol_table;
	asymbol *synthetic_symbols;
	long storage_needed, dynamic_storage_needed;
	long number_of_symbols, number_of_dynamic_symbols;
	long number_of_synth_symbols;
	char *filepath;
	char buffer[PATH_MAX];

	struct option options[] = {
		{"file", required_argument, 0, 'f'},
		{"base", required_argument, 0, 'b'},
		{"libc", no_argument, 0, 'c'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};

	filepath = argv[0];

	while (1) {
		int option_index = 0;
		int c = getopt_long(argc, argv, "f:b:ch", options, &option_index);

		if (c == -1)
			break;

		switch (c) {
		case 'f':
			filepath = optarg;
			printf("Set file name %s\n", filepath);
			break;
		case 'c':
			filepath = proc_maps_libc_base_name(buffer, sizeof(buffer));
			base_vma = proc_maps_libc_base_addr(NULL);
			printf("Set libc %s\n", filepath);
			break;
		case 'b':
			if (optarg[0] != '0' || optarg[1] != 'x') {
				fprintf(stderr, "Wrong format, start with '0x'\n");
				exit(1);
			}
			base_vma = strtoull(optarg, NULL, 16);
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

	tl_bfd_init();

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

	if (base_vma)
		printf("Text VMA 0x%lx\n", base_vma);

	/**
	 * If abfd is target process, we should set vma address, it's useful
	 * for PIE process.
	 */
	for (asect = abfd->sections; asect != NULL; asect = asect->next) {
		flagword flags = tl_bfd_section_flags(asect);
		if ((flags & SEC_CODE) && base_vma)
			/**
			 * FIXME: set vma, but symbol value not changed
			 */
#if defined(BFD_HAS_BFD_SET_SECTION_VMA)
			bfd_set_section_vma(asect, base_vma);
#elif defined(BFD_HAS_BFD_SET_SECTION_VMA2)
			bfd_set_section_vma(abfd, asect, base_vma);
#endif
	}

	if (!(bfd_get_file_flags(abfd) & HAS_SYMS)) {
		fprintf(stderr, "No syms in %s\n", bfd_get_filename(abfd));
		goto load_dynamic_sym;
	}

	storage_needed = bfd_get_symtab_upper_bound(abfd);
	symbol_table = (asymbol **)malloc(storage_needed);
	number_of_symbols = bfd_canonicalize_symtab(abfd, symbol_table);

load_dynamic_sym:
	/**
	 * FIXME: why symbols == dynamic symbols?
	 */
	dynamic_storage_needed = bfd_get_dynamic_symtab_upper_bound(abfd);
	dynamic_symbol_table = (asymbol **)malloc(dynamic_storage_needed);
	number_of_dynamic_symbols = bfd_canonicalize_dynamic_symtab(abfd, dynamic_symbol_table);

	/**
	 * What's synthetic symtab?
	 * All print symbol has '@plt' suffix
	 */
	number_of_synth_symbols = bfd_get_synthetic_symtab(abfd,
				number_of_symbols, symbol_table,
				number_of_dynamic_symbols, dynamic_symbol_table,
				&synthetic_symbols);

	printf("Scanning %ld symbols\n", number_of_symbols);
	printf("Scanning %ld dynamic symbols\n", number_of_dynamic_symbols);
	printf("Scanning %ld synthetic symbols\n", number_of_synth_symbols);

#ifdef TEST_bfd_print_symbol_vandf
	for (i = 0; i < number_of_symbols; i++) {
		bfd_print_symbol_vandf(abfd, stdout, symbol_table[i]);
		fprintf(stdout, "\n");
	}
#endif

	for (i = 0; i < number_of_symbols; i++) {
		asymbol *sym = symbol_table[i];
		handle_sym("Sym", sym, i == 0);
	}

	for (i = 0; i < number_of_dynamic_symbols; i++) {
		asymbol *sym = dynamic_symbol_table[i];
		handle_sym("Dyn", sym, i == 0);
	}

	for (i = 0; i < number_of_synth_symbols; i++) {
		asymbol *sym = &synthetic_symbols[i];
		handle_sym("Syn", sym, i == 0);
	}

	if (symbol_table)
		free(symbol_table);
	if (dynamic_symbol_table)
		free(dynamic_symbol_table);
	if (synthetic_symbols)
		free(synthetic_symbols);
close:
	bfd_close(abfd);
	return 0;
}
