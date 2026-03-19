#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	int myid, numprocs;
	int value;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	do {
		if (myid == 0) {
			scanf("%d", &value);
			if (numprocs > 1) {
				MPI_Send(&value, 1, MPI_INT, myid + 1, 0,
					 MPI_COMM_WORLD);
				fprintf(stderr, "%d send (%d) to %d\n", myid,
					value, myid + 1);
			}
		} else {
			MPI_Recv(&value, 1, MPI_INT, myid - 1, 0,
				 MPI_COMM_WORLD, &status);
			fprintf(stderr, "%d receive (%d) to %d\n", myid, value,
				myid + 1);

			if (myid < numprocs - 1) {
				MPI_Send(&value, 1, MPI_INT, myid + 1, 0,
					 MPI_COMM_WORLD);
				fprintf(stderr, "%d send (%d) to %d\n", myid,
					value, myid + 1);
			}
		}
		MPI_Barrier(MPI_COMM_WORLD);
	} while (value >= 0);

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
}
