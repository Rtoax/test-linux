/**
 * NOTE: test-linux bpf target default -O2, volatile disable optimize.
 */
int foo(void)
{
	int a, b, c;
	a = 1;
	b = 2;
	c = a + b;
	return c;
}
