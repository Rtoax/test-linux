#include <stdio.h>
#include <omp.h>

/*
setenv OMP_SCHEDULE "dynamic, 2"; enviroment variable
*/

static omp_lock_t lock;

int main(int argc, char *argv[])
{

	int i, j, id;

	omp_init_lock(&lock);

	omp_set_num_threads(5);


	#pragma omp parallel for
	for (j = 0; j < 5; j++) {

		omp_set_lock(&lock);

		//#pragma omp crtitical
		printf("- j = %d, id = %d\n",j,omp_get_thread_num());

		printf("+ j = %d, id = %d\n",j,omp_get_thread_num());

		omp_unset_lock(&lock);
	}

	omp_destroy_lock(&lock);

	return 0;
}
