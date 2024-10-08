void foo(int n, int *a, int *b, int *c)
{
	int i;

	#pragma GCC novector
	for (i = 0; i < n; ++i)
		a[i] = b[i] + c[i];
}

int main(void)
{
	int a[2], b[2], c[2];
	foo(2, a, b, c);
	return 0;
}
