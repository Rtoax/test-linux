#include <gelf.h>
#include <stdio.h>
#include <link.h>
#include <sys/auxv.h>

#define Addr	unsigned long
#define __unused	__attribute__((unused))

#if defined(M32)
# define Elf_Dyn	Elf32_Dyn
#else
# define Elf_Dyn	Elf64_Dyn
#endif

static Elf_Dyn __unused *dynamic = NULL;
static struct link_map __unused *lm = NULL;

void dump_link_map(struct link_map *l)
{
	printf("link_map: l_addr %zx\n", l->l_addr);
	printf("link_map: l_name %s\n", l->l_name);
	if (l->l_next)
		dump_link_map(l->l_next);
}

void dump_dynamic(Elf_Dyn *dynamic)
{
	if (!dynamic)
		return;
	Elf_Dyn *dyn = dynamic;

	while (dyn) {
		switch (dyn->d_tag) {
#define CASE(V)	case DT_##V: printf("0x%016zx %-16s\n", dyn->d_tag, #V); break;
		CASE(NEEDED);
		CASE(PLTRELSZ);
		CASE(PLTGOT);
		CASE(HASH);
		CASE(STRTAB);
		CASE(SYMTAB);
		CASE(RELA);
		CASE(RELASZ);
		CASE(RELAENT);
		CASE(STRSZ);
		CASE(SYMENT);
		CASE(INIT);
		CASE(FINI);
		CASE(SONAME);
		CASE(RPATH);
		CASE(SYMBOLIC);
		CASE(REL);
		CASE(RELSZ);
		CASE(RELENT);
		CASE(PLTREL);
		CASE(DEBUG);
		CASE(TEXTREL);
		CASE(JMPREL);
		CASE(BIND_NOW);
		CASE(INIT_ARRAY);
		CASE(FINI_ARRAY);
		CASE(INIT_ARRAYSZ);
		CASE(FINI_ARRAYSZ);
		CASE(RUNPATH);
		CASE(FLAGS);
		CASE(FLAGS_1);
		CASE(ENCODING);
# if ENCODING != PREINIT_ARRAY
		CASE(PREINIT_ARRAY);
# endif
		CASE(PREINIT_ARRAYSZ);
		CASE(SYMTAB_SHNDX);
# if defined(__x86_64__) || defined(__i386__)
#  if defined(DT_RELRSZ) && DT_NUM != DT_RELRSZ
		CASE(RELRSZ);
#  endif
#  if defined(DT_RELR)
		CASE(RELR);
#  endif
#  if defined(DT_RELRENT)
		CASE(RELRENT);
#  endif
# endif
		CASE(NUM);
		CASE(LOOS);
		CASE(HIOS);
		CASE(LOPROC);
		CASE(HIPROC);
		CASE(GNU_HASH);
		CASE(VERNEED);
		CASE(VERNEEDNUM);
		CASE(VERSYM);
		CASE(NULL);
		default:
			break;
#undef CASE
		}
		if (dyn->d_tag == DT_FLAGS_1) {
			if (dyn->d_un.d_val & DF_1_PIE) {
				printf("%18s   is PIE\n", "");
			}
		}
		if (dyn->d_tag == DT_NULL)
			break;
		dyn++;
	}
	return;
}

/**
 * _GLOBAL_OFFSET_TABLE_
 *
 * - define in libc.so.6;
 * - GOT[plt] in .got.plt section;
 * - var _GLOBAL_OFFSET_TABLE_ start from .got.plt section;
 *
 * .got entries are never resolved lazily.
 * .got.plt entries can be resolved lazily.
 */
extern const Addr _GLOBAL_OFFSET_TABLE_[];

off_t pie_off(void)
{
	size_t ehdr_size;
	unsigned long phdr_start;

#if !defined(PIE)
	return 0;
#endif

	if (sizeof(void *) == 4) {
		ehdr_size = sizeof(Elf32_Ehdr);
	} else if (sizeof(void *) == 8) {
		ehdr_size = sizeof(Elf64_Ehdr);
	}

	phdr_start = getauxval(AT_PHDR);
	return phdr_start - ehdr_size;
}

Addr elf_machine_dynamic(void)
{
	/**
	 * .dynamic section, check with: 'readelf -dW'.
	 *
	 * If program is PIE, GOT[0] need append the offset of load address.
	 *
	 * FIXME: link_map(GOT[1] or GOT[5]) is zero before program running,
	 * .dynamic(GOT[0]) is not zero.
	 */
	return _GLOBAL_OFFSET_TABLE_[0] + pie_off();
}

Addr addr_link_map(void)
{
#if defined(__x86_64__) || defined(__i386__)
	return _GLOBAL_OFFSET_TABLE_[1];
#elif defined(__aarch64__)
	return _GLOBAL_OFFSET_TABLE_[5];
#endif
}

/**
 * (gdb) disassemble /s _GLOBAL_OFFSET_TABLE_[2],+0x16
 */
Addr addr_dl_runtime_resolve(void)
{
#if defined(__x86_64__) || defined(__i386__)
	return _GLOBAL_OFFSET_TABLE_[2];
#elif defined(__aarch64__)
	return _GLOBAL_OFFSET_TABLE_[6];
#endif
}

int main(void)
{
	printf("size of Addr = %zu\n", sizeof(Addr));
	printf("size of Elf64_Dyn = %zu\n", sizeof(Elf64_Dyn));
	printf("size of Elf32_Dyn = %zu\n", sizeof(Elf32_Dyn));
	printf("size of Elf_Dyn = %zu\n", sizeof(Elf_Dyn));

	printf("_GLOBAL_OFFSET_TABLE_ addr = 0x%lx\n", (unsigned long)_GLOBAL_OFFSET_TABLE_);
/**
 * FIXME: Why segfault here??
 */
#if !defined(M32)
	printf("link_map = 0x%lx\n", addr_link_map());
	lm = (void *)addr_link_map();
	dump_link_map(lm);
	printf("elf_machine_dynamic = 0x%lx\n", elf_machine_dynamic());
	dynamic = (void *)elf_machine_dynamic();
	dump_dynamic(dynamic);
	printf("addr_dl_runtime_resolve = 0x%lx\n", addr_dl_runtime_resolve());
#endif

	/**
	 * More @plt
	 */
	/* fwrite@plt */
	fprintf(stderr, "Hello\n");
	dprintf(1, "Hello\n");
	puts("Hello");
	return 0;
}

