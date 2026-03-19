#include <stdio.h>
#include <math.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	int myid, numprocs;
	char message[20];

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	if (myid == 0) {
		strcpy(message, "hello, process I");
		MPI_Send(message, 20, MPI_CHAR, 1, 999, MPI_COMM_WORLD);
	} else if (myid == 1) {
		MPI_Recv(message, 20, MPI_CHAR, 0, 999, MPI_COMM_WORLD,
			 &status);
		printf("received : %s\n", message);
	}

	MPI_Finalize();
}
