#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <wait.h>


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
#if 0
		char name[80];
		snprintf(name, sizeof(name), "vma%d", i);
#else
		char name[80];
		char test_str[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		memcpy(name, test_str, 72);
		char store[8];
		memset(store, 0, 8);
		sprintf(store, "%d", i);
		memcpy(&name[72], store, 8);
#endif

		int ret = prctl(PR_SET_VMA, PR_SET_VMA_ANON_NAME, mems[i], size, name);
		if (ret)
			perror("prctl");
#else
		fprintf(stderr, "No CONFIG_ANON_VMA_NAME in kernel, skip.\n");
#endif
	}

	system("cat /proc/self/maps");

	for (i = 0; i < nr_mems && mems[i]; i++)
		munmap(mems[i], size);

	free(mems);

	return 0;
}
