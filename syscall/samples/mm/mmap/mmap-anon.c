#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <wait.h>
#include <errno.h>

#ifdef CONFIG_ANON_VMA_NAME
int rename_vma(unsigned long addr, unsigned long size, char *name)
{
	int res;
	/**
	 * The name can contain only printable ascii characters (isprint(3)),
	 * except '[', ']', '\', '$', and '`'. see R_SET_VMA(2const).
	 */
	res = prctl(PR_SET_VMA, PR_SET_VMA_ANON_NAME, addr, size, name);
	if (res < 0) {
		perror("[!] prctl");
		return -errno;
	}
	return res;
}

/**
 * TODO: I want to add PR_GET_VMA and PR_GET_VMA_ANON_NAME to kernel
 *
 * https://lore.kernel.org/lkml/tencent_77E0BC1E8E9A21CA1B9009DD66555C72A90A@qq.com/
 */
const char *get_vma_name(unsigned long addr)
{
#ifndef PR_GET_VMA
#define PR_GET_VMA             0x53564d42
#define PR_GET_VMA_ANON_NAME          0
#endif
	int ret;
	static char buffer[80];
	ret = prctl(PR_GET_VMA, PR_GET_VMA_ANON_NAME, addr, buffer, 0);
	if (ret) {
		perror("prctl PR_GET_VMA");
		return NULL;
	}
	return strlen(buffer) > 0 ? buffer : NULL;
}
#endif

int main(void)
{
	int i;
	char **mems;
	int nr_mems = 10;
	size_t size = getpagesize();

	mems = (char **)malloc(sizeof(char *) * nr_mems);

	for (i = 0; i < nr_mems; i++) {
		mems[i] = mmap(NULL, size, PROT_READ | PROT_WRITE,
			       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (mems[i] == MAP_FAILED) {
			perror("mmap");
			mems[i] = NULL;
			continue;
		}

		printf("mmap: %p\n", mems[i]);

		/* pagefault */
		memset(mems[i], 'a', size);

#ifdef CONFIG_ANON_VMA_NAME
		char name[80];
		switch (i % 3) {
		case 0:
			snprintf(name, sizeof(name), "vma%d", i);
			break;
		case 1:
			snprintf(name, sizeof(name), "vma");
			break;
		case 2:
			snprintf(name, sizeof(name), "anon");
			break;
		}
		rename_vma((unsigned long)mems[i], size, name);
#else
		fprintf(stderr, "No CONFIG_ANON_VMA_NAME in kernel, skip.\n");
#endif
	}

	char cmd[128];
	snprintf(cmd, sizeof(cmd), "cat /proc/%d/maps", getpid());
	system(cmd);

#ifdef CONFIG_ANON_VMA_NAME
	const char *name = get_vma_name(0);
	printf("%s\n", name ? : "");
	for (i = 0; i < nr_mems && mems[i]; i++) {
		name = get_vma_name((unsigned long)mems[i]);
		printf("%s\n", name ? : "");
	}
#endif

	for (i = 0; i < nr_mems && mems[i]; i++)
		munmap(mems[i], size);

	free(mems);

	return 0;
}
