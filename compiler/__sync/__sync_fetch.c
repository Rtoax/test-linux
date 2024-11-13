/**
 * type __sync_fetch_and_add (type *ptr, type value, ...)
 * type __sync_fetch_and_sub (type *ptr, type value, ...)
 * type __sync_fetch_and_or (type *ptr, type value, ...)
 * type __sync_fetch_and_and (type *ptr, type value, ...)
 * type __sync_fetch_and_xor (type *ptr, type value, ...)
 * type __sync_fetch_and_nand (type *ptr, type value, ...)
 *
 *	{ tmp = *ptr; *ptr op= value; return tmp; }
 *	{ tmp = *ptr; *ptr = ~(tmp & value); return tmp; }   // nand
 *
 * type __sync_add_and_fetch (type *ptr, type value, ...)
 * type __sync_sub_and_fetch (type *ptr, type value, ...)
 * type __sync_or_and_fetch (type *ptr, type value, ...)
 * type __sync_and_and_fetch (type *ptr, type value, ...)
 * type __sync_xor_and_fetch (type *ptr, type value, ...)
 * type __sync_nand_and_fetch (type *ptr, type value, ...)
 *
 *	{ *ptr op= value; return *ptr; }
 *	{ *ptr = ~(*ptr & value); return *ptr; }   // nand
 */
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

#define NR_LOOP 1000
#define NR_THREAD 10

atomic_int acnt;
int cnt;

void *test__sync_add(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__sync_fetch_and_add(&acnt, 1);
		__sync_add_and_fetch(&acnt, 1);
		cnt++;
		++cnt;
	}
	return 0;
}

void *test__sync_sub(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__sync_fetch_and_sub(&acnt, 1);
		__sync_sub_and_fetch(&acnt, 1);
		cnt--;
		--cnt;
	}
	return 0;
}

void *test__sync_or(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__sync_fetch_and_or(&acnt, 0xFF);
		__sync_or_and_fetch(&acnt, 0x00);
		cnt |= 0xFF;
		/* TODO */
	}
	return 0;
}

void *test__sync_and(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__sync_fetch_and_and(&acnt, 0xFF);
		__sync_and_and_fetch(&acnt, 0x00);
		cnt &= 0xFF;
		/* TODO */
	}
	return 0;
}

void *test__sync_xor(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__sync_fetch_and_xor(&acnt, 0xFF);
		__sync_xor_and_fetch(&acnt, 0x00);
		cnt ^= 0xFF;
		cnt ^= 0x00;
	}
	return 0;
}

void *test__sync_nand(void *thr_data)
{
	int n;
	for (n = 0; n < NR_LOOP; ++n) {
		__sync_fetch_and_nand(&acnt, 0xFF);
		__sync_nand_and_fetch(&acnt, 0x00);
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
	if (acnt != expect) {
		fprintf(stderr, "ERROR: %u != %u\n", acnt, expect);
	}
}

int main(void)
{
	exec_threads(" add", test__sync_add, 0, NR_LOOP * NR_THREAD * 2);
	exec_threads(" sub", test__sync_sub, NR_LOOP * NR_THREAD * 2, 0);
	exec_threads("  or", test__sync_or, 0, 0xFF);
	exec_threads(" and", test__sync_and, 0, 0);
	exec_threads(" xor", test__sync_xor, 0, 0);
	exec_threads("nand", test__sync_nand, 0, 0);
	return 0;
}

