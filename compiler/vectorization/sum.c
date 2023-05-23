#define SIZE (5)

long sum(int *v)
{
	long s = 0;
	unsigned int i;

	for (i = 0; i < SIZE; i++)
		s += v[i];

	return s;
}
