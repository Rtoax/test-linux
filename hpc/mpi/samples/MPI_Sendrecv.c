#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int i, rank, size;

	float *a = malloc(sizeof(float) * 10);

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (size != 3) {
		if (rank == 0) {
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
	}

	for (i = 0; i < 1; i++) {
		a[i] = 9;
	}

	if (rank == 0) {
		for (i = 0; i < 1; i++) {
			a[i] = 0;
		}
		MPI_Send(a, 1, MPI_FLOAT, 1, 111, MPI_COMM_WORLD);
	} else if (rank == 2) {
		for (i = 0; i < 1; i++) {
			a[i] = 2;
		}
		MPI_Recv(a, 1, MPI_FLOAT, 1, 111, MPI_COMM_WORLD, &status);
	} else if (rank == 1) {
		for (i = 0; i < 1; i++) {
			a[i] = 1;
		}
#ifdef CONFIG_MPI_Sendrecv_replace
		MPI_Sendrecv_replace(a, 1, MPI_FLOAT, 2, 111, 0, 111,
				     MPI_COMM_WORLD, &status);
#else
		MPI_Sendrecv(a, 1, MPI_FLOAT, 2, 111, a, 1, MPI_FLOAT, 0, 111,
			     MPI_COMM_WORLD, &status);
#endif
	}

	for (i = 0; i < 1; i++) {
		printf("rank = %d, a[%d] = %f\n", rank, i, a[i]);
	}

	MPI_Finalize();
}
