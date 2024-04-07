#pragma once

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>

struct test {
	const char *name;
	void (*init)(void);
	void (*run)(void);
	void (*fini)(void);
};


#define cr_assert_eq(a, b, fmt...) \
	if ((a) != (b)) { \
		printf("%s != %s\n", #a, #b); \
		assert(0); \
	}

void add_test(struct test *t);

#define Test(func, test_name, init, fini) \
	static void t_##func##test_name(void); \
	static struct test ___t = { \
		.name = #func#test_name, \
		init, \
		.run = t_##func##test_name, \
		fini, \
	}; \
	static void __attribute__((constructor(101))) \
		add_##func##test_name(void) { \
		add_test(&___t); \
	} \
	static void t_##func##test_name(void)

