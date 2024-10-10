void foo(int n, int *a, int *b, int *c)
{
	int i;
/**
 * see gcc git://gcc.gnu.org/git/gcc.git
 * commit 6fb5da03107f ("frontend: Add novector C pragma")
 */
#if defined(__GNUC__) && (__GNUC__ >= 14)
	#pragma GCC novector
#endif
	for (i = 0; i < n; ++i)
		a[i] = b[i] + c[i];
}

int main(void)
{
	int a[2], b[2], c[2];
	foo(2, a, b, c);
	return 0;
}
