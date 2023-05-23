/**
 * ref: https://monoinfinito.wordpress.com/series/vectorization-in-gcc/
 */

#define SIZE (5)

struct value_align {
	int v[SIZE];
} __attribute__ ((aligned (__BIGGEST_ALIGNMENT__)));

long sum(int *v)
{
	long s = 0;
	unsigned int i;

	for (i = 0; i < SIZE; i++)
		s += v[i];

	return s;
}

long sum_align(struct value_align *v)
{
	long s = 0;
	unsigned int i;

	for (i = 0; i < SIZE; i++)
		s += v->v[i];

	return s;
}
