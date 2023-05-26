/**
 * see also test-linux/compiler/vectorization
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

int main(void)
{
	struct value_align v = {
		.v = {1, 2, 3, 4, 5}
	};
	long sum1 = sum(v.v);
	long sum2 = sum_align(&v);

	return 0;
}
