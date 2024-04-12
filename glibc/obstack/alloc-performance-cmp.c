#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/time.h>
#include <obstack.h>
#ifdef HAVE_JEMALLOC
#define JEMALLOC_NO_RENAME
#include <jemalloc/jemalloc.h>
#define je_malloc malloc
#define je_free free
#endif
#ifdef HAVE_TCMALLOC
#include <gperftools/tcmalloc.h>
#endif

#if 1
#define debug()
#else
#define debug() printf("%s:%d\n",__func__, __LINE__)
#endif

unsigned long int test_alloc_size =  1500;
unsigned long int test_alloc_free_cnt = 9999999UL;

void *mymalloc(ssize_t size) { debug(); return malloc(size); }
void myfree(void *ptr) { debug(); free(ptr); }

#ifdef HAVE_JEMALLOC
void *myje_malloc(ssize_t size) { debug(); return je_malloc(size); }
void myje_free(void *ptr) { debug(); je_free(ptr); }
#endif

#ifdef HAVE_TCMALLOC
void *mytc_malloc(ssize_t size) { debug(); return tc_malloc(size); }
void mytc_free(void *ptr) { debug(); tc_free(ptr); }
#endif

unsigned long int diff_timeval(const char *prefix, struct timeval *big, struct timeval *small)
{
	unsigned long int diffsec = big->tv_sec - small->tv_sec;
	unsigned long int diffusec = diffsec * 1000000UL + (big->tv_usec - small->tv_usec);
	printf("%-32s %ld ms\n", prefix, diffusec);
	return diffusec;
}

void test_mem(void *mem, ssize_t size)
{
	/* TODO */
}

void test_malloc(void)
{
	struct timeval start, end;
	char *str = NULL;
	unsigned long int i;

	gettimeofday(&start, NULL);
	for (i = 0; i < test_alloc_free_cnt; i++) {
		str = malloc(test_alloc_size);
		test_mem(str, test_alloc_size);
		free(str);
	}
	gettimeofday(&end, NULL);
	diff_timeval(" Malloc>>", &end, &start);
}

#ifdef HAVE_JEMALLOC_OBSTACK
//gcc obstack-demo3-combine-jemalloc-cmp.c -DHAVE_JEMALLOC -ljemalloc -DHAVE_JEMALLOC_OBSTACK
#define obstack_chunk_alloc myje_malloc
#define obstack_chunk_free myje_free
#define obstack_alloc_failed_handler  TODO
#elif defined(HAVE_TCMALLOC_OBSTACK)
//gcc obstack-demo3-combine-jemalloc-cmp.c -DHAVE_JEMALLOC -ljemalloc -DHAVE_TCMALLOC -ltcmalloc -DHAVE_TCMALLOC_OBSTACK
#define obstack_chunk_alloc mytc_malloc
#define obstack_chunk_free mytc_free
#define obstack_alloc_failed_handler  TODO
#else
//gcc obstack-demo3-combine-jemalloc-cmp.c -DHAVE_JEMALLOC -ljemalloc
#define obstack_chunk_alloc mymalloc
#define obstack_chunk_free myfree
#define obstack_alloc_failed_handler  TODO
#endif

void test_obstack(void)
{
	struct obstack string_obstack;
	char *str = NULL;
	struct timeval start, end;
	unsigned long int i;

	obstack_init(&string_obstack);

	gettimeofday(&start, NULL);
	for (i = 0; i < test_alloc_free_cnt; i++) {
		str = (char *)obstack_alloc(&string_obstack, test_alloc_size);
		test_mem(str, test_alloc_size);
		obstack_free(&string_obstack, str);
	}
	gettimeofday(&end, NULL);
	diff_timeval("Obstack>>",  &end, &start);
}

void test_jemalloc(void)
{
#ifdef HAVE_JEMALLOC
	char *str = NULL;
	struct timeval start, end;
	unsigned long int i;

	gettimeofday(&start, NULL);
	for (i = 0; i < test_alloc_free_cnt; i++) {
		str = (char *)je_malloc(test_alloc_size);
		test_mem(str, test_alloc_size);
		je_free(str);
	}
	gettimeofday(&end, NULL);
	diff_timeval("Jemallo>>",  &end, &start);
#endif
}

void test_tcmalloc(void)
{
#ifdef HAVE_TCMALLOC
	char *str = NULL;
	struct timeval start, end;
	unsigned long int i;

	gettimeofday(&start, NULL);
	for (i = 0; i < test_alloc_free_cnt; i++) {
		str = (char *)tc_malloc (test_alloc_size);
		test_mem(str, test_alloc_size);
		tc_free(str);
	}
	gettimeofday(&end, NULL);
	diff_timeval("TCmallo>>",  &end, &start);
#endif
}

void test_obstack_jemalloc(void)
{
#ifdef HAVE_JEMALLOC
	struct obstack string_obstack;
	char *str = NULL;
	struct timeval start, end;
	unsigned long int i;

	obstack_init(&string_obstack);

	gettimeofday(&start, NULL);
	for (i = 0; i < test_alloc_free_cnt; i++) {
		str = (char *)obstack_alloc(&string_obstack, test_alloc_size);
		test_mem(str, test_alloc_size);
		obstack_free(&string_obstack, str);
	}
	gettimeofday(&end, NULL);
	diff_timeval("ObJemal>>",  &end, &start);
#endif
}

int main(int argc, char *argv[])
{
	unsigned long int cnt = 0;
	switch (argc) {
	case 3:
		cnt = strtoul(argv[2], NULL, 0);
		test_alloc_size = cnt ? cnt : test_alloc_size;
	case 2:
		cnt = strtoul(argv[1], NULL, 0);
		test_alloc_free_cnt = cnt ? cnt : test_alloc_free_cnt;
	case 1:
	default:
		printf("Usage: %s [block-size] [num-of-loop].\n", argv[0]);
		printf("Test mem size %ld, loop times %ld.\n",
			test_alloc_size, test_alloc_free_cnt);
		break;
	}

	test_malloc();
	test_obstack();
	test_jemalloc();
	test_tcmalloc();
	return 0;
}

