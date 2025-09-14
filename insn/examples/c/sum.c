/**
 * see also test-linux/compiler/vectorization
 * ref: https://monoinfinito.wordpress.com/series/vectorization-in-gcc/
 */

#define SIZE (1ULL << 15)

#if defined(TYPE_FLOAT)
typedef float type_t;
#elif defined(TYPE_INT)
typedef int type_t;
#else
# pragma error No type defined, use default 'int'
#endif

struct value_align {
	type_t v[SIZE];
} __attribute__ ((aligned (__BIGGEST_ALIGNMENT__)));

type_t sum(type_t *v)
{
	type_t s = 0;
	unsigned int i;

	for (i = 0; i < SIZE; i++)
		s += v[i];

	return s;
}

type_t sum_align(struct value_align *v)
{
	type_t s = 0;
	unsigned int i;

	for (i = 0; i < SIZE; i++)
		s += v->v[i];

	return s;
}

int main(void)
{
	struct value_align v;
	int i;

	for (i = 0; i < SIZE; i++)
		v.v[i] = i + 1;

	type_t sum1 = sum(v.v);
	type_t sum2 = sum_align(&v);

	(void)sum1;
	(void)sum2;

	return 0;
}
