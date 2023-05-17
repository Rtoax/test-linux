#include <stdio.h>
#include <unistd.h>

#include "rdtsc.h"
#include "utils.h"


struct clock_test {
	struct clock *clock;
	pthread_t r, w;
	volatile bool end;
	void (*start)(struct clock_test *);
	void (*stop)(struct clock_test *);
};

volatile uint64_t __cacheline_aligned__ now;
volatile int64_t __cacheline_aligned__ worst_err = 0;

void *reader(void *arg)
{
	struct clock_test *test = arg;
	struct clock *clk = test->clock;

	while (!test->end) {
		now = clk->read();
		now = clk->read();
		now = clk->read();
		now = clk->read();
		now = clk->read();
		now = clk->read();
		now = clk->read();
		now = clk->read();
	}

	return NULL;
}

void *writer(void *arg)
{
	struct clock_test *test = arg;
	struct clock *clk = test->clock;

	while (!test->end) {
		uint64_t oth_now = now;
		barrier();
		uint64_t after = clk->read();

		int64_t err = (int64_t)(oth_now - after);
		if (err >= worst_err)
			worst_err = err;
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

struct clock_test rdtsc_test = {
	.clock = &clock_rdtsc,
	.end = false,
	.start = now_test_start,
	.stop = now_test_stop,
};

void test(struct clock_test *test)
{
	test->start(test);
	sleep(2);
	test->stop(test);

	if (worst_err)
		printf("Worst errr %ld\n", worst_err);
}

int main(void)
{
	test(&rdtsc_test);

	return 0;
}

