#include <stdio.h>
#include <string.h>
#include <jemalloc/jemalloc.h>

//arenas.lookup (unsigned, void*) rw
//	Index of the arena to which an allocation belongs to.
#define HUGE_SZ (2 << 20)



void jemalloc_arenas_lookup(unsigned *value, void *ptr, size_t ptr_len)
{
	size_t size = sizeof(unsigned);
	je_mallctl("arenas.lookup", value, &size, ptr, ptr_len);
//	je_mallctl("arenas.lookup", value, &size, NULL, 0);
}

void test_1(){

	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);

	unsigned arena1, arena2;
	size_t sz = sizeof(unsigned);

	je_mallctl("arenas.create", &arena1, &sz, NULL, 0);
	printf("arenas.create arena1 = %d\n", arena1);

	void *huge = je_mallocx(HUGE_SZ, MALLOCX_ARENA(arena1));

	je_mallctl("arenas.lookup", &arena2, &sz, &huge,sizeof(huge));
	printf("arenas.lookup arena2 = %d\n", arena2);

	je_dallocx(huge, MALLOCX_ARENA(arena1));

	void *huge2 = je_mallocx(HUGE_SZ, 0);

	je_mallctl("arenas.lookup", &arena2, &sz, &huge2, sizeof(huge2));
	printf("arenas.lookup arena2 = %d\n", arena2);

	je_dallocx(huge2, 0);

}

void test_2(){

	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);

	unsigned arena1, arena2;
	size_t size = sizeof(arena1);

	je_mallctl("arenas.create", &arena1, &size, NULL, 0);
	printf("arena1 = %d\n", arena1);

	void *str = je_mallocx(HUGE_SZ, MALLOCX_ARENA(arena1));

	je_dallocx(str, MALLOCX_ARENA(arena1));

	je_mallctl("arenas.lookup", &arena2, &size, &str, sizeof(str));
	printf("arena2 = %d\n", arena2);

	void *str2 = je_mallocx(HUGE_SZ, MALLOCX_ARENA(arena1));
	jemalloc_arenas_lookup(&arena2, &str2, sizeof(str2));
	printf("arena2 = %d\n", arena2);

	void *str3 = je_malloc(HUGE_SZ);
	jemalloc_arenas_lookup(&arena2, &str3, sizeof(str3));
	printf("arena2 = %d\n", arena2);

}

int main()
{
	test_1();
	test_2();

}


