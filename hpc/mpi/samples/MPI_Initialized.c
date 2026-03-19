#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int myid, numprocs;

	int flag;

	MPI_Initialized(&flag);

	fprintf(stderr, "init: %d\n", flag);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	MPI_Initialized(&flag);

	fprintf(stderr, "init: %d\n", flag);

	MPI_Finalize();
}
