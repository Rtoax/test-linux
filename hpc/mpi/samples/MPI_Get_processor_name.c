#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	int myid, numprocs;
	int namelen;
	int version, subversion;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	MPI_Get_processor_name(processor_name, &namelen);
	MPI_Get_version(&version, &subversion);

	/* mpirun -n 10 ./a */
	fprintf(stdout, "stdout Process %d of %d on %s\n", myid, numprocs,
		processor_name);
	fprintf(stderr, "version %d.%d \n", version, subversion);

	MPI_Finalize();
}
