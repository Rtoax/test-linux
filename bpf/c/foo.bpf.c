int foo(void)
{
	/* bpf target default -O2, disable optimize */
	volatile int a, b, c;
	a = 1;
	b = 2;
	c = a + b;
	return c;
}
