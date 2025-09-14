#include <stdio.h>
#include <unistd.h>

#include "rdtsc.h"
#include "utils.h"
#include "pthread_helpers.h"


struct clock_test {
	struct clock *clock;
	pthread_t r, w;
	volatile bool end;
	volatile uint64_t __cacheline_aligned__ now;
	volatile int64_t __cacheline_aligned__ worst_err;
	void (*start)(struct clock_test *);
	void (*stop)(struct clock_test *);
};


void *reader(void *arg)
{
	struct clock_test *test = arg;
	struct clock *clk = test->clock;

	while (!test->end) {
		test->now = clk->read();
		test->now = clk->read();
		test->now = clk->read();
		test->now = clk->read();
		test->now = clk->read();
		test->now = clk->read();
		test->now = clk->read();
		test->now = clk->read();
	}

	return NULL;
}

void *writer(void *arg)
{
	struct clock_test *test = arg;
	struct clock *clk = test->clock;

	while (!test->end) {
		uint64_t oth_now = test->now;
		barrier();
		uint64_t after = clk->read();

		int64_t err = (int64_t)(oth_now - after);
		if (err >= test->worst_err)
			test->worst_err = err;
	}

	return NULL;
}

void now_test_start(struct clock_test *test)
{
	test->r = start_thread(reader, 1, test);
	test->w = start_thread(writer, 2, test);
}

void now_test_stop(struct clock_test *test)
{
	test->end = true;

	pthread_join(test->r, NULL);
	pthread_join(test->w, NULL);
}

uint64_t test(struct clock_test *test)
{
	struct timeval start, end;
	int test_interval_s = 2;

	gettimeofday(&start, NULL);

	test->start(test);
	sleep(test_interval_s);
	test->stop(test);

	gettimeofday(&end, NULL);

	end.tv_sec -= test_interval_s;

	return diff_tv_usec(&end, &start);
}

struct clock_test rdtsc_test = {
	.clock = &clock_rdtsc,
	.end = false,
	.now = 0,
	.worst_err = 0,
	.start = now_test_start,
	.stop = now_test_stop,
};

struct clock_test rdtsc_fence_test = {
	.clock = &clock_rdtsc_fence,
	.end = false,
	.now = 0,
	.worst_err = 0,
	.start = now_test_start,
	.stop = now_test_stop,
};

struct clock_test rdtscp_test = {
	.clock = &clock_rdtscp,
	.end = false,
	.now = 0,
	.worst_err = 0,
	.start = now_test_start,
	.stop = now_test_stop,
};

struct clock_test vdso_monotonic_test = {
	.clock = &clock_monotonic,
	.end = false,
	.now = 0,
	.worst_err = 0,
	.start = now_test_start,
	.stop = now_test_stop,
};

struct clock_test vdso_realtime_test = {
	.clock = &clock_realtime,
	.end = false,
	.now = 0,
	.worst_err = 0,
	.start = now_test_start,
	.stop = now_test_stop,
};

struct clock_test vdso_gettimeofday_test = {
	.clock = &clock_gettimeofday,
	.end = false,
	.now = 0,
	.worst_err = 0,
	.start = now_test_start,
	.stop = now_test_stop,
};

struct clock_test *tests[] = {
	&rdtsc_test,
	&rdtsc_fence_test,
	&rdtscp_test,
	&vdso_monotonic_test,
	&vdso_realtime_test,
	&vdso_gettimeofday_test,
};

int main(void)
{
	int i;

	printf(
	"Testing rdtsc/vdso\n"
	"- Err/Diff: Max rdtsc different or nanosecond different\n"
	"\n"
	);
	printf("%-20s %-16s %-16s\n", "NAME", "Err/Diff", "Latency(us)");

	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		struct clock_test *t = tests[i];
		uint64_t us = test(t);
		printf("%-20s %-16ld %-16ld\n",
			t->clock->name, t->worst_err,
			us);
	}

	return 0;
}

