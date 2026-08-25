#include <stdbool.h>

struct test_st {
	int a;
	bool uninit;
};

int main(void)
{
	struct test_st st = {
		.a = 1,
	};
	if (st.uninit) {
	}

	/**
	 * TODO: reproduct https://github.com/bpftrace/bpftrace/pull/5293
	 * runtime error: load of value 188, which is not a valid value for type 'bool'
	 */
	return 0;
}
