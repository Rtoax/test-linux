/**
 * type __atomic_add_fetch (type *ptr, type val, int memorder)
 * type __atomic_sub_fetch (type *ptr, type val, int memorder)
 * type __atomic_and_fetch (type *ptr, type val, int memorder)
 * type __atomic_xor_fetch (type *ptr, type val, int memorder)
 * type __atomic_or_fetch (type *ptr, type val, int memorder)
 * type __atomic_nand_fetch (type *ptr, type val, int memorder)
 *
 *     { *ptr op= val; return *ptr; }
 *     { *ptr = ~(*ptr & val); return *ptr; } // nand
 *
 *
 * type __atomic_fetch_add (type *ptr, type val, int memorder)
 * type __atomic_fetch_sub (type *ptr, type val, int memorder)
 * type __atomic_fetch_and (type *ptr, type val, int memorder)
 * type __atomic_fetch_xor (type *ptr, type val, int memorder)
 * type __atomic_fetch_or (type *ptr, type val, int memorder)
 * type __atomic_fetch_nand (type *ptr, type val, int memorder)
 *
 *     { tmp = *ptr; *ptr op= val; return tmp; }
 *     { tmp = *ptr; *ptr = ~(*ptr & val); return tmp; } // nand
 */
#include <stdio.h>
#include <pthread.h>

#define NR_LOOP 1000
#define NR_THREAD 10

int acnt;
int cnt;

int order = __ATOMIC_RELAXED;

void *test__atomic_add(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__atomic_fetch_add(&acnt, 1, order);
		__atomic_add_fetch(&acnt, 1, order);
		cnt++;
		++cnt;
	}
	return 0;
}

void *test__atomic_sub(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__atomic_fetch_sub(&acnt, 1, order);
		__atomic_sub_fetch(&acnt, 1, order);
		cnt--;
		--cnt;
	}
	return 0;
}

void *test__atomic_or(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__atomic_fetch_or(&acnt, 0xFF, order);
		__atomic_or_fetch(&acnt, 0x00, order);
		cnt |= 0xFF;
		/* TODO */
	}
	return 0;
}

void *test__atomic_and(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__atomic_fetch_and(&acnt, 0xFF, order);
		__atomic_and_fetch(&acnt, 0x00, order);
		cnt &= 0xFF;
		/* TODO */
	}
	return 0;
}

void *test__atomic_xor(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__atomic_fetch_xor(&acnt, 0xFF, order);
		__atomic_xor_fetch(&acnt, 0x00, order);
		cnt ^= 0xFF;
		cnt ^= 0x00;
	}
	return 0;
}

void *test__atomic_nand(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__atomic_fetch_nand(&acnt, 0xFF, order);
		__atomic_nand_fetch(&acnt, 0x00, order);
		cnt = ~(cnt & 0xFF);
		cnt = ~(cnt & 0x00);
	}
	return 0;
}

void exec_threads(const char *pfx, void *(*fn)(void *), int init, int expect)
{
	int n;
	pthread_t thr[NR_THREAD];

	acnt = init;
	cnt = init;

	for (n = 0; n < NR_THREAD; ++n)
		pthread_create(&thr[n], NULL, fn, NULL);

	for (n = 0; n < NR_THREAD; ++n)
		pthread_join(thr[n], NULL);

	printf("%s: atomic counter is %10u, non-atomic %10u\n", pfx, acnt, cnt);
	if (acnt != expect)
		fprintf(stderr, "ERROR: %u != %u\n", acnt, expect);
}

int main(void)
{
	exec_threads(" add", test__atomic_add, 0, NR_LOOP * NR_THREAD * 2);
	exec_threads(" sub", test__atomic_sub, NR_LOOP * NR_THREAD * 2, 0);
	exec_threads("  or", test__atomic_or, 0, 0xFF);
	exec_threads(" and", test__atomic_and, 0, 0);
	exec_threads(" xor", test__atomic_xor, 0, 0);
	exec_threads("nand", test__atomic_nand, 0, 0xffffffff);
	return 0;
}
