#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

#if defined(__GLIBC__) && defined(__GLIBC_PREREQ)
# if __GLIBC_PREREQ(2, 16)
#  include <sys/auxv.h>
# endif
#endif

#if __WORDSIZE == 64
typedef Elf64_auxv_t auxv_t;
#else
typedef Elf32_auxv_t auxv_t;
#endif

/**
 * Provides a method for retrieving values from the auxiliary vector.
 *
 * @return Always returns a result.  When the result is 0, check errno
 * to see if an error occurred during processing.
 */
static unsigned long __getauxval(unsigned long type)
{
	unsigned long val = 0;
	int n;

	errno = 0;
	val = getauxval(type);

	if (!val && (errno == ENOTSUP || errno == ENOENT)) {
		int auxv_fd = open("/proc/self/auxv", O_RDONLY);
		auxv_t auxv;

		if (auxv_fd == -1)
			return 0;

		errno = ENOENT;
		while (true) {
			n = read(auxv_fd, &auxv, sizeof(auxv));
			if (n < sizeof(auxv))
				break;
			if (auxv.a_type == type) {
				errno = 0;
				val = auxv.a_un.a_val;
				break;
			}
		}
		close(auxv_fd);
	}

	return val;
}

unsigned long tl_getauxval(unsigned long type)
{
	return __getauxval(type);
}

void print_hwcap(unsigned long val)
{
	printf("AT_HWCAP: ");
#if defined(__aarch64__)
#define HWCAP_NEON (1 << 12)
	if (val & HWCAP_NEON)
		printf("neon");
#elif defined(__x86_64__)
#endif
	printf("\n");
}

int main(void)
{
	unsigned long val;
	char buffer[256];
	pid_t pid = getpid();
	size_t ehdr_size;

	if (sizeof(void *) == 4) {
		ehdr_size = sizeof(Elf32_Ehdr);
	} else if (sizeof(void *) == 8) {
		ehdr_size = sizeof(Elf64_Ehdr);
	} else {
		fprintf(stderr, "ERROR: machine is not 32bit and 64bit.\n");
		exit(1);
	}

	val = tl_getauxval(AT_PLATFORM);
	printf("%-12s: %s\n", "AT_PLATFORM", (const char *)val);

	val = tl_getauxval(AT_EXECFN);
	printf("%-12s: %s\n", "AT_EXECFN", (const char *)val);

	/* see also getpagesize() and sysconf(_SC_PAGESIZE) */
	val = tl_getauxval(AT_PAGESZ);
	printf("%-12s: %ld\n", "AT_PAGESZ", val);

	val = tl_getauxval(AT_HWCAP);
	print_hwcap(val);

	val = tl_getauxval(AT_PHDR);
	printf("AT_PHDR = %lx, start vma = %lx\n", val, val - ehdr_size);
	sprintf(buffer, "cat /proc/%d/maps", pid);
	system(buffer);

	val = tl_getauxval(AT_ENTRY);
	printf("AT_ENTRY = %lx\n", val);

	val = tl_getauxval(AT_SYSINFO);
	printf("AT_SYSINFO = %lx\n", val);

	/* Return VMA [vdso] vm_start */
	void *vdso = (void *)getauxval(AT_SYSINFO_EHDR);
	printf("AT_SYSINFO_EHDR(vdso) = %p\n", vdso);

	return 0;
}
