#include <stdio.h>
#include <omp.h>


int m = 3;
#pragma omp threadprivate(m)

int main(int argc, char *argv[])
{
	m = 13;
	omp_set_num_threads(5);

	#pragma omp parallel
	{
		#pragma omp single copyprivate(m)
		{
			m += 50;
		}
		m++;
		printf("m = %d\n",m);
	}

	m = 99;

	#pragma omp parallel
	{
		printf("--m = %d\n",m);
	}

	#pragma omp parallel
	{
		#pragma omp single copyprivate(m)
		{
			m = 101;
		}
		printf("----m = %d\n",m);
	}
}
