/**
 * Check with:
 * $ sudo perf top -p $(pidof memcpy-stress)
 */
#include <argp.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/utsname.h>

#include "proc_helpers.h"

#define KB	(1024)
#define MB	(1024 * KB)
#define GB	(1024 * MB)
#define DEFAULT_ALLOC_MSIZE (1 * GB)

typedef void *(*memcpy_fn)(void *, const void *, size_t);

#ifdef SYMADDR___memcpy_ssse3
static memcpy_fn __memcpy_ssse3;
#define memcpy_stub __memcpy_ssse3
#define memcpy_name "__memcpy_ssse3"
#elif defined(SYMADDR___memcpy_generic)
static memcpy_fn __memcpy_generic;
#define memcpy_stub __memcpy_generic
#define memcpy_name "__memcpy_generic"
#elif defined(SYMADDR___memcpy_simd)
static memcpy_fn __memcpy_simd;
#define memcpy_stub __memcpy_simd
#define memcpy_name "__memcpy_simd"
#elif defined(SYMADDR___memcpy_a64fx) /* arm SVE/SVE2 */
static memcpy_fn __memcpy_a64fx;
#define memcpy_stub __memcpy_a64fx
#define memcpy_name "__memcpy_a64fx"
#elif defined(ARM_SOFTWARE___memcpy_aarch64) /* https://github.com/ARM-software/optimized-routines */
extern void *__memcpy_aarch64(void *, const void *, size_t);
#define memcpy_stub __memcpy_aarch64
#define memcpy_name "__memcpy_aarch64"
#elif defined(ARM_SOFTWARE___memcpy_aarch64_sve)
extern void *__memcpy_aarch64_sve(void *, const void *, size_t);
#define memcpy_stub __memcpy_aarch64_sve
#define memcpy_name "__memcpy_aarch64_sve"
#else
/* fallback to glibc's memcpy */
#define memcpy_stub memcpy
#define memcpy_name "memcpy"
#endif

static size_t block_size = 256;
static size_t msize = DEFAULT_ALLOC_MSIZE;
static size_t alloc_msize = DEFAULT_ALLOC_MSIZE;
static int verbose = false;
static const char *const version = "v0.0.3";

const char argp_prog_doc[] =
	"USAGE: [-b <block_size>] [-s <bytes>] [-a <bytes>] [-v|--verbose]\n";

static const struct argp_option opts[] = {
	{ "block-size", 'b', "BLOCK_SIZE", 0, "block size for each memory copy" },
	{ "msize", 's', "MSIZE", 0, "total size of memory copy" },
	{ "alloc", 'a', "ALLOC", 0, "size of memory allocated use to test" },
	{ "verbose", 'v', NULL, 1, "Display detail" },
	{ "version", 'V', NULL, 1, "Display version" },
	{ "uname", 'U', "UNAME", 1, "Display uname" },
	{},
};

static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	switch (key) {
	case 'b':
		block_size = strtoull(arg, NULL, 10);
		break;
	case 's':
		msize = strtoull(arg, NULL, 10);
		break;
	case 'a':
		alloc_msize = strtoull(arg, NULL, 10);
		break;
	case 'v':
		verbose = true;
		break;
	case 'V':
		printf("version %s\n", version);
		exit(EXIT_SUCCESS);
		break;
	case 'U': {
		struct utsname name;
		uname(&name);
		printf("%s %s %s %s %s\n", name.sysname, name.release,
			name.version, name.machine, name.nodename);
		exit(EXIT_SUCCESS);
		break;
	}
	case ARGP_KEY_ARG:
		argp_usage(state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static const struct argp argp = {
	.options = opts,
	.parser = parse_arg,
	.doc = argp_prog_doc,
};

#if defined(SYMADDR___memcpy_ssse3) || \
    defined(SYMADDR___memcpy_generic) || \
    defined(SYMADDR___memcpy_simd) || \
    defined(SYMADDR___memcpy_a64fx)
static void reloc_addr(void)
{
	unsigned long libc = proc_maps_libc_base_addr_2(NULL);
	(void)libc;
#ifdef SYMADDR___memcpy_ssse3
	__memcpy_ssse3 = (memcpy_fn)(libc + SYMADDR___memcpy_ssse3);
#elif defined(SYMADDR___memcpy_generic)
	__memcpy_generic = (memcpy_fn)(libc + SYMADDR___memcpy_generic);
#elif defined(SYMADDR___memcpy_simd)
	__memcpy_simd = (memcpy_fn)(libc + SYMADDR___memcpy_simd);
#elif defined(SYMADDR___memcpy_a64fx)
	__memcpy_a64fx = (memcpy_fn)(libc + SYMADDR___memcpy_a64fx);
#endif
}
#else
# define reloc_addr()
#endif

static void *map(size_t size)
{
	int i;
	/* Testing memory allocate */
	char *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (mem == MAP_FAILED) {
		fprintf(stderr, "memory allocate fatal. %s\n", strerror(errno));
		exit(1);
	}

	/* page fault */
	for (i = 0; i < size; i += getpagesize())
		mem[i] = '9';

	return mem;
}

static inline unsigned long usecs(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000UL + tv.tv_usec;
}

static inline unsigned long nsecs(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return ts.tv_sec * 1000000000UL + ts.tv_nsec;
}

static inline unsigned long getrand(unsigned long max)
{
	return (unsigned long)(max * 1.0 * rand() / RAND_MAX + 1.0);
}

int main(int argc, char *argv[])
{
	int err;
	size_t i, test_cnt, bytes_cnt, pos;
	char *buf1, *buf2;
	unsigned long start, end, rand_cost = 0;

	err = argp_parse(&argp, argc, argv, 0, NULL, NULL);
	if (err) {
		fprintf(stderr, "argp_parse return %d\n", err);
		return -err;
	}

	reloc_addr();

	buf1 = map(alloc_msize);
	buf2 = map(alloc_msize);

#ifdef RAND_MEM_POS
	unsigned long rand_idx;

	srand(nsecs());

	/**
	 * Get random spent time first
	 */
	test_cnt = bytes_cnt = 0;
	start = usecs();
	while (1) {
		for (i = 0; i < alloc_msize - block_size; i += block_size) {
			rand_idx = getrand(alloc_msize / block_size);
			pos = rand_idx * block_size;
			bytes_cnt += block_size;
			if (bytes_cnt >= msize)
				goto rand_cost_done;
		}
	}
rand_cost_done:
	end = usecs();
	rand_cost = end - start;
	if (verbose) {
		printf("Random cost %ld us\n", rand_cost);
	}
#endif /* RAND_MEM_POS */

	test_cnt = bytes_cnt = 0;

	start = usecs();

	while (1) {
		for (i = 0; i < alloc_msize - block_size; i += block_size) {

#ifdef RAND_MEM_POS
			/* Get random value */
			rand_idx = getrand(alloc_msize / block_size);
			pos = rand_idx * block_size;
#else
			pos = i;
#endif
#ifdef DEBUG
			printf("i = %ld/%ld, pos = %ld\n", i, alloc_msize, pos);
#endif
			/**
			 * |-------------------------------------| buf1
			 * |-------------------------------------| buf2
			 *
			 * If sequential copy
			 * |---|
			 * |---|
			 *     |---|
			 *     |---|
			 *         |---|
			 *         |---|
			 *
			 * If random copy, it may be possible to eliminate the
			 * effects of CPU prefetching
			 *        |---|
			 *        |---|
			 *   |---|
			 *   |---|
			 *                 |---|
			 *                 |---|
			 */
			/* Replace memcpy_stub here */
			memcpy_stub(buf2 + pos, buf1 + pos, block_size);

			bytes_cnt += block_size;
			test_cnt++;

			/* All test copy same memory size */
			if (bytes_cnt >= msize)
				goto test_done;
		}
	}

test_done:
	end = usecs();

	if (verbose) {
		printf("Test %s\n", memcpy_name);
		printf("%-16s %-16s %-16s %-16s %-16s %-16s\n",
			"BLOCK_SIZE(B)", "SPENT(us)", "COUNT", "ALLOC(MB)", "SIZE(MB)", "RATE(MB/s)");
		printf("%-16s %-16s %-16s %-16s %-16s %-16s\n",
			"-------------", "---------", "-----", "---------", "--------", "---------");
	}
	printf("%-16ld %-16ld %-16ld %-16ld %-16ld %-13.2f\n", block_size,
		end - start - rand_cost, test_cnt,
		alloc_msize / MB,
		bytes_cnt / MB,
		bytes_cnt * 1.0f / MB * 1000000UL / (end - start - rand_cost));

	munmap(buf1, alloc_msize);
	munmap(buf2, alloc_msize);

	return 0;
}
