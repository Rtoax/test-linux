#include <stdio.h>
#include <unistd.h>

#include "rdtsc.h"
#include "utils.h"


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

void test(struct clock_test *test)
{
	test->start(test);
	sleep(2);
	test->stop(test);

	printf("%-16s: Worst err %ld\n", test->clock->name, test->worst_err);
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

int main(void)
{
	test(&rdtsc_test);
	test(&rdtsc_fence_test);

	return 0;
}

