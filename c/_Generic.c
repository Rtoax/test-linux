#include <math.h>
#include <stdio.h>


int print_int(int i)
{
	return printf("int: %d\n", i);
}

int print_long(long l)
{
	return printf("long: %ld\n", l);
}

int print_float(float f)
{
	return printf("float: %f\n", f);
}

int print_double(double d)
{
	return printf("double: %lf\n", d);
}

#define __print(v) _Generic((v), \
		int:	print_int, \
		long:	print_long, \
		float:	print_float, \
		double:	print_double)(v)

#define print(v) do {\
		printf("%30s : ", #v); \
		__print(v); \
	} while (0)

int main(void)
{
	int i = 1;
	long l = 2;

	print(i);
	print((long)i);
	print(l);
	print((int)l);
	print(3.0f);
	print(4.0);
	print((double)5.0f);

	return 0;
}
