#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syscall.h>
#include <sys/syscall.h>

#include "nr2s.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

static int compar_sys(const void *a1, const void *a2)
{
	const struct syscall_n_str *s1 = a1;
	const struct syscall_n_str *s2 = a2;
#ifdef DEBUG
	fprintf(stderr, "%s:%d vs %s%d\n", s1->name, s1->num, s2->name, s2->num);
#endif
	return s1->num - s2->num;
}

static __attribute__((unused)) void sort_syscall_n_str(void)
{
#ifdef DEBUG
	fprintf(stderr, "sort syscall_str, size %ld\n", ARRAY_SIZE(syscall_str));
#endif
	qsort(syscall_str, ARRAY_SIZE(syscall_str), sizeof(struct syscall_n_str), compar_sys);
}

void display_sort_syscalls(void)
{
	int i;

	sort_syscall_n_str();

	for (i = 0; i < ARRAY_SIZE(syscall_str); i++) {
		int nr = syscall_str[i].num;
		/* array syscall_str has hole */
		if (!syscall_str[i].name)
			continue;
		printf("%4d(%#04x) %s\n", nr, nr, syscall_str[i].name);
	}
}

void display_raw_syscalls(void)
{
#define NR_SYS(nr)	printf("%30s : %4d(%#04x) %s\n", #nr, nr, nr, syscall_str[nr].name);
#include "nr.h"
#undef NR_SYS
}

int main(int argc, char *argv[])
{
	int i;
	enum {
		DISPLAY_SORT,
		DISPLAY_RAW,
	} display = DISPLAY_SORT;

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "raw"))
			display = DISPLAY_RAW;
		else if (!strcmp(argv[i], "sort"))
			display = DISPLAY_SORT;
	}

	switch (display) {
	case DISPLAY_RAW:
		display_raw_syscalls();
		break;
	case DISPLAY_SORT:
	default:
		display_sort_syscalls();
		break;
	}
	return 0;
}
